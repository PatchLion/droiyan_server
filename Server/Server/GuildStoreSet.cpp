// GuildStoreSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "GuildStoreSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuildStoreSet

IMPLEMENT_DYNAMIC(CGuildStoreSet, CRecordset)

CGuildStoreSet::CGuildStoreSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CGuildStoreSet)
	m_sStoreID = 0;
	m_iGuildSid = 0;
	m_strGuildName = _T("");
	m_strMasterName = _T("");
	m_sTaxRate = 0;
	m_iGuildDN = 0;
	m_tWarType = 0;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CGuildStoreSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgamenew;UID=drgame;PWD=drgame");
}

CString CGuildStoreSet::GetDefaultSQL()
{
	return _T("[dbo].[GUILD_STORE]");
}

void CGuildStoreSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CGuildStoreSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sStoreID]"), m_sStoreID);
	RFX_Long(pFX, _T("[iGuildSid]"), m_iGuildSid);
	RFX_Text(pFX, _T("[strGuildName]"), m_strGuildName);
	RFX_Text(pFX, _T("[strMasterName]"), m_strMasterName);
	RFX_Int(pFX, _T("[sTaxRate]"), m_sTaxRate);
	RFX_Long(pFX, _T("[iGuildDN]"), m_iGuildDN);
	RFX_Date(pFX, _T("[GetTime]"), m_GetTime);
	RFX_Date(pFX, _T("[WarTime]"), m_WarTime);
	RFX_Date(pFX, _T("[WarPlan]"), m_WarPlan);
	RFX_Byte(pFX, _T("[tWarType]"), m_tWarType);
	RFX_Binary(pFX, _T("[strAttackList]"), m_strAttackList);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CGuildStoreSet diagnostics

#ifdef _DEBUG
void CGuildStoreSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CGuildStoreSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
