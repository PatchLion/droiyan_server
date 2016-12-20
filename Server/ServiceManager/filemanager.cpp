// FileManager.cpp: implementation of the CFileManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServiceManager.h"
#include "ServiceManagerDoc.h"
#include "FileManager.h"

#include "Server.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileManager::CFileManager(CServer* pServer, 
						   LPCTSTR lpszModule,
						   LPCTSTR lpszAddr, 
						   int nPort, 
						   int nCapacity, 
						   DWORD dwStatus/*=SERVICE_STOPPED*/)
:CService(pServer, 
		  CService::typeFM, 
		  lpszModule,
		  CString (pServer->m_pDoc->m_strGameID) + _T(" File Manager"), 
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

CFileManager::~CFileManager()
{

}
