// GuildFortressTaxSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "GuildFortressTaxSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuildFortressTaxSet

IMPLEMENT_DYNAMIC(CGuildFortressTaxSet, CRecordset)

CGuildFortressTaxSet::CGuildFortressTaxSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CGuildFortressTaxSet)
	m_sFortressID = 0;
	m_sStoreID01 = 0;
	m_sStoreID02 = 0;
	m_sStoreID03 = 0;
	m_sStoreID04 = 0;
	m_sStoreID05 = 0;
	m_sStoreID06 = 0;
	m_sStoreID07 = 0;
	m_sStoreID08 = 0;
	m_sStoreID09 = 0;
	m_sStoreID10 = 0;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CGuildFortressTaxSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgamenew;UID=drgame;PWD=drgame");
}

CString CGuildFortressTaxSet::GetDefaultSQL()
{
	return _T("[dbo].[GUILD_FORTRESS_TAX]");
}

void CGuildFortressTaxSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CGuildFortressTaxSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sFortressID]"), m_sFortressID);
	RFX_Int(pFX, _T("[sStoreID01]"), m_sStoreID01);
	RFX_Int(pFX, _T("[sStoreID02]"), m_sStoreID02);
	RFX_Int(pFX, _T("[sStoreID03]"), m_sStoreID03);
	RFX_Int(pFX, _T("[sStoreID04]"), m_sStoreID04);
	RFX_Int(pFX, _T("[sStoreID05]"), m_sStoreID05);
	RFX_Int(pFX, _T("[sStoreID06]"), m_sStoreID06);
	RFX_Int(pFX, _T("[sStoreID07]"), m_sStoreID07);
	RFX_Int(pFX, _T("[sStoreID08]"), m_sStoreID08);
	RFX_Int(pFX, _T("[sStoreID09]"), m_sStoreID09);
	RFX_Int(pFX, _T("[sStoreID10]"), m_sStoreID10);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CGuildFortressTaxSet diagnostics

#ifdef _DEBUG
void CGuildFortressTaxSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CGuildFortressTaxSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
