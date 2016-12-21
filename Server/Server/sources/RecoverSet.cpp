// RecoverSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "RecoverSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecoverSet

IMPLEMENT_DYNAMIC(CRecoverSet, CRecordset)

CRecoverSet::CRecoverSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRecoverSet)
	m_sSid = 0;
	m_byHPDivide = 0;
	m_bySPDivide = 0;
	m_byPPDivide = 0;
	m_byTown = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CRecoverSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CRecoverSet::GetDefaultSQL()
{
	return _T("[dbo].[USER_RECOVER]");
}

void CRecoverSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRecoverSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Byte(pFX, _T("[byHPDivide]"), m_byHPDivide);
	RFX_Byte(pFX, _T("[bySPDivide]"), m_bySPDivide);
	RFX_Byte(pFX, _T("[byPPDivide]"), m_byPPDivide);
	RFX_Byte(pFX, _T("[byTown]"), m_byTown);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRecoverSet diagnostics

#ifdef _DEBUG
void CRecoverSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecoverSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
