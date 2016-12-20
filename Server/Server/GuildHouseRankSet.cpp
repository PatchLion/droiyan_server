// GuildHouseRankSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "GuildHouseRankSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuildHouseRankSet

IMPLEMENT_DYNAMIC(CGuildHouseRankSet, CRecordset)

CGuildHouseRankSet::CGuildHouseRankSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CGuildHouseRankSet)
	m_tSid = 0;
	m_iGuild = 0;
	m_tNum = 0;
	m_sValue = 0;
	m_sGuildLevel = 0;
	m_iLastTime = 0;
	m_sZone = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CGuildHouseRankSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgamenew;UID=drgame;PWD=drgame");
}

CString CGuildHouseRankSet::GetDefaultSQL()
{
	return _T("[dbo].[GUILD_HOUSE_RANK]");
}

void CGuildHouseRankSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CGuildHouseRankSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Byte(pFX, _T("[tSid]"), m_tSid);
	RFX_Long(pFX, _T("[iGuild]"), m_iGuild);
	RFX_Byte(pFX, _T("[tNum]"), m_tNum);
	RFX_Int(pFX, _T("[sValue]"), m_sValue);
	RFX_Int(pFX, _T("[sGuildLevel]"), m_sGuildLevel);
	RFX_Long(pFX, _T("[iLastTime]"), m_iLastTime);
	RFX_Int(pFX, _T("[sZone]"), m_sZone);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CGuildHouseRankSet diagnostics

#ifdef _DEBUG
void CGuildHouseRankSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CGuildHouseRankSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
