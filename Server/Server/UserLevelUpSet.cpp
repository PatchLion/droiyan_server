// UserLevelUpSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "UserLevelUpSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserLevelUpSet

IMPLEMENT_DYNAMIC(CUserLevelUpSet, CRecordset)

CUserLevelUpSet::CUserLevelUpSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CUserLevelUpSet)
	m_sLevel = 0;
	m_sHP = 0;
	m_sPP = 0;
	m_sDamage = 0;
	m_sDefense = 0;
	m_sWeight = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CUserLevelUpSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CUserLevelUpSet::GetDefaultSQL()
{
	return _T("[dbo].[USER_LEVEL_UP]");
}

void CUserLevelUpSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CUserLevelUpSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sLevel]"), m_sLevel);
	RFX_Int(pFX, _T("[sHP]"), m_sHP);
	RFX_Int(pFX, _T("[sPP]"), m_sPP);
	RFX_Int(pFX, _T("[sDamage]"), m_sDamage);
	RFX_Int(pFX, _T("[sDefense]"), m_sDefense);
	RFX_Int(pFX, _T("[sWeight]"), m_sWeight);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CUserLevelUpSet diagnostics

#ifdef _DEBUG
void CUserLevelUpSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CUserLevelUpSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
