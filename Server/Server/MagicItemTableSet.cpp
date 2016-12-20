// MagicItemTableSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "MagicItemTableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMagicItemTableSet

IMPLEMENT_DYNAMIC(CMagicItemTableSet, CRecordset)

CMagicItemTableSet::CMagicItemTableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CMagicItemTableSet)
	m_sChangeValue = 0;
	m_sSid = 0;
	m_sSubType = 0;
	m_strText = _T("");
	m_tLevel = 0;
	m_tNeedClass = 0;
	m_tUpgrade = 0;
	m_tUse = 0;
	m_tWearInfo = 0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CMagicItemTableSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CMagicItemTableSet::GetDefaultSQL()
{
	return _T("[dbo].[MAGIC_ITEM]");
}

void CMagicItemTableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CMagicItemTableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sChangeValue]"), m_sChangeValue);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Int(pFX, _T("[sSubType]"), m_sSubType);
	RFX_Text(pFX, _T("[strText]"), m_strText);
	RFX_Byte(pFX, _T("[tLevel]"), m_tLevel);
	RFX_Byte(pFX, _T("[tNeedClass]"), m_tNeedClass);
	RFX_Byte(pFX, _T("[tUpgrade]"), m_tUpgrade);
	RFX_Byte(pFX, _T("[tUse]"), m_tUse);
	RFX_Byte(pFX, _T("[tWearInfo]"), m_tWearInfo);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CMagicItemTableSet diagnostics

#ifdef _DEBUG
void CMagicItemTableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CMagicItemTableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
