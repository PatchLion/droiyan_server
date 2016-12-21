// BufferEx.h: interface for the CBufferEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUFFEREX_H__B811058F_9B70_4D42_8A2F_B0F9028F2BDC__INCLUDED_)
#define AFX_BUFFEREX_H__B811058F_9B70_4D42_8A2F_B0F9028F2BDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define AddString(p) Add(p, _tcslen(p))

class CBufferEx  
{
public:
	void AddData(TCHAR* pBuf, int nLength);
	void AddLongString(TCHAR* pBuf, int nLength);
	int GetLength();
	void Add(DWORD nVal);
	void Add(WORD nVal);
	void Add(short nVal);
	void Add(int nVal);
	void Add(TCHAR* pBuf, int nLength);
	void Add(BYTE ch);

	CBufferEx(int nSize = SEND_BUF_SIZE);
	virtual ~CBufferEx();

	inline operator LPTSTR()
	{
		return m_pData;
	}
	
private:
	TCHAR*	m_pData;
	UINT	m_nIndex;
	UINT	m_nSize;
};

#endif // !defined(AFX_BUFFEREX_H__B811058F_9B70_4D42_8A2F_B0F9028F2BDC__INCLUDED_)
