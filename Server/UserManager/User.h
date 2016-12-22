// User.h: interface for the CUser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USER_H__5589653B_178D_11D2_A53D_00A0248552AD__INCLUDED_)
#define AFX_USER_H__5589653B_178D_11D2_A53D_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CUser : public CObject  
{
public:
	CUser(int nID, LPCTSTR lpszIPAddr);
	virtual ~CUser();

	void Login (LPCTSTR lpszUserID, LPCTSTR lpszPasswd, CTime timeLogin);

	// User Identify
	int m_nID;
	CString m_strUserID;
	CString m_strPasswd;
	CString m_strIPAddr;

	// Check Result
	BYTE m_bLoginResult;
	BYTE m_bCheckResult;

	// User Time
	CTime m_timeLog;

	// Serial Data
	WORD m_wSerial;
	BOOL m_fIsGameroomSerial;
};

#endif // !defined(AFX_USER_H__5589653B_178D_11D2_A53D_00A0248552AD__INCLUDED_)
