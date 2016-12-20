// SETItemCountSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "SETItemCountSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSETItemCountSet

IMPLEMENT_DYNAMIC(CSETItemCountSet, CRecordset)

CSETItemCountSet::CSETItemCountSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSETItemCountSet)
	m_sSid = 0;
	m_sItemIndex = 0;
	m_iServerMax = 0;
	m_iServerNow = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSETItemCountSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame");
}

CString CSETItemCountSet::GetDefaultSQL()
{
	return _T("[dbo].[SET_ITEM_COUNT]");
}

void CSETItemCountSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSETItemCountSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Int(pFX, _T("[sItemIndex]"), m_sItemIndex);
	RFX_Long(pFX, _T("[iServerMax]"), m_iServerMax);
	RFX_Long(pFX, _T("[iServerNow]"), m_iServerNow);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSETItemCountSet diagnostics

#ifdef _DEBUG
void CSETItemCountSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSETItemCountSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
