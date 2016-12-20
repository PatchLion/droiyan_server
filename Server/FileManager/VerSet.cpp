// VerSet.cpp : implementation file
//

#include "stdafx.h"
#include "FileManager.h"
#include "VerSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVerSet

IMPLEMENT_DYNAMIC(CVerSet, CRecordset)

CVerSet::CVerSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CVerSet)
	m_strFileName = _T("");
	m_strCompName = _T("");
	m_wVersion = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CVerSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=HERO");
	return _T("ODBC;DSN=Droiyan;UID=Droiyan;PWD=Droiyan");
}

CString CVerSet::GetDefaultSQL()
{
	return _T("[dbo].[VERSION]");
}

void CVerSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CVerSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[strFileName]"), m_strFileName);
	RFX_Text(pFX, _T("[strCompName]"), m_strCompName);
	RFX_Int(pFX, _T("[wVersion]"), m_wVersion);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CVerSet diagnostics

#ifdef _DEBUG
void CVerSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CVerSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
