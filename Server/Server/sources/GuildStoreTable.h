// GuildStoreTable.h: interface for the CGuildStoreTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUILDSTORETABLE_H__F712EC70_85B1_450C_B2E7_BD6C710FD3D2__INCLUDED_)
#define AFX_GUILDSTORETABLE_H__F712EC70_85B1_450C_B2E7_BD6C710FD3D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGuildStoreTable  
{
public:
	CGuildStoreTable();
	virtual ~CGuildStoreTable();

public:
	int		m_sStoreID;
	long	m_iGuildSid;
	TCHAR	m_strGuildName[CHAR_NAME_LENGTH + 1];
	TCHAR	m_strMasterName[CHAR_NAME_LENGTH + 1];
	BYTE	m_tTaxRate;
	DWORD	m_iGuildDN;

	BYTE	m_tWarType;	
	int		m_wDay;
	int		m_wHour;
	int		m_wMinute;

	int		m_wWarMon;
	int		m_wWarDay;
	int		m_wWarHour;
	int		m_wWarMinute;

	int		m_wWarPlanMon;
	int		m_wWarPlanDay;
	int		m_wWarPlanHour;
	int		m_wWarPlanMinute;
};

#endif // !defined(AFX_GUILDSTORETABLE_H__F712EC70_85B1_450C_B2E7_BD6C710FD3D2__INCLUDED_)
