// DressingSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "DressingSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDressingSet

IMPLEMENT_DYNAMIC(CDressingSet, CRecordset)

CDressingSet::CDressingSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDressingSet)
	m_sSid = 0;
	m_sItemNum = 0;
	m_sCountMin = 0;
	m_sCountMax = 0;
	m_sItem01 = 0;
	m_sItemRatio01 = 0;
	m_sItem02 = 0;
	m_sItemRatio02 = 0;
	m_sItem03 = 0;
	m_sItemRatio03 = 0;
	m_sItem04 = 0;
	m_sItemRatio04 = 0;
	m_sItem05 = 0;
	m_sItemRatio05 = 0;
	m_sItem06 = 0;
	m_sItemRatio06 = 0;
	m_sItem07 = 0;
	m_sItemRatio07 = 0;
	m_sItem08 = 0;
	m_sItemRatio08 = 0;
	m_sItem09 = 0;
	m_sItemRatio09 = 0;
	m_sItem10 = 0;
	m_sItemRatio10 = 0;
	m_nFields = 24;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CDressingSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CDressingSet::GetDefaultSQL()
{
	return _T("[dbo].[DRESSING]");
}

void CDressingSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDressingSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Int(pFX, _T("[sItemNum]"), m_sItemNum);
	RFX_Int(pFX, _T("[sCountMin]"), m_sCountMin);
	RFX_Int(pFX, _T("[sCountMax]"), m_sCountMax);
	RFX_Int(pFX, _T("[sItem01]"), m_sItem01);
	RFX_Int(pFX, _T("[sItemRatio01]"), m_sItemRatio01);
	RFX_Int(pFX, _T("[sItem02]"), m_sItem02);
	RFX_Int(pFX, _T("[sItemRatio02]"), m_sItemRatio02);
	RFX_Int(pFX, _T("[sItem03]"), m_sItem03);
	RFX_Int(pFX, _T("[sItemRatio03]"), m_sItemRatio03);
	RFX_Int(pFX, _T("[sItem04]"), m_sItem04);
	RFX_Int(pFX, _T("[sItemRatio04]"), m_sItemRatio04);
	RFX_Int(pFX, _T("[sItem05]"), m_sItem05);
	RFX_Int(pFX, _T("[sItemRatio05]"), m_sItemRatio05);
	RFX_Int(pFX, _T("[sItem06]"), m_sItem06);
	RFX_Int(pFX, _T("[sItemRatio06]"), m_sItemRatio06);
	RFX_Int(pFX, _T("[sItem07]"), m_sItem07);
	RFX_Int(pFX, _T("[sItemRatio07]"), m_sItemRatio07);
	RFX_Int(pFX, _T("[sItem08]"), m_sItem08);
	RFX_Int(pFX, _T("[sItemRatio08]"), m_sItemRatio08);
	RFX_Int(pFX, _T("[sItem09]"), m_sItem09);
	RFX_Int(pFX, _T("[sItemRatio09]"), m_sItemRatio09);
	RFX_Int(pFX, _T("[sItem10]"), m_sItem10);
	RFX_Int(pFX, _T("[sItemRatio10]"), m_sItemRatio10);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDressingSet diagnostics

#ifdef _DEBUG
void CDressingSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDressingSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
