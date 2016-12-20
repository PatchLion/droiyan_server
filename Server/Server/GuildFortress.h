// GuildFortress.h: interface for the CGuildFortress class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUILDFORTRESS_H__42E14E0C_5B21_430C_9A03_60CC86DD6BB3__INCLUDED_)
#define AFX_GUILDFORTRESS_H__42E14E0C_5B21_430C_9A03_60CC86DD6BB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNpc;
class COM;
class USER;

struct ApplyGuildList
{
	long	lUsed;
	long	lGuild;	
	TCHAR	strGuildName[CHAR_NAME_LENGTH + 1];
};

struct TargetNpcList
{
	long	lUsed;								// 초기 셋팅시 NPC Thread간의 동기화를 위해
	short	sTargertID;
};

struct RepairNpcList
{
	short	sUid;								// sEZone에 셋팅된 유일한값
	short	sNid;								// 
	short	sHP;								// 현재 HP를 저장
};

struct MsgList
{
	int		iUsed;
	int		iMsgTime;
};

struct FortressCityList
{
	long	lUsed;
	long	lCityRank;
	TCHAR	strUserID[CHAR_NAME_LENGTH + 1];
};

class CGuildFortress  
{
public:
//	int		m_iCityDegree;
	int		m_sFortressID;	
	long	m_iGuildSid;
	DWORD	m_dwRepairCost;

	TCHAR	m_strGuildName[CHAR_NAME_LENGTH + 1];
	TCHAR	m_strMasterName[CHAR_NAME_LENGTH + 1];

	BYTE		m_tTaxRate;						  // 포트리스가 소유한 상점들에 세금을 적용한다.
	CWordArray	arStoreTax;						  // 상점 리스트	

	DWORD	m_iGuildDN;

	BYTE	m_tWarType;							  // 0: 길드전 날짜 결정 12시간전 1: 이미 길드전 날짜가 결정	
	BYTE	m_tGuildWar;						  // 0 : 길드전 준비단계
											      // 1 : 길드전중
												  // 2 : 일반 단계
	SYSTEMTIME m_wLastWarTime;
	SYSTEMTIME m_wPlanWarTime;

	DWORD	m_dwStartTick;
	int		m_iStandingTime;
	int		m_iEndingTime;

	BOOL	m_bHaveGuild;						  // 현재 길드에 속한 Fortress = TRUE	
	long	m_lUsed;							  // 길드전 수행중인지 아닌지 표시...
	long	m_lChangeUsed;						  // 주인이 바뀌는 시점에서 잠깐 멈춘다.	

	long	m_lListUsed;						  // 몹끼리 셋팅시 동기화를 위해
	long	m_lListCount;						  // 리스트 인덱스		
														
	ApplyGuildList	m_arAttackGuild[GUILDFORTRESS_ATTACK_MAX_NUM];// 길드전에 참가하는 길드 리스트	
	TargetNpcList	m_arFortressTarget[FORTRESS_TARGET_MAX_NUM]; // 4개의 N_Circle오델로가 있다.
	RepairNpcList	m_arRepairDBList[GUILD_REPAIR_MAX_NUM]; // 공성전시 수리될 필요가 있는 NPC를 저장
	int				m_iGuardList[GUILD_GUARD_MAX_NUM];

	CWordArray		m_arRepairNpcList;	
	CWordArray		m_arNpcList;
	CWordArray		m_arWarNpcList;
	CWordArray		m_arViolenceNpcList;

public:
	long			 m_lViolenceUsed;	
	FortressCityList m_arCityRankList[MAX_GUILD_USER];
	SYSTEMTIME		 m_wMopPartyTime;
	DWORD			 m_dwViolenceTick;

public:	
	MsgList	m_MsgTimer[GUILD_WAR_MAX_MSG_TIMER];
	int		m_iZone;							  // 성에 속한 존(타운 포탈에 이용한다)
	int		m_iPotalX;
	int		m_iPotalY;

public:
	void GetOutof(COM *pCom);
	void SetInitFortressViolence();
	BOOL SetNpcToFortressViolenceEnd(COM *pCom);
	void SetNpcToFortressViolenceBegin();//(COM *pCom);
	void AddGuildUserForFortressCityRank(TCHAR *strUserID, int sCityRank);
	int GetTotalCityValue();
	void ApplyTaxToStore();
	void SetInitFortress();
	void InitMemFortress(BYTE tGuildWarType);
	void UpdateInitFortress();
	void InitMsgTime();
	void StrFortressRepairList(CByteArray &Buf);
//	void StrFortressRepairList(TCHAR *pBuf);
	void FortressRepairListToStr(TCHAR *pBuf);
	void SetNpcToFortressWarEnd(COM *pCom);
	CNpc* GetNpc(int nid);
	void SetNpcToFortressWarBegin();
	void GuildGuardListToStr(TCHAR *pBuf);
	void GuildAttListToStr(TCHAR*pBuf);
	void StrGuildGuardList(TCHAR *pBuf);
	void StrToGuildAttList(TCHAR *pBuf, int iguild);

	CGuildFortress();
	virtual ~CGuildFortress();

};

#endif // !defined(AFX_GUILDFORTRESS_H__42E14E0C_5B21_430C_9A03_60CC86DD6BB3__INCLUDED_)
