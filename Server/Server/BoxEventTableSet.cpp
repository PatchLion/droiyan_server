// BoxEventTableSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "BoxEventTableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoxEventTableSet

IMPLEMENT_DYNAMIC(CBoxEventTableSet, CRecordset)

CBoxEventTableSet::CBoxEventTableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CBoxEventTableSet)
	m_sSid = 0;
	m_tType = 0;
	m_sIid = 0;
	m_sCount = 0;
	m_strText = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CBoxEventTableSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CBoxEventTableSet::GetDefaultSQL()
{
	return _T("[dbo].[BOX_EVENT]");
}

void CBoxEventTableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CBoxEventTableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Byte(pFX, _T("[tType]"), m_tType);
	RFX_Int(pFX, _T("[sIid]"), m_sIid);
	RFX_Int(pFX, _T("[sCount]"), m_sCount);
	RFX_Text(pFX, _T("[strText]"), m_strText);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CBoxEventTableSet diagnostics

#ifdef _DEBUG
void CBoxEventTableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBoxEventTableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
