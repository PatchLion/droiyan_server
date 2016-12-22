// BankSet.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "BankSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBankSet

IMPLEMENT_DYNAMIC(CBankSet, CRecordset)

CBankSet::CBankSet( CDatabase* pdb, int wClientID)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CBankSet)
	m_nID = 0;
	m_strName = _T("");
	m_strBank = _T("");
	m_nMoney = 0;
	m_strOper = _T("");
	m_strComment = _T("");
	m_bProcess = 0;
	m_bType = 0;
	m_strSocNo = _T("");
	m_strTelNo = _T("");
	m_wClientID = 0;
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
	m_wClientIDFilter = wClientID;
}


CString CBankSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=SOMA");
	return _T("ODBC;DSN=Droiyan;UID=Droiyan;PWD=Droiyan");
}

CString CBankSet::GetDefaultSQL()
{
	if(m_wClientIDFilter) m_strFilter.Format( "BANK.wClientID = %ld", m_wClientIDFilter);
	return _T("[dbo].[BANK]");
}

void CBankSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CBankSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[nID]"), m_nID);
	RFX_Date(pFX, _T("[timeReg]"), m_timeReg);
	RFX_Text(pFX, _T("[strName]"), m_strName);
	RFX_Text(pFX, _T("[strBank]"), m_strBank);
	RFX_Long(pFX, _T("[nMoney]"), m_nMoney);
	RFX_Text(pFX, _T("[strOper]"), m_strOper);
	RFX_Text(pFX, _T("[strComment]"), m_strComment);
	RFX_Byte(pFX, _T("[bProcess]"), m_bProcess);
	RFX_Byte(pFX, _T("[bType]"), m_bType);
	RFX_Text(pFX, _T("[strSocNo]"), m_strSocNo);
	RFX_Text(pFX, _T("[strTelNo]"), m_strTelNo);
	RFX_Int(pFX, _T("[wClientID]"), m_wClientID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CBankSet diagnostics

#ifdef _DEBUG
void CBankSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBankSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
