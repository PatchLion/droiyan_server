// SerialKey.cpp : implementation file
//

#include "stdafx.h"
#include "session.h"
#include "SerialKey.h"
//#include "BankSerial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSerialKey

CSerialKey::CSerialKey(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_wSerial = 0;
	m_SerialKey = 0;
}

CSerialKey::~CSerialKey()
{
	Close();
}

void CSerialKey::BindColumn()
{
	CRecordset::BindColumn();
	if (m_nNumCol > 0)
	{
		Bind(0, SQL_C_SLONG);
		Bind(1, SQL_C_SLONG);
	}
}

void CSerialKey::DataExchange()
{
	DXDWord (0, m_wSerial);
	DXDWord (1, m_SerialKey);
}

BOOL CSerialKey::GetSerialKey()
{
	if (!Open ())
		return FALSE;

	CString strSQL;
	strSQL.Format (_T("SELECT WSERIAL, SERIALKEY FROM SERIAL_KEY WHERE WSERIAL= '%u'"), m_wSerial);
	BOOL fRet = Query(strSQL) && Fetch ();

	Close ();
	return fRet;
}
