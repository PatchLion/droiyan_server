// ClientSet.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ClientSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSet

IMPLEMENT_DYNAMIC(CClientSet, CRecordset)

CClientSet::CClientSet( CDatabase* pdb, int Client_Filter)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CClientSet)
	m_nNumPC = 0;
	m_strAddress = _T("");
	m_strEMail = _T("");
	m_strHost = _T("");
	m_strKind = _T("");
	m_strName = _T("");
	m_strRegNo = _T("");
	m_strTelNo = _T("");
	m_strType = _T("");
	m_strUseLine = _T("");
	m_strZipCode = _T("");
	m_wID = 0;
	m_wLoc = 0;
	m_strIPAddress = _T("");
	m_strEtc = _T("");
	m_nFields = 16;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
	m_wClientFilter = Client_Filter;
}


CString CClientSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=SOMA");
	return _T("ODBC;DSN=Droiyan;UID=Droiyan;PWD=Droiyan");
}

CString CClientSet::GetDefaultSQL()
{
	if(m_wClientFilter) m_strFilter.Format( "CLIENT.wID = %ld", m_wClientFilter);
	return _T("[dbo].[CLIENT]");
}

void CClientSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CClientSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[wID]"), m_wID);
	RFX_Date(pFX, _T("[timeReg]"), m_timeReg);
	RFX_Text(pFX, _T("[strRegNo]"), m_strRegNo);
	RFX_Text(pFX, _T("[strName]"), m_strName);
	RFX_Text(pFX, _T("[strHost]"), m_strHost);
	RFX_Text(pFX, _T("[strAddress]"), m_strAddress);
	RFX_Text(pFX, _T("[strType]"), m_strType);
	RFX_Text(pFX, _T("[strKind]"), m_strKind);
	RFX_Text(pFX, _T("[strTelNo]"), m_strTelNo);
	RFX_Byte(pFX, _T("[wLoc]"), m_wLoc);
	RFX_Text(pFX, _T("[strZipCode]"), m_strZipCode);
	RFX_Text(pFX, _T("[strUseLine]"), m_strUseLine);
	RFX_Long(pFX, _T("[nNumPC]"), m_nNumPC);
	RFX_Text(pFX, _T("[strEMail]"), m_strEMail);
	RFX_Text(pFX, _T("[strIPAddress]"), m_strIPAddress);
	RFX_Text(pFX, _T("[strEtc]"), m_strEtc);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CClientSet diagnostics

#ifdef _DEBUG
void CClientSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CClientSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
