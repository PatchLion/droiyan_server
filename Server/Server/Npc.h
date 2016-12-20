// Npc.h: interface for the CNpc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPC_H__600048EF_818F_40E9_AC07_0681F5D27D32__INCLUDED_)
#define AFX_NPC_H__600048EF_818F_40E9_AC07_0681F5D27D32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "COM.h"
#include "Map.h"

#include "Packet.h"
#include "PathFind.h"
#include "Store.h"
#include "GuildFortress.h"
#include "EventItemNew.h"

#define CHANGE_PATH_STEP	2
#define CHANGE_PATH_RANGE	2
#define RANDOM_MOVE_LENGTH	10
#define	NPC_ITEM_BAND		2000

#define NPCTYPE_MONSTER		0
#define NPCTYPE_NPC			1
#define NPCTYPE_DOOR		2
#define NPCTYPE_GUARD		3			// 붙박이형 경비병
#define MPCTYPE_GUARD_MOVE	4			// 돌아다니는 경비병
#define NPCTYPE_GUILD_NPC	5			// 일반 필드에서 물건을 거래하는 NPC 
#define NPCTYPE_GUILD_GUARD	6			// 일반 필드에서 상점주변을 보호하는 경비병
#define NPCTYPE_GUILD_MARK	7			// 각 길드하우스에 있는 길드마크 NPC
#define NPCTYPE_GUILD_DOOR	8			// 공성전에서 쓰이는 문

#define GUILD_REPAIR_NPC_BAND	20000	// 손상되어 수리가 필요한 NPC
#define GUILD_FORTRESS_NPC_BAND	25000	// 성을 점령하는데 필요한 NPC

#define MAX_MAP_SIZE		10000		//@@@@@@@@@@@@@@@@@@@@@@@@@@@22
#define MAX_PATH_SIZE		100

#define NPC_ITEM_NUM		5

#define NPC_ATTACK_SHOUT	0
#define NPC_SUBTYPE_LONG_MON 1

#define NPC_TRACING_STEP	100

#define NPC_HAVE_USER_LIST	10

#define NPC_QUEST_MOP		 10000		// 퀘스트용 몹( 1 ~ 10000 )으로 사용 
#define NPC_EVENT_MOP		 31000		// 이벤트 몹 번호
#define NPC_EVENT_GREATE_MOP 30000		// 특 이벤트 몬스터 번호
#define NPC_MAGIC_ITEM		 500	// 1~10000번을 기준
#define NPC_RARE_ITEM		 2500
#define NPC_EVENT_CHANCE	40			// 이벤트 몹일경우 매직확률과 레어 확률울 올려준다. X 40 

/*
#define NPC_EVENT_MOON		620			// 보름달 드롭확율
#define NPC_EVENT_SONGPEON	920			// 송편/월병 드로확율
#define NPC_EVENT_BOX		1420		// 선물상자 드롭확율

#define EVENTITEM_SID_MOON			862	// 보름달	Sid
#define EVENTITEM_SID_SONGPEON_01	863	// 송편		Sid
#define EVENTITEM_SID_SONGPEON_11	864	//
#define EVENTITEM_SID_SONGPEON_31	865	//
#define EVENTITEM_SID_SONGPEON_51	866	//
#define EVENTITEM_SID_SONGPEON_71	867	//
#define EVENTITEM_SID_BOX			868 // 선물상자 Sid
*/

// 추석 이벤트를 크리스마스 이벤트로 변형하여 진행하기 위해 재정의 함
#define NPC_EVENT_MOON		620			// 산타인형드롭확율 5%
#define NPC_EVENT_SONGPEON	1120		// 막대사탕 드로확율 5%
#define NPC_EVENT_BOX		1420		// 크리스마스 양말 드롭확율 3%

