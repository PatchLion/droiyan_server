// LogSet.cpp: implementation of the CLogSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "usermanager.h"
#include "LogSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogSet::CLogSet(CDatabase* pDB)
: CRecordset (pDB)
{
	m_bLoginResult = LR_USER_INVALID;
	m_wSerial = 0;
}

CLogSet::~CLogSet()
{
	Close ();
}

void CLogSet::BindColumn()
{
	CRecordset::BindColumn ();
	if (m_nNumCol > 0)
	{
		Bind(0, SQL_C_UTINYINT);
		Bind(1, SQL_C_UTINYINT);
	}
}

void CLogSet::DataExchange()
{
	DXByte (0, m_bLoginResult);
	DXByte (1, m_bCheckResult);
}

BOOL CLogSet::Logout()
{
	if (!Open ())
		return FALSE;

	CString strSQL;
	strSQL.Format (_T("EXEC UM_LOGOUT '%s',%d"), m_strUserID, (int)m_bReason);

	BOOL fRet = Query (strSQL);
	Close ();
	return fRet;
}

BOOL CLogSet::Login()
{
	if (!Open ())
		return FALSE;

	CString strSQL;
	strSQL.Format (_T("EXEC UM_LOGIN '%s','%s',%d,%d,'%s',%d"), 
		m_strUserID, m_strPasswd, m_nServiceID, m_nSessionID, m_strIPAddr, m_wSerial);

	BOOL fRet = Query (strSQL) && Fetch ();
	Close ();
	return fRet;
}
