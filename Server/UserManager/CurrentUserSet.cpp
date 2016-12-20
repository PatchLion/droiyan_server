// CurrentUserSet.cpp: implementation of the CCurrentUserSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "usermanager.h"
#include "CurrentUserSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCurrentUserSet::CCurrentUserSet(CDatabase* pDB)
: CRecordset (pDB)
{
	m_nServiceID = 0;
}

CCurrentUserSet::~CCurrentUserSet()
{
	Close ();
}

void CCurrentUserSet::BindColumn()
{
	CRecordset::BindColumn ();
	if (m_nNumCol > 0)
	{
		Bind(0, SQL_C_SLONG);
	}
}

void CCurrentUserSet::DataExchange()
{
	DXInt (0, m_nServiceID);
}


BOOL CCurrentUserSet::GetServiceID()
{
	if (!Open ())
		return FALSE;

	CString strSQL;
	strSQL.Format (_T("SELECT nServiceID FROM CURRENTUSER WHERE strUserID='%s'"),
		m_strUserID);

	BOOL fRet = Query (strSQL) && Fetch ();
	Close ();
	return fRet;
}
