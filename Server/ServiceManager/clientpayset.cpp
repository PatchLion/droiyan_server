// ClientPaySet.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ClientPaySet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientPaySet

IMPLEMENT_DYNAMIC(CClientPaySet, CRecordset)

CClientPaySet::CClientPaySet( CDatabase* pdb, long Month_Filter, int Client_Filter)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CClientPaySet)
	m_wClientID = 0;
	m_nMonth = 0;
	m_nUseTime = 0;
	m_BANK_SERIAL_wSerial = 0;
	m_nBankID = 0;
	m_strSerialCode = _T("");
	m_CLIENT_PAY_wSerial = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
	m_nMonth_Filter = Month_Filter;
	m_nClient_Filter = Client_Filter;
}


CString CClientPaySet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=SOMA");
	return _T("ODBC;DSN=Droiyan;UID=Droiyan;PWD=Droiyan");
}

CString CClientPaySet::GetDefaultSQL()
{
	CString Filter;

	m_strFilter = _T("BANK_SERIAL.wSerial = CLIENT_PAY.wSerial ");
	if(m_nMonth_Filter)
	{
		Filter.Format( "AND CLIENT_PAY.nMonth = %ld", m_nMonth_Filter);
		m_strFilter += Filter;
	}

	if(m_nClient_Filter)
	{
		Filter.Format( "AND CLIENT_PAY.wClientID = %ld", m_nClient_Filter);
		m_strFilter += Filter;
	}

	return _T("[dbo].[CLIENT_PAY], [dbo].[BANK_SERIAL]");
}

void CClientPaySet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CClientPaySet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[wClientID]"), m_wClientID);
	RFX_Long(pFX, _T("[nMonth]"), m_nMonth);
	RFX_Long(pFX, _T("[nUseTime]"), m_nUseTime);
	RFX_Int(pFX, _T("[dbo].[BANK_SERIAL].[wSerial]"), m_BANK_SERIAL_wSerial);
	RFX_Long(pFX, _T("[nBankID]"), m_nBankID);
	RFX_Text(pFX, _T("[strSerialCode]"), m_strSerialCode);
	RFX_Int(pFX, _T("[dbo].[CLIENT_PAY].[wSerial]"), m_CLIENT_PAY_wSerial);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CClientPaySet diagnostics

#ifdef _DEBUG
void CClientPaySet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CClientPaySet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG