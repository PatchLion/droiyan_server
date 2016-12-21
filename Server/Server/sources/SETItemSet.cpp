// SETItemSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "SETItemSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSETItemSet

IMPLEMENT_DYNAMIC(CSETItemSet, CRecordset)

CSETItemSet::CSETItemSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSETItemSet)
	m_sSetIndex = 0;
	m_strMainName = _T("");
	m_bySetCount = 0;
	m_bySetAddOption1 = 0;
	m_bySetAddOption2 = 0;
	m_bySetAddOption3 = 0;
	m_bySetAddOption4 = 0;
	m_bySetAddOption5 = 0;
	m_bySetAddOption6 = 0;
	m_bySetAddOption7 = 0;
	m_bySetAddOption8 = 0;
	m_bySetAddOption9 = 0;
	m_sSet2 = 0;
	m_sSet3 = 0;
	m_sSet4 = 0;
	m_sSet5 = 0;
	m_sSet6 = 0;
	m_sSet7 = 0;
	m_sSet8 = 0;
	m_sSet9 = 0;
	m_sSet10 = 0;
	m_sSet11 = 0;
	m_sSet12 = 0;
	m_sSet13 = 0;
	m_sSet14 = 0;
	m_sSet15 = 0;
	m_sItem01 = 0;
	m_sItem02 = 0;
	m_sItem03 = 0;
	m_sItem04 = 0;
	m_sItem05 = 0;
	m_sItem06 = 0;
	m_sItem07 = 0;
	m_sItem08 = 0;
	m_sItem09 = 0;
	m_sItem10 = 0;
	m_nFields = 36;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSETItemSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame");
}

CString CSETItemSet::GetDefaultSQL()
{
	return _T("[dbo].[SET_ITEM]");
}

void CSETItemSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSETItemSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[sSetIndex]"), m_sSetIndex);
	RFX_Text(pFX, _T("[strMainName]"), m_strMainName);
	RFX_Byte(pFX, _T("[bySetCount]"), m_bySetCount);
	RFX_Byte(pFX, _T("[bySetAddOption1]"), m_bySetAddOption1);
	RFX_Byte(pFX, _T("[bySetAddOption2]"), m_bySetAddOption2);
	RFX_Byte(pFX, _T("[bySetAddOption3]"), m_bySetAddOption3);
	RFX_Byte(pFX, _T("[bySetAddOption4]"), m_bySetAddOption4);
	RFX_Byte(pFX, _T("[bySetAddOption5]"), m_bySetAddOption5);
	RFX_Byte(pFX, _T("[bySetAddOption6]"), m_bySetAddOption6);
	RFX_Byte(pFX, _T("[bySetAddOption7]"), m_bySetAddOption7);
	RFX_Byte(pFX, _T("[bySetAddOption8]"), m_bySetAddOption8);
	RFX_Byte(pFX, _T("[bySetAddOption9]"), m_bySetAddOption9);
	RFX_Int(pFX, _T("[sSet2]"), m_sSet2);
	RFX_Int(pFX, _T("[sSet3]"), m_sSet3);
	RFX_Int(pFX, _T("[sSet4]"), m_sSet4);
	RFX_Int(pFX, _T("[sSet5]"), m_sSet5);
	RFX_Int(pFX, _T("[sSet6]"), m_sSet6);
	RFX_Int(pFX, _T("[sSet7]"), m_sSet7);
	RFX_Int(pFX, _T("[sSet8]"), m_sSet8);
	RFX_Int(pFX, _T("[sSet9]"), m_sSet9);
	RFX_Int(pFX, _T("[sSet10]"), m_sSet10);
	RFX_Int(pFX, _T("[sSet11]"), m_sSet11);
	RFX_Int(pFX, _T("[sSet12]"), m_sSet12);
	RFX_Int(pFX, _T("[sSet13]"), m_sSet13);
	RFX_Int(pFX, _T("[sSet14]"), m_sSet14);
	RFX_Int(pFX, _T("[sSet15]"), m_sSet15);
	RFX_Int(pFX, _T("[sItem01]"), m_sItem01);
	RFX_Int(pFX, _T("[sItem02]"), m_sItem02);
	RFX_Int(pFX, _T("[sItem03]"), m_sItem03);
	RFX_Int(pFX, _T("[sItem04]"), m_sItem04);
	RFX_Int(pFX, _T("[sItem05]"), m_sItem05);
	RFX_Int(pFX, _T("[sItem06]"), m_sItem06);
	RFX_Int(pFX, _T("[sItem07]"), m_sItem07);
	RFX_Int(pFX, _T("[sItem08]"), m_sItem08);
	RFX_Int(pFX, _T("[sItem09]"), m_sItem09);
	RFX_Int(pFX, _T("[sItem10]"), m_sItem10);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSETItemSet diagnostics

#ifdef _DEBUG
void CSETItemSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSETItemSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
