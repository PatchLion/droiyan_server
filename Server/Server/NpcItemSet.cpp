// NpcItemSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "NpcItemSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNpcItemSet

IMPLEMENT_DYNAMIC(CNpcItemSet, CRecordset)

CNpcItemSet::CNpcItemSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CNpcItemSet)
	m_sIndex = 0;
	m_sItem01 = 0;
	m_sItem02 = 0;
	m_sItem03 = 0;
	m_sItem04 = 0;
	m_sItem05 = 0;
	m_sItem06 = 0;
	m_sItem07 = 0;
	m_sItem08 = 0;
	m_sItem09 = 0;
	m_sItem10 = 0;
	m_sItem11 = 0;
	m_sItem12 = 0;
	m_sItem13 = 0;
	m_sItem14 = 0;
	m_sItem15 = 0;
	m_sItem16 = 0;
	m_sItem17 = 0;
	m_sItem18 = 0;
	m_sItem19 = 0;
	m_sItem20 = 0;
	m_sPersent01 = 0;
	m_sPersent02 = 0;
	m_sPersent03 = 0;
	m_sPersent04 = 0;
	m_sPersent05 = 0;
	m_sPersent06 = 0;
	m_sPersent07 = 0;
	m_sPersent08 = 0;
	m_sPersent09 = 0;
	m_sPersent10 = 0;
	m_sPersent11 = 0;
	m_sPersent12 = 0;
	m_sPersent13 = 0;
	m_sPersent14 = 0;
	m_sPersent15 = 0;
	m_sPersent16 = 0;
	m_sPersent17 = 0;
	m_sPersent18 = 0;
	m_sPersent19 = 0;
	m_sPersent20 = 0;
	m_nFields = 41;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CNpcItemSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CNpcItemSet::GetDefaultSQL()
{
	return _T("[dbo].[MONSTER_ITEM]");
}

void CNpcItemSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CNpcItemSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sIndex]"), m_sIndex);
	RFX_Int(pFX, _T("[sItem01]"), m_sItem01);
	RFX_Int(pFX, _T("[sPersent01]"), m_sPersent01);
	RFX_Int(pFX, _T("[sItem02]"), m_sItem02);
	RFX_Int(pFX, _T("[sPersent02]"), m_sPersent02);
	RFX_Int(pFX, _T("[sItem03]"), m_sItem03);
	RFX_Int(pFX, _T("[sPersent03]"), m_sPersent03);
	RFX_Int(pFX, _T("[sItem04]"), m_sItem04);
	RFX_Int(pFX, _T("[sPersent04]"), m_sPersent04);
	RFX_Int(pFX, _T("[sItem05]"), m_sItem05);
	RFX_Int(pFX, _T("[sPersent05]"), m_sPersent05);
	RFX_Int(pFX, _T("[sItem06]"), m_sItem06);
	RFX_Int(pFX, _T("[sPersent06]"), m_sPersent06);
	RFX_Int(pFX, _T("[sItem07]"), m_sItem07);
	RFX_Int(pFX, _T("[sPersent07]"), m_sPersent07);
	RFX_Int(pFX, _T("[sItem08]"), m_sItem08);
	RFX_Int(pFX, _T("[sPersent08]"), m_sPersent08);
	RFX_Int(pFX, _T("[sItem09]"), m_sItem09);
	RFX_Int(pFX, _T("[sPersent09]"), m_sPersent09);
	RFX_Int(pFX, _T("[sItem10]"), m_sItem10);
	RFX_Int(pFX, _T("[sPersent10]"), m_sPersent10);
	RFX_Int(pFX, _T("[sItem11]"), m_sItem11);
	RFX_Int(pFX, _T("[sPersent11]"), m_sPersent11);
	RFX_Int(pFX, _T("[sItem12]"), m_sItem12);
	RFX_Int(pFX, _T("[sPersent12]"), m_sPersent12);
	RFX_Int(pFX, _T("[sItem13]"), m_sItem13);
	RFX_Int(pFX, _T("[sPersent13]"), m_sPersent13);
	RFX_Int(pFX, _T("[sItem14]"), m_sItem14);
	RFX_Int(pFX, _T("[sPersent14]"), m_sPersent14);
	RFX_Int(pFX, _T("[sItem15]"), m_sItem15);
	RFX_Int(pFX, _T("[sPersent15]"), m_sPersent15);
	RFX_Int(pFX, _T("[sItem16]"), m_sItem16);
	RFX_Int(pFX, _T("[sPersent16]"), m_sPersent16);
	RFX_Int(pFX, _T("[sItem17]"), m_sItem17);
	RFX_Int(pFX, _T("[sPersent17]"), m_sPersent17);
	RFX_Int(pFX, _T("[sItem18]"), m_sItem18);
	RFX_Int(pFX, _T("[sPersent18]"), m_sPersent18);
	RFX_Int(pFX, _T("[sItem19]"), m_sItem19);
	RFX_Int(pFX, _T("[sPersent19]"), m_sPersent19);
	RFX_Int(pFX, _T("[sItem20]"), m_sItem20);
	RFX_Int(pFX, _T("[sPersent20]"), m_sPersent20);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CNpcItemSet diagnostics

#ifdef _DEBUG
void CNpcItemSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CNpcItemSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
