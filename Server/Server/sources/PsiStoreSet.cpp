// PsiStoreSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "PsiStoreSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPsiStoreSet

IMPLEMENT_DYNAMIC(CPsiStoreSet, CRecordset)

CPsiStoreSet::CPsiStoreSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CPsiStoreSet)
	m_sStoreID = 0;
	m_sPsiID = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CPsiStoreSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CPsiStoreSet::GetDefaultSQL()
{
	return _T("[dbo].[PSI_STORE]");
}

void CPsiStoreSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPsiStoreSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sStoreID]"), m_sStoreID);
	RFX_Int(pFX, _T("[sPsiID]"), m_sPsiID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CPsiStoreSet diagnostics

#ifdef _DEBUG
void CPsiStoreSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CPsiStoreSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
