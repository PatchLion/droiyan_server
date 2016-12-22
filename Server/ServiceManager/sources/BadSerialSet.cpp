// BadSerialSet.cpp : implementation file
//

#include "stdafx.h"
#include "servicemanager.h"
#include "BadSerialSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBadSerialSet

IMPLEMENT_DYNAMIC(CBadSerialSet, CRecordset)

CBadSerialSet::CBadSerialSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CBadSerialSet)
	m_wSerial = 0;
	m_strOper = _T("");
	m_strReasion = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CBadSerialSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=SOMA");
	return _T("ODBC;DSN=Droiyan;UID=Droiyan;PWD=Droiyan");
}

CString CBadSerialSet::GetDefaultSQL()
{
	return _T("[dbo].[BADSERIAL]");
}

void CBadSerialSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CBadSerialSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[wSerial]"), m_wSerial);
	RFX_Date(pFX, _T("[dateStop]"), m_dateStop);
	RFX_Text(pFX, _T("[strOper]"), m_strOper);
	RFX_Text(pFX, _T("[strReasion]"), m_strReasion);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CBadSerialSet diagnostics

#ifdef _DEBUG
void CBadSerialSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBadSerialSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
