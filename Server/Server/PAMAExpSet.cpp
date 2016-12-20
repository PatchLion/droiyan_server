// PAMAExpSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "PAMAExpSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPAMAExpSet

IMPLEMENT_DYNAMIC(CPAMAExpSet, CRecordset)

CPAMAExpSet::CPAMAExpSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CPAMAExpSet)
	m_iPAMAExp = 0;
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CPAMAExpSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CPAMAExpSet::GetDefaultSQL()
{
	return _T("[dbo].[PAMAExp]");
}

void CPAMAExpSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPAMAExpSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[iPAMAExp]"), m_iPAMAExp);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CPAMAExpSet diagnostics

#ifdef _DEBUG
void CPAMAExpSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CPAMAExpSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
