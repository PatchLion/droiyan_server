// LOGIC.h: interface for the LOGIC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGIC_H__7514FC24_511B_11D3_BE41_00105A6B97E2__INCLUDED_)
#define AFX_LOGIC_H__7514FC24_511B_11D3_BE41_00105A6B97E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class LOGIC  
{
public:
	void Init();
	BYTE m_Logic;

	int m_LogicInt[MAX_LOGIC_INT];

	char m_LogicChar[MAX_LOGIC_CHAR_LEN+1];

	void Parse(char* pBuf);
	LOGIC();
	virtual ~LOGIC();

};

#endif // !defined(AFX_LOGIC_H__7514FC24_511B_11D3_BE41_00105A6B97E2__INCLUDED_)
