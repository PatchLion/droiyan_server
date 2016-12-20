// Server.cpp: implementation of the CServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServiceManager.h"
#include "ServiceManagerDoc.h"

#include "Server.h"
#include "Service.h"
#include "UserManager.h"
#include "FileManager.h"
#include "Session.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define STARTER_PORT 3000

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL (CServer, CObject, 1)

CServer::CServer ()
{
	m_pDoc = NULL;
	m_nAccess = 0;
}

CServer::CServer(CServiceManagerDoc* pDoc)
{
	m_pDoc = pDoc;
}

CServer::~CServer()
{
	if (m_fConnect)
		CClientSock::Close ();

	while (!m_listService.IsEmpty ())
		delete m_listService.RemoveHead ();
}

void CServer::OnReceiveMsg(CMsg & msg)
{
	switch (msg.ID ())
	{
	case SC_INSTALL_ACK :			OnSCInstallAck (msg); break;
	case SC_REMOVE_ACK :			OnSCRemoveAck (msg); break;
	case SC_START_ACK :				OnSCStartAck (msg); break;
	case SC_STOP_ACK :				OnSCStopAck (msg); break;
	case SC_PAUSE_ACK :				OnSCPauseAck (msg); break;
	case SC_CONTINUE_ACK :			OnSCContinueAck (msg); break;
	case SC_SETINTVALUE_ACK :		
	case SC_GETINTVALUE_ACK :		OnSCIntValueAck (msg); break;
	case SC_SETSTRINGVALUE_ACK :	
	case SC_GETSTRINGVALUE_ACK :	OnSCStringValueAck (msg); break;
	case SC_LIST_ACK :				OnSCListAck (msg); break;
	case SC_STATUS_ACK :			OnSCStatusAck (msg); break;
	case SC_LOGIN_ACK :				OnSCLoginAck (msg); break;
	}
}

void CServer::OnConnect(int nErrorCode)
{
	CClientSock::OnConnect(nErrorCode);
	if (!m_pDoc)
		return;
	if (m_fConnect)
	{
		CMsg msgSend;
		msgSend.ID (SC_LOGIN_REQ) << m_pDoc->m_strGameID << m_pDoc->m_strPasswd;
		SendMsg (msgSend);
	}

	m_pDoc->UpdateAllViews (NULL, UPDATE_SERVERSTATUS, this);
}

void CServer::OnClose(int nErrorCode)
{
	CClientSock::OnClose(nErrorCode);
	if (!m_pDoc)
		return;
	m_pDoc->UpdateAllViews (NULL, UPDATE_SERVERSTATUS, this);
}

