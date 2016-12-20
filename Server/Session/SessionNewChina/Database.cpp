// Database.cpp: implementation of the CDatabase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Database.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static SQLHENV	g_henv = SQL_NULL_HANDLE;
static int g_nEnvRef = 0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDatabase::CDatabase()
{
	m_hdbc = SQL_NULL_HANDLE;
}

CDatabase::~CDatabase()
{
	if (IsOpen ())
		Close ();
}

BOOL CDatabase::IsOpen()
{
	return (m_hdbc != SQL_NULL_HANDLE);
}

void CDatabase::Close()
{
	if (m_hdbc != SQL_NULL_HANDLE)
	{
		SQLFreeHandle (SQL_HANDLE_DBC, m_hdbc);
		m_hdbc = SQL_NULL_HANDLE;

		g_nEnvRef--;
		if (g_nEnvRef <= 0)
		{
			if (g_henv != SQL_NULL_HANDLE)
				SQLFreeHandle (SQL_HANDLE_ENV, g_henv);
			g_nEnvRef = 0;
		}
	}
}

BOOL CDatabase::Open(LPCTSTR lpszConnect)
{
	SQLRETURN nResult;                //result code

	if (IsOpen ())
		return FALSE;

	if (g_henv == SQL_NULL_HANDLE)
	{
		g_nEnvRef = 0;
		nResult = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, (SQLHANDLE*)&g_henv);
		if (!SQLOK(nResult))
		{
			g_henv = SQL_NULL_HANDLE;
			return FALSE;
		}
		nResult = SQLSetEnvAttr(g_henv, SQL_ATTR_ODBC_VERSION,
			(SQLPOINTER) SQL_OV_ODBC2, SQL_IS_INTEGER);
		if (!SQLOK(nResult))
		{
			SQLFreeHandle (SQL_HANDLE_ENV, g_henv);
			g_henv = SQL_NULL_HANDLE;
			return FALSE;
		}
	}

	// Allocate a new Connection Handle.
	nResult = SQLAllocHandle(SQL_HANDLE_DBC, g_henv, (SQLHANDLE*)&m_hdbc);
	if (!SQLOK(nResult))
	{
		m_hdbc = SQL_NULL_HANDLE;
		if (!g_nEnvRef && g_henv != SQL_NULL_HANDLE)
			SQLFreeHandle (SQL_HANDLE_ENV, g_henv);
		return FALSE;
	}

	// Call SQLDriverConnect to make a connection request. Provide SQL_DRIVER_COMPLETE_REQUIRED
	// flag sothat driver manager and driver can ask for connection information
	// If failed to connect, free the allocated hdbc in previous step.
	TCHAR szConnOut[1024];
	SQLSMALLINT nNumOut;
	nResult = SQLDriverConnect (m_hdbc, NULL, 
		(SQLCHAR*)lpszConnect, SQL_NTS, 
		(SQLCHAR*)szConnOut, 1024, &nNumOut, SQL_DRIVER_NOPROMPT);

	if (!SQLOK(nResult)) 
	{
		SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);
		m_hdbc = SQL_NULL_HANDLE;
		if (!g_nEnvRef && g_henv != SQL_NULL_HANDLE)
			SQLFreeHandle (SQL_HANDLE_ENV, g_henv);
		return FALSE;
	}

	g_nEnvRef++;
	return TRUE;
}

int GetAdjustedSQLSentence(char SqlSentence[])
{
	char sql_sentence[1024];
	char ret_sql_sentence[1024];
	int lenStr, i, k, error_count;
	BYTE byte, byte2;

	lenStr = strlen(SqlSentence);
	strcpy( sql_sentence, SqlSentence );

	k = 0;
	error_count = 0;
	for ( i = 0; i < lenStr; i++ )
	{
		byte = sql_sentence[i];
		if ( byte < 128 )
		{
			ret_sql_sentence[k++] = byte;
		}
		else
		{
			if ( byte >=0xa1 && byte <=0xfe )
			{
				i++;
				byte2 = sql_sentence[i];
				if ( byte2 >= 0xa1 && byte2 <=0xfe )
				{
					ret_sql_sentence[k++] = byte;
					ret_sql_sentence[k++] = byte2;
				}
				else
				{
					ret_sql_sentence[k++] = (char)0xA1;
					ret_sql_sentence[k++] = (char)0xBF;
					error_count++;
				}
			}
			else
			{
				ret_sql_sentence[k++] = (char)0xA1;
				ret_sql_sentence[k++] = (char)0xBF;
				error_count++;
			}
		}
	}

	ret_sql_sentence[k++] = '\0';

	if ( error_count <= 0 )
	{
		strcpy( SqlSentence, ret_sql_sentence );
	}

	return error_count;
}

int CheckQuostationMark(char SQLText[])
{
	int lenStr, i, k, error_count;
	BYTE byte;
	char sql_sentence[1024];
	char ret_sql_sentence[1024];

	lenStr = strlen(SQLText);
	strcpy( sql_sentence, SQLText );

	k = 0;
	error_count = 0;
	for ( i = 0; i < lenStr; i++ )
	{
		byte = sql_sentence[i];
		if ( byte != '\'' )
		{
			ret_sql_sentence[k++] = byte;
		}
		else
			error_count++;
	}

	ret_sql_sentence[k++] = '\0';

	if ( error_count <= 0 )
	{
		strcpy( SQLText, ret_sql_sentence );
	}

	return error_count;
}

SQLHDBC  CDatabase::Get_hdbc()
{
	return m_hdbc;
}
