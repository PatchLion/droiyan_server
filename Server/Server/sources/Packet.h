#ifndef _PACKET_H_
#define _PACKET_H_

#define ACCOUNT_LENGTH		12
#define PASSWORD_LENGTH		12
#define CHAR_NAME_LENGTH	30
#define	CHAR_NAME_LENGTH_CLIENT 16
#define GUILD_MARK_SIZE		384
#define GUILD_MAP_COUNT		40 //  40개
#define TEL_NAME_LENGTH		20
#define SHOP_NAME_LENGTH	20

#define CLASS_NUM			4

#define SKILL_NUM			5
#define SKILL_LEVEL			41

//#define SKILL_NAME_LENGTH	14

#define EQUIP_ITEM_NUM		10
#define	INVENTORY_NUM		24
//#define QUICK_ITEM		5
#define EBODY_NUM			4
#define GUARDIAN_NUM		1
#define TOTAL_SKILL_NUM			(CLASS_NUM * SKILL_NUM)
//#define TOTAL_CLASS_SKILL_NUM	(SKILL_NUM * SKILL_LEVEL)

#define TOTAL_PSI_NUM		32

#define MAX_ITEM_NUM		255			// 하나의 슬롯당 소유할수있는 최대값
#define BANK_MAX_ITEM		1000		// 한슬롯당 소유할수 있는 수
#define ACCOUNT_BANK_MAX_ITEM	32767	// 계정 은행에 한슬롯당 소유할수 있는 수

#define TOTAL_BANK_ITEM_NUM 48
#define TOTAL_ACCOUNT_BANK_ITEM_NUM 150

#define TOTAL_PERSONALSHOP_ITEM_NUM 7

#define TOTAL_INVEN_MAX		((EQUIP_ITEM_NUM + INVENTORY_NUM))
#define TOTAL_ITEM_NUM		((EQUIP_ITEM_NUM + INVENTORY_NUM + EBODY_NUM + 1 + 1))
//#define TOTAL_ITEM_SLOT_NUM ((EQUIP_ITEM_NUM + INVENTORY_NUM + QUICK_ITEM))
//#define TOTAL_USER_ITEM_NUM	((TOTAL_ITEM_NUM + EBODY_ITEM))

#define _SKILL_SIZE			((sizeof(short) + sizeof(BYTE)))
#define _ITEM_SIZE			((sizeof(short) * 5) + (sizeof(BYTE) * 11) + (sizeof(BYTE)))
#define _PSI_SIZE			((sizeof(short) + sizeof(BYTE)))
#define _SKILLINFO_SIZE		((sizeof(BYTE) + sizeof(DWORD)))

#define USER_SKILL_LEN		(_SKILL_SIZE * TOTAL_SKILL_NUM)
#define USER_ITEM_LEN		(_ITEM_SIZE * TOTAL_ITEM_NUM)

#define USER_SKILLINFO_LEN	(_SKILLINFO_SIZE * TOTAL_SKILL_NUM)

#define EQUIP_SLOT			0
#define INVENTORY_SLOT		1
//#define QUICK_SLOT			2
#define TRADE_SLOT			3
#define BANK_SLOT			4
#define GUILD_SLOT			5
#define ACCOUNT_BANK_SLOT	6

#define BRAWL				0		// Character Making 시 사용되는 클래스 숫자
#define STAFF				1
#define	EDGED				2
#define FIREARMS			3
#define NOCLASS				4

#define BRAWL_ITEM			8		// Item Table 에 정의된 클래스 숫자
#define STAFF_ITEM			4
#define	EDGED_ITEM			2
#define FIREARMS_ITEM		1

#define MAX_MOVE_TIME		100

#define ATTACK_UPGRADE_BAND		16	// 물리데미지 무기 업그레이드시 데미지 증가값
#define ATTACK_UPGRADE_PSI_BAND	4	// 사이오닉 무기 업그레이드시 데미지 증가값
#define DEFENSE_UPGRADE_BAND	4	// 방어구 업그레이드시 방어력 증가값

const BYTE SUCCESS				=	1;
const BYTE FAIL					=	0;
const BYTE SUCCESS_ZONE_CHANGE	=	2;

const BYTE ERR_1				=	1;
const BYTE ERR_2				=	2;
const BYTE ERR_3				=	3;
const BYTE ERR_4				=	4;
const BYTE ERR_5				=	5;
const BYTE ERR_6				=	6;
const BYTE ERR_7				=	7;
const BYTE ERR_8				=	8;
const BYTE ERR_9				=	9;
const BYTE ERR_10				=	10;
const BYTE ERR_11				=	11;
const BYTE ERR_12				=	12;
const BYTE UNKNOWN_ERR			=	255;

const BYTE ERR_SHORT_ATTACK_DELAY	= 0;
const BYTE ERR_TOO_LONG_DISTANCE	= 1;
const BYTE ERR_BROKEN				= 2;
const BYTE ERR_EMPTY_BULLET			= 3;
const BYTE ERR_EMPTY_ENERGE			= 4;
const BYTE ERR_EMPTY_SP				= 5;

const BYTE INFO_MODIFY			=	1;
const BYTE INFO_DELETE			= 	2;
const BYTE INFO_TOWNPOTAL		=   3;
const BYTE INFO_TOWNPOTAL_DELETE=	4;

const BYTE ITEM_INFO_MODIFY		=	1;
const BYTE ITEM_INFO_DELETE		=	2;
const BYTE ITEM_INFO_PICKUP		=	3;

const BYTE NORMAL_CHAT			=	1;
const BYTE WHISPER_CHAT			=	2;
const BYTE SHOUT_CHAT			=	3;
const BYTE GUILD_CHAT			=	4;
const BYTE BUDDY_CHAT			=	5;
const BYTE BUDDY_INVITE			=	6;
const BYTE BUDDY_OFF			=	7;
const BYTE MOP_CHAT				=	10;
const BYTE WHISPER_OK			=	11;
const BYTE WHISPER_DENY			=	12;

const BYTE CALL_CHAT			=	15;		// 특정유저 소환
const BYTE REMOTE_CHAT			=	16;		// 특정유저 특정좌표로 강제 이동
const BYTE MOP_CALL_CHAT		=	17;		// 특정몹 특정좌표로 강제 이동

const BYTE GUILD_INVITE			=	18;		// 길드 가입
const BYTE GUILD_DISPERSE		=	19;		// 길드 해산
const BYTE GUILD_OFF			=	20;		// 길드 탈퇴
const BYTE GUILD_KICK_OUT		=	21;		// 길마가 길드원 추방

const BYTE ITEM_MODE_CHAT		=	22;		// 아이템 받기 승낙, 거절를 표시

const BYTE OP_CLOAK_ON			=	23;		// 운영자 투명모드로
const BYTE OP_CLOAK_OFF			=	24;		// 운영자 투명모드 해제로...
const BYTE ALL_CHAT				=	25;		// 전체 접속자에게 메세지를 보낸다.
const BYTE GUILD_FIELD_WAR		=   26;		// 상대 길드를 상대로 필드전을 신청한다.
const BYTE GUILD_SURRENDER		=   27;		// 상대 길드를 상대로 항복한다.
const BYTE PK_COUNT_CHAT		=	28;
const BYTE COPY_TELEPORT		=	29;		// 지정한 상대방과 같이 이동한다.
const BYTE GUILD_USER_CHECK		=	30;		// 전체 길드원 목록를 보여준다.
const BYTE GUILD_WAR_APPLY_LIST =	31;		// 길전을 신청한 전체 길드 목록을 보여준다.
const BYTE GUILD_FORTRESS_DOOR	=	32;		// 포트리스 성문을 열고 닫는다.
const BYTE GUILD_DEPUTE_POWER	=	33;		// 길마 권한을 부길마에게 위임
const BYTE GUILD_STOP_POWER		=	34;		// 부길마 권한을 정지
const BYTE GUILD_USER_INFO_CALL =	35;		//yskang 0.2
const BYTE GUILD_CALL_CHAT		=	36;		//yskang 0.2 포트리스를 가지고 있는 길드짱이 특정 유저를 소환한다.

const BYTE SYSTEM_SPECIAL		=	0;		// 특별 정보
const BYTE SYSTEM_NORMAL		=	1;		// 일반 정보
const BYTE SYSTEM_ERROR			=	2;		// 에러정보
const BYTE SYSTEM_NPC			=	3;		// NPC 대화
const BYTE SYSTEM_ANNOUNCE		=	4;		// 운영자 메세지 정보
const BYTE SYSTEM_DISCONNECT	=	5;		// 시간 사용자 종료정보	

// Hit Mark List (Skill List)
const BYTE HIT_NONE				=	0;
const BYTE HIT_DAMAGE_C			=	1;
const BYTE HIT_VITAL_C			=	2;
const BYTE HIT_DELAY_C			=	3;
const BYTE HIT_CONCENTRATE		=	4;
const BYTE HIT_PSY_ACCLIMATE	=	5;
const BYTE HIT_FAST_CAST		=	6;
const BYTE HIT_WEAPON_ACCLIMATE	=	7;
const BYTE HIT_FAST_ATTACK		=	8;
const BYTE HIT_OUT_RANGE		=	9;
const BYTE HIT_STRAFE			=	10;
const BYTE HIT_BROKEN			=	11;
const BYTE HIT_FIXED			=	12;
const BYTE HIT_OVERHIT			=	13;
const BYTE HIT_FIRE				=	14;
const BYTE HIT_ICE				=	15;
const BYTE HIT_LIGHT			=	16;
const BYTE HIT_NUMB				=	17;
const BYTE HIT_POISON			=	18;
const BYTE HIT_C_GUARD			=	19;

const BYTE PSI_TELEPORT			=	7;

const BYTE BBS_NOT_OWNER		=	2;
const BYTE BBS_CONTENTS_DELETE	=	3;

// 상태이상 정보
//#define _ABNORMAL_DB			5

const BYTE ABNORMAL_TIME			=	0;
const BYTE PSI_ONE_TIME				=	1;
const BYTE PSI_TWO_TIME				=	2;
const BYTE PSI_THREE_TIME			=	3;

const BYTE ABNORMAL_BYTE_NONE		=	0;
const BYTE ABNORMAL_BYTE_POISON		=	1;
const BYTE ABNORMAL_BYTE_CONFUSION	=	2;
const BYTE ABNORMAL_BYTE_PARALYSIS	=	3;
const BYTE ABNORMAL_BYTE_BLIND		=	4;
const BYTE ABNORMAL_BYTE_LIGHT		=	5;
const BYTE ABNORMAL_BYTE_FIRE		=	6;
const BYTE ABNORMAL_BYTE_COLD		=	7;

const DWORD ABNORMAL_NONE			=	0;
const DWORD ABNORMAL_POISON			=	1;
const DWORD ABNORMAL_CONFUSION		=	1 << 2;
const DWORD ABNORMAL_PARALYSIS		=	1 << 3;
const DWORD ABNORMAL_BLIND			=	1 << 4;
const DWORD ABNORMAL_LIGHT			=	1 << 5;
const DWORD ABNORMAL_FIRE			=	1 << 6;
const DWORD ABNORMAL_COLD			=	1 << 7;
const DWORD ABNORMAL_HASTE			=	1 << 8;
const DWORD ABNORMAL_SHIELD			=	1 << 9;
const DWORD ABNORMAL_HIDE			=	1 << 10;
const DWORD ABNORMAL_DEX_UP			=	1 << 11;
const DWORD ABNORMAL_MAX_HP_UP		=	1 << 12;
const DWORD ABNORMAL_ADAMANTINE		=	1 << 13;
const DWORD ABNORMAL_MIGHTYWEAPON	=	1 << 14;
const DWORD ABNORMAL_BERSERKER		=	1 << 15;
const DWORD ABNORMAL_HIEXP			=	1 << 16;
const DWORD ABNORMAL_MAGICFIND		=	1 << 17;
const DWORD ABNORMAL_NOCHAT			=	1 << 18;

const DWORD ABNORMAL_FASTRUN		=	1 << 19;
const DWORD ABNORMAL_MINDSHOCK		=	1 << 20;
const DWORD ABNORMAL_MINDGUARD		=	1 << 21;
const DWORD ABNORMAL_PSISHIELD		=	1 << 22;
const DWORD ABNORMAL_PIERCING_SHIELD=	1 << 23;
const DWORD ABNORMAL_BIGSHIELD			=	1 << 30;

const DWORD OPERATION_MODE			=	1 << 31;	// 운영자 투명 옵션

const DWORD ABNORMAL_CLEAR_STATUS	= (0xFFFFFFFF ^ (ABNORMAL_POISON | ABNORMAL_CONFUSION | ABNORMAL_PARALYSIS | ABNORMAL_BLIND | ABNORMAL_LIGHT | ABNORMAL_FIRE | ABNORMAL_COLD));
const DWORD	ABNORMAL_CLEAR_PSI_ONE	= (0xFFFFFFFF ^ (ABNORMAL_HASTE | ABNORMAL_SHIELD | ABNORMAL_HIDE | ABNORMAL_DEX_UP | ABNORMAL_MAX_HP_UP | ABNORMAL_FASTRUN | ABNORMAL_PSISHIELD | ABNORMAL_PIERCING_SHIELD | ABNORMAL_MINDSHOCK));
const DWORD ABNORMAL_CLEAR_PSI_TWO	= (0xFFFFFFFF ^ (ABNORMAL_ADAMANTINE | ABNORMAL_MIGHTYWEAPON | ABNORMAL_BERSERKER));
const DWORD ABNORMAL_CLEAR_PSI_THREE= (0xFFFFFFFF ^ (ABNORMAL_MINDGUARD));

const short TYPE_MONEY_SID		=	10000;	// 아이템 과 돈을 구분하기위해 sid를 크게 잡았다.

/*
BYTE	NORMAL_ITEM		= 0;
BYTE	REMODEL_ITEM	= 1;
BYTE	MAGIC_ITEM		= 2;
BYTE	RARE_ITEM		= 3;
BYTE	UNIQUE_ITEM		= 4;
BYTE	SET_ITEM		= 5;
BYTE	UPGRADE_ITEM	= 6;
*/

const BYTE HP_POTION			= 1;
const BYTE PP_POTION			= 2;
const BYTE SP_POTION			= 3;
const BYTE ALL_POTION			= 4;
const BYTE SALUTE				= 5;
const BYTE EXP_POTION			= 6;
const BYTE MAGIC_POTION			= 7;
const BYTE KILLREMOVE_POTION	= 8;
const BYTE DEAD_POTION			= 9;
const BYTE XMAS_SALUTE			= 10;
const BYTE YEAR_SALUTE			= 11;

//#################################################################
//	Zone Server
//#################################################################
const BYTE	SERVER_LOGIN_REQ			= 1;

const BYTE	SERVER_LOGIN_RESULT			= 2;

const BYTE	SERVER_USER_LOGIN_REQ		= 3;

const BYTE	SERVER_USER_LOGIN_RESULT	= 4;

const BYTE	SERVER_DOUBLE_ACCOUNT_CLOSE = 5;

const BYTE	SERVER_DOUBLE_ID_CLOSE		= 6;

const BYTE	SERVER_USER_LOGOUT_REQ		= 7;

const BYTE	SERVER_USER_ZONELOGIN_REQ	= 8;

const BYTE	SERVER_USER_ZONELOGIN_RESULT= 9;

const BYTE	SERVER_USER_WHISPER_ONOFF	= 10;

const BYTE	SERVER_USER_WHISPER_REQ		= 11;

const BYTE	SERVER_USER_WHISPER_RESULT	= 12;

const BYTE	SERVER_USER_GUILD_CHAT		= 13;

const BYTE	SERVER_GUILD_NEW			= 14;

const BYTE	SERVER_GUILD_DISPERSE		= 15;

const BYTE	SERVER_GUILD_INVITE			= 16;

const BYTE	SERVER_GUILD_OFF			= 17;

const BYTE	SERVER_GUILD_MARK			= 18;

const BYTE	SERVER_USER_RESTART			= 19;

const BYTE	SERVER_USER_ZONE_LOGOUT		= 20;

const BYTE	SERVER_ALIVE				= 21;

const BYTE	SERVER_ANNOUNCE				= 22;

const BYTE	SERVER_ARK_WINNER			= 23;

const BYTE  SERVER_GUILD_SUBMASTER_ON	= 24;

const BYTE  SERVER_GUILD_SUBMASTER_OFF	= 25;

const BYTE	ZONE_LOGIN_REQ				= 233;
/*
	(C -> S)	// 다른 서버에서 담당하는 존으로 존체인지를 할때  (암호화 안함)

	VarChar		id[ACCOUNT_LENGTH];				// Account ID
	VarChar		pass[PASSWORD_LENGTH];			// Account Password
	VarChar		szCharName[CHAR_NAME_LENGTH];	// CharName

	short		myserver;
*/

const BYTE	ZONE_LOGIN_RESULT			= 234;
/*
	(C <- S)	// Game Login Result  (암호화 안함)

	BYTE		result;			// 01	: Login Success
								// else	: Login Fail

	// 실패인 경우 ------		// 01	: Invaild ID
								// 02	: DB에 없는 ID
								// 03	: Invalid Zone Number
								// 04	: Invalid Position
								// 05	: 현재 ID 사용중
								// ...
								// 255	: 알 수 없는 에러

	short		CurrZone;		// 현재 Zone Number
	int			uid;			// User Index
	short		PosX;			// Map 의 X 좌표
	short		PosY;			// Map 의 Y 좌표

	BYTE		tDir;			// 현재 보고있는 방향

	BYTE		tTime;			// 시간(0~24)
	BYTE		tMinute;		// 분  (0~60)


    Varchar		public_key;		// int64
	DWORD		dwSerial;		// 시리얼 시작 번호
*/


// CHAR INFO SERVER
const BYTE CIS_DISCONNECT				= 235;
/*
*/

