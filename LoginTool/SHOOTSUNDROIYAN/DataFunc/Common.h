#ifndef _COMMON_H_
#define _COMMON_H_
#include <Winsock2.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#include <ctype.h> 
#include <malloc.h>
#include <memory.h>
#include <time.h>
#include <stdio.h>
#include <process.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <shellapi.h>
#include <wininet.h>

#define FILELOG  "c:\\ShootSunDro.Log"
#define GameName "Droiyan Online"
//#define GameName	"CDX Example 2"

#define MainWndTxt	       "阳光决战-设置"
#define SHOOTSUN_VERSION   "阳光决战1.00 (基于冰风射日所写)"

#define WM_AUTOBANK		0X400+1343
#define WM_AUTOWEAPON	0X400+1344
#define WM_AUTODRUG		0X400+1345
#define WM_AUTODALL		0X400+1346

#define WM_INITUIDATA		0X400+1369
#define WM_POPUPMAIN		0X400+1370
#define WM_CLOSEMAIN		0X400+1371
#define WM_COMMONDMAIN		0X400+1372
#define WM_COMMONDCONFIG1	0X400+1373
#define WM_COMMONDCONFIG2	0X400+1374
#define WM_COMMONDCONFIG3	0X400+1375
#define WM_COMMONDCONFIG3_1	0X400+1376
#define WM_COMMONDCONFIG3_2	0X400+1377
#define WM_COMMONDCONFIG4	0X400+1378
#define WM_COMMONDCONFIG4_1 0x400+1379
#define WM_COMMONDCONFIG4_2 0x400+1380
#define WM_COMMONDCONFIG4_3 0x400+1381
#define WM_COMMONDCONFIG4_4 0x400+1382
#define WM_COMMONDCONFIG5	0X400+1383
#define WM_COMMONDCONFIG5_1 0x400+1384
#define WM_COMMONDCONFIG5_2 0x400+1385
#define WM_COMMONDCONFIG5_3 0x400+1386
#define WM_COMMONDCONFIG6	0X400+1387
#define WM_COMMONDCONFIG6_1	0X400+1388
#define WM_COMMONDCONFIG6_2	0X400+1389
#define WM_COMMONDCONFIG7	0X400+1390
#define WM_COMMONDCONFIG8	0X400+1391
#define WM_COMMONDCONFIG8_1	0X400+1392
#define WM_COMMONDCONFIG8_2	0X400+1393
#define WM_COMMONDCONFIG8_3	0X400+1394
#define WM_COMMONDCONFIG9	0X400+1395
#define WM_COMMONDCONFIG9_1	0X400+1396
#define WM_COMMONDCONFIG9_2	0X400+1397
#define WM_COMMONDCONFIG9_3	0X400+1398
#define WM_COMMONDCONFIG9_4	0X400+1399
#define WM_NOTIFYCONFIG1	0X400+1400
#define WM_NOTIFYCONFIG2	0X400+1401
#define WM_STOP		    0X400+1402

#define WM_NOTIFYCONFIG5    0x400 + 1500
#define WM_NOTIFYCONFIG6    0x400 + 1501

#define WM_COMMON_SPEED1    0x400 + 1502
#define WM_COMMON_SPEED2    0x400 + 1503

#define WM_XOR              0x400 + 1600

#define WM_CONNECT          0x400 + 1700

#define WM_ACCEPT_0            WM_USER + 1
#define WM_ACCEPT_1            WM_USER + 2
#define WM_ACCEPT_2            WM_USER + 3
#define WM_SERVER_READCLOSE_0  WM_USER + 4
#define WM_SERVER_READCLOSE_1  WM_USER + 5
#define WM_SERVER_READCLOSE_2  WM_USER + 6
#define WM_CLIENT_READCLOSE_0  WM_USER + 7
#define WM_CLIENT_READCLOSE_1  WM_USER + 8
#define WM_CLIENT_READCLOSE_2  WM_USER + 9
#define WM_LOGIN_READCLOSE     WM_USER + 10


