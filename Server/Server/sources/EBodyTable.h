// EBodyTable.h: interface for the CEBodyTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EBODYTABLE_H__59A1C67E_8F9D_43A1_BC80_F9766EC5B86B__INCLUDED_)
#define AFX_EBODYTABLE_H__59A1C67E_8F9D_43A1_BC80_F9766EC5B86B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEBodyTable  
{
public:
	CEBodyTable();
	virtual ~CEBodyTable();

public:
	short	m_sChangeValue;
	short	m_sRandom;
	short	m_sSubType;
	BYTE	m_tLevel;
	BYTE	m_tNeedClass;
	BYTE	m_tSid;
	BYTE	m_tUpgrade;
	BYTE	m_tWearInfo;
};

#endif // !defined(AFX_EBODYTABLE_H__59A1C67E_8F9D_43A1_BC80_F9766EC5B86B__INCLUDED_)
