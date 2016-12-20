// Service.cpp: implementation of the CService class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Starter.h"
#include "Service.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CService::CService()
{
	m_dwStatus = SERVICE_STOPPED;
}

CService::CService(ENUM_SERVICE_STATUS& ss)
{
	m_strServiceName = ss.lpServiceName;
	m_strDisplayName = ss.lpDisplayName;
	m_dwStatus = ss.ServiceStatus.dwCurrentState;

	if (!GetConfigInt (_T("ID"), m_nID))
		m_nID = 0;
	if (!GetConfigString (_T("Addr"), m_strAddr))
		m_strAddr = _T("");
	if (!GetConfigInt (_T("Port"), m_nPort))
		m_nPort = 0;
	if (!GetConfigInt (_T("Capacity"), m_nCapacity))
		m_nCapacity = 1;
	if (!GetConfigInt (_T("Timer"), (int&)m_nTimer))
		m_nTimer = 0;
	if (!GetConfigInt (_T("TimeOut"), (int&)m_nTimeOuts))
		m_nTimeOuts = 0;
	if (!GetConfigString (_T("Module"), m_strModule))
		m_strModule = _T("");
	if (!GetConfigString (_T("GameID"), m_strGameID))		m_strGameID = _T("Droiyan");
//		m_strGameID = _T("NETGAME");
	if (!GetConfigString (_T("UserID"), m_strUserID))		m_strUserID = _T("Droiyan");
//		m_strUserID = _T("NETGAME");
	if (!GetConfigString (_T("Password"), m_strPassword))	m_strPassword = _T("Droiyan");
//		m_strPassword = _T("NETGAME");
}

CService::~CService()
{
}


BOOL CService::SetConfigString(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	HKEY hKey;
	CString strRegKey;
	strRegKey.Format (_T("SYSTEM\\CurrentControlSet\\Services\\%s\\Config"), m_strServiceName);
	if (::RegOpenKeyEx (HKEY_LOCAL_MACHINE, strRegKey, 0, KEY_WRITE, &hKey) != ERROR_SUCCESS)
		return FALSE;

	DWORD dwType = REG_SZ, dwLen = strlen (lpszValue) + 1;
	BOOL fRet = (::RegSetValueEx (hKey, lpszName, NULL, dwType, 
		(BYTE*)lpszValue, dwLen) == ERROR_SUCCESS);
	::RegCloseKey (hKey);

	return fRet;
}