#define WINTHREAD unsigned __stdcall

#define	D_WORD_XOR1MUL				((WORD)0x009d)
#define	D_WORD_XOR3BASE				((WORD)0x086d)
#define	D_WORD_XOR3MUL				((WORD)0x087b)
#define	D_XORTABLE_LENGTH			8

#define QueryKeyV(s, name, var) \
	size = s; \
	if (RegQueryValueEx(myKey, name, 0, &type, (LPBYTE) var, &size) != 0) { if (err) { RegCloseKey(myKey); return -1; } }

#define SetKeyV(name, var, s, t) \
	RegSetValueEx(myKey, name, 0, t, (LPBYTE) var, s);

#define SERVERTAB                      9
#define MAXDATA                        9
#define MAXMAP                         29
#define MAXPLAYER                      1000
#define MAXFILTER                      1035
#define TABNUMBER                      9               //TAB数量
#define SETTINGNUM                     3               //数据存放的数量
#define OBJ_INFO_CHAIN_NUMBER          500         
#define ID_SHARED_FILE                 "HWIJNTJES"     //共享内存文件名

struct UIDATA
{

	HWND GamehWnd;  //游戏窗口
	HWND hMain;		//主DIALGO窗口
	HWND hGame;
	HWND hDebug;
	BOOL ShowMainDialog;
	BOOL ShowDebugDialog;
	BOOL bInstallUI;
	DWORD GameTheadID;

	HWND hMainConfig[TABNUMBER];	    // 游戏设置TAB窗口
	HWND hInfoConfig[3];

	HWND hMainConfig3_1;
	HWND hMainConfig3_2;

	HWND hMainConfig4_1;
	HWND hMainConfig4_2;
	HWND hMainConfig4_3;
	HWND hMainConfig4_4;

	HWND hMainConfig5_1;
	HWND hMainConfig5_2;
	HWND hMainConfig5_3;

	HWND hMainConfig6_1;
	HWND hMainConfig6_2;

	HWND hMainConfig8_1;
	HWND hMainConfig8_2;
	HWND hMainConfig8_3;

	HWND hMainConfig9_1;
	HWND hMainConfig9_2;
	HWND hMainConfig9_3;
	HWND hMainConfig9_4;

	BOOL RUNED;
	BYTE XorTable[8];

	char szExePath[256];

} ;
struct DATAMAP {

	BYTE Code1;
	BYTE Code2;

	int NaiJiu;
	char Data[256];

} ;

struct STATUS 
{
	BOOL Door;
	int Mode;
} ;

struct MAPDATA 
{
	BYTE Now;              // 现在所在的地区
	BOOL Door;             // 传送门是否可用
	int  Mode;             // 

	int Site;              // 0 银行 1 医院 2 武器
	                       // 3      4      5      6
	                       //            7
	BOOL AutoSave;         // 是否自动保存数据
	char Name[128];        // 该地区的名称
} ;

struct AUTOPLAY
{
	char Name[128];          // 名字

	int Time;               // 时间

	int Danger;             // 危险指数
} ;

/*
    ===============================================================

    队列解决玩家和怪物控制信息↑↓

    enemy_chain1      为包括npc 怪物 玩家，和物品的队列
    enemy_chain2      为地点队列

	=================================================================
*/

struct OBJ_BANK_CHAIN
{
	BYTE Code1;
	BYTE Code2;

	BYTE Index;

	int Mode;               // 0 为不操作 1 为存入银行 2 为携带   

	int Number;             // 维持数量

	OBJ_BANK_CHAIN *next;

} ;

struct SPEAK_CHAIN
{
	BYTE Mode;                            // 发言模式 
	char buf[255];                        //
	BOOL Status;

	SPEAK_CHAIN *next; 
} ;

struct OBJ_INFO_CHAIN
{
	BYTE Code1;
	BYTE Code2;

