// InitItemTableSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "InitItemTableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInitItemTableSet

IMPLEMENT_DYNAMIC(CInitItemTableSet, CRecordset)

CInitItemTableSet::CInitItemTableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CInitItemTableSet)
	m_tTypeClass = 0;
	m_sSid = 0;
	m_sSubSid = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CInitItemTableSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CInitItemTableSet::GetDefaultSQL()
{
	return _T("[dbo].[INIT_USER]");
}

void CInitItemTableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CInitItemTableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Byte(pFX, _T("[tTypeClass]"), m_tTypeClass);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Int(pFX, _T("[sSubSid]"), m_sSubSid);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CInitItemTableSet diagnostics

#ifdef _DEBUG
void CInitItemTableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CInitItemTableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
