// LogSet.cpp: implementation of the CLogSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Session.h"
#include "LogSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void DisplayDBError(CString header, SQLHSTMT hstmt);

CP_IP_TableArray		g_arCP_IP_Table;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogSet::CLogSet(CDatabase* pDB)
: CRecordset (pDB)
{
	m_bLoginResult = LR_USER_INVALID;
	m_wSerial = 0;
	db = pDB;
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
//	strSQL.Format (_T("EXEC UM_LOGOUT '%s',%d"), m_strUserID, (int)m_bReason);
	strSQL.Format (_T("EXEC UM_CURRENTUSER_LOGOUT '%s'"), m_strUserID);

	BOOL fRet = Query (strSQL);
	Close ();

	return fRet;
//	return 1;
}

// bDisplay -> 0:표시 안함, 1:개인 정액, 2:개인 시간, 3:겜방 정액, 4:겜방 시간
BOOL CLogSet::Login(BYTE fPay, BYTE& bDisplay, int& remainTime, TIMESTAMP_STRUCT& endTime, TCHAR *ServerIP, BYTE& viewType)
{	
	if (!Open ())		// sql alloc handle
		return FALSE;

	SQLCHAR   	strServerIP[IP_LENGTH];	::memset(strServerIP, 0x00, IP_LENGTH);
	SQLCHAR   	strTelecom[30];		::memset(strTelecom, 0x00, 30);

	SQLRETURN	retcode;
	SWORD	sParam1 = 0;
	SDWORD	cbParam1 = SQL_NTS, cbParam2 = SQL_NTS, cbParam3 = SQL_NTS, cbParam4 = SQL_NTS, cbParam5 = SQL_NTS, cbParam6 = SQL_NTS;

	BYTE ipCheck = 0;
	int index = -1;

	index = CheckTelecomIP();
	if( index >= 0 && index < g_arCP_IP_Table.GetSize() )
	{
		if(!g_arCP_IP_Table[index]) return FALSE;

		int len = 0;
		ipCheck = 11;
		len = strlen(g_arCP_IP_Table[index]->m_strClientID);
		if(len <= 0 || len > 30) return FALSE;

		memcpy(strTelecom, g_arCP_IP_Table[index]->m_strClientID, len);
	}

	CString strSQL;
//	strSQL.Format (_T("{ ? = CALL UM_LOGIN1 ('%s','%s',%d,'%s',%d,'%s', ?, ?, ?, ?, ?)}"), 
//		m_strUserID, m_strPasswd, m_nServiceID, m_strIPAddr, ipCheck, m_strNicAddr, viewType, bDisplay, remainTime, endTime, strServerIP);
	strSQL.Format (_T("{ ? = CALL UM_LOGIN_TELECOM ('%s','%s',%d,'%s',%d,'%s', ?, ?, ?, ?, ?)}"), 
		m_strUserID, m_strPasswd, m_nServiceID, m_strIPAddr, ipCheck, strTelecom, viewType, bDisplay, remainTime, endTime, strServerIP);

	// to avoid telecom ip China free by youn Gyu 02-09-16

	retcode = SQLBindParameter(m_hstmt, 1,SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_SMALLINT,0,0,&sParam1,0,&cbParam1);
	retcode = SQLBindParameter(m_hstmt, 2,SQL_PARAM_OUTPUT, SQL_C_UTINYINT, SQL_TINYINT,0,0,&viewType,0,&cbParam2);
	retcode = SQLBindParameter(m_hstmt, 3,SQL_PARAM_OUTPUT, SQL_C_UTINYINT, SQL_TINYINT,0,0,&bDisplay,0,&cbParam3);
	retcode = SQLBindParameter(m_hstmt, 4,SQL_PARAM_OUTPUT, SQL_C_SLONG, SQL_INTEGER,0,0,&remainTime,0,&cbParam4);
	retcode = SQLBindParameter(m_hstmt, 5,SQL_PARAM_OUTPUT, SQL_C_TIMESTAMP, SQL_TIMESTAMP,0,0,&endTime,0,&cbParam5);
	retcode = SQLBindParameter(m_hstmt, 6,SQL_PARAM_OUTPUT, SQL_C_TCHAR, SQL_WCHAR,sizeof(strServerIP),0,(TCHAR*)strServerIP,sizeof(strServerIP),&cbParam6);

    retcode = SQLExecDirect (m_hstmt, (unsigned char *)(LPCTSTR)strSQL, SQL_NTS);

	if(retcode == SQL_ERROR) DisplayDBError(strSQL, m_hstmt);

	Close ();			// sql free handle

	::memcpy(ServerIP, strServerIP, IP_LENGTH);

	if(retcode < 0) return 100;

	return sParam1;
/*
	if (!Open ())
		return FALSE;

	// 테스트 서버용
	CString strSQL;
	strSQL.Format (_T("EXEC UM_LOGIN_DROIYAN0 '%s','%s',%d,'%s',%d"), 
		m_strUserID, m_strPasswd, m_nServiceID, m_strIPAddr, 0);

	BOOL fRet = Query (strSQL) && Fetch ();
	Close ();
	return !fRet;
*/
	// 본 서버용
/*
	if (!Open ())		// sql alloc handle
		return FALSE;

	SQLCHAR   	strServerIP[16];	::ZeroMemory(strServerIP, 16);

	SQLRETURN	retcode;
	SWORD	sParam1 = 0;
	SDWORD	cbParam1 = SQL_NTS, cbParam2 = SQL_NTS, cbParam3 = SQL_NTS, cbParam4 = SQL_NTS, cbParam5 = SQL_NTS, cbParam6 = SQL_NTS;

	CString strSQL;
	strSQL.Format (_T("{ ? = CALL UM_LOGIN1 ('%s','%s',%d,'%s',%d,'%s', ?, ?, ?, ?, ?)}"), 
		m_strUserID, m_strPasswd, m_nServiceID, m_strIPAddr, fPay, m_strNicAddr, viewType, bDisplay, remainTime, endTime, strServerIP);

	retcode = SQLBindParameter(m_hstmt, 1,SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_SMALLINT,0,0,&sParam1,0,&cbParam1);
	retcode = SQLBindParameter(m_hstmt, 2,SQL_PARAM_OUTPUT, SQL_C_UTINYINT, SQL_TINYINT,0,0,&viewType,0,&cbParam2);
	retcode = SQLBindParameter(m_hstmt, 3,SQL_PARAM_OUTPUT, SQL_C_UTINYINT, SQL_TINYINT,0,0,&bDisplay,0,&cbParam3);
	retcode = SQLBindParameter(m_hstmt, 4,SQL_PARAM_OUTPUT, SQL_C_SLONG, SQL_INTEGER,0,0,&remainTime,0,&cbParam4);
	retcode = SQLBindParameter(m_hstmt, 5,SQL_PARAM_OUTPUT, SQL_C_TIMESTAMP, SQL_TIMESTAMP,0,0,&endTime,0,&cbParam5);
	retcode = SQLBindParameter(m_hstmt, 6,SQL_PARAM_OUTPUT, SQL_C_TCHAR, SQL_WCHAR,sizeof(strServerIP),0,(TCHAR*)strServerIP,sizeof(strServerIP),&cbParam6);

    retcode = SQLExecDirect (m_hstmt, (unsigned char *)(LPCTSTR)strSQL, SQL_NTS);

	if(retcode == SQL_ERROR) DisplayDBError(strSQL, m_hstmt);

	Close ();			// sql free handle

	::CopyMemory(ServerIP, strServerIP, 16);

	if(retcode < 0) return 100;

	return sParam1;
*/
}