	// 0 怪物 1 NPC 2 玩家 3 未知 或 等待扩展
	int Mode;                        // 类型

	int X;
	int Y;

	int Number;                      // 数量

	char Name[128];                   // 名称

	char Team[128];                   // 组织


	int BloodMax;                     // 生命数值
	int BloodNow;
};
// 地上物品
struct NOVELITY_SETUP_CHAIN
{
	BYTE Code1;
	BYTE Code2;

	int Mode;

	char Name[128];

	NOVELITY_SETUP_CHAIN *next;
} ;

struct OBJ_CHUM_CHAIN
{
	char Name[128];

	int Mode;

	int Attack;

	OBJ_CHUM_CHAIN *next;
} ;

struct NOVELITY_INFO_CHAIN 
{
	BYTE Code1;
	BYTE Code2;

	int X;
	int Y;

	int Number;

	char Name[128];

	struct NOVELITY_INFO *next;
} ;

struct OBJ_SITE_CHAIN
{
	char Name[128];

	int Time;

	int Danger;

	int X;
	int Y;

	int Mode;

	struct OBJ_SITE_CHAIN *next;
} ;

struct DOOR 
{
	char Name[20];                       // 名称地点
	int Number;                          // 位置
 
	int Mode;                            // 所在星球
	BYTE Site;                           // 地方
	BOOL Status;                         // 是否有数据
} ;

struct SERVER 
{
	char ID[64];
	char IP[32];
	int Port;
} ;

struct FILTER
{
	BYTE Code1;                           // 物品代码
	BYTE Code2;

	char Name[128];                       // 物品名称

	int Mode1;
	int Mode2;
	int Mode3;	
} ;

struct QUEUE
{
	int Mode;                             // 0 人 1 团

	char Name[64];                        // 

	BOOL Status;                          // 是否激活
} ;

struct ATTACK 
{
	QUEUE Queue[30];                      // 

	BYTE Code1;                           // 被攻击目标代码
	BYTE Code2;

	char Name1[64];                       // 敌人代码

	char Name2[64];                       // 队长代码

	int PlayerMode;                       // 现在的模式

	BOOL Enable;                          // 激活

} ;

struct GAMEIP
{
	char Name[64];
	char IP[32];
	unsigned int Port;
} ;

struct CONFIG {

	BOOL AUTO_PLAY;                      // 自动挂机

	int GameMode;                        // 是否在线 0 在线 1 脱机

	BOOL LOADDOOR;                       // 是否加载传送门


	BYTE Server;                         // 服务器列表
	char NameID[128];                    // 临时用户名密码

	char User_Name[32];
	char User_Password[32];

	int Server1;
	int Server2;

	char Char[64];

	BYTE TalkMode;
	char TalkBuf[255];

	BOOL Game;
 
	char IP[32];                         // 
	int Port;
	char IDPassword[128];

	BOOL AUTO_CONNECT;                   // 自动连接 脱离客户端
 
	BOOL AUTO_CONNECT_MODE1;             // 连接模式1
	BOOL AUTO_CONNECT_MODE2;             // 连接模式2

	int AUTO_CONNECT_TIME;               // 数据无响应时自动连接 时间

	BOOL RUNED;

	BOOL PLAYING;                        // 正在游戏

//	BOOL 
	BOOL AUTO_LOCK_TARGET;               // 锁定目标
	BOOL AUTO_GAME_INFO;                 // 战斗信息
	BOOL AUTO_CTRL;                      // 显示拾取
	BOOL AUTO_OTHER_AGGRESSIVE;          // 伴随攻击
	BOOL AUTO_OVER;                      // 法师穿墙
	BOOL AUTO_SELL;                      // 卖掉装备

	BOOL INFO_PLAYER_DIALOG;             // 窗口显示玩家信息
	BOOL INFO_NPC_DIALOG;                // 窗口显示怪物信息

	BOOL AUTO_SAVE_SITE1;                // 是否自动保存添加地点
	BOOL AUTO_SAVE_SITE2;                // 死亡后自动保存地点

