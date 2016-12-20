#if !defined(AFX_BANKSERIAL_H__3FFD99A7_7B4E_11D4_9030_00105A6B96E7__INCLUDED_)
#define AFX_BANKSERIAL_H__3FFD99A7_7B4E_11D4_9030_00105A6B96E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Recordset.h"

class CBankSerial : public CRecordset 
{
protected:
	void DataExchange();
	virtual void BindColumn();

public:
	CBankSerial(CDatabase* pDB);
	virtual ~CBankSerial();

	BOOL GetSerialCode();
	
	DWORD	m_wSerial;
	DWORD	m_nBankID;
	CString	m_strSerialCode;
};

#endif // !defined(AFX_BANKSERIAL_H__3FFD99A7_7B4E_11D4_9030_00105A6B96E7__INCLUDED_)
