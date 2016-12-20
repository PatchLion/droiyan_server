// AccessoriUpTable.h: interface for the CAccessoriUpTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCESSORIUPTABLE_H__70323D5B_2930_4873_BF22_52D1BA6EBE7E__INCLUDED_)
#define AFX_ACCESSORIUPTABLE_H__70323D5B_2930_4873_BF22_52D1BA6EBE7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRipel
{
public:
	CWordArray	m_arRipelTop;
	CWordArray	m_arRipelBottom;
	CWordArray	m_arRipelLeft;
	CWordArray	m_arRipelRight;
	CWordArray	m_arRipelCrest;

	CRipel();
	~CRipel();
};

class CAccessoriUpTable  
{
public:
	CAccessoriUpTable();
	virtual ~CAccessoriUpTable();

	int		m_sAid;
	int		m_sSid;
	BYTE	m_tType;
	BYTE	m_tGroup;
};

#endif // !defined(AFX_ACCESSORIUPTABLE_H__70323D5B_2930_4873_BF22_52D1BA6EBE7E__INCLUDED_)