	BOOL AUTO_NOVELITY;                  // 自动捡物
	BOOL AUTO_SPELL;                     // 自动加魔法

	BOOL AUTO_NOVELITY_0;                // 拾取白
	BOOL AUTO_NOVELITY_1;                // 拾取粉
	BOOL AUTO_NOVELITY_2;                // 拾取蓝
	BOOL AUTO_NOVELITY_3;                // 拾取黄

	BOOL AUTO_SELL_NOVELITY_0;           // 卖白
	BOOL AUTO_SELL_NOVELITY_1;           // 卖粉
	BOOL AUTO_SELL_NOVELITY_2;           // 卖蓝
	BOOL AUTO_SELL_NOVELITY_3;           // 卖黄

	BOOL NO_ATTACK;                      // 避免误伤
	BOOL RECV_INFO;                      // 顶端信息

	BOOL CHECK_8_1;                      // 法师穿墙
	BOOL CHECK_8_2;

	BOOL AUTO_MONEY;                     // 自动捡钱
	BOOL AUTO_SPEAK;                     // 自动发言

	BOOL AUTO_SPEAK_PK;                  // PK后自动发言
	char SPEAK_PK[256];

	BOOL AUTO_AGGRESSIVE;                // 自动攻击
	BOOL AUTO_COUTERATTACK;              // 自动反击
	BOOL AUTO_MAX_KILL; //自动使用必杀
	int  MaxKill_time;

	BOOL AUTO_ENERGY;                    // 补充能量
	
	BOOL AUTO_BLOOD;                     // 自动加血
	BOOL AUTO_PHYSICAL;                  // 自动体力

	int SPEAK_TIMER;                     // 发言间隔时间

	BOOL AUTO_DO_1;                      // 随身物品
	BOOL AUTO_DO_2;
	BOOL AUTO_DO_3;
	BOOL AUTO_DO_4;

	BOOL CHECK_9_1_1;                    // 
	BOOL CHECK_9_1_2;
	BOOL CHECK_9_1_3;
	BOOL CHECK_9_1_4;
	BOOL CHECK_9_1_5;

	BOOL EDIT_9_1_1;                     // 怪物生命
	BYTE COMBO_9_1_1;                    // 显示模式


	int BLOOD_MODE;                      // 0 = A 1 = B 2 = C
	int BLOOD_ADD_MODE;

	int SPELL_MODE;                      // 0 = A 1 = B 2 = C
	int PHYSICAL_MODE;                   // 0 = A 1 = B 2 = C

	BOOL BACK_CASTLE;                    // 自动回城保护

	BOOL AUTO_BUY;                       // 允许自动购买
	BOOL AUTO_BUYBUMBER;                 // 允许自动调整购买的数量

	int EDIT_OTHER_1;                    // 生命药水购买数值
	int EDIT_OTHER_2;                    // 魔法药水购买数值
	int EDIT_OTHER_3;                    // 
	int EDIT_OTHER_4;                    // 
	int EDIT_OTHER_5;                    // 
	int EDIT_OTHER_6;                    // 

	int BLOOD_USE_MODE;                  // 使用判断模式
	int SPELL_USE_MODE;                  // 

	BOOL AUTO_SELL_SCORE;                // 自动卖装备
	int SELL_SCORE;                      // 分数


	BOOL BANK_0;                         // 银行自动取放蓝
	BOOL BANK_1;

	BOOL AUTO_OPEN_DOOR;                 // 启动的时候自动打开传送门

	int EDIT_8_1_1;                      // 
	int EDIT_8_1_2;                      // 
	int EDIT_8_1_3;
	int EDIT_8_1_4;
	int EDIT_8_1_5;
	int EDIT_8_1_6;
	int EDIT_8_1_7;
	int EDIT_8_1_8;
	int EDIT_8_1_9;
	int EDIT_8_1_10;
	int EDIT_8_1_11;
	int EDIT_8_1_12;
	int EDIT_8_1_13;
	int EDIT_8_1_14;
	int EDIT_8_1_15;
	int EDIT_8_1_16;
	int EDIT_8_1_17;
	int EDIT_8_1_18;
	int EDIT_8_1_19;
	int EDIT_8_1_20;
	int EDIT_8_1_21;
	int EDIT_8_1_22;

