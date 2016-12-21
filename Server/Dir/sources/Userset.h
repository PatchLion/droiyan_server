// Userset.h: interface for the CUserset class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERSET_H__523B480A_4F90_11D3_BBC1_00C02615866B__INCLUDED_)
#define AFX_USERSET_H__523B480A_4F90_11D3_BBC1_00C02615866B__INCLUDED_

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
	CString m_strUserID;
	WORD m_nZoneNumber;  // Insert code when server is added.

	CUserSet(CDatabase* pDB);
	virtual ~CUserSet();

	BOOL GetZoneNumber();
	BOOL GetLogInZoneNumber();
};

#endif // !defined(AFX_USERSET_H__523B480A_4F90_11D3_BBC1_00C02615866B__INCLUDED_)
