// StarterCom.cpp: implementation of the CStarterCom class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Starter.h"
#include "StarterCom.h"
#include "..\include\SCProtocol.h"
#include "Service.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStarterCom::CStarterCom(LPCTSTR lpszServerName) :
CBaseCom (lpszServerName)
{
}

CStarterCom::~CStarterCom()
{
}

BOOL CStarterCom::Process()
{
	return CBaseCom::Process ();
}

void CStarterCom::OnPauseService()
{
	CBaseCom::OnPauseService ();
}

BOOL CStarterCom::OnContinueService()
{
	return CBaseCom::OnContinueService ();
}

void CStarterCom::OnStopService()
{
	while (!m_listService.IsEmpty ())
		delete m_listService.RemoveHead ();

	CBaseCom::OnStopService ();
}

BOOL CStarterCom::OnStartService()
{
	ENUM_SERVICE_STATUS bufStatus[256];
	DWORD dwBytesNeed, dwServiceReturn, dwResumeHandle = 0;

	memset (bufStatus, 0, sizeof (bufStatus));

	SC_HANDLE hSCM = ::OpenSCManager (NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCM)
		return FALSE;

	if (::EnumServicesStatus (hSCM, SERVICE_WIN32, SERVICE_STATE_ALL, 
		bufStatus, sizeof (bufStatus), 
		&dwBytesNeed, &dwServiceReturn, &dwResumeHandle))
	{
		for (DWORD i = 0; i < dwServiceReturn; i++)
		{
			HKEY hKey;
			CString strRegKey;
			strRegKey.Format (_T("SYSTEM\\CurrentControlSet\\Services\\%s\\Config"), 
				bufStatus[i].lpServiceName);

			if (::RegOpenKeyEx (HKEY_LOCAL_MACHINE, strRegKey, 0, KEY_READ, &hKey) == ERROR_SUCCESS &&
				m_strServerName != bufStatus[i].lpServiceName)
			{
				::RegCloseKey (hKey);
				
				CService* pService = new CService (bufStatus[i]);
				m_listService.AddTail (pService);
			}
		}
	}

	::CloseServiceHandle (hSCM);

	GetConfigString (NULL, _T("Passwd"), m_strAdminPasswd);

	return CBaseCom::OnStartService ();
}

void CStarterCom::OnTimer ()
{
	SC_HANDLE hSCM = ::OpenSCManager (NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCM)
		return;

	POSITION pos = m_listService.GetHeadPosition ();
	while (pos)
	{
		CService* pService = (CService*)m_listService.GetNext (pos);
		SC_HANDLE hService = ::OpenService (hSCM, pService->m_strServiceName, 
			SERVICE_QUERY_STATUS);
		if (hService)
		{
			SERVICE_STATUS ss;
			::QueryServiceStatus (hService, &ss);
			if (ss.dwCurrentState != pService->m_dwStatus)
			{
				pService->m_dwStatus = ss.dwCurrentState;
				CMsg msg;
				msg.ID (SC_STATUS_ACK) 
					<< pService->m_strServiceName 
					<< pService->m_dwStatus;
				BroadcastMsg (msg);
			}
			::CloseServiceHandle (hService);
		}
	}

	::CloseServiceHandle (hSCM);

	CBaseCom::OnTimer ();
}

BOOL CStarterCom::OnOpenSession (CSessDesc* pDes)
{
	return CBaseCom::OnOpenSession (pDes);
}

void CStarterCom::OnCloseSession (CSessDesc* pDes, int nCode)
{
	CBaseCom::OnCloseSession (pDes, nCode);
}

int CStarterCom::OnReceiveMsg (CSessDesc* pDes, CMsg& msg)
{
	switch (msg.ID ())
	{
	case SC_INSTALL_REQ			: OnSCInstallReq (pDes, msg); break;
	case SC_REMOVE_REQ			: OnSCRemoveReq (pDes, msg); break;
	case SC_START_REQ			: OnSCStartReq (pDes, msg); break;
	case SC_STOP_REQ			: OnSCStopReq (pDes, msg); break;	
	case SC_PAUSE_REQ			: OnSCPauseReq (pDes, msg); break;
	case SC_CONTINUE_REQ		: OnSCContinueReq (pDes, msg); break;	
	case SC_SETINTVALUE_REQ		: OnSCSetIntValueReq (pDes, msg); break;
	case SC_GETINTVALUE_REQ		: OnSCGetIntValueReq (pDes, msg); break;
	case SC_SETSTRINGVALUE_REQ	: OnSCSetStringValueReq (pDes, msg); break;
	case SC_GETSTRINGVALUE_REQ	: OnSCGetStringValueReq (pDes, msg); break;
	case SC_LIST_REQ			: OnSCListReq (pDes, msg); break;
	case SC_STATUS_REQ			: OnSCStatusReq (pDes, msg); break;
	case SC_LOGIN_REQ			: OnSCLoginReq (pDes, msg); break;
	}
	
	return 0;
}


