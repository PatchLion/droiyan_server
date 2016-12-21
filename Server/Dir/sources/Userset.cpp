// Userset.cpp: implementation of the CUserSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BadukDir.h"
#include "Userset.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserSet::CUserSet(CDatabase* pDB)
: CRecordset (pDB)
{
	m_nZoneNumber = 0;
}

CUserSet::~CUserSet()
{
	Close ();
}

void CUserSet::BindColumn()
{
	CRecordset::BindColumn ();
	if (m_nNumCol > 0)
	{
		Bind(0, SQL_C_CHAR, 20);
		Bind(1, SQL_C_SSHORT); // Insert code when server is added.
	}
}

void CUserSet::DataExchange()
{
	DXString (0, m_strUserID);
	DXWord (1, m_nZoneNumber); // Insert code when server is added.
}

BOOL CUserSet::GetLogInZoneNumber()
{
	if (!Open ())
		return FALSE;

	CString strSQL;
	strSQL.Format (_T("SELECT strUserId,ZoneNumber FROM ZONEINFO WHERE strUserID='%s'"),
		m_strUserID);  // Insert code when server is added.

	BOOL fRet = Query (strSQL) && Fetch ();
	if(fRet == FALSE)
	{
		Close();
		if(!Open()) return FALSE;
		strSQL.Format(_T("{call QUERY_ZONEINFO (\'%s\')}"), m_strUserID);
		fRet = Query(strSQL);
		if(fRet == FALSE)
		{
			m_nZoneNumber = 0; // Insert code when server is added.
		}
	}
	Close();
	return fRet;
}

BOOL CUserSet::GetZoneNumber()
{
	if (!Open ())
		return FALSE;

	CString strSQL;
	strSQL.Format (_T("SELECT strUserId,ZoneNumber FROM ZONEINFO WHERE strUserID='%s'"),
		m_strUserID);  // Insert code when server is added.

	BOOL fRet = Query (strSQL) && Fetch ();
	Close ();
	return fRet;
}
