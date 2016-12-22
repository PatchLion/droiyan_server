// Database.h: interface for the CDatabase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASE_H__C95DC859_6183_11D2_A57C_00A0248552AD__INCLUDED_)
#define AFX_DATABASE_H__C95DC859_6183_11D2_A57C_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SQLOK(nResult)	(nResult == SQL_SUCCESS || nResult == SQL_SUCCESS_WITH_INFO)

class CDatabase : public CObject  
{
protected:
	friend class CRecordset;
	SQLHDBC	m_hdbc;

public:
	void Close ();
	BOOL Open (LPCTSTR lpszConnect);
	BOOL IsOpen ();
	CDatabase();
	virtual ~CDatabase();
};

#endif // !defined(AFX_DATABASE_H__C95DC859_6183_11D2_A57C_00A0248552AD__INCLUDED_)
