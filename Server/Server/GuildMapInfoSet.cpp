// GuildMapInfoSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "GuildMapInfoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuildMapInfoSet

IMPLEMENT_DYNAMIC(CGuildMapInfoSet, CRecordset)

CGuildMapInfoSet::CGuildMapInfoSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CGuildMapInfoSet)
	m_sMapIndex = 0;
	m_tPkMode = 0;
	m_sReleatedStore = 0;
	m_sGuildZone = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CGuildMapInfoSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CGuildMapInfoSet::GetDefaultSQL()
{
	return _T("[dbo].[GUILD_MAP_INFO]");
}

void CGuildMapInfoSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CGuildMapInfoSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sMapIndex]"), m_sMapIndex);
	RFX_Byte(pFX, _T("[tPkMode]"), m_tPkMode);
	RFX_Int(pFX, _T("[sReleatedStore]"), m_sReleatedStore);
	RFX_Int(pFX, _T("[sGuildZone]"), m_sGuildZone);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CGuildMapInfoSet diagnostics

#ifdef _DEBUG
void CGuildMapInfoSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CGuildMapInfoSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
