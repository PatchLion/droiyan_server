// UserSet.h: interface for the CUserSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERSET_H__C95DC85B_6183_11D2_A57C_00A0248552AD__INCLUDED_)
#define AFX_USERSET_H__C95DC85B_6183_11D2_A57C_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Recordset.h"
 
class CUserSet : public CRecordset  
{
protected:
	virtual void DataExchange ();
	virtual void BindColumn ();

public:
	BOOL GetUser ();
	BOOL UpdateUser ();
	BOOL NewUser ();

	CString m_strUserID;
	CString m_strPasswd;
	CString m_strName;
	CString m_strSocNo;
	CString m_strAddr;
	CString m_strTel;
	CString m_strEMail;

	CUserSet(CDatabase* pDB);
	virtual ~CUserSet();
};

#endif // !defined(AFX_USERSET_H__C95DC85B_6183_11D2_A57C_00A0248552AD__INCLUDED_)
