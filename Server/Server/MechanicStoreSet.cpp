// MechanicStoreSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "MechanicStoreSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMechanicStoreSet

IMPLEMENT_DYNAMIC(CMechanicStoreSet, CRecordset)

CMechanicStoreSet::CMechanicStoreSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CMechanicStoreSet)
	m_sStoreID = 0;
	m_sSid = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CMechanicStoreSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CMechanicStoreSet::GetDefaultSQL()
{
	return _T("[dbo].[MECHANIC_STORE]");
}

void CMechanicStoreSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CMechanicStoreSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sStoreID]"), m_sStoreID);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CMechanicStoreSet diagnostics

#ifdef _DEBUG
void CMechanicStoreSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CMechanicStoreSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
