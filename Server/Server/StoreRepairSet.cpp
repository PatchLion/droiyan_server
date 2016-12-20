// StoreRepairSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "StoreRepairSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStoreRepairSet

IMPLEMENT_DYNAMIC(CStoreRepairSet, CRecordset)

CStoreRepairSet::CStoreRepairSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CStoreRepairSet)
	m_sStoreID = 0;
	m_sItemID = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CStoreRepairSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CStoreRepairSet::GetDefaultSQL()
{
	return _T("[dbo].[STORE_REPAIR]");
}

void CStoreRepairSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CStoreRepairSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sStoreID]"), m_sStoreID);
	RFX_Int(pFX, _T("[sItemID]"), m_sItemID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CStoreRepairSet diagnostics

#ifdef _DEBUG
void CStoreRepairSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CStoreRepairSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
