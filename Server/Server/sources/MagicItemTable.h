// MagicItemTable.h: interface for the CMagicItemTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAGICITEMTABLE_H__B8250F29_A0D3_45EA_B6DB_942F89F7074A__INCLUDED_)
#define AFX_MAGICITEMTABLE_H__B8250F29_A0D3_45EA_B6DB_942F89F7074A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMagicItemTable  
{
public:
	int GetMagicItemValue();
	CMagicItemTable();
	virtual ~CMagicItemTable();

	short	m_sSid;
	short	m_sSubType;
	short	m_sChangeValue;
	BYTE	m_tUpgrade;
	BYTE	m_tNeedClass;
	BYTE	m_tWearInfo;
	BYTE	m_tLevel;

	BYTE	m_tUse;

	BYTE	m_sAid;
};

#endif // !defined(AFX_MAGICITEMTABLE_H__B8250F29_A0D3_45EA_B6DB_942F89F7074A__INCLUDED_)
