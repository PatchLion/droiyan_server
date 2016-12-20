// ItemTable.h: interface for the CItemTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMTABLE_H__B000F7FB_9D51_4A8A_A5C5_2342982FB23D__INCLUDED_)
#define AFX_ITEMTABLE_H__B000F7FB_9D51_4A8A_A5C5_2342982FB23D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CItemTable  
{
public:
	short	m_sSid;
	short	m_sPid;
	CString	m_strName;
	CString	m_strText;
	BYTE	m_byWeight;
	DWORD	m_iDN;
	BYTE	m_byRLevel;
	BYTE	m_byClass;
	BYTE	m_byWear;
	short	m_sDuration;
	short	m_sDefense;
	BYTE	m_byAX;
	BYTE	m_byAY;
	BYTE	m_byAZ;
	BYTE	m_byRstr;
	BYTE	m_byRdex;
	BYTE	m_byRvol;
	short	m_sAttackDelay;
	BYTE	m_byRange;
	BYTE	m_byErrorRate;
	short	m_sBullNum;
	BYTE	m_byBullType;
	BYTE	m_bySubDefense;
	BYTE	m_bySubCure;
	short	m_sRepairHP;
	short	m_sRepairPP;
	short	m_sRepairSP;
	short	m_sEvent;
	short	m_sZone;
	BYTE	m_byMPP;
	short	m_sCTime;
	BYTE	m_bySpecial;

	CItemTable();
	~CItemTable();
};

#endif // !defined(AFX_ITEMTABLE_H__B000F7FB_9D51_4A8A_A5C5_2342982FB23D__INCLUDED_)
