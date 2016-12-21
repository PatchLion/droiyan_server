// PsiTableSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "PsiTableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPsiTableSet

IMPLEMENT_DYNAMIC(CPsiTableSet, CRecordset)

CPsiTableSet::CPsiTableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CPsiTableSet)
	m_iNeedDN = 0;
	m_iNeedXP = 0;
	m_sBasic = 0;
	m_sDelayTime = 0;
	m_sHoldTime = 0;
	m_sLevelUp = 0;
	m_sPid = 0;
	m_sSid = 0;
	m_strName = _T("");
	m_strText = _T("");
	m_tClass = 0;
	m_tNeedLevel = 0;
	m_tNeedPP = 0;
	m_tRange = 0;
	m_tRegi = 0;
	m_tTarget = 0;
	m_nFields = 16;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CPsiTableSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=drgame;PWD=drgame");
}

CString CPsiTableSet::GetDefaultSQL()
{
	return _T("[dbo].[PSI]");
}

void CPsiTableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPsiTableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[iNeedDN]"), m_iNeedDN);
	RFX_Long(pFX, _T("[iNeedXP]"), m_iNeedXP);
	RFX_Int(pFX, _T("[sBasic]"), m_sBasic);
	RFX_Int(pFX, _T("[sDelayTime]"), m_sDelayTime);
	RFX_Int(pFX, _T("[sHoldTime]"), m_sHoldTime);
	RFX_Int(pFX, _T("[sLevelUp]"), m_sLevelUp);
	RFX_Int(pFX, _T("[sPid]"), m_sPid);
	RFX_Int(pFX, _T("[sSid]"), m_sSid);
	RFX_Text(pFX, _T("[strName]"), m_strName);
	RFX_Text(pFX, _T("[strText]"), m_strText);
	RFX_Byte(pFX, _T("[tClass]"), m_tClass);
	RFX_Byte(pFX, _T("[tNeedLevel]"), m_tNeedLevel);
	RFX_Byte(pFX, _T("[tNeedPP]"), m_tNeedPP);
	RFX_Byte(pFX, _T("[tRange]"), m_tRange);
	RFX_Byte(pFX, _T("[tRegi]"), m_tRegi);
	RFX_Byte(pFX, _T("[tTarget]"), m_tTarget);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CPsiTableSet diagnostics

#ifdef _DEBUG
void CPsiTableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CPsiTableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