void CStarterCom::OnSCInstallReq(CSessDesc * pDes, CMsg & msg)
{
	CString strModulePath, strServiceName, strDisplayName, strAddr, strGameID, strUserID, strPassword;
	int nID, nPort, nCapacity, nTimer, nTimeOuts;

	msg >> strServiceName >> strGameID >> strUserID >> strPassword >> strModulePath >> strDisplayName
		>> nID >> strAddr >> nPort >> nCapacity >> nTimer >> nTimeOuts;

	CMsg msgSend;
	msgSend.ID (SC_INSTALL_ACK);
	CService* pService = new CService;
	if (!pService->InstallService (
		strModulePath, strGameID, strUserID, strPassword, strServiceName, strDisplayName,
		nID, strAddr, nPort, nCapacity, nTimer, nTimeOuts))
	{
		delete pService;
		CString strMsg;
		GetErrorMessage (strMsg);
		msgSend << 0 << strMsg;
		pDes->Say (msgSend);
	}
	else
	{
		m_listService.AddTail (pService);
		msgSend << 1 << strServiceName << strGameID << strUserID << strPassword << strModulePath << strDisplayName
			<< nID << strAddr << nPort << nCapacity << nTimer << nTimeOuts;
		BroadcastMsg (msgSend);
	}
}

void CStarterCom::OnSCRemoveReq(CSessDesc * pDes, CMsg & msg)
{
	CString strServiceName;
	msg >> strServiceName;

	CMsg msgSend;
	msgSend.ID (SC_REMOVE_ACK) << strServiceName;
	CService* pService = FindService (strServiceName);
	if (!pService)
	{
		CString strMsg;
		strMsg.LoadString (IDS_ERR_INVALIDSERVICE);
		msgSend << 0 << strMsg;
		pDes->Say (msgSend);
	}
	else if (!pService->RemoveService ())
	{
		CString strMsg;
		GetErrorMessage (strMsg);
		msgSend << 0 << strMsg;
		pDes->Say (msgSend);
	}
	else
	{
		POSITION pos = m_listService.Find (pService);
		if (pos)
			m_listService.RemoveAt (pos);
		delete pService;

		msgSend << 1;
		BroadcastMsg (msgSend);
	}
}

void CStarterCom::OnSCStartReq(CSessDesc * pDes, CMsg & msg)
{
	CString strServiceName;
	msg >> strServiceName;

	CMsg msgSend;
	msgSend.ID (SC_START_ACK) << strServiceName;
	CService* pService = FindService (strServiceName);
	if (!pService)
	{
		CString strMsg;
		strMsg.LoadString (IDS_ERR_INVALIDSERVICE);
		msgSend << 0 << strMsg;
		pDes->Say (msgSend);
	}
	else if (!pService->StartService ())
	{
		CString strMsg;
		GetErrorMessage (strMsg);
		msgSend << 0 << strMsg;
		pDes->Say (msgSend);
	}
	else
	{
		msgSend << 1;
		BroadcastMsg (msgSend);
	}
}

void CStarterCom::OnSCStopReq(CSessDesc * pDes, CMsg & msg)
{
	CString strServiceName;
	msg >> strServiceName;

	CMsg msgSend;
	msgSend.ID (SC_STOP_ACK) << strServiceName;
	CService* pService = FindService (strServiceName);
	if (!pService)
	{
		CString strMsg;
		strMsg.LoadString (IDS_ERR_INVALIDSERVICE);
		msgSend << 0 << strMsg;
		pDes->Say (msgSend);
	}
	else if (!pService->StopService ())
	{
		CString strMsg;
		GetErrorMessage (strMsg);
		msgSend << 0 << strMsg;
		pDes->Say (msgSend);
	}
	else
	{
		msgSend << 1;
		BroadcastMsg (msgSend);
	}
}

