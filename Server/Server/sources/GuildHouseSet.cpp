// GuildHouseSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "GuildHouseSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuildHouseSet

IMPLEMENT_DYNAMIC(CGuildHouseSet, CRecordset)

CGuildHouseSet::CGuildHouseSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CGuildHouseSet)
	m_tSid = 0;
	m_iGuild = 0;
	m_sZone = 0;
	m_sPotalX = 0;
	m_sPotalY = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CGuildHouseSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgamenew;UID=drgame;PWD=drgame");
}

CString CGuildHouseSet::GetDefaultSQL()
{
	return _T("[dbo].[GUILD_HOUSE]");
}

void CGuildHouseSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CGuildHouseSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Byte(pFX, _T("[tSid]"), m_tSid);
	RFX_Long(pFX, _T("[iGuild]"), m_iGuild);
	RFX_Int(pFX, _T("[sZone]"), m_sZone);
	RFX_Int(pFX, _T("[sPotalX]"), m_sPotalX);
	RFX_Int(pFX, _T("[sPotalY]"), m_sPotalY);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CGuildHouseSet diagnostics

#ifdef _DEBUG
void CGuildHouseSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CGuildHouseSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
