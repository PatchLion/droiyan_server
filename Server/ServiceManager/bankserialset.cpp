// BankSerialSet.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "BankSerialSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBankSerialSet

IMPLEMENT_DYNAMIC(CBankSerialSet, CRecordset)

CBankSerialSet::CBankSerialSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CBankSerialSet)
	m_nBankID = 0;
	m_strSerialCode = _T("");
	m_wSerial = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CBankSerialSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=SOMA");
	return _T("ODBC;DSN=Droiyan;UID=Droiyan;PWD=Droiyan");
}

CString CBankSerialSet::GetDefaultSQL()
{
	return _T("[dbo].[BANK_SERIAL]");
}

void CBankSerialSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CBankSerialSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[nBankID]"), m_nBankID);
	RFX_Text(pFX, _T("[strSerialCode]"), m_strSerialCode);
	RFX_Int(pFX, _T("[wSerial]"), m_wSerial);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CBankSerialSet diagnostics

#ifdef _DEBUG
void CBankSerialSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBankSerialSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
