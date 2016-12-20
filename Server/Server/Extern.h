#ifndef _EXTERN_H_
#define _EXTERN_H_

#include "ErrorLog.h"

#include "SERVERINFO.h"
#include "MAP.h"
#include "CELL.h"
#include "EVENT.h"
#include "Npc.h"
#include "NpcTable.h"
#include "NpcItem.h"
#include "NpcThread.h"

#include "ItemTable.h"
#include "SkillTable.h"
#include "PsiTable.h"

#include "LevelUpTable.h"
#include "PAMAExp.h"

#include "TableItem.h"	
#include "NpcChat.h"

#include "Store.h"

#include "InitItemTableSet.h"

#include "MagicItemTable.h"

#include "MyDB.h"

#include "Recover.h"
#include "RecoverRate.h"

#include "DNTable.h"
#include "Guild.h"
#include "GuildUser.h"
#include "GuildStoreTable.h"

#include "EBodyTable.h"
#include "SharedMemory.h"
#include "GuildMapInfoTable.h"

#include "GuildHouseWar.h"

#include "VirtualRoom.h"
#include "GuildHouse.h"

#include "UserLevelUpTable.h"

#include "EventItemTable.h" 
#include "EventItemNew.h" 
#include "NpcSayTable.h"

#include "GuildFortress.h"

#include "MonsterPsiSet.h"
#include "DressingSet.h"

#include "AccessoriUpTable.h"
#include "EventBlockingTable.h"

#include "RemodelingTable.h"

#include "BoxEventTable.h"
#include "SummonTable.h"
#include "ServerDlg.h"

#include "EBodyUpgradeTable.h"
#include "EBodyIdentifyTable.h"

typedef CTypedPtrArray <CPtrArray, SERVERINFO*>		ServerArray;
typedef CTypedPtrArray <CPtrArray, ZONEINFO*>		TownPotalArray;
typedef CTypedPtrArray <CPtrArray, TOWNPOTAL*>		RandomTownPotalArray;
typedef CTypedPtrArray <CPtrArray, MAP*>			ZoneArray;
typedef	CTypedPtrArray <CPtrArray, CELL*>			CellArray;
typedef CTypedPtrArray <CPtrArray, EVENT*>			EventArray;
typedef CTypedPtrArray <CPtrArray, CNpc*>			NpcArray;
typedef CTypedPtrArray <CPtrArray, CNpcTable*>		NpcTableArray;
typedef CTypedPtrArray <CPtrArray, CNpcThread*>		NpcThreadArray;
typedef CTypedPtrArray <CPtrArray, TableItem*>		TableItemArray;
typedef CTypedPtrArray <CPtrArray, CItemTable*>		ItemTableArray;
typedef CTypedPtrArray <CPtrArray, CMagicItemTable*>MagicItemTableArray;

typedef CTypedPtrArray <CPtrArray, CAccessoriUpTable*>	AccessoriUpTableArray;
typedef CTypedPtrArray <CPtrArray, CRemodelingTable*>	RemodelingTableArray;

typedef CTypedPtrArray <CPtrArray, CSkillTable*>	SkillTableArray;
typedef CTypedPtrArray <CPtrArray, CPsiTable*>		PsiTableArray;
typedef CTypedPtrArray <CPtrArray, CLevelUpTable*>	LevelUpTableArray;
typedef CTypedPtrArray <CPtrArray, CPAMAExp*>		PAMAExpArray;
typedef CTypedPtrArray <CPtrArray, CNpcChat*>		NpcChatArray;
typedef CTypedPtrArray <CPtrArray, CStore*>			StoreArray;

typedef CTypedPtrArray <CPtrArray, WEATHER_INFO*>		WeatherArray;

typedef CTypedPtrArray <CPtrArray, InitItemTable*>		InitItemTableArray;

typedef CTypedPtrArray <CPtrArray, CRecover*>		RecoverArray;
typedef CTypedPtrArray <CPtrArray, CRecoverRate*>	RecoverRateArray;

typedef CTypedPtrArray <CPtrArray, CDNTable*>		DNArray;
typedef CTypedPtrArray <CPtrArray, CGuild*>			GuildArray;
typedef CTypedPtrArray <CPtrArray, CGuildUser*>		GuildUserArray;
typedef CTypedPtrArray <CPtrArray, CGuildStoreTable*>GuildStoreArray;
typedef CTypedPtrArray <CPtrArray, CGuildHouseWar*>	GuildHouseWarArray;