//#################################################################
//	서버 테스트 코드임 (2001-11-15)
//#################################################################
const BYTE CHECK_ALIVE_REQ		= 255;
/*
	(C -> S)
*/
const BYTE CHECK_ALIVE_RESULT	= 255;
/*
	(C <- S)
*/

const BYTE CLIENT_TICK			= 254;
/*
	(C -> S) // Speed Hack 을 막기위해 5초마다 클라이언트에서 서버로 보내는 패킷
*/

//const BYTE SERVER_TICK_RESULT	= 6;
/*
	(C <- S)
	DWORD	dwTick;				// Server의 현재 Tick.
*/

const BYTE DB_USER_COUNT			= 253;
/*
	(S <- S)						//
*/

const BYTE DB_GUILD_WHEREHOUSE_EVENT_REQ = 252;
/*
	(S <- S)						//
*/

const BYTE DB_GUILD_ITEM_MOVE_REQ	= 251;
/*
	(S <- S)						//
*/

const BYTE ANNOUNCE_NOTICE			= 250;
/*
	(C -> S)						// 전체서버에 일괄적인 공지를위해
	String		strMsg;
*/

const BYTE ENCRYPTION_PKT			= 249;
/*									// 암호화를 의미
*/

const BYTE DB_USER_DEAD				= 248;
/*									// 유저가 죽었을때 로그를 남김
*/

//#################################################################
//	Information		(1 ~ 9)
//#################################################################

const BYTE USER_INFO			=	1;
/*
	(C <- S)		// Send User Info

	BYTE		Mode;			// 01(INFO_MODIFY)	: 유저정보 변경
								// 02(INFO_DELETE)	: 유저정보 삭제
								// 03(INFO_TOWNPOTAL)		 : 유저가 타운포탈 사용 -> 마을 진입
								// 04(INFO_TOWNPOTAL_DELETE) : 유저가 타운포탈로 이동, 유저 정보 삭제

	int			uid;			// User index

	// Mode 가 INFO_MODIFY 인 경우만 아래의 데이터 전송
	VarChar		szName;			// User Name
	short		nPosX;			// X Position
	short		nPosY;			// Y Position

	DWORD		dwSkin;			// 피부색(COLORREF)
	DWORD		dwHair;			// 머리색(COLORREF)
	BYTE		byGender;		// 남, 여

	char		szFace[10];		// 얼굴모양
								// 1 : 머리
								// 2 : 얼굴
								// 3 : 눈
								// 4 : 코
								// 5 : 입
								// 6 : 악세사리 1
								// 7 : 악세사리 2
								// 8~10 : 예비

	short		sEquipItem[10];	// 0 = 헬멧
								// 1 = 갑옷
								// 2 = 머리 액세서리
								// 3 = 몸 액세서리
								// 4 = 오른쪽 손 무기
								// 5 = 왼쪽   손 무기
								// 6 = 오른쪽 악세사리
								// 7 = 왼쪽   악세사리
								// 8 = 바지
								// 9 = 신발
								// 아이템을 장착하지 않은 슬롯은 id == -1

	short		sHP;
	short		sMaxHP;

	BYTE		tDir;			// 보고있는 방향

	DWORD		dwAbnormal		// 상태이상정보(Damaged)

								// const DWORD ABNORMAL_NONE			=	0;
								// const DWORD ABNORMAL_POISON			=	1;
								// const DWORD ABNORMAL_CONFUSION		=	1 << 2;
								// const DWORD ABNORMAL_PARALYSIS		=	1 << 3;
								// const DWORD ABNORMAL_BLIND			=	1 << 4;
								// const DWORD ABNORMAL_LIGHT			=	1 << 5;
								// const DWORD ABNORMAL_FIRE			=	1 << 6;
								// const DWORD ABNORMAL_COLD			=	1 << 7;
								// const DWORD ABNORMAL_HASTE			=	1 << 8;
								// const DWORD ABNORMAL_SHIELD			=	1 << 9;
								// const DWORD ABNORMAL_HIDE			=	1 << 10;
								// const DWORD ABNORMAL_DEX_UP			=	1 << 11;
								// const DWORD ABNORMAL_MAX_HP_UP		=	1 << 12;
								// const DWORD ABNORMAL_ADAMANTINE		=	1 << 13;
								// const DWORD ABNORMAL_MIGHTYWEAPON	=	1 << 14;
								// const DWORD ABNORMAL_BERSERKER		=	1 << 15;
								// const DWORD ABNORMAL_HIEXP			=	1 << 16;
								// const DWORD ABNORMAL_MAGICFIND		=	1 << 17;
								// const DWORD ABNORMAL_NOCHAT			=	1 << 18;

								// const DWORD ABNORMAL_FASTRUN			=	1 << 19;
								// const DWORD ABNORMAL_MINDSHOCK		=	1 << 20;
								// const DWORD ABNORMAL_MINDGUARD		=	1 << 21;
								// const DWORD ABNORMAL_PSISHIELD		=	1 << 22;
								// const DWORD ABNORMAL_PIERCING_SHIELD	=	1 << 23;

								// const DWORD OPERATION_MODE			=	1 << 31;	// 운영자 투명 옵션

	short		sCityRank;		// 시민등급

	int			iGuildIndex;	// 길드 인덱스
	VarChar		szGuildName;	// 길드 이름
	short		sVersion;		// 길드 문양 버젼
	BYTE		tClass;			// 클래스 정보
	BYTE		tKillState;		// 보라돌이인지 판단
								// 0 : 정상적인 유저
								// 1 : 보라돌이 유저
	
	VarChar		strLoveName		//호칭[애칭] //-- yskang 0.1

	short		sEBodyItem[4];	// 0 = 머리
								// 1 = 몸
								// 2 = 팔
								// 3 = 다리
								// 아이템을 장착하지 않은 슬롯은 id == -1
*/

const BYTE CHAR_DATA			=	2;
/*
(C <- S)		// Send Character Data

	VarChar		szName;			// User Name

	short		sSTR;			// 힘
	short		sCON;			// 건강
	short		sDEX;			// 민첩
	short		sVOL;			// 의지
	short		sWIS;			// 지혜
	short		sAbilitySum;	// 기본 능력치의 합

	DWORD		dwSkin;			// 피부색
	DWORD		dwHair;			// 머리색
	BYTE		Gender;			// 성별
	TCHAR		strFace[10];	// 얼굴모양

	DWORD		dwExp;			// 경험치
	DWORD		dwXP;			// 실패경험치

	short		sSkillPoint;	// 스킬 포인트
	short		sPA;			// 물리 포인트

	short		sMaxHP;			// 최대 HP
	short		sHP;			// 현재 HP
	short		sMaxPP;			// 최대 PP
	short		sPP;			// 현재 PP
	short		sMaxSP;			// 최대 SP
	short		sSP;			// 현재 SP

	DWORD		dwDN;			// 소지금
	short		sCityRank;		// 시민등급

	short		sLevel;			// 레벨
	BYTE		byClass;		// 클래스 (격투 = 0, 지팡이 = 1, 도검 = 2, 총기 = 3)

	typedef struct _tagSkill	// Skill
	{
		short	sSid;
		BYTE	tLevel;
	}UserSkill[TOTAL_SKILL_NUM];

	BYTE		tHavePsi;		// 사이오닉 보유수량
	typedef	struct _tagPsionic	// 사이오닉 보유수량이 1이상인 경우 전송
	{
		short	sSid;
		BYTE	tOnOff;
	} UserPsi[tHavePsi];

	typedef struct _tagItem		// Item;
	{
		short	sLevel;				// 아이템 장착 레벨@@@@@@@
		short	sSid;
		short	sDuration;
		short	sBullNum;
		short	sCount;
		BYTE	tMagic[6];		// 매직속성
		BYTE	tIQ;			// Item Quality
	}UserItem[TOTAL_ITEM_NUM];

	short		sEbody[4];		// 장착한 E_Body sSid, 없으면 -1

	DWORD		dwExpNext;		// 다음 레벨이 되기위한 필요 경험치

	DWORD		dwAbnormal		// 상태이상정보(Damaged)

								// const DWORD ABNORMAL_NONE			=	0;
								// const DWORD ABNORMAL_POISON			=	1;
								// const DWORD ABNORMAL_CONFUSION		=	1 << 2;
								// const DWORD ABNORMAL_PARALYSIS		=	1 << 3;
								// const DWORD ABNORMAL_BLIND			=	1 << 4;
								// const DWORD ABNORMAL_LIGHT			=	1 << 5;
								// const DWORD ABNORMAL_FIRE			=	1 << 6;
								// const DWORD ABNORMAL_COLD			=	1 << 7;
								// const DWORD ABNORMAL_HASTE			=	1 << 8;
								// const DWORD ABNORMAL_SHIELD			=	1 << 9;
								// const DWORD ABNORMAL_HIDE			=	1 << 10;
								// const DWORD ABNORMAL_DEX_UP			=	1 << 11;
								// const DWORD ABNORMAL_MAX_HP_UP		=	1 << 12;
								// const DWORD ABNORMAL_ADAMANTINE		=	1 << 13;
								// const DWORD ABNORMAL_MIGHTYWEAPON	=	1 << 14;
								// const DWORD ABNORMAL_BERSERKER		=	1 << 15;
								// const DWORD ABNORMAL_HIEXP			=	1 << 16;
								// const DWORD ABNORMAL_MAGICFIND		=	1 << 17;
								// const DWORD ABNORMAL_NOCHAT			=	1 << 18;
								
								// const DWORD ABNORMAL_FASTRUN			=	1 << 19;
								// const DWORD ABNORMAL_MINDSHOCK		=	1 << 20;
								// const DWORD ABNORMAL_MINDGUARD		=	1 << 21;
								// const DWORD ABNORMAL_PSISHIELD		=	1 << 22;
								// const DWORD ABNORMAL_PIERCING_SHIELD	=	1 << 23;

								// const DWORD OPERATION_MODE			=	1 << 31;	// 운영자 투명 옵션

	short		sChangeClass[CLASS_NUM];	// 전직정보

  	int			iGuildIndex;	// 길드 인덱스
	VarChar		szGuildName;	// 길드 이름
	short		sVersion;		// 길드 문양 버젼

	short		sMaxWeight;
	short		sCurWeight;
*/

const BYTE NPC_INFO				= 3;
/*
(C <- S)		// Send NPC Info

	BYTE		Mode;			// 01(INFO_MODIFY)	: NPC 정보 변경
								// 02(INFO_DELETE)	: NPC 정보 삭제

	short		nid;			// NPC index
	short		pid;			// NPC Picture Index
	VarChar		szName;			// NPC Name
	short		nPosX;			// X Position
	short		nPosY;			// Y Position
	BYTE		tState;			// NPC 상태
								// 00	: NPC Dead
								// 01	: NPC Live

	BYTE		tNpcKind;		// 00	: Monster
								// 01	: NPC

  	short		sMaxHP;			// 최대 HP
	short		sHP;			// 현재 HP

	short		sStepDelay;		// 걷는 속도 보정

	BYTE		tColor;			// 몹의 색을 구분

	short		sDimension;		// 현재 맵에 셋팅할수 있는 차원 번호
*/

const BYTE	ITEM_INFO			= 4;
/*
	short		sTotalIndex;	// 총 아이템 가지 종류 수

	short		sSid;
	short		sPid;
	Varchar		strName;
	Varchar		strText;
	BYTE		byNeedSP;
	DWORD		iDN;
	BYTE		byRLevel;
	BYTE		byClass;
	BYTE		byWear;
	short		sDuration;
	short		sDefense;
	BYTE		byAX;
	BYTE		byAY;
	BYTE		byAZ;
	BYTE		byHitRate;
	BYTE		byCritical;
	short		sAttackDelay;
	BYTE		byRange;
	BYTE		byErrorRate;
	short		sBullNum;
	BYTE		byBullType;
	BYTE		bySubAttack;
	BYTE		bySubDefense;
	BYTE		bySubCure;
	short		sRepairHP;
	short		sRepairPP;
	short		sRepairSP;
	short		sEvent;

	...							// 해당 수만큼 반복한다.
*/

const BYTE	SYSTEM_MSG			= 5;
/*
	(C <- S)		// 서버에서 클라이언트로 메세지를 보낸다.

	BYTE		type;			// 00 : 특별한 메세지, 반드시 보여져야 하는것, 메세지 박스로
								//		클라이언트는 강제종료한다 (ERROR MESSAGE).

								// 01 : Normal Message (Infomation Message)
								// 02 : Error Message (유저에게 에러정보를 보낼 때)
								// 03 : NPC Message (NPC가 하는 말)
								// 04 : 운영자 전체 스크롤 메세지
								// 05 : Dissconnect Message (사용기간(시간)이 지난 유저에게 보낼때)
	Varchar		Msg;
*/

const BYTE CLIENT_TIMER			= 6;
/*
	(C -> S)		// 클라이언트에서 1초이상 패킷전송이 없으면 보낸다.
	// 전달값 없음
*/

const BYTE SET_CLIENT_WORLD		= 7;
/*
	(C <- S)		// 날씨를 셋팅한다

	BYTE		type;			// 01 : 게임상 시간
								// 02 : 비
								// ...

	// 01 : 게임상 시간
		BYTE		tTime;		// 시간(0~24)

	// 02 : 비
		BYTE		OnOff;			// 00 : 오프
									// 01 : 온

*/

const BYTE CHANGE_ITEM_INFO		= 8;
/*
	(C <- S)		// 장착 무기 변동일때 보낸다.

	int			uid;			// User index

	short		sEquipItem[10];	// 0 = 헬멧
								// 1 = 갑옷
								// 2 = 머리 액세서리
								// 3 = 몸 액세서리
								// 4 = 오른쪽 손 무기
								// 5 = 왼쪽   손 무기
								// 6 = 오른쪽 악세사리
								// 7 = 왼쪽   악세사리
								// 8 = 바지
								// 9 = 신발
								// 아이템을 장착하지 않은 슬롯은 id == -1
*/

const BYTE USERINFO_REQ			= 9;
/*
	(C -> S)		// 특정 USER, NPC의 정보를 요청한다.

	int			uid;			// User or NPC ID
*/

//#################################################################
//	Login UI	(10 ~ 29)
//#################################################################

const BYTE SESSION_LOGIN_REQ	=	10;
/*
	(C -> S)		// Session Login Request

	VarChar		id[ACCOUNT_LENGTH];
	VarChar		password[PASSWORD_LENGTH];
*/

const BYTE SESSION_LOGIN_RESULT	=	11;
/*
	(C <- S)		// Session Login Result

	BYTE		result;			// 01 	: Login Success
								// else	: Login Fail
	// 성공인 경우
	// 보내는 값 없음

	// 실패인 경우
	BYTE		error_code;		// 01	: 존재하지 않는 ID
								// 02	: Password 불일치
								// 03	: 현재 Account 사용중
								// ...
								// 255	: 알 수 없는 에러
*/

const BYTE ACCOUNT_LOGIN_REQ =		12;
/*
	(C -> S)		// Account Login (암호화 안함)

	VarChar		id[ACCOUNT_LENGTH];
	short		myserver;		//	1 - 이카루스
									2 - 엘파도르
									3 - 가네지아
									4 - 필립포
									5 - 아스트
									6 - 그랑디에
									7 - 페세우스
									8 - 밀라디
									9 - 루이네트
									10- 타르샤	
*/

const BYTE ACCOUNT_LOGIN_RESULT =	13;
/*
	(C <- S)	// Account Login Result (암호화 안함)

	BYTE		result;			// 01	: Account Login Success
								// else : Account Login Fail
	// 실패인 경우 -------
	BYTE		nErrorCode;		// 01	: Invaild Account
								// 02	: 같은 계정으로 이미 누군가가 접속하여 있습니다.
								// ...
								// 255	: 알수 없는 에러

	// 성공인 경우 -------
	BYTE		nChar;			// Exist Character Number

	// nChar >= 1 인경우 nChar의 수만큼 반복
	{
	BYTE		nIndex;						// Character Index
	VarChar		szName[CHAR_NAME_LENGTH];	// 01 번째 Character
	short		STR;
	short		CON;
	short		DEX;
	short		VOL;
	short		WIS;
	DWORD		Skin;			// 피부색
	DWORD		Hair;			// 머리색
	BYTE		bGender;		// 남, 여
	Varchar		szFace[10];		// 얼굴모양

	BYTE		Class;			// 격투 = 0, 지팡이 = 1, 도검 = 2, 총기 = 3
	short		Level;
	short		HP;
	short		PP;
	short		SP;

  	typedef struct _tagSkill	// Skill
	{
		short	sSid;
		BYTE	tLevel;
	}UserSkill[TOTAL_SKILL_NUM];

	char		strWearItem[20];// 장착하고 있는 아이템 리스트
								// 그림번호[2] * EQUIP_ITEM_NUM
								// 그림번호 == -1 이면 장착하지 않음

	short		sEBodyItem[4];	// 0 = 머리
								// 1 = 몸
								// 2 = 팔
								// 3 = 다리
								// 아이템을 장착하지 않은 슬롯은 id == -1

  	varchar		strIPAddr[20];	// 이 캐릭터가 붙어야할 서버
	int			nPort;			// 이 캐릭터가 붙어야할 서버의 Listen포트
	}

	short	myserver;
	varchar	strAccount[ACCOUNT_LENGTH];
*/

const BYTE GAME_START_REQ =				14;
/*
	(C -> S)	// Game Login  (암호화 안함)

	VarChar		szCharName[CHAR_NAME_LENGTH];

	short		myserver;		// CharInfoServer에서 받은 값	

	varchar		szAccountID[ACCOUNT_LENGTH+1];

*/

