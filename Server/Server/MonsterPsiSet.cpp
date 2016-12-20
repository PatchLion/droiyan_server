// MonsterPsiSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "MonsterPsiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonsterPsiSet

IMPLEMENT_DYNAMIC(CMonsterPsiSet, CRecordset)

CMonsterPsiSet::CMonsterPsiSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CMonsterPsiSet)
	m_byRange = 0;
	m_sCasting = 0;
	m_sMaxDmg = 0;
	m_sMinDmg = 0;
	m_sPid = 0;
	m_sSid = 0;
	m_strName = _T("");
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CMonsterPsiSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CMonsterPsiSet::GetDefaultSQL()
{
	return _T("[dbo].[MONSTER_PSI]");
}

void CMonsterPsiSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CMonsterPsiSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Byte(pFX, _T("[byRange]"), m_byRange);
	RFX_Int(pFX, _T("[sCasting]"), m_sCasting);
	RFX_Int(pFX, _T("[sMaxDmg]"), m_sMaxDmg);
	RFX_Int(pFX, _T("[sMinDmg]"), m_sMinDmg);
	RFX_Int(pFX, _T("[sPid]"), m_sPid);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Text(pFX, _T("[strName]"), m_strName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CMonsterPsiSet diagnostics

#ifdef _DEBUG
void CMonsterPsiSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CMonsterPsiSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