	int HotKey;

	int NetSpeed;                        // 网络速度
	int GameSpeed;                       // 游戏速度

	int MoveRunSpeed;                    // 跑步移动速度
	int MoveSpellSpeed;                  // 瞬移移动速度
	int MoveSpeed;                       // 移动速度

	int RUNBUYNUMBER;                    // 购买生命药水底线数值
 

	char Computer_NPC1[3][20];            // 银行
	                                      // 医院
	                                      // 武器	

	char Computer_NPC2[3][20];            // 银行
	                                      // 医院
	                                      // 武器	

	BOOL Player_Mode_1;                  // 
	BOOL Player_Mode_2;                  // 
	BOOL Player_Mode_3;                  // 
	BOOL Player_Mode_4;                  // 
	BOOL Player_Mode_5;                  // 
	BOOL Player_Mode_6;                  // 
	BOOL Player_Mode_7;                  // 
	BOOL Player_Mode_8;                  // 
	BOOL Player_Mode_9;                  // 
	BOOL Player_Mode_10;                 // 
	BOOL Player_Mode_11;                 // 
	BOOL Player_Mode_12;                 // 
	BOOL Player_Mode_13;                 // 
	BOOL Player_Mode_14;                 // 
	BOOL Player_Mode_15;                 // 
	BOOL Player_Mode_16;                 // 

	int AggressiveMode1;                 // 普通攻击选择
	int AggressiveMode2;                 // 伴随攻击选择

	int Speed1;                          // 游戏速度
	int Speed2;                          // 攻击速度

	BOOL WITH_AGGRESSIVE;                 // 是否允许伴随攻击
	BOOL OTHER_ADD_BLOOD;                 // 额外加血

	UINT m_nTalk_TimerID;
	UINT m_nMainAggressive_TimerID;
	UINT m_nOtherAggressive_TimerID;
	UINT m_nSpell_TimerID;
	UINT m_nGameSpeed_TimerID;
	UINT m_nStay_TimerID;
	UINT m_nOtherBlood_TimerID;
	UINT m_nGotoSite_TimerID;
	UINT m_nMove_TimerID;
	UINT m_nBank_TimerID;
	UINT m_Authentication_TimerID;

	BYTE XORTable[8];

	int	m_nGameSpeeder;
	BOOL bSpeedChanged;
	BOOL bCtrlKey;

	BOOL BANK;

	char ServerIP[24];

	int ServerPort;
} ;

struct NOVELITYDATA
{
	BYTE Code[23];
} ;

struct NOVELITYSTATUS
{
	BYTE Now; 
	int Number; 
	int Modify; 
	int Color;
	int Status;
} ;

struct NOVELITYSELL
{
	BOOL Sell;                          // 是否卖掉
	BOOL Recv;                          // 是否接收到改数据卖掉的信息

	char Name[128];                     // 名称

	BYTE Code[24];                      // 代码
} ;

struct NOVELITYUSE
{
	int BloodANumber;                   // 红 A 现在 数量
	int BloodBNumber;
	int BloodCNumber;
	int BloodDNumber;

	BYTE BloodANow;                     // 红 A 现在 位置
	BYTE BloodBNow;
	BYTE BloodCNow;
	BYTE BloodDNow;

	int PhysicalANumber;                // 饼干 A  现在 数量
	int PhysicalBNumber;
	int PhysicalCNumber;

	BYTE PhysicalANow;                  // 饼干 A 现在 位置 
	BYTE PhysicalBNow;
	BYTE PhysicalCNow;

