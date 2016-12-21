///////////////////////////////////////////////////////////////////////////////
// Service Main

#include "stdafx.h"
#include "FileManager.h"
#include "FileManagerCom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HANDLE g_hIOCP = NULL;
extern TCHAR g_szAppName[];
//CErrorLog		g_ErrorLog;


DWORD dwSrvCtrlToPend[256] = {
	SERVICE_START_PENDING,
	SERVICE_STOP_PENDING,
	SERVICE_PAUSE_PENDING,
	SERVICE_CONTINUE_PENDING,
	0,
	SERVICE_STOP_PENDING,
	0
};

DWORD dwSrvPendToState[] = 
{
	0,
	0,
	SERVICE_RUNNING,
	SERVICE_STOPPED,
	0,
	SERVICE_RUNNING,
	SERVICE_PAUSED,
	0
};

void WINAPI ServiceHandler (DWORD dwControl)
{
	if (g_hIOCP)
		PostQueuedCompletionStatus (g_hIOCP, dwControl, 1, NULL);
}

void WINAPI ServiceMain (DWORD dwArgc, LPTSTR* lpszArgv)
{
	BOOL			fControlKey = TRUE;
	DWORD			dwControl = 0;

//	g_ErrorLog.OpenFile();

#ifdef _DEBUG
	CFileManagerCom		com (g_szAppName);
#else
	CFileManagerCom		com (lpszArgv[0]);
#endif

	g_hIOCP = CreateIoCompletionPort (INVALID_HANDLE_VALUE, NULL, 1, 0);
	if (g_hIOCP == NULL)
		return;

#ifdef _DEBUG
	SERVICE_STATUS_HANDLE hSS = RegisterServiceCtrlHandler (
		g_szAppName, ServiceHandler);
#else
	SERVICE_STATUS_HANDLE hSS = RegisterServiceCtrlHandler (
		lpszArgv[0], ServiceHandler);
#endif
	
/*
	DWORD err = 0;
	if(hSS == 0) 
	{
		err = GetLastError();
		g_ErrorLog.WriteError2(TRUE, _T(""),_T("RegisterServiceCtrlHandler가 0\n"));
	}

	g_ErrorLog.WriteError2(TRUE, _T(""),_T("RegisterServiceCtrlHandler가 무사통과\n"));
*/	SERVICE_STATUS ss;
	ss.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	ss.dwControlsAccepted = SERVICE_ACCEPT_STOP |
		SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_SHUTDOWN;

	do
	{
		if (fControlKey)
		{
			ss.dwWin32ExitCode = NO_ERROR;
			ss.dwServiceSpecificExitCode = 0;
			ss.dwCheckPoint = 0;
			ss.dwWaitHint = 0;

			if (dwControl == SERVICE_CONTROL_INTERROGATE)
				SetServiceStatus (hSS, &ss);
			else
			{
				if (dwSrvCtrlToPend[dwControl] != 0)
				{
					ss.dwCurrentState = dwSrvCtrlToPend[dwControl];
					ss.dwCheckPoint = 0;
					ss.dwWaitHint = 500;
					SetServiceStatus (hSS, &ss);
				}

				switch (dwControl)
				{
				case 0 :
					if (!com.OnStartService ())
						PostQueuedCompletionStatus (g_hIOCP, SERVICE_CONTROL_STOP, 1, NULL);
					break;
		
				case SERVICE_CONTROL_CONTINUE :
					if (!com.OnContinueService ())
						PostQueuedCompletionStatus (g_hIOCP, SERVICE_CONTROL_STOP, 1, NULL);
					break;

				case SERVICE_CONTROL_PAUSE :
					com.OnPauseService ();
					break;
		
				case SERVICE_CONTROL_STOP :
				case SERVICE_CONTROL_SHUTDOWN :
					com.OnStopService ();
					break;
				}

				if (dwSrvPendToState[ss.dwCurrentState] != 0)
				{
					ss.dwCurrentState = dwSrvPendToState[ss.dwCurrentState];
					ss.dwCheckPoint = 0;
					ss.dwWaitHint = 0;
					SetServiceStatus (hSS, &ss);
				}
			}
		}
		else if (!com.Process ())
			PostQueuedCompletionStatus (g_hIOCP, SERVICE_CONTROL_STOP, 1, NULL);

		if (ss.dwCurrentState != SERVICE_STOPPED)
		{
			DWORD dwCompKey;
			OVERLAPPED* po;
			fControlKey = GetQueuedCompletionStatus (g_hIOCP, &dwControl, 
				&dwCompKey, &po, 0);
		}
	} while (ss.dwCurrentState != SERVICE_STOPPED);

	CloseHandle (g_hIOCP);
}
