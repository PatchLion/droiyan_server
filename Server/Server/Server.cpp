/////////////////////////////////////////////////////////////////////
//	Server.cpp : Defines the class behaviors for the application.
//  Copyright (C) 2000,  Jin-Soo Jeon
//
//	If this code works, it was written by Jin-Soo Jeon.
//	If not, I don't know who wrote it.
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerApp

BEGIN_MESSAGE_MAP(CServerApp, CWinApp)
	//{{AFX_MSG_MAP(CServerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerApp construction

CServerApp::CServerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

CServerApp::~CServerApp()
{
	VERIFY(SOCKET_ERROR != WSACleanup());
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CServerApp object

CServerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CServerApp initialization

BOOL CServerApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// Load Winsock 2.2
	if(!LoadWinsock()) return FALSE;

#ifdef _AFXDLL
//	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	//Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// 다국어 버전 만들기
	HINSTANCE hInstanceLanguagePack = LoadLibrary("DRRCKorean.dll");

	if (NULL != hInstanceLanguagePack)	
		AfxSetResourceHandle(hInstanceLanguagePack);
	//

	CServerDlg dlg;
	m_pMainWnd = &dlg;

	dlg.m_InstanceChecker.ActivateChecker();
	if (dlg.m_InstanceChecker.PreviousInstanceRunning())
	{
		//AfxMessageBox(_T("Previous version detected, will now restore it"), MB_OK);
		dlg.m_InstanceChecker.ActivatePreviousInstance();
		m_pMainWnd = NULL;
		return FALSE;
	}

	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	AfxSetResourceHandle(AfxGetInstanceHandle());

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////
//	Load Winsock DLL ver 2.2
//
BOOL CServerApp::LoadWinsock()
{
	CString strError;

	// request minimum Winsock 2.2
	WORD wVersionRequested = MAKEWORD( 2, 2 );

	WSADATA wsaData;
	int err = WSAStartup( wVersionRequested, &wsaData );

	if( err != 0 )
	{
		strError.Format(_T("WSAStartup Error, Error# = %d"), ::GetLastError());
		AfxMessageBox(strError);
		return FALSE;
	}

	if( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 )
	{
		
		strError.Format( _T("Unsupported WinSock version %d.%d" ),
						 LOBYTE( wsaData.wVersion ),
						 HIBYTE( wsaData.wVersion ) );

		AfxMessageBox(strError);
		return FALSE;
	}

	return TRUE;
}
