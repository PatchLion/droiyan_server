// SerialSet.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "SerialSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSerialSet

IMPLEMENT_DYNAMIC(CSerialSet, CRecordset)

CSerialSet::CSerialSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSerialSet)
	m_wSerial = 0;
	m_strPasswd = _T("");
	m_nMaxReg = 0;
	m_nCurReg = 0;
	m_nValidDay = 0;
	m_addrStart = 0;
	m_addrEnd = 255;
	m_nType = 0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSerialSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=SOMA");
	return _T("ODBC;DSN=Droiyan;UID=Droiyan;PWD=Droiyan");
}

CString CSerialSet::GetDefaultSQL()
{
	return _T("[dbo].[SERIAL]");
}

void CSerialSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSerialSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[wSerial]"), m_wSerial);
	RFX_Text(pFX, _T("[strPasswd]"), m_strPasswd);
	RFX_Date(pFX, _T("[timeStart]"), m_timeStart);
	RFX_Date(pFX, _T("[timeEnd]"), m_timeEnd);
	RFX_Long(pFX, _T("[nMaxReg]"), m_nMaxReg);
	RFX_Long(pFX, _T("[nCurReg]"), m_nCurReg);
	RFX_Long(pFX, _T("[nValidDay]"), m_nValidDay);
	RFX_Int(pFX, _T("[addrStart]"), m_addrStart);
	RFX_Int(pFX, _T("[addrEnd]"), m_addrEnd);
	RFX_Int(pFX, _T("[nType]"), m_nType);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSerialSet diagnostics

#ifdef _DEBUG
void CSerialSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSerialSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

int CSerialSet::IsFirstUse()
{
	if(IsFieldNull(&m_strPasswd))
	{
		return 1;
	}
	else
	{
		if(IsFieldNull(&m_timeStart))
		{
			return 2;
		}
	}

	return 0;
}

int CSerialSet::GetType()
{
	if (!m_nValidDay)
		return SERIAL_NOTUSE;

	if (m_nMaxReg > 0)
	{
		if (m_nValidDay > 0)
			return SERIAL_PRIVATE_MONTH;
		else
			return SERIAL_PRIVATE_TIME;
	}
	else
	{
		if (m_nValidDay > 0)
			return SERIAL_GAMEROOM_MONTH;
		else
			return SERIAL_GAMEROOM_TIME;
	}
}
