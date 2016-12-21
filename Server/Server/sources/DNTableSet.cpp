// DNTableSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "DNTableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDNTableSet

IMPLEMENT_DYNAMIC(CDNTableSet, CRecordset)

CDNTableSet::CDNTableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDNTableSet)
	m_sIndex = 0;
	m_sMinDn = 0;
	m_sMaxDn = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CDNTableSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CDNTableSet::GetDefaultSQL()
{
	return _T("[dbo].[DN]");
}

void CDNTableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDNTableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sIndex]"), m_sIndex);
	RFX_Int(pFX, _T("[sMinDn]"), m_sMinDn);
	RFX_Int(pFX, _T("[sMaxDn]"), m_sMaxDn);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDNTableSet diagnostics

#ifdef _DEBUG
void CDNTableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDNTableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