#define EVENTITEM_SID_MOON			873	// 산타인형	Sid
#define EVENTITEM_SID_SONGPEON_01	872	// 막대사탕	Sid
#define EVENTITEM_SID_SONGPEON_11	864	//
#define EVENTITEM_SID_SONGPEON_31	865	//
#define EVENTITEM_SID_SONGPEON_51	866	//
#define EVENTITEM_SID_SONGPEON_71	867	//
#define EVENTITEM_SID_BOX			871 // 크리스마스 양말 Sid

#define NPC_GUILDHOUSE_BAND	10000		// 길드하우스에 관련된 NPC
//#define NPC_STORE_BAND			
#define FORTRESS_BAND	1000			// 요새에 속하는 NPC

#define NPC_EVENT_B_ITEM	57			// 범용회복제B 이벤트를 위한 임시 정의
#define NPC_EVENT_ITEM		634			// 이벤트를 위한 임시 정의
#define NPC_EVENT_INIT_STAT	756			// 극약 아이템
#define NPC_EVENT_FLOWER	773			// 몹이 떨어뜨리는 꽃바구니 교환권
#define NPC_EVENT_LOTTO		796			// 투스카니 이벤트

// 공성전에 쓰임
										// 길드전시 수리할 필요성 이 있으면
#define NPC_NON_REPAIR_STATE	0		// 0 : 최고 상태		
#define NPC_NEED_REPAIR_STATE	1		// 1 : 손상되어 수리 할 필요가 있는 상태
#define NPC_DEAD_REPAIR_STATE	2		// 2 : 완전히 망가진 상태

#define NPC_NCIRCLE_DEF_STATE	1
#define NPC_NCIRCLE_ATT_STATE	2

struct  DynamicMapList
{
	POINT map[NPC_MAP_SIZE];
};

struct  NpcSkillList
{
	short	sSid;
	BYTE	tLevel;
	BYTE	tOnOff;
};

struct	ExpUserList
{
	TCHAR	strUserID[CHAR_NAME_LENGTH + 1];			// 아이디(캐릭터 이름)
	int		iUid;		
	int		nDamage;								// 타격치 합
	BOOL	bIs;
};

struct	TargetUser
{
	int		iUid;
	int		sHP;
	int		sMaxHP;
};

struct ItemUserRightlist
{
	short uid;
	int nDamage;
};

//typedef CTypedPtrArray <CPtrArray, ExpUserList*>		arUserList;
typedef CArray <CPoint, CPoint> RandMoveArray;		// 8방향 RandomMove하기 위한 Array

class CNpc  
{
public:
	CNpc();
	virtual ~CNpc();