void CStarterCom::OnSCContinueReq(CSessDesc * pDes, CMsg & msg)
{
	CString strServiceName;
	msg >> strServiceName;

	CMsg msgSend;
	msgSend.ID (SC_CONTINUE_ACK) << strServiceName;
	CService* pService = FindService (strServiceName);
	if (!pService)
	{
		CString strMsg;
		strMsg.LoadString (IDS_ERR_INVALIDSERVICE);
		msgSend << 0 << strMsg;
		pDes->Say (msgSend);
	}
	else if (!pService || !pService->ContinueService ())
	{
		CString strMsg;
		GetErrorMessage (strMsg);
		msgSend << 0 << strMsg;
		pDes->Say (msgSend);
	}
	else
	{
		msgSend << 1;
		BroadcastMsg (msgSend);
	}
}

void CStarterCom::OnSCPauseReq(CSessDesc * pDes, CMsg & msg)
{
	CString strServiceName;
	msg >> strServiceName;

	CMsg msgSend;
	msgSend.ID (SC_PAUSE_ACK) << strServiceName;
	CService* pService = FindService (strServiceName);
	if (!pService)
	{
		CString strMsg;
		strMsg.LoadString (IDS_ERR_INVALIDSERVICE);
		msgSend << 0 << strMsg;
		pDes->Say (msgSend);
	}
	else if (!pService->PauseService ())
	{
		CString strMsg;
		GetErrorMessage (strMsg);
		msgSend << 0 << strMsg;
		pDes->Say (msgSend);
	}
	else
	{
		msgSend << 1;
		BroadcastMsg (msgSend);
	}
}

void CStarterCom::OnSCGetIntValueReq(CSessDesc * pDes, CMsg & msg)
{
	CString strServiceName, strName;
	msg >> strServiceName >> strName;

	CMsg msgSend;
	int nValue;
	msgSend.ID (SC_GETINTVALUE_ACK) << strServiceName << strName;

	CService* pService = FindService (strServiceName);

	if (!pService)
	{
		CString strMsg;
		strMsg.LoadString (IDS_ERR_INVALIDSERVICE);
		msgSend << 0 << strMsg;
	}
	else if (!pService->GetConfigInt (strName, nValue))
	{
		CString strMsg;
		strMsg.LoadString (IDS_ERR_GETVALUE);
		msgSend << 0 << strMsg;
	}
	else
		msgSend << 1 << nValue;

	pDes->Say (msgSend);
}

void CStarterCom::OnSCGetStringValueReq(CSessDesc * pDes, CMsg & msg)
{
	CString strServiceName, strName;
	msg >> strServiceName >> strName;

	CMsg msgSend;
	CString strValue;
	msgSend.ID (SC_GETSTRINGVALUE_ACK) << strServiceName << strName;

	CService* pService = FindService (strServiceName);

	if (!pService)
	{
		CString strMsg;
		strMsg.LoadString (IDS_ERR_INVALIDSERVICE);
		msgSend << 0 << strMsg;
	}
	else if (!pService->GetConfigString (strName, strValue))
	{
		CString strMsg;
		strMsg.LoadString (IDS_ERR_GETVALUE);
		msgSend << 0 << strMsg;
	}
	else
		msgSend << 1 << strValue;

	pDes->Say (msgSend);
}

void CStarterCom::OnSCSetIntValueReq(CSessDesc * pDes, CMsg & msg)
{
	CString strServiceName, strName;
	int nValue;
	msg >> strServiceName >> strName >> nValue;

	CMsg msgSend;
	msgSend.ID (SC_SETINTVALUE_ACK) << strServiceName << strName;

	CService* pService = FindService (strServiceName);

	if (!pService)
	{
		CString strMsg;
		strMsg.LoadString (IDS_ERR_INVALIDSERVICE);
		msgSend << 0 << strMsg;
		pDes->Say (msgSend);
	}
	else if (!pService->SetConfigInt (strName, nValue))
	{
		CString strMsg;
		strMsg.LoadString (IDS_ERR_SETVALUE);
		msgSend << 0 << strMsg;
		pDes->Say (msgSend);
	}
	else
	{
		msgSend << 1 << nValue;
		BroadcastMsg (msgSend);

		if (strName == _T("ID"))
			pService->m_nID = nValue;
		else if (strName == _T("Port"))
			pService->m_nPort = nValue;
		else if (strName == _T("Capacity"))
			pService->m_nCapacity = nValue;
		else if (strName == _T("Timer"))
			pService->m_nTimer = nValue;
		else if (strName == _T("TimeOut"))
			pService->m_nTimeOuts = nValue;
	}
}

