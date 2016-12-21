// BufferEx.cpp: implementation of the CBufferEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Server.h"
#include "BufferEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBufferEx::CBufferEx(int nSize)
{
	m_pData = new TCHAR [nSize];
	::ZeroMemory(m_pData, nSize);

	m_nIndex = 0;
	m_nSize = nSize;
}

CBufferEx::~CBufferEx()
{
	delete[] m_pData;
}

void CBufferEx::AddData(TCHAR *pBuf, int nLength)
{
	if(nLength < 0) return;
	if(m_nIndex >= m_nSize) return;

	::CopyMemory(m_pData + m_nIndex, pBuf, nLength);
	m_nIndex += nLength;
}

void CBufferEx::AddLongString(TCHAR *pBuf, int nLength)
{
	if(nLength < 0) return;
	if(m_nIndex >= m_nSize) return;

	short temp = (short) nLength;
	::CopyMemory(m_pData + m_nIndex, &temp, sizeof(short));
	m_nIndex += sizeof(short);

	::CopyMemory(m_pData + m_nIndex, pBuf, nLength);
	m_nIndex += nLength;
}

void CBufferEx::Add(TCHAR *pBuf, int nLength)
{
	if(nLength < 0) return;
	if(m_nIndex >= m_nSize) return;

	if(nLength <= 256)
	{
		*(m_pData + m_nIndex) = (TCHAR) nLength;
		m_nIndex++;
		::CopyMemory(m_pData + m_nIndex, pBuf, nLength);
		m_nIndex += nLength;
	}
	else 
	{
		//ASSERT(!"Too Big String!!!");

	}
}

void CBufferEx::Add(BYTE ch)
{
	if(m_nIndex >= m_nSize) return;

	*(m_pData + m_nIndex) = (TCHAR)ch;
	m_nIndex++;
}

void CBufferEx::Add(WORD nVal)
{
	if(m_nIndex >= m_nSize) return;

	::CopyMemory(m_pData + m_nIndex, &nVal, sizeof(WORD));
	m_nIndex += sizeof(WORD);
}

void CBufferEx::Add(short nVal)
{
	if(m_nIndex >= m_nSize) return;

	::CopyMemory(m_pData + m_nIndex, &nVal, sizeof(short));
	m_nIndex += sizeof(short);
}

void CBufferEx::Add(int nVal)
{
	if(m_nIndex >= m_nSize) return;

	::CopyMemory(m_pData + m_nIndex, &nVal, sizeof(int));
	m_nIndex += sizeof(int);
}

void CBufferEx::Add(DWORD nVal)
{
	if(m_nIndex >= m_nSize) return;

	::CopyMemory(m_pData + m_nIndex, &nVal, sizeof(DWORD));
	m_nIndex += sizeof(DWORD);
}

int CBufferEx::GetLength()
{
	return m_nIndex;
}
