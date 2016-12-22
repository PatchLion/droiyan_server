// SerialSet.h: interface for the CSerialSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIALSET_H__C95DC85C_6183_11D2_A57C_00A0248552AD__INCLUDED_)
#define AFX_SERIALSET_H__C95DC85C_6183_11D2_A57C_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Recordset.h"

class CSerialSet : public CRecordset  
{
protected:
	void DataExchange ();
	virtual void BindColumn ();

public:
	BOOL RegSerial ();

	CString m_strUserID;
	WORD m_wSerial;
	WORD m_wGameSerial;
	WORD m_wPrivateSerial;
	BYTE m_bCheckResult;
	CString m_strPasswd;
	CTime m_timeStart;
	CTime m_timeEnd;
	int m_nCurReg;

	CSerialSet(CDatabase* pDB);
	virtual ~CSerialSet();
};

#endif // !defined(AFX_SERIALSET_H__C95DC85C_6183_11D2_A57C_00A0248552AD__INCLUDED_)
