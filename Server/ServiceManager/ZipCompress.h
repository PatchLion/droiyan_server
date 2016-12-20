// ZipCompress.h: interface for the CZipCompress class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZIPCOMPRESS_H__2CA4C478_FED2_47EF_96B3_B8E64CF2F835__INCLUDED_)
#define AFX_ZIPCOMPRESS_H__2CA4C478_FED2_47EF_96B3_B8E64CF2F835__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ZipArchive.h"

//#define	 TEMP_PATH	"C:\\session\\upgrade\\"	
#define	 TEMP_PATH	"D:\\DroiyanTest\\"	

typedef struct _VERLIST
{
	int				iVer;
	CString			strZipName;
	CStringArray	arFileList;
	
} VerList;


typedef CTypedPtrArray <CPtrArray, VerList*>	arVerList;


class CVerSet;

class CZipCompress  
{
public:
	int ZipCompare(int ver);
	BOOL GetFileNameFromDB(arVerList &vList);
	BOOL SetFileNameToDB(int ver, CString strFile, int iDel);
	CZipArchive m_zip;

	arVerList	m_VerList;	
	arVerList	m_ZipVerList;
//	CStringArray m_FileNames;
//	CString m_strDir;
//	int		m_iVersion;
//	CString m_sZipName;			//	압축할 버젼 이름
//	CString m_strFileName;		//	해당 파일 이름
//	CString m_strPath;			//	해당 디렉토리 경로

	BOOL GetFileName(CString &strFileName, CString &szFile, bool bOpen);
	BOOL SetFilesToCompress(int verCount, CString &strPath, CProgressCtrl	&prograss);
	BOOL GetFileNameToCompress(int iVersion, CString &strPathName, CString &strZipName);


	CZipCompress();
	virtual ~CZipCompress();

};

#endif // !defined(AFX_ZIPCOMPRESS_H__2CA4C478_FED2_47EF_96B3_B8E64CF2F835__INCLUDED_)
