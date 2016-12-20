// Msg.cpp: implementation of the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CMsg::ReadData (void* pData, int n)
{
	if (m_nRdOff + n + 4 > DEFAULT_SIZE)
		return;

	memcpy (pData, m_pData + m_nRdOff, n);
	m_nRdOff += n;
}

void CMsg::WriteData (void* pData, int n)
{

	memcpy (m_pData + m_nWrOff, pData, n);
	m_nWrOff += n;
	memcpy (m_pHead + 2, &m_nWrOff, 2);
}

CMsg::CMsg()
{
	m_pHead = m_buf;
	m_pData = m_pHead + 4;
	m_nRdOff = m_nWrOff = 0;
	m_pHead[2] = m_pHead[3] = 0;
}

CMsg::CMsg(CMsg& VEPMsg)
{
	m_pHead = m_buf;
	m_pData = m_pHead + 4;
	m_nRdOff = 0;
	m_nWrOff = VEPMsg.m_nWrOff;
	memcpy (m_pHead, VEPMsg.m_pHead, DEFAULT_SIZE);
}

CMsg::CMsg(void* pBuf)
{
	m_pHead = m_buf;
	m_pData = m_pHead + 4;
	m_nRdOff = 0;
	m_nWrOff = *((WORD*)((BYTE*)pBuf + 2));
	memcpy (m_pHead, pBuf, m_nWrOff + 4);
}

CMsg& CMsg::ID( WORD id )
{
	memcpy (m_pHead, &id, sizeof (WORD));
	m_pHead[2] = 0;
	m_pHead[3] = 0;
	m_nRdOff = m_nWrOff = 0;

	return *this;
}

WORD CMsg::ID()
{
	return *((WORD*)m_pHead);
}

void* CMsg::GetBuf ()
{
	return (void*)m_pHead;
}

void CMsg::SetBuf (BYTE* pBuf)
{
	m_pHead = pBuf;
	m_pData = pBuf + 4;
}

WORD CMsg::GetSize ()
{
	return *((WORD*)(m_pHead + 2)) + 4;
}

BOOL CMsg::IsReadAll ()
{
	return (GetSize () - 4 <= m_nRdOff);
}

void CMsg::Copy(void* pBuf)
{
	m_nRdOff = 0;
	m_nWrOff = *((WORD*)((BYTE*)pBuf + 2));
	memcpy (m_pHead, pBuf, m_nWrOff + 4);
}

CMsg& CMsg::operator<<( char arg )
{
	WriteData (&arg, 1);
	return *this;
}

CMsg& CMsg::operator<<( BYTE arg )
{
	WriteData (&arg, 1);
	return *this;
}

CMsg& CMsg::operator<<( short arg )
{
	WriteData (&arg, 2);
	return *this;
}

CMsg& CMsg::operator<<( WORD arg )
{
	WriteData (&arg, 2);
	return *this;
}

CMsg& CMsg::operator<<( int	arg )
{
	WriteData (&arg, 4);
	return *this;
}

CMsg& CMsg::operator<<( DWORD arg )
{
	WriteData (&arg, 4);
	return *this;
}

CMsg& CMsg::operator<<( LPCTSTR	arg )
{
	short nLen = (short)strlen (arg);
	WriteData (&nLen, 2);
	WriteData ((void*)arg, nLen);
	return *this;
}

CMsg& CMsg::operator>>( char& arg )
{
	ReadData (&arg, 1);
	return *this;
}

CMsg& CMsg::operator>>( BYTE& arg )
{
	ReadData (&arg, 1);
	return *this;
}

CMsg& CMsg::operator>>( short& arg )
{
	ReadData (&arg, 2);
	return *this;
}

CMsg& CMsg::operator>>( WORD&	arg )
{
	ReadData (&arg, 2);
	return *this;
}

CMsg& CMsg::operator>>( int& arg )
{
	ReadData (&arg, 4);
	return *this;
}

CMsg& CMsg::operator>>( DWORD& arg )
{
	ReadData (&arg, 4);
	return *this;
}

CMsg& CMsg::operator>>( CString& arg )
{
	short nLen;
	char *string;

	ReadData(&nLen, 2);
	string = new char[nLen+1];
	ReadData(string, nLen);
	string[nLen] = 0;
	arg = string;
	delete[] string;
	
	return *this;
}

CMsg& CMsg::operator=( CMsg& VEPMsg )
{
	memcpy (m_pHead, VEPMsg.m_pHead, DEFAULT_SIZE);
	m_nRdOff = VEPMsg.m_nRdOff;
	m_nWrOff = VEPMsg.m_nWrOff;
	return *this;
}