	BOOL SetLive(COM* pCom);
	BOOL FindEnemy(COM* pCom);
	BOOL GetTargetPath(COM* pCom);
	BOOL IsCloseTarget(COM* pCom, int nRange = 1);
	BOOL IsCloseTarget(USER *pUser, int nRange = 1);
	BOOL IsMovingEnd();
	BOOL IsChangePath(COM* pCom, int nStep = CHANGE_PATH_STEP);
	USER* GetUser(COM* pCom, int uid);
	BOOL ResetPath(COM* pCom);
	BOOL GetTargetPos(COM* pCom, CPoint& pt);
	BOOL StepMove(COM* pCom, int nStep);
	BOOL GetLastPoint(int sx, int sy, int& ex, int& ey);

protected:
	void ClearPathFindData(void);
	void InitSkill();
	
public:	
	void SendNpcInfoBySummon(COM* pCom);
	BOOL CheckUserForNpc_Live(int x, int y);
	DWORD GetItemThrowTime();
	void UserListSort();
	CPoint FindNearRandomPointForItem(int x, int y);
	BOOL UpdateEventItemNewRemain(CEventItemNew* pEventItem);
	void GiveItemToMap(COM* pCom, ItemList* pItem);
	void GiveEventItemNewToUser(USER* pUser);
	void SetISerialToItem(ItemList *pItem, int iEventItemSid);
	int AreaAttack(COM* pCom);
	void GetWideRangeAttack(COM* pCom, int x, int y, int damage, int except_uid);
	int PsiAttack(COM* pCom);
	void TestCode(COM *pCom, USER *pUser);
	void SendFortressInsight(COM *pCom, TCHAR *pBuf, int nLength);
	void SetMapAfterGuildWar();
	void SetMapTypeBeforeGuildWar(COM *pCom);
	void SendFortressNCircleColor(COM *pCom);
	//void SetDoorDamagedInFortressWar(int nDamage, TCHAR *id, int uuid, COM *pCom);
	void SetDoorDamagedInFortressWar(int nDamage, USER *pUser);
	//void SetDamagedInFortressWar(int nDamage, TCHAR *id, int uuid, COM *pCom);
	void SetDamagedInFortressWar(int nDamage, USER *pUser);
	void SetFortressState();
	BOOL UpdateEventItem(int sid);
	int GetEventItemNum(COM *pCom);
	void GiveEventItemToUser(USER *pUser);
	void Send(USER* pUser, TCHAR* pBuf, int nLength);
	int GetCityNumForVirtualRoom(int zone);
	//void SetDamagedInGuildWar(int nDamage, TCHAR *id, int uuid, COM *pCom);
	void SetDamagedInGuildWar(int nDamage, USER *pUser);
	void SetGuildType(COM *pCom);
	void EventNpcInit(int x, int y);
	int IsMagicItem(COM* pCom, ItemList *pItem, int iTable);
	int IsTransformedItem(int sid);
	void ToTargetMove(COM* pCom, USER* pUser);
	void NpcTrace(TCHAR* pMsg);
	CPoint ConvertToServer(int x, int y);
	void Init();
	BOOL IsStepEnd();
	BOOL PathFind(CPoint start, CPoint end);
	void InitTarget(void);
	void SendToRange(COM* pCom, char* temp_send, int index, int min_x, int min_y, int max_x, int max_y);
	CPoint ConvertToClient(int x, int y);
	void FillNpcInfo(char* temp_send, int& index, BYTE flag);
	void SendUserInfoBySightChange(int dir_x, int dir_y, int prex, int prey, COM* pCom);
	int GetFinalDamage(USER* pUser, int type = 1);
	void DeleteNPC();
	void SetFireDamage();
	BOOL CheckClassItem(int artable, int armagic);
	void ChangeSpeed(COM *pCom, int delayTime);
	CNpc* GetNpc(int nid);
	void InitUserList();
	BOOL GetBackPoint(int &x, int &y);
	void GetBackDirection(int sx, int sy, int ex, int ey);
	void NpcBack(COM *pCom);
	BOOL IsDamagedUserList(USER *pUser);
	void FindFriend();
	void NpcStrategy(BYTE type);
	void NpcTypeParser();
	void NpcFighting(COM *pCom);
	void NpcTracing(COM *pCom);
	void NpcAttacking(COM *pCom);
	void NpcMoving(COM *pCom);
	void NpcStanding(COM *pCom);
	void NpcLive(COM *pCom);
	void ChangeTarget(USER *pUser, COM* pCom);
	BOOL IsSurround(int targetx, int targety);
	BOOL CheckNpcRegenCount();
	void IsUserInSight(COM *pCom);
	void SendExpToUserList(COM *pCom);
	BOOL SetDamage(int nDamage, int uid, COM *pCom);
	void SetColdDamage(void);
	CPoint FindNearRandomPoint(int xpos, int ypos);
	BOOL IsMovable(int x, int y);
	void GiveNpcHaveItem(COM *pCom);
	int GetCriticalInitDamage(BOOL* bSuccessSkill);
	int GetNormalInitDamage();
	void SendAttackMiss(COM* pCom, int tuid);
	void IsSkillSuccess(BOOL *bSuccess);
	BYTE GetWeaponClass();
	//yskang 0.3 void SendAttackSuccess(COM *pCom, int tuid, CByteArray &arAction1, CByteArray &arAction2, short sHP, short sMaxHP);
	void SendAttackSuccess(COM *pCom, int tuid,BOOL bIsCritical, short sHP, short sMaxHP);//yskang 0.3
	void GiveItemToMap(COM *pCom, int iItemNum, BOOL bItem, int iEventNum = 0);
	BOOL GetDistance(int xpos, int ypos, int dist);
	void SendInsight(COM* pCom, TCHAR *pBuf, int nLength);
	void SendExactScreen(COM* pCom, TCHAR* pBuf, int nLength);

