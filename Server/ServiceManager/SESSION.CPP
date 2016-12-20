// Session.cpp: implementation of the CSession class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServiceManager.h"
#include "ServiceManagerDoc.h"
#include "Session.h"

#include "Service.h"
#include "Server.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSession::CSession(CServer* pServer, 
				   LPCTSTR lpszModule,
				   LPCTSTR lpszDisplayName,
				   int nServerID, 
				   LPCTSTR lpszAddr,
				   int nPort, 
				   int nCapacity,
				   DWORD dwTimeOuts, 
				   DWORD dwStatus/*=SERVICE_STOPPED*/)
:CService(pServer, 
		  CService::typeSM, 
		  lpszModule,
		  lpszDisplayName, 
		  nServerID, 
		  lpszAddr, 
		  nPort, 
		  nCapacity, 
		  0, 
		  dwTimeOuts, 
		  dwStatus)
{
	m_strModulePath = m_strModule.Left (m_strModule.GetLength () - 12);
}

CSession::~CSession()
{
	while (!m_listCount.IsEmpty ())
		delete m_listCount.RemoveHead ();
}
