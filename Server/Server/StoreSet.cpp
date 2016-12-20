// StoreSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "StoreSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStoreSet

IMPLEMENT_DYNAMIC(CStoreSet, CRecordset)

CStoreSet::CStoreSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CStoreSet)
	m_sStoreID = 0;
	m_sItemID = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CStoreSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CStoreSet::GetDefaultSQL()
{
	return _T("[dbo].[STORE]");
}

void CStoreSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CStoreSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sStoreID]"), m_sStoreID);
	RFX_Int(pFX, _T("[sItemID]"), m_sItemID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CStoreSet diagnostics

#ifdef _DEBUG
void CStoreSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CStoreSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
