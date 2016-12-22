// BankSerial.cpp : implementation file
//

#include "stdafx.h"
#include "session.h"
#include "BankSerial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBankSerial

CBankSerial::CBankSerial(CDatabase* pDB)
: CRecordset (pDB)
{
	m_wSerial = 0;
	m_nBankID = 0;
	m_strSerialCode = _T("");
}

CBankSerial::~CBankSerial()
{
	Close ();
}

void CBankSerial::BindColumn()
{
	CRecordset::BindColumn();
	if (m_nNumCol > 0)
	{
		Bind(0, SQL_C_ULONG);
		Bind(1, SQL_C_ULONG);
		Bind(2, SQL_C_CHAR, 14);
	}
}


void CBankSerial::DataExchange()
{
	DXDWord(0, m_wSerial);
	DXDWord(1, m_nBankID);
	DXString(2, m_strSerialCode);
}


BOOL CBankSerial::GetSerialCode()
{
	if (!Open())
		return FALSE;

	CString strSQL;
	strSQL.Format (_T("SELECT WSERIAL, NBANKID, STRSERIALCODE FROM BANK_SERIAL WHERE STRSERIALCODE = '%s'"), m_strSerialCode);

	BOOL fRet = Query(strSQL) && Fetch ();
	
	Close ();
	return fRet;
}