const BYTE GAME_START_RESULT =			15;
/*
	(C <- S)	// Game Login Result  (암호화 안함)

	BYTE		result;			// 01	: Login Success
								// else	: Login Fail

	// 실패인 경우 ------		// 01	: Invaild ID
								// 02	: DB에 없는 ID
								// 03	: Invalid Zone Number
								// 04	: Invalid Position
								// 05	: 현재 ID 사용중
								// ...
								// 255	: 알 수 없는 에러

	short		CurrZone;		// 현재 Zone Number
	int			uid;			// User Index
	short		PosX;			// Map 의 X 좌표
	short		PosY;			// Map 의 Y 좌표

	BYTE		tDir;			// 현재 보고있는 방향

	BYTE		tTime;			// 시간(0~24)
	BYTE		tMinute;		// 분  (0~60)

    Varchar		public_key;		// int64
	DWORD		dwSerial;		// 시리얼 시작 번호
*/

const BYTE NEW_ACCOUNT_REQ =		16;
/*
	(C -> S)	// New Session Account Req

	VarChar	szUserID[ACCOUNT_LENGTH];
	VarChar	szPassword[PASSWORD_LENGTH];
	VarChar	szRealName[40];
	VarChar	szSocNo[15];
	VarChar	szAddress[80];
	VarChar	szTel[20];
	VarChar	szEmail[30];
	VarChar	szQuiz01[50];
	VarChar	szAnswer01[50];
*/

const BYTE NEW_ACCOUNT_RESULT =		17;
/*
	(C <- S)	// New Session Account Result
	BYTE	result;				// 01 	: New Account Create Success
								// else	: New Account Create Fail
*/

const BYTE	NEW_CHAR_REQ		= 18;
/*
	(C -> S)	// Make New Character (암호화 안함)
	VarChar		szAccount[ACCOUNT_LENGTH];			// Account
	BYTE		nIndex;								// Char Index (몇번째 캐릭터?)
	VarChar		szCharName[CHAR_NAME_LENGTH];		// Char Name

	DWORD		Skin;				// 피부색
	DWORD		Hair;				// 머리색
	BYTE		bGender;			// 남, 여
	char		szFace[10];			// 얼굴모양
									// 1 : 머리
									// 2 : 얼굴
									// 3 : 눈
									// 4 : 코
									// 5 : 입
									// 6 : 악세사리 1
									// 7 : 악세사리 2
									// 8~10 : 예비

	BYTE		Class;				// 격투 = 0, 지팡이 = 1, 도검 = 2, 총기 = 3

*/

const BYTE	NEW_CHAR_RESULT		= 19;
/*
	(C <- S)	// Make New Character Result (암호화 안함)

	BYTE		result;				// 01	: Make New Character Success
									// else : Make New Character Fail
	// 실패인 경우 -------
	BYTE		nErrorCode;			// 01	: Invaild Account
									// 02	: Invaild Char Num
									// 03	: Invalid Ability (잘못된 능력치)
									// 04	: Invalid Skin
									// 05	: Invalid Hair
									// 06	: Invalid Face
									// 07	: Exist Character Name(이미 존재하는 이름)
									// 08	: Invalid Char Name
									// 09	: Invalid Ablity Sum
									// 10	: Invalid Class
									// ...
									// 255	: 알수 없는 에러

	// 성공일경우
	BYTE		nIndex;						// Character Index
	VarChar		szName[CHAR_NAME_LENGTH];	// Character Name

	short		STR;
	short		CON;
	short		DEX;
	short		VOL;
	short		WIS;

	DWORD		Skin;				// 피부색
	DWORD		Hair;				// 머리색
	BYTE		bGender;			// 남, 여

	char		szFace[10];			// 얼굴모양

	BYTE		Class;				// 격투 = 0, 지팡이 = 1, 도검 = 2, 총기 = 3

	short		Level;
	short		HP;
	short		PP;
	short		SP;

  	typedef struct _tagSkill	// Skill
	{
		short	sSid;
		BYTE	tLevel;
	}UserSkill[TOTAL_SKILL_NUM];

	char		strWearItem[20];// 장착하고 있는 아이템 리스트
								// 그림번호[2] * EQUIP_ITEM_NUM
								// 그림번호 == -1 이면 장착하지 않음

*/

const BYTE	DELETE_CHAR_REQ		= 20;
/*
	(C -> S)	// Delete Character (암호화 안함)

	VarChar		szAccount[ACCOUNT_LENGTH];		// Account
	VarChar		szCharName[CHAR_NAME_LENGTH];	// Char Name
	BYTE		nIndex;							// Char Index (몇번째 캐릭터?)
	Varchar		szJumin[13];					// 주민등록번호
	Varchar		szIP[15];						// 삭제한 컴퓨터의 IP
*/

const BYTE	DELETE_CHAR_RESULT	= 21;
/*
	(C <- S)	// Delete Character Result (암호화 안함)
	BYTE		result;				// 01	: Delete Character Success
									// else : Delete Character Fail

	// 성공인경우
	BYTE		nIndex;				// Character Index

	// 실패인 경우 -------
	BYTE		nErrorCode;			// 01	: Invaild Account
									// 02	: Invaild Char Name
									// 03	: Invaild Char Index
									// 04	: Database Error
									// 05	: Invalid Jumin Bunho
									// 06	: 주민번호가 틑림
									// 07	: 길드 마스터일때는 길드를 먼저 해산하고 삭제..
									// ...
									// 255	: 알수 없는 에러
*/

const BYTE	LOGOUT_REQ			= 22;
/*
	(C -> S)	// Log Out Req
	// 전달값 없음
*/

const BYTE	REROLL_REQ			= 23;
/*
	(C -> S)	// Reroll Request

	BYTE		Class;				// 격투 = 0, 지팡이 = 1, 도검 = 2, 총기 = 3
*/

const BYTE	REROLL_RESULT		= 24;
/*
	(C <- S)	// Reroll	Result
	BYTE		STR;			// 힘
	BYTE		CON;			// 건강
	BYTE		DEX;			// 민첩
	BYTE		VOL;			// 의지
	BYTE		WIS;			// 지혜
*/

const BYTE	RESTART_REQ			= 25;
/*
	(C -> S)	// Restart문의
*/

const BYTE	RESTART_RESULT		= 26;
/*
	(C <- S)	// RESTART_REQ	Result

	BYTE		result;			// 01	: Restart Success
								// else : Restart Fail
*/

const BYTE	CHECK_ID_REQ		= 27;
/*
	(C -> S)	// Check Character ID Request
	
	VarChar		szCharID[CHAR_NAME_LENGTH];	// 캐릭터이름
*/

const BYTE	CHECK_ID_RESULT		= 27;		// Packet 재활용
/*
	(C <- S)	// Check Character ID Result
	
	BYTE		tResult;		// 00 : 같은 이름의 캐릭터가 이미 존재합니다.
								// 01 : 사용하실 수 있는 아이디 입니다.
*/

//#################################################################
//	CHAT, BBS		(28 ~ 43)
//#################################################################

const BYTE	MOVE_CHAT_REQ		= 28;
/*
	(C -> S)	// Chat Move Req
	short		will_x;				// 움직이려고 하는 좌표의 X 값
	short		will_y;				// 움직이려고 하는 좌표의 Y 값
*/

const BYTE	MOVE_CHAT_RESULT	= 29;
/*
	(C <- S)	// Chat Move Result

	BYTE		result;				// 01	: Move Success
									// else	: Move Fail

	// 성공시
	int			uid;				// User Index
	short		will_x;				// 움직이려고 하는 좌표의 X 값
	short		will_y;				// 움직이려고 하는 좌표의 Y 값
*/

const BYTE	CHAT_REQ			= 30;
/*
	(C -> S)	// Chat Req

	BYTE		Type;				// 01 : Normal Chat
									// 02 : 귓속말
									// 03 : 8 화면 외침
									// 04 : Bunch Chat
									// 05 : Buddy Chat
									// 06 : Buddy 초청
									// 07 : Buddy 탈퇴
									// 10 : 몬스터 잡기 - 성공시 결과는 MOVE_CHAT_RESULT 로 보냄
									// 11 : 귓말허용
									// 12 : 귓말거부
									// 13 : 인사
									// 14 : 도발
									// 15 : 유저 송환		--성공시 양쪽에 결과는 MOVE_CHAT_RESULT 로 보냄
									// 16 : 유저 강제 이동  -- 성공시 양쪽에 결과는 MOVE_CHAT_RESULT 로 보냄
									// 17 : 몹을 유저근처로 강제 소환
									// 18 : 길드 가입
									// 19 : 길드 해산
									// 20 : 길드 탈퇴
									// 21 : 길드 추방
									// 22 : 아이템 받기, 거부
									// 23 : 운영자 투명
									// 24 : 운영자 투명 해제
									// 25 : 전체 채팅	-- 현재 운영자만 할수있음...
									// 26 : 필드 길드전
									// 27 : 필드전 항복
									// 28 : PK누적값 보기
									// 29 : 1인 동반 워프
									// 30 : 길드원 목록 보기
									// 31 : 공성전 신청 길드를 보여준다.
									// 32 : 포트리스 성문을 열고 닫는다.
									// 33 : 길드 권한 이양
									// 34 : 길드 권한 중지
									// 35 : 길드 원소환용 유저리스트
									// 36 : 길드원 소환

	VarString	UserID(CHAR_NAME_LENGTH)	// 02의 경우 ID 보냄

	VarString	Msg;						// 메세지(6, 11, 12, 13, 14 의 경우 메세지 없음)

	// 클라이언트에서 파싱해서 type으로 conversion
	|--------------------------------------------------------------------------------
	|	채팅 명령어 : '/' 로 시작된다.
	|--------------------------------------------------------------------------------
	|	기능		| 영문 명령어	| 한글 명령어	|	설명
	|---------------|---------------|------------------------------------------------
	|*	설정/해제	| /TO ID		| /귓말 ID 		|	해당 ID에 대한 귓속말 설정, 해제
	|	(client)	| /GUILD		| /길드 		|	자신의 길드원 귓속말 설정/해제(C)
	|				| /BUDDY		| /버디			|	자신의 BUDDY 와 귓속말 설정/해제(C)
	|				| /SHOUT		| /외침			|	외치기 모드 설정/해제(N)
	|---------------|---------------|-------------------------------------------------
	|	귓속말		| /TO ID Msg	| /귓말 ID Msg	|	해당 ID 에게 귓속말
	|				| /GUILD Msg	| /길드	Msg		|	자신의 길드원과 전체대화
	|				| /BUDDY Msg	| /버디	Msg		|	자신의 BUDDY 와 귓속말(C)
	|				| /SHOUT Msg	| /외침	Msg		|	사용자를 중심으로 8 화면 외침, 스테미나 소비(C)
	|---------------|---------------|------------------------------------------------
	|	사람찾기	| /FI ID		| /찾기 ID		|	지정한 ID 가 게임중 인지 체크
	|				|				| 				|	별도의 패킷으로 처리한다
	|---------------|---------------|------------------------------------------------
	|*	수신거부	| /EX ID		| /차단 ID		|	수신거부 설정/해제 (해당 ID의 모든 메세지 거부)
	|---------------|---------------|------------------------------------------------
	|	귓말허용	| /TOY			| /귓말켬		|
	|---------------|---------------|------------------------------------------------
	|	귓말거부	| /TON			| /귓말끔		|
	|---------------|---------------|------------------------------------------------
	|*수신거부리스트| /EXLIST		| /차단목록		| 현재 수신거부중인 ID들을 보여준다.
	|---------------|---------------|------------------------------------------------
	|*음악/소리 조절| /MUSIC		| /음악			| 음악 ON/OFF(N)
	| (client)		| /SOUND		| /소리			| 효과음 ON/OFF(N)
	|---------------|---------------|------------------------------------------------
	|	거래		| /TRADE ID		| /거래 ID		| 해당 ID에 대해 거래창을 연다.(N)
	|---------------|---------------|------------------------------------------------
	|	위치		| /MOVE X Y		| /이동 X Y		| 해당위치로 이동(N)
	|---------------|---------------|------------------------------------------------
	| 몬스터잡기    | /MOP 이름     | /몹 이름      | 해당 이름의 몬스터 근처로 이동
	|---------------|---------------|------------------------------------------------
	| 몬스터소환	| /MOPCALL 이름	| /몹소환 이름  | 해당 이름의 몬스터를 운영자근처로 소환
	|---------------|---------------|------------------------------------------------
	| 유저 소환     | /CALL 이름    | /소환 이름    | 해당 이름의 유저를 운영자 근처로 이동
	|---------------|---------------|------------------------------------------------
	| 유저 강제이동 | /REMOTE 이름  | /원격 이름  X Y | 해당 이름의 유저를 특정위치로 이동
	|---------------|---------------|------------------------------------------------
	| 운영자 투명	| /CLOAKY		| /투명			| 운영자를 투명상태로 만든다.
	|---------------|---------------|------------------------------------------------
	| 영자 투명 해제| /CLOAKN		| /해제			| 운영자 투명상태에서 일반 상태로 만든다.
	|---------------|---------------|------------------------------------------------
	| 전체 채팅		| /ANNOUNCE		| /전채			| 접속한 모든 유저에게 메세지를 날린다.
	|---------------|---------------|------------------------------------------------
	| 버디 초대		| /INVITE 이름  | /초대 이름	 | 해당 이름의 유저를 버디에 가입시킨다.
	|---------------|---------------|------------------------------------------------
	| 버디 탈퇴		| /LEAVE		| /탈퇴			 | 자신이 버디에서 탈퇴한다.
	|---------------|---------------|------------------------------------------------
	| 버디 탈퇴		| /LEAVE  이름	| /탈퇴  이름	 | 버디장이 특정 유저를 버디에서 탈퇴시킨다.
	|---------------|---------------|------------------------------------------------
	| 길드 문양등록	| /MARK  이름	| /문장  BMP	 | (Client자체)길드 문양을 등록한다.
	| 길드 가입		| /				| /길드가입		 | 해당 길드에 가입한다.
	| 길드 해산		| /				| /길드해산		 | 해당 길드를 해산한다.
	| 길드 탈퇴		| /				| /길드탈퇴		 | 해당 길드에서 탈퇴한다.
	| 길드 추방		| /				| /길드추방	이름 | 해당 길드에서 길마가 특정 유저를 탈퇴시킨다.
	|---------------|---------------|------------------------------------------------
	| 아이템 받기	| /				| /아이템받기	 | ( ITEM_MODE_CHAT OFF)아이템 받기옵션을 활성화한다.
	| 아이템 거부	| /				| /아이템거부	 | ( ITEM_MODE_CHAT ON )아이템 거부옵션을 활성화한다.
	|---------------|---------------|------------------------------------------------
	| 길드 필드전	| /				| /전쟁 길드이름 | 해당 길드를 상대로 필드전을 신청(/전쟁 Guild_ID 길드이름)
	|---------------|---------------|------------------------------------------------
	| 필드전 항복	| /				| /항복			 | 해당 길드를 상대로 항복을 선언한다.
	|---------------|---------------|------------------------------------------------
	| PK누적값	보기| /PK			| /피케이		 | 현재 누적된 PK횟수를 본다.
	|---------------|---------------|------------------------------------------------
	| 1인 동반위프	| /COPY			| /카피	ID		 | 유저를 지정하여 임의의 장소로 이동한다.
	|---------------|---------------|-----------------------------------------------
	| 길드원 전체보기|/GUILD		| /길드원		 | 길드원 전체 목록을 보여준다.
	|---------------|---------------|------------------------------------------------
	| 신청길드 보기 | /				| /신청길드		 | 길드전을 신청한 전체 길드 목록을 보여준다.
	|---------------|---------------|------------------------------------------------
	| 성문열고 닫기 | /				| /출입			 | 포트리스 성문을 열고 닫는다.
	|---------------|---------------|------------------------------------------------
	| 길드권한 부여	| /endow		| /부여			 | 길마가 부길마를 지정한다.
	|---------------|---------------|------------------------------------------------
	| 길드권한 중지 | /stop			| /권한중지		 | 부길마의 권리를 반납한다.

  // * 가 있는 명령어는 클라이언트에서 자체처리
*/

const BYTE	CHAT_RESULT			= 31;
/*
	(C <- S)	// Chat Result

	BYTE		result;				// 01	: 성공
									// else	: 실패

	// 실패일 경우
	BYTE		error_code;			// 01	: 스테미너 부족(외치기의 경우)
									// 02	: 귓말 거부중
									// 03	: 상대 없음 (귓말, 사람찾기의 경우)
									// 04	: 접속한 길드가 하나도 없음(길드 귓말)
									// 05	: 접속한 Buddy가 하나도 없음(Buddy 귓말)
									// 06	: 잘못된 유저아이디(귓말, 사람찾기의 경우)
									// 07	: 해당 길드가 존재하지 않는다.
									// 08	: 해당 길드에 가입한 유저가 아니다.
									// 09	: 이미 다른 길드에 가입한 유저다.
									// 10	: 길드 짱	권한이 없다.
									// 11	: 최대 인원수를 넘었다.
									// 12	: 상대길드가 전쟁중이다.
									// ...
									// 255	: 알수 없는 에러

	// 성공일 경우
	BYTE		Type;				// 01 : Normal Chat
									// 02 : 귓속말
									// 03 : 8 화면 외침
									// 04 : Guild Chat
									// 05 : Buddy Chat
									// 10 : 사람찾기
									// 11 : 귓말허용
									// 12 : 귓말거부

	int			uid;				// User Index		(Type이 01~ 10 사이만 전송)
	VarString	Name;				// Character Name	(Type이 01~ 10 사이만 전송)
	VarString	Msg;				// Message			(Type이 01~ 09 사이만 전송)
*/

const BYTE	FIND_USER_REQ		= 32;
/*
	(C -> S)	// User 가 접속중인지 확인

	VarString	UserName[CHAR_NAME_LENGTH]	// User Name
*/

const BYTE	FIND_USER_RESULT	= 33;
/*
	(C <- S)	// Find User Result

	BYTE		result;				// 00	: 성공
									// 01	: 잘못된 유저아이디
									// 02	: 상대 없음
									// ...
									// 255	: 알수 없는 에러

	VarString	UserName;			// Character Name
*/

