// AccessoriUpTableSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "AccessoriUpTableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccessoriUpTableSet

IMPLEMENT_DYNAMIC(CAccessoriUpTableSet, CRecordset)

CAccessoriUpTableSet::CAccessoriUpTableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAccessoriUpTableSet)
	m_sAid = 0;
	m_sSid = 0;
	m_strText = _T("");
	m_tType = 0;
	m_tGroup = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CAccessoriUpTableSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CAccessoriUpTableSet::GetDefaultSQL()
{
	return _T("[dbo].[ACCESSORI_UP]");
}

void CAccessoriUpTableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAccessoriUpTableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sAid]"), m_sAid);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Text(pFX, _T("[strText]"), m_strText);
	RFX_Byte(pFX, _T("[tType]"), m_tType);
	RFX_Byte(pFX, _T("[tGroup]"), m_tGroup);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAccessoriUpTableSet diagnostics

#ifdef _DEBUG
void CAccessoriUpTableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CAccessoriUpTableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
