// LogSet.h: interface for the CLogSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGSET_H__C95DC85D_6183_11D2_A57C_00A0248552AD__INCLUDED_)
#define AFX_LOGSET_H__C95DC85D_6183_11D2_A57C_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Recordset.h"

class CLogSet : public CRecordset  
{
protected:
	virtual void DataExchange ();
	virtual void BindColumn ();

public:	
	CDatabase * db;

	BOOL Initialize ();
	BYTE ChangePass(CString cPasswd);
	int m_nServiceID;
	CString m_strUserID;
	CString m_strPasswd;

//	CString m_strIPAddr;
	TCHAR	m_strIPAddr[IP_LENGTH];
	_int64	m_lIPNum;			// IPAddr --> bigint(8 byte) convert

	DWORD m_wSerial;
	BYTE m_bReason;
	CString m_strBizNo;
	CString m_strNicAddr;

	BYTE m_bLoginResult;
	BYTE m_bCheckResult;

	CLogSet(CDatabase* pDB);
	virtual ~CLogSet();

	BOOL Logout();
	//BOOL Login ();
	//BOOL Login( CString strGameID );
	int CheckTelecomIP();
	BOOL Login(BYTE fPay, BYTE& bDisplay, int& remainTime, TIMESTAMP_STRUCT& endTime, TCHAR *ServerIP, BYTE& viewType);

	BOOL GetGameRoomInfo();
};

#endif // !defined(AFX_LOGSET_H__C95DC85D_6183_11D2_A57C_00A0248552AD__INCLUDED_)
