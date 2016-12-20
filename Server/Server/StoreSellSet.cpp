// StoreSellSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "StoreSellSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStoreSellSet

IMPLEMENT_DYNAMIC(CStoreSellSet, CRecordset)

CStoreSellSet::CStoreSellSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CStoreSellSet)
	m_sStoreID = 0;
	m_sItemID = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CStoreSellSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CStoreSellSet::GetDefaultSQL()
{
	return _T("[dbo].[STORE_SELL]");
}

void CStoreSellSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CStoreSellSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sStoreID]"), m_sStoreID);
	RFX_Int(pFX, _T("[sItemID]"), m_sItemID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CStoreSellSet diagnostics

#ifdef _DEBUG
void CStoreSellSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CStoreSellSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
