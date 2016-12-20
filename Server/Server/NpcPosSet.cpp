// NpcPosSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "NpcPosSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNpcPosSet

IMPLEMENT_DYNAMIC(CNpcPosSet, CRecordset)

CNpcPosSet::CNpcPosSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CNpcPosSet)
	m_sSid = 0;
	m_strName = _T("");
	m_byType = 0;	
	m_sZone = 0;
	m_sX = 0;
	m_sY = 0;
	m_sMinX = 0;
	m_sMinY = 0;
	m_sMaxX = 0;
	m_sMaxY = 0;
	m_sCount = 0;
	m_sRegenTime =0; 
	m_sEvent = 0;
	m_sEZone = 0;
	m_sGuild = 0;
	m_sDimension = 0;
	m_sHaveItem = 0;
	m_sSay = 0;
	m_nFields = 18;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CNpcPosSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgamenew;UID=drgame;PWD=drgame");
}

CString CNpcPosSet::GetDefaultSQL()
{
	return _T("[dbo].[MONSTER_POS]");
}

void CNpcPosSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CNpcPosSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Text(pFX, _T("[strName]"), m_strName);
	RFX_Byte(pFX, _T("[byType]"), m_byType);
	RFX_Int(pFX, _T("[sZone]"), m_sZone);
	RFX_Int(pFX, _T("[sX]"), m_sX);
	RFX_Int(pFX, _T("[sY]"), m_sY);
	RFX_Int(pFX, _T("[sMinX]"), m_sMinX);
	RFX_Int(pFX, _T("[sMinY]"), m_sMinY);
	RFX_Int(pFX, _T("[sMaxX]"), m_sMaxX);
	RFX_Int(pFX, _T("[sMaxY]"), m_sMaxY);
	RFX_Int(pFX, _T("[sCount]"), m_sCount);
	RFX_Long(pFX, _T("[sRegenTime]"), m_sRegenTime);
	RFX_Int(pFX, _T("[sEvent]"), m_sEvent);
	RFX_Int(pFX, _T("[sEZone]"), m_sEZone);
	RFX_Int(pFX, _T("[sGuild]"), m_sGuild);
	RFX_Int(pFX, _T("[sDimension]"), m_sDimension);
	RFX_Int(pFX, _T("[sHaveItem]"), m_sHaveItem);
	RFX_Int(pFX, _T("[sSay]"), m_sSay);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CNpcPosSet diagnostics

#ifdef _DEBUG
void CNpcPosSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CNpcPosSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
