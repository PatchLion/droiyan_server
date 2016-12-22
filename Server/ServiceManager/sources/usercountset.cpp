// UserCountSet.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "UserCountSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserCountSet

IMPLEMENT_DYNAMIC(CUserCountSet, CRecordset)

CUserCountSet::CUserCountSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CUserCountSet)
	m_nServiceID = 0;
	m_nNumUser = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CUserCountSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=SOMA");
	return _T("ODBC;DSN=Droiyan;UID=Droiyan;PWD=Droiyan");
}

CString CUserCountSet::GetDefaultSQL()
{
	return _T("[dbo].[USERCOUNT]");
}

void CUserCountSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CUserCountSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[nServiceID]"), m_nServiceID);
	RFX_Long(pFX, _T("[nNumUser]"), m_nNumUser);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CUserCountSet diagnostics

#ifdef _DEBUG
void CUserCountSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CUserCountSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
