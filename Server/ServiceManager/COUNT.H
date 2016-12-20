// Count.h: interface for the CCount class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COUNT_H__C95DC847_6183_11D2_A57C_00A0248552AD__INCLUDED_)
#define AFX_COUNT_H__C95DC847_6183_11D2_A57C_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCount : public CObject  
{
public:
	CTime m_time;
	int m_nNum;
	int m_nUserNum;
	CCount(int nNum);
};

#endif // !defined(AFX_COUNT_H__C95DC847_6183_11D2_A57C_00A0248552AD__INCLUDED_)
