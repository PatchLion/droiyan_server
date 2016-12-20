// SessThread.cpp : implementation file
//

#include "stdafx.h"
#include "FileManager.h"
#include "SessThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSessThread

IMPLEMENT_DYNCREATE(CSessThread, CWinThread)

CSessThread::CSessThread()
{
}

CSessThread::~CSessThread()
{
}

BOOL CSessThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CSessThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSessThread, CWinThread)
	//{{AFX_MSG_MAP(CSessThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSessThread message handlers

int CSessThread::Run() 
{
	
	return CWinThread::Run();
}

BOOL CSessThread::OnIdle(LONG lCount) 
{
	return CWinThread::OnIdle(lCount);
}

BOOL CSessThread::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	
	return CWinThread::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
