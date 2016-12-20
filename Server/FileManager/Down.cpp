// Down.cpp: implementation of the CDown class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileManager.h"
#include "FileManagerCom.h"
#include "FileInfo.h"
#include "Down.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDown::CDown()
{
	m_pDes = NULL;
	m_dwCurrentDown = m_dwCurrentSend = 0;
	m_nState = stateNone;
}

CDown::~CDown()
{
	Reset ();
}

void CDown::SetDesc (CSessDesc* pDes)
{
	m_pDes = pDes;
}

BOOL CDown::IsDownState ()
{
	;
}

CFileInfo* CDown::GetFileInfo ()
{
	if (m_listFile.IsEmpty ())
		return NULL;

	CFileInfo* pInfo = (CFileInfo*)m_listFile.RemoveHead ();
	m_strFileName = pInfo->m_strPathName;
	return pInfo;
}

int CDown::GetNumDownFile()
{
	return m_listFile.GetCount ();
}

void CDown::AddFileInfo (CFileInfo* pInfo)
{
	m_listFile.AddTail (pInfo);
}

BOOL CDown::ProcDown()
{
	int nRead = m_file.Read (m_buf, DEF_DOWN_SIZE);
	if (nRead < DEF_DOWN_SIZE)
	{
		m_file.Close ();
		m_dwCurrentSend = m_dwCurrentDown = 0;
		m_nState = stateNone;
	}

	if (nRead)
	{
		CMsg msg;
		msg.ID (FM_DOWN_ACK);
		msg.WriteData (m_buf, nRead);
		if (m_pDes) m_pDes->Say (msg);
		m_dwCurrentSend += nRead;
	}

	return TRUE;
}

BOOL CDown::StartDown ()
{
	if (!m_file.Open (m_strFileName, CFile::modeRead | CFile::shareDenyNone))
		return FALSE;

	m_nState = stateDown;
	m_dwCurrentDown = m_dwCurrentSend = 0;
	return TRUE;
}

DWORD CDown::GetLengthTotalFile()
{
	DWORD dwLength = 0;
	POSITION pos = m_listFile.GetHeadPosition ();
	while (pos)
	{
		CFileInfo* pInfo = (CFileInfo*)m_listFile.GetNext (pos);
		dwLength += pInfo->m_dwLength;
	}
	return dwLength;	
}

void CDown::Reset()
{
	if (m_nState == stateDown)
		m_file.Close ();

	m_dwCurrentDown = m_dwCurrentSend = 0;
	m_nState = stateNone;
	m_listFile.RemoveAll ();
}