BOOL CLogSet::Initialize()
{
	if (!Open ())
		return FALSE;

	CString strSQL;
	strSQL.Format (_T("DELETE FROM CURRENTUSER WHERE nServiceID=%d"), m_nServiceID);

	BOOL fRet = Query (strSQL);
	Close ();
	return fRet;
}

//	by Youn Gyu 2001. 3. 27
BYTE CLogSet::ChangePass(CString cPasswd)
{
	if (!Open ())
		return 1;

	BYTE tret = 0;
	SQLRETURN	retcode;
	SWORD	sParam1 = 0;
	SDWORD	cbParam1 = SQL_NTS, cbParam2 = SQL_NTS;
	BOOL	retval = FALSE;

	CString strSQL;
	strSQL.Format (_T("{ ? = CALL CHANGEPASSWD ('%s', '%s', '%s', ?)}"), m_strUserID, m_strPasswd, cPasswd, tret);

	retcode = SQLBindParameter(m_hstmt, 1,SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER,0,0,&sParam1,0,&cbParam1);
	retcode = SQLBindParameter(m_hstmt, 2,SQL_PARAM_OUTPUT, SQL_C_UTINYINT, SQL_TINYINT,0,0,&tret,0,&cbParam2);

    retcode = SQLExecDirect (m_hstmt, (unsigned char *)(LPCTSTR)strSQL, SQL_NTS);

	if (retcode==SQL_ERROR)
	{
		tret = 1;

		TRACE("Return Error..\n");
	}
	else if (retcode==SQL_NO_DATA)
	{
		tret = 1;
	}

	if(SQLOK(retcode))
	{		
		if(tret == 1) tret = 0;
		else tret = 1;
	}

	Close ();			// sql free handle
	return tret;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&777 02-03-19
BOOL CLogSet::GetGameRoomInfo()
{
	if (!Open ())		// sql alloc handle
	{
		return FALSE;
	}

	TCHAR			strSQL[2048];

	int i = 0, len = 0;
	SQLRETURN	retcode;
	SQLINTEGER   lTelecomIndex = 0;
	SQLBIGINT dStartIP = 0, dEndIP = 0;

	SQLINTEGER		sInd;

	SQLCHAR			strID[30];
	SQLCHAR			startIP[17];
	SQLCHAR			endIP[17];
	SQLINTEGER   lType = 0;

	::ZeroMemory(strID, sizeof(strID));
	::ZeroMemory(startIP, sizeof(startIP));
	::ZeroMemory(endIP, sizeof(endIP));

	::ZeroMemory(strSQL, sizeof(strSQL));
	wsprintf(strSQL,TEXT("SELECT * FROM CP_IP_MASK"));

	retcode = SQLExecDirect( m_hstmt, (unsigned char*)strSQL, SQL_NTS);
	if( retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO )
	{
		while (TRUE)
		{
			retcode = SQLFetch(m_hstmt);

			if (retcode ==SQL_SUCCESS || retcode ==SQL_SUCCESS_WITH_INFO)
			{
				i = 1;
				CCP_IP_MASKTable *pIP = new CCP_IP_MASKTable;

				SQLGetData( m_hstmt, i++, SQL_C_ULONG, &lTelecomIndex, sizeof(lTelecomIndex), &sInd );
				SQLGetData( m_hstmt, i++, SQL_C_CHAR, &strID, sizeof(strID), &sInd );
				SQLGetData( m_hstmt, i++, SQL_C_CHAR, &startIP, sizeof(startIP), &sInd );
				SQLGetData( m_hstmt, i++, SQL_C_ULONG, &dStartIP, sizeof(dStartIP), &sInd );
				SQLGetData( m_hstmt, i++, SQL_C_CHAR, &endIP, sizeof(endIP), &sInd );
				SQLGetData( m_hstmt, i++, SQL_C_ULONG, &dEndIP, sizeof(dEndIP), &sInd );
				SQLGetData( m_hstmt, i++, SQL_C_ULONG, &lType, sizeof(lType), &sInd );

				len = strlen((char *)strID);
				::ZeroMemory(pIP->m_strClientID, sizeof(pIP->m_strClientID));
				::CopyMemory(pIP->m_strClientID, strID, len);
				pIP->m_startnum = (double)dStartIP;
				pIP->m_endnum = (double)dEndIP;
				::CopyMemory(pIP->m_StartIP, startIP, sizeof(startIP));
				::CopyMemory(pIP->m_EndIP, endIP, sizeof(endIP));
//				pIP->m_StartIP.Format("%s", startIP);
//				pIP->m_EndIP.Format("%s", endIP);
				pIP->m_iType = (int)lType;

				g_arCP_IP_Table.Add(pIP);

				lTelecomIndex = 0;
				dStartIP = 0;
				dEndIP = 0;
				len = 0;

				::ZeroMemory(strID, sizeof(strID));
				::ZeroMemory(startIP, sizeof(startIP));
				::ZeroMemory(endIP, sizeof(endIP));
			}
			else break;
		}
	}
	else
	{
		Close();
		return FALSE;
	}

	if(retcode == SQL_ERROR)
	{
		Close();
		return FALSE;
	}

	Close ();			// sql free handle

/*	if (!Open ())		// sql alloc handle
	{
		return FALSE;
	}

	SQLRETURN	retcode;
	SQLCHAR	bizno[13] = _T("");
	SWORD	sParam1 = 0;
	SDWORD	cbParam1 = SQL_NTS, cbParam2 = SQL_NTS;
	BOOL	retval = FALSE;

//	TCHAR			szSQL[1024];
	// 1. MATCH COUNT
//	memset(szSQL, 0x00, 1024);
//	wsprintf(szSQL, TEXT("{ ? = CALL GM_GETBIZNO ('%s', ?)}"), m_strIPAddr );

	CString strSQL;
	strSQL.Format (_T("{ ? = CALL GM_GETBIZNO ('%s', ?)}"), m_strIPAddr );

	retcode = SQLBindParameter(m_hstmt, 1,SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER,0,0,&sParam1,0,&cbParam1);
	retcode = SQLBindParameter(m_hstmt, 2,SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_CHAR,0,0,bizno,13,&cbParam2);

    retcode = SQLExecDirect (m_hstmt, (unsigned char *)(LPCTSTR)strSQL, SQL_NTS);

/*	do
	{
		SWORD nResultColumns;
		SQLNumResultCols(m_hstmt, &nResultColumns);
		if (nResultColumns != 0)
		{
			do {
				retcode = SQLFetch(m_hstmt);
			} while ( retcode != SQL_NO_DATA_FOUND );
		}
		retcode = SQLMoreResults(m_hstmt);
	} while ( retcode != SQL_NO_DATA_FOUND );*/
 
/*	if(retcode == SQL_ERROR) DisplayDBError(strSQL, m_hstmt);

	if(SQLOK(retcode))
	{
		if( bizno[0] != NULL ) {
			m_strBizNo = bizno;
			retval =TRUE;
		}
		else  {
			m_strBizNo = "";
#ifdef _DEBUG
			DisplayError( retcode, SQL_HANDLE_STMT, m_hstmt);
#endif
			retval= FALSE;
		}
	}
	else m_strBizNo = "";

	Close ();			// sql free handle
	return retval;
*/
	return TRUE;
}

int CLogSet::CheckTelecomIP()
{	
	int i = 0;
	int index1 = 0;

	i = strlen(m_strIPAddr);
	if(i <= 0 || i > IP_LENGTH) return -1;

	CString strIP = _T("");
	CString strIP1 = _T("");
	CString strIP2 = _T("");
	CString strIP3 = _T("");
	CString strIP4 = _T("");

	strIP.Format("%s", m_strIPAddr);

	index1 = strIP.Find(".");
	strIP1 = strIP.Left(index1);

	strIP.Delete(0, index1 + 1);
	index1 = strIP.Find(".");
	strIP2 = strIP.Left(index1);

	strIP.Delete(0, index1 + 1);
	index1 = strIP.Find(".");
	strIP3 = strIP.Left(index1);

	strIP.Delete(0, index1 + 1);
	strIP4 = strIP;

	DWORD ip1 = atoi(strIP1);
	DWORD ip2 = atoi(strIP2);
	DWORD ip3 = atoi(strIP3);
	DWORD ip4 = atoi(strIP4);

	ip1 = ip1 << 24;
	ip2 = ip2 << 16;
	ip3 = ip3 << 8;

	DWORD ip = ip1^ip2^ip3^ip4;	

	for(i = 0; i < g_arCP_IP_Table.GetSize(); i++)
	{
		if( ip >= g_arCP_IP_Table[i]->m_startnum && ip <= g_arCP_IP_Table[i]->m_endnum )
		{
			return i;
		}
	}

	return -1;
}
