// SerialSet.cpp: implementation of the CSerialSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "usermanager.h"
#include "SerialSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSerialSet::CSerialSet(CDatabase* pDB)
: CRecordset (pDB)
{
	m_wSerial = 0;
}

CSerialSet::~CSerialSet()
{
	Close ();
}

void CSerialSet::BindColumn()
{
	CRecordset::BindColumn ();
	if (m_nNumCol > 0)
	{
		Bind(0, SQL_C_UTINYINT);
		Bind(1, SQL_C_USHORT);
		Bind(2, SQL_C_TIMESTAMP);
		Bind(3, SQL_C_TIMESTAMP);
		Bind(4, SQL_C_SLONG);
	}
}

void CSerialSet::DataExchange()
{
	DXByte (0, m_bCheckResult);
	DXWord (1, m_wSerial);
	DXTime (2, m_timeStart);
	DXTime (3, m_timeEnd);
	DXInt (4, m_nCurReg);
}

BOOL CSerialSet::RegSerial ()
{
	if (!Open ())
		return FALSE;

	CString strSQL;
	strSQL.Format (_T("EXEC REGSERIAL '%s',%d,'%s'"), m_strUserID, m_wSerial, m_strPasswd);

	BOOL fRet = Query (strSQL) && Fetch ();
	Close ();
	return fRet;
}
