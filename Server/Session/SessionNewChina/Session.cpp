// Session.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Session.h"
#include "Iocp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BUFFYSERVER_PORT	2040

extern CIOCP<CSessDesc> m_UserBase;

/////////////////////////////////////////////////////////////////////////////
// CSessionApp

BEGIN_MESSAGE_MAP(CSessionApp, CWinApp)
	//{{AFX_MSG_MAP(CSessionApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSessionApp construction

CSessionApp::CSessionApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSessionApp object

CSessionApp theApp;
TCHAR g_szAppName[256];

/////////////////////////////////////////////////////////////////////////////
// CSessionApp initialization

BOOL CSessionApp::InitInstance()
{
	TCHAR szOption[32];
	sscanf (m_lpCmdLine, "%s %s", g_szAppName, szOption);

	if (!strcmpi (szOption, _T("install")))
	{
		TCHAR		szModulePath[_MAX_PATH];

		SC_HANDLE hSCM = OpenSCManager (NULL, NULL, SC_MANAGER_CREATE_SERVICE);
		GetModuleFileName (NULL, szModulePath, _MAX_PATH);
		SC_HANDLE hService = CreateService (hSCM, g_szAppName, g_szAppName, 0,
			SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE,
			szModulePath, NULL, NULL, NULL, NULL, NULL);
		CloseServiceHandle (hService);
		CloseServiceHandle (hSCM);
	}
	else if (!strcmpi (szOption, _T("uninstall")))
	{
		SC_HANDLE hSCM = OpenSCManager (NULL, NULL, SC_MANAGER_CREATE_SERVICE);
		SC_HANDLE hService = OpenService (hSCM, g_szAppName, DELETE);
		DeleteService (hService);
		CloseServiceHandle (hService);
		CloseServiceHandle (hSCM);
	}
	else
	{
#ifdef _DEBUG
		ServiceMain (0, NULL);
#elif _CONSOLE
		ServiceMain (0, NULL);
#else
		SERVICE_TABLE_ENTRY	ServiceTable[] = {
			{ g_szAppName, ServiceMain }, { NULL, NULL }
		};
		StartServiceCtrlDispatcher (ServiceTable);
#endif
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CBaseCom

CBaseCom::CBaseCom( LPCTSTR lpszServerName )
{
	WORD	wVersionReq;
	WSADATA	wsaData;
	wVersionReq = MAKEWORD (2,2);
	if (WSAStartup (wVersionReq, &wsaData))
		return;

//#ifdef _USE_KEEPALIVE
	DWORD nkeepaliveinterval = 1000*10;
	DWORD nkeepalivetime = 1000*120;
	HKEY hKey;
    DWORD dwDisposition;
	HKEY key = NULL;
	CString strRegKey;

	strRegKey = CString(_T("SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters"));

	if (::RegCreateKeyEx (HKEY_LOCAL_MACHINE,strRegKey , 
		NULL, NULL, REG_OPTION_NON_VOLATILE, 
		KEY_WRITE, NULL, &hKey, &dwDisposition) != ERROR_SUCCESS)
	{
#ifdef _DEBUG
		AfxMessageBox("Parameters");
#endif
		return;
	}

/*
	// 키 폴터 만들때...
	if (::RegCreateKeyEx (p_hKey, "KeepAliveTime", NULL, NULL, REG_OPTION_NON_VOLATILE, 
		KEY_WRITE, NULL, &hKey, &dwDisposition) != ERROR_SUCCESS)
	{
#ifdef _DEBUG
		AfxMessageBox("CREATE KEEPALIVETIME");
#endif
		return;
	}
*/
	// 시간 변수가 없으면 세팅...
	BOOL fRet = (::RegSetValueEx (hKey, "KeepAliveTime", NULL, REG_DWORD, 
				(BYTE*)&nkeepalivetime, sizeof(DWORD) ) == ERROR_SUCCESS);

	fRet = (::RegSetValueEx (hKey, "KeepAliveInterval", NULL, REG_DWORD, 
			(BYTE*)&nkeepaliveinterval, sizeof(DWORD) ) == ERROR_SUCCESS);

	::RegCloseKey (hKey);
//#endif
//
	m_fSuspend = FALSE;

	m_strServerName = lpszServerName;

	m_hKey = NULL;
	strRegKey = CString(_T("SYSTEM\\CurrentControlSet\\Services\\"));
	strRegKey += m_strServerName;
	strRegKey += _T("\\Config");
	if (RegOpenKeyEx (HKEY_LOCAL_MACHINE, strRegKey, 0, KEY_READ, &m_hKey) != ERROR_SUCCESS)
	{
#ifdef _DEBUG
		AfxMessageBox("CONFIG");
#endif
		return;
	}

	if (!GetConfigInt (NULL, _T("ID"), m_nServerID))
		m_nServerID = 0;

	if (!GetConfigString (NULL, _T("Addr"), m_strServerAddr))
		m_strServerAddr = _T("");

	if (!GetConfigInt (NULL, _T("Port"), m_nServerPort))
		m_nServerPort = 0;

	if (!GetConfigInt (NULL, _T("Capacity"), m_nCapacity))
		m_nCapacity = 1;
	if (!GetConfigInt (NULL, _T("Timer"), (int&)m_dwTimer))
		m_dwTimer = 0;
	if (!GetConfigInt (NULL, _T("TimeOut"), (int&)m_dwTimeOut))
		m_dwTimeOut = 0;

	if (!GetConfigString (NULL, _T("GameID"), m_strGameID))		m_strGameID = _T("Droiyan");
	if (!GetConfigString (NULL, _T("UserID"), m_strUserID))		m_strUserID = _T("Droiyan");
	if (!GetConfigString (NULL, _T("Password"), m_strPassword))	m_strPassword = _T("Droiyan");
}

CBaseCom::~CBaseCom ()
{
	RegCloseKey( m_hKey );
	WSACleanup();
}

BOOL CBaseCom::OnStartService()
{
	if ( !m_UserBase.Listen( m_nServerPort, (char *)LPCTSTR(m_strServerAddr) ) )
		return FALSE;

	// ACCEPT THREAD ENABLE...
	//m_UserBase.m_bAcceptEnableFlag = TRUE;

	m_fSuspend = FALSE; 
	m_dwLastTime = GetTickCount ();

	return TRUE;
}

void CBaseCom::OnStopService()
{
}

BOOL CBaseCom::OnContinueService()
{
	m_fSuspend = FALSE; 
	m_dwLastTime = GetTickCount ();

	return TRUE;
}

void CBaseCom::OnPauseService()
{
	m_fSuspend = TRUE; 
}

BOOL CBaseCom::Process()
{
	return TRUE;
}

void CBaseCom::OnTimer ()
{
}

BOOL CBaseCom::OnOpenSession (CSessDesc* pDes)
{
	if (m_fSuspend)
		return FALSE;

	pDes->m_dwLastTime = ::GetTickCount ();
	return TRUE;
}

void CBaseCom::OnCloseSession (CSessDesc* pDes, int nCode)
{
	pDes->Close ();
}

int CBaseCom::OnReceiveMsg (CSessDesc* pDes, CMsg& msg)
{
	return 0;
}

BOOL CBaseCom::GetConfigInt(LPCTSTR lpszKey, LPCTSTR lpszName, int & nValue)
{
	if (!m_hKey)
		return FALSE;

	HKEY hKey = NULL;
	if (RegOpenKeyEx (m_hKey, lpszKey, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
		return FALSE;

	DWORD dwType, dwLen;
	dwLen = sizeof (DWORD);
	BOOL fRet = (RegQueryValueEx (hKey, lpszName, NULL, &dwType, 
		(BYTE*)&nValue, &dwLen) == ERROR_SUCCESS && dwType == REG_DWORD);
	RegCloseKey (hKey);
	return fRet;
}

BOOL CBaseCom::GetConfigString(LPCTSTR lpszKey, LPCTSTR lpszName, CString & strValue)
{
	if (!m_hKey)
		return FALSE;

	HKEY hKey = NULL;
	if (RegOpenKeyEx (m_hKey, lpszKey, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
		return FALSE;

	DWORD dwType, dwLen;
	TCHAR szValue[128];
	dwLen = sizeof (szValue);
	BOOL fRet = (RegQueryValueEx (hKey, lpszName, NULL, &dwType, 
		(BYTE*)&szValue[0], &dwLen) == ERROR_SUCCESS && dwType == REG_SZ);
	RegCloseKey (hKey);
	strValue = szValue;
	return fRet;
}

