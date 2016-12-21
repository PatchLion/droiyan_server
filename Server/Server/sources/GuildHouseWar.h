// GuildHouseWar.h: interface for the CGuildHouseWar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUILDHOUSEWAR_H__410F61B7_AB0D_4522_8787_6DB5B8C76BBE__INCLUDED_)
#define AFX_GUILDHOUSEWAR_H__410F61B7_AB0D_4522_8787_6DB5B8C76BBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_GUILD_HOUSE_NUM	7
#define MAX_GUILD_APPLY_NUM 1

class COM;
class USER;

struct UserList
{
	int		uid;
	TCHAR	strUserName[CHAR_NAME_LENGTH + 1];	
};

struct	ApplyGuildHouseWar
{
	long	lUsed;				// 동기화를 맞추기위해...	
	long	lGuild;				// 길드번호	
	int		iCurValue;			// 현재 가중치
	DWORD	dwTimer;			// 시작시 셋팅
	DWORD	dwIntervalTick;		// 5분마다 체크

	int		iGuildLevel;		// 길드원 총 합산 레벨	

	int		iGuildNum;			// 총 참가 인원
	UserList	arUserList[MAX_GUILD_HOUSE_USER];	// 참가중인 유저 인덱스

	CWordArray	arNpcList;		// NPC 리스트	(초기에 셋팅)
	int			iWarZone;		// 초기에 존을 셋팅(존이 틀릴수 있다)
};

struct TopGuildList
{
	long	lGuild;
	int		iLastValue;

	int		iGuildNum;
	int		iGuildLevel;
	DWORD	dwLastTime;
	TCHAR	strGuildName[CHAR_NAME_LENGTH + 1];
};

//typedef CTypedPtrArray <CPtrArray, ApplyGuildHouseWar*>	GuildHouseWarList;

class CGuildHouseWar  
{
public:
	int		m_iCity;	// 해당 도시를 셋팅		
public:	
	void ResetGuildHouseRank();
	void SendTownPotalMsg(COM *pCom);
	//void SetUserListToWarEnd(USER** user_array);	
	void SetUserListToWarEnd();	

	void SetUserListToWarEnd(COM *pCom);
	void SetNpcListToWarEnd();
	void SwapTopGuildList(TopGuildList &s, TopGuildList &d);
	BOOL CheckGuildMopEnd();
	void CheckGuildUserEnd();
	void CheckGuildHouseRank();
	BOOL CheckGuildHouseWarEnd(USER** user_array);
	void InitGuild();
						// 하나의 도시에 하나의 길드전 맵 대응		
	ApplyGuildHouseWar	m_CurrentGuild;//[MAX_GUILD_APPLY_NUM];
	TopGuildList		m_TopList[MAX_GUILD_HOUSE_NUM];	// 상위 길드리스트	

	CGuildHouseWar();
	virtual ~CGuildHouseWar();

};

#endif // !defined(AFX_GUILDHOUSEWAR_H__410F61B7_AB0D_4522_8787_6DB5B8C76BBE__INCLUDED_)
