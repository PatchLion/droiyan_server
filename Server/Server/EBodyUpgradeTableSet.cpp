// EBodyUpgradeTableSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "EBodyUpgradeTableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEBodyUpgradeTableSet

IMPLEMENT_DYNAMIC(CEBodyUpgradeTableSet, CRecordset)

CEBodyUpgradeTableSet::CEBodyUpgradeTableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CEBodyUpgradeTableSet)
	m_tRandom1 = 0;
	m_tRandom2 = 0;
	m_tRandom3 = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CEBodyUpgradeTableSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CEBodyUpgradeTableSet::GetDefaultSQL()
{
	return _T("[dbo].[EBODY_UPGRADE]");
}

void CEBodyUpgradeTableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CEBodyUpgradeTableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Byte(pFX, _T("[tRandom1]"), m_tRandom1);
	RFX_Byte(pFX, _T("[tRandom2]"), m_tRandom2);
	RFX_Byte(pFX, _T("[tRandom3]"), m_tRandom3);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEBodyUpgradeTableSet diagnostics

#ifdef _DEBUG
void CEBodyUpgradeTableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEBodyUpgradeTableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