    int SpellANumber;                   // 蓝 A 现在 数量
	int SpellBNumber;
	int SpellCNumber;
	int SpellDNumber;

	BYTE SpellANow;                     // 蓝 A 现在 位置
	BYTE SpellBNow;
	BYTE SpellCNow;
	BYTE SpellDNow;

	int SpellA_Number;                  // 常用 A
	int SpellB_Number;                  // 常用 B

	BYTE SpellA_Now;                    // 常用 A
	BYTE SpellB_Now;                    // 常用 B

	int CityNumber;                     // 回城药水的现在数量
	BYTE CityNow;                       // 回城药水的现在的位置

	int RandomNumber;                   // 闪避药水的现在的数量
	BYTE RandomNow;                     // 闪避药水的现在的位置

	BYTE DoorNumber;                    // 传送门数量 基本无用
	int DoorNow;                        // 传送门位置

	int EnergyWeaponNumber;             // 武器能量包值
	BYTE EnergyWeaponNow;               // 武器能量

	int AggressiveEnergyNow;            // 必杀值
	int AggressiveEnergyMax;            // 最大必杀值
} ;

struct GAMEDATA 
{
	char user[128];
	char password[128];
	char IP[128];
	char PlayerAcount1[128];
	int  PlayerAcount_len;
	char StrPKWARE[20480];
	int PKLen;
	BOOL ALL;                           // 买药 
	BOOL WEAPON;                        // 修理
	BOOL SELL;                          // 卖装备
	BOOL BANK;                          // 银行
	BOOL DRUG;                          // 备药

	BOOL RECV_SELL;                     // 接收卖武器信息
	BOOL RECV_REPAIR;                   // 接收到维修信息
	BOOL RECV_BANK;                     // 接收银行信息


	int PlayerLevel;                    // 等级
	int PlayerMode;                     // 职业类型
	char PlayerName[128];               // 玩家名称
	char PlayerAcount[128];

	DOOR Door[30];                      // 传送门
	BYTE DoorNumber;                    // 传送门数据数量
	BYTE DoorNow;                       // 传送门现在位置
	BOOL DoorTmp;                       // 临时传送门的数据
	int ServerID;
	char stats[8];
	char NamePlayerInfo[256];
	char PlayerInfoPath[256];

	BYTE TalkMode;
	char TalkBuf[256];

	SOCKET s;                           // 

	BOOL Moved;                         // 是否已经开始移动
	BOOL MoveSpell;                     // 是否会移动魔法
	BOOL Goto_Aggressive;               // 是否已经有目标
            // 

	int Goto_X;				            // 目的x坐标
	int Goto_Y;				            // 目的y坐标
	int x;                          //现在X做标
	int y;                          //现在Y做标
	int z;                          // 现在的位置

	int Site_X;                         // 范围
	int Site_Y;                         // 

	int Danger;                         // 危险程度

	BOOL MOTION_STOP;                   // 如果死亡暂时停止所有动作
	BOOL DO_NOVELITY;                   // 打掉怪物后拾取物品中
	BOOL DO_BUY;                        // 如果正在买药或者修理则先忽律挂机
	BOOL DO_MOVE;                       // 职业坐标移动
	BOOL DO_PAUSE;                      // 挂机暂停中
	BOOL DO_MODFIYSITE;                 // 挂机正在更换地点中　，忽律下一次，对本地点怪物攻击
	BOOL DO_BEGIN;                      // 第一次启动挂机标志
	BOOL DO_TMP_SITE;                   // 临时切换地点时需要

	BOOL CONNECTING;                    // 正在连接

	BYTE MYSENDTime1;
	BYTE MYSENDTime2;
	BYTE MYSENDTime3;
	BYTE MYSENDTime4;

	BYTE MYRECVTime1;
	BYTE MYRECVTime2;
	BYTE MYRECVTime3;
	BYTE MYRECVTime4;

	int  BankMode;                       // 是否为私人或综合银行
	BOOL BankInfo;                       // 是否允许接收银行信息