const BYTE	BBS_OPEN			= 34;
/*
	(C <- S)	// BBS를 Open 한다.

	short	BBS_NUM;				// BBS Number
	short	nCount;					// 줄수
	varchar nData;					// 게시물 데이터(번호, 작성자 ID, 작성일, 조회수, 제목)
									// int		iIndex,
									// Varchar	strWriter,
									// Varchar	strTime,
									// int		iView,
									// Varchar	strTitle

*/

const BYTE	BBS_NEXT			= 35;
/*
	(C -> S) // BBS의 게시물 정보를 읽는다.

	short	BBS_NUM;				// BBS Number
	int		nIndex;					// 읽고자 하는 게시물 정보의 시작번호
*/

const BYTE	BBS_NEXT_RESULT		= 36;
/*
	(C <- S)	// 다음 게시물 정보를 보낸다.

	short	BBS_NUM;				// BBS Number
	short	nCount;					// 줄수
	varchar nData;					// 게시물 데이터(번호, 작성자 ID, 작성일, 조회수, 제목)
									// int		iIndex,
									// Varchar	strWriter,
									// Varchar	strTime,
									// int		iView,
									// Varchar	strTitle
*/

const BYTE	BBS_READ			= 37;
/*
(C -> S) // 게시물의 내용을 읽는다.

	short	BBS_NUM;				// BBS Number
	int		nIndex;					// 읽고자 하는 게시물의 번호
*/

const BYTE	BBS_READ_RESULT		= 38;
/*
(C <- S) // 게시물의 내용을 보낸다.

	short	BBS_NUM;				// BBS Number
	int		nIndex;					// 읽고자 하는 게시물의 번호
	Varchar Writer;					// 작성자
	Varchar Title;					// 제목
	Varchar Time;					// 작성일자
	VarData Contents;				// 내용
*/

const BYTE	BBS_WRITE			= 39;
/*
	(C -> S) // 게시물을 작성한다.

	short	BBS_NUM;				// BBS Number
	VarChar	Title;					// 게시물 제목
	VarData	Contents;				// 게시물 내용
*/

const BYTE	BBS_EDIT			= 40;
/*
	(C -> S) // 게시물을 수정한다.

	short	BBS_NUM;				// BBS Number
	int		nIndex;					// 게시물 번호
	VarChar	Title;					// 게시물 제목
	VarData	Contents;				// 게시물 내용
*/

const BYTE	BBS_ERROR			= 41;
/*
	(C <- S)	// 게시판 관련된 에러 리턴

	BYTE		result;				// 01	: 성공
									// 02	: 권한 없음(자신의 게시물이 아니거나 운영자가 아님)
									// 03	: 게시물이 삭제됨
									// ...
									// 255	: 알수 없는 에러
*/

const BYTE	BBS_DELETE			= 42;
/*
	(C -> S) 	// 게시물을 삭제한다.

	short		BBS_NUM;			// BBS Number
	int			nIndex;				// 게시물 번호
*/

//#################################################################
//	Item		(43 ~ 63)
//#################################################################
const BYTE	ITEM_BULLNUM		= 43;
/*
	(C <- S)	// 아이템의 잔탄수(레티륨팩량)가 변경된것을 알려준다.

	BYTE	tSlot;					// 아이템 슬롯번호
	short	sBullBum;				// 변경된 잔탄수(레티륨팩량)
*/

const BYTE	ITEM_DURATION		= 44;
/*
	(C <- S)	// 아이템의 내구도가 변경된것을 알려준다.

	BYTE	tSlot;					// 아이템 슬롯번호
	short	sDuration;				// 변경된 내구도
*/

const BYTE	ITEM_LOAD_REQ		= 45;
/*
	(C -> S) 	// 맵 또는 몹에게서 아이템을 획득

	BYTE	byReqType;				// 1 : 몹
									// 2 : 맵

	// 1번 몹일 경우
	short	sSid;					// 몬스터 인덱스

	// 2번 맵일경우
	short	sX;						// 맵에서
	short	sY;
*/

const BYTE	ITEM_LOAD_RESULT	= 46;
/*
	(S -> C) // 인증을 하고 해당 리스트를 보낸다.
	BYTE	result;					// 00	: 아이템 없음(실패)
									// 01	: 성공시

		// 01 아이템 성공시
		BYTE	ChangedSlotNum;		// 변화된 슬롯의 갯수

		typedef struct _tagMoveItem
		{
			BYTE	tSlot;
			short	sLevel;				//@@@@@@@@
			short	sSid;
			short	sDuration;
			short	sBullNum;
			short	sCount;
			BYTE	tMagic[6];
			BYTE	tIQ;
		} MoveItemInfo[ChangedSlotNum];

	// 돈 성공시
	// (C <- S) MONEY_CHANGED로 전송

	// 00 : 실패시
	error_01 : Item Load 범위를 벗어났다
	error_02 : 잘못된 좌표
	error_03 : 우선권이 없다
	error_04 : 무게를 초과하였다
	error_05 : 비어있는 인벤이 없다 
	error_08 : 줍는 확률 실패 

	error_06 : 유령아이템이다.
	error_07 : 시스템 업뎃 실패
	error_255 : 알수 없는에러
*/

const BYTE	ITEM_GIVE_REQ		= 47;
/*
	( C -> S ) // 상대방에게 아이템, 돈을 줄때

	BYTE	tType;					// 00	: 맵상에 버림
									// 01	: 상대방에게 준다

	BYTE	tObject					// 00	: 돈
									// 01	: 아이템
	//  00	: 맵상에 버림

		short		will_x;			// 맵상에서 좌표
		short		will_y;			//

  		//	00	: 돈일경우
			DWORD	dwDN;				// 돈 액수

		//	01	: 아이템일경우
			BYTE	bySlotId;			// 인벤토리창의 인덱스
			short	sCount				// 얼만큼 갯수


	//  01	: 상대방에게 준다(?)

		//	00	: 돈일경우
			int		uid;				// 받을 상대방
			DWORD	dwDN;				// 돈 액수

		//	01	: 아이템일경우
			int		uid;				// 받을 상대방
			BYTE	bySlotId;			// 인벤토리창의 인덱스
			short	sCount				// 얼만큼 갯수


 // 돈 성공시
// (C <- S) MONEY_CHANGED로 전송
*/

const BYTE	ITEM_GIVE_RESULT	= 48;
/*
	( C <- S ) // 상대방에게 주고 또는 맵에 버리고 내 인벤에서 지운다.

	BYTE	result;					// 00	: 실패
									// 01	: 성공

	// 00 실패면
	BYTE	error;					// 01	: 줄수있는 상대가 없다.
									// 02	: 상대 인벤에 여유공간이 부족하다.
									// 03	: 상대방이 거부
									// 04	: 맵상에 버릴만한 공간이 없다(?).
									// 05	: 내 인벤에 아이템이 없다.
									// 06	: 상대에게 돈을 더줄수가 없다.
									// ...
									// 255	: UnKnown Error

	// 01 성공이면
		typedef struct _tagItem
		{
			byte	bySlot;
			short	sLevel;
			short	sSid;
			short	sDuration;
			short	sBullNum;
			short	sCount;
			BYTE	tMagic[6];
			BYTE	tIQ;
		} ItemInfo;

*/


const BYTE	ITEM_TRADE_REQ		= 49;
/*
	( C -> S -> Other C ) // 아이템..교환을 상대방에게 신청한다

	int			uid;				// 상대방 uid
	Varchar		UserName;			// 상대방 이름
	BYTE		Mode;				// 00 : 요청취소
									// 01 : 요청
									// 02 : 승낙
									// 03 : 거절
									//...
									// 255: 알 수 없는 에러

*/

const BYTE	ITEM_TRADE_RESULT	= 50;
/*
	( Other C -> S -> C ) // 아이템..교환을 상대방에게 응답한다

	int			uid;				// 상대방 uid
	Varchar		UserName;			// 상대방 이름
	BYTE		result;				// 01	: 성공(승낙)
									// else	: 실패(거절등...)

	// 실패일 경우
	BYTE		error_code;			// 01 : 상대편 거절(취소)
									// 02 : 준비안됨
									// 03 : 다른사람과 거래중
									// 04 : 상대편을 찾을 수 없음
									// 05 : 거리가 너무 떨어짐
									// 06 : 자신이 거절
									// ...
									// 255: 알 수 없는 에러
*/

const BYTE	EXCHANGE_REQ		= 51;
/*
	( C -> S -> C(모두다))			// 실제로 아이템 교환을 한다.

	int			uid;				// 상대편 uid

	BYTE		Type;				// 0 = 취소
									// 1 = 자신이 교환 승낙
									// 2 = 상대편이 교환 승낙
									// 3 = 자신이 아이템 올림
									// 4 = 상대편이 아이템 올림
									// 5 = 자신이 돈을 올림
									// 6 = 상대편이 돈을 올림


	// Type 이 3 일 경우
	(C -> S)
	BYTE		tSlotId;			// 인벤토리창의 인덱스		(올릴때 항목) 그외는 받을때 항목
	short		dwCount;			// 얼만큼 갯수				(올릴때 항목)

			(S -> C)
				// 트레이드에 올라갈 아이템
			short		sLevel;				// 아이템 장착 레벨		///@@@@@@@@
			short		sItemID;			// 아이템 인덱스
			short		wDur;				// 내구도
			short		byBullNum;			// 장탄수
			short		dwCount;			// 얼만큼 갯수
			BYTE	    tMagic[6];			// 매직속성
			BYTE		tIQ;				// Item Quality

				// 인벤토리에서 변동된 아이템
			BYTE		tSlotId;			// 인벤토리창의 인덱스
			short		sLevel;				// 아이템 장착 레벨
			short		sItemID;			// 아이템 인덱스
			short		wDur;				// 내구도
			short		byBullNum;			// 장탄수
			short		dwCount;			// 얼만큼 갯수
			BYTE	    tMagic[6];			// 매직속성
			BYTE		tIQ;				// Item Quality

	// Type 이 4일 경우
	short		sLevel;				// 아이템 장착 레벨
	short		sItemID;			// 아이템 인덱스
	short		wDur;				// 내구도
	short		byBullNum;			// 장탄수
	short		dwCount;			// 얼만큼 갯수
	BYTE	    tMagic[6];			// 매직속성
	BYTE		tIQ;				// Item Quality

	// Type 이 5 일 경우
	DWORD		dwCount;			// 거래에 올린 총 합의 돈
	DWORD		dwMyMoney;			// 자기에게 남은돈

	// Type 이 6 일 경우
	DWORD		dwCount;			// 거래에 올린 총 합의 돈
*/

const BYTE	EXCHANGE_RESULT		= 52;
/*
	( C <- S )						// 결과값

	BYTE		result;				// 0 = 거절
									// 1 = 교환 동의
									// 2 = 서버 거절
	// 거절, 서버거절의 경우
	BYTE		error_code;			// 1	: 잘못된 유저 아이디
									// 2	: 교환신청을 한 사용자가 아님
									// 3	: 잘못된 아이템 정보
									// 4 	: 자신이 교환취소
									// 5	: 타인이 교환취소
									// 6	: 자신의 인벤토리 풀
									// 7	: 타인의 인벤토리 풀
									// ...
									// 255 : UNKNOWN ERROR

	// 교환 동의일 경우

	// 변경아이템 목록
	DWORD		dwDN				// 소지금 변동

	BYTE		byItemNumber;		// 총 교환한 아이템 수 또는 돈
		BYTE		bySlotId;			// 인벤토리창의 인덱스
		short		sLevel;				// 아이템 장착 레벨				//@@@@@
		short		sItemID;			// 아이템 인덱스
		short		sDuration;			// 내구도
		short		byBullNum;			// 장탄수
		short		sCount				// 얼만큼 갯수 (돈  또는 아이템)
		BYTE	    tMagic[6];			// 매직속성
		BYTE		tIQ;				// Item Quality

		...								// 갯수만큼 반복한다.
*/

const BYTE	ITEM_MOVE_REQ		 = 53;
/*
	( C -> S )						// 아이템 이동( 예)장비장착, 퀵아이템, 인벤토리내에서 이동등.. )
	BYTE			tType;			// 0 : 일반 아이템(인벤토리내)
									// 1 : Quick Item 등록
									// 2 : Quick Item 이동, 등록 취소

	// 0 : 일반 아이템경우
	BYTE			bySourceSlot;	// 원래 아이템이 있던 슬롯 위치
	BYTE			byDestSlot;		// 옮기려는 슬롯 위치

	// 1, 2 번 타입은 클라이언트 자체 처리한다.
	>>-----------------------------[ 없어진 코드 : jjs07 ] ----------------------------->>
	// 1 : Quick Item 등록
	BYTE			bySourceSlot;	// 인벤토리 슬롯 위치
	BYTE			byDestSlot;		// QuickSlotNum 슬롯 위치 (0,1,2,3,4)

	// 2 : Quick Item 이동, 등록 취소
	BYTE			bySourceSlot;	// 해당 QuickSlotNum 슬롯 위치
	BYTE			byDestSlot;		// 옮기려는 위치
									// 예)  등록취소 = 255
									//		그외 0~4까지 이동 번호
	<<---------------------------------------------------------------------------------<<
*/

const BYTE	ITEM_MOVE_RESULT	 = 54;
/*
	( C <- S )

	BYTE			Result;			// 01 : Success
									// else	: Fail

	// 아이템 성공시 내려감
	BYTE			tType;			// 0 : 일반 아이템
									// 1 : Quick Item 등록				// 1, 2 번은 이제 사라진 코드 : jjs07
									// 2 : Quick Item 이동, 등록 취소
									// 3 : 구매한 Item 목록
									// 4 : 판매한 Item 목록
									// 5 : 수리한 Item 목록

			// 0 : 일반 아이템 성공시
			BYTE			ChangedSlotNum;	// 변화된 슬롯의 갯수

			typedef struct _tagMoveItem
			{
				byte	bySlot;
				short	sLevel;				// 아이템 장착 레벨//@@@@@@@@@@@
				short	sSid;
				short	sDuration;
				short	sBullNum;
				short	sCount;
				BYTE	tMagic[6];
				BYTE	tIQ;
			} MoveItemInfo[ChangedSlotNum];

			// 1 : Quick Item 등록시
			BYTE			tQuickSlotNum;	// 등록한 슬롯 번호
			short			sSid;

			// 2 : Quick Item 이동, 등록 취소
			BYTE			tChangedSlotNum;// 변화된 슬롯의 갯수

			typedef struct _tagQuickItem
			{
				byte	tSlot;			    // 해당 Quick Slot 번호
				short	sSid;
			} QuickItemInfo[tChangedSlotNum];

		  // 3, 4, 5목록 처리
			BYTE			ChangedSlotNum;	// 변화된 슬롯의 갯수

			typedef struct _tagMoveItem
			{
				byte	bySlot;
				short	sLevel;				// 아이템 장착 레벨//@@@@@@@@@
				short	sSid;
				short	sDuration;
				short	sBullNum;
				short	sCount;
				BYTE	tMagic[6];
				BYTE	tIQ;
			} MoveItemInfo[ChangedSlotNum];
*/

const BYTE  ITEM_USE_REQ		= 55;
/*
	(C -> S)	// 퀵아이템 사용 요청
	BYTE		tType;			// 01 : 일회성 소모 아이템
								// 02 : 복수 사용 아이템

	// 01 : 일회성 소모 아이템
	BYTE		tSlot			// 사용하고자 하는 아이템

	// 02 : 복수 사용 아이템
	BYTE		tSlot;			// 사용하고자 하는 아이템
	BYTE		tSid;			// 여러개의 번호중 어떤 번호를 사용할거냐?

*/
const BYTE  ITEM_USE_RESULT		= 56;
/*
	(C <- S)	// 퀵아이템 사용 통보

	BYTE		tType;			// 00 : 실패
								// 01 : 성공

	// 성공일경우
	BYTE		tMode;			// 01  : SP, PP, HP 한번에 일정량을 채워준다.
								// 08  : 혼란치료
								// 16  : 마비치료
								// 32  : 중독치료
								// 64  : 시력치료
								// 127 : 모든 상태이상치료
								// 100 : 검, 총용 리필
								// 101 : 포탈사용
								// 102 : 복권 아이템
								// 103 : 카피칩 아이템
	// 01 일때
	short		sSP_Refill;		// 회복된 수치
	short		sHP_Refill;
	short		sPP_Refill;

		typedef struct _tagItem	// 사용한 아이템 정보(서버에서 계산, 남아있는 총수)
		{
			byte	bySlot;
			short	sLevel;				// 아이템 장착 레벨//@@@@@@@@
			short	sSid;
			short	sDuration;
			short	sBullNum;
			short	sCount;
			BYTE	tMagic[6];
			BYTE	tIQ;
		} ItemInfo;

	// 08 16 32 64 127 100 101 103: 일때
	typedef struct _tagItem
	{
		byte	bySlot;
		short	sLevel;				// 아이템 장착 레벨//@@@@@@@@
		short	sSid;
		short	sDuration;
		short	sBullNum;
		short	sCount;
		BYTE	tMagic[6];
		BYTE	tIQ;
	} ItemInfo;

	// 102 : 복권아이템일때
	byte		bySlot;			// 인벤 슬롯
	DWORD		dwDN;			// 당첨된금액

*/

const BYTE	MONEY_CHANGED		= 57;
/*
	(C <- S)	// 소지금 변경 통보

	BYTE		tType;			// 0 : 거래 중일때
								// 1 : 그외 소지금 변동일때
	// 0 : 거래 중일때
	DWORD		dwTradeDN;		// 거래 창에서 금액
	DWORD		dwDN;			// 소지금

	// 1 : 그외 소지금 변동일때
	DWORD	dwDN;				// 소지금
*/