	void SightRecalc(COM* pCom);

	BOOL IsInRange();
	BOOL RandomMove(COM* pCom);
	int SendDead(COM* pCom, int type = 1);
	void Dead(void);
	BOOL SetDamage(int nDamage);
	int GetDefense();
	int GetAttack();
	int Attack(COM* pCom);

	// Inline Function
	int GetUid(int x, int y );
	BOOL SetUid(int x, int y, int id);

	BOOL SetUidNPC(int x, int y, int id);
	void shouhu_rand(	ItemList *pMapItem);

	struct Target
	{
		int	id;
		int x;
		int y;
		int failCount;
//		int nLen;
//		TCHAR szName[CHAR_NAME_LENGTH + 1];
	};
	Target	m_Target;
	int		m_ItemUserLevel;		// 죽을때 매직 이상 아이템를 떨구기위해 참조해야하는 유저의레벨

	int		m_TotalDamage;	// 총 누적된 대미지양
	ExpUserList m_DamagedUserList[NPC_HAVE_USER_LIST]; // 나에게 타격치를 준 유저정보를 리스트로 관리한다.(경험치 분배)
//	arUserList m_arDamagedUserList;

	BOOL	m_bFirstLive;		// NPC 가 처음 생성되는지 죽었다 살아나는지 판단.
	BYTE	m_NpcState;			// NPC의 상태 - 살았다, 죽었다, 서있다 등등...
	BYTE	m_NpcVirtualState;	// NPC상태 -- 유저가 들어올때만 활성화 (일회성으로 살아남)
	int		m_ZoneIndex;		// NPC 가 존재하고 있는 존의 인덱스

	short	m_sNid;				// NPC (서버상의)일련번호

	MapInfo	**m_pOrgMap;		// 원본 MapInfo 에 대한 포인터

	int		m_nInitX;			// 처음 생성된 위치 X
	int		m_nInitY;			// 처음 생성된 위치 Y

	int		m_sCurZ;			// Current Zone;
	int		m_sCurX;			// Current X Pos;
	int		m_sCurY;			// Current Y Pos;

	int		m_sOrgZ;			// 원래 DB의 Zone
	int		m_sOrgX;			// 원래 DB의 X Pos
	int		m_sOrgY;			// 원래 DB의 Y Pos

	int		m_presx;			// 이전 시야 X
	int		m_presy;			// 이전 시야 Y

	//
	//	PathFind Info
	//
	CPoint	m_ptDest;
	int		m_min_x;
	int		m_min_y;
	int		m_max_x;
	int		m_max_y;

	long	m_lMapUsed;			// 맵 메모리를 보호하기위해(사용중 : 1, 아니면 : 0)
//	int		**m_pMap;

	int		m_pMap[MAX_MAP_SIZE];// 2차원 -> 1차원 배열로 x * sizey + y

	CSize	m_vMapSize;
	CPoint	m_vStartPoint, m_vEndPoint;

//	CPoint m_curStartPoint;
	CPathFind m_vPathFind;

	NODE	*m_pPath;

	int		m_nInitMinX;
	int		m_nInitMinY;
	int		m_nInitMaxX;
	int		m_nInitMaxY;

	CPoint		m_ptCell;					// 현재 Cell 위치
	int			m_nCellZone;

