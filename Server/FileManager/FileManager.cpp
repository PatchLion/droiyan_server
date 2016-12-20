// FileManager.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FileManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileManagerApp

BEGIN_MESSAGE_MAP(CFileManagerApp, CWinApp)
	//{{AFX_MSG_MAP(CFileManagerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileManagerApp construction

CFileManagerApp::CFileManagerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFileManagerApp object

CFileManagerApp theApp;
TCHAR g_szAppName[256];

/////////////////////////////////////////////////////////////////////////////
// CFileManagerApp initialization

BOOL CFileManagerApp::InitInstance()
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

CBaseCom::CBaseCom (LPCTSTR lpszServerName)
{
	WORD	wVersionReq;
	WSADATA	wsaData;
	wVersionReq = MAKEWORD (2,2);
	if (WSAStartup (wVersionReq, &wsaData))
		return;

	m_sockListen = INVALID_SOCKET;
	m_fSuspend = FALSE;

	m_strServerName = lpszServerName;

	m_hKey = NULL;
	CString strRegKey (_T("SYSTEM\\CurrentControlSet\\Services\\"));
	strRegKey += m_strServerName;
	strRegKey += _T("\\Config");
	if (RegOpenKeyEx (HKEY_LOCAL_MACHINE, strRegKey, 0, KEY_READ, &m_hKey) != ERROR_SUCCESS)
		return;

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
//		m_strGameID = _T("NETGAME");
	if (!GetConfigString (NULL, _T("UserID"), m_strUserID))		m_strUserID = _T("Droiyan");
//		m_strUserID = _T("NETGAME");
	if (!GetConfigString (NULL, _T("Password"), m_strPassword))	m_strPassword = _T("Droiyan");
//		m_strPassword = _T("NETGAME");
}

CBaseCom::~CBaseCom ()
{
	if (m_sockListen != INVALID_SOCKET)
		closesocket (m_sockListen);

	while (!m_listActive.IsEmpty ())
		delete m_listActive.RemoveHead ();

	while (!m_listInactive.IsEmpty ())
		delete m_listInactive.RemoveHead ();

	RegCloseKey (m_hKey);
	WSACleanup ();
}

BOOL CBaseCom::OnStartService()
{
	for (int i = 0; i < m_nCapacity; i++)
	{
		CSessDesc* pDes = new CSessDesc (this);
		if (!pDes)
			return FALSE;
		m_listInactive.AddTail (pDes);
	}

	m_sockListen = OpenServer (m_strServerAddr, m_nServerPort);
	if (m_sockListen == INVALID_SOCKET)
		return FALSE;

	m_fSuspend = FALSE; 
	m_dwLastTime = GetTickCount ();

	::InitializeCriticalSection (&m_Section);

	return TRUE;
}

void CBaseCom::OnStopService()
{
	closesocket (m_sockListen);
	m_sockListen = INVALID_SOCKET;

	::EnterCriticalSection (&m_Section);

	POSITION pos = m_listActive.GetHeadPosition ();
	while (pos)
	{
		CSessDesc* pDes = (CSessDesc*)m_listActive.GetNext (pos);
		if (pDes->m_hThread)
			::TerminateThread (pDes->m_hThread, 0);
		pDes->Close ();
		delete pDes;
	}
	m_listActive.RemoveAll ();

	while (!m_listInactive.IsEmpty ())
		delete m_listInactive.RemoveHead ();

	::LeaveCriticalSection (&m_Section);
	::DeleteCriticalSection (&m_Section);
}

BOOL CBaseCom::OnContinueService()
{
	m_sockListen = OpenServer (m_strServerAddr, m_nServerPort);
	if (m_sockListen == INVALID_SOCKET)
		return FALSE;

	m_fSuspend = FALSE; 
	m_dwLastTime = GetTickCount ();

	return TRUE;
}

void CBaseCom::OnPauseService()
{
	m_fSuspend = TRUE; 
	closesocket (m_sockListen);
	m_sockListen = INVALID_SOCKET;
}

BOOL CBaseCom::Process()
{
	if (m_fSuspend)
		return TRUE;

	// Process Timer Function
	DWORD dwCurrentTime = GetTickCount ();
	if (m_dwTimer)
	{
		while (dwCurrentTime - m_dwLastTime > m_dwTimer)
		{
			OnTimer ();
			m_dwLastTime += m_dwTimer;
		}
	}

	// Socket Select
	fd_set	fdr;
	FD_ZERO (&fdr);
	FD_SET (m_sockListen, &fdr);

	struct timeval t;
	t.tv_sec = 0;
	t.tv_usec = 1000;

	::select (0, &fdr, NULL, NULL, &t);

	// if new connection...
	if (FD_ISSET (m_sockListen, &fdr))
	{
		::EnterCriticalSection (&m_Section);

		if (m_listInactive.IsEmpty ())
		{
			SOCKET sock = accept (m_sockListen, NULL, NULL);
			if (sock != INVALID_SOCKET)
				closesocket (sock);
		}
		else
		{
			CSessDesc* pDes = (CSessDesc*)m_listInactive.RemoveHead ();
			if (pDes->Create (m_sockListen))
			{
				if (!OnOpenSession (pDes))
				{
					OnCloseSession (pDes, ERROR_DENYOPEN);
					pDes->Close ();
					m_listInactive.AddTail (pDes);
				}
				else
					m_listActive.AddTail (pDes);
			}
			else
				m_listInactive.AddTail (pDes);
		}

		::LeaveCriticalSection (&m_Section);
	}
	
	return TRUE;
}

void CBaseCom::OnTimer ()
{
}

BOOL CBaseCom::OnOpenSession (CSessDesc* pDes)
{
	return TRUE;
}

void CBaseCom::OnCloseSession (CSessDesc* pDes, int nCode)
{
	pDes->Close ();

	::EnterCriticalSection (&m_Section);

	POSITION pos = m_listActive.Find (pDes);
	if (pos)
	{
		m_listActive.RemoveAt (pos);
		m_listInactive.AddTail (pDes);
	}

	::LeaveCriticalSection (&m_Section);
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



