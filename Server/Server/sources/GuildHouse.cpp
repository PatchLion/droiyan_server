// GuildHouse.cpp: implementation of the CGuildHouse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "Extern.h"
#include "GuildHouse.h"

#include "mcommon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGuildHouse::CGuildHouse()
{
	iSid = 0;
	iGuild = 0;
	iZone = 0;
	iPotalX = 0;
	iPotalY = 0;

	iMarkNpc = -1;
	lUsed = 0;
}

CGuildHouse::~CGuildHouse()
{

}

void CGuildHouse::UpdateGuildHouse()
{
	SQLHSTMT		hstmt = NULL;
	SQLRETURN		retcode = 0;
	BOOL			bQuerySuccess = TRUE;
	TCHAR			szSQL[8000];

	BYTE			tSid = iSid;

	::ZeroMemory(szSQL, sizeof(szSQL));
	
	_sntprintf(szSQL, sizeof(szSQL), TEXT("{call UPDATE_GUILD_HOUSE(%d, %d)}"), tSid, iGuild);

	int db_index = 0;
	CDatabase* pDB = g_DBNew[AUTOMATA_THREAD].GetDB( db_index );
	if( !pDB ) return;

	retcode = SQLAllocHandle( (SQLSMALLINT)SQL_HANDLE_STMT, pDB->m_hdbc, &hstmt );
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLExecDirect(hstmt, (unsigned char *)szSQL, SQL_NTS);
		if (retcode ==SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
		}
		else if (retcode==SQL_ERROR)
		{
			DisplayErrorMsg( hstmt );
			bQuerySuccess = FALSE;
		}
	}
	else
	{
//		if (hstmt!=NULL) SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);
//		g_DBNew[AUTOMATA_THREAD].ReleaseDB(db_index);
		return;
	}

	if (hstmt!=NULL) SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);

	g_DBNew[AUTOMATA_THREAD].ReleaseDB(db_index);
	//g_DBNew.ReleaseDB(db_index);
}

