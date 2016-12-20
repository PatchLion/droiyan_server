// ItemTableSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "ItemTableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CItemTableSet

IMPLEMENT_DYNAMIC(CItemTableSet, CRecordset)

CItemTableSet::CItemTableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CItemTableSet)
	m_byAX = 0;
	m_byAY = 0;
	m_byAZ = 0;
	m_byBullType = 0;
	m_byClass = 0;
	m_byErrorRate = 0;
	m_byMPP = 0;
	m_byRange = 0;
	m_byRdex = 0;
	m_byRLevel = 0;
	m_byRstr = 0;
	m_byRvol = 0;
	m_bySpecial = 0;
	m_bySubCure = 0;
	m_bySubDefense = 0;
	m_byWear = 0;
	m_byWeight = 0;
	m_iDN = 0;
	m_sAttackDelay = 0;
	m_sBullNum = 0;
	m_sCTime = 0;
	m_sDefense = 0;
	m_sDuration = 0;
	m_sEvent = 0;
	m_sPid = 0;
	m_sRepairHP = 0;
	m_sRepairPP = 0;
	m_sRepairSP = 0;
	m_sSid = 0;
	m_strName = _T("");
	m_strText = _T("");
	m_sZone = 0;
	m_nFields = 32;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CItemTableSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CItemTableSet::GetDefaultSQL()
{
	return _T("[dbo].[ITEM]");
}

void CItemTableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CItemTableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Byte(pFX, _T("[byAX]"), m_byAX);
	RFX_Byte(pFX, _T("[byAY]"), m_byAY);
	RFX_Byte(pFX, _T("[byAZ]"), m_byAZ);
	RFX_Byte(pFX, _T("[byBullType]"), m_byBullType);
	RFX_Byte(pFX, _T("[byClass]"), m_byClass);
	RFX_Byte(pFX, _T("[byErrorRate]"), m_byErrorRate);
	RFX_Byte(pFX, _T("[byMPP]"), m_byMPP);
	RFX_Byte(pFX, _T("[byRange]"), m_byRange);
	RFX_Byte(pFX, _T("[byRdex]"), m_byRdex);
	RFX_Byte(pFX, _T("[byRLevel]"), m_byRLevel);
	RFX_Byte(pFX, _T("[byRstr]"), m_byRstr);
	RFX_Byte(pFX, _T("[byRvol]"), m_byRvol);
	RFX_Byte(pFX, _T("[bySpecial]"), m_bySpecial);
	RFX_Byte(pFX, _T("[bySubCure]"), m_bySubCure);
	RFX_Byte(pFX, _T("[bySubDefense]"), m_bySubDefense);
	RFX_Byte(pFX, _T("[byWear]"), m_byWear);
	RFX_Byte(pFX, _T("[byWeight]"), m_byWeight);
	RFX_Long(pFX, _T("[iDN]"), m_iDN);
	RFX_Int(pFX, _T("[sAttackDelay]"), m_sAttackDelay);
	RFX_Int(pFX, _T("[sBullNum]"), m_sBullNum);
	RFX_Int(pFX, _T("[sCTime]"), m_sCTime);
	RFX_Int(pFX, _T("[sDefense]"), m_sDefense);
	RFX_Int(pFX, _T("[sDuration]"), m_sDuration);
	RFX_Int(pFX, _T("[sEvent]"), m_sEvent);
	RFX_Int(pFX, _T("[sPid]"), m_sPid);
	RFX_Int(pFX, _T("[sRepairHP]"), m_sRepairHP);
	RFX_Int(pFX, _T("[sRepairPP]"), m_sRepairPP);
	RFX_Int(pFX, _T("[sRepairSP]"), m_sRepairSP);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Text(pFX, _T("[strName]"), m_strName);
	RFX_Text(pFX, _T("[strText]"), m_strText);
	RFX_Int(pFX, _T("[sZone]"), m_sZone);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CItemTableSet diagnostics

#ifdef _DEBUG
void CItemTableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CItemTableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
