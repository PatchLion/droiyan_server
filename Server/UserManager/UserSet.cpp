// UserSet.cpp: implementation of the CUserSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "usermanager.h"
#include "UserSet.h"

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
		Bind(0, SQL_C_CHAR, 13);
		Bind(1, SQL_C_CHAR, 11);
		Bind(2, SQL_C_CHAR, 11);
		Bind(3, SQL_C_CHAR, 15);
		Bind(4, SQL_C_CHAR, 61);
		Bind(5, SQL_C_CHAR, 21);
		Bind(6, SQL_C_CHAR, 31);
	}
}

void CUserSet::DataExchange()
{
	DXString (0, m_strUserID);
	DXString (1, m_strPasswd);
	DXString (2, m_strName);
	DXString (3, m_strSocNo);
	DXString (4, m_strAddr);
	DXString (5, m_strTel);
	DXString (6, m_strEMail);
}

BOOL CUserSet::NewUser()
{
	if (!Open ())
		return FALSE;

	CString strSQL;
	strSQL.Format (_T("EXEC NEWUSER '%s','%s','%s','%s','%s','%s','%s'"),
		m_strUserID, m_strPasswd, m_strName, m_strSocNo, m_strAddr, m_strTel, m_strEMail);

	BOOL fRet = Query (strSQL);
	Close ();
	return fRet;
}

BOOL CUserSet::UpdateUser()
{
	if (!Open ())
		return FALSE;

	CString strSQL;
	strSQL.Format (_T("EXEC UPDATEUSER '%s','%s','%s','%s','%s','%s','%s'"),
		m_strUserID, m_strPasswd, m_strName, m_strSocNo, m_strAddr, m_strTel, m_strEMail);

	BOOL fRet = Query (strSQL);
	Close ();
	return fRet;
}

BOOL CUserSet::GetUser()
{
	if (!Open ())
		return FALSE;

	CString strSQL;
	strSQL.Format (_T("SELECT strUserID,strPasswd,strName,strSocNo,strAddr,strTel,strEMail FROM NGSCUSER WHERE strUserID='%s'"),
		m_strUserID);

	BOOL fRet = Query (strSQL) && Fetch ();
	Close ();
	return fRet;
}