typedef CTypedPtrArray <CPtrArray, CGuildMapInfoTable*>	GuildMapArray;

typedef CTypedPtrArray <CPtrArray, CSharedMemory*>	SharedMemoryArray;

typedef CTypedPtrArray <CPtrArray, CVirtualRoom*>	VirtualRoomArray;
typedef CTypedPtrArray <CPtrArray, CGuildHouse*>	GuildHouseArray;
typedef CTypedPtrArray <CPtrArray, CUserLevelUpTable*>	UserLevelArray;

typedef CTypedPtrArray <CPtrArray, CEventItemTable*> EventItemArray;
typedef CTypedPtrArray <CPtrArray, CEventItemNew*> EventItemNewArray;

typedef CTypedPtrArray <CPtrArray, CNpcSayTable*> NpcSayArray;

typedef CTypedPtrArray <CPtrArray, CGuildFortress*> GuildFortressArray;

typedef CTypedPtrArray <CPtrArray, DynamicMapList*> DynamicMapArray;

typedef CTypedPtrArray <CPtrArray, CMonsterPsi*> MonsterPsiArray;
typedef CTypedPtrArray <CPtrArray, DRESSING_DATA*> DressingDataArray;

typedef CTypedPtrArray <CPtrArray, int*> MyServerArray;

typedef CTypedPtrArray <CPtrArray, CBoxEventTable*> BoxEventTableArray;
typedef CTypedPtrArray <CPtrArray, CSummonTable*> SummonTableArray;

typedef CTypedPtrArray <CPtrArray, CEBodyTable*>			EBodyArray;
typedef CTypedPtrArray <CPtrArray, CEBodyUpgradeTable*>		EBodyUpgradeTableArray;
typedef CTypedPtrArray <CPtrArray, CEBodyIdentifyTable*>	EBodyIdentifyTableArray;

extern GuildArray			g_arGuildData;
extern GuildUserArray		g_arGuildUser;
extern GuildHouseWarArray	g_arGuildHouseWar;
extern GuildHouseArray		g_arGuildHouse;
extern GuildFortressArray	g_arGuildFortress;
//extern GuildStoreArray		g_arGuildStore;	

extern InitItemTableArray		g_arInitItem;

extern TableItemArray	g_DBItemArray;
		
extern CMyDB				g_DB[];
extern CMyDB				g_DBSession[];
extern CMyDB				g_DBNew[];

extern CErrorLog			g_ErrorLog;
extern HANDLE				g_hIOCP;
extern ZoneArray			g_zone;
// alisia
extern ZoneArray			g_zonesize;
//
extern CellArray			g_cell;
extern EventArray			g_event;

extern ServerArray			g_server;
extern NpcArray				g_arNpc;
extern NpcTableArray		g_arNpcTable;
extern NpcTableArray		g_arCityNpcTable;
extern NpcThreadArray		g_arNpcThread;
extern CNpcItem				g_NpcItem;
extern CNpcItem				g_ValItem;

extern BOOL					g_bNpcExit;

extern ItemTableArray		g_arItemTable;
extern MagicItemTableArray	g_arMagicItemTable;

extern AccessoriUpTableArray	g_arAccessoriUpTable;		// Accessori Upgrade Table
extern CRipel				g_Ripel;						// Ripel's crest

extern RemodelingTableArray	g_arRemodelingTable1;			// 1 단 개조 Table
extern RemodelingTableArray	g_arRemodelingTable2;			// 2 단 개조 Table
extern RemodelingTableArray	g_arRemodelingTable3;			// 3 단 개조 Table

extern CWordArray			g_arRemodelingRandomIndex1;		// 1 단 개조 확율 인덱스
extern int					g_iRemodelingArmorIndex1;		// 1 단 개조 방어구 시작 인덱스
extern CWordArray			g_arRemodelingRandomIndex2;		// 2 단 개조 확율 인덱스
extern int					g_iRemodelingArmorIndex2;		// 2 단 개조 방어구 시작 인덱스
extern CWordArray			g_arRemodelingRandomIndex3;		// 3 단 개조 확율 인덱스
extern int					g_iRemodelingArmorIndex3;		// 3 단 개조 방어구 시작 인덱스

