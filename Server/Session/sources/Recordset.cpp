// Recordset.cpp: implementation of the CRecordset class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Recordset.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define SQLERR_FORMAT       "SQL Error State:%s, Native Error Code: %lX, ODBC Error: %s"
#define SQLERRMSGTITLE      "SQL_ERROR results"
#define SQLERRCNTDTITLE     "SQL_ERROR results continued"
#define SQLWRNMSGTITLE      "SQL_SUCCESS_WITH_INFO results"
#define SQLWRNCNTDTITLE     "SQL_SUCCESS_WITH_INFO results continued"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRecordset::CRecordset(CDatabase * pDB)
{
	m_pDB = pDB;
	m_hstmt = SQL_NULL_HANDLE;
	m_pDataPos[0] = m_bufData;
}

CRecordset::~CRecordset()
{

}

BOOL CRecordset::Open()
{
	if (!m_pDB || !m_pDB->IsOpen ())
		return FALSE;
	if (m_hstmt != SQL_NULL_HANDLE)
		return FALSE;

	SQLRETURN nResult;
	nResult = SQLAllocHandle (SQL_HANDLE_STMT, m_pDB->m_hdbc, (SQLHANDLE*)&m_hstmt);
	if (!SQLOK(nResult))
	{
		m_hstmt = SQL_NULL_HANDLE;
		return FALSE;
	}

	return TRUE;
}

BOOL CRecordset::IsOpen ()
{
	return (m_hstmt != SQL_NULL_HANDLE);
}

void CRecordset::Close()
{
	if (m_hstmt != SQL_NULL_HANDLE)
	{
		SQLCloseCursor(m_hstmt);
		SQLFreeHandle (SQL_HANDLE_STMT, m_hstmt);
		m_hstmt = SQL_NULL_HANDLE;
	}
}

void CRecordset::BindColumn()
{
	SQLRETURN nResult = SQLNumResultCols(m_hstmt, (SWORD*)&m_nNumCol);
#ifdef _DEBUF
	if (!SQLOK (nResult))
	{
		DisplayError (nResult, SQL_HANDLE_STMT, m_hstmt);
	}
#endif
}


BOOL CRecordset::Query(LPCTSTR lpszQuery)
{
	if (!IsOpen ())
		return FALSE;

	// execute SQL and process errors if any
	// call SQLExecDirect to execute the SQL statement
	SQLRETURN nResult;                    // return code
	nResult = SQLExecDirect(m_hstmt, (SQLCHAR*)lpszQuery, SQL_NTS);
	if (!SQLOK (nResult)) 
	{
#ifdef _DEBUG
		DisplayError (nResult, SQL_HANDLE_STMT, m_hstmt);
#endif
		return FALSE;
	}

	BindColumn ();

	return TRUE;
}

int CRecordset::Execute(LPCTSTR lpszQuery)
{
	if (!IsOpen ())
		return FALSE;

	SQLRETURN	nResult;                    // return code
	SWORD		sParmRet=0;
	SDWORD		cbParmRet=SQL_NTS;

	nResult = SQLBindParameter(m_hstmt, 1,SQL_PARAM_OUTPUT,SQL_C_SSHORT,SQL_INTEGER,0,0,&sParmRet,0,&cbParmRet);
	if (!SQLOK (nResult)) 
	{
#ifdef _DEBUG
		DisplayError (nResult, SQL_HANDLE_STMT, m_hstmt);
#endif
		return -1;
	}

	nResult = SQLExecDirect(m_hstmt, (SQLCHAR*)lpszQuery, SQL_NTS);
	if (!SQLOK (nResult)) 
	{
#ifdef _DEBUG
		DisplayError (nResult, SQL_HANDLE_STMT, m_hstmt);
#endif
		return -1;
	}

	return sParmRet;
}


void CRecordset::Bind(int nCol, SQLSMALLINT nType, DWORD dwLen)
{
	switch (nType)
	{
	case SQL_C_SSHORT			:
	case SQL_C_USHORT			: dwLen = sizeof (short int); break;
	case SQL_C_SLONG			:
	case SQL_C_ULONG			: dwLen = sizeof (long int); break;
	case SQL_C_BIT				:
	case SQL_C_STINYINT			:
	case SQL_C_UTINYINT			: dwLen = sizeof (char); break;
	case SQL_C_FLOAT			: dwLen = sizeof (float); break;
	case SQL_C_TIME				:
	case SQL_C_DATE				:
	case SQL_C_TIMESTAMP		: dwLen = sizeof(TIMESTAMP_STRUCT);
	}

	SQLBindCol(m_hstmt, (SQLSMALLINT)nCol + 1, 
		nType, (SQLPOINTER)m_pDataPos[nCol], (SQLINTEGER)dwLen, 
		(SQLINTEGER*)&m_dwDataLen[nCol]);
	m_pDataPos[nCol + 1] = m_pDataPos[nCol] + dwLen;
}

