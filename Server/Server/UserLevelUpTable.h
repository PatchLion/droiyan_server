// UserLevelUpTable.h: interface for the CUserLevelUpTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERLEVELUPTABLE_H__9B4BBFC1_B5E0_473C_AB0A_1DCDA91B1FF3__INCLUDED_)
#define AFX_USERLEVELUPTABLE_H__9B4BBFC1_B5E0_473C_AB0A_1DCDA91B1FF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUserLevelUpTable  
{
public:
	CUserLevelUpTable();
	virtual ~CUserLevelUpTable();

	int		m_sLevel;
	int		m_sHP;
	int		m_sPP;
	int		m_sDamage;
	int		m_sDefense;
	int		m_sWeight;
};

#endif // !defined(AFX_USERLEVELUPTABLE_H__9B4BBFC1_B5E0_473C_AB0A_1DCDA91B1FF3__INCLUDED_)
