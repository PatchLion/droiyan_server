// FileManagerCom.cpp: implementation of the CFileManagerCom class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileManager.h"
#include "FileManagerCom.h"
#include "FileInfo.h"

#include "VerSet.h"
#include "PatchVer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define ERROR_VER			(ERROR_USER + 0)
#define ERROR_INFO			(ERROR_USER + 1)
#define ERROR_DOWN			(ERROR_USER + 2)
#define ERROR_FILE			(ERROR_USER + 3)
#define ERROR_ENDDOWN		(ERROR_USER + 4)

#define INSTALL_FILE		_T("inst.exe")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileManagerCom::CFileManagerCom(LPCTSTR lpszServerName) :
CBaseCom (lpszServerName)
{
	m_pInfoInst = NULL;
}

CFileManagerCom::~CFileManagerCom()
{
}

BOOL CFileManagerCom::Process()
{
	return CBaseCom::Process ();
}

void CFileManagerCom::OnPauseService()
{
	if (m_pInfoInst)
	{
		delete m_pInfoInst;
		m_pInfoInst = NULL;
	}

	while (!m_listFile.IsEmpty ())
		delete m_listFile.RemoveHead ();

	CBaseCom::OnPauseService ();
}

BOOL CFileManagerCom::OnContinueService()
{
	if (!GetConfigString (NULL, _T("SrcPath"), m_strFilePath))
		return FALSE;

	if (!GetConfigInt (NULL, _T("Hold"), (int&)m_dwThreadHold))
		return FALSE;

	if (!LoadInstallFile ())
		return FALSE;

	if (!LoadFileZipInfo ())
		return FALSE;
	
//	if (!LoadFileInfo ())
//		return FALSE;

	return CBaseCom::OnContinueService ();
}

void CFileManagerCom::OnStopService()
{
	if (m_pInfoInst)
	{
		delete m_pInfoInst;
		m_pInfoInst = NULL;
	}

	while (!m_listFile.IsEmpty ())
		delete m_listFile.RemoveHead ();

	CBaseCom::OnStopService ();
}

BOOL CFileManagerCom::OnStartService()
{
	if (!CBaseCom::OnStartService ())
		return FALSE;

	if (!GetConfigString (NULL, _T("SrcPath"), m_strFilePath))
		return FALSE;

	if (!GetConfigInt (NULL, _T("Hold"), (int&)m_dwSendHold))
		m_dwSendHold = 4096;

	if (!GetConfigInt (NULL, _T("Buf"), (int&)m_dwThreadHold))
		m_dwThreadHold = 1024;

	if (!LoadInstallFile ())
		return FALSE;

	if (!LoadFileZipInfo ())
		return FALSE;

//	if (!LoadFileInfo ())
//		return FALSE;

	return TRUE;
}

void CFileManagerCom::OnTimer ()
{
	CBaseCom::OnTimer ();
}

BOOL CFileManagerCom::OnOpenSession (CSessDesc* pDes)
{
	return CBaseCom::OnOpenSession (pDes);
}

void CFileManagerCom::OnCloseSession (CSessDesc* pDes, int nCode)
{
	CBaseCom::OnCloseSession (pDes, nCode);
}

int CFileManagerCom::OnReceiveMsg (CSessDesc* pDes, CMsg& msg)
{
	switch (msg.ID ())
	{
	case 0	: 
		{
			CMsg msgSend;
			msgSend.ID (0) 
				<< (BYTE)m_fSuspend
				<< m_listActive.GetCount ();
			pDes->Say (msgSend);
		}
		return 0;
	case FM_VERSIONINFO_REQ :	return OnFMVersioninfoReq (pDes, msg);
	case FM_DOWNINFO_REQ :		return OnFMDowninfoReq (pDes, msg);
	case FM_FILEINFO_REQ :		return OnFMFileinfoReq (pDes, msg);
	case FM_ENDDOWN_REQ :		return OnFMEnddownReq (pDes, msg);
	case FM_DOWN_REQ :			return OnFMDownReq (pDes, msg);
	case FM_DOWN_ACK :			return OnFMDownAck (pDes, msg);
	}
	return ERROR_INVALID;
}

int CFileManagerCom::OnFMDowninfoReq(CSessDesc * pDes, CMsg & msg)
{
	WORD wVer;
	msg >> wVer;

	if (wVer)
	{
		POSITION pos = m_listFile.GetHeadPosition ();
		while (pos)
		{
			CFileInfo* pInfo = (CFileInfo*)m_listFile.GetNext (pos);
			if (pInfo->m_wVer > wVer)
				pDes->AddFileInfo (pInfo);
		}
	}
	else
		pDes->AddFileInfo (m_pInfoInst);

	CMsg msgSend;
	msgSend.ID (FM_DOWNINFO_ACK) 
		<< pDes->GetNumDownFile () 
		<< pDes->GetLengthTotalFile ();
	pDes->Say (msgSend);

	return 0;
}

int CFileManagerCom::OnFMFileinfoReq(CSessDesc * pDes, CMsg & msg)
{
	CMsg msgSend;
	CFileInfo* pInfo = pDes->GetFileInfo ();
	if (!pInfo)
	{
		msgSend.ID (FM_FILEINFO_ACK) 
			<< _T("") << 0 << (BYTE)0; 
		pDes->Say (msgSend);
	}
	else
	{
		CString t_str;
		if(pDes->m_bInstFlag == TRUE)
		{
			if(pInfo->m_strFileName.CompareNoCase("upgrade.exe"))
			{
				t_str = m_strGameID + _T("\\");
			}
		}
		else
		{
			if(!pInfo->m_strFileName.CompareNoCase("upgrade.exe"))
			{
				t_str = _T("..\\");
			}
		}
		t_str += pInfo->m_strFileName;
		msgSend.ID (FM_FILEINFO_ACK) 
			<< t_str
			<< pInfo->m_dwLength
			<< pInfo->m_bComp;
		pDes->Say (msgSend);
		if(pDes->m_bInstFlag == FALSE && !pInfo->m_strFileName.CompareNoCase("instemul.exe"))
		{
			pDes->m_bInstFlag = TRUE;
		}
	}

	return 0;
}