const BYTE	FIELD_ITEM_INFO		= 58;

/*
	(C <- S)					// 맵상에서 쌓여있는 아이템 정보를 보낸다.

	short		sLoopCount;		// 전체 아이템 수

		BYTE		Mode;			// 01(ITEM_INFO_MODIFY)	: FIELD ITEM 정보
									// 02(ITEM_INFO_DELETE)	: FIELD ITEM DEL된 정보를 보낸다
									// 03(ITEM_INFO_PICKUP)	: FIELD ITEM 에 있는 아이템를 줍는다.

		short		nPosX;			// X Position
		short		nPosY;			// Y Position

		short		sSid;			//(-1)일경우 Item은 없다.
		DWORD		dwCount;
		BYTE		tIQ;			// 매직 부터 값이 1이상 그외는 0임

		// Mode == 03(ITEM_INFO_PICKUP) 일 경우 추가.
		int			uid;			// 줍는 유저

*/

/*
const BYTE	ITEM_WEIGHT_CHANGE	= 59;
/*
	(C <- S)					// 아이템 무게변동를 알린다.

	short		sMaxWeight;		// 현재 들수있는 최대무게
	short		sCurWeight;		// 현재 무게
*/

const BYTE	SERVER_TIME_REQ		= 59;
/*
	(C -> S)	// 서버의 게임시간, 로컬시간을 요청한다.

	// 전달인자 없음
*/

const BYTE	SERVER_TIME_RESULT	= 59;
/*
	(C <- S)	// 서버의 게임시간, 로컬시간을 보내준다.

	short		sYear;
	short		sMonth;
	short		sDay;
	short		sHour;
	short		sMinute;
	short		sSecond;
*/

//#################################################################
//	Game PK Button	(62)
//#################################################################

const BYTE PK_BUTTON_REQ			= 62;

//#################################################################
//	Game Main UI	(63 ~ 88)
//#################################################################
const BYTE	QUESTWINDOW_OPEN_REQ	= 63;
/*
	(C -> S)	// Quest Window Open Request
*/

const BYTE	QUESTWINDOW_OPEN_RESULT	= 63;	// Packet 재활용
/*
	(C <- S)	// Quest Window Open Result

	short		sCount;				// 보유한 퀘스트의 갯수
	
	// sCount > 0 인 경우
	short		sQuestNum[sCount];	// 퀘스트 번호 (sCount 만큼 반복해서 보낸다)
*/

const BYTE	TRADE_MODE_REQ		= 64;
/*
	(C -> S)	// Trade Mode On/Off Req
	BYTE		Mode;			// 00	: Off
								// 01	: On
*/

const BYTE	TRADE_MODE_RESULT	= 65;
/*
	(C <- S)	// Trade Mode On/Off Result
	BYTE		Mode;			// 00	: Off
								// 01	: On
*/

const BYTE	OPEN_EQUIP_REQ		= 68;
/*
	(C -> S)	// Equip/Skill Window Open
	// 전달값 없음
*/

const BYTE	OPEN_EQUIP_RESULT	= 69;
/*
	(C <- S)	// Equip/Skill Window Open Result

	short		WeaponInfo[8];
	BYTE		EvadeInfo[4];

	BYTE		Rate[5];			// 스킬 적용 성공율
*/

const BYTE	CHANGE_WEAPON_REQ	= 70;
/*
	(C -> S)	// 무기 변경 (오른손 , 왼손 무기 전환)
*/

const BYTE	CHANGE_WEAPON_RESULT= 71;
/*
	(C <- S)	// 무기 변경 결과

	BYTE		result;			// 00 : 무기 변경 불가능
								// 01 : 성공 ( 성공시에는 UserInfo 발생)

	// result 가 성공일때
	BYTE		tEnable;		// 해당 무기 스킬을 쓸수 있는지 판단
								// 00 : 쓸 수 없음
								// 01 : 쓸 수 있음

	BYTE		tSkillClass		// 해당 스킬 클래스표시
	typedef struct _tagSkill	// Skill
	{
		short	sSid;		// Skill id
		BYTE	tLevel;		// Level
	}UserSkill[SKILL_NUM];	// SKILL_NUM = 5
*/

const BYTE	SKILL_ONOFF_REQ		= 72;
/*
	(C -> S)	// 특정 스킬을 ON/OFF 한다.

	short		sSid;			// Skill ID
*/

const BYTE	SKILL_ONOFF_RESULT	= 73;
/*
	(C <- S)	// 스킬 ON/OFF RESULT

	BYTE		result;			// 00 : Fail
								// 01 : Success
	// 성공일 경우
	short	sSid;		// Skill id
	BYTE	tLevel;		// Level
	BYTE	tOnOff;		// On/Off 정보
*/

const BYTE	PSI_CHANGE_REQ		= 74;
/*
	(C -> S)	// 사이오닉 전환 요구

	short		sSid;			// Psionic ID
*/

const BYTE	PSI_CHANGE_RESULT	= 75;
/*
	(C <- S)	// Psionic Change RESULT

	BYTE		result;			// 00 : Fail
								// 01 : Success
	// 성공일 경우
	short	sSid;				// Psionic id
	BYTE	tUsedPP;			// Consumed Psionic PP Value
*/

const BYTE	LEVEL_UP			= 76;//@@@@@@@@@@@@@@@바꿈
/*
	(C <- S)					// level up

	BYTE	tType;				// 00 : error
								// 01 : 일반 경험치
								// 02 : 레벨업 발생
	// 01 : 일반 경험치
		DWORD	dwExp;			// 누적된 경험치

	// 02 : 레벨업 발생
		DWORD	dwExp;			// 시작 경험치
		DWORD	dwMaxExp;		// 다음 레벨까지 최대 경험치
		short	sLevel;			// 현재 레벨
		short	sSkillPoint;	// 누적 스킬포인트
		short	sPA;			// 누적 PA



*/
const BYTE	LEVEL_DOWN			= 77;
/*
	(C <- S)					// level down
								// 결과값으로 USER_STATUS_SKILL_UP_RESULT + LEVEL_UP 사용
*/								// 나중에 중복되는 내용을 정리

const BYTE	USER_STATUS_SKILL_UP_REQ= 78;//@@@@@@@@@@@@@@@바꿈
/*
	(C -> S)					// PA, Skill를 올린다.

	BYTE	tType;				// 01 : PA
								// 02 : Skill


	// 01 : PA 능력치 증가
		BYTE	tPaMaNum;	// 0~4까지중 +번호

	// 02 : Skill Level 증가
		BYTE	tSkillNum;

*/

const BYTE	USER_STATUS_SKILL_UP_RESULT= 79;//@@@@@@@@@@@@@@@바꿈
/*
	(C <- S)					// PA, Skill의 결과값를 리턴
	short		sPA;			// 물리 포인트

	short		sSTR;			// 힘
	short		sCON;			// 건강
	short		sDEX;			// 민첩
	short		sVOL;			// 의지
	short		sWIS;			// 지혜

	short		sHP;			// 현재
	short		sPP;
	short		sSP;
	short		sMaxHP;			// 최대치
	short		sMaxPP;			//
	short		sMaxSP;			//

	short		sMaxDamage;		// 최대 공격력
	short		sMaxDefense;	// 최대 방어력

	short		sSkillPoint;	// 스킬 포인트

	BYTE		tSkillClass		// 해당 스킬 클래스표시
	typedef struct _tagSkill	// Skill
	{
		short	sSid;		// Skill id
		BYTE	tLevel;		// Level
	}UserSkill[SKILL_NUM];	// SKILL_NUM = 5
*/

const BYTE	BUDDY_MODE_REQ			= 80;
/*
	(C -> S)	// BUDDY Mode On/Off Req
	BYTE		Mode;			// 00	: Off
								// 01	: On
*/

const BYTE	BUDDY_MODE_RESULT		= 81;
/*
	(C <- S)	// BUDDY Mode On/Off Result
	BYTE		Mode;			// 00	: Off
								// 01	: On
*/

const BYTE	BUDDY_USER_CHANGE		= 82;
/*
	(C <- S)	// 버디 구성원 변화가 발생하면   (가입과 탈퇴는 chat로...)

	BYTE		tType;				// 01 : 구성원 추가
									// 02 : 구성원 탈퇴
									// 03 : 구성원 데이터 갱신

	// 01 : 구성원 추가
	int			uid;				// 상대방 uid
	Varchar		UserName;			// 상대방 이름

  	DWORD		dwSkin;				// 피부색(COLORREF)
	DWORD		dwHair;				// 머리색(COLORREF)
	BYTE		byGender;			// 남, 여

	char		szFace[10];			// 얼굴모양
									// 1 : 머리
									// 2 : 얼굴
									// 3 : 눈
									// 4 : 코
									// 5 : 입
									// 6 : 악세사리 1
									// 7 : 악세사리 2
									// 8~10 : 예비

	short		sMaxHP;				// 최대 HP
	short		sHP;				// 현재 HP

	// 02 : 구성원 탈퇴
	int			uid;				// 상대방 uid

	// 03 : 구성원 데이터 갱신
	int			uid;				// 상대방 uid
	short		sMaxHP;				// 최대 HP
	short		sHP;				// 현재 HP
*/


//#################################################################
//	Move			(88 ~ 106)
//#################################################################
const BYTE	CHANGE_DIR_REQ		= 88;
/*
	(C -> S)	// 방향전환 요구

	BYTE		tDir;			//	3 4 5
								//	2 8 6
								//	1 0 7
*/

const BYTE CHANGE_DIR_RESULT	= 89;
/*
	(S -> C)	// 방향전환 결과

	int			uid;			// User id
	BYTE		tDir;			// 방향
*/

const BYTE	MOVE_FIRST_REQ		= 90;
/*
	(C -> S)	// Move First Request

	short		will_x;				// 움직이려고 하는 첫 좌표의 X 값
	short		will_y;				// 움직이려고 하는 첫 좌표의 Y 값

	short		end_x;				// 움직이려는 마지막 좌표의 X 값
	short		end_y;				// 움직이려는 마지막 좌표의 Y 값
*/

const BYTE	MOVE_FIRST_RESULT	= 91;
/*
	(C <- S)	// Move First Result

	BYTE		result;				// 01	: Move First Success
									// else	: Move First Fail

	// 실패시
	int			uid;				// User Index
	short		cur_x;				// 서버의 현재 x 좌표
	short		cur_y;				// 서버의 현재 y 좌표

	// 성공시
	int			uid;				// User Index
	short		will_x;				// 움직이려고 하는 첫 좌표의 X 값
	short		will_y;				// 움직이려고 하는 첫 좌표의 Y 값

	short		end_x;				// 움직이려는 마지막 좌표의 X 값
	short		end_y;				// 움직이려는 마지막 좌표의 Y 값
*/

const BYTE	MOVE_REQ			= 92;
/*
	(C -> S)	// Move Req
	short		will_x;				// 움직이려고 하는 좌표의 X 값
	short		will_y;				// 움직이려고 하는 좌표의 Y 값
*/

const BYTE	MOVE_RESULT			= 93;
/*
	(C <- S)	// Move Result

	BYTE		result;				// 01	: Move Success
									// else	: Move Fail

	// 실패시
	int			uid;				// User Index
	short		cur_x;				// 서버의 현재 x 좌표
	short		cur_y;				// 서버의 현재 y 좌표

	// 성공시
	int			uid;				// User Index
	short		will_x;				// 움직이려고 하는 좌표의 X 값
	short		will_y;				// 움직이려고 하는 좌표의 Y 값
*/


const BYTE	MOVE_END_REQ		= 94;
/*
	(C -> S)	// Move Req
	short		end_x;				// 움직이려고 하는 마지막 좌표의 X 값
	short		end_y;				// 움직이려고 하는 마지막 좌표의 Y 값
*/

const BYTE	MOVE_END_RESULT		= 95;
/*
	(C <- S)	// Move Result

	BYTE		result;				// 01	: Move Success
									// else	: Move Fail
	// 실패시
	int			uid;				// User Index
	short		cur_x;				// 서버의 현재 x 좌표
	short		cur_y;				// 서버의 현재 y 좌표

	// 성공시
	int			uid;				// User Index
	short		end_x;				// 움직이려고 하는 마지막 좌표의 X 값
	short		end_y;				// 움직이려고 하는 마지막 좌표의 Y 값
*/

const BYTE	RUN_FIRST_REQ		= 96;
/*
	(C -> S)	// Run First Request

	short		w_x1;				// 뛰려는 첫 좌표의 X 값
	short		w_y1;				// 뛰려는 첫 좌표의 Y 값
	short		w_x2;				// 뛰려는 2번째 좌표의 X 값
	short		w_y2;				// 뛰려는 2번째 좌표의 X 값

	short		end_x;				// 뛰려는 마지막 좌표의 X 값
	short		end_y;				// 뛰려는 마지막 좌표의 Y 값
*/

const BYTE	RUN_FIRST_RESULT	= 97;
/*
	(C <- S)	// Run First Result

	BYTE		result;				// 01	: Run First Success
									// else	: Run First Fail
	// 실패시
	int			uid;				// User Index
	short		cur_x;				// 서버의 현재 x 좌표
	short		cur_y;				// 서버의 현재 y 좌표

	// 성공시
	// w_x2, w_y2 가 -1 이면 두번째 좌표로는 이동 불가.
	int			uid;				// User Index
	short		w_x1;				// 뛰려는 첫 좌표의 X 값
	short		w_y1;				// 뛰려는 첫 좌표의 Y 값
	short		w_x2;				// 뛰려는 2번째 좌표의 X 값
	short		w_y2;				// 뛰려는 2번째 좌표의 X 값

	short		end_x;				// 뛰려는 마지막 좌표의 X 값
	short		end_y;				// 뛰려는 마지막 좌표의 Y 값
*/

const BYTE	RUN_REQ				= 98;
/*
	(C -> S)	// Run Request

	short		w_x1;				// 뛰려는 첫 좌표의 X 값
	short		w_y1;				// 뛰려는 첫 좌표의 Y 값
	short		w_x2;				// 뛰려는 2번째 좌표의 X 값
	short		w_y2;				// 뛰려는 2번째 좌표의 X 값

*/

const BYTE	RUN_RESULT			= 99;
/*
	(C <- S)	// Run Result

	BYTE		result;				// 01	: Run Success
									// else	: Run Fail
	// 실패시
	int			uid;				// User Index
	short		cur_x;				// 서버의 현재 x 좌표
	short		cur_y;				// 서버의 현재 y 좌표

	// 성공시
	// w_x2, w_y2 가 -1 이면 두번째 좌표로는 이동 불가.
	int			uid;				// User Index
	short		w_x1;				// 뛰려는 첫 좌표의 X 값
	short		w_y1;				// 뛰려는 첫 좌표의 Y 값
	short		w_x2;				// 뛰려는 2번째 좌표의 X 값
	short		w_y2;				// 뛰려는 2번째 좌표의 X 값
*/

const BYTE	RUN_END_REQ			= 100;
/*
	(C -> S)	// Run End Request

	short		w_x1;				// 뛰려는 첫 좌표의 X 값
	short		w_y1;				// 뛰려는 첫 좌표의 Y 값
	short		w_x2;				// 뛰려는 2번째 좌표의 X 값
	short		w_y2;				// 뛰려는 2번째 좌표의 X 값

*/

const BYTE	RUN_END_RESULT		= 101;
/*
	(C <- S)	// Run End Result

	BYTE		result;				// 01	: Run End Success
									// else	: Run End Fail

	// 실패시
	int			uid;				// User Index
	short		cur_x;				// 서버의 현재 x 좌표
	short		cur_y;				// 서버의 현재 y 좌표

	// 성공시
	// w_x2, w_y2 가 -1 이면 두번째 좌표로는 이동 불가.
	int			uid;				// User Index
	short		w_x1;				// 뛰려는 첫 좌표의 X 값
	short		w_y1;				// 뛰려는 첫 좌표의 Y 값
	short		w_x2;				// 뛰려는 2번째 좌표의 X 값
	short		w_y2;				// 뛰려는 2번째 좌표의 X 값
*/

const BYTE	SET_STAEMINA		= 102;
/*
	(C <- S)	// 스테미너 정보를 셋팅한다.

	short		sSP;				// 스테미너 값
*/


//#################################################################
//	Battle		(106 ~ 130)
//#################################################################
const BYTE SET_XP					= 106;
/*
	(C <- S)	// XP 정보를 셋팅한다.

	DWORD		dwXP;				// XP 값
*/

const BYTE SET_HP					= 107;
/*
	(C <- S)	// HP 정보를 셋팅한다.

	short		sHP;				// HP 값
*/

const BYTE SET_PP					= 108;
/*
	(C <- S)	// PP 정보를 셋팅한다.

	short		sPP;				// PP 값
*/

const BYTE PSI_ATTACK_REQ			= 109;
/*
	(C -> S)	// Psionic Attack Req

	int			TargetID;			// 공격대상 ID
	BYTE		PsionicID;			// 사이오닉 sid

	// 사이오닉이 텔레포트일 경우 전송 (텔레포트 아이디는 PSI_TELEPORT 로 정의되어 있음)
	int			PosX;				// 텔레포트할 위치좌표 X
	int			PosY;				// 텔레포트할 위치좌표 Y
*/

const BYTE PSI_ATTACK_RESULT		= 110;
/*
	(C <- S)	// Psionic Attack Result

	BYTE		bSuccess;			// 00 : Attack Fail
									// 01 : Attack Success

	// Attack Miss, Attack Success 의 경우 전송, Fail 일 경우 bSuccess 정보만 전송한다.
	BYTE		PsionicID;			// 사이오닉 sid

	int			SourceID;			// 공격자 ID
	int			DestID;				// 공격 받은자 ID
*/

const BYTE ATTACK_REQ				= 111;
/*
	(C -> S)	// Attack Request

	short		TargetID;			// Target ID
*/