BOOL CRecordset::Fetch()
{
	if (!IsOpen ())
		return FALSE;

	SQLRETURN nResult;
	nResult = SQLFetch(m_hstmt);
	if (!SQLOK (nResult))
	{
#ifdef _DEBUG
		DisplayError (nResult, SQL_HANDLE_STMT, m_hstmt);
#endif
		return FALSE;
	}
	DataExchange ();
	return TRUE;
}

void CRecordset::DataExchange()
{

}

void CRecordset::DXString(int nCol, CString &strField)
{
	if (!IsFieldNull (nCol))
		strField = (LPTSTR)m_pDataPos[nCol];
}

void CRecordset::DXWord(int nCol, WORD &wField)
{
	if (!IsFieldNull (nCol))
		wField = *((WORD*)m_pDataPos[nCol]);
}

void CRecordset::DXDWord(int nCol, DWORD &dwField)
{
	if (!IsFieldNull (nCol))
		dwField = *((DWORD*)m_pDataPos[nCol]);
}

void CRecordset::DXByte(int nCol, BYTE &bField)
{
	if (!IsFieldNull (nCol))
		bField = *((BYTE*)m_pDataPos[nCol]);
}

void CRecordset::DXTime(int nCol, CTime &timeField)
{
	if (!IsFieldNull (nCol))
	{
		TIMESTAMP_STRUCT* pts = (TIMESTAMP_STRUCT*)(m_pDataPos[nCol]);
		timeField = CTime (pts->year, pts->month, pts->day, 
			pts->hour, pts->minute, 0);
	}
}

void CRecordset::DXInt(int nCol, int &nField)
{
	if (!IsFieldNull (nCol))
		nField = *((int*)m_pDataPos[nCol]);
}

BOOL CRecordset::IsFieldNull(int nCol)
{
	return m_dwDataLen[nCol] == SQL_NULL_DATA;
}

#ifdef _DEBUG
void CRecordset::DisplayError(SQLRETURN nResult, SWORD fHandleType, SQLHANDLE handle)
{
   UCHAR    szErrState[SQL_SQLSTATE_SIZE+1];    // SQL Error State string
   UCHAR    szErrText[SQL_MAX_MESSAGE_LENGTH+1];    // SQL Error Text string
   char szBuffer[SQL_SQLSTATE_SIZE+SQL_MAX_MESSAGE_LENGTH+MAX_DATALEN+1];
   char szDispBuffer[SQL_SQLSTATE_SIZE+SQL_MAX_MESSAGE_LENGTH+MAX_DATALEN+1];
   // formatted Error text Buffer
   SWORD    wErrMsgLen;             // Error message length
   UDWORD   dwErrCode;              // Native Error code
   int  iSize;                      // Display Error Text size
   SQLRETURN  nErrResult;             // Return Code from SQLGetDiagRec
   SWORD sMsgNum = 1;
   SWORD fFirstRun = TRUE;

   szBuffer[0] = '\0';

   do
      {
         // continue to bring messageboxes till all errors are displayed.
         // more than one message box may be reqd. as err text has fixed
         // string size.

         // initialize display buffer with the string in error text buffer
         strcpy(szDispBuffer, szBuffer);

         // call SQLGetDiagRec function with proper ODBC handles, repeatedly until
         // function returns SQL_NO_DATA. Concatenate all error strings
         // in the display buffer and display all results.
         while ((nErrResult = SQLGetDiagRec(fHandleType, handle, sMsgNum++,
                                            szErrState, (SQLINTEGER*)&dwErrCode, szErrText,
                                            SQL_MAX_MESSAGE_LENGTH-1, &wErrMsgLen))
                != SQL_NO_DATA) {

				
				if(nErrResult == SQL_ERROR || nErrResult == SQL_INVALID_HANDLE)
					break;

            wsprintf(szBuffer, SQLERR_FORMAT, (LPSTR)szErrState, dwErrCode, (LPSTR)szErrText);
            iSize = strlen(szDispBuffer);
            if (iSize && (iSize+strlen(szBuffer)+1) >= 80)
               break;
            if (iSize)
               strcat(szDispBuffer, "\n");
            strcat(szDispBuffer, szBuffer);
         }

         // display proper ERROR or WARNING message with proper title
			
         //if (nResult == SQL_SUCCESS_WITH_INFO)
         //   MessageBox(NULL, szDispBuffer, (fFirstRun? SQLWRNMSGTITLE : SQLWRNCNTDTITLE),
         //              MB_OK | MB_ICONINFORMATION);
         //else if (nErrResult != SQL_NO_DATA)
         //   MessageBox(NULL, szDispBuffer, (fFirstRun? SQLERRMSGTITLE : SQLERRCNTDTITLE),
         //              MB_OK | MB_ICONEXCLAMATION);

		 TRACE("*** %s ***\n", szDispBuffer );

         if (fFirstRun)
            fFirstRun = FALSE;
      }

   while (!(nErrResult == SQL_NO_DATA || nErrResult == SQL_ERROR || nErrResult == SQL_INVALID_HANDLE));
}
/********************************************* END OF FILE **************************************************/
#endif

