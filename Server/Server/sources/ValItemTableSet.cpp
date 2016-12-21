// ValItemTableSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "ValItemTableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CValItemTableSet

IMPLEMENT_DYNAMIC(CValItemTableSet, CRecordset)

CValItemTableSet::CValItemTableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CValItemTableSet)
	m_sSid = 0;
	m_sValItem01 = 0;
	m_tPersentVal01 = 0;
	m_sValItem02 = 0;
	m_tPersentVal02 = 0;
	m_sValItem03 = 0;
	m_tPersentVal03 = 0;
	m_sValItem04 = 0;
	m_tPersentVal04 = 0;
	m_sValItem05 = 0;
	m_tPersentVal05 = 0;
	m_sValItem06 = 0;
	m_tPersentVal06 = 0;
	m_nFields = 13;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CValItemTableSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CValItemTableSet::GetDefaultSQL()
{
	return _T("[dbo].[VAL_ITEM]");
}

void CValItemTableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CValItemTableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Int(pFX, _T("[sValItem01]"), m_sValItem01);
	RFX_Byte(pFX, _T("[tPersentVal01]"), m_tPersentVal01);
	RFX_Int(pFX, _T("[sValItem02]"), m_sValItem02);
	RFX_Byte(pFX, _T("[tPersentVal02]"), m_tPersentVal02);
	RFX_Int(pFX, _T("[sValItem03]"), m_sValItem03);
	RFX_Byte(pFX, _T("[tPersentVal03]"), m_tPersentVal03);
	RFX_Int(pFX, _T("[sValItem04]"), m_sValItem04);
	RFX_Byte(pFX, _T("[tPersentVal04]"), m_tPersentVal04);
	RFX_Int(pFX, _T("[sValItem05]"), m_sValItem05);
	RFX_Byte(pFX, _T("[tPersentVal05]"), m_tPersentVal05);
	RFX_Int(pFX, _T("[sValItem06]"), m_sValItem06);
	RFX_Byte(pFX, _T("[tPersentVal06]"), m_tPersentVal06);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CValItemTableSet diagnostics

#ifdef _DEBUG
void CValItemTableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CValItemTableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
