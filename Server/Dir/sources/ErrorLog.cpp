// Class Name	: CErrorLog
// Do			: Error Logging
//
//	If this code works, it was written by JinSoo Jeon.
//	If not, I don't know who wrote it.
//

#include "stdafx.h"
#include "ErrorLog.h"

#include <lmerr.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( CErrorLog, CStdioFile);

CErrorLog::CErrorLog()
{
	m_szTime = _T("");
	m_szFileName = _T("");

	m_bFullPath = FALSE;
	m_bIsOpen	= FALSE;
}

CErrorLog::~CErrorLog()
{
	if(m_hFile != CFile::hFileNull) Close();
}

BOOL CErrorLog::OpenFile(LPCTSTR szFileName)
{
	if(m_bIsOpen) return FALSE;

	if(szFileName != _T("")) m_szFileName = szFileName;
	else
	{
		m_szFileName = GetProgPath();
		m_szFileName += _T("\\ErrorLog.log");
	}

	return Open(m_szFileName, 
		CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::shareDenyNone | CFile::typeBinary);
}

void CErrorLog::SetFullPath(BOOL bFull)
{
	m_bFullPath = bFull;
}

BOOL CErrorLog::_WriteError(BOOL bCondition, LPCTSTR szCondition, LPCTSTR szFunction, LPCTSTR szFile, int szLine, DWORD dwError)
{
	if(!bCondition) return FALSE;

	CString szMsg = _T("");
	CString szError = _T("");
	CString szFileName = _T("");

	GetErrorTime();
	GetSysErrorText(szError, dwError);
	RemoveReturn(szError);

	if(m_bFullPath) szFileName = szFile;
	else szFileName = GetFileName(szFile);

	szMsg.Format(_T("%s|%s(%d)|%s()|%s|err = %lu|%s\r\n"), 
		m_szTime, szFileName, szLine, szFunction, szCondition, dwError, szError);

	SeekToEnd();
	WriteString(szMsg);
	Flush( );

	return TRUE;
}

BOOL CErrorLog::_WriteError(BOOL bCondition, LPCTSTR szCondition, LPCTSTR szFunction, LPCTSTR szFile, int szLine, LPCTSTR szUserMsg)
{
	if(!bCondition) return FALSE;

	CString szMsg = _T("");
	CString szError = szUserMsg;
	CString szFileName = _T("");

	GetErrorTime();
	RemoveReturn(szError);

	if(m_bFullPath) szFileName = szFile;
	else szFileName = GetFileName(szFile);

	szMsg.Format(_T("%s|%s(%d)|%s()|%s|err = %lu|%s\r\n"), 
		m_szTime, szFileName, szLine, szFunction, szCondition, 0, szError);

	SeekToEnd();
	WriteString(szMsg);
	Flush( );

	return TRUE;
}

BOOL CErrorLog::_ShowError(BOOL bCondition, LPCTSTR szCondition, LPCTSTR szFunction, LPCTSTR szFile, int szLine, DWORD dwError)
{
	if(!bCondition) return FALSE;

	CString szMsg = _T("");
	CString szError = _T("");
	CString szFileName = _T("");

	GetSysErrorText(szError, dwError);

	if(m_bFullPath) szFileName = szFile;
	else szFileName = GetFileName(szFile);

	szMsg.Format(_T("%s(%d) : %s() : %s : err#(%lu)=%s"), 
		szFileName, szLine, szFunction, szCondition, dwError, szError);

	AfxMessageBox(szMsg);

	return TRUE;
}

CString CErrorLog::GetSysErrorText(DWORD dwError)
{
	static CString szMsg;
	GetSysErrorText(szMsg, dwError);

	return szMsg;
}

DWORD CErrorLog::GetSysErrorText(CString& errmsg, DWORD dwError)
{
	HMODULE 	hModule 	= NULL;		// default to system source
	LPTSTR		MessageBuffer	= NULL;
	DWORD		dwBufferLength;
	
	if(0 == dwError) dwError = ::GetLastError();

    //
	// if error_code is in the network range, load the message source
	//
	if (dwError >= NERR_BASE && dwError <= MAX_NERR) {
	    hModule = ::LoadLibraryEx(_T("netmsg.dll"), NULL, LOAD_LIBRARY_AS_DATAFILE);
	}
 
	//
	// call FormatMessage() to allow for message text to be acquired
	// from the system or the supplied module handle
	//
	dwBufferLength = ::FormatMessage( 
	    FORMAT_MESSAGE_ALLOCATE_BUFFER |
	    FORMAT_MESSAGE_IGNORE_INSERTS |
	    FORMAT_MESSAGE_FROM_SYSTEM |		// always consider system table
	    ((hModule != NULL) ? FORMAT_MESSAGE_FROM_HMODULE : 0),
	    hModule,					// module to get message from (NULL == system)
	    dwError,
	    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),	// default language
	    (LPTSTR) &MessageBuffer, 0, NULL );

    if ( MessageBuffer ) {
	    if ( dwBufferLength ) errmsg = (LPCTSTR)MessageBuffer;
 
	    // free the buffer allocated by the system
	    ::LocalFree(MessageBuffer);
	}
 
	//
	// if you loaded a message source, unload it
	//
	if (hModule != NULL) ::FreeLibrary(hModule);

    if ( errmsg.GetLength() == 0 ) 
	{
	    errmsg.Format( TEXT( "Unknown System Error %lu" ), dwError);
	}

    return dwError;
}

void CErrorLog::GetErrorTime()
{
	SYSTEMTIME st;
	::GetLocalTime(&st);

	m_szTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), 
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
}

int CErrorLog::RemoveReturn(CString& szText)
{
	int count1 = 0, count2 = 0;
	int strLen = szText.GetLength();

	TCHAR* str = szText.GetBuffer( strLen );
	while(*str) {
		if(*str == 0x0d) {
			_tcscpy(str, str + 1);
			count1++;
		}
		else str++;
	}
	szText.ReleaseBuffer(strLen - count1);

	strLen = szText.GetLength();
	str = szText.GetBuffer(strLen );
	while(*str) {
		if(*str == 0x0a) {
			_tcscpy(str, str + 1);
			count2++;
		}
		else str++;
	}
	szText.ReleaseBuffer(strLen - count2);

	return (count1 + count2);
}

CString CErrorLog::GetProgPath()
{
	char Buf[256], Path[256];
	char drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];

	::GetModuleFileName(AfxGetApp()->m_hInstance, Buf, 256);
	_splitpath(Buf,drive,dir,fname,ext);
	strcpy(Path, drive);
	strcat(Path, dir);		
	CString _Path = Path;
	return _Path;
}

CString CErrorLog::GetFileName(LPCTSTR szPath)
{
	CString szRet;
	TCHAR drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];

	_tsplitpath(szPath, drive, dir, fname, ext);
	szRet.Format(_T("%s%s"), fname, ext);

	return szRet;
}
