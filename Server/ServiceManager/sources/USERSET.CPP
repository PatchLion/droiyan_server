// UserSet.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "UserSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserSet

IMPLEMENT_DYNAMIC(CUserSet, CRecordset)

CUserSet::CUserSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CUserSet)
	m_bEmail = 1;
	m_bAdmin = 0;
	m_strAddr1 = _T("");
	m_strAddr2 = _T("");
	m_strEMail = _T("");
	m_strHandNo = _T("");
	m_strName = _T("");
	m_strPasswd = _T("");
	m_strPhoneNo = _T("");
	m_strPostalCode = _T("");
	m_strQuery1 = _T("");
	m_strQuery2 = _T("");
	m_strReply1 = _T("");
	m_strReply2 = _T("");
	m_strSocNo = _T("");
	m_strUserID = _T("");
	m_wSerial = 0;
	m_nFields = 18;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CUserSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=SOMA");
	return _T("ODBC;DSN=Droiyan;UID=Droiyan;PWD=Droiyan");
}

CString CUserSet::GetDefaultSQL()
{
	return _T("[dbo].[NGSCUSER]");
}

void CUserSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CUserSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[bEmail]"), m_bEmail);
	RFX_Int(pFX, _T("[bAdmin]"), m_bAdmin);
	RFX_Text(pFX, _T("[strAddr1]"), m_strAddr1);
	RFX_Text(pFX, _T("[strAddr2]"), m_strAddr2);
	RFX_Text(pFX, _T("[strEMail]"), m_strEMail);
	RFX_Text(pFX, _T("[strHandNo]"), m_strHandNo);
	RFX_Text(pFX, _T("[strName]"), m_strName);
	RFX_Text(pFX, _T("[strPasswd]"), m_strPasswd);
	RFX_Text(pFX, _T("[strPhoneNo]"), m_strPhoneNo);
	RFX_Text(pFX, _T("[strPostalCode]"), m_strPostalCode);
	RFX_Text(pFX, _T("[strQuery1]"), m_strQuery1);
	RFX_Text(pFX, _T("[strQuery2]"), m_strQuery2);
	RFX_Text(pFX, _T("[strReply1]"), m_strReply1);
	RFX_Text(pFX, _T("[strReply2]"), m_strReply2);
	RFX_Text(pFX, _T("[strSocNo]"), m_strSocNo);
	RFX_Text(pFX, _T("[strUserID]"), m_strUserID);
	RFX_Date(pFX, _T("[timeLog]"), m_timeLog);
	RFX_Date(pFX, _T("[timeReg]"), m_timeReg);
	RFX_Long(pFX, _T("[wSerial]"), m_wSerial);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CUserSet diagnostics

#ifdef _DEBUG
void CUserSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CUserSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
