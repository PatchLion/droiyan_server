// RecoverRateSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "RecoverRateSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecoverRateSet

IMPLEMENT_DYNAMIC(CRecoverRateSet, CRecordset)

CRecoverRateSet::CRecoverRateSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRecoverRateSet)
	m_sSid = 0;
	m_sHpSpeedupTime = 0;
	m_byHpSpeedupLevel = 0;
	m_sSpSpeedupTime = 0;
	m_bySpSpeedupLevel = 0;
	m_sPpSpeedupTime = 0;
	m_byPpSpeedupLevel = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CRecoverRateSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CRecoverRateSet::GetDefaultSQL()
{
	return _T("[dbo].[USER_RECOVER_RATE]");
}

void CRecoverRateSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRecoverRateSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Int(pFX, _T("[sHpSpeedupTime]"), m_sHpSpeedupTime);
	RFX_Byte(pFX, _T("[byHpSpeedupLevel]"), m_byHpSpeedupLevel);
	RFX_Int(pFX, _T("[sSpSpeedupTime]"), m_sSpSpeedupTime);
	RFX_Byte(pFX, _T("[bySpSpeedupLevel]"), m_bySpSpeedupLevel);
	RFX_Int(pFX, _T("[sPpSpeedupTime]"), m_sPpSpeedupTime);
	RFX_Byte(pFX, _T("[byPpSpeedupLevel]"), m_byPpSpeedupLevel);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRecoverRateSet diagnostics

#ifdef _DEBUG
void CRecoverRateSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecoverRateSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
