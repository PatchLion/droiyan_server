// RemodelingTableSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "RemodelingTableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRemodelingTableSet

IMPLEMENT_DYNAMIC(CRemodelingTableSet, CRecordset)

CRemodelingTableSet::CRemodelingTableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRemodelingTableSet)
	m_sRid = 0;
	m_sSid = 0;
	m_tWearInfo = 0;
	m_tNeedClass = 0;
	m_sPlan = 0;
	m_tRandom1 = 0;
	m_tRandom2 = 0;
	m_tReplace = 0;
	m_strText = _T("");
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CRemodelingTableSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CRemodelingTableSet::GetDefaultSQL()
{
	return _T("[dbo].[REMODELING_01]");
}

void CRemodelingTableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRemodelingTableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sRid]"), m_sRid);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Byte(pFX, _T("[tWearInfo]"), m_tWearInfo);
	RFX_Byte(pFX, _T("[tNeedClass]"), m_tNeedClass);
	RFX_Int(pFX, _T("[sPlan]"), m_sPlan);
	RFX_Byte(pFX, _T("[tRandom1]"), m_tRandom1);
	RFX_Byte(pFX, _T("[tRandom2]"), m_tRandom2);
	RFX_Byte(pFX, _T("[tReplace]"), m_tReplace);
	RFX_Text(pFX, _T("[strText]"), m_strText);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRemodelingTableSet diagnostics

#ifdef _DEBUG
void CRemodelingTableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRemodelingTableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
