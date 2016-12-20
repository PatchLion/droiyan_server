// ZoneInfoSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "ZoneInfoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoneInfoSet

IMPLEMENT_DYNAMIC(CZoneInfoSet, CRecordset)

CZoneInfoSet::CZoneInfoSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CZoneInfoSet)
	m_sSid = 0;
	m_sZone = 0;
	m_tPkMode = 0;
	m_tWeather = 0;
	m_sPotalZone = 0;
	m_sPotalX = 0;
	m_sPotalY = 0;
	m_sPotalX1 = 0;
	m_sPotalY1 = 0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CZoneInfoSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CZoneInfoSet::GetDefaultSQL()
{
	return _T("[dbo].[ZONEINFO]");
}

void CZoneInfoSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CZoneInfoSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Int(pFX, _T("[sZone]"), m_sZone);
	RFX_Byte(pFX, _T("[tPkMode]"), m_tPkMode);
	RFX_Byte(pFX, _T("[tWeather]"), m_tWeather);
	RFX_Int(pFX, _T("[sPotalZone]"), m_sPotalZone);
	RFX_Int(pFX, _T("[sPotalX]"), m_sPotalX);
	RFX_Int(pFX, _T("[sPotalY]"), m_sPotalY);
	RFX_Int(pFX, _T("[sPotalX1]"), m_sPotalX1);
	RFX_Int(pFX, _T("[sPotalY1]"), m_sPotalY1);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CZoneInfoSet diagnostics

#ifdef _DEBUG
void CZoneInfoSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CZoneInfoSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
