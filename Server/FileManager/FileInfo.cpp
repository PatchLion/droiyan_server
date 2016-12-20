// FileInfo.cpp: implementation of the CFileInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileManager.h"
#include "FileInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileInfo::CFileInfo(LPCTSTR lpszFileName, LPCTSTR lpszPathName, 
					 BYTE bComp, WORD wVer, DWORD dwLength)
{
	m_strFileName = lpszFileName;
	m_strPathName = lpszPathName;
	m_bComp = bComp;
	m_wVer = wVer;
	m_dwLength = dwLength;
}

CFileInfo::~CFileInfo()
{

}
