// EBodyIdentifyTableSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "EBodyIdentifyTableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEBodyIdentifyTableSet

IMPLEMENT_DYNAMIC(CEBodyIdentifyTableSet, CRecordset)

CEBodyIdentifyTableSet::CEBodyIdentifyTableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CEBodyIdentifyTableSet)
	m_sSid = 0;
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CEBodyIdentifyTableSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CEBodyIdentifyTableSet::GetDefaultSQL()
{
	return _T("[dbo].[EBODY_IDENTIFY]");
}

void CEBodyIdentifyTableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CEBodyIdentifyTableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEBodyIdentifyTableSet diagnostics

#ifdef _DEBUG
void CEBodyIdentifyTableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEBodyIdentifyTableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
