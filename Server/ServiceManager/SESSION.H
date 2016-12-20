// Session.h: interface for the CSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SESSION_H__691746A1_2381_11D2_A54A_00A0248552AD__INCLUDED_)
#define AFX_SESSION_H__691746A1_2381_11D2_A54A_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Service.h"

class CSession : public CService  
{
public:
	void KickoutUser (LPCTSTR lpszUserID);
	CStringList m_listFilter;
	CObList m_listCount;
	BOOL m_fPay;
	int m_nUMPort;
	CString m_strUMAddr;
	CString m_strName;
	CString m_strModulePath;

	CSession(CServer* pServer, 
		LPCTSTR lpszModule,
		LPCTSTR lpszDisplayName, 
		int nServerID, 
		LPCTSTR lpszAddr, int nPort, 
		int nCapacity, DWORD dwTimeOuts, 
		DWORD dwStatus = SERVICE_STOPPED);
	virtual ~CSession();
};

#endif // !defined(AFX_SESSION_H__691746A1_2381_11D2_A54A_00A0248552AD__INCLUDED_)
