// BadIDSet.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "BadIDSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBadIDSet

IMPLEMENT_DYNAMIC(CBadIDSet, CRecordset)

CBadIDSet::CBadIDSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CBadIDSet)
	m_strComment = _T("");
	m_strOper = _T("");
	m_strPasswd = _T("");
	m_strUserID = _T("");
	m_tType = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CBadIDSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=SOMA");
	return _T("ODBC;DSN=Droiyan;UID=Droiyan;PWD=Droiyan");
}

CString CBadIDSet::GetDefaultSQL()
{
	return _T("[dbo].[BADID]");
}

void CBadIDSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CBadIDSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[strComment]"), m_strComment);
	RFX_Text(pFX, _T("[strOper]"), m_strOper);
	RFX_Text(pFX, _T("[strPasswd]"), m_strPasswd);
	RFX_Text(pFX, _T("[strUserID]"), m_strUserID);
	RFX_Date(pFX, _T("[timeReg]"), m_timeReg);
	RFX_Date(pFX, _T("[timeReturn]"), m_timeReturn);
	RFX_Byte(pFX, _T("[tType]"), m_tType);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CBadIDSet diagnostics

#ifdef _DEBUG
void CBadIDSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBadIDSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
