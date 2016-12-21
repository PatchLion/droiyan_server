// Guild.h: interface for the CGuild class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUILD_H__5B1C220E_3EE8_4D66_8869_26E959393574__INCLUDED_)
#define AFX_GUILD_H__5B1C220E_3EE8_4D66_8869_26E959393574__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Map.h"
#include "GuildUser.h"

//typedef CTypedPtrArray <CPtrArray, CGuildUser*> GuildUserArray;

class CGuild  
{
public:
//	void RemoveUser(TCHAR *userID);
//	CGuildUser* GetUser(TCHAR *userID);
	BOOL AddUser(TCHAR *userID, int iGuildID);
	BOOL RemoveUser(TCHAR *userID);
	int  GetUser(TCHAR *userID);
	void GuildMapToStr(TCHAR *pBuf);
	void strToGuildMap(TCHAR *pBuf);
	void StrToGuildItem(TCHAR *pBuf);
	void GuildItemToStr(TCHAR *pBuf);
	void SetSubGuildMaster(TCHAR *strName);
	void RemoveSubGuildMaster();

	CGuild();
	virtual ~CGuild();

public:
	BOOL CheckGuildSubMaster();
	BOOL IsMasterPower(TCHAR *strUserID);
	void InitGuild();
	long		m_lSid;
	long		m_lUsed;

	int			m_iUsedUser;
	TCHAR		m_strUsedUser[CHAR_NAME_LENGTH+1];
	TCHAR		m_strGuildName[CHAR_NAME_LENGTH + 1];
	TCHAR		m_strMasterName[CHAR_NAME_LENGTH + 1];
	TCHAR		m_strSubMasterName[CHAR_NAME_LENGTH + 1];

	long		m_lSubMaster;
	BYTE		m_strMark[GUILD_MARK_SIZE];
	short		m_sVersion;
	DWORD		m_dwGuildDN;
	ItemList	m_UserGuildItem[TOTAL_BANK_ITEM_NUM];// User Bank Item DB

	DWORD		m_dwHaveMap[GUILD_MAP_COUNT];	//	40
//	DWORD		m_dwExp;

//	GuildUserArray	m_arUser;
	CGuildUser	m_arUser[MAX_GUILD_USER];
};

#endif // !defined(AFX_GUILD_H__5B1C220E_3EE8_4D66_8869_26E959393574__INCLUDED_)
