// SharedMemory.cpp: implementation of the CSharedMemory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SharedMemory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSharedMemory::CSharedMemory()
{
	m_lpData	= NULL;
	m_hMapping	= NULL;
	m_nSize		= 0;
}

CSharedMemory::CSharedMemory(UINT nSize, LPCTSTR pszName)
{
	m_lpData	= NULL;
	m_hMapping	= NULL;
	m_nSize		= 0;

	if(!Create(nSize, pszName)) AfxThrowMemoryException();
}

CSharedMemory::~CSharedMemory()
{
	Delete();
}

BOOL CSharedMemory::Create (UINT nSize, LPCTSTR pszName)
{
	HANDLE hMapping = ::CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE,	0, nSize, pszName);
	if(hMapping == NULL || hMapping == INVALID_HANDLE_VALUE) return FALSE;

	LPVOID pVoid = ::MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0,	0);
	if(pVoid == NULL)
	{
		::CloseHandle(hMapping);
		return FALSE;
	}

	m_hMapping = hMapping;
	m_lpData = pVoid;
	m_nSize = nSize;

	return TRUE;
}

void CSharedMemory::Delete()
{
	if(m_lpData != NULL)
	{
		::FlushViewOfFile(m_lpData, 0);
		::UnmapViewOfFile(m_lpData);
		m_lpData = NULL;
	}
	
	if(m_hMapping != NULL)
	{
		::CloseHandle(m_hMapping);
		m_hMapping = NULL;
	}

	m_nSize	= 0;
}

BOOL CSharedMemory::Open(LPCTSTR szName, UINT nSize, BOOL bReadOnly)
{
	DWORD dwDesiredAccess = bReadOnly ? FILE_MAP_READ : FILE_MAP_WRITE;
	HANDLE hMapping = ::OpenFileMapping(dwDesiredAccess, 0, szName);

	if(hMapping == NULL)
	{
		TRACE(_T("Failed in call to OpenFileMapping, GetLastError returned %d\n"), GetLastError());
	    return FALSE;
	}

	LPVOID lpVoid = ::MapViewOfFile(hMapping, dwDesiredAccess, 0, 0, nSize);
	if(lpVoid == NULL)
	{
		TRACE(_T("Failed in call to MapViewOfFile, GetLastError returned %d\n"), GetLastError());
		::CloseHandle(hMapping);
		return FALSE;
	}

	m_hMapping = hMapping;
	m_lpData = lpVoid;

	return TRUE;
}