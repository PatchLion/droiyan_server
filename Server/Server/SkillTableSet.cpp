// SkillTableSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "SkillTableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkillTableSet

IMPLEMENT_DYNAMIC(CSkillTableSet, CRecordset)

CSkillTableSet::CSkillTableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSkillTableSet)
	m_sPid = 0;
	m_sSid = 0;
	m_tClass = 0;
	m_tInc = 0;
	m_tLevel = 0;
	m_tRepair = 0;
	m_tSuccess = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSkillTableSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CSkillTableSet::GetDefaultSQL()
{
	return _T("[dbo].[SKILL]");
}

void CSkillTableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSkillTableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sPid]"), m_sPid);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Byte(pFX, _T("[tClass]"), m_tClass);
	RFX_Byte(pFX, _T("[tInc]"), m_tInc);
	RFX_Byte(pFX, _T("[tLevel]"), m_tLevel);
	RFX_Byte(pFX, _T("[tRepair]"), m_tRepair);
	RFX_Byte(pFX, _T("[tSuccess]"), m_tSuccess);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSkillTableSet diagnostics

#ifdef _DEBUG
void CSkillTableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSkillTableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
