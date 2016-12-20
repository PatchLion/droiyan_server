// Store.h: interface for the CStore class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STORE_H__88D5E249_0673_4E53_BB8E_DA847DB3CFF1__INCLUDED_)
#define AFX_STORE_H__88D5E249_0673_4E53_BB8E_DA847DB3CFF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SharedMemory.h"
#include "MemUser.h"

struct GuildStoreInfo
{
	long	m_iGuildSid;		// 해당 길드 인덱스
	TCHAR	m_strGuildName[CHAR_NAME_LENGTH + 1]; // 해당 길드 이름
	TCHAR	m_strMasterName[CHAR_NAME_LENGTH + 1];// 해당 길드 짱 이름
	DWORD	m_iGuildDN;							  // 누적된 금액	

	BYTE	m_tWarType;							  // 0: 길드전 날짜 결정 12시간전 1: 이미 길드전 날짜가 결정	
	BYTE	m_tGuildWar;						  // 0 : 길드전 준비단계
											      // 1 : 길드전중
												  // 2 : 일반 단계
	SYSTEMTIME m_wLastWarTime;
	SYSTEMTIME m_wPlanWarTime;
};

struct AttckGuildList
{
	TCHAR GuildName[CHAR_NAME_LENGTH + 1];
	long	iGuildSid;
};

//typedef CTypedPtrArray <CPtrArray, AttckGuildList*>		AttGuildArray;

class CStore  
{
public:
	void GuildListToStr(TCHAR *pBuf);
	void StrToGuildList(TCHAR *pBuf);
	void InitStoreInfo(int sid);
	BOOL IsCanRepair(short sSid);
	int	 IsCanBuyPsi(CStore *pStore, int iClass);
	BOOL IsCanSell(short sSid);

public:
	BOOL IsCanBuy(short sSid);
	void SetGuildStoreTex();
	BOOL UpdateGuildStore();
	short	m_sStoreID;			// 상점 ID
	BYTE	m_tStoreType;		// 상점타입 - 0: 일반 아이템, 1: 사이오닉, 2: 메카닉 

	BOOL	m_bHaveGuild;		// 현재 길드에 속한 상점이다	TRUE	
	long	m_lUsed;			// 길드전 수행중인지 아닌지 표시...
	long	m_lAreaUsed;		// 길드전 수행지역을 표시함
	DWORD	m_dwStartTick;

	int		m_sRate;			// 시세

//	GuildStoreInfo	m_StoreInfo;
	long	m_iGuildSid;		// 해당 길드 인덱스
	TCHAR	m_strGuildName[CHAR_NAME_LENGTH + 1]; // 해당 길드 이름
	TCHAR	m_strMasterName[CHAR_NAME_LENGTH + 1];// 해당 길드 짱 이름
	DWORD	m_iGuildDN;							  // 누적된 금액	

	BYTE	m_tWarType;							  // 0: 길드전 날짜 결정 12시간전 1: 이미 길드전 날짜가 결정	
	BYTE	m_tGuildWar;						  // 0 : 길드전 준비단계
											      // 1 : 길드전중
												  // 2 : 일반 단계
	SYSTEMTIME m_wLastWarTime;
	SYSTEMTIME m_wPlanWarTime;

	int		m_iStandingTime;
	long	m_lListUsed;						  // 길드전에 참가하는 길드 리스트	
	long	m_lListCount;
	int		m_arAttackGuild[GUILD_ATTACK_MAX_NUM]; // 최대 20개의 길드가 전쟁에 참가할수 있다.

	CWordArray	m_arItems;			// 아이템 ID Array
	CWordArray	m_arSellList;		// 각 상점에서 구매하는 아이템 목록
	CWordArray	m_arRepairList;		// 각 상점에서 수리하는 아이템 목록

	CWordArray	m_arNpcList;

	CStore();
	~CStore();
};

#endif // !defined(AFX_STORE_H__88D5E249_0673_4E53_BB8E_DA847DB3CFF1__INCLUDED_)