const BYTE ATTACK_RESULT			= 112;
/*
	(C <- S)	// Attack Result

	BYTE		bSuccess;			// 00	: Attack Fail
									// 01	: Attack Success
									// 02	: Attack Miss

	// Attack Fail 일 경우 아래의 에러코드만 보낸다.
	BYTE		tError;				// 00	: Too Short Attack Delay
									// 01	: Too Long Distance
									// 02	: 총기고장
									// 03	: 잔탄부족
									// 04	: 레티늄팩 Empty
									// 05	: 스테미나 부족


	// Attack Success, Attack Miss 의 경우에만 아래패킷 전송
	int			SourceID;			// 공격자 ID
	int			DestID;				// 공격 받은자 ID

	// Attack Success 의 경우에만 전송 (MISS 인 경우는 아래내용 전송안함)

	// 공격측에 뜨는 스킬 액션
	BYTE		tActionNum1;		// 스킬액션 1 숫자
	BYTE		tSkillAction1[tActionNum1];		// Skill Action (해당 스킬 액션표 참조, DEFINE 되어있음)
												// 0 : None
												// 1 : Damage Critical
												// 2 : Vital Critical
												// 3 : Delay Critical
												// 4 : Concentrate (PSI)
												// 5 : PSY Acclimate
												// 6 : Fast Cast
												// 7 : Weapon Acclimate
												// 8 : Fast Attack
												// 9 : Out Range
												// 10: Strafe
												// 11: Broken
												// 12: Fixed
												// 13: Overheat
												// 14: 화염데미지
												// 15: 냉기데미지
												// 16: 전기대미지
												// 17: 마비
												// 18: 중독
												// 19: Guard

	// 방어측에 뜨는 스킬 액션
	BYTE		tActionNum2;		// 스킬액션 2 숫자
	BYTE		tSkillAction2[tActionNum2];		// Skill Action (해당 스킬 액션표 참조, DEFINE 되어있음)

	short		HP;					// 공격받은자의 HP
	short		MaxHP;				// 공격받은자의 최대 HP
*/
//yskang 0.3 2002-11-6 변경되는 패킷...
/*
	(C <- S)	// Attack Result

	BYTE		bSuccess;			// 00	: Attack Fail
							// 01	: 보통 공격 성공
							// 02	: 보통 공격 실패(상대방 피한거)
							// 03 	: 크리티컬 공격 성공
							// 04   : 크리티컬 공격 실패(상대방 피한거)



	// Attack Fail 일 경우 아래의 에러코드만 보낸다.
	BYTE		tError;				// 00	: Too Short Attack Delay
									// 01	: Too Long Distance
									// 02	: 총기고장
									// 03	: 잔탄부족
									// 04	: 레티늄팩 Empty
									// 05	: 스테미나 부족


	// Attack Success, Attack Miss 의 경우에만 아래패킷 전송
	int			SourceID;			// 공격자 ID
	int			DestID;				// 공격 받은자 ID

	short		HP;					// 공격받은자의 HP
	short		MaxHP;				// 공격받은자의 최대 HP
*/


const BYTE	DEAD					= 113;
/*
	(C <-S)		// you are dead!!!

	short		uid;				// USER, NPC ID
	short		posx;				// X Position
	short		posy;				// Y Position
*/

const BYTE	LIVE_REQ				= 114;
/*
	(C -> S)	// Revival Request

	(C <- S)	// 결과값으로 USER_INFO로 알려준다.
*/


const BYTE	PSI_TOWN_POTAL			= 115;
/*
	(C <- S)	// PSI_ATTACK_REQ에대한 결과값 반환(최적화 필요)

	BYTE		tType;				// 00 : Fail
									// 01 : Success

	// 성공일때만...
	BYTE	tSuccess				// 00 : 같은 존이다
									// 01 : 다른 존이다.

	int		uid;					// 사용자 uid

	short	nPosX;					// X Position
	short	nPosY;					// Y Position
	short	sZone;					// Load Zone Number
*/

const BYTE	SET_SPEED_MONSTER		= 116;
/*
	(C <- S)	// 이동 속도 변화를 알려 준다.

	int		uid;					// 몹 uid
	short	sDelay;					// 변화된 속도를 표시
*/

const BYTE	SET_USER_STATE			= 117;
/*
	(C <- S)	// 유저 상태 변화정보를 보낸다.

	int		uid;			// uid
	DWORD	dwAbnormal		// 상태이상정보(Damaged)

							// const DWORD ABNORMAL_NONE			=	0;
							// const DWORD ABNORMAL_POISON			=	1;
							// const DWORD ABNORMAL_CONFUSION		=	1 << 2;
							// const DWORD ABNORMAL_PARALYSIS		=	1 << 3;
							// const DWORD ABNORMAL_BLIND			=	1 << 4;
							// const DWORD ABNORMAL_LIGHT			=	1 << 5;
							// const DWORD ABNORMAL_FIRE			=	1 << 6;
							// const DWORD ABNORMAL_COLD			=	1 << 7;
							// const DWORD ABNORMAL_HASTE			=	1 << 8;
							// const DWORD ABNORMAL_SHIELD			=	1 << 9;
							// const DWORD ABNORMAL_HIDE			=	1 << 10;
							// const DWORD ABNORMAL_DEX_UP			=	1 << 11;
							// const DWORD ABNORMAL_MAX_HP_UP		=	1 << 12;
							// const DWORD ABNORMAL_ADAMANTINE		=	1 << 13;
							// const DWORD ABNORMAL_MIGHTYWEAPON	=	1 << 14;
							// const DWORD ABNORMAL_BERSERKER		=	1 << 15;
							// const DWORD ABNORMAL_HIEXP			=	1 << 16;
							// const DWORD ABNORMAL_MAGICFIND		=	1 << 17;
							// const DWORD ABNORMAL_NOCHAT			=	1 << 18;
							
							// const DWORD ABNORMAL_FASTRUN			=	1 << 19;
							// const DWORD ABNORMAL_MINDSHOCK		=	1 << 20;
							// const DWORD ABNORMAL_MINDGUARD		=	1 << 21;
							// const DWORD ABNORMAL_PSISHIELD		=	1 << 22;
							// const DWORD ABNORMAL_PIERCING_SHIELD	=	1 << 23;
							  
							// const DWORD OPERATION_MODE			=	1 << 31;	// 운영자 투명 옵션
*/

const BYTE	SET_USER_PK_STATE			= 118;
/*
	(C <- S)	// 현재 시민등급 또는 PK상태를 보낸다.

	int		uid;					// uid

	BYTE	tType;					// 01 : 유저 시민등급
									// 02 : 유저가 일시적인 카오상태에 있다.

	// 01 : 유저 시민등급
	short	sCityRank;				// -5 ~ 5까지 시민등급을 보냄

	// 02 : 유저가 일시적인 카오상태에 있다.
	BYTE	tPKStatus;				// 현재 일시적인 카오상태 : 1
									// 현재 카오상태에서 벗어남 : 0
*/

const BYTE	USE_POTION					= 119;
/*
	(S -> C)	// 물약 사용정보를 보낸다.

	int		uid;
	BYTE	tType;					// 01 : 체력회복제
									// 02 : 정신안정제
									// 03 : 스테미너회복제
									// 04 : 범용회복제
									// 05 : 폭죽
									// 06 : 경험치 2배
									// 07 : 매직찬스 5배
									// 08 : PK 수치 - 1
									// 09 : 극약

									const BYTE HP_POTION			= 1;
									const BYTE PP_POTION			= 2;
									const BYTE SP_POTION			= 3;
									const BYTE ALL_POTION			= 4;
									const BYTE SALUTE				= 5;
									const BYTE EXP_POTION			= 6;
									const BYTE MAGIC_POTION			= 7;
									const BYTE KILLREMOVE_POTION	= 8;
									const BYTE DEAD_POTION			= 9;

*/

//#################################################################
//	Event		(131 ~ 170)
//#################################################################
const BYTE MAX_HP_EXIT				= 120;
/*
	short		sHP;
	short		sMaxHP;
*/
const BYTE	CLIENT_EVENT			= 131;
/*
	(C -> S)	// 서버에 Event 수행을 요청한다.

	BYTE		tType;				// 01 : USER, NPC ID
									// 02 : HyperText

	// 01 : USER, NPC ID
		int			uid;			// USER, NPC ID

	// 02 : HyperText 해당 존에서 발생하는 이벤트 번호를 보낸다.

		short		sZone;			// 해당 존 번호
		short		sEventNum;		// 이벤트 번호
*/

const BYTE	STORE_OPEN				= 132;
/*
	(C <- S)	// 특정 상점을 연다. (BUY 인터페이스)

	short		sStoreID;			// 상점아이디
	short		sRate;				// 시세(나중에 지역에 따라 세금이 틀려질 때등...)
	short		sCount;				// 파는 아이템의 총 갯수

	typedef struct _tagSellItem		// 파는 아이템의 정보
	{
		short	sSid;	// Item serial id
		DWORD	dwCost;	// Item cost
	}SellItem[sCount];
*/

const BYTE	BUY_ITEM				= 133;
/*
	(C -> S)	// 아이템을 구입한다.

	short		sStoreID;			// 상점아이디
	short		sCount;				// 구매하는 아이템의 총갯수

	typedef struct _tagBuyItem		// 구매 아이템의 정보
	{
		short	sSid;	// Item serial id
		short	sNum;	// Item count
	}BuyItem[sCount];
*/
/*
	(S -> C)	// 결과값으로 ITEM_MOVE_RESULT을 이용한다. tType = 3;(일반아이템) +
*/

const BYTE	CLIENT_EVENT_SAY		= 134;
/*
	(C <- S)	// HyperText의 NPC_SAY 실행통보.

	BYTE		result;				// 01	: 성공
									// else	: 실패

	short		iSayNum;			// Npc Say Number

	BYTE		tCount;				// "%s"가 들어간 횟수

	typedef struct _tagSay			//
	{
		Varchar	strMsg;				// Message
	}strMsg[tCount];

	// 성공일 경우

*/

/*
const BYTE	SELL_ITEM_OPEN_REQ		= 134;

	(C -> S)	// 아이템을 상점에 팔기위해 팔수있는 목록과 가격을 요청한다.

	short		sStoreID;
*/

const BYTE	SELL_ITEM_OPEN_RESULT	= 135;
/*
	(C <- S)	// 해당 상점에서 사는 목록과 가격을 내려준다.

	short		sStoreID;			// 상점 아이디
	short		sCount;				// 팔수 있는 아이템의 총갯수

	// sCount > 0 인 경우에만 전송
	typedef struct _tagSellInfo
	{
		short	sSlot;		// 해당 상점에 팔수 있는 유저인벤토리의 슬롯 번호
		short	sDuration; // 현재 내구도
		DWORD	dwDN;		// 가격
	}SellInfo[sCount];
*/

const BYTE	SELL_ITEM				= 136;
/*
	(C -> S)	// 아이템을 상점에 판다.

	short		sStoreID;			// 상점아이디
	short		sCount;				// 팔려는 아이템의 총갯수

	typedef struct _tagSellItem		// 구매 아이템의 정보
	{
		short	sSlot;	// 해당 상점에 팔수 있는 유저인벤토리의 슬롯 번호
		short	sNum;	// Item count
	}SellItem[sCount];
*/
/*
	(S -> C)	// 결과값으로 ITEM_MOVE_RESULT을 이용한다. tType = 4;(일반아이템) +
*/


//const BYTE	EBODY_IDENTIFY_OPEN	= 137;
/*
	(S -> C)	// 확인할 수 있는 EBody 목록은 보낸다.

	short		sStoreID;
	short		sCount;				// 확인할 수 있는 EBody의 총갯수

	BYTE		tSlot[sCount];		// 확인할 슬롯 정보

	// EBody 확인 결과는 ITEM_MOVE_RESULT 로 보낸다.
*/

const BYTE	REPAIR_ITEM_OPEN_RESULT	= 138;
/*
	(C <- S)	// 해당 상점에서 사는 목록과 가격을 내려준다.

	short		sStoreID;			// 상점 아이디
	short		tCount;				// 수리 할수 있는 아이템의 총갯수

	// tCount > 0 인 경우에만 전송
	typedef struct _tagRepairInfo
	{
		short	sSlot;				// 해당 상점에서 수리할수 있는 유저 인벤토리의 슬롯 번호
		short	sDuration;			// 현재 내구도
		DWORD	dwDN;				// 가격
	}RepairInfo[tCount];
*/

const BYTE	REPAIR_ITEM				= 139;		
/*
	(C -> S)	// 수리 아이템목록을 보낸다.

	short		sStoreID;			// 상점아이디

	short		tCount;

	typedef struct _tagRepair
	{
		short	sSlot;				// 해당 상점에서 수리할수 있는 유저 인벤토리의 슬롯 번호
	}Repair[tCount];

*/
/*
	(S -> C)	// 결과값으로 ITEM_MOVE_RESULT을 이용한다. tType = 5;(일반아이템)
*/
const BYTE	BUY_PSY_OPEN_RESULT		= 140;
/*
	(C <- S)	// 해당 상점에서 습득할수있는 목록을 내려준다.

	short		sStoreID;			// 상점 아이디
	short		sPsiCount;			// 익힐수있는 총 Psi 수

	// sPsiCount > 0 인 경우에만 전송
	typedef struct _tagPsiInfo
	{
		short	sSid;				// Psi serial id
	}PsiInfo[sPsiCount];

*/

const BYTE	BUY_PSY_REQ				= 141;
/*
	(C -> S)	// 사이오닉 구입을 보낸다

	short		sStoreID;			// 상점 아이디
	short		sPsiCount;			// 총 Psi 수

	// sPsiCount > 0 인 경우에만 전송
	typedef struct _tagPsiInfo
	{
		short	sSid;				// Psi serial id
	}PsiInfo[sPsiCount];
*/

const BYTE	BUY_PSY_RESULT			= 142;
/*
	(C <- S)	// 결과를 인증한다.

	BYTE		tType;				// 01 : 성공
									// else : 실패


	// 00 : 실패이면
									//	error 01 : 상점 사이오닉이 자기 클래스와 맞는게 없다.
									//	error 02 : 구입에 필요한 레벨이 높다.
									//	error 03 : XP가 모자란다.
									//	error 04 : DN이 모자란다.
									//	error 05 : 익힐수 있는 한도를 넘었다.
									//	error 06 : 이미 습득한 사이오닉를 선택했다.

	// 01 : 성공이면
		short		sPsiCount;			// 총 Psi 수

		// sPsiCount > 0 인 경우에만 전송
		typedef struct _tagPsiInfo
		{
			short	sSid;				// Psi serial id
		}PsiInfo[sPsiCount];
*/

const BYTE	BANK_OPEN				= 143;
/*
	(C <- S)							// 은행에 보관된 아이템과 돈를 보낸다.

		DWORD		BankDN;				// 은행에 보관된 돈

		BYTE		TotalSlotNum;		// 은행에 보관된 아이템 슬롯의 갯수

		typedef struct _tagItem
		{
			byte	bySlot;
			short	sLevel;				// 아이템 장착 레벨@@@
			short	sSid;
			short	sDuration;
			short	sBullNum;
			short	sCount;
			BYTE	tMagic[6];
			BYTE	tIQ;
		} ItemInfo[TotalSlotNum];
*/

const BYTE	BANK_ITEM_MOVE_REQ		= 144;
/*
	( C -> S )						// 아이템 이동
	BYTE			tType;			// 1 : 은행에 아이템 보관
									// 2 : 은행에서 아이템 찾기
									// 3 : DN 입금
									// 4 : DN 출금

	// 1 : 은행에 아이템 보관
		BYTE		tSourceSlot;	// 사용자 아이템이 있던 슬롯 위치
		short		sCount;

	// 2 : 은행에서 아이템 찾기
		BYTE		tSourceSlot;	// 은행에 아이템이 있던 슬롯 위치
		short		sCount;

	// 3 : DN 입금
	 	DWORD		dwDN;			// 소지금
	// 4 : DN 출금
		DWORD		dwDN;			// 소지금
*/

const BYTE	BANK_ITEM_MOVE_RESULT	= 145;
/*
	( C <- S )						// 아이템 이동
	BYTE			tType;			// 0 : 실패
									// 1 : 은행에 아이템 보관
									// 2 : 은행에서 아이템 찾기
									// 3 : DN 입금
									// 4 : DN 출금

	// 1 : 은행에 아이템 보관
	// 2 : 은행에서 아이템 찾기
		typedef struct _tagItem
		{
			byte	bySlot;			// 은행 인벤 슬롯 번호
			short	sLevel;				// 아이템 장착 레벨@@@@@@@@@@@
			short	sSid;
			short	sDuration;
			short	sBullNum;
			short	sCount;
			BYTE	tMagic[6];
			BYTE	tIQ;
		};

		typedef struct _tagItem
		{
			byte	bySlot;			// 사용자 인벤 슬롯 번호
			short	sLevel;				// 아이템 장착 레벨
			short	sSid;
			short	sDuration;
			short	sBullNum;
			short	sCount;
			BYTE	tMagic[6];
			BYTE	tIQ;
		};

	 // 3 : DN 입금
	 // 4 : DN 출금
		DWORD		dwDN;			// 은행내 입금한 총금액
		DWORD		dwDN;			// 소지한 총금액
*/

const BYTE	CURE_RESULT				= 146;
/*
	(C <- S)						// 병원에서 회복과 상태이상 치료 결과를 보낸다.

	BYTE	tType					// 00 : 실패
									// 01 : HP, PP, SP회복
									// 02 : 상태이상 치료
									...
	// 01 : HP, PP, SP회복
	short		sHP;				// HP 값
	short		sPP;				// PP 값
	short		sSP;				// SP 값

	// 02 : 상태이상 치료
	// 예정...
*/

const BYTE	HELP_REQ				= 147;
/*
	(C -> S)						// 서버로 도움말 이벤트를 요청한다.
*/

