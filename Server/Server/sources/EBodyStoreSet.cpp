// EBodyStoreSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "EBodyStoreSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEBodyStoreSet

IMPLEMENT_DYNAMIC(CEBodyStoreSet, CRecordset)

CEBodyStoreSet::CEBodyStoreSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CEBodyStoreSet)
	m_sStoreID = 0;
	m_sEbodyID = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CEBodyStoreSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CEBodyStoreSet::GetDefaultSQL()
{
	return _T("[dbo].[EBODY_STORE]");
}

void CEBodyStoreSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CEBodyStoreSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sStoreID]"), m_sStoreID);
	RFX_Int(pFX, _T("[sEbodyID]"), m_sEbodyID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEBodyStoreSet diagnostics

#ifdef _DEBUG
void CEBodyStoreSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEBodyStoreSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
