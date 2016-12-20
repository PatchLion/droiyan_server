#if !defined(AFX_SERIALKEY_H__3FFD99A3_7B4E_11D4_9030_00105A6B96E7__INCLUDED_)
#define AFX_SERIALKEY_H__3FFD99A3_7B4E_11D4_9030_00105A6B96E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SerialKey.h : header file
//
#include "Recordset.h"

/////////////////////////////////////////////////////////////////////////////
// CSerialKey recordset

class CSerialKey : public CRecordset  
{
public:
	BOOL GetSerialKey();
	CSerialKey(CDatabase* pDB);
	virtual ~CSerialKey();
	DWORD	m_wSerial;
	DWORD	m_SerialKey;

protected:
	void DataExchange();
	virtual void BindColumn();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALKEY_H__3FFD99A3_7B4E_11D4_9030_00105A6B96E7__INCLUDED_)
