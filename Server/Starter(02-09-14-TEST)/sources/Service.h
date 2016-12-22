// Service.h: interface for the CService class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVICE_H__2937F9E6_21EA_11D2_A547_00A0248552AD__INCLUDED_)
#define AFX_SERVICE_H__2937F9E6_21EA_11D2_A547_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CService : public CObject  
{
public:
	BOOL RemoveService ();
	BOOL PauseService();
	BOOL ContinueService();
	BOOL StopService ();
	BOOL StartService ();
	BOOL InstallService (LPCTSTR lpszModulePath, LPCTSTR lpszGameID, LPCTSTR lpszUserID, LPCTSTR lpszPassword,
		LPCTSTR lpszServiceName, LPCTSTR lpszDisplayName, 
		int nID, LPCTSTR lpszAddr, int nPort, 
		int nCapacity, int nTimer, int nTimeOuts);
	DWORD m_dwStatus;
	BOOL GetConfigInt (LPCTSTR lpszName, int& nValue);
	BOOL SetConfigInt (LPCTSTR lpszName, int nValue);
	BOOL GetConfigString (LPCTSTR lpszName, CString& strValue);
	BOOL SetConfigString (LPCTSTR lpszName, LPCTSTR lpszValue);

	CString m_strGameID;
	CString m_strUserID;
	CString m_strPassword;
	CString m_strModule;
	int m_nTimer;
	int m_nTimeOuts;
	int m_nCapacity;
	int m_nPort;
	CString m_strAddr;
	int m_nID;
	CString m_strDisplayName;
	CString m_strServiceName;

	CService();
	CService(ENUM_SERVICE_STATUS& ss);
	virtual ~CService();
};

#endif // !defined(AFX_SERVICE_H__2937F9E6_21EA_11D2_A547_00A0248552AD__INCLUDED_)
