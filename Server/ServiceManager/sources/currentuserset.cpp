// CurrentUserSet.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "CurrentUserSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurrentUserSet

IMPLEMENT_DYNAMIC(CCurrentUserSet, CRecordset)

CCurrentUserSet::CCurrentUserSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CCurrentUserSet)
	m_bUseSecond = 0;
	m_nAccountID = 0;
	m_nAcctType = 0;
	m_nCPAccountID = 0;
	m_nCPAcctType = 0;
	m_nCPID = 0;
	m_nDisplay = 0;
	m_nServiceID = 0;
	m_nValidTime = 0;
	m_strBizNo = _T("");
	m_strClientID = _T("");
	m_strIPAddr = _T("");
	m_strServerIPAddr = _T("");
	m_nFields = 16;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CCurrentUserSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=SOMA");
	return _T("ODBC;DSN=Droiyan;UID=Droiyan;PWD=Droiyan");
}

CString CCurrentUserSet::GetDefaultSQL()
{
	return _T("[dbo].[CURRENTUSER]");
}

void CCurrentUserSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCurrentUserSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Byte(pFX, _T("[bUseSecond]"), m_bUseSecond);
	RFX_Long(pFX, _T("[nAccountID]"), m_nAccountID);
	RFX_Byte(pFX, _T("[nAcctType]"), m_nAcctType);
	RFX_Long(pFX, _T("[nCPAccountID]"), m_nCPAccountID);
	RFX_Byte(pFX, _T("[nCPAcctType]"), m_nCPAcctType);
	RFX_Long(pFX, _T("[nCPID]"), m_nCPID);
	RFX_Byte(pFX, _T("[nDisplay]"), m_nDisplay);
	RFX_Int(pFX, _T("[nServiceID]"), m_nServiceID);
	RFX_Date(pFX, _T("[nValidDay]"), m_nValidDay);
	RFX_Long(pFX, _T("[nValidTime]"), m_nValidTime);
	RFX_Text(pFX, _T("[strBizNo]"), m_strBizNo);
	RFX_Text(pFX, _T("[strClientID]"), m_strClientID);
	RFX_Text(pFX, _T("[strIPAddr]"), m_strIPAddr);
	RFX_Text(pFX, _T("[strServerIPAddr]"), m_strServerIPAddr);
	RFX_Date(pFX, _T("[timeCPLogin]"), m_timeCPLogin);
	RFX_Date(pFX, _T("[timeLogin]"), m_timeLogin);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCurrentUserSet diagnostics

#ifdef _DEBUG
void CCurrentUserSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCurrentUserSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
