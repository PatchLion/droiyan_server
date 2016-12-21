// NpcTableSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "NpcTableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNpcTableSet

IMPLEMENT_DYNAMIC(CNpcTableSet, CRecordset)

CNpcTableSet::CNpcTableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CNpcTableSet)
	m_sSid = 0;
	m_sPid = 0;
	m_strName = _T("");
	m_sSTR = 0;
	m_sDEX = 0;
	m_sVOL = 0;
	m_sWIS = 0;
	m_sMaxHP = 0;
	m_sMaxPP = 0;
	m_byClass = 0;
	m_byClassLevel = 0;
	m_sExp = 0;
	m_byAX = 0;
	m_byAY = 0;
	m_byAZ = 0;
	m_byRange = 0;
	m_sAI = 0;
	m_sAttackDelay = 0;
	m_byVitalC = 0;
	m_byWildShot = 0;
	m_byExcitedRate = 0;
	m_byIronSkin = 0;
	m_byReAttack = 0;
	m_bySubAttack = 0;
	m_byState = 0;
	m_byPsi = 0;
	m_byPsiLevel = 0;
	m_bySearchRange = 0;
	m_sSpeed = 0;
	m_sInclination = 0;
	m_byColor = 0;
	m_sStandTime = 0;
	m_tNpcType = 0;
	m_sFamilyType = 0;
	m_tItemPer = 0;
	m_tDnPer = 0;
	m_byDefense = 0;
	m_nFields = 37;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CNpcTableSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CNpcTableSet::GetDefaultSQL()
{
	return _T("[dbo].[MONSTER]");
}

void CNpcTableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CNpcTableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Int(pFX, _T("[sPid]"), m_sPid);
	RFX_Text(pFX, _T("[strName]"), m_strName);
	RFX_Int(pFX, _T("[sSTR]"), m_sSTR);
	RFX_Int(pFX, _T("[sDEX]"), m_sDEX);
	RFX_Int(pFX, _T("[sVOL]"), m_sVOL);
	RFX_Int(pFX, _T("[sWIS]"), m_sWIS);
	RFX_Int(pFX, _T("[sMaxHP]"), m_sMaxHP);
	RFX_Int(pFX, _T("[sMaxPP]"), m_sMaxPP);
	RFX_Byte(pFX, _T("[byClass]"), m_byClass);
	RFX_Byte(pFX, _T("[byClassLevel]"), m_byClassLevel);
	RFX_Long(pFX, _T("[sExp]"), m_sExp);
	RFX_Int(pFX, _T("[byAX]"), m_byAX);
	RFX_Int(pFX, _T("[byAY]"), m_byAY);
	RFX_Int(pFX, _T("[byAZ]"), m_byAZ);
	RFX_Byte(pFX, _T("[byRange]"), m_byRange);
	RFX_Int(pFX, _T("[sAI]"), m_sAI);
	RFX_Int(pFX, _T("[sAttackDelay]"), m_sAttackDelay);
	RFX_Byte(pFX, _T("[byVitalC]"), m_byVitalC);
	RFX_Byte(pFX, _T("[byWildShot]"), m_byWildShot);
	RFX_Byte(pFX, _T("[byExcitedRate]"), m_byExcitedRate);
	RFX_Byte(pFX, _T("[byIronSkin]"), m_byIronSkin);
	RFX_Byte(pFX, _T("[byReAttack]"), m_byReAttack);
	RFX_Byte(pFX, _T("[bySubAttack]"), m_bySubAttack);
	RFX_Byte(pFX, _T("[byState]"), m_byState);
	RFX_Byte(pFX, _T("[byPsi]"), m_byPsi);
	RFX_Byte(pFX, _T("[byPsiLevel]"), m_byPsiLevel);
	RFX_Byte(pFX, _T("[bySearchRange]"), m_bySearchRange);
	RFX_Int(pFX, _T("[sSpeed]"), m_sSpeed);
	RFX_Int(pFX, _T("[sInclination]"), m_sInclination);
	RFX_Byte(pFX, _T("[byColor]"), m_byColor);
	RFX_Int(pFX, _T("[sStandTime]"), m_sStandTime);
	RFX_Byte(pFX, _T("[tNpcType]"), m_tNpcType);
	RFX_Int(pFX, _T("[sFamilyType]"), m_sFamilyType);
	RFX_Byte(pFX, _T("[tItemPer]"), m_tItemPer);
	RFX_Byte(pFX, _T("[tDnPer]"), m_tDnPer);
	RFX_Int(pFX, _T("[byDefense]"), m_byDefense);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CNpcTableSet diagnostics

#ifdef _DEBUG
void CNpcTableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CNpcTableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
