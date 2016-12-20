// UserManager.h: interface for the CUserManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERMANAGER_H__691746A4_2381_11D2_A54A_00A0248552AD__INCLUDED_)
#define AFX_USERMANAGER_H__691746A4_2381_11D2_A54A_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Service.h"

class CUserManager : public CService  
{
public:
	void KickoutUser (LPCTSTR lpszUserID, int nServiceID);
	int m_nFMPort;
	int m_nGSPort;
	CString m_strFMAddr;
	CString m_strGSAddr;
	CString	m_strModulePath;
	CUserManager(CServer* pServer, LPCTSTR lpszModule,
		LPCTSTR lpszAddr, int nPort, int nCapacity, 
		DWORD dwStatus = SERVICE_STOPPED);
	virtual ~CUserManager();
};

#endif // !defined(AFX_USERMANAGER_H__691746A4_2381_11D2_A54A_00A0248552AD__INCLUDED_)
