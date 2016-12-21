// TownPotalTableSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "TownPotalTableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTownPotalTableSet

IMPLEMENT_DYNAMIC(CTownPotalTableSet, CRecordset)

CTownPotalTableSet::CTownPotalTableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTownPotalTableSet)
	m_sPotalZone = 0;
	m_sPotalX1 = 0;
	m_sPotalY1 = 0;
	m_sPotalX2 = 0;
	m_sPotalY2 = 0;
	m_sPotalX3 = 0;
	m_sPotalY3 = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CTownPotalTableSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CTownPotalTableSet::GetDefaultSQL()
{
	return _T("[dbo].[TOWN_POTAL]");
}

void CTownPotalTableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTownPotalTableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sPotalZone]"), m_sPotalZone);
	RFX_Int(pFX, _T("[sPotalX1]"), m_sPotalX1);
	RFX_Int(pFX, _T("[sPotalY1]"), m_sPotalY1);
	RFX_Int(pFX, _T("[sPotalX2]"), m_sPotalX2);
	RFX_Int(pFX, _T("[sPotalY2]"), m_sPotalY2);
	RFX_Int(pFX, _T("[sPotalX3]"), m_sPotalX3);
	RFX_Int(pFX, _T("[sPotalY3]"), m_sPotalY3);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTownPotalTableSet diagnostics

#ifdef _DEBUG
void CTownPotalTableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CTownPotalTableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
