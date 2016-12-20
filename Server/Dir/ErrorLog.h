// Class Name	: CErrorLog
// Do			: Error Logging
// Create		: 2000.05.31	by JinSoo Jeon
// Edit			: 2000.06.21 - Convert more OS error to string
//				: 2000.07.12 - Add another GetSysErrorText() version : __FILE__, __LINE__ support
//				:	by JinSoo Jeon
//				: 2000.07.15 - Add Define Function and delete needless function , Now version is 2.0 
//					by JinSoo Jeon
//
//	If this code works, it was written by JinSoo Jeon.
//	If not, I don't know who wrote it.
//

#pragma once

#define ShowError(c, f) _ShowError((c), #c, f, __FILE__, __LINE__, ::GetLastError())
#define WriteError(c, f) _WriteError((c), #c, f, __FILE__, __LINE__, ::GetLastError())
#define WriteError2(c, f, e) _WriteError((c), #c, f, __FILE__, __LINE__, e)

class CErrorLog : public CStdioFile
{
	DECLARE_DYNAMIC(CErrorLog);
public:
	CErrorLog();
	~CErrorLog();

	BOOL	OpenFile(LPCTSTR szFileName = _T(""));
	DWORD	GetSysErrorText(CString& errmsg, DWORD dwError = 0);
	CString	GetSysErrorText(DWORD dwError = 0);
	BOOL	_ShowError(BOOL bCondition, LPCTSTR szCondition, LPCTSTR szFunction, LPCTSTR szFile, int szLine, DWORD dwError);
	BOOL	_WriteError(BOOL bCondition, LPCTSTR szCondition, LPCTSTR szFunction, LPCTSTR szFile, int szLine, DWORD dwError);
	BOOL	_WriteError(BOOL bCondition, LPCTSTR szCondition, LPCTSTR szFunction, LPCTSTR szFile, int szLine, LPCTSTR szUserMsg);
	void	SetFullPath(BOOL bFull = FALSE);
	int		RemoveReturn(CString& szText);
	CString GetFileName(LPCTSTR szPath);

private:
	CString m_szFileName;
	CString m_szTime;

	CString GetProgPath();
	void	GetErrorTime();

	BOOL	m_bFullPath;
	BOOL	m_bIsOpen;
};