	int Time;                            // 现在的系统时间
	int SiteNumber;                      // 地点数量
	char *TMPDOOR;                       // 临时地点记录
//	int TMPDOORNUMBER;                   // 地点数据
	 

	int Blood_Now;                       // 现在的生命数值
	int Blood_Max;                       // 生命最大数值
	int Blood_N[6];                      // 生命药的位置 a b c d
	int Blood_W;//回城保护

	int Physical_Now;                    // 体力现在的数值
	int Physical_Max;                    // 体力最大值
	int Physical_N[6];                      // 体力的位置 a b c

    int Spell_Now;                       // 魔法现在的数值
    int Spell_Max;                       // 魔法最大值
	int Spell_N[6];                      // 精神药的位置 a b c d ba bb
	BYTE lockID[2]; //锁定攻击的目标
	BYTE Spell_lockID[2];
	BYTE Spell_code;

	int Energy_Now;                      // 当前能量数值
	int EnergyWeapon_Now1;                // 枪当前能量包的位置
	int EnergyWeapon_Now2;                // 剑当前能量包的位置
	int EnergyWeapon_Number;             // 当前能量包的个数
	int Return_Now;   //时空药水

	int ME_X;                            // 玩家现在的x坐标
	int ME_Y;                            // 玩家现在的y坐标 

	int nGotoCounte;					 // 瞬移次数

	BOOL SystemInfo;                    // 是否允许显示系统信息
	char SystemInfoStr[25600];            // 系统信息显示
	BYTE SystemInfoMode;                // 显示模式
	int SystemLen;


	BYTE AggressiveCode1;                // 现在正在攻击的怪物代码
	BYTE AggressiveCode2;                // 现在正在攻击的怪物代码
	char AggressiveStr[128];             // 现在攻击对方的名称

	int AggressiveLast;                  // 上次数值
	int AggressiveNow;                   // 本次攻击数值

	BYTE TempCode1;
	BYTE TempCode2;

	BYTE MeCode1;                        // 玩家现在的代码
    BYTE MeCode2;                        // 玩家地区编号

	int AggressiveX;                     // 怪物x坐标
	int AggressiveY;                     // 怪物y坐标

	BOOL AggressiveStatus;               // 怪物现在的状态

	NOVELITYDATA Novelity39[39];         // 玩家身上的 物品栏 24 
	BOOL SellNovelity39[39];             // 用于卖掉装备临时数据
	BYTE Code39[4];                      // 

	NOVELITYDATA Novelity48[48];         // 私人银行
	BYTE Code48[5];                      // 

	NOVELITYDATA Novelity150[150];       // 综合银行
	BYTE Code150[7]; 

	NOVELITYUSE  Novelity_39;            // 消耗物品
	NOVELITYUSE  Novelity_48;            // 消耗物品
	NOVELITYUSE  Novelity_150;           // 消耗物品

	FILTER SellFilter[24];               // 卖掉装备
	FILTER StayFilter[24];               // 保留装备

	BOOL Player_Mode_1;                  // 
	BOOL Player_Mode_2;                  // 
	BOOL Player_Mode_3;                  // 
	BOOL Player_Mode_4;                  // 
	BOOL Player_Mode_5;                  // 
	BOOL Player_Mode_6;                  //
	BOOL Player_Mode_7;                  //
	BOOL Player_Mode_8;                  //
	BOOL Player_Mode_9;                  //
	BOOL Player_Mode_10;                 // 
	BOOL Player_Mode_11;                 // 
	BOOL Player_Mode_12;                 // 
	BOOL Player_Mode_13;                 //
	BOOL Player_Mode_14;                 // 
	BOOL Player_Mode_15;                 // 
	BOOL Player_Mode_16;                 // 

	STATUS Status;                       // 
} ;

//BOOL GetAllWnd();

HANDLE CreateMapFile();
void ReadDataEx(LPSTR szData,DWORD dwOffsize,DWORD dwCopySize);
void WriteDataEx(LPSTR szData,DWORD dwOffsize,DWORD dwCopySize);

