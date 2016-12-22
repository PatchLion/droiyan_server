// Recordset.h: interface for the CRecordset class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECORDSET_H__C95DC85A_6183_11D2_A57C_00A0248552AD__INCLUDED_)
#define AFX_RECORDSET_H__C95DC85A_6183_11D2_A57C_00A0248552AD__INCLUDED_
 
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_DATALEN	8192
#define MAX_COLUMN	256

#include "Database.h"

class CRecordset : public CObject  
{
protected:
	void DXInt (int nCol, int& nField);
	void DXTime (int nCol, CTime& timeField);
	void DXByte (int nCol, BYTE& bField);
	void DXDWord (int nCol, DWORD& dwField);
	void DXWord (int nCol, WORD& wField);
	void DXString (int nCol, CString& strField);
	BYTE m_bufData[MAX_DATALEN];
	BYTE* m_pDataPos[MAX_COLUMN];
	DWORD m_dwDataLen[MAX_COLUMN];

	SQLSMALLINT m_nNumCol;
	SQLHSTMT m_hstmt;
	CDatabase* m_pDB;

	void Bind (int nCol, SQLSMALLINT nType, DWORD dwLen = 0);
	virtual void BindColumn ();
	virtual void DataExchange ();

#ifdef _DEBUG
	void DisplayError (SQLRETURN nResult, SWORD fHandleType, SQLHANDLE handle);
#endif
	
public:
	int Execute(LPCTSTR lpszQuery);
	BOOL IsFieldNull (int nCol);
	BOOL Fetch ();
	BOOL Open ();
	BOOL Query (LPCTSTR lpszQuery);
	BOOL IsOpen ();
	void Close ();

	CRecordset(CDatabase* pDB);
	virtual ~CRecordset();
};

#endif // !defined(AFX_RECORDSET_H__C95DC85A_6183_11D2_A57C_00A0248552AD__INCLUDED_)