const BYTE	ZONE_CHANGE_RESULT		= 148;
/*
	(C <- S)						// 존 체인지 결과값을 보낸다.

	BYTE	tType;					// 00 : 실패
									// 01 : 성공
									// 02 : 서버를 바꿔서 존체인지를 해야한다.

	// tType = 00 일때 ----> 추가로 보내는 패킷없음

	// tType = 01 일때
	int		uid;					// 사용자 uid

	short	nPosX;					// X Position
	short	nPosY;					// Y Position
	short	sZone;					// Load Zone Number

	// tType = 02 일때  (서버를 바꿔야 하는 경우)
	Varchar	strAddress;				// 접속할 서버의 IP Address
	int		iPort;					// 접속할 서버의 Port

*/

const BYTE	EBODY_IDENTIFY_OPEN	= 149;
/*
	(S -> C)	// 확인할 수 있는 EBody 목록은 보낸다.

	short		sStoreID;
	short		sCount;				// 확인할 수 있는 EBody의 총갯수

	BYTE		tSlot[sCount];		// 확인할 슬롯 정보

	// EBody 확인 결과는 ITEM_MOVE_RESULT 로 보낸다.
*/

const BYTE EBODY_IDENTIFY_REQ		= 150;
/*
	(C -> S)	// 확인할 아이템목록을 보낸다.

	short		sStoreID;			// 상점아이디
	short		tCount;				// 총갯수

	BYTE		tSlot[sCount];		// 해당 상점에서 확인할수 있는 유저 인벤토리의 슬롯 번호들
*/

const BYTE UPGRADE_ITEM_DIALOG		= 152;
/*
	(C <- S)						// 아이템 업그레이드를 원할때만 보낸다.

	BYTE	tType;					// 아이템 업그레이드 타입
									// 0 : 무기, 방어구
									// 1 : 액세서리
									// 2 : 축 웨피리스, 축 아머리스
									// 3 : 일반 웨피리스, 일반 아머리스
									// 4 : 아이템 개조
									// 5 : Remagic Request with Event
									// 6 : Remagic Request with Event
									// 7 : EBody Upgrade
*/

const BYTE UPGRADE_ITEM_REQ			= 153;
/*
	(C -> S)						// 아이템을 선택하고 동의 할때...

	BYTE	tType;					// 아이템 업그레이드 타입
									// 0 : 무기, 방어구
									// 1 : 액세서리
									// 2 : 축 웨피리스, 축 아머리스
									// 3 : 일반 웨피리스, 일반 아머리스
									// 4 : 아이템 개조
									// 5 : Remagic Request with Event
									// 6 : Remagic Request with Event
									// 7 : EBody Upgrade

	short	sSourceSlot;			// 선택한 아이템 슬롯번호 ( 없으면 -1 ) 

	short	sItemSlot;				// 웨피, 아머, 막대사탕 등 특수 아이템으로 업그레이드, 리매직을 할때

	short   sMaterialSlot1;			// 매직속성 1개 붙은 재료 ( 없으면 -1 )
	short   sMaterialSlot2;			// 매직속성 1개 붙은 재료 ( 없으면 -1 )
	short   sMaterialSlot3;			// 매직속성 1개 붙은 재료 ( 없으면 -1 )
	short   sMaterialSlot4;			// 매직속성 1개 붙은 재료 ( 없으면 -1 )
*/

const BYTE UPGRADE_ITEM_RESULT		= 154;
/*
	(C <- S)						// 아이템 업그레이드 결과를 알린다.

	BYTE	tType;					// 00 : 실패
									// 01 : 성공
									// 02 : 개조성공
									// 03 : 리매직 성공

	BYTE	tChangedSlotNum;		// 변화된 슬롯의 갯수

	typedef struct _tagItem
	{
		byte	bySlot;			// 사용자 인벤 슬롯 번호
		short	sLevel;			// 아이템 장착 레벨
		short	sSid;
		short	sDuration;
		short	sBullNum;
		short	sCount;
		BYTE	tMagic[6];
		BYTE	tIQ;
	}ChangeItems[tChangedSlotNum];
*/

const BYTE TELEPORT_REQ				= 155;
/*
	(C -> S)						// 현재 유저가 보유하고있는 기억좌표값을 요구
*/

const BYTE TELEPORT_RESULT			= 156;
/*
	(C <- S)

	BYTE	tCount;

		typedef struct _tagTel
		{
			BYTE	tIndex;			// 저장된 순서 
			Varchar	TelName;		// 기억장소 이름
			int		nZone;			// 존번호 //yskang 0.9 handy 수정
		};
*/

const BYTE TELEPORT_EDIT_REQ		= 157;
/*
	(C -> S)						// 현재 유저가 보유하고있는 기억좌표중 일부값을 삭제 요구

	BYTE	tType;					// 1 : 기억장소 추가
									// 2 : 기억장소 삭제

	// 1 : 기억장소 추가
	Varchar	TelName;				// 기억장소 이름

	// 2 : 기억장소 삭제
  	BYTE	tIndex;					// 저장된 순서
	Varchar	TelName;				// 기억장소 이름
*/

const BYTE TELEPORT_EDIT_RESULT		= 158;
/*
	(C <- S)

	BYTE	tSuccess;				// 1 : 성공
									// else 실패

	// 1 : 성공
	BYTE	tType;					// 1 : 기억장소 추가
									// 2 : 기억장소 삭제

  	BYTE	tIndex;					// 저장된 순서 
	Varchar	TelName;				// 기억장소 이름
	int		nZone;					// 존 번호 //yskang 0.9 handy 수정
*/

const BYTE TELEPORT_COPY_REQ		= 159;
/*
	(C -> S)						// 해당 유저에게 이동 수락여부를 요구

	int		uid;					// User Index
	VarChar	strUserName;			// 함께 이동을  신청한 유저이름

	BYTE	tSlot;					// 사용하고자 하는 아이템
	BYTE	tIndex;					// 저장된 순서
	Varchar	TelName;				// 기억장소 이름
*/

const BYTE TELEPORT_COPY_DIALOG_REQ	= 160;
/*
	(C <- S)						// 해당 유저에게 이동 수락여부를 요구

	BYTE	tType;					// 1 : 신청인
									// else

	int		uid;					// User Index
	VarChar	strUserName;			// 함께 이동을  신청한 유저이름
*/

const BYTE TELEPORT_COPY_RESULT		= 161;
/*
	(C -> S -> C)					// 이동 수락 여부를 결정

	BYTE	tType;					// 승낙 : 1
									// 거절 : 2
									// 취소 : 3
									// else error

	int		uid;					// User Index
	VarChar	strUserName;			// 함께 이동을  신청한 유저이름
*/

const BYTE GUARD_BOW				= 162;
/*
	(C <- S)						// 경비병 인사를 알린다.

	int		uid;					// 경비병 uid
	BYTE	tDir;					// 보고있는 방향
*/

const BYTE EVENT_UPGRADE_ITEM_REQ   = 163;
/*
	(C -> S)						// 상품권 이벤트를 회수한다.

	BYTE	tEventSlot;				// 이벤트 상품권 슬롯
	BYTE	tItemSlot;				// 업글하기위한 해당 슬롯
*/

//#################################################################
//	Guild		(170 ~ 200)
//#################################################################
const BYTE  GUILD_DIALOG			= 170;
/*
	(C <- S)						// 길드 창립 조건에 맞을때만 보낸다.
*/

const BYTE GUILD_OPEN_REQ			= 171;
/*
	(C -> S)						// 길드 창설 문의

	Varchar		strGuildName;		// 길드 이름
*/

const BYTE GUILD_OPEN_RESULT		= 172;
/*
	(C <- S)						// 길드 창설 결과값을 보낸다.

	BYTE		tTYpe;				// 00 : 실패
									// 01 : 등록 성공

	// 00 : 실패
	BYTE		err					//	01 : 제한 길이를 넘는 길드명칭
									//	02 : 길드 창설 레벨이 모자람
									//	03 : 길드 창설 자금이 모자람
									//	04 : 이미 등록한 길드 명칭임
									//	05 : 다른 길드의 길드원이다.
									//	255 : UnKnown Error
	// 01 : 등록 성공
	int			iSid;				// 길드 인덱스
	VarChar		szGuildName;		// 길드 이름
*/

const BYTE GUILD_ADD_REQ			= 173;
/*
	(C -> S)						// 새로운 길드가 추가되어 클라이언트 파일에 추가 필요.

	int		iGuildID;				// Guild ID
*/

const BYTE GUILD_ADD_RESULT			= 174;
/*
	(C <- S)						// 해당 요청을 보내준다.

	BYTE		tType;				// 00 : 실패
									// 01 : 성공

	// 00 : 실패
	BYTE		err					// 01 : 해당 길드가 없다
									// 255 : UnKnown Error
	// 01 : 해당 길드 정보
	int			iSid;				// 길드 인덱스
	Varchar		strGuildName;		// 길드 이름
	short		sVersion;			// 길드문양 버젼
	VarBinary	GuildMark;			// 길드 문양

*/

const BYTE GUILD_MARK_ADD_REQ		= 175;
/*
	(C -> S)						// 새로운 길드 문양를 추가한다.

	VarBinary	GuildMark;			// 길드 문양
*/

const BYTE GUILD_MARK_ADD_RESULT	= 176;
/*
	(C <- S)						// 해당 요청을 보내준다.

	BYTE		tType;				// 00 : 권한이 없다.
									// 01 : 성공

	// 00 : 실패
	BYTE		err					// 01 : 길드짱 권한이 없다.
									// 02 : 길드가 없다.

	// 01 : 등록 성공
	short		sVersion;
*/

const BYTE	GUILD_WAREHOUSE_OPEN	= 177;
/*
	(C <- S)							// 길드창고에 보관된 아이템과 돈를 보낸다.

		DWORD		GuildDN;				// 길드 창고에 보관된 돈

		BYTE		TotalSlotNum;		// 길드창고에 보관된 아이템 슬롯의 갯수

		typedef struct _tagItem
		{
			byte	bySlot;
			short	sLevel;				// 아이템 장착 레벨@@@
			short	sSid;
			short	sDuration;
			short	sBullNum;
			short	sCount;
			BYTE	tMagic[6];
			BYTE	tIQ;
		} ItemInfo[TotalSlotNum];
*/

const BYTE	GUILD_ITEM_MOVE_REQ		= 178;
/*
	( C -> S )						// 아이템 이동
	BYTE			tType;			// 1 : 길드 창고에 아이템 보관
									// 2 : 길드 창고에서 아이템 찾기
									// 3 : DN 입금
									// 4 : DN 출금

	// 1 : 길드 창고에 아이템 보관
		BYTE		tSourceSlot;	// 사용자 아이템이 있던 슬롯 위치
		short		sCount;

	// 2 : 길드 창고에서 아이템 찾기
		BYTE		tSourceSlot;	// 길드 창고에 아이템이 있던 슬롯 위치
		short		sCount;

	// 3 : DN 입금
	 	DWORD		dwDN;			// 소지금
	// 4 : DN 출금
		DWORD		dwDN;			// 소지금
*/

const BYTE	GUILD_ITEM_MOVE_RESULT	= 179;
/*
	( C <- S )						// 아이템 이동
	BYTE			tType;			// 0 : 실패
									// 1 : 길드 창고에 아이템 보관
									// 2 : 길드 창고에서 아이템 찾기
									// 3 : DN 입금
									// 4 : DN 출금

	// 1 : 길드 창고에 아이템 보관
	// 2 : 길드 창고에서 아이템 찾기
		typedef struct _tagItem
		{
			byte	bySlot;			// 길드 창고 인벤 슬롯 번호
			short	sLevel;			// 아이템 장착 레벨@@@@@@@@@@@
			short	sSid;
			short	sDuration;
			short	sBullNum;
			short	sCount;
			BYTE	tMagic[6];
			BYTE	tIQ;
		};

		typedef struct _tagItem
		{
			byte	bySlot;			// 사용자 인벤 슬롯 번호
			short	sLevel;			// 아이템 장착 레벨
			short	sSid;
			short	sDuration;
			short	sBullNum;
			short	sCount;
			BYTE	tMagic[6];
			BYTE	tIQ;
		};

	 // 3 : DN 입금
	 // 4 : DN 출금
		DWORD		dwDN;			// 길드 창고내 입금한 총금액
		DWORD		dwDN;			// 소지한 총금액
*/

const BYTE GUILD_INFO				= 180;	//@@@@@@@@@@@@ 자리를 Info에 넣어야한다.
/*
	(C <- S)						// 길드 정보를 보낸다.

	int			uid;				// 유저
	int			iGuildID;			// 길드 번호			(-1 : 해당 유저가 길드에 없다)
	VarChar		szGuildName;		// 길드 이름
	short		sVersion;			// 길드 문양 버젼		(-1 : 해당 유저가 길드에 없다)
*/

const BYTE GUILD_USER_INFO_REQ		= 181;
/*
	(C -> S)						// 현재 접속중인 길드원 정보를 요구한다.
*/

const BYTE GUILD_USER_INFO_RESULT	= 182;
/*
	(C <- S)						// 길드 소속원 정보를 보낸다.

	BYTE		tType;				// 1 : 길드 하우스 인원 신청 정보
									// 2 : 길드 마스터가 보는 길드 정보
									// 3 : 포트리스 길마가 길드원 소환
									// else 일반 길드 정보

	// else 일반 길드 정보
	VarChar		strGuildMaster;		// 길드 마스터이름

	BYTE		tCount;				// 길드원 수

	typedef struct _tagGuild
	{
		Varchar		strGuilUser;	// 길드원 이름
		short		sLevel;			// 레벨
	}Guild[tCount];

	// 1 : 길드 하우스 인원 신청 정보
	VarChar		strGuildMaster;		// 길드 마스터이름
	BYTE		tCount;				// 길드원 수

	typedef struct _tagGuild
	{
		Varchar		strGuilUser;	// 길드원 이름
		short		sLevel;			// 레벨
		int			uid;			// 길드 유저

	}Guild[tCount];

  	short		sGuildHouseZone;	// Vertual Room Index
*/

const BYTE GUILD_WAREHOUSE_CLOSE	= 183;
/*	(C -> S)						// 길드창고 창을 닫는다고 통보한다.
*/

const BYTE GUILD_TAX_OPEN			= 184;
/*
	(C <- S)						// 길드상점에서 세금 조정 문의

	short	sStoreID;				// 신청하려는 상점 인덱스
	short	sCurTax;				// 현재 세금..
*/

const BYTE GUILD_TAX_REQ			= 185;
/*
	(C -> S)						// 길드상점에서 세금 조정

	short	sStoreID;
	short	sTax;					// 0 ~ 200%까지
*/

const BYTE GUILD_WAR_OPEN			= 186;
/*
	(C <- S)						//

	short	sStoreID;				// 신청하려는 상점 인덱스
	short	sYear;					// 현재 서버 시간을 기준으로 몇일후...
	BYTE	tMon;
	BYTE	tDay;
*/

const BYTE GUILD_WAR_REQ			= 187;
/*
	(C -> S)						// 길드전 날짜를 결정

	short	sStoreID;
	short	sYear;					//
	BYTE	tMon;
	BYTE	tDay;
	BYTE	tHour
*/

const BYTE GUILD_WAR_APPLY_OPEN		= 188;
/*
	(C <- S)						// 길드전을 신청한다.

	short	sStoreID;
	VarChar	strGuildName;			// 상대 길드이름
*/

const BYTE GUILD_WAR_APPLY_REQ		= 189;
/*
	(C -> S)						// 길드전을 신청한다.

	short	sStoreID;
*/

const BYTE GUILD_WAR				= 190;
/*
	(C <- S)						// 길드전 시작을 알린다.

	BYTE	tType;					// 1 : 길드전 시작..
									// 2 : 길드전 종료...
									// 3 : 길드전중 죽어서 마을로 부활할때...

	BYTE	tGuildWarType;			// 1 : 필드전
									// 2 : 상점전
									// 3 : 공성전

	short	sAreaIndex;				// 전쟁지역(필드전은 = 0)

	// 1 : 길드전 종료시에는 내려가지 않는다.
	TYPE	tGuildUser;				// 0 : 일반유저
									// 1 : 해당 길드원 유저

	// 1 : 해당 길드원이 길드전 시작일때...
	short	sCount;

	typedef struct _GuildList
	{
		int	iGuildID;				// 길드전에 참가한 리스트

	}GuildList[sCount];

*/

const BYTE GUILD_FIELD_WAR_REQ		= 191;
/*
	(C -> S -> C)					// 해당 길마에게 필드전 수락여부를 요구

	int		iGuildID;
	VarChar	strGuildName;			// 필드전을 신청한 길드이름
*/

const BYTE GUILD_FIELD_WAR_RESULT	= 192;
/*
	(C -> S -> C)						// 필드전 수락 여부를 결정

	BYTE	tType;					// 승낙 : 1
									// 거절 : 2
*/

const BYTE SIGHT_INFO_COMPRESSED	= 193;
/*
	꼭 써야행?
*/

const BYTE GUILD_HOUSE_APPLY_REQ	= 194;
/*
	(C -> S)						//

	short	sCount;

	typedef struct _UserList
	{
		int uid;					// 길드 하우스분양에 참가한 리스트

	}UserList[sCount];

  	short	sGuildHouseZone;		// Vertual Room Index
*/

const BYTE GUILD_FORTRESS_NCIRCLE	= 195;
/*
	(C <- S)						// 공성전중 해당 N_Circle의 색이 바뀜을 알려..

	BYTE	tType;					// 0 : N_Circle의 색 변화
									// 1 : 해당 포트리스 길드 점령

	// 0 : N_Circle의 색 변화
	int		Uid;
	BYTE	tColor;					// 0 : defalut(파랑)
									// 1 : Non_default(빨강);

	// 1 : 해당 포트리스 길드 점령
	int		FortressUid;

	int		Uid1;
	int		Uid2;
	int		Uid3;
	int		Uid4;
*/

