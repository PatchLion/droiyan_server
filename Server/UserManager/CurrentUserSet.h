// CurrentUserSet.h: interface for the CCurrentUserSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURRENTUSERSET_H__AA8578C4_151A_11D3_AAD0_00A0248552AD__INCLUDED_)
#define AFX_CURRENTUSERSET_H__AA8578C4_151A_11D3_AAD0_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Recordset.h"

class CCurrentUserSet : public CRecordset  
{
protected:
	virtual void DataExchange();
	virtual void BindColumn();

public:
	CString	m_strUserID;
	int m_nServiceID;

	BOOL GetServiceID ();
	CCurrentUserSet(CDatabase* pDB);
	virtual ~CCurrentUserSet();

};

#endif // !defined(AFX_CURRENTUSERSET_H__AA8578C4_151A_11D3_AAD0_00A0248552AD__INCLUDED_)
