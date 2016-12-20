// NpcSayEventSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "NpcSayEventSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNpcSayEventSet

IMPLEMENT_DYNAMIC(CNpcSayEventSet, CRecordset)

CNpcSayEventSet::CNpcSayEventSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CNpcSayEventSet)
	m_sSid = 0;
	m_strNpcSay = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CNpcSayEventSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CNpcSayEventSet::GetDefaultSQL()
{
	return _T("[dbo].[NPC_SAY_EVENT]");
}

void CNpcSayEventSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CNpcSayEventSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Text(pFX, _T("[strNpcSay]"), m_strNpcSay);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CNpcSayEventSet diagnostics

#ifdef _DEBUG
void CNpcSayEventSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CNpcSayEventSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