int CFileManagerCom::OnFMEnddownReq(CSessDesc * pDes, CMsg & msg)
{
	return ERROR_ENDDOWN;
}

int CFileManagerCom::OnFMDownReq(CSessDesc * pDes, CMsg & msg)
{
	if (!pDes->StartDown ())
	{
		CMsg msgSend;
		msgSend.ID (FM_DOWN_ACK);
		pDes->Say (msgSend);
	}

	return 0;
}

int CFileManagerCom::OnFMDownAck(CSessDesc *pDes, CMsg &msg)
{
	DWORD dwDownLen;
	msg >> dwDownLen;

	pDes->m_dwCurrentDown = dwDownLen;

	return 0;
}

BOOL CFileManagerCom::LoadInstallFile()
{
	CFile file;
	CFileStatus rStatus;
	CString strPathName = m_strFilePath + _T("\\") + INSTALL_FILE;
	if (!file.GetStatus (strPathName, rStatus))
		return FALSE;

	m_pInfoInst = new CFileInfo (INSTALL_FILE, strPathName, 0, 0, rStatus.m_size);
	return TRUE;
}

////////////////////////////////////////////////////////////////////////
//
//	버젼별로 압축한 파일를 가져온다. 
//
BOOL CFileManagerCom::LoadFileZipInfo()
{
	CString strConnect;

	strConnect.Format (_T("DSN=%s;UID=%s;PWD=%s"), 
		m_strGameID, m_strUserID, m_strPassword);

	CDatabase db;
	db.SetLoginTimeout (5);
	if (!db.OpenEx (strConnect, CDatabase::noOdbcDialog))
		return FALSE;
	
	CPatchVer	pVerSet(&db);
	if (!pVerSet.Open ())
	{
		db.Close ();
		return FALSE;
	}

	CString strPathName;
	BYTE bComp;
	DWORD dwLength;

	while (!m_listFile.IsEmpty ()) delete m_listFile.RemoveHead ();

	while (!pVerSet.IsEOF())
	{
		bComp = (BYTE)1;		// 압축한 상태...
		strPathName = m_strFilePath + _T("\\") + pVerSet.m_strFileName;

		CFile file;
		CFileStatus rStatus;
		if (!file.GetStatus (strPathName, rStatus))
		{
			pVerSet.Close ();
			db.Close ();
			return FALSE;
		}

		dwLength = rStatus.m_size;
		
		CFileInfo* pInfo = new CFileInfo (
			pVerSet.m_strFileName, 
			strPathName, 
			bComp, 
			pVerSet.m_sVersion, 
			dwLength);
		m_listFile.AddTail (pInfo);

		pVerSet.MoveNext ();
	}

	pVerSet.Close ();
	db.Close ();

	return TRUE;
}

BOOL CFileManagerCom::LoadFileInfo()
{
	CString strConnect;

	strConnect.Format (_T("DSN=%s;UID=%s;PWD=%s"), 
		m_strGameID, m_strUserID, m_strPassword);

	CDatabase db;
	db.SetLoginTimeout (5);
	if (!db.OpenEx (strConnect, CDatabase::noOdbcDialog))
		return FALSE;

	CVerSet verset (&db);
	if (!verset.Open ())
	{
		db.Close ();
		return FALSE;
	}

	CString strPathName;
	BYTE bComp;
	DWORD dwLength;

	while (!m_listFile.IsEmpty ())
		delete m_listFile.RemoveHead ();

	while (!verset.IsEOF ())
	{
		if (verset.m_strCompName != _T(""))
		{
			bComp = (BYTE)1;
			strPathName = m_strFilePath + _T("\\") + verset.m_strCompName;
		}
		else
		{
			bComp = (BYTE)0;
			strPathName = m_strFilePath + _T("\\") + verset.m_strFileName;
		}

		CFile file;
		CFileStatus rStatus;
		if (!file.GetStatus (strPathName, rStatus))
		{
			verset.Close ();
			db.Close ();
			return FALSE;
		}

		dwLength = rStatus.m_size;
		
		CFileInfo* pInfo = new CFileInfo (
			verset.m_strFileName, 
			strPathName, 
			bComp, 
			verset.m_wVersion, 
			dwLength);
		m_listFile.AddTail (pInfo);

		verset.MoveNext ();
	}

	verset.Close ();
	db.Close ();

	return TRUE;
}

int CFileManagerCom::OnFMVersioninfoReq (CSessDesc *pDes, CMsg &msg)
{
	int n_version;

	n_version = 10;

	CString fm_upgradepath = "\\";
	CString fm_sFMUrl = "upgrade.droiyan.com.cn";		// 업그레이드 서버
	CString fm_loginid = "download";
	CString fm_loginpw = "download";
	
	CMsg msgSend;
	msgSend.ID (FM_VERSIONINFO_ACK)
		<< n_version
		<< fm_sFMUrl
		<< fm_upgradepath
		<< fm_loginid
		<< fm_loginpw;

	pDes->Say (msgSend);

	return 0;
}


