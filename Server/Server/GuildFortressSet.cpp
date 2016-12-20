// GuildFortressSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "GuildFortressSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuildFortressSet

IMPLEMENT_DYNAMIC(CGuildFortressSet, CRecordset)

CGuildFortressSet::CGuildFortressSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CGuildFortressSet)
	m_sFortressID = 0;
	m_iGuildSid = 0;
	m_strGuildName = _T("");
	m_sTaxRate = 0;
	m_iGuildDN = 0;
	m_tWarType = 0;
	m_sPotalX = 0;
	m_sPotalY = 0;
	m_sZone = 0;
	m_nFields = 17;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CGuildFortressSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgamenew;UID=drgame;PWD=drgame");
}

CString CGuildFortressSet::GetDefaultSQL()
{
	return _T("[dbo].[GUILD_FORTRESS]");
}

void CGuildFortressSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CGuildFortressSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sFortressID]"), m_sFortressID);
	RFX_Long(pFX, _T("[iGuildSid]"), m_iGuildSid);
	RFX_Text(pFX, _T("[strGuildName]"), m_strGuildName);
	RFX_Int(pFX, _T("[sTaxRate]"), m_sTaxRate);
	RFX_Long(pFX, _T("[iGuildDN]"), m_iGuildDN);
	RFX_Date(pFX, _T("[GetTime]"), m_GetTime);
	RFX_Date(pFX, _T("[WarTime]"), m_WarTime);
	RFX_Date(pFX, _T("[WarPlan]"), m_WarPlan);
	RFX_Byte(pFX, _T("[tWarType]"), m_tWarType);
	RFX_Binary(pFX, _T("[HireGuardList]"), m_HireGuardList);
	RFX_Binary(pFX, _T("[strAttackList]"), m_strAttackList);
	RFX_Binary(pFX, _T("[strRepairList]"), m_strRepairList);
	RFX_Int(pFX, _T("[sPotalX]"), m_sPotalX);
	RFX_Int(pFX, _T("[sPotalY]"), m_sPotalY);
	RFX_Int(pFX, _T("[sZone]"), m_sZone);
	RFX_Date(pFX, _T("[MopPartyTime]"), m_MopPartyTime);
	RFX_Date(pFX, _T("[ReleaseTime]"), m_ReleaseTime);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CGuildFortressSet diagnostics

#ifdef _DEBUG
void CGuildFortressSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CGuildFortressSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
