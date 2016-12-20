// ZipCompress.cpp: implementation of the CZipCompress class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "servicemanager.h"
#include "ZipCompress.h"
#include "VerSet.h"
#include "PatchVer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CZipCompress::CZipCompress()
{
}

CZipCompress::~CZipCompress()
{
}

////////////////////////////////////////////////////////////////////////
//
//	DB에서 해당 버젼의 파일들를 가져온다.
//
BOOL CZipCompress::GetFileNameToCompress(int iVersion, CString &strPathName, CString &strZipName)
{
	CString strFileName;
	CVerSet VerSet (&g_db);

	VerList *tempList;

	try 
	{
		if(VerSet.IsOpen()) VerSet.Close();
		if(!VerSet.Open()) 
		{
			AfxMessageBox(_T("VerSet DB Open Fail"));
			return FALSE;
		}
		if(VerSet.IsBOF()) 
		{
			AfxMessageBox(_T("VerSet DB Empty"));
			return FALSE;
		}

		tempList = NULL;
		tempList = new VerList;
		tempList->iVer = iVersion;
		tempList->strZipName = strZipName;

		while(!VerSet.IsEOF())
		{
			if(VerSet.m_wVersion == iVersion)
			{
				strFileName = _T("");
				strFileName = strPathName + _T("\\") + VerSet.m_strFileName;

				tempList->arFileList.Add(strFileName);
			}

			VerSet.MoveNext();
		}

		m_VerList.Add(tempList);

		VerSet.Close();
		return TRUE;
	}
	catch(CMemoryException * e)
	{
		e->ReportError();
		e->Delete();
	}
	catch(CDBException* e)
	{
		e->ReportError();
		e->Delete();
	}

	return FALSE;
}

// 목록에 따라 파일를 압축한다.
BOOL CZipCompress::SetFilesToCompress(int verCount, CString &strPath, CProgressCtrl	&prograss)
{
	int i;
	DWORD dwSize;

	CFile file;
	CFileFind fFind;
	CString		strMsg;

	m_zip.Open(m_VerList[verCount]->strZipName, CZipArchive::create);
		
	for(i = 0; i < m_VerList[verCount]->arFileList.GetSize(); i++)
	{
		dwSize = 0;
		file.Open(m_VerList[verCount]->arFileList[i], CFile::modeRead);
		dwSize = file.GetLength();
		file.Close();
/*		if(fFind.FindFile(m_VerList[verCount]->arFileList[i]))
		{
			FindNextFile();
			dwSize = fFind.GetLength();
		else FALSE;
*/
		TRACE("%s파일 %d", m_VerList[verCount]->arFileList[i], dwSize);
		if(!m_zip.AddNewFile(m_VerList[verCount]->arFileList[i], strPath, -1, dwSize)) return FALSE;
		prograss.SetPos(i*100/m_VerList.GetSize());
	}

	// 압축한 파일이 있는지 체크한다.
	if(fFind.FindFile(m_VerList[verCount]->strZipName)) 
	{
		if(!SetFileNameToDB(m_VerList[verCount]->iVer, m_VerList[verCount]->strZipName, 0))
		{
			AfxMessageBox(_T("Patch File 쓰기 실패"));
			return FALSE;
		}
	}

	m_zip.Close();

	return TRUE;
}

BOOL CZipCompress::GetFileName(CString &strFileName, CString &szFile, bool bOpen)
{
	int iFileSize = 0, iPathSize = 0;
	strFileName = szFile = _T("");

	CFileDialog fd(bOpen, "zip", bOpen ? NULL : "archive", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Zip Files (*.zip)|*.zip|All Files (*.*)|*.*||");
	if (fd.DoModal() != IDOK) return FALSE;
	szFile = fd.GetPathName();
	strFileName = fd.GetFileName();
	return TRUE;
}

BOOL CZipCompress::SetFileNameToDB(int ver, CString strFile, int iDel)
{
	SQLHSTMT		hstmt = NULL;
	SQLRETURN		retcode = 0;
	BOOL			bQuerySuccess = TRUE;
	TCHAR			szSQL[8000];		

	SQLSMALLINT	sCount = 0;
	SQLINTEGER sCountInd;

	::ZeroMemory(szSQL, sizeof(szSQL));

	_sntprintf(szSQL, sizeof(szSQL), TEXT("{call EDIT_PATCH_VERSION (\'%s\',%d, %d, ?)}"), strFile, ver, iDel);

	retcode = SQLAllocHandle( (SQLSMALLINT)SQL_HANDLE_STMT, g_db.m_hdbc, &hstmt );
	
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLBindParameter(hstmt,1 ,SQL_PARAM_OUTPUT,SQL_C_SSHORT, SQL_SMALLINT, 0, 0, &sCount, 0, &sCountInd);
		retcode = SQLExecDirect(hstmt, (unsigned char *)szSQL, SQL_NTS);
		if (retcode ==SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
		}
		else if (retcode==SQL_ERROR)
		{
			bQuerySuccess = FALSE;
		}
	}	
	
	if (hstmt!=NULL) SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);
	
	if(sCount == 3)
	{
		AfxMessageBox(_T("DB에 동일한 파일 이름 또는 버젼이 있습니다."));
		return FALSE;
	}

	if( !bQuerySuccess ) return FALSE;

	return TRUE;
}

BOOL CZipCompress::GetFileNameFromDB(arVerList &vList)
{	
	BOOL bFlag = TRUE;

	int iVer = 0;
	VerList *tempVer;
	CString strFileName = _T("");
	CPatchVer pVerSet(&g_db);

	try 
	{
		if(pVerSet.IsOpen()) pVerSet.Close();

		if(!pVerSet.Open()) 
		{
			AfxMessageBox(_T("VerSet DB Open Fail"));
			return FALSE;
		}
		
		while(!pVerSet.IsEOF())
		{
			tempVer = NULL;
			tempVer = new VerList;
			tempVer->strZipName = pVerSet.m_strFileName;
			tempVer->iVer = pVerSet.m_sVersion;
			
			vList.Add(tempVer);
			pVerSet.MoveNext();
		}

		pVerSet.Close();
		if(vList.GetSize() <= 0) return FALSE;
		return bFlag;
	}
	catch(CMemoryException * e)
	{
		e->ReportError();
		e->Delete();
	}
	catch(CDBException* e)
	{
		e->ReportError();
		e->Delete();
	}

	return FALSE;
}

int CZipCompress::ZipCompare(int ver)
{
/*	CFileFind fFind;

	CString zipName;

	GetCurrentDir(
	for(int i = 0; i < m_VerList.GetSize(); i++)
	{
		zipName = m_VerList[i]->strZipName;
		if(!fFind.FindFile(zipName))
		{
			CString strMsg;
			strMsg.Format("%s이 해당 ftp파일 목록에 존재하지 않습니다.", m_VerList[i]->strZipName);
			AfxMessageBox(strMsg);
			return -1;
		}

		m_zip.Open(zipName);

		for(i = 0; i < m_VerList[i]->arFileList.GetSize(); i++)
		{	
			CFileHeader tempHeader;
			m_Zip.GetFileInfo(tempHeader, i);
		}
		m_zip.Close();

	}
*/	return 1;
}