extern BoxEventTableArray	g_arBoxEventTable;				// Box Event Table Array
extern SummonTableArray		g_arSummonTable;				// Summon Monster Table
extern CServerDlg*			g_pMainDlg;

extern SkillTableArray		g_arSkillTable;
extern PsiTableArray		g_arPsiTable;

extern LevelUpTableArray	g_arLevelUpTable;
extern PAMAExpArray			g_arPAMAExp;

extern StoreArray			g_arStore;
extern StoreArray			g_arPsiStore;

extern NpcChatArray			g_arNpcChat;

extern RecoverArray			g_arRecoverTable;
extern RecoverRateArray		g_arRecoverRateTable;

extern DNArray				g_arDNTable;

extern StoreArray				g_arEBodyStore;
extern EBodyArray				g_arEBodyTable;
extern EBodyUpgradeTableArray	g_arEBodyUpgradeTable;
extern EBodyIdentifyTableArray	g_arEBodyIdentifyTable;

extern GuildMapArray		g_arMapTable;

extern VirtualRoomArray		g_arVirtualRoom;

extern UserLevelArray		g_arUserLevel;

extern EventItemArray		g_arEventItemTable;
extern EventItemArray		g_arAddEventItemTable;
extern EventItemNewArray	g_arEventItemNew;

extern NpcSayArray			g_arNpcSayEventTable;

extern DynamicMapArray		g_arDynamicMapTable;

extern MonsterPsiArray		g_arMonsterPsi;
extern DressingDataArray	g_arDressingData;

extern MyServerArray		g_arMyServer;

extern BOOL	g_bDebug;

extern int					g_ItemSerialIndex;

extern int g_8x[];
extern int g_8y[];
extern int g_16x[];
extern int g_16y[];

extern POINT g_rPt[8][6];

extern int g_BrawlClass[];					// 해당 계열에서 사용할수있는 무기계열 종류(아이템 테이블 종류)
extern int g_StaffClass[];
extern int g_EdgedClass[];
extern int g_FireArmsClass[];

extern BYTE g_DynamicSkillInfo[];

//extern _int64				g_OnlineStart;
extern _int64				g_OnlineEnd;
//extern _int64				g_Online_Update_ticks;

extern _int64				g_OnlineMinStart;
extern _int64				g_Online_Update_Min_ticks;

extern long					g_GameTime;
extern long					g_GameDay;
extern long					g_GameMinute;

extern long					g_TotalNPC;			// DB에있는 총 수
extern long					g_CurrentNPCError;	// 세팅에서 실패한 수
extern long					g_CurrentNPC;		// 현재 게임상에서 실제로 셋팅된 수
extern long					g_CurrentGuildCount;// 현재 길드에 등록한 마지막 sid번호 

extern WeatherArray			g_WeatherZone;
extern TownPotalArray		g_TownPotal;
extern RandomTownPotalArray	g_RandomTownPotal;

extern int					g_CityRank[5][3];		// 시민등급당 감소치
extern int					g_CityRankValue[];		// 시민등급 누적치

extern CFile				g_fpSpeedHack;
extern CFile				g_fpBackServer;
extern CFile				g_fpGuildHouseRank;
extern CFile				g_fpEventItem;

extern NpcThreadArray		g_arEventNpcThread;

extern int					g_ClassWeight[];		// 각 계열별 기본 무게

extern SharedMemoryArray	g_arSharedMemory;
extern SharedMemoryArray	g_arStoreSharedMemory;
extern SharedMemoryArray	g_arFortressSharedMemory;
extern SharedMemoryArray	g_arGuildHouseSharedMemory;

extern int	g_ItemAttUpgrade[];
extern int	g_ItemDefUpgrade[];
extern int	g_ItemDefUpgrade_[];
extern int  g_ItemAccessoriUpgrade[];
extern int  g_ItemBlessingUpgrade[];
extern int  g_ItemNormalDownUpgrade[];

extern volatile long g_bShutDown;

extern volatile long g_dwItemSerial;		// Item Logging
extern DWORD g_dwFortressTime;

extern CEventBlockingTable	*g_pEventBlock;

extern int g_iMoonEvent;

extern int g_iAccessoriSlot[MAX_ACCESSORI];
extern const short	SID_RING_OF_LIFE;
extern const short	SID_NECKLACE_OF_SHIELD;
extern const short	SID_EARRING_OF_PROTECT;

#endif