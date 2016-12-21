// ExceptionZoneSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "ExceptionZoneSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExceptionZoneSet

IMPLEMENT_DYNAMIC(CExceptionZoneSet, CRecordset)

CExceptionZoneSet::CExceptionZoneSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CExceptionZoneSet)
	m_sZone = 0;
	m_tFighterType = 0;
	m_tEventMopType = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CExceptionZoneSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame");
}

CString CExceptionZoneSet::GetDefaultSQL()
{
	return _T("[dbo].[ZONE_EXCEPTION]");
}

void CExceptionZoneSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CExceptionZoneSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sZone]"), m_sZone);
	RFX_Byte(pFX, _T("[tFighterType]"), m_tFighterType);
	RFX_Byte(pFX, _T("[tEventMopType]"), m_tEventMopType);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CExceptionZoneSet diagnostics

#ifdef _DEBUG
void CExceptionZoneSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CExceptionZoneSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
