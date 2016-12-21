// NpcChatSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "NpcChatSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNpcChatSet

IMPLEMENT_DYNAMIC(CNpcChatSet, CRecordset)

CNpcChatSet::CNpcChatSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CNpcChatSet)
	m_sCid = 0;
	m_sSize = 0;
	m_strTalk = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CNpcChatSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CNpcChatSet::GetDefaultSQL()
{
	return _T("[dbo].[NPC_CHAT]");
}

void CNpcChatSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CNpcChatSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sCid]"), m_sCid);
	RFX_Int(pFX, _T("[sSize]"), m_sSize);
	RFX_Text(pFX, _T("[strTalk]"), m_strTalk);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CNpcChatSet diagnostics

#ifdef _DEBUG
void CNpcChatSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CNpcChatSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