void LoadDoorItem(HWND hWnd);
BOOL GetDoorStatus(char Name[20]);
int GetMeCityMode(BYTE Code);
void AddNovelityInfo(int index);
void AddInfoList(int i, char tmp1[32], char *tmp2, char tmp3[32], char tmp4[32]);
void DeleteAll4_1();
void AddInfoList4_1(int i, char buf1[12], char buf2[128], char buf3[32], char buf4[32]);
void DeleteAll4_2();
void AddInfoList4_2(int i, char buf1[128], char buf2[32]);
void DeleteAll4_3();
void AddInfoList4_3(int i, char buf1[12], char buf2[128], char buf3[32], char buf4[32]);
void DeleteAll5_1();
void AddInfoList5_1(int i, char *buf1, char *buf2, char *buf3);

void DeleteAll6();
void AddInfoList6_1(int i, char *buf1, char *buf2, char *buf3);
void DeleteAll9_1();
void AddInfoList9_1(int i, char *buf1, char *buf2, char *buf3); 
void ConverNPCString(char* szName,char* szPos,char* szDest,int nDestlen);
char* GetMapName(int Code);

void SaveLog_(char *p);
BOOL InstallPKware(char* cExePath);
void UninstallPKware();
int PKware_Implode(char *buf, int nLen, int resLen);
int PKware_Explode(char *buf, int nLen, int resLen);
void TFPKware_(LPBYTE lpTarget, int nLen);

void InstallTab(int index);
void UninstallUI();

//int PoupDialog();

struct NOVELITY_SETUP_CHAIN *add_novelity_setup_obj(char Name[128], int Mode);
struct NOVELITY_SETUP_CHAIN *search_novelity_setup_obj(struct NOVELITY_SETUP_CHAIN *h, char Name[256], NOVELITY_SETUP_CHAIN **pp);
struct NOVELITY_SETUP_CHAIN *sub_novelity_setup_obj(char Name[128]);

void create_site_obj();
void create_chum_obj();
void create_obj();
void clear_obj();

int search_code_obj(BYTE Code1, BYTE Code2);
int search_space_obj();
void add_obj(BYTE Code1, BYTE Code2, int X, int Y, int BloodNow, int BloodMax, int mode, char *buf1, char *buf2);
void sub_obj(BYTE Code1, BYTE Code2);
void modify_obj(BYTE Code1, BYTE Code2, int X, int Y, int BloodNow, int BloodMax);

struct OBJ_SITE_CHAIN *search_time_obj(struct OBJ_SITE_CHAIN *h, int Time, OBJ_SITE_CHAIN **pp);
struct OBJ_SITE_CHAIN *search_site_obj(struct OBJ_SITE_CHAIN *h, char name[128], OBJ_SITE_CHAIN **pp);
struct OBJ_SITE_CHAIN *add_site_obj(char name[128], int Time, int Danger, int X, int Y, int Mode);
struct OBJ_SITE_CHAIN *sub_site_obj(char name[128]);


struct OBJ_CHUM_CHAIN *search_chum_obj(struct OBJ_CHUM_CHAIN *h, char Name[128], OBJ_CHUM_CHAIN **pp);
struct OBJ_CHUM_CHAIN *add_chum_obj(int mode, char Name[128], int Attack);
struct OBJ_CHUM_CHAIN *sub_chum_obj(char name[128]);

struct SPEAK_CHAIN *search_speak_chain(struct SPEAK_CHAIN *h, char name[128], SPEAK_CHAIN **pp);
struct SPEAK_CHAIN *sub_speak_chain(char name[255]);
struct SPEAK_CHAIN *add_speak_chain(char buf[255], int Mode, BOOL Status);
struct OBJ_BANK_CHAIN *add_bank_chain(BYTE Code1, BYTE Code2, BYTE Index, int Mode, int Number);


#endif