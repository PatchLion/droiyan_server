// Service.h: interface for the CService class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVICE_H__3731D1A4_2242_11D2_A549_00A0248552AD__INCLUDED_)
#define AFX_SERVICE_H__3731D1A4_2242_11D2_A549_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ClientSock.h"

class CServer;
class CService : public CClientSock  
{
public:
	void GetStatus ();
	virtual BOOL Continue ();
	virtual BOOL Pause ();
	virtual BOOL Stop ();
	virtual BOOL Start ();

	enum { typeNone, typeUM, typeSM, typeFM, typeGS };
	CString m_strGameID;
	CString m_strUserID;
	CString m_strPassword;
	int m_nType;
	CServer* m_pServer;
	DWORD m_dwStatus;
	DWORD m_dwTimeOuts;
	DWORD m_dwTimer;
	int m_nCapacity;
	int m_nPort;
	int m_nServerID;
	CString m_strAddr;
	CString m_strDisplayName;
	CString m_strModule;
	CString m_strServiceName;
	int m_nNumUser;
	BYTE m_bSuspend;
	CService(CServer* pServer, int nType,
		LPCTSTR lpszModule, LPCTSTR lpszDisplayName, int nServerID, 
		LPCTSTR lpszAddr, int nPort, 
		int nCapacity, DWORD dwTimer, DWORD dwTimeOuts,
		DWORD dwStatus = SERVICE_STOPPED);
	virtual ~CService();
	virtual void OnConnect(int nErrorCode);

protected:
	virtual void OnReceiveMsg (CMsg& msg);
};

#endif // !defined(AFX_SERVICE_H__3731D1A4_2242_11D2_A549_00A0248552AD__INCLUDED_)
