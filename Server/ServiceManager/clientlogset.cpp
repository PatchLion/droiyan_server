// ClientLogSet.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ClientLogSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientLogSet

IMPLEMENT_DYNAMIC(CClientLogSet, CRecordset)

CClientLogSet::CClientLogSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CClientLogSet)
	m_nLogID = 0;
	m_strUserID = _T("");
	m_wSerial = 0;
	m_nUseTime = 0;
	m_strIPAddr = _T("");
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CClientLogSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=SOMA");
	return _T("ODBC;DSN=Droiyan;UID=Droiyan;PWD=Droiyan");
}

CString CClientLogSet::GetDefaultSQL()
{
	return _T("[dbo].[CLIENT_LOG]");
}

void CClientLogSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CClientLogSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[nLogID]"), m_nLogID);
	RFX_Text(pFX, _T("[strUserID]"), m_strUserID);
	RFX_Int(pFX, _T("[wSerial]"), m_wSerial);
	RFX_Date(pFX, _T("[timeLogin]"), m_timeLogin);
	RFX_Long(pFX, _T("[nUseTime]"), m_nUseTime);
	RFX_Text(pFX, _T("[strIPAddr]"), m_strIPAddr);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CClientLogSet diagnostics

#ifdef _DEBUG
void CClientLogSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CClientLogSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
