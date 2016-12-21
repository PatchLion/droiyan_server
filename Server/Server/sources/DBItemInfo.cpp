// DBItemInfo.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "DBItemInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBItemInfo

IMPLEMENT_DYNAMIC(CDBItemInfo, CRecordset)

CDBItemInfo::CDBItemInfo(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDBItemInfo)
	m_sNum = 0;
	m_strName = _T("");
	m_iCost = 0;
	m_tArm = 0;
	m_tUseLevel = 0;
	m_tUseType = 0;
	m_sPicNum = 0;
	m_sWg = 0;
	m_sDur = 0;
	m_sMaxAt = 0;
	m_sAtDelay = 0;
	m_tDmgX = 0;
	m_tDmgY = 0;
	m_tDmgZ = 0;
	m_tDf = 0;
	m_tAt = 0;
	m_tCrit = 0;
	m_tRange = 0;
	m_tOut = 0;
	m_tBullNum = 0;
	m_tBullType = 0;
	m_tStErr = 0;
	m_tStDf = 0;
	m_tStCure = 0;
	m_tHP = 0;
	m_tPP = 0;
	m_sSP = 0;
	m_nFields = 27;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CDBItemInfo::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CDBItemInfo::GetDefaultSQL()
{
	return _T("[dbo].[DBITEM]");
}

void CDBItemInfo::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDBItemInfo)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sNum]"), m_sNum);
	RFX_Text(pFX, _T("[strName]"), m_strName);
	RFX_Long(pFX, _T("[iCost]"), m_iCost);
	RFX_Byte(pFX, _T("[tArm]"), m_tArm);
	RFX_Byte(pFX, _T("[tUseLevel]"), m_tUseLevel);
	RFX_Byte(pFX, _T("[tUseType]"), m_tUseType);
	RFX_Int(pFX, _T("[sPicNum]"), m_sPicNum);
	RFX_Int(pFX, _T("[sWg]"), m_sWg);
	RFX_Int(pFX, _T("[sDur]"), m_sDur);
	RFX_Int(pFX, _T("[sMaxAt]"), m_sMaxAt);
	RFX_Int(pFX, _T("[sAtDelay]"), m_sAtDelay);
	RFX_Byte(pFX, _T("[tDmgX]"), m_tDmgX);
	RFX_Byte(pFX, _T("[tDmgY]"), m_tDmgY);
	RFX_Byte(pFX, _T("[tDmgZ]"), m_tDmgZ);
	RFX_Byte(pFX, _T("[tDf]"), m_tDf);
	RFX_Byte(pFX, _T("[tAt]"), m_tAt);
	RFX_Byte(pFX, _T("[tCrit]"), m_tCrit);
	RFX_Byte(pFX, _T("[tRange]"), m_tRange);
	RFX_Byte(pFX, _T("[tOut]"), m_tOut);
	RFX_Byte(pFX, _T("[tBullNum]"), m_tBullNum);
	RFX_Byte(pFX, _T("[tBullType]"), m_tBullType);
	RFX_Byte(pFX, _T("[tStErr]"), m_tStErr);
	RFX_Byte(pFX, _T("[tStDf]"), m_tStDf);
	RFX_Byte(pFX, _T("[tStCure]"), m_tStCure);
	RFX_Byte(pFX, _T("[tHP]"), m_tHP);
	RFX_Byte(pFX, _T("[tPP]"), m_tPP);
	RFX_Int(pFX, _T("[sSP]"), m_sSP);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDBItemInfo diagnostics

#ifdef _DEBUG
void CDBItemInfo::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDBItemInfo::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
