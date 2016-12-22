// LogSet.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "LogSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogSet

IMPLEMENT_DYNAMIC(CLogSet, CRecordset)

CLogSet::CLogSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CLogSet)
	m_nLogID = 0;
	m_nServiceID = 0;
	m_strUserID = _T("");
	m_wSerial = 0;
	m_nUseTime = 0;
	m_bReason = 0;
	m_strIPAddr = _T("");
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CLogSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=SOMA");
	return _T("ODBC;DSN=Droiyan;UID=Droiyan;PWD=Droiyan");
}

CString CLogSet::GetDefaultSQL()
{
	return _T("[dbo].[LOG]");
}

void CLogSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CLogSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[nLogID]"), m_nLogID);
	RFX_Long(pFX, _T("[nServiceID]"), m_nServiceID);
	RFX_Text(pFX, _T("[strUserID]"), m_strUserID);
	RFX_Int(pFX, _T("[wSerial]"), m_wSerial);
	RFX_Date(pFX, _T("[timeLogin]"), m_timeLogin);
	RFX_Long(pFX, _T("[nUseTime]"), m_nUseTime);
	RFX_Byte(pFX, _T("[bReason]"), m_bReason);
	RFX_Text(pFX, _T("[strIPAddr]"), m_strIPAddr);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CLogSet diagnostics

#ifdef _DEBUG
void CLogSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CLogSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
