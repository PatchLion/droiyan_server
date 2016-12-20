// FileInfo.h: interface for the CFileInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEINFO_H__574E7D81_10A0_11D2_A53A_00A0248552AD__INCLUDED_)
#define AFX_FILEINFO_H__574E7D81_10A0_11D2_A53A_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CFileInfo : public CObject  
{
public:
	CString m_strFileName;
	CString m_strPathName;
	BYTE	m_bComp;
	WORD	m_wVer;
	DWORD	m_dwLength;

	CFileInfo(LPCTSTR lpszFileName, LPCTSTR lpszPathName, 
		BYTE bComp, WORD wVer, DWORD dwLength);
	virtual ~CFileInfo();
};

#endif // !defined(AFX_FILEINFO_H__574E7D81_10A0_11D2_A53A_00A0248552AD__INCLUDED_)
