// SharedMemory.h: interface for the CSharedMemory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAREDMEMORY_H__E4CFD1A7_91B9_4A93_9E85_7C5583208794__INCLUDED_)
#define AFX_SHAREDMEMORY_H__E4CFD1A7_91B9_4A93_9E85_7C5583208794__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSharedMemory  
{
public:
	CSharedMemory(UINT nSize, LPCTSTR pszName);
	CSharedMemory();

	virtual ~CSharedMemory();

	BOOL Create (UINT nSize, LPCTSTR pszName = NULL);
	void Delete();
	BOOL Open(LPCTSTR szName, UINT nSize, BOOL bReadOnly = FALSE);

	LPVOID	m_lpData;
	HANDLE	m_hMapping;
	UINT	m_nSize;
};

#endif // !defined(AFX_SHAREDMEMORY_H__E4CFD1A7_91B9_4A93_9E85_7C5583208794__INCLUDED_)