	// NPC Class, Skill
	NpcSkillList	m_NpcSkill[SKILL_NUM];	// NPC 가 가지고 있는 스킬
	BYTE			m_tWeaponClass;			// NPC 의 무기 클래스 

	DWORD			m_dwDelayCriticalDamage;	// Delay Critical Damage
	DWORD			m_dwLastAbnormalTime;		// 상태이상이 걸린시간

	BOOL			m_bRandMove;				// 8방향 선택 Random Move 인가?
	RandMoveArray	m_arRandMove;				// 8방향 선택 Random Move에서 사용하는 좌표 Array

	DWORD			m_dLastFind;				// FindEnemy 함수에 인위적 Term을 주기 위해 사용하는 TickCount

	BOOL			m_bCanNormalAT;				// 일반 공격을 하는가?
	BOOL			m_bCanMagicAT;				// 사이오닉 공격을 하는가?
	BOOL			m_bCanSPAT;					// 특수 공격을 하는가?

	BYTE			m_tSPATRange;				// 특수 공격 범위
	BYTE			m_tSPATAI;					// 특수 공격을 할 수 있는 몹일때 어느 경우에 특수 공격을 할건지

	int				m_iNormalATRatio;			// 일반 공격 확률
	int				m_iSpecialATRatio;			// 특수 공격 확률
	int				m_iMagicATRatio;			// 매직 공격 확률


	//----------------------------------------------------------------
	//	아이템을 처리하는 변수
	//----------------------------------------------------------------
	ItemList	m_NpcHaveItem[NPC_ITEM_NUM];	

	//----------------------------------------------------------------
	//	MONSTER DB 쪽에 있는 변수들
	//----------------------------------------------------------------
	int		m_sSid;				// MONSTER(NPC) Serial ID
	int		m_sPid;				// MONSTER(NPC) Picture ID
	TCHAR	m_strName[20];		// MONSTER(NPC) Name

	int		m_sSTR;				// 힘
	int		m_sDEX;				// 민첩
	int		m_sVOL;				// 의지
	int		m_sWIS;				// 지혜

	int		m_sMaxHP;			// 최대 HP
	int		m_sHP;				// 현재 HP
	int		m_sMaxPP;			// 최대 PP
	int		m_sPP;				// 현재 PP

	BYTE	m_byClass;			// 무기계열
	BYTE	m_byClassLevel;		// 무기계열 레벨
	
	DWORD	m_sExp;				// 경험치

	int 	m_byAX;				// 공격값 X
	int 	m_byAY;				// 공격값 Y
	int	    m_byAZ;				// 공격값 Z

	int		m_iDefense;		// 방어값
	BYTE	m_byRange;			// 사정거리

	int		m_sAI;				// 인공지능 인덱스
	int		m_sAttackDelay;		// 공격딜레이

	BYTE	m_byVitalC;			// 신체데미지 크리티컬
	BYTE	m_byWildShot;		// 난사 레벨
	BYTE	m_byExcitedRate;	// 흥분 레벨
	BYTE	m_byIronSkin;
	BYTE	m_byReAttack;
	BYTE	m_bySubAttack;		// 상태이상 발생(부가공격)
	BYTE	m_byState;			// 몬스터 (NPC) 상태이상

	BYTE	m_byPsi;			// 사이오닉 적용
	BYTE	m_byPsiLevel;		// 사이오닉레벨

	BYTE	m_bySearchRange;	// 적 탐지 범위
	int		m_sSpeed;			// 이동속도	

	int		m_sInclination;
	BYTE	m_byColor;
	int		m_sStandTime;
	BYTE	m_tNpcType;			// NPC Type
								// 0 : Normal Monster
								// 1 : NPC
								// 2 : 각 입구,출구 NPC
								// 3 : 경비병

