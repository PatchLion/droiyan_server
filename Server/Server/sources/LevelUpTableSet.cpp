// LevelUpTableSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "LevelUpTableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLevelUpTableSet

IMPLEMENT_DYNAMIC(CLevelUpTableSet, CRecordset)

CLevelUpTableSet::CLevelUpTableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CLevelUpTableSet)
	m_iExp = 0;
	m_sLevel = 0;
	m_tBasicUp = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CLevelUpTableSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CLevelUpTableSet::GetDefaultSQL()
{
	return _T("[dbo].[LEVEL_UP]");
}

void CLevelUpTableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CLevelUpTableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_BigInt(pFX, _T("[iExp]"), m_iExp);
	RFX_Int(pFX, _T("[sLevel]"), m_sLevel);
	RFX_Byte(pFX, _T("[tBasicUp]"), m_tBasicUp);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CLevelUpTableSet diagnostics

#ifdef _DEBUG
void CLevelUpTableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CLevelUpTableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
