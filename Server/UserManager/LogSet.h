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
	int m_nServiceID;
	int m_nSessionID;
	CString m_strUserID;
	CString m_strPasswd;
	CString m_strIPAddr;
	WORD m_wSerial;

	BYTE m_bReason;

	BYTE m_bLoginResult;
	BYTE m_bCheckResult;

	CLogSet(CDatabase* pDB);
	virtual ~CLogSet();

	BOOL Logout();
	BOOL Login ();
};

#endif // !defined(AFX_LOGSET_H__C95DC85D_6183_11D2_A57C_00A0248552AD__INCLUDED_)
