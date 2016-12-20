// MemUser.h: interface for the CMemUser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMUSER_H__A2D30C97_9428_4023_80A4_664B2B403E04__INCLUDED_)
#define AFX_MEMUSER_H__A2D30C97_9428_4023_80A4_664B2B403E04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MemDefine.h"


class CMemGuildHouseRank
{
public:
	CMemGuildHouseRank();
	~CMemGuildHouseRank();

	BYTE	tSid;	
	int		lGuild;
	BYTE	iGuildNum;
	short	iLastValue;
	short	iGuildLevel;
	DWORD	dwLastTime;
};

class CMemFortress
{
public:
	CMemFortress();
	~CMemFortress();

	short	m_sFortressID;
	int		m_iGuildSid;

	short	m_sTaxRate;
	DWORD	m_dwStoreDN;
	BYTE	m_tWarType;

	TCHAR	m_AttackList[_GUILDLIST_DB];
	TCHAR	m_RepairList[_GUILDREPAIRLIST_DB];
};

class CMemStore
{
public:
	CMemStore();
	~CMemStore();

	short	m_sStoreID;						// 상점 인덱스
	int		m_iGuildSid;					// 상점을 소유한 길드 인덱스

	short	m_sTaxRate;						// 세금
	DWORD	m_dwStoreDN;					// 누적 값
	BYTE	m_tWarType;						// 길드전 시기 결정 플래그

	TCHAR	m_AttackList[_GUILDLIST_DB];	// 길드전을 신청한 길드 리스트
};

class CMemBank
{
public:
	CMemBank();
	~CMemBank();

	int		m_uid;

	TCHAR	m_strUserID[CHAR_NAME_LENGTH + 1];	// 아이디(캐릭터 이름)
	TCHAR	m_UserBankItem[_BANK_DB];		// 은행내 아이템
	DWORD	m_dwBankDN;						// User Bank DN
};

class CMemAccountBank
{
public:
	CMemAccountBank();
	~CMemAccountBank();

	int		m_uid;

	TCHAR	m_strAccount[CHAR_NAME_LENGTH + 1];	// 아이디(캐릭터 이름)
	TCHAR	m_AccountBankItem[_ACCOUNT_BANK_DB];// 은행내 아이템
	DWORD	m_dwBankDN;							// User Bank DN
};

typedef struct _ITEMLOG
{
	CTime	t;
	short	m_sLogType;
	char	m_strUserId[CHAR_NAME_LENGTH + 1];		// 행위 주체
	char	m_strEtc[CHAR_NAME_LENGTH + 1];			// 관련자

	short	m_sLevel;
	short	m_sSid;
	short	m_sDuration;
	short	m_sBullNum;
	short	m_sCount;
	BYTE	m_tMagic[11];
	BYTE	m_tIQ;

	UINT64	m_iItemSerial;

	DWORD	m_dwResultDN;
	DWORD	m_dwInOutDN;
	DWORD	m_dwRelateDN;
} ITEMLOG;

class CMemUser  
{
public:
	CMemUser();
	~CMemUser();

	CMemBank	m_UB;
	CMemAccountBank m_AB;

	int			m_uid;					// Server User id

	TCHAR		m_strAccount[CHAR_NAME_LENGTH + 1];
	TCHAR		m_strUserID[CHAR_NAME_LENGTH + 1];	// 아이디(캐릭터 이름)
	
	//-- yskang 0.1 길드에게 호칭부여....
	TCHAR m_strLoveName[LOVE_NAME_LENGTH+1];

	DWORD		m_dwSaveTime;			// 년 4, 월 4, 일 5, 시 5, 분 6, 초 6 BYTE	

	short		m_sSTR;					// 힘
	short		m_sCON;					// 건강
	short		m_sDEX;					// 민첩성
	short		m_sVOL;					// 의지
	short		m_sWIS;					// 지혜
	
	DWORD		m_iSkin;				// 피부색
	DWORD		m_iHair;				// 머리색
	short		m_sGender;				// 성별
	TCHAR		m_strFace[10];			// 얼굴모양

	int			m_curx;					// 현재 X 좌표
	int			m_cury;					// 현재 Y 좌표
	int			m_curz;					// 현재 존

	DWORD		m_dwBuddy;				// 버디번호
	long		m_dwGuild;				// 길드번호

	DWORD	m_dwExp;				// 레벨경험치

	short		m_sPA;					// PA Point
	short		m_sSkillPoint;			// Skill Point
	
	DWORD		m_dwXP;					// X Point

	short		m_sMaxHP;				// 최대 HP
	short		m_sHP;					// 현재 HP
	short		m_sMaxPP;				// 최대 PP
	short		m_sPP;					// 현재 PP
	short		m_sMaxSP;				// 최대 SP
	short		m_sSP;					// 현재 SP

	DWORD		m_dwDN;					// 소지금

	short		m_sCityRank;			// 시민 등급
	short		m_sKillCount;			// PK한 횟수

	short		m_sLevel;				// 계열레벨
	BYTE		m_byClass;				// 클래스

	TCHAR		m_strSkill[_SKILL_DB];	// User Skill DB
	TCHAR		m_strItem[_ITEM_DB];	// User Item DB
	TCHAR		m_strPsi[_PSI_DB];		// User Psionic DB
	TCHAR		m_strHaveEvent[_EVENT_DB];// User Event DB
	TCHAR		m_strTel[_TEL_DB];		// User Tel DB

	short		m_sChangeClass[_CHANGE_DB];		// 전직시 클래스레벨 저장

	BYTE		m_tAbnormalKind;				// 상태이상 종류
	DWORD		m_dwAbnormalTime;				// 상태이상 걸린후 남은 시간
	
	TCHAR		m_strQuickItem[_QUICKITEM_DB];	// Quick Item Index
	
	BYTE		m_tIsOP;					// 운영자인지 판단
											// 0: Normal User
											// 1: Game Operator
											// 2: Server Operator

	BYTE		m_bLive;				// 죽었니? 살았니?

	BYTE		m_sTempSTR;				// 힘
	BYTE		m_sTempCON;				// 건강
	BYTE		m_sTempDEX;				// 민첩성
	BYTE		m_sTempVOL;				// 의지
	BYTE		m_sTempWIS;				// 지혜

	int			m_iCityValue;			// 현재 누적 성향값

	DWORD		m_dwSaintTime;

	DWORD		m_dwHiExpTime;			// 경험치 2배 물약을 먹은후 남은 시간 
	DWORD		m_dwMagicFindTime;		// 매직찬스 5배 물약을 먹은후 남은 시간
	DWORD		m_dwNoChatTime;			// 채금을 먹은후 남은 시간

	BYTE		m_tPsiOneKind;			
	BYTE		m_tPsiTwoKind;
	BYTE		m_tPsiThreeKind;
	
	DWORD		m_dwPsiOneTime;
	DWORD		m_dwPsiTwoTime;
	DWORD		m_dwPsiThreeTime;
	DWORD       m_dwBSTime;
	DWORD       m_dwDNMoney;

	char		m_arItemLogData[100][sizeof(ITEMLOG)];	// 아이템 로깅
	
	int			m_iMyServer;			// 지금 접속한 서버 인덱스
};

#endif // !defined(AFX_MEMUSER_H__A2D30C97_9428_4023_80A4_664B2B403E04__INCLUDED_)
