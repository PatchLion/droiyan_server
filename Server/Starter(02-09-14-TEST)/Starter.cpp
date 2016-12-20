// Starter.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Starter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStarterApp

BEGIN_MESSAGE_MAP(CStarterApp, CWinApp)
	//{{AFX_MSG_MAP(CStarterApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStarterApp construction

CStarterApp::CStarterApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CStarterApp object

CStarterApp theApp;
TCHAR g_szAppName[256] = _T("Starter");

/////////////////////////////////////////////////////////////////////////////
// CStarterApp initialization

BOOL CStarterApp::InitInstance()
{
	TCHAR szOption[32];
	sscanf (m_lpCmdLine, "%s", szOption);

	if (!strcmpi (szOption, _T("install")))
	{
		TCHAR		szModulePath[_MAX_PATH];

		SC_HANDLE hSCM = OpenSCManager (NULL, NULL, SC_MANAGER_CREATE_SERVICE);
		GetModuleFileName (NULL, szModulePath, _MAX_PATH);
		SC_HANDLE hService = CreateService (hSCM, g_szAppName, g_szAppName, 0,
			SERVICE_WIN32_OWN_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_IGNORE,
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

	m_nServerID = 0;
	m_nCapacity = 50;
	m_dwTimer = 500;
	m_dwTimeOut = 0;

	m_hKey = NULL;
	CString strRegKey (_T("SYSTEM\\CurrentControlSet\\Services\\"));
	strRegKey += m_strServerName;
	RegOpenKeyEx (HKEY_LOCAL_MACHINE, strRegKey, 0, KEY_READ, &m_hKey);
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
		CSessDesc* pDes = new CSessDesc;
		if (!pDes)
			return FALSE;
		m_listInactive.AddTail (pDes);
	}

	m_sockListen = OpenServer (NULL, 3000);
	if (m_sockListen == INVALID_SOCKET)
		return FALSE;

	m_fSuspend = FALSE; 
	m_dwLastTime = GetTickCount ();

	return TRUE;
}

void CBaseCom::OnStopService()
{
	closesocket (m_sockListen);
	m_sockListen = INVALID_SOCKET;

	while (!m_listActive.IsEmpty ())
		delete m_listActive.RemoveHead ();

	while (!m_listInactive.IsEmpty ())
		delete m_listInactive.RemoveHead ();
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
	POSITION pos = m_listActive.GetHeadPosition ();
	while (pos)
	{
		CSessDesc* pDes = (CSessDesc*)m_listActive.GetNext (pos);
		OnCloseSession (pDes, ERROR_SUSPEND);
		pDes->Close ();
		m_listInactive.AddTail (pDes);
	}
	m_listActive.RemoveAll ();
}

BOOL CBaseCom::Process()
{
	struct timeval t;
	fd_set	fdr, fds;
	FD_ZERO (&fdr);
	FD_ZERO (&fds);
	FD_SET (m_sockListen, &fdr);

	DWORD dwCurrentTime = GetTickCount ();
	POSITION pos, pos1;

	pos = m_listActive.GetHeadPosition ();
	while (pos)
	{
		pos1 = pos;
		CSessDesc* pDes = (CSessDesc*)m_listActive.GetNext (pos);
		if (!pDes->IsValid ())
		{
			m_listActive.RemoveAt (pos1);
			m_listInactive.AddTail (pDes);
		}
		else if (pDes->IsTimeOut (dwCurrentTime, m_dwTimeOut))
			OnCloseSession (pDes, ERROR_RECVTIMEOUT);
		else
		{
			FD_SET (pDes->GetClientSock (), &fdr);
			if (pDes->m_nWrCntClient)
				FD_SET (pDes->GetClientSock (), &fds);
			if (pDes->IsLinked ())
			{
				FD_SET (pDes->GetServerSock (), &fdr);
				if (pDes->m_nWrCntServer)
					FD_SET (pDes->GetServerSock (), &fds);
			}
		}
	}

	t.tv_sec = 0;
	if (m_dwTimer)
	{
		if (!m_fSuspend)
		{
			while (dwCurrentTime - m_dwLastTime > m_dwTimer)
			{
				OnTimer ();
				m_dwLastTime += m_dwTimer;
			}
		}
		t.tv_usec = (dwCurrentTime - m_dwLastTime) * 1000;
	}
	else
		t.tv_usec = 1000;

	if (::select (0, &fdr, &fds, NULL, &t))
	{
		pos = m_listActive.GetHeadPosition ();
		while (pos)
		{
			pos1 = pos;
			int nError;
			CSessDesc* pDes = (CSessDesc*)m_listActive.GetNext (pos);
			if (pDes->IsLinked ())
			{
				if (FD_ISSET (pDes->GetClientSock (), &fdr))
				{
					pDes->m_dwLastTime = dwCurrentTime;
					nError = pDes->ClientToServer ();
					if (nError)
						OnCloseSession (pDes, nError);
				}
				if (FD_ISSET (pDes->GetServerSock (), &fdr))
				{
					nError = pDes->ServerToClient ();
					if (nError)
						OnCloseSession (pDes, nError);
				}
				if (pDes->m_nWrCntClient &&
					FD_ISSET (pDes->GetClientSock (), &fds))
				{
					int nSend = send (pDes->GetClientSock (), 
						(char*)&pDes->m_bufClient[0], pDes->m_nWrCntClient, 0);
					if (nSend < 0)
						OnCloseSession (pDes, ERROR_CLIENTSEND);
					else if (nSend > 0)
					{
						pDes->m_nWrCntClient -= nSend;
						memmove (&pDes->m_bufClient[0], 
							&pDes->m_bufClient[nSend], pDes->m_nWrCntClient);
					}
				}
				if (pDes->m_nWrCntServer && 
					FD_ISSET (pDes->GetServerSock (), &fds))
				{
					int nSend = send (pDes->GetServerSock (), 
						(char*)&pDes->m_bufServer[0], pDes->m_nWrCntServer, 0);
					if (nSend < 0)
						OnCloseSession (pDes, ERROR_CLIENTSEND);
					else if (nSend > 0)
					{
						pDes->m_nWrCntServer -= nSend;
						memmove (&pDes->m_bufServer[0], 
							&pDes->m_bufServer[nSend], pDes->m_nWrCntServer);
					}
				}
			}
			else
			{
				if (FD_ISSET (pDes->GetClientSock (), &fdr))
				{
					pDes->m_dwLastTime = dwCurrentTime;
					nError = pDes->Hear ();
					if (nError)
						OnCloseSession (pDes, nError);
					else
					{
						while (!nError && pDes->CheckMsg ())
						{
							nError = OnReceiveMsg (pDes, pDes->m_msg);
							if (nError)
								OnCloseSession (pDes, nError);
							else
								pDes->Copy ();
						}
					}
				}
				if (pDes->m_nWrCntClient && 
					FD_ISSET (pDes->GetClientSock (), &fds))
				{
					int nSend = send (pDes->GetClientSock (), 
						(char*)&pDes->m_bufClient[0], pDes->m_nWrCntClient, 0);
					if (nSend < 0)
						OnCloseSession (pDes, ERROR_CLIENTSEND);
					else if (nSend > 0)
					{
						pDes->m_nWrCntClient -= nSend;
						memmove (&pDes->m_bufClient[0], 
							&pDes->m_bufClient[nSend], pDes->m_nWrCntClient);
					}
				}
			}
		}

		if (FD_ISSET (m_sockListen, &fdr))
		{
			if (m_fSuspend)
			{
				CSessDesc* pDes = new CSessDesc;
				if (pDes->Create (m_sockListen))
					OnCloseSession (pDes, ERROR_SUSPEND);
				delete pDes;
			}
			else if (m_listInactive.IsEmpty ())
			{
				CSessDesc* pDes = new CSessDesc;
				if (pDes->Create (m_sockListen))
					OnCloseSession (pDes, ERROR_SERVERFULL);
				delete pDes;
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
		}
	}
	
	return TRUE;
}

void CBaseCom::OnTimer ()
{
}

BOOL CBaseCom::OnOpenSession (CSessDesc* pDes)
{
	struct sockaddr_in client_addr;
	int nLen = sizeof (client_addr);
	getpeername (pDes->GetClientSock (), (struct sockaddr *)&client_addr, &nLen);
	CString strIPAddr = inet_ntoa (client_addr.sin_addr);

	////////////////////////////////////////////////////////////////////////
	// 중국 IP대역
//	if(strIPAddr.Left(10).CompareNoCase(_T("211.99.58.")))
	if(strIPAddr.Left(9).CompareNoCase(_T("172.20.3.")))
		return FALSE;

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

BOOL CBaseCom::SetConfigString (LPCTSTR lpszKey, LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (!m_hKey)
		return FALSE;

	HKEY hKey = NULL;
	if (RegOpenKeyEx (m_hKey, lpszKey, 0, KEY_WRITE, &hKey) != ERROR_SUCCESS)
		return FALSE;

	DWORD dwType = REG_SZ, dwLen = strlen (lpszValue) + 1;
	BOOL fRet = (RegSetValueEx (hKey, lpszName, NULL, dwType, 
		(BYTE*)lpszValue, dwLen) == ERROR_SUCCESS);
	RegCloseKey (hKey);
	return fRet;
}

BOOL CBaseCom::SetConfigInt (LPCTSTR lpszKey, LPCTSTR lpszName, int nValue)
{
	if (!m_hKey)
		return FALSE;

	HKEY hKey = NULL;
	if (RegOpenKeyEx (m_hKey, lpszKey, 0, KEY_WRITE, &hKey) != ERROR_SUCCESS)
		return FALSE;

	DWORD dwType = REG_DWORD, dwLen = sizeof (DWORD);
	BOOL fRet = (RegSetValueEx (hKey, lpszName, NULL, dwType, 
		(BYTE*)&nValue, dwLen) == ERROR_SUCCESS && dwType == REG_DWORD);
	RegCloseKey (hKey);
	return fRet;
}

