// SessDesc.cpp: implementation of the CSessDesc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileManager.h"
#include "FileInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UINT Process( LPVOID pParam )
{
	CSessDesc* pDes = (CSessDesc*)pParam;
	if (!pDes || !pDes->IsValid ())
		return 0;
	CBaseCom* pCom = pDes->m_pCom;
	if (!pCom)
		return 0;

	struct timeval t;
	struct timeval* pt;
	if (pDes->m_dwTimeOut)
	{
		pt = &t;
		t.tv_sec = pDes->m_dwTimeOut / 1000;
		t.tv_usec = (pDes->m_dwTimeOut % 1000)* 1000;
	}
	else
	{
		pt = NULL;
	}

	while (TRUE)
	{
		fd_set	fdr;
		FD_ZERO (&fdr);

		if (!pDes->IsValid ())
			return 0;
		else
			FD_SET (pDes->GetClientSock (), &fdr);

		if (::select (0, &fdr, NULL, NULL, pt))
		{
			int nError;
			if (FD_ISSET (pDes->GetClientSock (), &fdr))
			{
				nError = pDes->Hear ();
				if (nError)
				{
					pCom->OnCloseSession (pDes, nError);
					return 0;
				}
				else
				{
					while (!nError && pDes->CheckMsg ())
					{
						nError = pCom->OnReceiveMsg (pDes, pDes->m_msg);
						if (nError)
						{
							pCom->OnCloseSession (pDes, nError);
							return 0;
						}
						else
							pDes->Copy ();
					}
				}
			}
			if (pDes->IsDownState ())
			{
				if (!pDes->ProcDown ())
				{
					pCom->OnCloseSession (pDes, ERROR_CLIENTSEND);
					return 0;
				}
			}
		}
		else
		{
			pCom->OnCloseSession (pDes, ERROR_RECVTIMEOUT);
			return 0;
		}
	}

	return 0;
}

CSessDesc::CSessDesc(CBaseCom* pCom)
{
	m_pCom = pCom;
	m_buf = (char*)m_msg.GetBuf ();
	m_nRdCnt = 0;
	m_sockClient = INVALID_SOCKET;
	m_nState = stateNone;
	m_hThread = NULL;
	m_dwCurrentDown = m_dwCurrentSend = 0;
	m_bInstFlag = FALSE;
}

CSessDesc::~CSessDesc()
{
	Close ();
}

BOOL CSessDesc::Create (SOCKET sockListen)
{
	Close ();

	m_sockClient = accept (sockListen, NULL, NULL);
	if (m_sockClient == INVALID_SOCKET)
		return FALSE;

	if (m_pCom)
		m_dwTimeOut = m_pCom->m_dwTimeOut;
	else
		m_dwTimeOut = 0;

	DWORD dwThreadID;
	m_hThread = ::CreateThread (NULL, 0, 
		(LPTHREAD_START_ROUTINE)Process, this, 0, &dwThreadID);
	if (!m_hThread)
	{
		Close ();
		return FALSE;
	}

	return TRUE;
}

void CSessDesc::Close ()
{
	m_hThread = NULL;

	if (m_sockClient != INVALID_SOCKET)
	{
		shutdown (m_sockClient, SD_BOTH);
		closesocket (m_sockClient);
		m_sockClient = INVALID_SOCKET;
	}
	if (m_nState == stateDown)
		m_file.Close ();

	m_listFile.RemoveAll ();
	m_bInstFlag = FALSE;
	m_nState = stateNone;
	m_nRdCnt = 0;
	m_msg.Clear ();
	m_dwCurrentDown = m_dwCurrentSend = 0;
}

BOOL CSessDesc::Connect (CBaseCom* pCom, LPCTSTR lpszAddr, int nPort)
{
	Close ();

	m_pCom = pCom;
	m_sockClient = OpenClient (lpszAddr, nPort);
	if (m_sockClient == INVALID_SOCKET)
		return FALSE;

	m_dwTimeOut = 0;

	DWORD dwThreadID;
	m_hThread = ::CreateThread (NULL, 0, 
		(LPTHREAD_START_ROUTINE)Process, this, 0, &dwThreadID);
	if (!m_hThread)
	{
		Close ();
		return FALSE;
	}
	return TRUE;
}

BOOL CSessDesc::CheckMsg ()
{
	if (m_nRdCnt < 4)
		return FALSE;
	int nSize = m_msg.GetSize ();
	if (DEFAULT_SIZE < nSize)
	{
		m_msg.Clear ();
		m_nRdCnt = 0;
		return FALSE;
	}
	if (m_nRdCnt < nSize)
		return FALSE;
	return TRUE;
}

int CSessDesc::Hear ()
{
	if (m_sockClient == INVALID_SOCKET)
		return ERROR_INVALID;

	int nRecv = recv (m_sockClient, m_buf + m_nRdCnt, 
		DEFAULT_SIZE - m_nRdCnt, 0);
	if (nRecv <= 0)
		return ERROR_CLIENTRECV;
	m_nRdCnt += nRecv;
	return 0;
}

int CSessDesc::Say (CMsg& msg)
{
	if (m_sockClient == INVALID_SOCKET)
		return ERROR_INVALID;

	int nSize = msg.GetSize ();
	char* pBuf = (char*)msg.GetBuf ();

	if (::send (m_sockClient, pBuf, nSize, 0) < 0)
		return ERROR_CLIENTSEND;

	return 0;
}

void CSessDesc::Copy ()
{
	int nSize = m_msg.GetSize ();
	m_msg.Clear ();
	m_nRdCnt -= nSize;
	if (m_nRdCnt)
		memmove (m_buf, m_buf + nSize, m_nRdCnt);
}

CFileInfo* CSessDesc::GetFileInfo ()
{
	if (m_listFile.IsEmpty ())
		return NULL;

	CFileInfo* pInfo = (CFileInfo*)m_listFile.RemoveHead ();
	m_strFileName = pInfo->m_strPathName;
	return pInfo;
}

int CSessDesc::GetNumDownFile()
{
	return m_listFile.GetCount ();
}

void CSessDesc::AddFileInfo (CFileInfo* pInfo)
{
	m_listFile.AddTail (pInfo);
}

BOOL CSessDesc::ProcDown()
{
	if (m_dwCurrentDown + m_pCom->m_dwSendHold < m_dwCurrentSend)
		return TRUE;

	CMsg msg;
	msg.ID (FM_DOWN_ACK);
	int nToRead = m_pCom->m_dwThreadHold;
	int nRead = m_file.Read ((BYTE*)msg.GetBuf () + 4, nToRead);
	if (nRead < nToRead)
	{
		m_file.Close ();
		m_dwCurrentSend = m_dwCurrentDown = 0;
		m_nState = stateNone;
	}

	if (nRead)
	{
		memcpy ((BYTE*)msg.GetBuf () + 2, &nRead, 2);
		Say (msg);
		m_dwCurrentSend += nRead;
	}

	return TRUE;
}

BOOL CSessDesc::StartDown ()
{
	if (!m_file.Open (m_strFileName, CFile::modeRead | CFile::shareDenyNone))
		return FALSE;

	m_nState = stateDown;
	m_dwCurrentDown = m_dwCurrentSend = 0;
	return TRUE;
}

DWORD CSessDesc::GetLengthTotalFile()
{
	DWORD dwLength = 0;
	POSITION pos = m_listFile.GetHeadPosition ();
	while (pos)
	{
		CFileInfo* pInfo = (CFileInfo*)m_listFile.GetNext (pos);
		dwLength += pInfo->m_dwLength;
	}
	return dwLength;	
}