const BYTE DEL_GUILD_CHAR_REQ		= 196;
/*
	(S <- S)						//
*/

const BYTE GUILD_INVITE_USER_REQ	= 197;
/*
	(S <- S)						//
*/

const BYTE CHALLENGE_GUILD			= 198;
/*
	(C <- S)						// 공성전을 신청한 길드이름을 보낸다.

	short	sCount;

	typedef	struct	_GUILD
	{
		Varchar	strGuildName;
	}GuildInfo[sCount];
*/
const BYTE GUILD_OFF_WITH_THREAD	= 199;		// 길드 탈퇴

const BYTE	NEW_CHAR_REQ_WITH_THREAD = 200;

const BYTE ADDRESS_WINDOW_OPEN		= 201;		// 주소입력창

const BYTE AREA_ATTACK_RESULT		= 202;		// 범위 공격

/*
const BYTE GUILD_WAR_AREA			= 203;		// 범위 공격
/*
	(C <- S)						// 길드전 지역임을 알린다.

	BYTE	tType;					// 1 : 길드전이 시작하는 장소존재
									// 2 : 길드전이 종료하는 장소존재
    short	sCount;

	typedef	struct	_GUILD_AREA
	{
		short	Guild_Area_Index;
	}GuildArea[sCount];

*/

const BYTE DRESSING					= 204;		// 선광
/*
	(C -> S)
	
	(S -> C)

	BYTE	success/fail

	<success>
	short	slot					// 재료가 있던 슬롯
	short	sLevel
	short	sSid
	short	sDuration
	short	sBullNum
	short	sCount
	BYTE	tMagic 6개
	BYTE	tIQ

	<fail>
	none...

*/

const BYTE DRESSING_WINDOW_OPEN		= 205;		// 선광 창 열기

const BYTE ACCOUNT_BANK_OPEN		= 206;		// 은행 열기
/*
	(C -> S)

	none...

	(S -> C)

	byte	ACCOUNT_BANK_OPEN;
	short	store_id;				// 상점 번호 - 창고 이용시 서버로 리턴 시켜 주어야 함
	dword	m_dwAccountBankDN;
	byte	count;

	;;count만큼
	{
		byte	slot;
		short	sLevel;
		short	sSid;
		short	sDuration;
		short	sBullNum;
		short	sCount;

		6개
		{
			byte	tMagic;
		}

		byte	tIQ;

		DWORD	dwCost;				// 물건 각각의 찾을때 소요되는 비용
	}
*/

const BYTE ACCOUNT_BANK_ITEM_MOVE_RESULT = 207;
/*
	(S -> C)

	BYTE	ACCOUNT_BANK_ITEM_MOVE_RESULT;

	BYTE	result;

	
	if(result == 0)
	{
		return;		// fail
	}
	else if(result == 1 )
	{
		은행에 아이템 넣기

		BYTE	bankslot;
		short	sLevel;
		short	sSid;
		short	sDuration;
		short	sBullNum;
		short	sCount;

		BYTE	tMagic * 6개
		BYTE	tIQ;

		byte	userslot;
		short	sLevel;
		short	sSid;
		short	sDuration;
		short	sBullNum;
		short	sCount;

		byte	tMagic;
		byte	tIQ;
	}
	else if(result == 2 )
	{
		은행에서 아이템 빼기

		DWORD	m_dwDN
		DWORD	m_dwAccountBankDN

		short	bankchangeslotcount		// 아이템빼기로 은행에서 변한 슬롯 개수

		bankchangeslotcount 만큼
		{
			BYTE	bankslot			// 뱅크에서 변한 슬롯번호
			short	sLevel
			short	sSid
			short	sDuration
			short	sBullNum
			short	sCount
			
			BYTE	tMagic * 6개
			BYTE	tIQ
		}

		short	myinvenchangecount		// 아이템을 은행에서 찾으므로서 바뀐 내 인벤 슬롯 개수

		myinvenchangecount 만큼
		{
			BYTE	myinvenslot			// 인벤에서 변한 슬롯번호
			short	sLevel
			short	sSid
			short	sDuration
			short	sBullNum
			short	sCount
			
			BYTE	tMagic * 6개
			BYTE	tIQ
		}
	}
	else if(result == 3 )
	{
		은행에 돈넣기

		DWORD	m_dwAccountBankDN		// 은행내 입금한 총금액
		DWORD	m_dwDN					// 소지한 총금액
	}
*/
const BYTE SELECT_OVER100_SKILL		= 208;
/*
	(C -> S)

	BYTE	selectedskill (20-21)
*/

const BYTE ACCOUNT_BANK_ITEM_MOVE_REQ = 209;
/*
	(C -> S)

	BYTE	type

	switch(type)
	{
	case BANK_ITEM_INPUT:
	{
		BYTE	tSourceSlot							// 사용자 아이템이 있던 슬롯 위치
		short	sCount								// 얼마만큼 보관
	}
	case BANK_ITEM_OUTPUT:
	{
		short	store_id
		DWORD	outputdn							// 은행에서 찾을 돈
		short	slotcount							// 몇개의 슬롯에서 찾을 건지

		slotcount만큼
		{
			short	slot							// 은행에서 슬롯 번호
			short	count							// 몇개를 찾을 건지
		}
	}
	case BANK_DN_INPUT:
	{
		DWORD	InputDN								// 은행에 입금할 돈
	}
*/

const BYTE PRE_REG_USER_EVENT_REQ	= 210;
/*
	(S -> C)										// 해당 창을 연다

	(C -> S)										// 입력된값을 보낸다.
	Varchar		strSerialNum;
	
*/

const BYTE PRE_REG_GAMEROOM_EVENT_REQ= 211;
/*
	(S -> C)										// 해당 창을 연다

	(C -> S)										// 입력된값을 보낸다.
	Varchar		strSerialNum;
	Varchar		strSocNum;							// 등록한 사업주의 주민번호
	
*/

const BYTE ADDRESS_WINDOW_OPEN_NEW		= 212;			// 주소입력창


// 중국어 버젼에서 필요한 패킷. 
const BYTE ENCRYPTION_START_REQ			= 213;
/*
	(C -> S)										// Before AccountLogin, Encryption Public_Key request;	

	BYTE	tType;									// Zone Server인지 CharInfo서버에서 접속하는건지 Client에서 구분 필요
*/
const BYTE ENCRYPTION_START_RESULT		= 214;
/*
	(S -> C)

    Varchar		public_key;		// int64

	BYTE		tType;			//					0 : CharInfoServer, 1 : GameStartReq, 2 : ZonLoginReq
*/

const BYTE GUILD_INVITE_REQ				= 215;
/*
	(C -> S -> C)									// 길드 가입 여부를 물어본다.

	int			uid;								// 길드 마스터
*/

const BYTE GUILD_INVITE_RESULT			= 216;
/*
	(C -> S -> C)									// 수락 여부를 결정

	BYTE	tType;									// 승낙 : 1
													// 거절 : 거절당하는 피주체 2
													// 거절 : 주체인 경우 3
													// 서버 거절 : 4

	int			uid;								// 상대방 uid

	// 서버가 거절이면  : 4
	BYTE		error_code;			// 03	: 상대 없음 (귓말, 사람찾기의 경우)
									// 06	: 잘못된 유저아이디(귓말, 사람찾기의 경우)
									// 07	: 해당 길드가 존재하지 않는다.
									// 08	: 해당 길드에 가입한 유저가 아니다.
									// 09	: 이미 다른 길드에 가입한 유저다.
									// 10	: 길드 짱	권한이 없다.
									// 11	: 최대 인원수를 넘었다.
									// 12	: 상대길드가 전쟁중이다.

*/

/////////////////////////////

//-----------------------------------------------------------------------------------------------------
//--yskang 0.1
//길드 기능중 호칭을 부여하기 위하여 추가되는 패킷
//-----------------------------------------------------------------------------------------------------
const BYTE LOVE_NAME_REQ		= 217;		//길드원 호칭[애칭] 추가 또는 삭제 작업을 한다.
/*											//자신의 호칭[애칭] 추가 또는 삭제 작업을 한다.										
	(C -> S)
	BYTE	bCommand;				//1 저장 0 삭제 
	// 1 : 길드원 호칭[애칭] 저장	//<길마가 50이하 Level이면 보내지 않는다,자신이면 80이하...>
	int		uid;					//길드원 uid 또는 자신의 uid
	Varchar LoveName;				//호칭[애칭]
	// 0 : 삭제
	int		uid;
*/


const BYTE LOVE_NAME_RESULT		= 217;
/*
	(C <- S)

	BYTE	tSuccess;				// 1 : 성공
									// 0 : 실패
	// 0 : 실패
	BYTE	error_code;
	01 : 권한이 없다.
	02 : 찾는 아이디가 없다.
	03 : 같은 길드원이 아니다.
	04 : 호칭[애칭]이 잘못되었다.
	05 : 디비에 저장 할 수 없었다.
	06 : 욕이다.
*/
const BYTE LOVE_NAME			= 218; //등록시 같은 화면에 있는 사람에게 전달한다.
/*
	(C <- S)
	int		uid;
	varchar LoveName;
*/

//-----------------------------------------------------------------------------------------------------
// zinee 2002-11-07
// 메일 시스템 패킷
//-----------------------------------------------------------------------------------------------------

const BYTE MAIL_INFO_REQ			= 219;	// 클라이언트에서 메일 정보 요청
/*
	(C -> S)
*/
const BYTE MAIL_INFO_RESULT			= 219;
/*
	(S -> C)
	int		nNewMail			// 새 메일 갯수
	int		nCurMail			// 현재 메일 갯수
*/

const BYTE MAIL_SEND_REQ			= 220;	// 클라이언트에서 메일 보내기 요청
/*
	(C -> S)
	varchar		strRecvID		// 수신자 아이디
	varData		Contents		// 메일내용
*/
const BYTE MAIL_SEND_RESULT			= 220;
/*
	(S -> C)
	BYTE	error
	// 0 : 성공
	// 1 : 우표없음
	// 2 : 존재하지 않는 아이디
	// 3 : 메일 시스템 과부하


	// 성공시.
	typedef struct _tagMailItem		// 우표 아이템의 정보
	{
		short	sSlot;	// Item Slot number
		short	sNum;	// Item count
	};
*/
const BYTE MAIL_LIST_REQ			= 221;
/*
	(C -> S)
	int		nIndex		// 읽고자 하는 메일정보의 시작번호 (-1일경우 처음)
*/
const BYTE MAIL_LIST_RESULT			= 221;
/*
	(S -> C)
	short	nCount			// 리스트 갯수( 존재시 한번요청에 기본 20개 )

	Data					// nCount 갯수만큼 반복 (인덱스,보낸아이디,날짜,읽음여부)
	{
		int		nIndex
		varchar	strSendID
		varchar	Date		// 날짜형식 02/11/23 14:34
		BYTE	bRead		// 0: 새편지 1: 읽은 편지
	}
*/
const BYTE MAIL_CONTENTS_REQ		= 222;
/*
	(C -> S)
	int		nIndex			// 보고자 하는 메일의 고유번호
*/
const BYTE MAIL_CONTENTS_RESULT		= 222;
/*
	(S -> C)
	BYTE	error
							// 0: 성공
							// 1: 찾는편지없음
							// 2: 올바르지 않은 요청(자기편지 아님)

	Data					// 에러가 없을경우(error==0) 따라오는 데이터
	{
		int		nIndex
		vardata	Contents
	}
*/
const BYTE MAIL_DELETE_REQ			= 223;
/*
	(C -> S)
	int		nIndex				// 삭제메일 번호
	
	int		nLastIndex			// 맨마지막 Data요청 인덱스.
*/
const BYTE MAIL_DELETE_RESULT		= 223;
/*
	int		error
								// 0: 성공
								// 1: 존재하지 않는 편지
								// 2: 올바르지 않은 삭제( 자기메일이 아닐경우 )

	// 성공했을때.
	int		nIndex				// 메일 번호

	int		nNewMail			// 새 메일 갯수
	int		nCurMail			// 현재 메일 갯수

	int		nCount			// 마지막 편지갯수 없으면 0 있으면 1
	Data					// 
	{
		int		nIndex		// DELETE_REQ의  nLastIndex에 대한 결과 Index
		varchar	strSendID
		varchar	Date		// 날짜형식 02/11/23 14:34
		BYTE	bRead		// 0: 새편지 1: 읽은 편지
	}
*/

const BYTE REVIVAL_REQ				= 224;
/*
	(S -> C -> S)

	varchar strUserID		// 부활시켜주는 유저 아이디

  	// 성공시 결과값을 USER_INFO로 알려준다. LIVE_REQ 의 결과값과 동일.
	// 실패시 REVIVAL_ERROR 패킷을 전송한다.

*/

const BYTE REVIVAL_RESULT			= 225;
/*
	(S -> C)

	// 클라이언트의 REVIVAL_REQ 요청에 실패할 경우에만 전송되는 패킷

	BYTE	error			// 0: 성공 -> 성공시 USER_INFO 패킷이 따로 뒤따라간다.
							// 1: 부활해주는 유저가 없음(접속이 끊겼거나 기타...이유로)
							// 2: 부활해주는 유저의 인벤에 리버스리온 없음.(다른 유저부활에 사용됐다거나..)
							// 3: 알수없는에러( 유저가 부활할 장소를 못찾을 경우 등등.. )

	/////////////////////////////////////////////////////////////////////////////////////
	// error = 0  : 성공할 경우 USER_INFO의 패킷과 Mode를 제외한 데이터가 뒤따라간다.

		int			uid;			// User index

		// Mode 가 INFO_MODIFY 인 경우만 아래의 데이터 전송
		VarChar		szName;			// User Name
		short		nPosX;			// X Position
		short		nPosY;			// Y Position

		DWORD		dwSkin;			// 피부색(COLORREF)
		DWORD		dwHair;			// 머리색(COLORREF)
		BYTE		byGender;		// 남, 여

		char		szFace[10];		// 얼굴모양
									// 1 : 머리
									// 2 : 얼굴
									// 3 : 눈
									// 4 : 코
									// 5 : 입
									// 6 : 악세사리 1
									// 7 : 악세사리 2
									// 8~10 : 예비

		short		sEquipItem[10];	// 0 = 헬멧
									// 1 = 갑옷
									// 2 = 머리 액세서리
									// 3 = 몸 액세서리
									// 4 = 오른쪽 손 무기
									// 5 = 왼쪽   손 무기
									// 6 = 오른쪽 악세사리
									// 7 = 왼쪽   악세사리
									// 8 = 바지
									// 9 = 신발
									// 아이템을 장착하지 않은 슬롯은 id == -1

		short		sHP;
		short		sMaxHP;

		BYTE		tDir;			// 보고있는 방향

		DWORD		dwAbnormal		// 상태이상정보(Damaged)

									// const DWORD ABNORMAL_NONE			=	0;
									// const DWORD ABNORMAL_POISON			=	1;
									// const DWORD ABNORMAL_CONFUSION		=	1 << 2;
									// const DWORD ABNORMAL_PARALYSIS		=	1 << 3;
									// const DWORD ABNORMAL_BLIND			=	1 << 4;
									// const DWORD ABNORMAL_LIGHT			=	1 << 5;
									// const DWORD ABNORMAL_FIRE			=	1 << 6;
									// const DWORD ABNORMAL_COLD			=	1 << 7;
									// const DWORD ABNORMAL_HASTE			=	1 << 8;
									// const DWORD ABNORMAL_SHIELD			=	1 << 9;
									// const DWORD ABNORMAL_HIDE			=	1 << 10;
									// const DWORD ABNORMAL_DEX_UP			=	1 << 11;
									// const DWORD ABNORMAL_MAX_HP_UP		=	1 << 12;
									// const DWORD ABNORMAL_ADAMANTINE		=	1 << 13;
									// const DWORD ABNORMAL_MIGHTYWEAPON	=	1 << 14;
									// const DWORD ABNORMAL_BERSERKER		=	1 << 15;
									// const DWORD ABNORMAL_HIEXP			=	1 << 16;
									// const DWORD ABNORMAL_MAGICFIND		=	1 << 17;
									// const DWORD ABNORMAL_NOCHAT			=	1 << 18;

									// const DWORD ABNORMAL_FASTRUN			=	1 << 19;
									// const DWORD ABNORMAL_MINDSHOCK		=	1 << 20;
									// const DWORD ABNORMAL_MINDGUARD		=	1 << 21;
									// const DWORD ABNORMAL_PSISHIELD		=	1 << 22;
									// const DWORD ABNORMAL_PIERCING_SHIELD	=	1 << 23;

									// const DWORD OPERATION_MODE			=	1 << 31;	// 운영자 투명 옵션

		short		sCityRank;		// 시민등급

		int			iGuildIndex;	// 길드 인덱스
		VarChar		szGuildName;	// 길드 이름
		short		sVersion;		// 길드 문양 버젼
		BYTE		tClass;			// 클래스 정보
		BYTE		tKillState;		// 보라돌이인지 판단
									// 0 : 정상적인 유저
									// 1 : 보라돌이 유저
		
		VarChar		strLoveName		//호칭[애칭] //-- yskang 0.1	
*/		

//-----------------------------------------------------------------------------------------------------
// Finito
// 226 - Expression Packet - Client packet asking to send expression info
// 255 - Screen capture packet - Sends server date and time to client.
//-----------------------------------------------------------------------------------------------------

const BYTE EXPRESSION_REQ			= 226;
/*
		short		sExpression	
*/
const BYTE EXPRESSION_OPEN			= 230;
const BYTE TRANSFORM_REQ			= 234;
const BYTE PERSONAL_SHOP_REQ		= 239;
const BYTE SCREEN_CAPTURE_REQ		= 245;

#endif
