// SessDesc.cpp: implementation of the CSessDesc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Starter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSessDesc::CSessDesc()
{
	m_buf = (char*)m_msg.GetBuf ();
	m_nRdCnt = m_nWrCntClient = m_nWrCntServer = 0;
	m_sockServer = m_sockClient = INVALID_SOCKET;
	m_pObject = NULL;
	m_fLoginSucc = FALSE;
}

CSessDesc::~CSessDesc()
{
	Close ();
}

BOOL CSessDesc::Create (SOCKET sockListen)
{
	Close ();

	m_sockClient = accept (sockListen, NULL, NULL);
	if (m_sockClient != INVALID_SOCKET)
	{
		u_long argp = 1;
		ioctlsocket (m_sockClient, FIONBIO, &argp);

		m_dwLastTime = GetTickCount ();
		return TRUE;
	}
	return FALSE;
}

void CSessDesc::Close ()
{
	if (m_sockClient != INVALID_SOCKET)
	{
		if (m_nWrCntClient)
			send (m_sockClient, (char*)&m_bufClient[0], 
				m_nWrCntClient, 0);
		shutdown (m_sockClient, SD_BOTH);
		closesocket (m_sockClient);
		m_sockClient = INVALID_SOCKET;
	}
	if (m_sockServer != INVALID_SOCKET)
	{
		if (m_nWrCntServer)
			send (m_sockServer, (char*)&m_bufServer[0], 
				m_nWrCntServer, 0);
		shutdown (m_sockServer, SD_BOTH);
		closesocket (m_sockServer);
		m_sockServer = INVALID_SOCKET;
	}
	m_nRdCnt = m_nWrCntClient = m_nWrCntServer = 0;
	m_msg.Clear ();
}

BOOL CSessDesc::Connect (LPCTSTR lpszAddr, int nPort)
{
	Close ();

	m_sockClient = OpenClient (lpszAddr, nPort);
	return (m_sockClient != INVALID_SOCKET);
}

BOOL CSessDesc::Link (LPCTSTR lpszAddr, int nPort)
{
	if (m_sockClient == INVALID_SOCKET)
		return FALSE;

	m_nRdCnt = m_nWrCntClient = m_nWrCntServer = 0;
	m_sockServer = OpenClient (lpszAddr, nPort);
	return (m_sockServer != INVALID_SOCKET);
}

void CSessDesc::Unlink ()
{
	m_nRdCnt = m_nWrCntClient = m_nWrCntServer = 0;
	if (m_sockServer != INVALID_SOCKET)
	{
		shutdown (m_sockServer, SD_BOTH);
		closesocket (m_sockServer);
		m_sockServer = INVALID_SOCKET;
	}
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

	return Send (CLIENT, pBuf, nSize);
}

void CSessDesc::Copy ()
{
	int nSize = m_msg.GetSize ();
	m_msg.Clear ();
	m_nRdCnt -= nSize;
	if (m_nRdCnt)
		memmove (m_buf, m_buf + nSize, m_nRdCnt);
}

int CSessDesc::ClientToServer ()
{
	if (m_sockServer == INVALID_SOCKET ||
		m_sockClient == INVALID_SOCKET)
		return ERROR_INVALID;

	int nRecv = recv (m_sockClient, m_buf, DEFAULT_SIZE, 0);
	if (nRecv <= 0)
		return ERROR_CLIENTRECV;

	return Send (SERVER, m_buf, nRecv);
}

int CSessDesc::ServerToClient ()
{
	if (m_sockServer == INVALID_SOCKET ||
		m_sockClient == INVALID_SOCKET)
		return ERROR_INVALID;

	int nRecv = recv (m_sockServer, m_buf, DEFAULT_SIZE, 0);
	if (nRecv <= 0)
		return ERROR_SERVERRECV;

	return Send (CLIENT, m_buf, nRecv);
}

int CSessDesc::Send (int nTarget, char* pBufSrc, int nSize)
{
	if (nTarget == CLIENT)
	{
		if (m_nWrCntClient + nSize > MAX_BUF)
			return ERROR_CLIENTSEND;
		memcpy (&m_bufClient[m_nWrCntClient], pBufSrc, nSize);
		m_nWrCntClient += nSize;
	}
	else
	{
		if (m_nWrCntServer + nSize > MAX_BUF)
			return ERROR_CLIENTSEND;
		memcpy (&m_bufServer[m_nWrCntServer], pBufSrc, nSize);
		m_nWrCntServer += nSize;
	}
	return 0;
}