	int		m_sFamilyType;		// 각 몹들간의 가족관계 정의
	BYTE	m_tItemPer;			// 아이템 떨어질 확률
	BYTE	m_tDnPer;			// 돈 떨어질 확률
	//----------------------------------------------------------------
	//	MONSTER AI에 관련된 변수들
	//----------------------------------------------------------------
	BYTE	m_tNpcLongType;		// 공격 거리 : 원거리(1), 근거리(0)
	BYTE	m_tNpcAttType;		// 공격 성향 : 선공(1), 후공(0)
	BYTE	m_tNpcGroupType;	// 군집을 형성하냐(1), 안하냐?(0)
//	BYTE	m_tNpcTraceType;	// 끝까지 따라간다(1), 시야에서 없어지면 그만(0)

	//----------------------------------------------------------------
	//	MONSTER_POS DB 쪽에 있는 변수들
	//----------------------------------------------------------------
	int		m_sMinX;			// NPC 움직임 영역
	int		m_sMinY;
	int		m_sMaxX;
	int		m_sMaxY;

	int		m_Delay;			// 다음 상태로 전이되기 까지의 시간
	DWORD	m_dwLastThreadTime;	// NPC Thread 에서 마지막으로 수행한 시간

	DWORD	m_dwStepDelay;
	short	m_sClientSpeed;		// 애니 속도 비율를 정의(500 : 100 = 600 : x)

	BYTE	m_byType;
	int		m_sRegenTime;		// NPC 재생시간
	int		m_sEvent;			// 이벤트 번호
	int		m_sEZone;			// 몬스터 자체가 가지는 이벤트존

	int		m_sGuild;			// NPCTYPE_GUILD_GUARD라면 해당 필드상점 인덱스
								// NPCTYPE_GUILD_NPC라면...

	short	m_sDimension;		// 이벤트몹 또는 그외 맵에서 2셀 이상 자리를 차지하는 NPC를 위해

	int		m_sHaveItem;		// 몬스터가 죽을 당시 줄 아이템 인덱스

	long	m_lEventNpc;

	//----------------------------------------------------------------
	//	상태이상관련
	//----------------------------------------------------------------
	BYTE	m_tAbnormalKind;
	DWORD	m_dwAbnormalTime;
	
	//----------------------------------------------------------------
	//	길드전과 관련
	//----------------------------------------------------------------
	BYTE	m_tNCircle;			// 0 : 처음상태
								// 1 : 방어측 상태
								// 2 : 공격측 상태

	BYTE	m_tRepairDamaged;	// 길드전시 수리할 필요성 이 있으면
								// 0 : 최고 상태
								// 1 : 손상되어 수리 할 필요가 있는 상태
								// 2 : 완전히 망가진 상태

	CGuildFortress *m_pGuardFortress;
	CStore* m_pGuardStore;		// 경비병이라면 해당 상점을 가지고 있다.
	BYTE	m_tGuildWar;		// 0 : 길드전 준비단계
								// 1 : 길드전중
								// 2 : 일반 단계

	ItemUserRightlist		m_iHaveItemUid[NPC_HAVE_USER_LIST];
	long					m_lFortressState;
	long					m_lDamage;	// 각 데미지가 한번에 하나씩 들어오도록 동기화 한다. by Youn Gyu 02-10-08

	BOOL	m_bSummon;
	int		m_sSummonOrgZ;
	int		m_sSummonOrgX;
	int		m_sSummonOrgY;
	int		m_SummonZoneIndex;

	BOOL	m_bSummonDead;
	LONG	m_lNowSummoning;

	int		m_TableZoneIndex;
	int		m_sTableOrgZ;
	int		m_sTableOrgX;
	int		m_sTableOrgY;

	LONG	m_lKillUid;					// 몹을 마지막으로 죽인 유저의 uid
	short	m_sQuestSay;				// 퀘스트를 가지고 있는 이벤트 몹인경우 != 0 (1 ~~ 10000)
	int Dead_User_level;
	int NpcDrop; //밍膠괵놔膠틔늴鑒
};

#endif // !defined(AFX_NPC_H__600048EF_818F_40E9_AC07_0681F5D27D32__INCLUDED_)