BOOL CService::GetConfigString(LPCTSTR lpszName, CString & strValue)
{
	HKEY hKey;
	CString strRegKey;
	strRegKey.Format (_T("SYSTEM\\CurrentControlSet\\Services\\%s\\Config"), m_strServiceName);
	if (::RegOpenKeyEx (HKEY_LOCAL_MACHINE, strRegKey, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
		return FALSE;

	DWORD dwType, dwLen;
	TCHAR szValue[256];
	dwLen = sizeof (szValue);
	BOOL fRet = (::RegQueryValueEx (hKey, lpszName, NULL, &dwType, 
		(BYTE*)&szValue[0], &dwLen) == ERROR_SUCCESS && dwType == REG_SZ);
	::RegCloseKey (hKey);
	strValue = szValue;

	return fRet;
}

BOOL CService::SetConfigInt(LPCTSTR lpszName, int nValue)
{
	HKEY hKey;
	CString strRegKey;
	strRegKey.Format (_T("SYSTEM\\CurrentControlSet\\Services\\%s\\Config"), m_strServiceName);
	if (::RegOpenKeyEx (HKEY_LOCAL_MACHINE, strRegKey, 0, KEY_WRITE, &hKey) != ERROR_SUCCESS)
		return FALSE;

	DWORD dwType = REG_DWORD, dwLen = sizeof (DWORD);
	BOOL fRet = (::RegSetValueEx (hKey, lpszName, NULL, dwType, 
		(BYTE*)&nValue, dwLen) == ERROR_SUCCESS);
	::RegCloseKey (hKey);

	return fRet;
}

BOOL CService::GetConfigInt(LPCTSTR lpszName, int & nValue)
{
	HKEY hKey;
	CString strRegKey;
	strRegKey.Format (_T("SYSTEM\\CurrentControlSet\\Services\\%s\\Config"), m_strServiceName);
	if (::RegOpenKeyEx (HKEY_LOCAL_MACHINE, strRegKey, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
		return FALSE;

	DWORD dwType, dwLen;
	dwLen = sizeof (DWORD);
	BOOL fRet = (::RegQueryValueEx (hKey, lpszName, NULL, &dwType, 
		(BYTE*)&nValue, &dwLen) == ERROR_SUCCESS && dwType == REG_DWORD);
	::RegCloseKey (hKey);

	return fRet;
}

BOOL CService::InstallService(LPCTSTR lpszModulePath, LPCTSTR lpszGameID, LPCTSTR lpszUserID, LPCTSTR lpszPassword,
							  LPCTSTR lpszServiceName, LPCTSTR lpszDisplayName, 
							  int nID, LPCTSTR lpszAddr, int nPort, 
							  int nCapacity, int nTimer, int nTimeOuts)
{
	SC_HANDLE hSCM = ::OpenSCManager (NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCM)
		return FALSE;

	SC_HANDLE hService = ::CreateService (
		hSCM, lpszServiceName, lpszDisplayName, 0,
		SERVICE_WIN32_OWN_PROCESS, 
		SERVICE_DEMAND_START, 
		SERVICE_ERROR_IGNORE,
		lpszModulePath, NULL, NULL, NULL, NULL, NULL);
	if (!hService)
		return FALSE;
	::CloseServiceHandle (hService);
	::CloseServiceHandle (hSCM);

	m_dwStatus = SERVICE_STOPPED;
	m_strServiceName = lpszServiceName;
	m_strDisplayName = lpszDisplayName;
	m_nID = nID;
	m_strAddr = lpszAddr;
	m_nPort = nPort;
	m_nCapacity = nCapacity;
	m_nTimer = nTimer;
	m_nTimeOuts = nTimeOuts;
	m_strModule = lpszModulePath;
	m_strGameID = lpszGameID;
	m_strUserID = lpszUserID;
	m_strPassword = lpszPassword;

	HKEY hKey;
	CString strRegKey;
	DWORD dwDisposition;
	strRegKey.Format (_T("SYSTEM\\CurrentControlSet\\Services\\%s\\Config"), m_strServiceName);
	if (::RegCreateKeyEx (HKEY_LOCAL_MACHINE, strRegKey, NULL, NULL, REG_OPTION_NON_VOLATILE, 
		KEY_WRITE, NULL, &hKey, &dwDisposition) != ERROR_SUCCESS)
		return FALSE;
	::RegCloseKey (hKey);

	if (!SetConfigInt (_T("ID"), m_nID) ||
		!SetConfigString (_T("Addr"), m_strAddr) ||
		!SetConfigInt (_T("Port"), m_nPort) ||
		!SetConfigInt (_T("Capacity"), m_nCapacity) ||
		!SetConfigInt (_T("Timer"), (int&)m_nTimer) ||
		!SetConfigInt (_T("TimeOut"), (int&)m_nTimeOuts) ||
		!SetConfigString (_T("Module"), m_strModule) ||
		!SetConfigString (_T("GameID"), m_strGameID) ||
		!SetConfigString (_T("UserID"), m_strUserID) ||
		!SetConfigString (_T("Password"), m_strPassword))
		return FALSE;

	return TRUE;
}

BOOL CService::StartService()
{
	if (m_dwStatus != SERVICE_STOPPED)
		return FALSE;

	SC_HANDLE hSCM = ::OpenSCManager (NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCM)
		return FALSE;

	SC_HANDLE hService = ::OpenService (hSCM, m_strServiceName, 
		SERVICE_START);
	if (!hService)
		return FALSE;
	BOOL fRet = ::StartService (hService, 0, NULL);
	::CloseServiceHandle (hService);
	::CloseServiceHandle (hSCM);
	return fRet;
}

BOOL CService::StopService()
{
	if (m_dwStatus == SERVICE_STOPPED)
		return FALSE;

	SC_HANDLE hSCM = ::OpenSCManager (NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCM)
		return FALSE;

	SC_HANDLE hService = ::OpenService (hSCM, m_strServiceName, 
		SERVICE_STOP);
	if (!hService)
		return FALSE;
	SERVICE_STATUS ss;
	BOOL fRet = ::ControlService (hService, SERVICE_CONTROL_STOP, &ss);
	::CloseServiceHandle (hService);
	::CloseServiceHandle (hSCM);
	return fRet;
}

BOOL CService::ContinueService()
{
	if (m_dwStatus != SERVICE_PAUSED)
		return FALSE;

	SC_HANDLE hSCM = ::OpenSCManager (NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCM)
		return FALSE;

	SC_HANDLE hService = ::OpenService (hSCM, m_strServiceName, 
		SERVICE_PAUSE_CONTINUE);
	if (!hService)
		return FALSE;
	SERVICE_STATUS ss;
	BOOL fRet = ::ControlService (hService, SERVICE_CONTROL_CONTINUE, &ss);
	::CloseServiceHandle (hService);
	::CloseServiceHandle (hSCM);
	return fRet;
}

BOOL CService::PauseService()
{
	if (m_dwStatus != SERVICE_RUNNING)
		return FALSE;

	SC_HANDLE hSCM = ::OpenSCManager (NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCM)
		return FALSE;

	SC_HANDLE hService = ::OpenService (hSCM, m_strServiceName, 
		SERVICE_PAUSE_CONTINUE);
	if (!hService)
		return FALSE;
	SERVICE_STATUS ss;
	BOOL fRet = ::ControlService (hService, SERVICE_CONTROL_PAUSE, &ss);
	::CloseServiceHandle (hService);
	::CloseServiceHandle (hSCM);
	return fRet;
}

BOOL CService::RemoveService()
{
	SC_HANDLE hSCM = ::OpenSCManager (NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCM)
		return FALSE;

	SC_HANDLE hService = ::OpenService (hSCM, m_strServiceName, DELETE);
	if (!hService)
		return FALSE;

	BOOL fRet = ::DeleteService (hService);
	::CloseServiceHandle (hService);
	::CloseServiceHandle (hSCM);
	return fRet;
}