void CStarterCom::OnSCSetStringValueReq(CSessDesc * pDes, CMsg & msg)
{
	CString strServiceName, strName, strValue;
	msg >> strServiceName >> strName >> strValue;

	CMsg msgSend;
	msgSend.ID (SC_SETSTRINGVALUE_ACK) << strServiceName << strName;

	CService* pService = FindService (strServiceName);

	if (!pService)
	{
		CString strMsg;
		strMsg.LoadString (IDS_ERR_INVALIDSERVICE);
		msgSend << 0 << strMsg;
		pDes->Say (msgSend);
	}
	else if (!pService->SetConfigString (strName, strValue))
	{
		CString strMsg;
		strMsg.LoadString (IDS_ERR_SETVALUE);
		msgSend << 0 << strMsg;
		pDes->Say (msgSend);
	}
	else
	{
		msgSend << 1 << strValue;
		BroadcastMsg (msgSend);

		if (strName == _T("Addr"))
			pService->m_strAddr = strValue;
	}
}

void CStarterCom::OnSCListReq(CSessDesc * pDes, CMsg & msg)
{
	CMsg msgSend;
	msgSend.ID (SC_LIST_ACK) << m_listService.GetCount ();
	POSITION pos = m_listService.GetHeadPosition ();
	while (pos)
	{
		CService* pService = (CService*)m_listService.GetNext (pos);
		msgSend << pService->m_strServiceName << pService->m_strGameID << pService->m_strUserID << pService->m_strPassword
			<< pService->m_strModule << pService->m_strDisplayName 
			<< pService->m_nID << pService->m_strAddr << pService->m_nPort
			<< pService->m_nCapacity << pService->m_nTimer
			<< pService->m_nTimeOuts << pService->m_dwStatus;
	}
	pDes->Say (msgSend);
}

void CStarterCom::OnSCStatusReq(CSessDesc * pDes, CMsg & msg)
{
	CString strServiceName;
	msg >> strServiceName;

	CService* pService = FindService (strServiceName);
	if (pService)
	{
		CMsg msgSend;
		msgSend.ID (SC_STATUS_ACK) 
			<< pService->m_strServiceName 
			<< pService->m_dwStatus;
		pDes->Say (msgSend);
	}
}

void CStarterCom::OnSCLoginReq(CSessDesc * pDes, CMsg & msg)
{
	CString strGameID, strPasswd;
	msg >> strGameID >> strPasswd;

	CMsg msgSend;
	msgSend.ID (SC_LOGIN_ACK);
	CString strPasswd1;
	if (!GetConfigString (NULL, strGameID, strPasswd1))
	{
		SetConfigString (NULL, strGameID, strPasswd);
		msgSend << 1;
	}
	else if (strPasswd == strPasswd1)
		msgSend << 1;
	else
		msgSend << 0;

	pDes->Say (msgSend);
}

void CStarterCom::BroadcastMsg(CMsg & msg)
{
	POSITION pos = m_listActive.GetHeadPosition ();
	while (pos)
	{
		CSessDesc* pDes = (CSessDesc*)m_listActive.GetNext (pos);
		pDes->Say (msg);
	}
}

CService* CStarterCom::FindService(LPCTSTR lpszService)
{
	POSITION pos = m_listService.GetHeadPosition ();
	while (pos)
	{
		CService* pService = (CService*)m_listService.GetNext (pos);
		if (pService->m_strServiceName == lpszService)
			return pService;
	}
	return NULL;
}

void CStarterCom::GetErrorMessage(CString & strMsg)
{
	LPVOID lpMsgBuf;
	::FormatMessage (
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf, 0, NULL);
	strMsg = (LPTSTR)lpMsgBuf;
	::LocalFree( lpMsgBuf );
}

