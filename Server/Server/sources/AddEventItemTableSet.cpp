// AddEventItemTableSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "AddEventItemTableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddEventItemTableSet

IMPLEMENT_DYNAMIC(CAddEventItemTableSet, CRecordset)

CAddEventItemTableSet::CAddEventItemTableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAddEventItemTableSet)
	m_sSid = 0;
	m_tType = 0;
	m_tGiveFlag = 0;
	m_tEnd = 0;
	m_tUsed = 0;
	m_strSerialNum = _T("");
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CAddEventItemTableSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgamenew;UID=drgame;PWD=drgame");
}

CString CAddEventItemTableSet::GetDefaultSQL()
{
	return _T("[dbo].[EVENT_TABLE_ADD1]");
}

void CAddEventItemTableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAddEventItemTableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Byte(pFX, _T("[tType]"), m_tType);
	RFX_Byte(pFX, _T("[tGiveFlag]"), m_tGiveFlag);
	RFX_Byte(pFX, _T("[tEnd]"), m_tEnd);
	RFX_Byte(pFX, _T("[tUsed]"), m_tUsed);
	RFX_Text(pFX, _T("[strSerialNum]"), m_strSerialNum);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAddEventItemTableSet diagnostics

#ifdef _DEBUG
void CAddEventItemTableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CAddEventItemTableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
