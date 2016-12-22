// PatchVer.cpp : implementation file
//

#include "stdafx.h"
#include "servicemanager.h"
#include "PatchVer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPatchVer

IMPLEMENT_DYNAMIC(CPatchVer, CRecordset)

CPatchVer::CPatchVer(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CPatchVer)
	m_strFileName = _T("");
	m_sVersion = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CPatchVer::GetDefaultConnect()
{
	return _T("ODBC;DSN=Droiyan;UID=Droiyan;PWD=Droiyan");
}

CString CPatchVer::GetDefaultSQL()
{
	return _T("[dbo].[PATCH_VERSION]");
}

void CPatchVer::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPatchVer)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[strFileName]"), m_strFileName);
	RFX_Int(pFX, _T("[sVersion]"), m_sVersion);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CPatchVer diagnostics

#ifdef _DEBUG
void CPatchVer::AssertValid() const
{
	CRecordset::AssertValid();
}

void CPatchVer::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
