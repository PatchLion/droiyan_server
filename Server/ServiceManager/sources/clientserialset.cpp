// ClientSerialSet.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ClientSerialSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSerialSet

IMPLEMENT_DYNAMIC(CClientSerialSet, CRecordset)

CClientSerialSet::CClientSerialSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CClientSerialSet)
	m_wSerial = 0;
	m_wClientID = 0;
	m_nLastLogID = 0;
	m_bProcess = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CClientSerialSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=SOMA");
	return _T("ODBC;DSN=Droiyan;UID=Droiyan;PWD=Droiyan");
}

CString CClientSerialSet::GetDefaultSQL()
{
	return _T("[dbo].[CLIENT_SERIAL]");
}

void CClientSerialSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CClientSerialSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[wSerial]"), m_wSerial);
	RFX_Int(pFX, _T("[wClientID]"), m_wClientID);
	RFX_Long(pFX, _T("[nLastLogID]"), m_nLastLogID);
	RFX_Byte(pFX, _T("[bProcess]"), m_bProcess);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CClientSerialSet diagnostics

#ifdef _DEBUG
void CClientSerialSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CClientSerialSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