void CServer::OnSCInstallAck(CMsg & msg)
{
	if (m_pDoc)
	{
		int nResult;
		msg >> nResult;

		if (!nResult)
		{
			CString strMsg;
			msg >> strMsg;
			AfxMessageBox (strMsg);
			return;
		}

		CString strServiceName, strModule, strDisplayName, strAddr, strGameID, strUserID, strPassword;
		int nID, nPort, nCapacity;
		DWORD dwTimer, dwTimeOuts;

		msg >> strServiceName >> strGameID >> strUserID >> strPassword >> strModule >> strDisplayName >> nID >> strAddr
			>> nPort >> nCapacity >> dwTimer >> dwTimeOuts;

		CString strType = strServiceName.Left (2);

		CMsg msgSend;
		CService* pService = NULL;
		if (m_pDoc->m_strGameID == strGameID)
		{
			if (strType == _T("UM"))
			{
				m_pDoc->m_pUserManager = new CUserManager (this, strModule, strAddr, nPort, nCapacity);
				pService = m_pDoc->m_pUserManager;

				msgSend.ID (SC_GETSTRINGVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("GSAddr");
				SendMsg (msgSend);

				msgSend.ID (SC_GETSTRINGVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("FMAddr");
				SendMsg (msgSend);

				msgSend.ID (SC_GETSTRINGVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("DBAddr");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("GSPort");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("FMPort");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("DBPort");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("GameVer");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ)
					<< pService->m_strServiceName
					<< _T("NoticeStatus");
				SendMsg (msgSend);

				msgSend.ID (SC_GETSTRINGVALUE_REQ)
					<< pService->m_strServiceName
					<< _T("NoticeMessage");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ)
					<< pService->m_strServiceName
					<< _T("NoticeSessionStatus");
				SendMsg (msgSend);

				msgSend.ID (SC_GETSTRINGVALUE_REQ)
					<< pService->m_strServiceName
					<< _T("NoticeSessionMessage");
				SendMsg (msgSend);
			}
			else if (strType == _T("SM"))
			{
				pService = new CSession (this, strModule, strDisplayName, nID, strAddr, nPort, nCapacity, dwTimeOuts);
				m_pDoc->m_listSession.AddTail (pService);

				msgSend.ID (SC_GETSTRINGVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("UMAddr");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("UMPort");
				SendMsg (msgSend);

				msgSend.ID (SC_GETSTRINGVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("ServName");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("Pay");
				SendMsg (msgSend);
			}
			else if (strType == _T("FM"))
			{
				m_pDoc->m_pFileManager = new CFileManager (this, strModule, strAddr, nPort, nCapacity);
				pService = m_pDoc->m_pFileManager;

				msgSend.ID (SC_GETSTRINGVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("SrcPath");
				SendMsg (msgSend);

				msgSend.ID (SC_GETSTRINGVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("DBAddr");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("DBPort");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("Hold");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("Buf");
				SendMsg (msgSend);
			}
			else if (strType == _T("GS"))
			{
				pService = new CService (this, CService::typeGS, strModule, strDisplayName, nID, strAddr, nPort, nCapacity, dwTimer, dwTimeOuts);
				m_pDoc->m_listGame.AddTail (pService);
			}
			else
				return;
		}
		else
			return;

		m_listService.AddTail (pService);
		m_pDoc->UpdateAllViews (NULL, UPDATE_INSTALLSERVICE, pService);
	}
}

void CServer::OnSCRemoveAck(CMsg & msg)
{
	CString strServiceName;
	int nResult;
	msg >> strServiceName >> nResult;

	if (!nResult)
	{
		CString strMsg;
		msg >> strMsg;
		AfxMessageBox (strMsg);
		return;
	}

	CService* pService = FindService (strServiceName);
	if (pService && m_pDoc)
	{
		m_pDoc->UpdateAllViews (NULL, UPDATE_REMOVESERVICE, pService);
		POSITION pos = m_listService.Find (pService);
		m_listService.RemoveAt (pos);

		switch (pService->m_nType)
		{
		case CService::typeUM :
			m_pDoc->m_pUserManager = NULL;
			break;
		case CService::typeFM :
			m_pDoc->m_pFileManager = NULL;
			break;
		case CService::typeSM :
			pos = m_pDoc->m_listSession.Find (pService);
			if (pos)
				m_pDoc->m_listSession.RemoveAt (pos);
			break;
		case CService::typeGS :
			pos = m_pDoc->m_listGame.Find (pService);
			if (pos)
				m_pDoc->m_listGame.RemoveAt (pos);
			break;
		}
		delete pService;
	}
}

void CServer::OnSCStartAck(CMsg & msg)
{
	CString strServiceName;
	int nResult;
	msg >> strServiceName >> nResult;

	CService* pService = FindService (strServiceName);
	if (pService)
	{
		if (!nResult)
		{
			CString strMsg;
			msg >> strMsg;
			AfxMessageBox (strMsg);
		}
		else if (pService->m_nType == CService::typeUM && 
			pService->Create ())
			pService->Connect (pService->m_strAddr, pService->m_nPort);
	}
}

void CServer::OnSCStopAck(CMsg & msg)
{
	CString strServiceName;
	int nResult;
	msg >> strServiceName >> nResult;

	CService* pService = FindService (strServiceName);
	if (pService && !nResult)
	{
		CString strMsg;
		msg >> strMsg;
		AfxMessageBox (strMsg);
	}
}

void CServer::OnSCContinueAck(CMsg & msg)
{
	CString strServiceName;
	int nResult;
	msg >> strServiceName >> nResult;

	CService* pService = FindService (strServiceName);
	if (pService && !nResult)
	{
		CString strMsg;
		msg >> strMsg;
		AfxMessageBox (strMsg);
	}
}

void CServer::OnSCPauseAck(CMsg & msg)
{
	CString strServiceName;
	int nResult;
	msg >> strServiceName >> nResult;

	CService* pService = FindService (strServiceName);
	if (pService && !nResult)
	{
		CString strMsg;
		msg >> strMsg;
		AfxMessageBox (strMsg);
	}
}

void CServer::OnSCIntValueAck(CMsg & msg)
{
	CString strServiceName, strFieldName;
	int nValue, nResult;

	msg >> strServiceName >> strFieldName >> nResult >> nValue;
	if (nResult)
	{
		CService* pService = FindService (strServiceName);
		CSession* pSM;
		CUserManager* pUM;
		CFileManager* pFM;
		if (pService)
		{
			if (strFieldName == _T("Port"))
				pService->m_nPort = nValue;
			else if (strFieldName == _T("Capacity"))
				pService->m_nCapacity = nValue;
			else if (strFieldName == _T("Timer"))
				pService->m_dwTimer = nValue;
			else if (strFieldName == _T("TimeOut"))
				pService->m_dwTimeOuts = nValue;
			else if (strFieldName == _T("ID"))
				pService->m_nServerID = nValue;
			else
			{
				BOOL fEtc = FALSE;
				switch (pService->m_nType)
				{
				case CService::typeFM :
					pFM = (CFileManager*)pService;
					if (strFieldName == _T("Hold"))
						pFM->m_dwHold = nValue;
					else if (strFieldName == _T("Buf"))
						pFM->m_dwBuffer = nValue;
					else
						fEtc = TRUE;
					break;

				case CService::typeUM :
					pUM = (CUserManager*)pService;
					if (strFieldName == _T("FMPort"))
						pUM->m_nFMPort = nValue;
					else if (strFieldName == _T("GSPort"))
						pUM->m_nGSPort = nValue;
					else if (strFieldName == _T("GameVer"))
						m_pDoc->m_wGameVer = (WORD)nValue;
					else if (strFieldName == _T("NoticeStatus"))
						m_pDoc->m_vNoticeValue = (BYTE)nValue;
					else if (strFieldName == _T("NoticeSessionStatus"))
						m_pDoc->m_vNoticeSessionValue = (BYTE)nValue;
					else
						fEtc = TRUE;
					break;
				case CService::typeSM :
					pSM = (CSession*)pService;
					if (strFieldName == _T("UMPort"))
						pSM->m_nUMPort = nValue;
					else if (strFieldName == _T("Pay"))
						pSM->m_fPay = nValue;
					else
						fEtc = TRUE;
					break;
				default :
					fEtc = TRUE;
				}
				if (fEtc)
				{
					CString strMsg;
					strMsg.FormatMessage (IDS_FMT_VALUEINT, strServiceName, strFieldName, nValue);
					AfxMessageBox (strMsg);
				}
			}
			m_pDoc->UpdateAllViews (NULL, UPDATE_SERVICECONFIG, pService);
		}
	}
}

void CServer::OnSCStringValueAck(CMsg & msg)
{
	CString strServiceName, strFieldName, strValue;
	int nResult;

	msg >> strServiceName >> strFieldName >> nResult >> strValue;
	if (nResult)
	{
		CService* pService = FindService (strServiceName);
		CSession* pSM;
		CUserManager* pUM;
		CFileManager* pFM;
		if (pService)
		{
			if (strFieldName == _T("Addr"))
				pService->m_strAddr = strValue;
			else
			{
				BOOL fEtc = FALSE;
				switch (pService->m_nType)
				{
				case CService::typeFM :
					pFM = (CFileManager*)pService;
					if (strFieldName == _T("SrcPath"))
						pFM->m_strSrcPath = strValue;
					else 
						fEtc = TRUE;
					break;
				case CService::typeUM :
					pUM = (CUserManager*)pService;
					if (strFieldName == _T("GSAddr"))
						pUM->m_strGSAddr = strValue;
					else if (strFieldName == _T("FMAddr"))
						pUM->m_strFMAddr = strValue;
					else if (strFieldName == _T("NoticeMessage"))
						m_pDoc->m_strNoticeMessage = strValue;
					else if (strFieldName == _T("NoticeSessionMessage"))
						m_pDoc->m_strNoticeSessionMessage = strValue;
					else 
						fEtc = TRUE;
					break;
				case CService::typeSM :
					pSM = (CSession*)pService;
					if (strFieldName == _T("UMAddr"))
						pSM->m_strUMAddr = strValue;
					else if (strFieldName == _T("ServName"))
						pSM->m_strName = strValue;
					else 
						fEtc = TRUE;
					break;
				default :
					fEtc = TRUE;
					break;
				}
				if (fEtc)
				{
					CString strMsg;
					strMsg.FormatMessage (IDS_FMT_VALUESTRING, strServiceName, strFieldName, strValue);
					AfxMessageBox (strMsg);
				}
			}
			m_pDoc->UpdateAllViews (NULL, UPDATE_SERVICECONFIG, pService);
		}
	}
}

void CServer::OnSCListAck(CMsg & msg)
{
	int nNumService;
	msg >> nNumService;
	for (int i = 0; i < nNumService; i++)
	{
		CString strServiceName, strModule, strDisplayName, strAddr, strGameID, strUserID, strPassword;
		int nID, nPort, nCapacity;
		DWORD dwTimer, dwTimeOuts, dwStatus;

		msg >> strServiceName >> strGameID >> strUserID >> strPassword >> strModule >> strDisplayName >> nID >> strAddr
			>> nPort >> nCapacity >> dwTimer >> dwTimeOuts >> dwStatus;

		if (m_pDoc && m_pDoc->m_strGameID == strGameID)
		{
			CString strType = strServiceName.Left (2);
			CMsg msgSend;
			CService* pService = NULL;
			if (strType == _T("UM"))
			{
				m_pDoc->m_pUserManager = new CUserManager (this, strModule, strAddr, nPort, nCapacity, dwStatus);
				pService = m_pDoc->m_pUserManager;

				msgSend.ID (SC_GETSTRINGVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("GSAddr");
				SendMsg (msgSend);

				msgSend.ID (SC_GETSTRINGVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("FMAddr");
				SendMsg (msgSend);

				msgSend.ID (SC_GETSTRINGVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("DBAddr");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("GSPort");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("FMPort");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("DBPort");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("GameVer");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ)
					<< pService->m_strServiceName
					<< _T("NoticeStatus");
				SendMsg (msgSend);

				msgSend.ID (SC_GETSTRINGVALUE_REQ)
					<< pService->m_strServiceName
					<< _T("NoticeMessage");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ)
					<< pService->m_strServiceName
					<< _T("NoticeSessionStatus");
				SendMsg (msgSend);

				msgSend.ID (SC_GETSTRINGVALUE_REQ)
					<< pService->m_strServiceName
					<< _T("NoticeSessionMessage");
				SendMsg (msgSend);
			}
			else if (strType == _T("SM"))
			{
				pService = new CSession (this, strModule, strDisplayName, nID, strAddr, nPort, nCapacity, dwTimeOuts, dwStatus);
				m_pDoc->m_listSession.AddTail (pService);

				msgSend.ID (SC_GETSTRINGVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("UMAddr");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("UMPort");
				SendMsg (msgSend);

				msgSend.ID (SC_GETSTRINGVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("ServName");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("Pay");
				SendMsg (msgSend);
			}
			else if (strType == _T("FM"))
			{
				m_pDoc->m_pFileManager = new CFileManager (this, strModule, strAddr, nPort, nCapacity, dwStatus);
				pService = m_pDoc->m_pFileManager;

				msgSend.ID (SC_GETSTRINGVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("SrcPath");
				SendMsg (msgSend);

				msgSend.ID (SC_GETSTRINGVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("DBAddr");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("DBPort");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("Hold");
				SendMsg (msgSend);

				msgSend.ID (SC_GETINTVALUE_REQ) 
					<< pService->m_strServiceName
					<< _T("Buf");
				SendMsg (msgSend);
			}
			else if (strType == _T("GS"))
			{
				pService = new CService (this, CService::typeGS, strModule, strDisplayName, nID, strAddr, nPort, nCapacity, dwTimer, dwTimeOuts, dwStatus);
				m_pDoc->m_listGame.AddTail (pService);
			}

			if (pService)
			{
				m_listService.AddTail (pService);
				m_pDoc->UpdateAllViews (NULL, UPDATE_INSTALLSERVICE, pService);
			}
		}
	}
}

void CServer::OnSCStatusAck(CMsg & msg)
{
	CString strServiceName;
	DWORD dwStatus;
	msg >> strServiceName >> dwStatus;

	CService* pService = FindService (strServiceName);
	if (pService)
	{
		pService->m_dwStatus = dwStatus;
		m_pDoc->UpdateAllViews (NULL, UPDATE_SERVICESTATUS, pService);
	}
}

void CServer::OnSCLoginAck(CMsg & msg)
{
	int nResult;
	msg >> nResult;
	m_nAccess = nResult + 1;

	CMsg msgSend;
	msgSend.ID (SC_LIST_REQ);
	SendMsg (msgSend);
}

BOOL CServer::ConnectToServer()
{
	if (!Create ())
		return FALSE;
	Connect (m_strAddr, STARTER_PORT);
	return TRUE;
}

void CServer::Serialize(CArchive & ar)
{
	if (ar.IsStoring ())
	{
		ar << m_strName << m_strAddr;
	}
	else
	{
		ar >> m_strName >> m_strAddr;
	}
	m_listAddr.Serialize (ar);
}

CService* CServer::FindService(LPCTSTR lpszServiceName)
{
	POSITION pos = m_listService.GetHeadPosition ();
	while (pos)
	{
		CService* pService = (CService*)m_listService.GetNext (pos);
		if (pService->m_strServiceName == lpszServiceName)
			return pService;
	}
	return NULL;
}

