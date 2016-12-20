// UserManager.cpp: implementation of the CUserManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServiceManager.h"
#include "ServiceManagerDoc.h"
#include "UserManager.h"
#include "Server.h"
#include "Session.h"
#include "../include/UMProtocol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserManager::CUserManager(CServer* pServer, 
						   LPCTSTR lpszModule,
						   LPCTSTR lpszAddr, 
						   int nPort, 
						   int nCapacity, 
						   DWORD dwStatus/*=SERVICE_STOPPED*/)
:CService(pServer, 
		  CService::typeUM, 
		  lpszModule,
		  CString (pServer->m_pDoc->m_strGameID) + _T(" User Manager"), 
		  0, 
		  lpszAddr, 
		  nPort, 
		  nCapacity, 
		  0, 
		  0, 
		  dwStatus)
{
	m_strModulePath = m_strModule.Left (m_strModule.GetLength () - 16);
}

CUserManager::~CUserManager()
{

}


void CUserManager::KickoutUser(LPCTSTR lpszUserID, int nServiceID)
{
	if (m_fConnect)
	{
		CMsg msg;
		msg.ID (UM_KICKOUT_REQ) 
			<< lpszUserID 
			<< (BYTE)nServiceID
			<< DR_CANCEL;
		SendMsg (msg);
	}
}
