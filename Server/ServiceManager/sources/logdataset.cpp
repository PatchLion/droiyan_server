// LogDataSet.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "LogDataSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogDataSet

IMPLEMENT_DYNAMIC(CLogDataSet, CRecordset)

CLogDataSet::CLogDataSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CLogDataSet)
	m_nServiceID = 0;
	m_nCount = 0;
	m_nUseTime = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CLogDataSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=SOMA");
	return _T("ODBC;DSN=Droiyan;UID=Droiyan;PWD=Droiyan");
}

CString CLogDataSet::GetDefaultSQL()
{
	return _T("[dbo].[LOGDATA]");
}

void CLogDataSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CLogDataSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Date(pFX, _T("[timeDate]"), m_timeDate);
	RFX_Long(pFX, _T("[nServiceID]"), m_nServiceID);
	RFX_Long(pFX, _T("[nCount]"), m_nCount);
	RFX_Long(pFX, _T("[nUseTime]"), m_nUseTime);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CLogDataSet diagnostics

#ifdef _DEBUG
void CLogDataSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CLogDataSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
