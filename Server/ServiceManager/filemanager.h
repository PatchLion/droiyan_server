// FileManager.h: interface for the CFileManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEMANAGER_H__691746A6_2381_11D2_A54A_00A0248552AD__INCLUDED_)
#define AFX_FILEMANAGER_H__691746A6_2381_11D2_A54A_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Service.h"

class CFileManager : public CService  
{
public:
	DWORD m_dwBuffer;
	DWORD m_dwHold;
	CString m_strSrcPath;
	CString m_strModulePath;
	CFileManager(CServer* pServer, LPCTSTR lpszModule,
		LPCTSTR lpszAddr, int nPort, int nCapacity, 
		DWORD dwStatus = SERVICE_STOPPED);
	virtual ~CFileManager();

};

#endif // !defined(AFX_FILEMANAGER_H__691746A6_2381_11D2_A54A_00A0248552AD__INCLUDED_)
