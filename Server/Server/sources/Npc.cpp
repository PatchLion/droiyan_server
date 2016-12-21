// Npc.cpp: implementation of the CNpc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "USER.h"
#include "Npc.h"

#include "Extern.h"
#include "MAP.h"
#include "BufferEx.h"

#include "Mcommon.h"
#include "scdefine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CRITICAL_SECTION m_CS_EventItemLogFileWrite;

//////////////////////////////////////////////////////////////////////
// Fortress Paket Variable
extern CRITICAL_SECTION m_CS_FortressData;
extern CPtrList				RecvFortressData;
extern long nFortressDataCount;
extern struct drop_info g_DropItem[256][4];

//int surround_x[8] = {-2, -1, 0, 1, 2, 1, 0, -1};
//int surround_y[8] = {0, -1, -2, -1, 0, 1, 2, 1};

int surround_x[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int surround_y[8] = {0, -1, -1, -1, 0, 1, 1, 1};

int g_iMoonEvent = 1;

//#define STEP_DELAY			//440

#define UPDATE_EVENT_INVEN_TIME		12

//////////////////////////////////////////////////////////////////////
//	Inline Function
//
inline int CNpc::GetUid(int x, int y )
{
	MAP* pMap = g_zone[m_ZoneIndex];
	return pMap->m_pMap[x][y].m_lUser;
}

inline BOOL CNpc::SetUid(int x, int y, int id)
{
	MAP* pMap = g_zone[m_ZoneIndex];

	if(pMap->m_pMap[x][y].m_bMove != 0) return FALSE;
	if(pMap->m_pMap[x][y].m_lUser != 0 && pMap->m_pMap[x][y].m_lUser != id ) return FALSE;

	pMap->m_pMap[x][y].m_lUser = id;

	return TRUE;
}

BOOL CNpc::SetUidNPC(int x, int y, int id)
{
	MAP* pMap = g_zone[m_ZoneIndex];

	if(pMap->m_pMap[x][y].m_bMove != 0) return FALSE;
	if(pMap->m_pMap[x][y].m_lUser != 0 && pMap->m_pMap[x][y].m_lUser != id ) return FALSE;

	pMap->m_pMap[x][y].m_lUser = id;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNpc::CNpc()
{
	m_NpcVirtualState = NPC_STANDING;
	m_NpcState = NPC_LIVE;

	InitTarget();

	m_ItemUserLevel = 0;
//	m_Delay = 0;			// ´ÙÀ½ »óÅÂ·Î ÀüÀÌµÇ±â ±îÁöÀÇ ½Ã°£( mili/sec )
//	m_dwLastThreadTime = 0;
	m_Delay = 0;
	m_dwLastThreadTime = GetTickCount();

	m_sClientSpeed = 0;		// Å¬¶óÀÌ¾ðÆ® ¾Ö´Ï¸¦ À§ÇÑ ÀÌµ¿ ºñÀ²
	m_dwStepDelay = 0;		// ´ÙÀ½ ÆÖÅ¶±îÁöÀÇ ½Ã°£ µô·¹ÀÌ
	m_tNpcAttType = 0;		// °ø°Ý ¼ºÇâ
	m_tNpcLongType = 0;		// ¿ø°Å¸®(1), ±Ù°Å¸®(0)
	m_tNpcGroupType = 0;	// µµ¿òÀ» ÁÖ´Â³Ä(1), ¾ÈÁÖ´Â³Ä?(0)
//	m_tNpcTraceType = 0;	// ³¡±îÁö µû¶ó°£´Ù(1), ½Ã¾ß¿¡¼­ ¾ø¾îÁö¸é ±×¸¸(0)

	m_pPath = NULL;
	m_pOrgMap = NULL;

//	m_pMap = NULL;
	m_lMapUsed = 0;			// ¸Ê ¸Þ¸ð¸®º¸È£

	m_bFirstLive = TRUE;

	m_tWeaponClass = BRAWL;
	m_dwDelayCriticalDamage = 0;
	m_dwLastAbnormalTime	= GetTickCount();

	::ZeroMemory(m_pMap, sizeof(m_pMap));// ÀÏÂ÷¿ø ¸ÊÀ¸·Î ÃÊ±âÈ­ÇÑ´Ù.

	m_tAbnormalKind = 0;
	m_dwAbnormalTime = 0;

	m_presx = -1;
	m_presy = -1;

	m_lEventNpc = 0;

	m_pGuardStore = NULL;				// ±æµåÀüÀ»À§ÇØ ÇØ´ç »óÁ¡À» °¡Áö°í ¿Â´Ù.
	m_pGuardFortress = NULL;

	m_tRepairDamaged = 0;
	m_tNCircle = NPC_NCIRCLE_DEF_STATE;
	m_lFortressState = 0;
	m_lDamage = 0;

	m_bSummon = FALSE;
	m_sSummonOrgZ = m_sOrgZ;
	m_sSummonOrgX = m_sOrgX;
	m_sSummonOrgY = m_sOrgY;
	m_SummonZoneIndex = m_ZoneIndex;

	m_bSummonDead = FALSE;
	m_lNowSummoning = 0;

	m_lKillUid = -1;
	m_sQuestSay = 0;

	InitSkill();
	InitUserList();
}

CNpc::~CNpc()
{
	ClearPathFindData();

	InitUserList();
}

//////////////////////////////////////////////////////////////////////
//	NPC ½ºÅ³Á¤º¸¸¦ ÃÊ±âÈ­ ÇÑ´Ù.
//
void CNpc::InitSkill()
{
	for(int i = 0; i < SKILL_NUM; i++)
	{
		m_NpcSkill[i].sSid = 0;
		m_NpcSkill[i].tLevel = 0;
		m_NpcSkill[i].tOnOff = 0;
	}
}

///////////////////////////////////////////////////////////////////////
//	±æÃ£±â µ¥ÀÌÅÍ¸¦ Áö¿î´Ù.
//
void CNpc::ClearPathFindData()
{
	::ZeroMemory(m_pMap, sizeof(m_pMap));	// ÀÏÂ÷¿ø ¸ÊÀ» À§ÇØ
/*	int i;

	if(m_pMap)
	{
		int **tmp = m_pMap;
		
		m_pMap = NULL;

		for(i = 0; i < m_vMapSize.cx; i++)
		{
			delete[] tmp[i];
		}
		delete[] tmp;
	}
*/
}

///////////////////////////////////////////////////////////////////////
// NPC °¡ Ã³À½ »ý±â°Å³ª Á×¾ú´Ù°¡ »ì¾Æ³¯ ¶§ÀÇ Ã³¸®
//
BOOL CNpc::SetLive(COM* pCom)
{
	NpcTrace(_T("SetLive()"));

	if(m_tRepairDamaged > 0) return FALSE;		 // °ø¼ºÀüÁß ¼Õ»ó ¹Þ¾Ò´Ù¸é ¼ö¸®µÉ¶§±îÁö ±×´ë·Î À¯ÁöµÇ¾î¾ßÇÔ...
	if(m_pGuardFortress && m_tGuildWar == GUILD_WARRING)
	{
		if(!m_bFirstLive) return FALSE;
	}
	else m_tGuildWar = GUILD_WAR_AFFTER;		// ¸ðµç ¸÷À» ±æµåÀü¿¡ ´ëÇØ¼­ ÃÊ±âÈ­ÇÑ´Ù...

	if(m_bSummonDead)							// ¼ÒÈ¯‰ç¾ú´ø ¸÷¿¡ ´ëÇØ¼­
	{
		m_ZoneIndex = m_TableZoneIndex;
		m_sCurZ		= m_sOrgZ	= m_sTableOrgZ;
		m_sOrgX		= m_sTableOrgX;
		m_sOrgY		= m_sTableOrgY;
		
		m_pOrgMap = g_zone[m_ZoneIndex]->m_pMap;	// MapInfo Á¤º¸ ¼ÂÆÃ
		
		m_bSummonDead = FALSE;
	}

	// NPCÀÇ HP, PP ÃÊ±âÈ­ ----------------------//	
	int i = 0, j = 0;
	m_sHP = m_sMaxHP;
	m_sPP = m_sMaxPP;
	NpcDrop=4;
	int iTryLiveCount = 0;

	InitTarget();

	InitUserList();					// Å¸°ÙÀ»À§ÇÑ ¸®½ºÆ®¸¦ ÃÊ±âÈ­.	

	// NPC ÃÊ±âÀ§Ä¡ °áÁ¤ ------------------------//
	MAP* pMap = g_zone[m_ZoneIndex];
	
	m_nInitMinX = m_sOrgX - m_sMinX;		if(m_nInitMinX < 1) m_nInitMinX = 1; 
	m_nInitMinY = m_sOrgY - m_sMinY;		if(m_nInitMinY < 1) m_nInitMinY = 1; 
	m_nInitMaxX = m_sOrgX + m_sMaxX;		if(m_nInitMaxX >= pMap->m_sizeMap.cx) m_nInitMaxX = pMap->m_sizeMap.cx - 1;
	m_nInitMaxY = m_sOrgY + m_sMaxY;		if(m_nInitMaxY >= pMap->m_sizeMap.cy) m_nInitMaxY = pMap->m_sizeMap.cy - 1;

	CPoint pt;
	CPoint ptTemp;

	int modify_index = 0;
	char modify_send[2048];	

//	if(m_lEventNpc == 0 && m_sEvent == 1000) return TRUE;//@@@@@@@@@@@@@@@@@@@@@@ Test Code(ÀÓ½Ã·Î ¸÷À» ¼ÒÈ¯ÇÏ±âÀ§ÇØ)

	if(m_lEventNpc == 1 && !m_bFirstLive) 
	{
		// À¯Àú¿¡°Ô NPC Á¤º¸Àü¼Û... 
		// ÀÌÀ¯ : Á×Àº ¸ð½ÀÀ» º¸¿©Áà¾ßÇÏ±â¶§¹®¿¡ ´ÙÀ½ ¸®Á¨µÉ Â÷·Ê°¡ ¿Ã¶§ INFO_DELETE¸¦ º¸³½´Ù. 
		::ZeroMemory(modify_send, sizeof(modify_send));

		for(int i = 0; i < NPC_NUM; i++)
		{
			if(g_arEventNpcThread[0]->m_ThreadInfo.pNpc[i] != NULL)
			{
				if(g_arEventNpcThread[0]->m_ThreadInfo.pNpc[i]->m_sNid == m_sNid)
				{
					FillNpcInfo(modify_send, modify_index, INFO_DELETE);
					SendInsight(pCom, modify_send, modify_index);

					g_arEventNpcThread[0]->m_ThreadInfo.pNpc[i] = NULL;
					InterlockedExchange(&m_lEventNpc, (LONG)0);
					InterlockedExchange(&g_arEventNpcThread[0]->m_ThreadInfo.m_lNpcUsed[i], (LONG)0);								
					return TRUE;
				}
			}
		}
		return TRUE;
	}

	if(m_tNpcType != NPCTYPE_MONSTER && m_bFirstLive)//NPCTYPE_DOOR || m_tNpcType == NPCTYPE_GUARD)
	{
		m_nInitX = m_sCurX = m_sOrgX;
		m_nInitY = m_sCurY = m_sOrgY;

		pMap->m_pMap[m_sCurX][m_sCurY].m_lUser = m_sNid + NPC_BAND;

//		TRACE("NPC DOOR %s(nid = %d) - %d %d\n", m_strName, m_sNid, m_sCurX, m_sCurY);
		CPoint temp = ConvertToClient(m_sCurX, m_sCurY);
		TRACE("NPC DOOR %s(nid = %d) - %d %d\n", m_strName, m_sNid, temp.x, temp.y);
	}
	else
	{
		while(1)
		{
			i++;
																						
			if(m_lEventNpc == 1)			// ¼ÒÈ¯¸÷ÀÏ°æ¿ì µÇµµ·ÏÀÌ¸é Ã³À½ ÁöÁ¤ÇÑ ÁÂÇ¥·Î
			{
				if(pMap->m_pMap[m_sOrgX][m_sOrgY].m_bMove == 0)	
				{ 
					pt.x = m_sOrgX; 
					pt.y = m_sOrgY; 
					
					m_nInitX = m_sCurX = pt.x;
					m_nInitY = m_sCurY = pt.y;
					
					//ptTemp = ConvertToClient(m_sCurX, m_sCurY);
					break;
				}
				else
				{
					pt = FindNearRandomPoint(m_sOrgX, m_sOrgY);
					if(pt.x <= 0 || pt.y <= 0) 
					{
						pt.x = myrand(m_nInitMinX, m_nInitMaxX);
						pt.y = myrand(m_nInitMinY, m_nInitMaxY);
					}
				}
			}
			else
			{
				pt.x = myrand(m_nInitMinX, m_nInitMaxX);
				pt.y = myrand(m_nInitMinY, m_nInitMaxY);

				// Test Code By Youn Gyu 02-08-13 (ÇöÀç´Â ÁÖº¯ 25¼¿·Î¸¸ Á¦ÇÑ)
				if( m_sCurZ != 1 && m_sCurZ != 1005 ) // ÀÏ´Ü ´øÁ¯¸¸ Ã£´Â´Ù.
				{
					if(m_tNpcType == NPCTYPE_MONSTER)
					{
						if( !CheckUserForNpc_Live(pt.x, pt.y) )
						{
							iTryLiveCount += 1;
							if(iTryLiveCount >= 20) return FALSE;
							else continue;
						}
					}
				}
				//TRACE("MONSTER %s(nid = %d) - %d %d\n", m_strName, m_sNid, m_sCurX, m_sCurY);
			}
			
			if(pt.x < 0 || pt.x >= pMap->m_sizeMap.cx) continue;
			if(pt.y < 0 || pt.y >= pMap->m_sizeMap.cy) continue;

			if(pMap->m_pMap[pt.x][pt.y].m_bMove != 0 || pMap->m_pMap[pt.x][pt.y].m_lUser != 0)
			{
				if(i >= 100) 
				{
					m_nInitX = m_sCurX = m_sOrgX;
					m_nInitY = m_sCurY = m_sOrgY;
//					TRACE("sid = %d, loop = %d My standing point is invalid x = %d, y = %d\n", m_sSid, i, pt.x, pt.y);
					InterlockedIncrement(&g_CurrentNPCError);
					return FALSE;
//					break;
					
/*					DeleteNPC();// »èÁ¦°¡ ¾Æ´Ô...
					TRACE("sid = %d, loop = %d My standing point is invalid x = %d, y = %d\n", m_sSid, i, pt.x, pt.y);
					return FALSE;
*/					
				}
				continue;
			}

			m_nInitX = m_sCurX = pt.x;
			m_nInitY = m_sCurY = pt.y;

//			ptTemp = ConvertToClient(m_sCurX, m_sCurY);
			break;
		}
	}

	SetUid(m_sCurX, m_sCurY, m_sNid + NPC_BAND);

	if(m_sDimension > 0) SetMapTypeBeforeGuildWar(pCom);		// ¸ÊÀ» ¼ÂÆÃÇÑ´Ù.

	// »óÅÂÀÌ»ó Á¤º¸ ÃÊ±âÈ­
	m_dwLastAbnormalTime	= GetTickCount();
	m_tAbnormalKind = 0;
	m_dwAbnormalTime = 0;

	// °ø¼ºÀü¿¡¼­ NPC HP°¡ ¼ö¸®°¡ ¾ÈµÇ¾î ÀÖÀ¸¸é
//	if(m_pGuardFortress) SetFortressState();
	
	if(m_bFirstLive)	// NPC °¡ Ã³À½ »ì¾Æ³ª´Â °æ¿ì
	{
		NpcTypeParser();
		m_tWeaponClass = GetWeaponClass();
		m_bFirstLive = FALSE;

		InterlockedIncrement(&g_CurrentNPC);
	}

	// ¸÷À» ¸¶Áö¸·À¸·Î Á×ÀÎ À¯ÀúÀÇ uid ÃÊ±âÈ­
	m_lKillUid = -1;

	// Test Code
//	CString strTemp = m_strName;
//	if(strTemp == "Äý" || strTemp == "±×·¹ÀÌÆ®ºòÇ²")m_sHP = 1;

	// À¯Àú¿¡°Ô NPC Á¤º¸Àü¼Û...
	modify_index = 0;
	::ZeroMemory(modify_send, sizeof(modify_send));
	FillNpcInfo(modify_send, modify_index, INFO_MODIFY);

	SendInsight(pCom, modify_send, modify_index);

	m_presx = -1;
	m_presy = -1;

	SightRecalc(pCom);

	return TRUE;
}


///////////////////////////////////////////////////////////////////
//	NPC ±âº»ÀûÀÎ ¼ºÇâÀ» ºÐ·ù, ¼ÂÆÃÇÑ´Ù.
//
void CNpc::NpcTypeParser()
{
	MYSHORT sAI;

	BYTE upTemp = 0;			// »óÀ§ 8ºñÆ®
	BYTE dwTemp = 0;			// ÇÏÀ§ 8ºñÆ®

	sAI.i = (short)m_sAI;

	upTemp = sAI.b[0];
	dwTemp = sAI.b[1];
//	temp = m_sAI;//m_byAI

	m_tNpcAttType = upTemp >> 7;

	upTemp = upTemp << 1;
	m_tNpcLongType = upTemp >> 7;

	upTemp = upTemp << 1;
	m_tNpcGroupType = upTemp >> 7;

	m_iNormalATRatio = m_byIronSkin;
	m_iSpecialATRatio = m_byReAttack;
	m_iMagicATRatio = m_bySubAttack;

	m_tSPATRange = m_byWildShot;

/*
	switch( (int)m_byVitalC )
	{
	case	0:	// ÀÏ¹Ý¸¸
		m_bCanNormalAT = TRUE;
		m_bCanMagicAT = FALSE;
		m_bCanSPAT = FALSE;
		break;

	case	1:	// ¸ÅÁ÷¸¸
		m_bCanNormalAT = FALSE;
		m_bCanMagicAT = TRUE;
		m_bCanSPAT = FALSE;
		break;

	case	2:	// ÀÏ¹Ý, Æ¯¼ö
		m_bCanNormalAT = TRUE;
		m_bCanMagicAT = FALSE;
		m_bCanSPAT = TRUE;

		m_tSPATRange = m_byWildShot;
		m_tSPATAI = m_byExcitedRate;
		break;

	case	3:	// ¸ÅÁ÷, Æ¯¼ö
		m_bCanNormalAT = FALSE;
		m_bCanMagicAT = TRUE;
		m_bCanSPAT = TRUE;

		m_tSPATRange = m_byWildShot;
		m_tSPATAI = m_byExcitedRate;
		break;

	case	4:	// ÀÏ¹Ý, ¸ÅÁ÷
		m_bCanNormalAT = TRUE;
		m_bCanMagicAT = FALSE;
		m_bCanSPAT = TRUE;
		break;

	case	5:	// Æ¯¼ö¸¸
		m_bCanNormalAT = FALSE;
		m_bCanMagicAT = FALSE;
		m_bCanSPAT = TRUE;

		m_tSPATRange = m_byWildShot;
		m_tSPATAI = m_byExcitedRate;
		break;

	case	6:	// ÀÏ¹Ý, ¸ÅÁ÷, Æ¯¼ö
		m_bCanNormalAT = TRUE;
		m_bCanMagicAT = TRUE;
		m_bCanSPAT = TRUE;

		m_tSPATRange = m_byWildShot;
		m_tSPATAI = m_byExcitedRate;
		break;

	default:
		m_bCanNormalAT = TRUE;
		m_bCanMagicAT = FALSE;
		m_bCanSPAT = FALSE;
		break;

	}
*/
}

///////////////////////////////////////////////////////////////////
//	NPC ÁÖº¯ÀÇ ÀûÀ» Ã£´Â´Ù.
//
BOOL CNpc::FindEnemy(COM *pCom)
{
	BOOL bSearch = FALSE;

	if(m_tNpcType == NPCTYPE_NPC || m_tNpcType == NPCTYPE_DOOR || m_tNpcType == NPCTYPE_GUILD_DOOR) return FALSE;
	if(m_tNpcType == NPCTYPE_GUILD_NPC || m_tNpcType == NPCTYPE_GUILD_MARK) return FALSE;

	if(m_byAX == 0 && m_byAZ == 0 ) return FALSE;		// ³»°¡ °ø°Ý·ÂÀÌ ¾øÀ¸¸é °ø°ÝÇÏÁö ¾Ê´Â´Ù
	if(m_bySearchRange == 0) return FALSE;
	if(m_tNpcType == NPCTYPE_GUARD) bSearch = TRUE;
	if(m_tNpcType == NPCTYPE_GUILD_GUARD)
	{
		if(m_pGuardFortress && m_tRepairDamaged == NPC_DEAD_REPAIR_STATE) return FALSE;
		// °ø¼ºÀü¿¡¼­ ÇØ´ç ±¤¼±Æ÷ HP°¡ 0ÀÌ¸é µ¿ÀÛ ºÒ´ÉÀÓ 
		 bSearch = TRUE;
	}

	if(!bSearch && !m_tNpcAttType && m_Target.id < 0 )
	{
		return FALSE;
	}
	else
	{
//		if( (GetTickCount() - m_dLastFind) < (DWORD)1000 )
		if( (GetTickCount() - m_dLastFind) < (DWORD)2000 )
		{
			return FALSE;
		}
	}

	m_dLastFind = GetTickCount();

//	if(m_Target.id != -1) return TRUE;

	int min_x, min_y, max_x, max_y;

	min_x = m_sCurX - m_bySearchRange;		if( min_x < 0 ) min_x = 0;
	min_y = m_sCurY - m_bySearchRange;		if( min_y < 0 ) min_y = 0;
	max_x = m_sCurX + m_bySearchRange;
	max_y = m_sCurY + m_bySearchRange;

	if(max_x >= g_zone[m_ZoneIndex]->m_sizeMap.cx) max_x = g_zone[m_ZoneIndex]->m_sizeMap.cx - 2;
	if(max_y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) max_y = g_zone[m_ZoneIndex]->m_sizeMap.cy - 2;

	int ix, iy;
	int target_uid;
	int uid;
	int rank = 0;

	USER *pUser = NULL;
	CNpc *pNpc = NULL;

	int tempLevel = 0, oldLevel = 1000;

	for(ix = min_x; ix <= max_x; ix++)
	{
		for(iy = min_y; iy <= max_y; iy++)
		{
			target_uid = m_pOrgMap[ix][iy].m_lUser;

			if( target_uid >= USER_BAND && target_uid < NPC_BAND )
			{
				uid = target_uid - USER_BAND;

				pUser = GetUser(pCom, uid);
				if( pUser != NULL && pUser->m_bLive == USER_LIVE)
				{
					if( ix != pUser->m_curx || iy != pUser->m_cury )
					{
						continue;
					}

					if(m_tNpcType == NPCTYPE_GUARD || m_tNpcType == NPCTYPE_GUILD_GUARD)
					{
						//rank = DEATH_RANK - CITY_RANK_INTERVAL;
						if(pUser->m_sKillCount > 100 || pUser->m_bPkStatus)
						{
							m_Target.id	= target_uid;
							m_Target.failCount = 0;
							m_Target.x	= ix;
							m_Target.y	= iy;							
							return TRUE;
						}
					}
																	// ±æµåÀüÇÒ¶§´Â »óÁ¡¼ÒÀ¯ ±æµå¿øÀº ¹«½Ã
					if(m_tNpcType == NPCTYPE_GUILD_GUARD)	
					{
						if(m_tGuildWar == GUILD_WARRING)
						{
							//if(pUser->m_dwGuild == m_pGuardStore->m_iGuildSid) continue;
							if(m_pGuardStore) 
							{
								if(pUser->m_dwGuild == m_pGuardStore->m_iGuildSid) continue;
							}
							else if(m_pGuardFortress)
							{
								if(pUser->m_dwGuild == m_pGuardFortress->m_iGuildSid) continue;
							}

							m_Target.id	= target_uid;
							m_Target.failCount = 0;
							m_Target.x	= ix;
							m_Target.y	= iy;
							return TRUE;
						}
					}

					if(pUser->m_tIsOP == 1) continue;				// ¿î¿µÀÚÀÌ¸é ¹«½Ã...^^
					if(pUser->m_bPShopOpen == TRUE) continue;		// User has personal shop
//					if(pUser->m_dwHideTime > 0) continue;			// Àº´Ð »óÅÂ¸é ¹«½ÃµÈ´Ù.
					//ÈÄ°ø¸÷...
					if(!m_tNpcAttType)		// ³¯ °ø°ÝÇÑ ³ðÀ» Ã£´Â´Ù.
					{
						if(IsDamagedUserList(pUser) || (m_tNpcGroupType && m_Target.id == target_uid))
						{
							m_Target.id	= target_uid;
							m_Target.failCount = 0;
							m_Target.x	= ix;
							m_Target.y	= iy;
							return TRUE;
						}
					}
					else	// ¼±°ø¸÷...
					{						
						if(IsSurround(ix, iy) == TRUE) continue;	//µÑ·¯ ½×¿© ÀÖÀ¸¸é ¹«½ÃÇÑ´Ù.(¿ø°Å¸®, ±Ù°Å¸® ¹«½Ã)

						USER *pTUser;

						pTUser = pCom->GetUserUid(uid);
						if ( pTUser == NULL ) continue;

						tempLevel = pTUser->m_sLevel;

						if(tempLevel <= oldLevel) 
						{
							oldLevel = tempLevel;									
							m_Target.id	= target_uid;
							m_Target.failCount = 0;
							m_Target.x	= ix;
							m_Target.y	= iy;
							return TRUE;
						}
					}
				}
			}
		}
	}

	InitUserList();		// ¾Æ¹«µµ ¾øÀ¸¹Ç·Î ¸®½ºÆ®¿¡ °ü¸®ÇÏ´Â À¯Àú¸¦ ÃÊ±âÈ­ÇÑ´Ù.
	InitTarget();

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//	ÁÖº¯¿¡ ³ª¸¦ °ø°ÝÇÑ À¯Àú°¡ ÀÖ´ÂÁö ¾Ë¾Æº»´Ù
//
BOOL CNpc::IsDamagedUserList(USER *pUser)
{
//	int count = m_arDamagedUserList.GetSize();
	if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) return FALSE;

	int sLen = strlen(pUser->m_strUserID);

	if(sLen < 0 || sLen > CHAR_NAME_LENGTH) return FALSE;

	for(int i = 0; i < NPC_HAVE_USER_LIST; i++)
	{
		if(strcmp(m_DamagedUserList[i].strUserID, pUser->m_strUserID) == 0) return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//	Target °ú NPC °£ Path FindingÀ» ¼öÇàÇÑ´Ù.
//
BOOL CNpc::GetTargetPath(COM* pCom)
{
	USER* pUser = GetUser(pCom, m_Target.id - USER_BAND);
	if(pUser == NULL)
	{
		InitTarget();
		return FALSE;
	}
	if(pUser->m_sHP <= 0 || pUser->m_state != STATE_GAMESTARTED || pUser->m_bLive == FALSE)
	{
		InitTarget();
		return FALSE;
	}
/*	if(strcmp(m_Target.szName, pUser->m_strUserID) != 0)
	{
		InitTarget();
		return FALSE;
	}
*/
	int iTempRange = m_bySearchRange;				// ÀÏ½ÃÀûÀ¸·Î º¸Á¤ÇÑ´Ù.
//	if(m_arDamagedUserList.GetSize()) iTempRange *= 2;	// °ø°Ý¹ÞÀº »óÅÂ¸é Ã£À» ¹üÀ§ Áõ°¡.
	if(IsDamagedUserList(pUser)) iTempRange *= 2;	// °ø°Ý¹ÞÀº »óÅÂ¸é Ã£À» ¹üÀ§ Áõ°¡.
	else iTempRange += 4;
	
	int min_x = m_sCurX - iTempRange;	if(min_x < 0) min_x = 0;
	int min_y = m_sCurY - iTempRange;	if(min_y < 0) min_y = 0;
	int max_x = m_sCurX + iTempRange;	if(max_x >= g_zone[m_ZoneIndex]->m_sizeMap.cx) max_x = g_zone[m_ZoneIndex]->m_sizeMap.cx - 1;
	int max_y = m_sCurY + iTempRange;	if(max_y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) max_y = g_zone[m_ZoneIndex]->m_sizeMap.cy - 1;

	// ¸ñÇ¥Á¡ÀÌ Search Range¸¦ ¹þ¾î³ªÁö ¾Ê´ÂÁö °Ë»ç
	CRect r = CRect(min_x, min_y, max_x+1, max_y+1);
	if(r.PtInRect(CPoint(pUser->m_curx, pUser->m_cury)) == FALSE) return FALSE;

	// Run Path Find ---------------------------------------------//
	CPoint start, end;
	start.x = m_sCurX - min_x;
	start.y = m_sCurY - min_y;
	end.x = pUser->m_curx - min_x;
	end.y = pUser->m_cury - min_y;

	m_ptDest.x = m_Target.x;
	m_ptDest.y = m_Target.y;

	m_min_x = min_x;
	m_min_y = min_y;
	m_max_x = max_x;
	m_max_y = max_y;

	return PathFind(start, end);
}

////////////////////////////////////////////////////////////////////////////////
//	NPC °¡ Path Find ÇÏ·Á´Â ¸¶Áö¸· Á¡Àº ÇöÀç ¾Ë°í¸®Áò»ó Ç×»ó ÀÌµ¿ºÒ°¡ ÁÂÇ¥ÀÌ¹Ç·Î
//	¸¶Áö¸· ÁÂÇ¥¸¦ ¼öÁ¤
//	
//	## ÇöÀç(2000-12-12) ÆÐ½ºÆÄÀÎµå ¾Ë°í¸®ÁòÀÌ ¼öÁ¤µÇ¾î ÀÌ ÇÔ¼ö´Â ÇÊ¿ä¾øÀ½ ##
BOOL CNpc::GetLastPoint(int sx, int sy, int& ex, int& ey)
{
	int i;
	int x = 0, y = 0;
	int nx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
	int ny[] = {-1, -1, -1, 0, 1, 1, 1, 0};
	
	BOOL bSearchDest = FALSE;
	MAP* pMap = g_zone[m_ZoneIndex];
	for(i = 0; i < sizeof(nx)/sizeof(nx[0]); i++)
	{
		x = ex + nx[i]; 
		if(x >= pMap->m_sizeMap.cx) x--;
		if(x < 0) x = 0;

		y = ey + ny[i];
		if(y >= pMap->m_sizeMap.cy) y--;
		if(y < 0) y = 0;
		
		if(m_pOrgMap[x][y].m_bMove == 0 && m_pOrgMap[x][y].m_lUser == 0) 
		{
			ex = x;
			ey = y;
			bSearchDest = TRUE;
			break;
		}
	}

	if (bSearchDest) return TRUE;

	int nSearchSize = max(abs(sx - ex), abs(sy - ey));
//	ASSERT(nSearchSize);
	
	for (i = nSearchSize; i > 0; i--) 
	{
		x = sx + (ex - sx) * i / nSearchSize;
		y = sy + (ey - sy) * i / nSearchSize;
		
		if ((x + y) % 2 != 0) y++;	//º¸Á¤

		if(m_pOrgMap[x][y].m_bMove == 0 && m_pOrgMap[x][y].m_lUser == 0) 
		{
			ex = x;
			ey = y;
			bSearchDest = TRUE;
			break;
		}
	}

	if (!bSearchDest) return FALSE;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
//	NPC¿Í Target °úÀÇ °Å¸®°¡ ÁöÁ¤ ¹üÀ§º¸´Ù ÀÛÀºÁö ÆÇ´Ü
//
BOOL CNpc::IsCloseTarget(COM* pCom, int nRange)
{
	// È¤½Ã³ª °æºñº´ÀÌ NPC¸¦ °ø°ÝÇÏ°Ô µÇ¸é Å¸°ÙÀÌ À¯Àú°¡ ¾Æ´Ï¶ó NPCÀÏ ¼ö µµ ÀÖ´Ù.
	USER* pUser = GetUser(pCom, m_Target.id - USER_BAND);
	if(pUser == NULL) 
	{
		InitTarget();
		return FALSE;
	}
	if(pUser->m_sHP <= 0 || pUser->m_state != STATE_GAMESTARTED || pUser->m_bLive == FALSE)
	{
		InitTarget();
		return FALSE;
	}

	CPoint ptUser	= ConvertToClient(pUser->m_curx, pUser->m_cury);
	CPoint ptNpc	= ConvertToClient(m_sCurX, m_sCurY);

	//^^ ¼Ò¸¶¿¡¼­´Â °Å¸®°Ë»öÀÌ ¾Æ´Ï¶ó ¸Ê °Ë»öÀ¸·Î °Å¸®°è»ê ¹× Àß¸øµÈ À¯Àú ÁÂÇ¥¸¦ Ã¼Å©ÇÏ°í ÀÖÀ½
	int dx = abs(ptUser.x - ptNpc.x);
	int dy = abs(ptUser.y - ptNpc.y);
	int max_dist = __max(dx, dy);
	
	if(max_dist > nRange * 2) return FALSE; // Å¬¶óÀÎÆ® ÁÂÇ¥´Â 2Â÷ÀÌ°¡ ÇÑ¼¿ÀÌ¹Ç·Î *2¸¦ ÇÑ´Ù.

	m_Target.x = pUser->m_curx;
	m_Target.y = pUser->m_cury;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
//	NPC¿Í Target °úÀÇ °Å¸®°¡ ÁöÁ¤ ¹üÀ§º¸´Ù ÀÛÀºÁö ÆÇ´Ü
//
BOOL CNpc::IsCloseTarget(USER *pUser, int nRange)
{
	if(pUser == NULL)
	{
		return FALSE;
	}
	if(pUser->m_sHP <= 0 || pUser->m_state != STATE_GAMESTARTED || pUser->m_bLive == FALSE)
	{
		return FALSE;
	}

	CPoint ptUser	= ConvertToClient(pUser->m_curx, pUser->m_cury);
	CPoint ptNpc	= ConvertToClient(m_sCurX, m_sCurY);

	//^^ ¼Ò¸¶¿¡¼­´Â °Å¸®°Ë»öÀÌ ¾Æ´Ï¶ó ¸Ê °Ë»öÀ¸·Î °Å¸®°è»ê ¹× Àß¸øµÈ À¯Àú ÁÂÇ¥¸¦ Ã¼Å©ÇÏ°í ÀÖÀ½
	int dx = abs(pUser->m_curx - m_sCurX);
	int dy = abs(pUser->m_cury - m_sCurY);
	int max_dist = __max(dx, dy);
	
	if(max_dist > nRange * 2) return FALSE;

	InitTarget();
	m_Target.id = pUser->m_uid + USER_BAND;
	m_Target.x = pUser->m_curx;
	m_Target.y = pUser->m_cury;

/*	if(pUser->m_strUserID != NULL)
	{
		m_Target.nLen = strlen(pUser->m_strUserID);

		if(m_Target.nLen <= CHAR_NAME_LENGTH) strncpy(m_Target.szName, pUser->m_strUserID, m_Target.nLen);
		else								  ::ZeroMemory(m_Target.szName, sizeof(m_Target.szName));
	}
*/	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//	Path Find ·Î Ã£Àº±æÀ» ´Ù ÀÌµ¿ Çß´ÂÁö ÆÇ´Ü
//
BOOL CNpc::IsMovingEnd()
{
	if( m_bRandMove )		// 8¹æÇâ ¼±ÅÃ ¿òÁ÷ÀÓÀÏ¶§
	{
		if( m_arRandMove.GetSize() ) return FALSE;

		return TRUE;
	}

	if(!m_pPath) return TRUE;

	int min_x = m_min_x;
	int min_y = m_min_y;

	if((m_sCurX - min_x) == m_vEndPoint.x && (m_sCurY - min_y) == m_vEndPoint.y) return TRUE;

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////
//	ÇØ´ç uidÀÇ USER* ¸¦ ¾ò´Â´Ù.
//
USER* CNpc::GetUser(COM* pCom, int uid)
{
	if(!pCom) return NULL;
	//if(uid < 0 || uid >= MAX_USER) return NULL;

	return pCom->GetUserUid(uid);
}

/////////////////////////////////////////////////////////////////////////////////
//	Target ÀÇ À§Ä¡°¡ ´Ù½Ã ±æÃ£±â¸¦ ÇÒ Á¤µµ·Î º¯Çß´ÂÁö ÆÇ´Ü
//	È¥¶õµîÀÇ »óÅÂÀÌ»ó »çÀÌ¿À´ÐÀÌ³ª ½ºÅ³µîÀÌ Áö¿øµÇ¸é ÀÌ ÇÔ¼ö¸¦ ÀÌ¿ëÇÏ¸é µÉ µí
//
BOOL CNpc::IsChangePath(COM* pCom, int nStep)
{
	if(!m_pPath) return TRUE;

	CPoint pt;
	GetTargetPos(pCom, pt);
	NODE* pTemp = m_pPath;

	CPoint ptPath[2];
	while(1)
	{
		if(pTemp == NULL) break;

		if(pTemp->Parent) 
		{
			ptPath[0].x = m_min_x + pTemp->x;
			ptPath[0].y = m_min_y + pTemp->y;

			pTemp = pTemp->Parent;			
		}
		else
		{			
			ptPath[1].x = m_min_x + pTemp->x;
			ptPath[1].y = m_min_y + pTemp->y;

			break;
		}
	}

	for(int i = 0; i < 2; i++)
	{
		if(abs(ptPath[i].x - pt.x) <= m_byRange && abs(ptPath[i].y - pt.y) <= m_byRange) return FALSE;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////
//	Target ÀÇ ÇöÀç À§Ä¡¸¦ ¾ò´Â´Ù.
//
BOOL CNpc::GetTargetPos(COM *pCom, CPoint &pt)
{
	USER* pUser = GetUser(pCom, m_Target.id - USER_BAND);

	if(!pUser) return FALSE;

	pt.x = pUser->m_curx;
	pt.y = pUser->m_cury;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////
//	Target °ú NPC °£¿¡ ±æÃ£±â¸¦ ´Ù½ÃÇÑ´Ù.
//
BOOL CNpc::ResetPath(COM* pCom)
{
	CPoint pt;
	GetTargetPos(pCom, pt);

	m_Target.x = pt.x;
	m_Target.y = pt.y;

	return GetTargetPath(pCom);
}

/////////////////////////////////////////////////////////////////////////////////
//	Step ¼ö ¸¸Å­ Å¸ÄÏÀ» ÇâÇØ ÀÌµ¿ÇÑ´Ù.
//
BOOL CNpc::StepMove(COM* pCom, int nStep)
{
//	if(m_tNpcType == NPCTYPE_GUILD_DOOR)	return FALSE;	// ÀÌµ¿¾ÈÇÏ°Ô...

	if(!m_pPath && !m_bRandMove) return FALSE;
	if(m_NpcState != NPC_MOVING && m_NpcState != NPC_TRACING && m_NpcState != NPC_BACK) return FALSE;
	
	int min_x;
	int min_y;
	int will_x;
	int will_y;

	CPoint ptPre;

	MAP* pMap = g_zone[m_ZoneIndex];
	if( !pMap ) return FALSE;
	if( !pMap->m_pMap ) return FALSE;

	for(int i = 0; i < nStep; i++)
	{
		if( m_bRandMove )
		{
			if( !m_arRandMove.GetSize() ) return FALSE;

			min_x = m_min_x;
			min_y = m_min_y;

			will_x = min_x + m_arRandMove[0].x;
			will_y = min_y + m_arRandMove[0].y;

			m_arRandMove.RemoveAt( 0 );

			if( will_x >= pMap->m_sizeMap.cx || will_x < 0 || will_y >= pMap->m_sizeMap.cy || will_y < 0 )
			{
				m_vEndPoint.x = m_sCurX - min_x;
				m_vEndPoint.y = m_sCurY - min_y;

				return FALSE;
			}

			if( pMap->m_pMap[will_x][will_y].m_bMove != 0 || pMap->m_pMap[will_x][will_y].m_lUser != 0 )
			{
				m_vEndPoint.x = m_sCurX - min_x;
				m_vEndPoint.y = m_sCurY - min_y;

				return FALSE;
			}

			ptPre.x = m_sCurX;
			ptPre.y = m_sCurY;

			m_sCurX = will_x;
			m_sCurY = will_y;

			// ½Ã¾ß Àç°è»ê...
			SightRecalc( pCom );

			break;
		}
		else if(m_pPath->Parent)
		{
			m_pPath = m_pPath->Parent;

			min_x = m_min_x;
			min_y = m_min_y;

			will_x = min_x + m_pPath->x;
			will_y = min_y + m_pPath->y;

			if(will_x >= pMap->m_sizeMap.cx || will_x < 0 || will_y >= pMap->m_sizeMap.cy || will_y < 0) 
			{
				m_vEndPoint.x = m_sCurX - min_x;
				m_vEndPoint.y = m_sCurY - min_y;
				return FALSE;
			}
			
			if(pMap->m_pMap[will_x][will_y].m_bMove != 0 || pMap->m_pMap[will_x][will_y].m_lUser != 0)
			{
				m_vEndPoint.x = m_sCurX - min_x;
				m_vEndPoint.y = m_sCurY - min_y;
				return FALSE;
			}

			ptPre.x = m_sCurX;
			ptPre.y = m_sCurY;

			m_sCurX = will_x;
			m_sCurY = will_y;

			//½Ã¾ß Àç°è»ê...
			SightRecalc(pCom);

			break;
		}
		
		return FALSE;
	}

	if(SetUid(m_sCurX, m_sCurY, m_sNid + NPC_BAND))
	{
		pMap->m_pMap[ptPre.x][ptPre.y].m_lUser = 0;
		return TRUE;
	}
	else return FALSE;

//	return SetUid(m_sCurX, m_sCurY, m_sNid + NPC_BAND);
}

//////////////////////////////////////////////////////////////////////////////
//	Target ¿¡ ´ëÇÑ °ø°Ý Ã³¸®
//
int CNpc::Attack(COM *pCom)
{
	if(!pCom) return 10000;

	int ret = 0;
	int nStandingTime = m_sStandTime;

	// ÃÑ±â°è¿­ ÀÏ¶§´Â Å¸°Ù°úÀÇ °Å¸®°è»êÀ» ´Þ¸®ÇØ¾ß ÇÑ´Ù.
//	if(m_tNpcType != NPCTYPE_GUARD && m_tNpcType != NPCTYPE_GUILD_GUARD)// °æºñº´ÀÌ ¾Æ´Ï¸é ½Ã¾ß °è»ê
//	{
	if(IsCloseTarget(pCom, m_byRange) == FALSE)// Check Code (´ÜÁö ¹æ¾îÀûÀÎ Ãø¸é¿¡¼­ ³ÖÀº ÄÚµå)
	{
		if(m_tNpcType == NPCTYPE_GUARD || m_tNpcType == NPCTYPE_GUILD_GUARD)
		{
			m_NpcState = NPC_STANDING;
			return 0;
		}
		m_NpcState = NPC_TRACING;			// °ø°ÝÇÏ°í µµ¸Á°¡´Â À¯Àú¸¦ µû¶ó Àâ±âÀ§ÇØ(¹ÝÀÀÀ» Á»´õ ºü¸£°Ô) 
		return 0;							// IsCloseTarget()¿¡ À¯Àú x, y°ªÀ» °»½ÅÇÏ°í Delay = 0À¸·Î ÁÜ
	}
//	}

	short	sTempHP		= 0;
	CNpc*	pNpc		= NULL;	
	USER*	pUser		= NULL;

	CByteArray	arSkillAction1, arSkillAction2;

	int		nHit = 0;
	int		nAvoid = 0;

	BOOL	bIsHit = FALSE;
	BOOL	bIsCritical = FALSE;

	int		nDamage		= 0;
	int		nDefense	= 0;

	int		iRandom = 0;
//	int		iDefenseDex = 0;
//	double	determine	= 0;
	int		determine = 0;
	int		iDexHitRate = 0, iLevelHitRate = 0;

	int nID = m_Target.id;					// Target À» ±¸ÇÑ´Ù.

	// ¸íÁß¿©ºÎ ÆÇ´Ü º¯¼ö ÃÊ±âÈ­
	bIsHit = FALSE;		

	// È¸ÇÇ°ª/¸íÁßÆÇÁ¤/µ¥¹ÌÁö °è»ê -----------------------------------------//
	if(nID >= USER_BAND && nID < NPC_BAND)	// Target ÀÌ User ÀÎ °æ¿ì
	{
		pUser = GetUser(pCom, nID - USER_BAND);
		
		if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED)// User °¡ Invalid ÇÑ °æ¿ì
		{
			InitTarget();
			m_NpcState = NPC_STANDING;
			return nStandingTime;
		}

		if(pUser->m_bLive == USER_DEAD)			// User °¡ ÀÌ¹Ì Á×Àº°æ¿ì
		{
			InitTarget();
			m_NpcState = NPC_STANDING;
			return nStandingTime;
		}

		if(pUser->m_dwNoDamageTime != 0)		// User °¡ ¹«ÀûÅ¸ÀÓ¿¡ ÀÖÀ»°æ¿ì
		{
			InitTarget();
			m_NpcState = NPC_STANDING;
			return nStandingTime;
		}
		
		if(pUser->m_bPShopOpen == TRUE)			// User has personal shop 
		{
			InitTarget();
			m_NpcState = NPC_STANDING;
			return nStandingTime;
		}

/*	À§¿¡¼­ ÀÌ¹Ì Ã¼Å© ÇÔ
		if(pUser->m_state == STATE_DISCONNECTED)
		{
			InitTarget();
			m_NpcState = NPC_STANDING;
			return nStandingTime;
		}
*/
		if(m_tNpcType == NPCTYPE_GUILD_GUARD)	
		{
			if(m_tGuildWar == GUILD_WARRING && pUser->m_dwGuild > 0)
			{
				if(m_pGuardStore) 
				{
					if(pUser->m_dwGuild == m_pGuardStore->m_iGuildSid) return nStandingTime;
				}
				else if(m_pGuardFortress)
				{
					if(pUser->m_dwGuild == m_pGuardFortress->m_iGuildSid) return nStandingTime;
				}
			}
		}
												// Àº´Ð »óÅÂÀÌ¸é °æºñº´À» Á¦¿ÜÇÑ ¸ðµç ¸÷¿¡ ÇØ´ç			
//		if(m_tNpcType != NPCTYPE_GUARD && pUser->m_dwHideTime > 0)
//		{
//			InitTarget();
//			m_NpcState = NPC_MOVING;
//			return nStandingTime;
//		}

		if(pUser->m_tIsOP == 1)
		{
			InitTarget();
			m_NpcState = NPC_MOVING;
			return nStandingTime;
		}

		// È¸ÇÇ°ª °è»ê 
		nAvoid = pUser->GetAvoid();
		
		// ¸íÁß¿©ºÎ ÆÇ´Ü
		iRandom = (int)((double)XdY(1, 1000) / 10 + 0.5); 
		
		iDexHitRate = (int)( 30.0 * ( (double)m_sDEX/(m_sDEX + pUser->m_sMagicDEX) ) + 15.0 );
		iLevelHitRate = (int)( 70.0 * ( (double)m_byClassLevel/(pUser->m_sLevel + m_byClassLevel) ) + 15.0);

		determine = iDexHitRate + iLevelHitRate - (nAvoid+pUser->m_Avoid);
/*
		iDefenseDex = pUser->m_sMagicDEX;
		if(iDefenseDex < 0) iDefenseDex = 0; //¹æ¾î ÄÚµå

		determine = 200 * ((double)m_sDEX / (m_sDEX + iDefenseDex)) * ((double)m_byClassLevel / (m_byClassLevel + pUser->m_sLevel));
		determine = determine - nAvoid;
*/
		if(determine < ATTACK_MIN) determine = ATTACK_MIN;			// ÃÖ¼Ò 20
		else if(determine > ATTACK_MAX) determine = ATTACK_MAX;		// ÃÖ´ë

		if(iRandom < determine)	bIsHit = TRUE;		// ¸íÁß

		// °ø°Ý ¹Ì½º
		if(bIsHit == FALSE)					
		{
			SendAttackMiss(pCom, nID);
			return m_sAttackDelay;;
		}

		// ¸íÁßÀÌ¸é //Damage Ã³¸® ----------------------------------------------------------------//

		nDamage = GetFinalDamage(pUser);	// ÃÖÁ¾ ´ë¹ÌÁö
		nDamage=nDamage-(pUser->m_DynamicMagicItem[5]+pUser->m_DynamicMagicItem[6]);
		if(nDamage < 0) nDamage = 15;
		if(pUser->m_tAbnormalKind == ABNORMAL_BYTE_COLD) nDamage += 10;		// »ó´ëÆíÀÌ ³Ã±â ÀÌ»óÀÌ¸é µ¥¹ÌÁö Ãß°¡
		if(nDamage > 0) pUser->SetDamage(nDamage);

		// ¹æ¾îÃø ³»±¸µµ °¨¼Ò
		pUser->SendDamagedItem(nDamage);

//		if(pUser->m_bLive == USER_DEAD || pUser->m_sHP <= 0)//@@@ ³ªÁß¿¡ °íÄ§
		if(pUser->m_lDeadUsed == 1)
		{
			InitTarget();
			m_NpcState = NPC_STANDING;
			m_Delay = m_sStandTime;

			if(m_NpcVirtualState == NPC_STANDING)
			{
				if(m_sPid == 179) pUser->GetLevelDownExp(FALSE, -1, TRUE,m_strName);//°ø¿ë ¸ó½ºÅÍÀÏ°æ¿ì °æÇèÄ¡ 1%°¨¼Ò
				else				pUser->GetLevelDownExp(FALSE, -1, FALSE,m_strName);// °æÇèÄ¡¿Í ±×¿Ü º¯È­·®¸¦ ¹Ý¿µÇÑ´Ù.
			}
			if(m_tNpcType == NPCTYPE_GUARD) pUser->SendCityRank(1);				// °æºñº´¿¡°Ô Á×À¸¸é PK Ä«¿îÆ® 1 °¨¼Ò
																				// ÇöÀç °æºñº´Àº ³ë¸» °ø°Ý¸¸ ÇÏ¹Ç·Î ÀÌ°÷¿¡¸¸ Ãß°¡ 
																				// Add by JJS 2002.05.24
		}

		//yskang 0.3 SendAttackSuccess(pCom, nID, arSkillAction1, arSkillAction2, pUser->m_sHP, pUser->m_sMagicMaxHP);
		SendAttackSuccess(pCom, nID, bIsCritical, pUser->m_sHP, pUser->m_sMagicMaxHP);//yskang 0.3
	}

	return m_sAttackDelay;
}

CNpc* CNpc::GetNpc(int nid)
{
	CNpc* pNpc = NULL;

	int nSize = g_arNpc.GetSize();

	if(nid < 0 || nid >= nSize) return NULL;

	for( int i = 0; i < g_arNpc.GetSize(); i++)
	{
		pNpc = g_arNpc[i];
		if( !pNpc ) continue;

		if( pNpc->m_sNid == nid )
		{
			return pNpc;
		}
	}
	return NULL;
}
////////////////////////////////////////////////////////////////////////////
//	NPC ÀÇ °ø°Ý·ÂÀ» ¾ò¾î¿Â´Ù.
//
int CNpc::GetAttack()
{
	int X = m_byAX;
	int Y = m_byAZ;

	return XdY(X, Y);
}

////////////////////////////////////////////////////////////////////////////
//	NPC ÀÇ ¹æ¾î·ÂÀ» ¾ò¾î¿Â´Ù.
//
int CNpc::GetDefense()
{
	return m_iDefense;
}

/////////////////////////////////////////////////////////////////////////////
//	Damage °è»ê, ¸¸¾à m_sHP °¡ 0 ÀÌÇÏÀÌ¸é »ç¸ÁÃ³¸®
//
BOOL CNpc::SetDamage(int nDamage)
{
	if(m_NpcState == NPC_DEAD) return TRUE;
	if(m_sHP <= 0) return TRUE;
	if(nDamage <= 0) return TRUE;

	m_sHP -= nDamage;

	if( m_sHP <= 0 )
	{
		m_sHP = 0;
		return FALSE;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
//	NPC »ç¸ÁÃ³¸®
//
void CNpc::Dead()
{
	long lNpcUid = m_sNid + NPC_BAND;
	if(m_pOrgMap[m_sCurX][m_sCurY].m_lUser == lNpcUid)
	{
		::InterlockedExchange(&m_pOrgMap[m_sCurX][m_sCurY].m_lUser, (LONG)0);
	}
	
	m_sHP = 0;
	m_NpcState = NPC_DEAD;
	
	if(m_bSummon)
	{
		m_bSummonDead = TRUE;
		m_bSummon = FALSE;
	}
	
	if(m_NpcVirtualState == NPC_MOVING)	m_NpcVirtualState = NPC_WAIT;
	
	m_Delay = m_sRegenTime;
	m_bFirstLive = FALSE;
}

//////////////////////////////////////////////////////////////////////////////
//	NPC »ç¸ÁÃ³¸®½Ã °æÇèÄ¡ ºÐ¹è¸¦ °è»êÇÑ´Ù.(ÀÏ¹Ý À¯Àú¿Í ¹öµð »ç¿ëÀÚ±¸ºÐ)
//
void CNpc::SendExpToUserList(COM *pCom)
{
	int i;
	int exp = 0;//, eventExp = 0;
	int totalDamage = 0;
	int firstDamage = 0;
	DWORD plusExp = 0;
	int MaxDamage=0;
	USER *KeypUser=NULL;

	if(m_NpcVirtualState == NPC_WAIT) return;		// °¡»ó°ø°£¿¡¼­ °æÇèÄ¡ ¾ø´Ù.
	if(m_tNpcType >= NPCTYPE_GUILD_NPC) return;


	if(InterlockedCompareExchange((long*)&m_lDamage, (long)1, (long)0) == (long)0){
		if(NpcDrop<=0) {
			InterlockedExchange(&m_lDamage, (LONG)0); 
			return;
		}else{
			NpcDrop=NpcDrop-1;
		}

		InterlockedExchange(&m_lDamage, (LONG)0); 
	}
//	if(m_tNpcType == NPCTYPE_GUILD_NPC || m_tNpcType == NPCTYPE_GUILD_DOOR) return;
//	if(m_tNpcType == NPCTYPE_GUILD_GUARD) return;	// ±æµåÀü¿¡¼­ Á×Àº °æºñº´Àº °æÇèÄ¡¸¦ ¾ÈÁØ´Ù.
//	SYSTEMTIME gTime;
//	GetLocalTime(&gTime);	

	USER *pUser = NULL;

	IsUserInSight(pCom);					// ÇöÀç ¼¿¹üÀ§¾È¿¡ ÀÖ´À³Ä?(¸÷À» ±âÁØÀ¸·Î ÇÑ È­¸é : ÇÃ·¡±× ¼ÂÆÃ)

	if(m_DamagedUserList[0].iUid >= 0 && m_DamagedUserList[0].nDamage > 0)	// Ã¹¹øÂ°¿¡ À¯Àú°¡ ÀÖ´Ù¸é 2¹è 
	{
		MaxDamage=firstDamage = m_DamagedUserList[0].nDamage;
		m_DamagedUserList[0].nDamage = m_DamagedUserList[0].nDamage * 2;
		
	}
														
	for(i = 0; i < NPC_HAVE_USER_LIST; i++)				// ÀÏ´Ü ¸®½ºÆ®¸¦ °Ë»öÇÑ´Ù.
	{												
		if(m_DamagedUserList[i].iUid < 0 || m_DamagedUserList[i].nDamage<= 0) continue;		// ¾ÈÀüÄÚµå
		if(m_DamagedUserList[i].bIs == TRUE) pUser = GetUser(pCom, m_DamagedUserList[i].iUid);
		if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) continue;
		KeypUser=pUser;
		if(abs(pUser->m_sLevel-m_byClassLevel) >40)
			 continue;

		totalDamage = m_DamagedUserList[i].nDamage;
		if(MaxDamage<totalDamage){
			MaxDamage=totalDamage;
			KeypUser=pUser;
		}

		if ( (m_sExp / 5) <= 0 ) continue;
	    if ( totalDamage == 0 ) continue;
		if(((m_TotalDamage + firstDamage) /5) <= 0) continue;
		long long t=(long long)(m_sExp / 5) * totalDamage;
		exp =(int)(t/((m_TotalDamage + firstDamage) / 5));

		pUser->m_iCityValue += m_sInclination;
		if(pUser->m_iCityValue > 2000000000) pUser->m_iCityValue = 2000000000;	// ÃÖ´ë°ªÀÌ ¾ø¾î¼­ ÀÓÀÇ·Î Á¤Çß´Ù.
		
		if(pUser->m_iDisplayType != 5 && pUser->m_iDisplayType != 6)
			pUser->GetExpCommon((int)(exp * 1.1));
		else
			pUser->GetExpCommon((int)(exp * 0.8)); //¹«·á »ç¿ëÀÚ´Â °æÇèÄ¡¸¦ ³·Ãá´Ù.
		//---------------------------------------------------------------------------------------------
		

	}
	Dead_User_level=0;
	if(KeypUser!=NULL)
		Dead_User_level=KeypUser->m_sLevel;
	
}

//////////////////////////////////////////////////////////////////////////////
//	ÇöÀç ¸÷À» ±âÁØÀ¸·Î ÇÑ È­¸é ¹üÀ§¾È¿¡ ÀÖ´ÂÁö ÆÇ´Ü
//
void CNpc::IsUserInSight(COM *pCom)
{
	int j;

	USER* pUser = NULL;

	int iSearchRange = m_bySearchRange;						// ÀÓ½Ã·Î Àâ¾Ò´Ù.
	int min_x, min_y, max_x, max_y;

	min_x = m_sCurX - 12;		if( min_x < 0 ) min_x = 0;
	min_y = m_sCurY - 13;		if( min_y < 0 ) min_y = 0;
	max_x = m_sCurX + 12;
	max_y = m_sCurY + 13;

	if(max_x >= g_zone[m_ZoneIndex]->m_sizeMap.cx) max_x = g_zone[m_ZoneIndex]->m_sizeMap.cx - 1;
	if(max_y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) max_y = g_zone[m_ZoneIndex]->m_sizeMap.cy - 1;

	int ix, iy;
	int target_uid;
	int uid;
	int iLen = 0;

	for(j = 0; j < NPC_HAVE_USER_LIST; j++)
	{
		m_DamagedUserList[j].bIs = FALSE;
	}

	for(ix = min_x; ix <= max_x; ix++)
	{
		for(iy = min_y; iy <= max_y; iy++)
		{
			target_uid = m_pOrgMap[ix][iy].m_lUser;

			if( target_uid >= USER_BAND && target_uid < NPC_BAND )
			{
				uid = target_uid - USER_BAND;
				for(j = 0; j < NPC_HAVE_USER_LIST; j++)
				{												// °®°íÀÖ´Â ¸®½ºÆ®»óÀÇ À¯Àú¿Í °°´Ù¸é		
					if(m_DamagedUserList[j].iUid == uid)		// ÃÖÁ¾ ID¸¦ ºñ±³ÇØ¼­ µ¿ÀÏÇÏ¸é	
					{
						pUser = pCom->GetUserUid(uid);		
						if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED || pUser->m_curz != m_sCurZ) continue;
																
						iLen = strlen(pUser->m_strUserID);
						if(iLen <= 0 || iLen > CHAR_NAME_LENGTH) continue;

						if(strcmp(pUser->m_strUserID, m_DamagedUserList[j].strUserID) == 0) 
						{										// ÀÌ¶§¼­¾ß Á¸ÀçÇÑ´Ù´Â Ç¥½Ã¸¦ ÇÑ´Ù.
							m_DamagedUserList[j].bIs = TRUE;
						}
					}
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//	NPC DEAD Packet À» ÀÎ±Ù À¯Àú¿¡°Ô º¸³½´Ù.
//
int CNpc::SendDead(COM *pCom, int type)
{
//	ASSERT(pCom);
	if(!pCom) return 0;
	if(m_NpcState != NPC_DEAD || m_sHP > 0) return 0;

	CBufferEx TempBuf;

	CPoint pt = ConvertToClient(m_sCurX, m_sCurY);

	TempBuf.Add(DEAD);
	TempBuf.Add((short)(m_sNid + NPC_BAND));
	TempBuf.Add((short)pt.x);
	TempBuf.Add((short)pt.y);
		
	SendInsight(pCom, TempBuf, TempBuf.GetLength());
	if(( (type)  &&  (abs(Dead_User_level-m_byClassLevel) <=50) )|| m_sEvent!=0)
		GiveNpcHaveItem(pCom);	// ¾ÆÀÌÅÛ ¶³±¸±â(°æºñº´ÀÌ¸é ¾È¶³¾îÆ®¸²)
	
	return m_sRegenTime;
}

////////////////////////////////////////////////////////////////////////////////
//	ÁÖº¯¿¡ ÀûÀÌ ¾ø°Å³ª ¼öµ¿¸÷ÀÇ °æ¿ì ÀÓÀÇÀÇ Á¡À¸·Î ±æÃ£±â¸¦ ÇÑ ÈÄ ¿òÁ÷ÀÎ´Ù.
//
BOOL CNpc::RandomMove(COM *pCom)
{
	if(m_bySearchRange == 0) return FALSE;
	if(pCom == NULL) return FALSE;

	if(m_tNpcType == NPCTYPE_GUILD_DOOR)	return FALSE;	// ÀÌµ¿¾ÈÇÏ°Ô...
	if(m_tNpcType == NPCTYPE_GUARD || m_tNpcType == NPCTYPE_GUILD_GUARD)	return FALSE;	// ÀÌµ¿¾ÈÇÏ°Ô...
	// NPC °¡ ÃÊ±â À§Ä¡¸¦ ¹þ¾î³µ´ÂÁö ÆÇ´ÜÇÑ´Ù.
	BOOL bIsIn = IsInRange();

	MAP* pMap = g_zone[m_ZoneIndex];
	if( !pMap ) return FALSE;
	if( !pMap->m_pMap ) return FALSE;

	CPoint pt;
	int nLoop = 0;
	int nDestX = -1, nDestY = -1;
	int min_x, min_y, max_x, max_y;
	int temp_minx = 0, temp_miny = 0, temp_maxx = 0, temp_maxy = 0;

	CRect rectIn;

	if(bIsIn)	// NPC °¡ ÃÊ±â À§Ä¡¸¦ ¹þ¾î³ªÁö ¾Ê¾ÒÀ¸¸é
	{
/*alisia
		int temp_range = m_bySearchRange / 2;

		min_x = m_sCurX - temp_range;	if(min_x < 0) min_x = 0;
		min_y = m_sCurY - temp_range;	if(min_y < 0) min_y = 0;
		max_x = m_sCurX + temp_range;	if(max_x >= g_zone[m_ZoneIndex]->m_sizeMap.cx) max_x = g_zone[m_ZoneIndex]->m_sizeMap.cx - 1;
		max_y = m_sCurY + temp_range;	if(max_y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) max_y = g_zone[m_ZoneIndex]->m_sizeMap.cy - 1;

		rectIn.IntersectRect(CRect(m_nInitMinX, m_nInitMinY, m_nInitMaxX, m_nInitMaxY), CRect(min_x, min_y, max_x, max_y));

		nLoop = 0;
		while(1)
		{
			nDestX = myrand(rectIn.left, rectIn.right);
			nDestY = myrand(rectIn.top, rectIn.bottom);

			if(pMap->m_pMap[nDestX][nDestY].m_bMove != 0 || pMap->m_pMap[nDestX][nDestY].m_lUser != 0)
			{
				if(nLoop++ >= 10) 
				{
					TRACE("NOT FIND~~\n");
					return FALSE;
				}
				continue;
			}
			
			break;
		}
alisia*/

		m_bRandMove = TRUE;		// ÇöÀç ¿òÁ÷ÀÓÀÌ 8¹æÇâ ¼±ÅÃ ¿òÁ÷ÀÓÀÎÁö¸¦ ³ªÅ¸³½´Ù - PathFind() ÇÔ¼ö ¾È¿¡¼­ ¸®¼ÂÇÑ´Ù

		m_arRandMove.RemoveAll();

		int axis_x[3];	axis_x[0] = -1;	axis_x[1] = 0;	axis_x[2] = 1;
		int axis_y[3];	axis_y[0] = -1;	axis_y[1] = 0;	axis_y[2] = 1;
		int rand_x, rand_y, rand_d;

		rand_x = myrand( 0, 2 );
		rand_y = myrand( 0, 2 );
		rand_d = myrand( 1, 5 );

		for( int i = 1; i <= rand_d; i++ )
		{
			m_arRandMove.Add( CPoint( axis_x[rand_x] * i, axis_y[rand_y] * i ) );
		}

		m_min_x = m_sCurX;
		m_min_y = m_sCurY;

		return TRUE;
	}
	else		// NPC °¡ ÃÊ±â À§Ä¡¸¦ ¹þ¾î³µÀ¸¸é
	{
		int x = 0, y = 0;
		
		min_x = m_sCurX;
		min_y = m_sCurY;
		max_x = m_sCurX;
		max_y = m_sCurY;

		if(m_nInitMinX < m_sCurX)	{min_x -= m_bySearchRange;	x += 1;} if(min_x < 0) min_x = 0;
		if(m_nInitMinY < m_sCurY)	{min_y -= m_bySearchRange;	y += 1;} if(min_y < 0) min_y = 0;
		if(m_nInitMaxX > m_sCurX)	{max_x += m_bySearchRange;	x += 1;} if(max_x >= g_zone[m_ZoneIndex]->m_sizeMap.cx) max_x = g_zone[m_ZoneIndex]->m_sizeMap.cx - 1;
		if(m_nInitMaxY > m_sCurY)	{max_y += m_bySearchRange;	y += 1;} if(max_y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) max_y = g_zone[m_ZoneIndex]->m_sizeMap.cy - 1;
				
		nLoop = 0;
		while(1)
		{
			nDestX = min_x + (rand() % (m_bySearchRange * x + 1)); 
			if(nDestX > max_x) nDestX = max_x;

			nDestY = min_y + (rand() % (m_bySearchRange * y + 1));
			if(nDestY > max_y) nDestY = max_y;

			if(pMap->m_pMap[nDestX][nDestY].m_bMove != 0 || pMap->m_pMap[nDestX][nDestY].m_lUser != 0)
			{
				if(nLoop++ >= 10) return FALSE;
				continue;
			}
			
			break;
		}
	}

	if(nDestX < 0 || nDestY < 0)
	{
		return FALSE;
	}

	// Run Path Find ---------------------------------------------//
	CPoint start, end;
	start.x = m_sCurX - min_x;
	start.y = m_sCurY - min_y;
	end.x = nDestX - min_x;
	end.y = nDestY - min_y;

	if(start.x < 0 || start.y < 0 || end.x < 0 || end.y < 0)
	{
		return FALSE;
	}

	m_ptDest.x = nDestX;
	m_ptDest.y = nDestY;

	m_min_x = min_x;
	m_min_y = min_y;
	m_max_x = max_x;
	m_max_y = max_y;

	return PathFind(start, end);
}

/////////////////////////////////////////////////////////////////////////////////////
//	NPC °¡ ÃÊ±â »ý¼ºÀ§Ä¡ ¾È¿¡ ÀÖ´ÂÁö °Ë»ç
//
BOOL CNpc::IsInRange()
{
	// NPC °¡ ÃÊ±â À§Ä¡¸¦ ¹þ¾î³µ´ÂÁö ÆÇ´ÜÇÑ´Ù.
//	CRect rect(m_nInitMinX, m_nInitMinY, m_nInitMaxX, m_nInitMaxY);
	
//	return rect.PtInRect(CPoint(m_sCurX, m_sCurY));

	if( m_nInitMinX > m_sCurX || m_nInitMaxX < m_sCurX ) return FALSE;
	if( m_nInitMinY > m_sCurY || m_nInitMaxY < m_sCurY ) return FALSE;

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////
//	½Ã¾ß°¡ º¯°æµÆ´ÂÁö ÆÇ´ÜÇÏ°í º¯°æµÆ´Ù¸é º¯°æ³»¿ëÀ» Å¬¶óÀÌ¾ðÆ®·Î Àü¼ÛÇÑ´Ù.
//
void CNpc::SightRecalc(COM* pCom)
{
	int sx, sy;

	sx = m_sCurX / SIGHT_SIZE_X;
	sy = m_sCurY / SIGHT_SIZE_Y;

	int dir_x = 0;
	int dir_y = 0;

	if( sx == m_presx && sy == m_presy ) return;
	
	if( m_presx == -1 || m_presy == -1 )
	{
		dir_x = 0;
		dir_y = 0;
	}
	else
	{
		if( sx > m_presx && abs(sx-m_presx) == 1 )		dir_x = DIR_H;
		if( sx < m_presx && abs(sx-m_presx) == 1 )		dir_x = DIR_L;
		if( sy > m_presy && abs(sy-m_presy) == 1 )		dir_y = DIR_H;
		if( sy < m_presy && abs(sy-m_presy) == 1 )		dir_y = DIR_L;
		if( abs(sx-m_presx) > 1 )						dir_x = DIR_OUTSIDE;
		if( abs(sy-m_presy) > 1 )						dir_y = DIR_OUTSIDE;
	}

	int prex = m_presx;
	int prey = m_presy;
	m_presx = sx;
	m_presy = sy;

	SendUserInfoBySightChange(dir_x, dir_y, prex, prey, pCom);
}

//////////////////////////////////////////////////////////////////////////////////////////
//	½Ã¾ßº¯°æÀ¸·Î ÀÎÇÑ À¯ÀúÁ¤º¸ Àü¼Û
//
void CNpc::SendUserInfoBySightChange(int dir_x, int dir_y, int prex, int prey, COM *pCom)
{
	int min_x = 0, min_y = 0;
	int max_x = 0, max_y = 0;

	int sx = m_presx;
	int sy = m_presy;

	int modify_index = 0;
	char modify_send[1024];		::ZeroMemory(modify_send, sizeof(modify_send));
	FillNpcInfo(modify_send, modify_index, INFO_MODIFY);

	int delete_index = 0;
	char delete_send[1024];		::ZeroMemory(delete_send, sizeof(delete_send));
	FillNpcInfo(delete_send, delete_index, INFO_DELETE);

	if( prex == -1 || prey == -1 )
	{
		min_x = (sx-1)*SIGHT_SIZE_X;
		max_x = (sx+2)*SIGHT_SIZE_X;
		min_y = (sy-1)*SIGHT_SIZE_Y;
		max_y = (sy+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, modify_send, modify_index, min_x, min_y, max_x, max_y);
		return;
	}
	if( dir_x == DIR_OUTSIDE || dir_y == DIR_OUTSIDE )
	{
		min_x = (prex-1)*SIGHT_SIZE_X;
		max_x = (prex+2)*SIGHT_SIZE_X;
		min_y = (prey-1)*SIGHT_SIZE_Y;
		max_y = (prey+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, delete_send, delete_index, min_x, min_y, max_x, max_y);
		min_x = (sx-1)*SIGHT_SIZE_X;
		max_x = (sx+2)*SIGHT_SIZE_X;
		min_y = (sy-1)*SIGHT_SIZE_Y;
		max_y = (sy+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, modify_send, modify_index, min_x, min_y, max_x, max_y);
		return;
	}
	if( dir_x > 0 )
	{
		min_x = (prex-1)*SIGHT_SIZE_X;
		max_x = (prex)*SIGHT_SIZE_X;
		min_y = (prey-1)*SIGHT_SIZE_Y;
		max_y = (prey+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, delete_send, delete_index, min_x, min_y, max_x, max_y);
		min_x = (sx+1)*SIGHT_SIZE_X;
		max_x = (sx+2)*SIGHT_SIZE_X;
		min_y = (sy-1)*SIGHT_SIZE_Y;
		max_y = (sy+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, modify_send, modify_index, min_x, min_y, max_x, max_y);
	}
	if( dir_y > 0 )
	{
		min_x = (prex-1)*SIGHT_SIZE_X;
		max_x = (prex+2)*SIGHT_SIZE_X;
		min_y = (prey-1)*SIGHT_SIZE_Y;
		max_y = (prey)*SIGHT_SIZE_Y;
		SendToRange(pCom, delete_send, delete_index, min_x, min_y, max_x, max_y);
		min_x = (sx-1)*SIGHT_SIZE_X;
		max_x = (sx+2)*SIGHT_SIZE_X;
		min_y = (sy+1)*SIGHT_SIZE_Y;
		max_y = (sy+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, modify_send, modify_index, min_x, min_y, max_x, max_y);
	}
	if( dir_x < 0 )
	{
		min_x = (prex+1)*SIGHT_SIZE_X;
		max_x = (prex+2)*SIGHT_SIZE_X;
		min_y = (prey-1)*SIGHT_SIZE_Y;
		max_y = (prey+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, delete_send, delete_index, min_x, min_y, max_x, max_y);
		min_x = (sx-1)*SIGHT_SIZE_X;
		max_x = (sx)*SIGHT_SIZE_X;
		min_y = (sy-1)*SIGHT_SIZE_Y;
		max_y = (sy+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, modify_send, modify_index, min_x, min_y, max_x, max_y);
	}
	if( dir_y < 0 )
	{
		min_x = (prex-1)*SIGHT_SIZE_X;
		max_x = (prex+2)*SIGHT_SIZE_X;
		min_y = (prey+1)*SIGHT_SIZE_Y;
		max_y = (prey+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, delete_send, delete_index, min_x, min_y, max_x, max_y);
		min_x = (sx-1)*SIGHT_SIZE_X;
		max_x = (sx+2)*SIGHT_SIZE_X;
		min_y = (sy-1)*SIGHT_SIZE_Y;
		max_y = (sy)*SIGHT_SIZE_Y;
		SendToRange(pCom, modify_send, modify_index, min_x, min_y, max_x, max_y);
	}
}

////////////////////////////////////////////////////////////////////////////////
//	ÇÑÈ­¸é³»ÀÇ À¯Àú¿¡°Ô¸¸ Á¤º¸Àü¼Û
//
void CNpc::SendExactScreen(COM* pCom, TCHAR *pBuf, int nLength)
{
	if(nLength <= 0 || nLength >= SEND_BUF_SIZE) return;
	
	SEND_DATA* pNewData = NULL;
	pNewData = new SEND_DATA;
	if(pNewData == NULL) return;

	pNewData->flag = SEND_SCREEN;
	pNewData->len = nLength;

	::CopyMemory(pNewData->pBuf, pBuf, nLength);

	pNewData->uid = 0;
	pNewData->x = m_sCurX;
	pNewData->y = m_sCurY;
	pNewData->z = m_sCurZ;
	pNewData->zone_index = m_ZoneIndex;

	pCom->Send(pNewData);
	if(pNewData) delete pNewData;
}

///////////////////////////////////////////////////////////////////////////////
//	½Ã¾ß¾È¿¡ ÀÖ´Â À¯Àú¿¡°Ô µ¥ÀÌÅÍ Àü¼Û
//
void CNpc::SendInsight(COM* pCom, TCHAR *pBuf, int nLength)
{
/*
	if(nLength <= 0 || nLength >= SEND_BUF_SIZE) return;
	
	SEND_DATA* pNewData = NULL;
	pNewData = new SEND_DATA;
	if(pNewData == NULL) return;

	pNewData->flag = SEND_INSIGHT;
	pNewData->len = nLength;

	::CopyMemory(pNewData->pBuf, pBuf, nLength);

	pNewData->uid = 0;
	pNewData->x = m_sCurX;
	pNewData->y = m_sCurY;
	pNewData->z = m_sCurZ;
	pNewData->zone_index = m_ZoneIndex;

	EnterCriticalSection( &(pCom->m_critSendData) );
	pCom->m_arSendData.Add( pNewData );
	LeaveCriticalSection( &(pCom->m_critSendData) );

	PostQueuedCompletionStatus( pCom->m_hSendIOCP, 0, 0, NULL );
*/
	if(nLength <= 0 || nLength >= SEND_BUF_SIZE) return;

	int sx = m_sCurX / SIGHT_SIZE_X;
	int sy = m_sCurY / SIGHT_SIZE_Y;
	
	int min_x = (sx-1)*SIGHT_SIZE_X; if( min_x < 0 ) min_x = 0;
	int max_x = (sx+2)*SIGHT_SIZE_X;
	int min_y = (sy-1)*SIGHT_SIZE_Y; if( min_y < 0 ) min_y = 0;
	int max_y = (sy+2)*SIGHT_SIZE_Y;
	
	MAP* pMap = g_zone[m_ZoneIndex];
	if( !pMap ) return;
	
	if( max_x >= pMap->m_sizeMap.cx ) max_x = pMap->m_sizeMap.cx - 1;
	if( max_y >= pMap->m_sizeMap.cy ) max_y = pMap->m_sizeMap.cy - 1;
	
	int temp_uid;
	USER* pUser = NULL;

	for( int i = min_x; i < max_x; i++ )
	{
		for( int j = min_y; j < max_y; j++ )
		{				
			temp_uid = pMap->m_pMap[i][j].m_lUser;

			if(temp_uid < USER_BAND || temp_uid >= NPC_BAND) continue;
			else temp_uid -= USER_BAND;
			
			if( temp_uid >= 0 && temp_uid < MAX_USER )
			{
				pUser = pCom->GetUserUid(temp_uid);
				if ( pUser == NULL ) continue;
				
				if( pUser->m_state == STATE_GAMESTARTED )
				{
					if( pUser->m_curx == i && pUser->m_cury == j && pUser->m_curz == m_sCurZ )
					{
						Send( pUser, pBuf, nLength );
					}
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
//	ÇöÀç NPC ÀÇ À§Ä¡¿Í (xpos, ypos) »çÀÌÀÇ °Å¸®¸¦ °è»ê
//
BOOL CNpc::GetDistance(int xpos, int ypos, int dist)
{
	if(xpos >= g_zone[m_ZoneIndex]->m_sizeMap.cx || xpos < 0 || ypos >= g_zone[m_ZoneIndex]->m_sizeMap.cy || ypos < 0) return FALSE;

	int dx = abs(xpos - m_sCurX);
	int dy = abs(ypos - m_sCurY);

	if(dx + dy > dist * 2) return FALSE;
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////////
//	NPC °¡ °¡Áø ¾ÆÀÌÅÛÀ» ¶³±º´Ù.
//
void CNpc::GiveNpcHaveItem(COM *pCom)
{
	int temp = 0;
	int iPer = 0, iVal = 0;
	int iRandom;
	int nCount = 1;
	int nDnHap = 0;

//	SYSTEMTIME gTime;
//	GetLocalTime(&gTime);	

	if(m_NpcVirtualState == NPC_WAIT) return;

/*	if(gTime.wDay > 7 && gTime.wDay < 14)					// 8ÀÏºÎÅÍ 13ÀÏ±îÁö	
	{
		if(m_byClassLevel <= 20)		nCount = 1;
		else if(m_byClassLevel <= 50)	nCount = 2;
		else if(m_byClassLevel <= 70)	nCount = 3;
		else							nCount = 5;
	}
	else
	{
*/
	if(m_byClassLevel <= 50)		nCount = 2;
	else							nCount = 2;

	if(m_sEvent== 32000) nCount = 4;
	if( m_sEvent == NPC_EVENT_MOP )				nCount = 8;		// ÀÌº¥Æ® ¸÷ÀÏ°æ¿ì ¾ÆÀÌÅÛ ¶³¾îÁú È½¼ö¸¦ ´Ã¸°´Ù.
	if( m_sEvent == NPC_EVENT_GREATE_MOP )		nCount = 16;	// ¿¢½º¸®¿Â µî Æ¯¼ö ¸ó½ºÅÍÀÏ °æ¿ì 10°³¸¦ ¶³¾î¶ß¸°´Ù.
//	}
/*
	for(int i = 0; i < nCount; i++)
	{
		iRandom = myrand(1, 30);

		if(iRandom < m_tItemPer)
		{

			iRandom = myrand(1, 10000);
			for(int i = 2; i < g_NpcItem.m_nField; i += 2)
			{			
//				iPer = g_NpcItem.m_ppItem[i][m_byClassLevel];
				iPer = g_NpcItem.m_ppItem[i][m_sHaveItem];
				if(iPer == 0) return;
				if(iRandom < iPer)
				{											// ¿ì¼± ±âº»Å×ÀÌºí¸¦ ÂüÁ¶ÇÏ±âÀ§ÇØ	
//					temp = g_NpcItem.m_ppItem[i-1][m_byClassLevel];
					temp = g_NpcItem.m_ppItem[i-1][m_sHaveItem];
					iVal = temp;
					if(temp >= g_arItemTable.GetSize()) return;

					if(g_arItemTable[temp]->m_byWear <= 5 || g_arItemTable[temp]->m_byWear == 117 || g_arItemTable[temp]->m_byWear == 20)	// º¯ÇüÅ×ÀÌºíÀÌ´Ù.
					{
						iVal = IsTransformedItem(g_arItemTable[temp]->m_sSid);
						if(iVal == -1) iVal = temp;//return;
					}
					if (iVal == 845 || iVal == 909 || iVal == 846 || iVal == 907 || iVal == 908) iVal = 847;
					GiveItemToMap(pCom, iVal, TRUE);
					break;
				}
			}

		}

		else if(iRandom < m_tDnPer)
		{
//			SYSTEMTIME gTime;										//@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Event Code ±â°£µ¿¾È ÀÏ½ÃÀûÀ¸·Î ´Ã·ÁÁØ´Ù.
//			GetLocalTime(&gTime);

			iPer = g_arDNTable[m_byClassLevel]->m_sMinDn;
			iVal = g_arDNTable[m_byClassLevel]->m_sMaxDn;
			iRandom = myrand(iPer, iVal);
																	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Event Code ±â°£µ¿¾È ÀÏ½ÃÀûÀ¸·Î ´Ã·ÁÁØ´Ù.	

			nDnHap += iRandom;
			//GiveItemToMap(pCom, iRandom, FALSE);
		}
	}
	if(nDnHap > 0 )
	{
      if (nDnHap == 845 || nDnHap == 909 || nDnHap == 846 || nDnHap == 907 || nDnHap == 908) nDnHap = 847;
		GiveItemToMap(pCom, nDnHap, FALSE);
	}
	*/
	int tItemHavePer;
	if(m_sPid>255)
		return;
	int tItemPer=g_DropItem[m_sPid][m_byColor].DropNovelity;
	int tLeechdomPer = g_DropItem[m_sPid][m_byColor].DropLeechdom+tItemPer;
	int tItemN=g_DropItem[m_sPid][m_byColor].n;
	int i;
	//TRACE("ÊýÁ¿ %d\n",nCount);
	for(i = 0; i < nCount; i++)
	{
		//TRACE( "i=%d\n",i);
		iRandom = myrand(1, 100);
		//TRACE("Ëæ»úÊý %d\n",iRandom);
		if(iRandom < tItemPer)
		{
			//TRACE( "ÎïÆ·--\n");
			iRandom = myrand(1, 10000)%tItemN;
			tItemHavePer = g_DropItem[m_sPid][m_byColor].novelity[iRandom].per;
			temp = iVal = g_DropItem[m_sPid][m_byColor].novelity[iRandom].code1+g_DropItem[m_sPid][m_byColor].novelity[iRandom].code2*256;
			if(iVal >= g_arItemTable.GetSize()){
				return;
			}
			iRandom = myrand(1, 1000);
			if(iRandom < tItemHavePer){	
				if(g_arItemTable[temp]->m_byWear <= 5 || g_arItemTable[temp]->m_byWear == 117 || g_arItemTable[temp]->m_byWear == 20)	// º¯ÇüÅ×ÀÌºíÀÌ´Ù.
				{
					iVal = IsTransformedItem(g_arItemTable[temp]->m_sSid);
					if(iVal == -1) iVal = temp;
				}
			//	TRACE( "ÎïÆ·´úÂë %s,%d\n",g_arItemTable[iVal]->m_strName,iVal);
				GiveItemToMap(pCom, iVal, TRUE);
				
				//break;
			}
		}
		else if(iRandom < tLeechdomPer)//µôÀ¶Ò©
		{
			//TRACE( "À¶Ò©--\n");
			if(m_byClassLevel <30)
				iVal=31;
			else if(m_byClassLevel <70)
				iVal=32;
			else if(m_byClassLevel <120)
				iVal=33;
			else
				iVal=227+256*3;
			GiveItemToMap(pCom, iVal, TRUE);
		}else{
			//TRACE( "Ç®--\n");
			int money= g_DropItem[m_sPid][m_byColor].money;
			iRandom =money+(money *myrand(0,15)%15);//15%¸¡¶¯
			nDnHap += iRandom;
		}
		//TRACE( "i=%d\n",i);
	}
	//TRACE( "i=%d----------------------------------------\n",i);
	if(nDnHap > 0 )
	{
		if (nDnHap == 845 || nDnHap == 909 || nDnHap == 846 || nDnHap == 907 || nDnHap == 908) nDnHap = 847;
		GiveItemToMap(pCom, nDnHap, FALSE);
	}
}

///////////////////////////////////////////////////////////////////////////////////
//	¾ÆÀÌÅÛÁß º¯Çü¾ÆÀÌÅÛÀÌ ÀÖ´ÂÁö ÆÇ´ÜÇÑ´Ù.
//
int CNpc::IsTransformedItem(int sid)
{
	int iVal = 0;
	int i, j, iRandom;

	for(i = 0; i < g_ValItem.m_nRow; i++)
	{
		if(g_ValItem.m_ppItem[g_ValItem.m_nField-2][i] == sid)		// ¸Ç ¸¶Áö¸· ÇÊµå¿¡¼­ ¾ÆÀÌÅÛ Ç×¸ñ(6°³ Á¾·ù)
		{
			iRandom = myrand(1, 100);
			for(j = 2; j < g_ValItem.m_nField; j+= 2)
			{
				iVal = g_ValItem.m_ppItem[j][i];
				if(iRandom < iVal)
				{
					if(sid >= g_arItemTable.GetSize()) return -1;
					else return g_ValItem.m_ppItem[j-1][i];
				}
			}
		}
	}

	return -1;
}

///////////////////////////////////////////////////////////////////////////////////
//	¾ÆÀÌÅÛÁß ¸ÅÁ÷ ¾ÆÀÌÅÛÀ» ¶³¾îµå¸±¼öÀÖ´ÂÁö ÆÇ´Ü
//
int CNpc::IsMagicItem(COM* pCom, ItemList *pItem, int iTable)
{
	int i = 0, j;
	int iMagicTemp = 1 , iRareTemp = 1;
	int iRandom = myrand( 1, 10000 );

	int iMagicCount = 0, iCount = 0;
	int nLoop = 0, iType = 0;
	int nEventMoon = 0;
	int nEventSongpeon = 0;
	int nEventBox = 0;
	int iMagicUp=0;

	USER* pUser = NULL;

/*	SYSTEMTIME gTime;										//@@@@@@@@@@@@@@@ Event Code ±â°£µ¿¾È ÀÏ½ÃÀûÀ¸·Î ´Ã·ÁÁØ´Ù.
	GetLocalTime(&gTime);
	if(gTime.wMonth < 7) { iMagicTemp = 10; iRareTemp = 2; }
	else if(gTime.wMonth == 7) 
	{ 
		if(gTime.wDay <= 7) { iMagicTemp = 10; iRareTemp = 2; } 
	}
	*/
	if(m_sEvent== 32000){
		iMagicTemp=0;
		iRareTemp = 3; 
	}else if(m_sEvent == NPC_EVENT_MOP)				// ÇöÀç ºòÇ²,Äý,½ºÄÝÇÇ¿À
	{
		iMagicTemp = 0; 
		iRareTemp = 4; 
	}
	else if(m_sEvent == NPC_EVENT_GREATE_MOP)	// ¿¢½º¸®¿Â
	{
		iMagicTemp = 0;  //70
		iRareTemp = 8;    //75
	}

	if(m_lKillUid >= 0)
	{
		pUser = GetUser(pCom, m_lKillUid);
		if(pUser != NULL && pUser->m_state == STATE_GAMESTARTED)
		{
			if(pUser->m_dwMagicFindTime != 0)	// ¸ÅÁ÷ ÆÄÀÎ´õ¸¦ ¸ÔÀº »óÅÂÀÌ¸é
			{
					iMagicTemp=0;
					iMagicUp=10000;
			}
		}
	}

	nEventMoon		= NPC_RARE_ITEM * iRareTemp + (NPC_EVENT_MOON - NPC_RARE_ITEM);
	nEventSongpeon	= nEventMoon + (NPC_EVENT_SONGPEON - NPC_EVENT_MOON);
	nEventBox		= nEventSongpeon + (NPC_EVENT_BOX - NPC_EVENT_SONGPEON);

    if(iRandom <= NPC_MAGIC_ITEM * iMagicTemp)	// ¸ÅÁ÷
	{
		nLoop = 2;
		iType = MAGIC_ITEM;
	}
	else if((iRandom > NPC_MAGIC_ITEM * iMagicTemp) && (iRandom <=( NPC_RARE_ITEM * iRareTemp+iMagicUp)))	// ·¹¾î 
	{ 
		nLoop = 4;
		iType = RARE_ITEM; 
	}	
	else if(0 && iRandom > NPC_RARE_ITEM * iRareTemp && iRandom <= nEventMoon)
	{
		return EVENT_ITEM_MOON;
	}
	else if(0 && iRandom > nEventMoon && iRandom <= nEventSongpeon)
	{
		return EVENT_ITEM_SONGPEON;
	}
	else if(0 && iRandom > nEventSongpeon && iRandom <= nEventBox)
	{
		return EVENT_ITEM_BOX;
	}
	else return NORMAL_ITEM;								// ÀÏ¹Ý¾ÆÀÌÅÛ

	int iTemp = 0;

	if(m_ItemUserLevel <= 20)       iMagicCount = 42;		// ¸ÅÁ÷ÀÎµ¦½º ¹üÀ§¸¦ ·¹º§¿¡ µû¶ó Á¦ÇÑÇÑ´Ù. 
	else if(m_ItemUserLevel <= 40)  iMagicCount = 106;
	else if(m_ItemUserLevel <= 60)  iMagicCount = 143;
	else							iMagicCount = 166;

	

	if(iMagicCount >= g_arMagicItemTable.GetSize()) iMagicCount = g_arMagicItemTable.GetSize() - 1;

	while(nLoop > i)										// ¹«Á¶°Ç 4°³¼Ó¼º°ªÀ» ±¸ÇÑ´Ù.
	{
		
		iRandom = myrand(0, iMagicCount);
		//------------------------------------------------------------------------------------------------
		//yskang 0.6 À¯·á»ç¿ëÀÚ¿¡°Ô ÇÁ¸®¹Ì¾ö ÁÁÀº ¿É¼ÇÀÇ ¾ÆÀÌÅÛÀÌ ¶³¾îÁø´Ù.
		if(pUser != NULL)
		{
			if(pUser->m_iDisplayType !=5 && pUser->m_iDisplayType !=6)//À¯·á »ç¿ëÀÚÀÌ´Ù.
			{
				if(m_ItemUserLevel <= 20)
					iRandom = myrand(0, iMagicCount); //ÁÁÀº ¾ÆÀÌÅÛÀÌ ¶³¾îÁú È®·üÀ» ³ôÀÎ´Ù.
				else
					iRandom = myrand(41, iMagicCount); 
			}
		}
		//------------------------------------------------------------------------------------------------

		if(!g_arMagicItemTable[iRandom]->m_tUse) continue;

		if(CheckClassItem(iTable, iRandom) == FALSE) 
		{
			if(i == 0) continue;							// ¸ÅÁ÷Àº ±âº»ÀÌ 1°³
			else if(iType == RARE_ITEM && i <= 2) continue;	// ·¡¾î´Â ±âº»ÀÌ 3°³
			else { i++; continue; }
		}

		for(j = 0; j < 4; j++)
		{
			if(iCount != 0 && iCount == g_arMagicItemTable[iRandom]->m_sSubType)	// ¼Ó¼ºÀÌ °ãÄ¥¼ö ÀÖÀ¸¹Ç·Î ÀÌÁß Å«°ª¸¸ ¼±ÅÃ	
			{
				iCount = g_arMagicItemTable[pItem->tMagic[j]]->m_sChangeValue;
				if(iCount < g_arMagicItemTable[iRandom]->m_sChangeValue)
				{
					iTemp = g_arMagicItemTable[pItem->tMagic[j]]->m_tLevel;
					if(pItem->sLevel - iTemp > 0) pItem->sLevel -= iTemp;
					pItem->sLevel += g_arMagicItemTable[iRandom]->m_tLevel;
					pItem->tMagic[j] = iRandom; 

					if(g_arMagicItemTable[pItem->tMagic[j]]->m_sSubType == MAGIC_DURATION_UP)
					{
						iTemp = g_arMagicItemTable[pItem->tMagic[j]]->m_sChangeValue;
						if(pItem->sDuration - iTemp > 0) pItem->sDuration -= iTemp;
						pItem->sDuration += g_arMagicItemTable[iRandom]->m_sChangeValue; // ³»±¸·Â Áõ°¡ ¼Ó¼ºÀº ¼ÂÆÃµÉ¶§ 
					}
					break;
				}
				else if(iCount == g_arMagicItemTable[iRandom]->m_sChangeValue) break;
			}

			if(pItem->tMagic[j] > 0) continue;	// ÀÌ¹Ì ½½·Ô¿¡ °ªÀÌ ÀÖÀ¸¸é ³Ñ¾î°¨
			else
			{ 
				pItem->tMagic[j] = iRandom; i++; 
				if(g_arMagicItemTable[iRandom]->m_tLevel > 0) pItem->sLevel += g_arMagicItemTable[iRandom]->m_tLevel;
				if(g_arMagicItemTable[pItem->tMagic[j]]->m_sSubType == MAGIC_DURATION_UP)
				{
					pItem->sDuration += g_arMagicItemTable[iRandom]->m_sChangeValue; // ³»±¸·Â Áõ°¡ ¼Ó¼ºÀº ¼ÂÆÃµÉ¶§ 
				}
				break; 
			}
		}
//		i++;
	}

	return iType;
}
//Ëæ»úÊØ»¤ÊôÐÔ
void CNpc::shouhu_rand(	ItemList *pMapItem)
{
	int a;

	a=myrand(0,15)%100;
	pMapItem->tIQ=0x09;//ÊØ»¤ÑÕÉ«
	switch (a){
		case 0:pMapItem->tMagic[0]=1; return;//ËðÉË2 3 5
		case 1:pMapItem->tMagic[0]=4; return;//ÎäÆ÷µÈ¼¶Ôö¼Ó1 2 3
		case 2:pMapItem->tMagic[0]=7; return;//½«¶Ô·½ÉúÃü2 5 10×ª»¯³É×Ô¼ºÉúÃü
		case 3:pMapItem->tMagic[0]=10; return;//¶ÔÖÜÎ§Ôì³É2% 5 10ÉËº¦
		case 4:pMapItem->tMagic[0]=13; return;//13 ·ÀÓùÔö¼Ó3 6 10
		case 5:pMapItem->tMagic[0]=16; return;//Ä§·¨·ÀÓùÔö¼Ó3 6 10
		case 6:pMapItem->tMagic[0]=19; return;//½«µÐÈË¶Ô×Ô¼º¹¥»÷ÉËº¦2% 3 5 ·´Éäµ½µÐÈËÉíÉÏ
		case 7:pMapItem->tMagic[0]=22; return;// ´ò¹Ö¾­ÑéÖµÌá¸ß2% 3% 5%
		case 8:pMapItem->tMagic[0]=25; return;//½ð±ÒÌá¸ß10% ½ð±ÒÌá¸ß20% ½ð±ÒÌá¸ß50%
		case 9:pMapItem->tMagic[0]=28; return;// ËùÓÐ¼¼ÄÜÔö¼Ó1  ËùÓÐ¼¼ÄÜÔö¼Ó2  ËùÓÐ¼¼ÄÜÔö¼Ó3
		case 10:pMapItem->tMagic[0]=31; return;//µôÂäÎïÆ·Ìá¸ß2% µôÂäÎïÆ·Ìá¸ß3% µôÂäÎïÆ·Ìá¸ß5%
		case 11:pMapItem->tMagic[0]=34; return;//¹¥»÷Á¦Ôö¼Ó10 ¹¥»÷Á¦Ôö¼Ó20 ¹¥»÷Á¦Ôö¼Ó30
		case 12:pMapItem->tMagic[0]=37; return;//ÎüÈ¡¶Ô·½ÉúÃü10 ÎüÈ¡¶Ô·½ÉúÃü20 ÎüÈ¡¶Ô·½ÉúÃü30
		case 13:pMapItem->tMagic[0]=40; return;//ÉúÃüÔö¼Ó10 ÉúÃüÔö¼Ó20 ÉúÃüÔö¼Ó30
		case 14:pMapItem->tMagic[0]=1; return;//ËðÉË2 3 5
		case 15:pMapItem->tMagic[0]=13; return;//13 ·ÀÓùÔö¼Ó3 6 10
		case 16:pMapItem->tMagic[0]=1; return;//ËðÉË2 3 5
		case 17:pMapItem->tMagic[0]=34; return;//¹¥»÷Á¦Ôö¼Ó10 ¹¥»÷Á¦Ôö¼Ó20 ¹¥»÷Á¦Ôö¼Ó30
		case 18:pMapItem->tMagic[0]=13; return;//13 ·ÀÓùÔö¼Ó3 6 10
		case 19:pMapItem->tMagic[0]=1; return;//ËðÉË2 3 5
		case 20:pMapItem->tMagic[0]=40; return;//ÉúÃüÔö¼Ó10 ÉúÃüÔö¼Ó20 ÉúÃüÔö¼Ó30
		case 21:pMapItem->tMagic[0]=1; return;//ËðÉË2 3 5
		case 22:pMapItem->tMagic[0]=13; return;//13 ·ÀÓùÔö¼Ó3 6 10
		case 23:pMapItem->tMagic[0]=40; return;//ÉúÃüÔö¼Ó10 ÉúÃüÔö¼Ó20 ÉúÃüÔö¼Ó30
		case 24:pMapItem->tMagic[0]=40; return;//ÉúÃüÔö¼Ó10 ÉúÃüÔö¼Ó20 ÉúÃüÔö¼Ó30
		case 25:pMapItem->tMagic[0]=1; return;//ËðÉË2 3 5
		case 26:pMapItem->tMagic[0]=13; return;//13 ·ÀÓùÔö¼Ó3 6 10
		case 27:pMapItem->tMagic[0]=1; return;//ËðÉË2 3 5
		case 28:pMapItem->tMagic[0]=40; return;//ÉúÃüÔö¼Ó10 ÉúÃüÔö¼Ó20 ÉúÃüÔö¼Ó30
		case 29:pMapItem->tMagic[0]=34; return;//¹¥»÷Á¦Ôö¼Ó10 ¹¥»÷Á¦Ôö¼Ó20 ¹¥»÷Á¦Ôö¼Ó30
		case 30:pMapItem->tMagic[0]=1; return;//ËðÉË2 3 5
		default:
			pMapItem->tMagic[0]=0;return;
	}
}

///////////////////////////////////////////////////////////////////////////////////
//	NPC ItemÀ» ¸Ê¿¡ ¶³±º´Ù.
//
void CNpc::GiveItemToMap(COM *pCom, int iItemNum, BOOL bItem, int iEventNum)
{
	int i, iRandom = 0;
	int iType = 0;
	BYTE tEBodySid = 0;

	CPoint pt;
	pt = FindNearRandomPointForItem(m_sCurX, m_sCurY);							// ÇöÀç ÀÚ±âÁÂÇ¥¸¦ Á¦¿ÜÇÑ 24Ä­
	if(pt.x <= -1 || pt.y <= -1) return;
	if(pt.x >= g_zone[m_ZoneIndex]->m_sizeMap.cx || pt.y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) return;

	ItemList *pMapItem = NULL;
	if(InterlockedCompareExchange((long*)&g_zone[m_ZoneIndex]->m_pMap[pt.x][pt.y].m_FieldUse, (long)1, (long)0) == (long)0)
	{
		pMapItem = new ItemList;

		if(!bItem)					// µ·ÀÏ °æ¿ì
		{
			pMapItem->tType = TYPE_MONEY;
			pMapItem->dwMoney = iItemNum;

			pMapItem->uid[0] = m_iHaveItemUid[0].uid;
			pMapItem->uid[1] = m_iHaveItemUid[1].uid;
			pMapItem->uid[2] = m_iHaveItemUid[2].uid;

			pMapItem->SuccessRate[0] = (BYTE)m_iHaveItemUid[0].nDamage;
			pMapItem->SuccessRate[1] = (BYTE)m_iHaveItemUid[1].nDamage;
			pMapItem->SuccessRate[2] = (BYTE)m_iHaveItemUid[2].nDamage;
			pMapItem->dwTime = GetItemThrowTime();
		}
		else							// ¾ÆÀÌÅÛ ¸ñ·ÏÀÏ°æ¿ì
		{
			if(iItemNum >= g_arItemTable.GetSize())
			{
				if(pMapItem) delete pMapItem;
				return; 
			}
			else
			{
				pMapItem->tType = TYPE_ITEM;
				pMapItem->sLevel = g_arItemTable[iItemNum]->m_byRLevel;
				pMapItem->sSid = g_arItemTable[iItemNum]->m_sSid;
				pMapItem->sDuration = g_arItemTable[iItemNum]->m_sDuration;
				pMapItem->sCount = 1;
				pMapItem->sBullNum = g_arItemTable[iItemNum]->m_sBullNum;
				for(i = 0; i < MAGIC_NUM; i++) pMapItem->tMagic[i] = 0;	// ³ªÁß¿¡ Magic Item Ãß°¡ÇÒ °Í
				pMapItem->tIQ = NORMAL_ITEM;
				pMapItem->iItemSerial = 0;

				pMapItem->uid[0] = m_iHaveItemUid[0].uid;				// ¿ì¼± ¼øÀ§
				pMapItem->uid[1] = m_iHaveItemUid[1].uid;
				pMapItem->uid[2] = m_iHaveItemUid[2].uid;

				pMapItem->SuccessRate[0] = (BYTE)m_iHaveItemUid[0].nDamage;	// ¿ì¼± ¼øÀ§ ºñÀ²
				pMapItem->SuccessRate[1] = (BYTE)m_iHaveItemUid[1].nDamage;
				pMapItem->SuccessRate[2] = (BYTE)m_iHaveItemUid[2].nDamage;

				pMapItem->dwTime = GetItemThrowTime();
				//GetLocalTime(&pMapItem->ThrowTime);
			
				int iWear = g_arItemTable[iItemNum]->m_byWear;

				if(iWear >= 1 && iWear <= 5) 
				{
					iType = IsMagicItem(pCom, pMapItem, iItemNum);
					if(iType == MAGIC_ITEM)
					{
						pMapItem->tIQ = MAGIC_ITEM;	// ¸ÅÁ÷¸¸ Ã³¸®...
					}
					else if(iType == RARE_ITEM)
					{
						pMapItem->tIQ = RARE_ITEM;	// ·¡¾î¸¸ Ã³¸®...

// 						int n = pMapItem->tMagic[0] + pMapItem->tMagic[1] + pMapItem->tMagic[2] + pMapItem->tMagic[3];
// 						if(n > 500) {
// 							int iRandom = myrand(1, 100);
// 							//¼«Æ·µôÂä¿ØÖÆ
// 							if(iRandom < 30){
// 								pMapItem->tMagic[0] = 0;
// 							}
// 						}
						
					}
					else if(iType == EVENT_ITEM_MOON)	// º¸¸§´Þ
					{
						iItemNum = EVENTITEM_SID_MOON;
						pMapItem->sLevel = g_arItemTable[iItemNum]->m_byRLevel;
						pMapItem->sSid = g_arItemTable[iItemNum]->m_sSid;
						pMapItem->sDuration = g_arItemTable[iItemNum]->m_sDuration;
						pMapItem->sCount = 1;
						pMapItem->sBullNum = g_arItemTable[iItemNum]->m_sBullNum;
						iWear = g_arItemTable[iItemNum]->m_byWear;
					}
					else if(iType == EVENT_ITEM_SONGPEON)	// ¼ÛÆí ¶Ç´Â ¿ùº´
					{
						/*
						if(m_byClassLevel < 11) iItemNum = EVENTITEM_SID_SONGPEON_01;
						else if(m_byClassLevel >= 11 && m_byClassLevel < 31) iItemNum = EVENTITEM_SID_SONGPEON_11;
						else if(m_byClassLevel >= 31 && m_byClassLevel < 51) iItemNum = EVENTITEM_SID_SONGPEON_31;
						else if(m_byClassLevel >= 51 && m_byClassLevel < 71) iItemNum = EVENTITEM_SID_SONGPEON_51;
						else if(m_byClassLevel >= 71) iItemNum = EVENTITEM_SID_SONGPEON_71;
						*/
						iItemNum = EVENTITEM_SID_SONGPEON_01;
						
						pMapItem->sLevel = g_arItemTable[iItemNum]->m_byRLevel;
						pMapItem->sSid = g_arItemTable[iItemNum]->m_sSid;
						pMapItem->sDuration = g_arItemTable[iItemNum]->m_sDuration;
						pMapItem->sCount = 1;
						pMapItem->sBullNum = g_arItemTable[iItemNum]->m_sBullNum;
						iWear = g_arItemTable[iItemNum]->m_byWear;
					}
					else if(iType == EVENT_ITEM_BOX)	// ¼±¹°»óÀÚ
					{
						iItemNum = EVENTITEM_SID_BOX;
						pMapItem->sLevel = g_arItemTable[iItemNum]->m_byRLevel;
						pMapItem->sSid = g_arItemTable[iItemNum]->m_sSid;
						pMapItem->sDuration = g_arItemTable[iItemNum]->m_sDuration;
						pMapItem->sCount = 1;
						pMapItem->sBullNum = g_arItemTable[iItemNum]->m_sBullNum;
						iWear = g_arItemTable[iItemNum]->m_byWear;
					}
				}
				
				// ¾Ç¼¼»ç¸® Ã³¸®
				else if(iWear >= 6 && iWear <= 8)	// Ê×ÊÎµôÂä
				{
					pMapItem->tIQ = MAGIC_ITEM;	// ¾Ç¼¼»ç¸®´Â ¹«Á¶°Ç ¸ÅÁ÷
					pMapItem->tMagic[0] = g_arItemTable[iItemNum]->m_bySpecial;
				}
				
				// ¿¡ÀÌ´õ Ã³¸®
				else if(iWear == 126) //ºÆÊ¯µôÂä....ºÍÊôÐÔËæ»ú.
				{
					iRandom = myrand(1, 1000);
					for(i = 0; i < g_arEBodyTable.GetSize(); i++)
					{
						if(iRandom <= g_arEBodyTable[i]->m_sRandom) 
						{
							tEBodySid = g_arEBodyTable[i]->m_tSid;
							break;
						}	
					}
					pMapItem->tIQ = MAGIC_ITEM;	//
					pMapItem->tMagic[0] = tEBodySid;
				}else if(iWear==130)
				{
					shouhu_rand(pMapItem);

				}else if(iWear==143){//»ÃÊ¯
					byte tMagic=0;
					iRandom = myrand(1, 6);
					switch(iRandom){
						case 1: tMagic=3;break;
						case 2: tMagic=13;break;
						case 3: tMagic=23;break;
						case 4: tMagic=43;break;
						case 5: tMagic=53;break;
						case 6: tMagic=63;break;
						default: tMagic=0;break;
					}
					pMapItem->tIQ = MAGIC_ITEM;	
					pMapItem->tMagic[0] =tMagic;
					pMapItem->tMagic[5]= 1;

				}else if(iItemNum==987){
					pMapItem->tIQ = MAGIC_ITEM;	
					pMapItem->tMagic[0] =59;

				}
			}
		}		

		// ÇØ´ç À¯Àú¿¡°Ô ¾Ë¸°´Ù.			
	//	pCom->DelThrowItem();
		pCom->SetThrowItem( pMapItem, pt.x, pt.y, m_ZoneIndex );

		::InterlockedExchange(&g_zone[m_ZoneIndex]->m_pMap[pt.x][pt.y].m_FieldUse, 0);
	}
}

//////////////////////////////////////////////////////////////////////////////////
//	ÇöÀç À§Ä¡¸¦ Áß½ÉÀ¸·Î 25 ¼¿Áß ¾ÆÀÌÅÛ¸¦ ¶³¾îÁú¼öÀÖ´Â ÁÂÇ¥¸¦ ·¥´ýÀ¸·Î »ý¼º
//
CPoint CNpc::FindNearRandomPoint(int x, int y)
{
	CPoint t;
	int i;
	int iX, iY;
	int rand_x = 1, rand_y = 1;

	MAP *pMap = g_zone[m_ZoneIndex];
	if( !pMap ) return CPoint(-1, -1);
	if( !pMap->m_pMap ) return CPoint(-1, -1);

	int dir[25][2];

	//	X					Y
	dir[0][0]  =  0;		dir[0][1] =  0;		// 
	dir[1][0]  = -1;		dir[1][1] =  0;		// 
	dir[2][0]  = -1;		dir[2][1] =  1;		// 
	dir[3][0]  =  0;		dir[3][1] =  1;		// 
	dir[4][0]  =  1;		dir[4][1] =  1;		// 

	dir[5][0]  =  1;		dir[5][1] =  0;		// 
	dir[6][0]  =  1;		dir[6][1] = -1;		// 
	dir[7][0]  =  0;		dir[7][1] = -1;		// 
	dir[8][0]  = -1;		dir[8][1] = -1;		// 
	dir[9][0]  = -2;		dir[9][1] = -1;		// 

	dir[10][0] = -2;		dir[10][1] =  0;	// 
	dir[11][0] = -2;		dir[11][1] =  1;	// 
	dir[12][0] = -2;		dir[12][1] =  2;	// 
	dir[13][0] = -1;		dir[13][1] =  2;	// 
	dir[14][0] =  0;		dir[14][1] =  2;	// 

	dir[15][0] =  1;		dir[15][1] =  2;	// 
	dir[16][0] =  2;		dir[16][1] =  2;	// 
	dir[17][0] =  2;		dir[17][1] =  1;	// 
	dir[18][0] =  2;		dir[18][1] =  0;	// 
	dir[19][0] =  2;		dir[19][1] = -1;	// 

	dir[20][0] =  2;		dir[20][1] = -2;	// 
	dir[21][0] =  1;		dir[21][1] = -2;	// 
	dir[22][0] =  0;		dir[22][1] = -2;	// 
	dir[23][0] = -1;		dir[23][1] = -2;	// 
	dir[24][0] = -2;		dir[24][1] = -2;	// 

	rand_x = myrand(1, 8, TRUE);
	rand_y = myrand(0, 1, TRUE);

	iX = dir[rand_x][rand_y] + x;
	iY = dir[rand_x][rand_y] + y;

	rand_x = iX; rand_y = iY;
		
	if(rand_x >= pMap->m_sizeMap.cx || rand_x < 0 || rand_y >= pMap->m_sizeMap.cy || rand_y < 0) return CPoint(-1, -1);

	if(g_zone[m_ZoneIndex]->m_pMap[rand_x][rand_y].m_lUser == 0)
	{
		if( IsMovable( rand_x, rand_y ) )
		{
//			if(g_zone[m_ZoneIndex]->m_pMap[rand_x][rand_y].iIndex == -1) return CPoint( rand_x, rand_y );
			return CPoint( rand_x, rand_y );
		}
	}

	rand_x = x, rand_y = y;

	for( i = 1; i < 25; i++)
	{
		iX = rand_x + dir[i][0];
		iY = rand_y + dir[i][1];

		if( iX >= pMap->m_sizeMap.cx || iX < 0 || iY >= pMap->m_sizeMap.cy || iY < 0) continue;

		if(g_zone[m_ZoneIndex]->m_pMap[iX][iY].m_lUser != 0) continue;	// ºó ¸ÊÀÎÁö È®ÀÎÇÑ´Ù.

		if( IsMovable( iX, iY ) )
		{
//			if(g_zone[m_ZoneIndex]->m_pMap[iX][iY].iIndex == -1) return CPoint( iX, iY );
			return CPoint( iX, iY );
		}
	}

	return CPoint(-1, -1);
}

CPoint CNpc::FindNearRandomPointForItem(int x, int y)
{
	CPoint t;
	int i;
	int iX, iY;
	int rand_x = 1, rand_y = 1;

	MAP *pMap = g_zone[m_ZoneIndex];
	if( !pMap ) return CPoint(-1, -1);
	if( !pMap->m_pMap ) return CPoint(-1, -1);

	int dir[25][2];

	//	X					Y
	dir[0][0]  =  0;		dir[0][1] =  0;		// 
	dir[1][0]  = -1;		dir[1][1] =  0;		// 
	dir[2][0]  = -1;		dir[2][1] =  1;		// 
	dir[3][0]  =  0;		dir[3][1] =  1;		// 
	dir[4][0]  =  1;		dir[4][1] =  1;		// 

	dir[5][0]  =  1;		dir[5][1] =  0;		// 
	dir[6][0]  =  1;		dir[6][1] = -1;		// 
	dir[7][0]  =  0;		dir[7][1] = -1;		// 
	dir[8][0]  = -1;		dir[8][1] = -1;		// 
	dir[9][0]  = -2;		dir[9][1] = -1;		// 

	dir[10][0] = -2;		dir[10][1] =  0;	// 
	dir[11][0] = -2;		dir[11][1] =  1;	// 
	dir[12][0] = -2;		dir[12][1] =  2;	// 
	dir[13][0] = -1;		dir[13][1] =  2;	// 
	dir[14][0] =  0;		dir[14][1] =  2;	// 

	dir[15][0] =  1;		dir[15][1] =  2;	// 
	dir[16][0] =  2;		dir[16][1] =  2;	// 
	dir[17][0] =  2;		dir[17][1] =  1;	// 
	dir[18][0] =  2;		dir[18][1] =  0;	// 
	dir[19][0] =  2;		dir[19][1] = -1;	// 

	dir[20][0] =  2;		dir[20][1] = -2;	// 
	dir[21][0] =  1;		dir[21][1] = -2;	// 
	dir[22][0] =  0;		dir[22][1] = -2;	// 
	dir[23][0] = -1;		dir[23][1] = -2;	// 
	dir[24][0] = -2;		dir[24][1] = -2;	// 

	rand_x = myrand(1, 8, TRUE);
	rand_y = myrand(0, 1, TRUE);

	iX = dir[rand_x][rand_y] + x;
	iY = dir[rand_x][rand_y] + y;

	rand_x = iX; rand_y = iY;
		
	if(rand_x >= pMap->m_sizeMap.cx || rand_x < 0 || rand_y >= pMap->m_sizeMap.cy || rand_y < 0) return CPoint(-1, -1);

//	if(g_zone[m_ZoneIndex]->m_pMap[rand_x][rand_y].m_lUser == 0)
//	{
//		if( IsMovable( rand_x, rand_y ) )
//		{
//			if(g_zone[m_ZoneIndex]->m_pMap[rand_x][rand_y].iIndex == -1) return CPoint( rand_x, rand_y );
//		}
//	}

	if( g_zone[m_ZoneIndex]->m_pMap[rand_x][rand_y].m_FieldUse == 0 )
	{
		if( g_zone[m_ZoneIndex]->m_pMap[rand_x][rand_y].iIndex == -1 ) return CPoint( rand_x, rand_y );
	}

	rand_x = x, rand_y = y;

	for( i = 1; i < 25; i++)
	{
		iX = rand_x + dir[i][0];
		iY = rand_y + dir[i][1];

		if( iX >= pMap->m_sizeMap.cx || iX < 0 || iY >= pMap->m_sizeMap.cy || iY < 0) continue;

//		if(g_zone[m_ZoneIndex]->m_pMap[iX][iY].m_lUser != 0) continue;	// ºó ¸ÊÀÎÁö È®ÀÎÇÑ´Ù.
		if( g_zone[m_ZoneIndex]->m_pMap[iX][iY].m_FieldUse != 0 ) continue;	// »ç¿ëÁßÀÎÁö Ã¼Å©.

//		if( IsMovable( iX, iY ) )
//		{
//			if(g_zone[m_ZoneIndex]->m_pMap[iX][iY].iIndex == -1) return CPoint( iX, iY );
//		}
		if(g_zone[m_ZoneIndex]->m_pMap[iX][iY].iIndex == -1) return CPoint( iX, iY );
	}

	return CPoint(-1, -1);
}

///////////////////////////////////////////////////////////////////////////////////
//	x, y °¡ ¿òÁ÷ÀÏ ¼ö ÀÖ´Â ÁÂÇ¥ÀÎÁö ÆÇ´Ü
//
BOOL CNpc::IsMovable(int x, int y)
{
	if(x < 0 || y < 0 ) return FALSE;

	if(!g_zone[m_ZoneIndex] ) return FALSE;
	if(!g_zone[m_ZoneIndex]->m_pMap) return FALSE;
	if(x >= g_zone[m_ZoneIndex]->m_sizeMap.cx || y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) return FALSE;
	if(g_zone[m_ZoneIndex]->m_pMap[x][y].m_bMove || g_zone[m_ZoneIndex]->m_pMap[x][y].m_lUser) return FALSE;

	return TRUE;
}
			
//////////////////////////////////////////////////////////////////////////////////////////////
//	NPC °ø°Ý ¼º°ø
//
void CNpc::SendAttackSuccess(COM *pCom, int tuid, BOOL bIsCritical, short sHP, short sMaxHP)
{
	if(pCom == NULL) return;

	CBufferEx TempBuf;
//	CByteArray arAction1;
//	CByteArray arAction2;
	
	TempBuf.Add(ATTACK_RESULT);
	//--------------------------------------------------
	//yskang 0.3 NPC´Â Å©¸®Æ¼ÄÃ °ø°ÝÀÌ ¾ø´Ù.
	//--------------------------------------------------
	TempBuf.Add(ATTACK_SUCCESS);
	TempBuf.Add((int)(m_sNid + NPC_BAND));
	TempBuf.Add(tuid);
	//----------------------------------------------------

/*	BYTE tAction1 = (BYTE)arAction1.GetSize();
	BYTE tAction2 = (BYTE)arAction2.GetSize();
	int i = 0;

	TempBuf.Add(tAction1);
	if(tAction1 > 0)
	{
		for(i = 0; i < arAction1.GetSize(); i++)
		{
			TempBuf.Add(arAction1[i]);
		}
	}
	TempBuf.Add(tAction2);
	if(tAction2 > 0)
	{
		for(i = 0; i < arAction2.GetSize(); i++)
		{
			TempBuf.Add(arAction2[i]);
		}
	}
	
*/	
	TempBuf.Add((short)sHP);
	TempBuf.Add((short)sMaxHP);

//	SendInsight(pCom, TempBuf, TempBuf.GetLength());
	SendExactScreen(pCom, TempBuf, TempBuf.GetLength());
}

////////////////////////////////////////////////////////////////////////////
//	NPC °ø°Ý ¹Ì½º
//
void CNpc::SendAttackMiss(COM *pCom, int tuid)
{
	CBufferEx TempBuf;
	
	TempBuf.Add(ATTACK_RESULT);
	TempBuf.Add(ATTACK_MISS);
	TempBuf.Add((int)(m_sNid + NPC_BAND));
	TempBuf.Add(tuid);

//	SendInsight(pCom, TempBuf, TempBuf.GetLength());
	SendExactScreen(pCom, TempBuf, TempBuf.GetLength());
}

/////////////////////////////////////////////////////////////////////////
//	NPC ÀÇ ¹«±â °è¿­À» ±¸ÇÑ´Ù.
//
BYTE CNpc::GetWeaponClass()
{
	BYTE tClass = BRAWL;

	switch (m_byClass)
	{
	case 1:
		tClass = BRAWL;
		break;
		
	case 2:
		tClass = STAFF;
		break;
		
	case 4:
		tClass = EDGED;
		break;
		
	case 8:
		tClass = FIREARMS;
		break;
	}

	return tClass;
}

/////////////////////////////////////////////////////////////////////////////////////
//	°ø°Ý½Ã¸¶´Ù ½ºÅ³¼º°ø ¿©ºÎ¸¦ Ã¼Å©ÇÑ´Ù.
//
void CNpc::IsSkillSuccess(BOOL *bSuccess)
{
	int iOnCount = 0;
	int i = 0;
	
	for(i = 0; i < SKILL_NUM; i++) bSuccess[i] = FALSE;

	for(i = 0; i < SKILL_NUM; i++) 
	{
		if(m_NpcSkill[i].tOnOff == 1) iOnCount++;
	}

	int iRandom = XdY(1, 100);
	int iRate = 0;

	for(i = 0; i < SKILL_NUM; i++)
	{
		iRate = (int)((double)m_sWIS * 0.5 + m_NpcSkill[i].tLevel * 2 - iOnCount * 25 + 50 /* +Magic Bonus*/);		//!Magic

		if(iRandom <= iRate) 
		{
			bSuccess[i] = TRUE;
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////
//	ÃÊ±â ÀÏ¹Ý µ¥¹ÌÁö¸¦ ¾ò´Â´Ù.
//
int CNpc::GetNormalInitDamage()
{
	int nHit = 0;
	int nDamage = 0;
	int xyz = 0;

	xyz = XdY(m_byAX, m_byAY) + m_byAZ;

//  2002-10-17 by Youn Gyu
//	if(m_byClass == FIREARMS) nHit = (int)((double)m_sDEX/3 + 0.5);
//	else					  nHit = (int)((double)m_sSTR/2 + 0.5);

	if(nHit < 0) nHit = 0;

	nDamage = nHit + xyz;
	return nDamage;
}

///////////////////////////////////////////////////////////////////////////////////////
//	ÃÊ±â Å©¸®Æ¼ÄÃ µ¥¹ÌÁö¸¦ ¾ò´Â´Ù.
//
int CNpc::GetCriticalInitDamage(BOOL *bSuccessSkill)
{
	int nDamage = 0;
	int xyz = 0;

	xyz = XdY(m_byAX, m_byAY) + m_byAZ;
/*
	// º¸½º¸÷ÀÏ¶§ ±âÈ¹¿¡¼­ ¾Ë·ÁÁÙ¿¹Á¤...
*/
	return nDamage;

}

///////////////////////////////////////////////////////////////////////////
//	³Ã±â µ¥¹ÌÁö¸¦ ¼ÂÆÃÇÑ´Ù.
//
void CNpc::SetColdDamage()
{
	if(m_tAbnormalKind != ABNORMAL_BYTE_NONE) return;		// ÀÌ¹Ì »óÅÂÀÌ»óÀÌ °É·ÁÀÖ´Â »óÅÂÀÌ¸é ¸®ÅÏ

	m_tAbnormalKind = ABNORMAL_BYTE_COLD;
	m_dwAbnormalTime = COLD_TIME;
	m_dwLastAbnormalTime = GetTickCount();
}

///////////////////////////////////////////////////////////////////////////
//	È­¿°µ¥¹ÌÁö¸¦ ¼ÂÆÃÇÑ´Ù.
//
void CNpc::SetFireDamage()
{
	if(m_tAbnormalKind != ABNORMAL_BYTE_NONE) return;		// ÀÌ¹Ì »óÅÂÀÌ»óÀÌ °É·ÁÀÖ´Â »óÅÂÀÌ¸é ¸®ÅÏ

	m_tAbnormalKind = ABNORMAL_BYTE_FIRE;
	m_dwAbnormalTime = FIRE_TIME;
	m_dwLastAbnormalTime = GetTickCount();
}

/////////////////////////////////////////////////////////////////////////////
//	Damage °è»ê, ¸¸¾à m_sHP °¡ 0 ÀÌÇÏÀÌ¸é »ç¸ÁÃ³¸®
//
BOOL CNpc::SetDamage(int nDamage, int uuid, COM *pCom)
{
	if(m_NpcState == NPC_DEAD) return TRUE;
	if(m_sHP <= 0) return TRUE;
	if(nDamage <= 0) return TRUE;

	if(m_tNpcType == NPCTYPE_GUARD) return TRUE;

	if(m_tGuildWar == GUILD_WAR_AFFTER)
	{
		if(m_tNpcType >= NPCTYPE_GUILD_NPC) return TRUE;
//		if(m_tNpcType == NPCTYPE_GUILD_NPC) return TRUE;
//		if(m_tNpcType == NPCTYPE_GUILD_GUARD) return TRUE;
//		if(m_tNpcType == NPCTYPE_GUILD_DOOR) return TRUE;
	}

	if(InterlockedCompareExchange((long*)&m_lDamage, (long)1, (long)0) == (long)0)
	{
		int i;
		int iLen = 0;
		int userDamage = 0;
		ExpUserList *tempUser = NULL;

		int uid = uuid - USER_BAND;

		USER* pUser = GetUser(pCom, uid);
														// ÇØ´ç »ç¿ëÀÚÀÎÁö ÀÎÁõ
		if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) 
		{
			InterlockedExchange(&m_lDamage, (LONG)0);
			return TRUE;
		}

		iLen = strlen(pUser->m_strUserID);
		if(iLen <= 0 || iLen > CHAR_NAME_LENGTH) 
		{
			InterlockedExchange(&m_lDamage, (LONG)0);
			return TRUE;
		}

		if(m_tGuildWar == GUILD_WARRING)// ±æµåÀüÀÌ ¹ú¾îÁö´Â »óÁ¡ÀÇ »óÀÏ °æ¿ì
		{
			if(m_tNpcType == NPCTYPE_GUILD_NPC)		// »óÁ¡°ú °ø¼ºÀü¿¡¼­ NPC´Â ¼­·Î ´Ù¸¥ °á°ú¸¦ ¸¸µé±â ¶§¹®
			{
//				if(m_pGuardStore) { SetDamagedInGuildWar(nDamage, pUser); InterlockedExchange(&m_lDamage, (LONG)0); return TRUE; }
				if(m_pGuardFortress) { SetDamagedInFortressWar(nDamage, pUser); InterlockedExchange(&m_lDamage, (LONG)0); return TRUE; }
			}
			else if(m_tNpcType == NPCTYPE_GUILD_DOOR)	// °ø¼ºÀüÀ» À§ÇØ Æ¯º°È÷	  
			{
				if(m_pGuardFortress) { SetDoorDamagedInFortressWar(nDamage, pUser); InterlockedExchange(&m_lDamage, (LONG)0); return TRUE; }
			}
			else if(m_tNpcType == NPCTYPE_GUILD_GUARD)	// °¢ ±æµå¿¡ ¼ÓÇÑ °æºñº´Àº ÀÚ±â±æµå¿øÀ¸·ÎºÎÅÍ º¸È£(?)¹Þ±âÀ§ÇØ
			{
				if(pUser->m_dwGuild > 0)
				{
/*					if(m_pGuardStore) 
					{ 
						if(m_pGuardStore->m_iGuildSid == pUser->m_dwGuild)
						{
							InterlockedExchange(&m_lDamage, (LONG)0);
							return TRUE; 
						}
*/					if(m_pGuardFortress) 
					{ 
						if(m_pGuardFortress->m_iGuildSid == pUser->m_dwGuild)
						{
							InterlockedExchange(&m_lDamage, (LONG)0); 
							return TRUE; 
						}
					}
				}
			}
		}

		if( m_sEvent == NPC_EVENT_GREATE_MOP || m_sEvent== NPC_EVENT_MOP|| m_sEvent== 32000)			// ¿¢½º¸®¿Â µî Æ¯¼ö ¸ó½ºÅÍÀÏ°æ¿ì 10%¸¸ ¹Ý¿µÇÑ´Ù.
		{
			nDamage = (int)( (double)nDamage * 0.1 );
		}

		userDamage = nDamage;
														// À×¿© µ¥¹ÌÁö´Â ¼Ò¿ë¾ø´Ù.		
		if( (m_sHP - nDamage) < 0 ) userDamage = m_sHP;

		for(i = 0; i < NPC_HAVE_USER_LIST; i++)
		{
			if(m_DamagedUserList[i].iUid == uid)
			{
				if(strcmp(m_DamagedUserList[i].strUserID, pUser->m_strUserID) == 0) 
				{ 
					m_DamagedUserList[i].nDamage += userDamage; 
					goto go_result;
				}
			}
		}

		for(i = 0; i < NPC_HAVE_USER_LIST; i++)				// ÀÎ¿ø Á¦ÇÑÀÌ ÃÖÁ¾ ´ë¹ÌÁö¿¡ ¿µÇâÀ» ¹ÌÄ¡³ª?
		{
			if(m_DamagedUserList[i].iUid == -1)
			{
				if(m_DamagedUserList[i].nDamage <= 0)
				{
					strncpy(m_DamagedUserList[i].strUserID, pUser->m_strUserID, iLen);
					m_DamagedUserList[i].iUid = uid;
					m_DamagedUserList[i].nDamage = userDamage;
					m_DamagedUserList[i].bIs = FALSE;
					break;
				}
			}
		}

go_result:
		m_TotalDamage += userDamage;
		m_sHP -= nDamage;
		
		if( m_sHP <= 0 )
		{
			UserListSort();							// ¾ÆÀÌÅÛÀÇ ÁÖÀÎÀÌ ´©±º°¡

			m_ItemUserLevel = pUser->m_sLevel;
			m_sHP = 0;

			InterlockedExchange(&m_lKillUid, (LONG)uid);
			if(m_sPid==190)
				m_sEvent=2;
			// Á×Àº ¸÷ÀÌ Äù½ºÆ®¿¡ ¼ÓÇÑ ÀÌº¥Æ® ¸÷ÀÎ°æ¿ì ÇØ´ç ÀÌº¥Æ®¸¦ ½ÇÇà
			if(m_sEvent > 0 && m_sEvent <= NPC_QUEST_MOP)	
				pUser->RunQuestEvent(this, m_sCurZ, m_sEvent);
			Dead();
			InterlockedExchange(&m_lDamage, (LONG)0);
			return FALSE;
		}

		ChangeTarget(pUser, pCom);

		InterlockedExchange(&m_lDamage, (LONG)0);
	}
	return TRUE;
}

BOOL CNpc::CheckNpcRegenCount()
{
/*	if(m_NpcState != NPC_DEAD) return FALSE;

	QueryPerformanceCounter((LARGE_INTEGER*)&m_RegenLastCount);

	if((m_RegenLastCount - m_RegenStartCount) >= g_Online_Update_Min_ticks)
	{
		m_RegenStartCount += g_Online_Update_Min_ticks;
		m_RegenCount += 10000;
	}

	if(m_RegenCount >= (DWORD)m_sRegenTime) return TRUE;
*/
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
//	Å¸°ÙÀÌ µÑ·¯ ½×¿© ÀÖÀ¸¸é ´ÙÀ½ Å¸°ÙÀ» Ã£´Â´Ù.
//
BOOL CNpc::IsSurround(int targetx, int targety)
{
	if(m_tNpcLongType) return FALSE;		//¿ø°Å¸®´Â Åë°ú

	for(int i = 0; i < (sizeof(surround_x) / sizeof(surround_x[0])); i++)		// ÁÖº¯ 8¹æÇâ
	{
		if(IsMovable(targetx + surround_x[i], targety + surround_y[i])) return FALSE;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	³ª¸¦ °ø°ÝÇÑ À¯Àú¸¦ Å¸°ÙÀ¸·Î »ï´Â´Ù.(±âÁØ : ·¾°ú HP¸¦ ±âÁØÀ¸·Î ¼±Á¤)
//
void CNpc::ChangeTarget(USER *pUser, COM* pCom)
{
	int preDamage, lastDamage;
	int dist;

	if(m_byAX == 0 && m_byAZ == 0 ) return;		// ³»°¡ °ø°Ý·ÂÀÌ ¾øÀ¸¸é °ø°ÝÇÏÁö ¾Ê´Â´Ù
	if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) return;
	if(pUser->m_bLive == USER_DEAD) return;
	if(pUser->m_tIsOP == 1) return;		// ¿î¿µÀÚ´Â ¹«½Ã...^^
	if(pUser->m_bPShopOpen == TRUE) return;
	USER *preUser = NULL;
	preUser = GetUser(pCom, m_Target.id - USER_BAND);

	if(pUser == preUser) return;

	if(preUser != NULL && preUser->m_state == STATE_GAMESTARTED)
	{
		if(strcmp(pUser->m_strUserID, preUser->m_strUserID) == 0) return;
		
		preDamage = 0; lastDamage = 0;
		preDamage = GetFinalDamage(preUser, 0);
		lastDamage = GetFinalDamage(pUser, 0); 

		dist = abs(preUser->m_curx - m_sCurX) + abs(preUser->m_cury - m_sCurY);
		if(dist == 0) return;
		preDamage = (int)((double)preDamage/dist + 0.5);
		dist = abs(pUser->m_curx - m_sCurX) + abs(pUser->m_cury - m_sCurY);
		if(dist == 0) return;
		lastDamage = (int)((double)lastDamage/dist + 0.5);

		if(preDamage > lastDamage) return;
	}
		
	m_Target.id	= pUser->m_uid + USER_BAND;
	m_Target.x	= pUser->m_curx;
	m_Target.y	= pUser->m_cury;

/*	if(pUser->m_strUserID != NULL)
	{
		m_Target.nLen = strlen(pUser->m_strUserID);

		if(m_Target.nLen <= CHAR_NAME_LENGTH) strncpy(m_Target.szName, pUser->m_strUserID, m_Target.nLen);
		else								  ::ZeroMemory(m_Target.szName, sizeof(m_Target.szName));
	}
*/										// ¾î½½·· °Å¸®´Âµ¥ °ø°ÝÇÏ¸é ¹Ù·Î ¹Ý°Ý
	if(m_NpcState == NPC_STANDING || m_NpcState == NPC_MOVING)
	{									// °¡±îÀÌ ÀÖÀ¸¸é ¹Ý°ÝÀ¸·Î ÀÌ¾îÁö±¸
		if(IsCloseTarget(pUser, m_byRange) == TRUE)
		{
			m_NpcState = NPC_FIGHTING;
			NpcFighting(pCom);
		}
		else							// ¹Ù·Î µµ¸Á°¡¸é ÁÂÇ¥¸¦ °»½ÅÇÏ°í ÃßÀû	
		{
			if(GetTargetPath(pCom) == TRUE)	// ¹Ý°Ý µ¿ÀÛÈÄ ¾à°£ÀÇ µô·¹ÀÌ ½Ã°£ÀÌ ÀÖÀ½	
			{
				m_NpcState = NPC_TRACING;
				NpcTracing(pCom);
			}
			else
			{
				ToTargetMove(pCom, pUser);
			}
		}
	}
//	else m_NpcState = NPC_ATTACKING;	// ÇÑÂü °ø°ÝÇÏ´Âµ¥ ´©°¡ ¹æÇØÇÏ¸é ¸ñÇ¥¸¦ ¹Ù²Þ

	if(m_tNpcGroupType)					// °¡Á·Å¸ÀÔÀÌ¸é ½Ã¾ß¾È¿¡ °°Àº Å¸ÀÔ¿¡°Ô ¸ñÇ¥ ÁöÁ¤
	{
		m_Target.failCount = 0;
		FindFriend();
	}
}

/////////////////////////////////////////////////////////////////////////////
//	NPC »óÅÂº°·Î ºÐÈ­ÇÑ´Ù.
//
void CNpc::NpcLive(COM *pCom)
{
	if(SetLive(pCom))
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sStandTime;

	}
	else
	{
		m_NpcState = NPC_LIVE;
		m_Delay = m_sStandTime * 10;
	}
}

/////////////////////////////////////////////////////////////////////////////
//	NPC°¡ ¼­ÀÖ´Â°æ¿ì.
//
void CNpc::NpcStanding(COM *pCom)
{
	NpcTrace(_T("NpcStanding()"));

	if(RandomMove(pCom) == TRUE)
	{
		m_NpcState = NPC_MOVING;

		if( m_sStandTime > 2500 )
		{
			m_Delay = m_sStandTime - 2000;
		}
		else
		{
			m_Delay = m_sStandTime;
		}

//		m_Delay = m_sStandTime;
//		m_Delay = m_sSpeed;		 // 2001-09-01, jjs07 
		return;
	}

	m_NpcState = NPC_STANDING;

	m_Delay = m_sStandTime;
}

/////////////////////////////////////////////////////////////////////////////
//	NPC°¡ ÀÌµ¿ÇÏ´Â °æ¿ì.
//
void CNpc::NpcMoving(COM *pCom)
{
	NpcTrace(_T("NpcMoving()"));

	if(m_sHP <= 0) 
	{
		Dead();
		return;
	}

	if(FindEnemy(pCom) == TRUE)		// ÀûÀ» Ã£´Â´Ù. 
	{
		if(m_tNpcType == NPCTYPE_GUARD || m_tNpcType == NPCTYPE_GUILD_GUARD) 
		{ 
			m_NpcState = NPC_FIGHTING; 
			m_Delay = 0; 
		}
		else 
		{ 
			m_NpcState = NPC_ATTACKING;
			m_Delay = m_sSpeed;
		}
		return;
	}

	if(m_tNpcType == NPCTYPE_GUARD || m_tNpcType == NPCTYPE_GUILD_GUARD) // ÀÌµ¿¾ÈÇÏ°Ô...
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sStandTime;
		return;
	}

	if(IsMovingEnd())				// ÀÌµ¿ÀÌ ³¡³µÀ¸¸é
	{
		m_NpcState = NPC_STANDING;

		//¿µ¿ª ¹Û¿¡ ÀÖÀ¸¸é ¼­ÀÖ´Â ½Ã°£À» Âª°Ô...
		if(IsInRange())	m_Delay = m_sStandTime;
		else m_Delay = m_sStandTime - 1000;

		if(m_Delay < 0) m_Delay = 0;

		return;
	}

	if(StepMove(pCom, 1) == FALSE)	// ÇÑÄ­ ¿òÁ÷ÀÓ(°È´Âµ¿ÀÛ, ´Þ¸±¶§´Â 2Ä­)
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sStandTime;
		return;
	}

	CBufferEx TempBuf;

	CPoint t = ConvertToClient( m_sCurX, m_sCurY );		// ¿òÁ÷ÀÌ·Á´Â ¼­¹öÁÂÇ¥°¡ Å¬¶óÀÌ¾ðÆ®¿¡¼­ ¸ø¿òÁ÷ÀÌ´Â ÁÂÇ¥¸é ¸®ÅÏ

	if(IsStepEnd())	TempBuf.Add(MOVE_END_RESULT);
	else			TempBuf.Add(MOVE_RESULT);

	TempBuf.Add(SUCCESS);
	TempBuf.Add((int)(NPC_BAND + m_sNid));
	TempBuf.Add((short)t.x);
	TempBuf.Add((short)t.y);

	SendInsight(pCom, TempBuf, TempBuf.GetLength());

	m_Delay = m_sSpeed;
}

/////////////////////////////////////////////////////////////////////////////
//	NPC°¡ °ø°ÝÇÏ´Â°æ¿ì.
//
void CNpc::NpcAttacking(COM *pCom)
{
	NpcTrace(_T("NpcAttacking()"));
	
	int ret = 0;

	if( m_byPsi > 0 && m_byPsi < g_arMonsterPsi.GetSize() )	// ¸¶¹ýÀÌ ÀÖ´Â ³ðÀÌ¶ó¸é...
	{
		CMonsterPsi* pMagic = g_arMonsterPsi[(int)m_byPsi];

		if( pMagic )
		{
			if( IsCloseTarget( pCom, pMagic->m_byRange ) )
			{
				m_NpcState = NPC_FIGHTING;
				m_Delay = 0;
				return;
			}
		}
	}

	if(IsCloseTarget(pCom, m_byRange))	// °ø°ÝÇÒ ¼ö ÀÖ´Â¸¸Å­ °¡±î¿î °Å¸®ÀÎ°¡?
	{
		m_NpcState = NPC_FIGHTING;
		m_Delay = 0;
		return;
	}

	if(m_tNpcType == NPCTYPE_GUARD || m_tNpcType == NPCTYPE_GUILD_GUARD)// ¼­ÀÖ´Â °æºñº´ÀÏ¶§ °ø°ÝÀÌ ½ÇÆÐÇÏ¸é Àá±ñ µ¿¾È ½¬µµ·ÏÇÑ´Ù. 
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sStandTime/2;
		return;
	}

	if(GetTargetPath(pCom) == FALSE)
	{
		if(RandomMove(pCom) == FALSE)
		{
			m_NpcState = NPC_STANDING;
			m_Delay = m_sStandTime;
			return;
		}

		m_NpcState = NPC_MOVING;
		m_Delay = m_sSpeed;
		return;
	}

	m_NpcState = NPC_TRACING;
	m_Delay = 0;
}

/////////////////////////////////////////////////////////////////////////////
//	NPC°¡ À¯Àú¸¦ ÃßÀûÇÏ´Â °æ¿ì.
//
void CNpc::NpcTracing(COM *pCom)
{
	NpcTrace(_T("NpcTracing()"));

	if(m_tNpcType == NPCTYPE_GUARD || m_tNpcType == NPCTYPE_GUILD_GUARD) return;

	if(GetUser(pCom, (m_Target.id - USER_BAND)) == NULL)	// Target User °¡ Á¸ÀçÇÏ´ÂÁö °Ë»ç
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sStandTime;
		return;
	}

	if( m_byPsi > 0 && m_byPsi < g_arMonsterPsi.GetSize() )	// ¸¶¹ýÀÌ ÀÖ´Â ³ðÀÌ¶ó¸é...
	{
		CMonsterPsi* pMagic = g_arMonsterPsi[(int)m_byPsi];

		if( pMagic )
		{
			if( IsCloseTarget( pCom, pMagic->m_byRange ) )
			{
				m_NpcState = NPC_FIGHTING;
				m_Delay = 0;
				return;
			}
		}
	}

	if(IsCloseTarget(pCom, m_byRange))						// ±ÙÁ¢ÀüÀ» ¹úÀÏ¸¸Å­ °¡±î¿î °Å¸®ÀÎ°¡?
	{
		m_NpcState = NPC_FIGHTING;
		m_Delay = 0;
		return;
	}

	if(IsSurround(m_Target.x, m_Target.y))					// ¸ñÇ¥ Å¸°ÙÀÌ µÑ·¯½×¿© ÀÖÀ¸¸é ´ÙÀ½ Å¸°ÙÀ» Ã£´Â´Ù.
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sStandTime;
		return;
	}

	if(IsChangePath(pCom))									// ±æÃ£±â¸¦ ´Ù½Ã ÇÒ¸¸Å­ Target ÀÇ À§Ä¡°¡ º¯Çß´Â°¡?
	{
		if(ResetPath(pCom) == FALSE)// && !m_tNpcTraceType)
		{
			m_NpcState = NPC_STANDING;
			m_Delay = m_sStandTime;
			return;
		}
	}
	
	if(StepMove(pCom, 1) == FALSE)							// ÇÑÄ­ ¿òÁ÷ÀÓ(°È´Âµ¿ÀÛ, ´Þ¸±¶§´Â 2Ä­)
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sStandTime;	
		return;
	}

	CBufferEx TempBuf;

	CPoint t = ConvertToClient( m_sCurX, m_sCurY );		// ¿òÁ÷ÀÌ·Á´Â ¼­¹öÁÂÇ¥°¡ Å¬¶óÀÌ¾ðÆ®¿¡¼­ ¸ø¿òÁ÷ÀÌ´Â ÁÂÇ¥¸é ¸®ÅÏ

	if(IsStepEnd())	TempBuf.Add(MOVE_END_RESULT);
	else			TempBuf.Add(MOVE_RESULT);

	TempBuf.Add(SUCCESS);
	TempBuf.Add((int)(NPC_BAND + m_sNid));
	TempBuf.Add((short)t.x);
	TempBuf.Add((short)t.y);

	SendInsight(pCom, TempBuf, TempBuf.GetLength());

	m_Delay = m_sSpeed;
}

/////////////////////////////////////////////////////////////////////////////
//	¸÷ÀÇ ¼Óµµ º¯È­¸¦ ¾Ë·Á ÁØ´Ù.
//
void CNpc::ChangeSpeed(COM *pCom, int delayTime)
{
/*	CBufferEx TempBuf;

	int tempTime = delayTime * NPC_TRACING_STEP;
	
	if(m_Delay > m_sSpeed) m_Delay = m_sSpeed;// ½ºÅÄµù ½Ã°£ÀÌ 1000ÀÏ°æ¿ì 

	m_Delay = m_Delay + tempTime;			// 10, 50, 100´ÜÀ§·Î Áõ.°¨
	
	if(m_Delay <= 500) m_Delay = 500;		// ÃÖ¼Ò´Â Ç×»ó 500ÀÓ	
											// 500À» 100%ÀÌ¸é 600Àº 80À¸·Î °¨¼Ò	
	short step = 100 - (m_Delay - 500) * 10/50;

	TempBuf.Add(SET_SPEED_MONSTER);

	TempBuf.Add(m_sNid + NPC_BAND);
	TempBuf.Add(step);

		// NPC ÁÖÀ§ÀÇ À¯Àú¿¡°Ô Á¤º¸Àü¼Û
	CPoint ptOld;
	if(SightRecalc(ptOld))
	{
		SendRemainSight(pCom, TempBuf, TempBuf.GetLength(), ptOld);
	}
	else SendInsight(pCom, TempBuf, TempBuf.GetLength());
*/
}

/////////////////////////////////////////////////////////////////////////////
//	NPC°¡ °ø°ÝÇÏ´Â °æ¿ì.
//
void CNpc::NpcFighting(COM *pCom)
{
	NpcTrace(_T("NpcFighting()"));

	if(m_sHP <= 0) 
	{
		Dead();
		return;
	}

	m_dwDelayCriticalDamage = 0;

	int at_type_total = m_iNormalATRatio + m_iSpecialATRatio + m_iMagicATRatio;
	if( at_type_total > 100 )
	{
		m_iNormalATRatio = 100;
		m_iSpecialATRatio = 0;
		m_iMagicATRatio = 0;
		at_type_total = 100;
	}

	int at_type[1000],i;

	for( i = 0; i < 100; i++ ) at_type[i] = 1;

	int rand_index = m_iNormalATRatio;

	for( i = rand_index; i < rand_index+m_iSpecialATRatio; i++ )
	{
		at_type[i] = 2;
	}

	rand_index += m_iSpecialATRatio;

	for( i = rand_index; i < rand_index+m_iMagicATRatio; i++ )
	{
		at_type[i] = 3;
	}

	int at_type_rand = myrand( 0, 99 );

	if( at_type[at_type_rand] == 3 )
	{
		if( m_byPsi )
		{
			m_Delay = PsiAttack( pCom );

			if( m_Delay == -1 )
			{
				m_NpcState = NPC_ATTACKING;
				m_Delay = m_sSpeed;
			}

			return;
		}
	}
	else if( at_type[at_type_rand] == 2 )
	{
		m_Delay = AreaAttack( pCom );

		if( m_Delay == -1 )
		{
			m_NpcState = NPC_ATTACKING;
			m_Delay = m_sSpeed;
		}
		return;
	}
	else
	{
		m_Delay = Attack(pCom);
	}
}


/////////////////////////////////////////////////////////////////////////////
//	Å¸°Ù°úÀÇ °Å¸®¸¦ »çÁ¤°Å¸® ¹üÀ§·Î À¯ÁöÇÑ´Ù.(¼¿´ÜÀ§)
//
void CNpc::NpcBack(COM *pCom)
{
	NpcTrace(_T("NpcBack()"));

	if(GetUser(pCom, (m_Target.id - USER_BAND)) == NULL)	// Target User °¡ Á¸ÀçÇÏ´ÂÁö °Ë»ç
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sSpeed;//STEP_DELAY;
		return;
	}

	if(IsMovingEnd())								// ÀÌµ¿ÀÌ ³¡³µÀ¸¸é
	{
		m_Delay = m_sSpeed;
		NpcFighting(pCom);
		return;
	}
	
	if(StepMove(pCom, 1) == FALSE)					// ÇÑÄ­ ¿òÁ÷ÀÓ(°È´Âµ¿ÀÛ, ´Þ¸±¶§´Â 2Ä­)
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sSpeed;//STEP_DELAY;
		return;
	}

	m_Delay = m_sSpeed;//STEP_DELAY;
}

/////////////////////////////////////////////////////////////////////////////
//	´Ù¸¥ ¸÷°úÀÇ ¿¬°è¸¦ À§ÇØ¼­...
//
void CNpc::NpcStrategy(BYTE type)
{
	switch(type)
	{
	case NPC_ATTACK_SHOUT:
		m_NpcState = NPC_TRACING;
		m_Delay = m_sSpeed;//STEP_DELAY;
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
//	½Ã¾ß ¹üÀ§³»ÀÇ ³»µ¿·á¸¦ Ã£´Â´Ù.
//
void CNpc::FindFriend()
{
	CNpc* pNpc = NULL;

	if(m_bySearchRange == 0) return;

	int min_x, min_y, max_x, max_y;

	min_x = m_sCurX - m_bySearchRange;		if( min_x < 0 ) min_x = 0;
	min_y = m_sCurY - m_bySearchRange;		if( min_y < 0 ) min_y = 0;
	max_x = m_sCurX + m_bySearchRange;
	max_y = m_sCurY + m_bySearchRange;

	if(max_x >= g_zone[m_ZoneIndex]->m_sizeMap.cx) max_x = g_zone[m_ZoneIndex]->m_sizeMap.cx - 1;
	if(max_y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) max_y = g_zone[m_ZoneIndex]->m_sizeMap.cy - 1;

	int ix, iy;
	int target_uid;
	int uid;

	int tempLevel = 0, oldLevel = 1000;

	if(m_Target.id == -1) return;

	for(ix = min_x; ix <= max_x; ix++)
	{
		for(iy = min_y; iy <= max_y; iy++)
		{
			target_uid = m_pOrgMap[ix][iy].m_lUser;

			if( target_uid >= NPC_BAND && target_uid < INVALID_BAND)
			{
				uid = target_uid - NPC_BAND;				
				pNpc = g_arNpc[uid];
				if(pNpc == NULL) continue;
									
				if(pNpc->m_tNpcGroupType && m_sNid != uid && pNpc->m_sFamilyType == m_sFamilyType)
				{
//					pNpc->m_Target.nLen = strlen(pNpc->m_Target.szName);	// ÀÌ¹Ì ¸ñÇ¥°¡ ÀÖ¾î¼­ ÀÌ¹Ì °ø°ÝÇÏ°í ÀÖÀ¸¸é...
//					if(pNpc->m_Target.nLen > 0 && pNpc->m_NpcState == NPC_FIGHTING) continue;
					if(pNpc->m_Target.id >= 0 && pNpc->m_NpcState == NPC_FIGHTING) continue;

					pNpc->m_Target.id = m_Target.id;		// °°Àº Å¸ÀÔÀÇ µ¿·á¿¡°Ô µµ¿òÀ» ¿äÃ»ÇÑ´Ù.
					pNpc->m_Target.x = m_Target.x;			// °°Àº ¸ñÇ¥¸¦ °ø°ÝÇÏÀÚ°í...
					pNpc->m_Target.y = m_Target.y;

/*					if(m_Target.szName != NULL)
					{
						pNpc->m_Target.nLen = strlen(m_Target.szName);

						if(pNpc->m_Target.nLen <= CHAR_NAME_LENGTH) strncpy(pNpc->m_Target.szName, m_Target.szName, pNpc->m_Target.nLen);
						else								  ::ZeroMemory(pNpc->m_Target.szName, sizeof(pNpc->m_Target.szName));
					}
*/					pNpc->m_Target.failCount = 0;
					pNpc->NpcStrategy(NPC_ATTACK_SHOUT);
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
//	Å¸°ÙÁ¡À¸·ÎºÎÅÍ ÃÖ´ëÇÑ ¸Ö¸® ¶³¾îÁø Á¡À» Ã£´Â´Ù.(ÁÖÀÇ : ¿ø°Å¸®´Â ¼Óµµ°¡ »¡¶ó¾ß ÇÑ´Ù...¾È±×·¯¸é °è¼Ó °Å¸®¸¦ À¯ÁöÇÏ´Ù Á×´Â¼ö°¡ ÀÖ´Ù.)
//
BOOL CNpc::GetBackPoint(int &x, int &y)
{
	int ex = m_sCurX;
	int ey = m_sCurY;

	int dx = m_Target.x - m_sCurX;
	int dy = m_Target.y - m_sCurY;

	int min = ( abs(dx) + abs(dy) )/2;
	int max = m_byRange - min;
	int count = myrand(min, max);

	if(count <= 0) return FALSE;							// 0ÀÌ¸é ¿ø·¡ »çÁ¤°Å¸®¿Í °°´Ù.
	if(count >= m_byRange && count > 2) count -= 1;			// È¤½Ã³ª ¸ô¶ó¼­ ÃÖ´ëÇÑ ¾ïÁ¦ÇÑ´Ù.

	if(dy > 0)
	{
		if(dx > 0)		{ ex -= count; ey -= count; }
		else if(dx < 0)	{ ex += count; ey -= count; }
		else			{ ey -= (count*2); }				// È¦¼ö, Â¦¼ö¸¦ ¸ÂÃá´Ù.
	}
	else if(dy < 0)
	{
		if(dx > 0)		{ ex -= count; ey += count; }
		else if(dx < 0)	{ ex += count; ey += count; }
		else			{ ey += (count*2); }
	}
	else
	{
		if(dx > 0)		{ ex -= (count*2); }
		else			{ ex += (count*2); }
	}

	if(IsMovable(ex, ey) == FALSE)							// Ã£Àº Á¡ÀÌ ¿òÁú¼ö ¾ø´Â °÷ÀÌ¶ó¸é 8¹æÇâÀ¸·Î Å½»ö
	{
		for(int i = 0; i < (sizeof(surround_x) / sizeof(surround_x[0])); i++)		// ÁÖº¯ 8¹æÇâ
		{
			if(IsMovable(ex + surround_x[i], ey + surround_y[i])) 
			{
				x = ex; y = ey;
				return TRUE;
			}
		}
	}
	else
	{
		x = ex; y = ey;
		return TRUE;
	}

	return FALSE;									
}

/////////////////////////////////////////////////////////////////////////////
//	À¯Àú¸®½ºÆ®¸¦ ÃÊ±âÈ­ÇÑ´Ù.
//
void CNpc::InitUserList()
{
	m_TotalDamage = 0;
	for(int i = 0; i < NPC_HAVE_USER_LIST; i++)
	{
		m_DamagedUserList[i].bIs = FALSE;
		m_DamagedUserList[i].iUid = -1;
		m_DamagedUserList[i].nDamage = 0;
		::ZeroMemory(m_DamagedUserList[i].strUserID, sizeof(m_DamagedUserList[i].strUserID));
	}
/*	int i;
									// °æÇèÄ¡ ºÐ¹è¸¦ À§ÇØ °ü¸®ÇÏ´ø ¸®½ºÆ®
	for(i = 0; i < m_arDamagedUserList.GetSize(); i++)
	{
		if(m_arDamagedUserList[i])
		{
			delete m_arDamagedUserList[i];
			m_arDamagedUserList[i] = NULL;
		}
	}
	m_arDamagedUserList.RemoveAll();
*/
}

/////////////////////////////////////////////////////////////////////////////
//	ÇØ´ç ¸ÅÁ÷ ¼Ó¼ºÀÌ ¾ÆÀÌÅÛ °è¿­ ¹× ¿þ¾îÁ¤º¸°¡ ¸Â´ÂÁö Ã¼Å©ÇÑ´Ù.
//
BOOL CNpc::CheckClassItem(int artable, int armagic)
{
	if(artable < 0 || artable >= g_arItemTable.GetSize()) return FALSE;
	if(armagic < 0 || armagic >= g_arMagicItemTable.GetSize()) return FALSE;
	if(armagic==148||armagic==149||armagic==150||armagic==151||armagic==152||armagic==153||armagic==156|| armagic==158 || armagic==162||armagic==164 || armagic==166){
		return FALSE;
	}
	int iWear;

	BYTE armWear = g_arItemTable[artable]->m_byWear;			// ¾ÆÀÌÅÛ °è¿­ 1: ¹«±â 2~8 : Âø¿ë¾ÆÀÌÅÛ
	BYTE tNeedClass = g_arItemTable[artable]->m_byClass;
	BYTE armMagic = g_arMagicItemTable[armagic]->m_tNeedClass;	// ¸ÅÁ÷¼Ó¼º °è¿­

	if(armMagic != 15)
	{
		BYTE tTemp = 1;	
		BYTE tFire = 0;
		BYTE tEdge = 0;
		BYTE tStaff = 0;
		BYTE tBrawl = 0;

		tFire	 = tTemp & tNeedClass; tTemp = 2; 
		tEdge	 = tTemp & tNeedClass; tTemp = 4;
		tStaff	 = tTemp & tNeedClass; tTemp = 8;
		tBrawl	 = tTemp & tNeedClass;

		tFire = tFire & armMagic;
		tEdge = tEdge & armMagic;
		tStaff = tStaff & armMagic;
		tBrawl = tBrawl & armMagic;

		tTemp = tFire^tEdge^tStaff^tBrawl;
		if(!tTemp) return FALSE;
//		if(tNeedClass != armMagic) return FALSE;
	}

	iWear = g_arMagicItemTable[armagic]->m_tWearInfo;		// ¿þ¾î Á¤º¸·Î Àß¸øµÈ ¼Ó¼ºÀÌ ºÙ´Â°ÍÀ» ¹æÁö

	if(iWear == 0) return TRUE;
	else if(iWear == 1)											
	{														// 1¹øÀÌ¸é ¹«±â·ù¿¡ ºÙ´Â´Ù.
		if(armWear != 1) return FALSE;
		else return TRUE;
	}
	else if(iWear == 2)										// 2¹øÀÌ¸é ¹«±â¸¦ Á¦¿ÜÇÑ Âø¿ë¾ÆÀÌÅÛ¿¡ ºÙ´Â´Ù.
	{
		if(armWear <= 1 || armWear >= 9) return FALSE;
		else return TRUE;
	}
	else return FALSE;
}

void CNpc::DeleteNPC()
{
	// Áö±Ý ¸ó½ºÅÍ¸¦ Áö¿ìÁö ¾Ê´Â´Ù. ´ÜÁö, ¾²·¹µå »ó¿¡¼­ µ¹Áö ¸øÇÏµµ·Ï ¸·±â¸¸ ÇÑ´Ù.
	m_bFirstLive = FALSE;
	m_tNpcType = 2;

	// ³ªÁß¿¡ ±â·ÏÇÏÀÚ.
}

//////////////////////////////////////////////////////////////////////////////////
//	ÃÖÁ¾ µ¥¹ÌÁö¸¦ ±¸ÇÑ´Ù.
//
int CNpc::GetFinalDamage(USER *pUser, int type)
{
	if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) return 0;

	int iInitDamage = GetNormalInitDamage();
	int iFinalDamage = 0, iFinalTemp = 0;
	
//	int iBasic = (int)((double)(pUser->m_sCON + pUser->m_DynamicUserData[MAGIC_CON_UP])/3 + 0.5);					// ±âº»¸äÁý
	int iBasic = (int)((double)(pUser->m_sMagicCON + pUser->m_DynamicUserData[MAGIC_CON_UP] + (int)((double)pUser->m_DynamicEBodyData[EBODY_CON_TO_DEFENSE] / 100 * (double)pUser->m_sMagicCON) )/3 + 0.5);				// ±âº»¸äÁý
	if(iBasic < 0) iBasic = 0;

	BYTE tWeaponClass = 255;
	BOOL bCanUseSkill = pUser->IsCanUseWeaponSkill(tWeaponClass);

	int		iDefense = 1;
	double	dIron = 0;
	double	dShield = 0;
	double	dGuard = 0;
	int		iCAttack = 0;
	double	dAdamantine = 0;
	double	dDefenseUP = 0;
	double	dABDefense = 0;

	int		iIronLevel = 0;
	int		iGuardLevel = 0;
	int		iVitalLevel = 0;
	int		iCounterAttackLevel = 0;
	int		iDefenseUPLevel = 0;
	int		iABDefenseLevel = 0;

	int		iIS = 0;
	int		iCA = 0;

	int i = 0;
	int iRandom = 0;
	int iSkillSid = 0;
	int tClass = tWeaponClass * SKILL_NUM;

	iDefense = pUser->GetDefense();							// ¹æ¾î±¸

	if(tWeaponClass != 255)
	{
		for(i = tClass; i < tClass + SKILL_NUM; i++)	// IronSkill
		{
			iSkillSid = pUser->m_UserSkill[i].sSid;

			if(iSkillSid == SKILL_IRON)					// 1 index
			{
				iIronLevel = pUser->m_UserSkill[i].tLevel;
				if(iIronLevel < 0) iIronLevel = 0;
				
				// ¾ÆÀÌÅÛ¿¡ ÀÇÇÑ ½ºÅ³ º¯µ¿ ·¹º§
				if(iIronLevel >= 1) iIronLevel += pUser->m_DynamicUserData[g_DynamicSkillInfo[iSkillSid]]+ pUser->m_DynamicUserData[MAGIC_ALL_SKILL_UP];
				
				if(iIronLevel >= SKILL_LEVEL) iIronLevel = SKILL_LEVEL - 1;
				if(iSkillSid >= g_arSkillTable.GetSize()) continue;

				iRandom = (int)((double)XdY(1, 1000) / 10 + 0.5);
				if(iRandom < g_arSkillTable[iSkillSid]->m_arSuccess.GetAt(iIronLevel)) iIS = 1;
				
				// ¾ÆÀÌ¾ð½ºÅ²¿¡ ÀÇÇÑ ±âº» ¸äÁýÀÇ Áõ°¡
				iBasic = (int)((double)iBasic * (1 + (double)(iIS * g_arSkillTable[iSkillSid]->m_arInc.GetAt(iIronLevel) / 100)) );
			}

			if(iSkillSid == SKILL_CRITICAL_GUARD)					// Critical Guard 11 index
			{
				iGuardLevel = pUser->m_UserSkill[i].tLevel;		
				if(iGuardLevel < 0) iGuardLevel = 0;
				
				// ¾ÆÀÌÅÛ¿¡ ÀÇÇÑ ½ºÅ³ º¯µ¿ ·¹º§
				if(iGuardLevel >= 1) iGuardLevel += pUser->m_DynamicUserData[g_DynamicSkillInfo[iSkillSid]]+ pUser->m_DynamicUserData[MAGIC_ALL_SKILL_UP];
				
				if(iGuardLevel >= SKILL_LEVEL) iGuardLevel = SKILL_LEVEL - 1;
				if(iSkillSid >= g_arSkillTable.GetSize()) continue;
				
				iRandom = (int)((double)XdY(1, 1000) / 10 + 0.5);
				if(iRandom < g_arSkillTable[iSkillSid]->m_arSuccess.GetAt(iGuardLevel))
				{				
					dGuard = (double)(iInitDamage *g_arSkillTable[iSkillSid]->m_arInc.GetAt(iGuardLevel))/100.0;
				}
			}

			if(iSkillSid == SKILL_BACK_ATTACK)					// ¹Ý°Ý 2 index
			{
				iCounterAttackLevel = pUser->m_UserSkill[i].tLevel;		
				if(iCounterAttackLevel < 0) iCounterAttackLevel = 0;
				
				// ¾ÆÀÌÅÛ¿¡ ÀÇÇÑ ½ºÅ³ º¯µ¿ ·¹º§
				if(iCounterAttackLevel >= 1) iCounterAttackLevel += pUser->m_DynamicUserData[g_DynamicSkillInfo[iSkillSid]] + pUser->m_DynamicUserData[MAGIC_ALL_SKILL_UP];
				
				if(iCounterAttackLevel >= SKILL_LEVEL) iCounterAttackLevel = SKILL_LEVEL - 1;
				if(iSkillSid >= g_arSkillTable.GetSize()) continue;
				
				if(pUser->GetDistance(m_sCurX, m_sCurY, 1) == FALSE) iCA = 0;//m_byRange > 1) iCA = 0;
				else
				{
					iRandom = (int)((double)XdY(1, 1000) / 10 + 0.5);
					if(iRandom < g_arSkillTable[iSkillSid]->m_arSuccess.GetAt(iCounterAttackLevel)) iCA = 1;
				}
				
				iCAttack = (int)(iInitDamage * iCA * (double)g_arSkillTable[iSkillSid]->m_arInc.GetAt(iCounterAttackLevel) / 100.0);
			}

			if(iSkillSid == SKILL_ABSOLUTE_DEFENSE)					// Absolute Defense
			{
				iABDefenseLevel = pUser->m_UserSkill[i].tLevel;		
				if(iABDefenseLevel < 0) iABDefenseLevel = 0;
				
				// ¾ÆÀÌÅÛ¿¡ ÀÇÇÑ ½ºÅ³ º¯µ¿ ·¹º§
				if(iABDefenseLevel >= 1) iABDefenseLevel += pUser->m_DynamicUserData[MAGIC_ALL_SKILL_UP];
				
				if(iABDefenseLevel >= SKILL_LEVEL) iABDefenseLevel = SKILL_LEVEL - 1;
				if(iSkillSid >= g_arSkillTable.GetSize()) continue;
				
				iRandom = (int)((double)XdY(1, 1000) / 10 + 0.5);
				if(iRandom < g_arSkillTable[iSkillSid]->m_arSuccess.GetAt(iABDefenseLevel))
				{
					dABDefense = (double)(iDefense * (double)g_arSkillTable[iSkillSid]->m_arInc.GetAt(iABDefenseLevel)/100.0);
				}
			}
			if(iSkillSid == SKILL_DEFENSE_UP)					// Defense up
			{
				iDefenseUPLevel = pUser->m_UserSkill[i].tLevel;		
				if(iDefenseUPLevel < 0) iDefenseUPLevel = 0;
				
				// ¾ÆÀÌÅÛ¿¡ ÀÇÇÑ ½ºÅ³ º¯µ¿ ·¹º§
				if(iDefenseUPLevel >= 1) iDefenseUPLevel += pUser->m_DynamicUserData[MAGIC_ALL_SKILL_UP];
				
				if(iDefenseUPLevel >= SKILL_LEVEL) iDefenseUPLevel = SKILL_LEVEL - 1;
				if(iSkillSid >= g_arSkillTable.GetSize()) continue;
				
				iRandom = (int)((double)XdY(1, 1000) / 10 + 0.5);
				if(iRandom < g_arSkillTable[iSkillSid]->m_arSuccess.GetAt(iDefenseUPLevel))
				{
					dDefenseUP = (double)(iDefense * (double)g_arSkillTable[iSkillSid]->m_arInc.GetAt(iDefenseUPLevel)/100.0);
				}
			}
		}
	}

//	if(pUser->m_dwShieldTime != 0)	dShield = (double)(iInitDamage * 0.2);
	if(pUser->m_bNecklaceOfShield && pUser->m_dwShieldTime != 0)		dShield = (double)(iInitDamage * 0.3);
	else if(pUser->m_bNecklaceOfShield && pUser->m_dwBigShieldTime != 0)	dShield = (double)(iInitDamage * 0.35);
	else if(pUser->m_bNecklaceOfShield || pUser->m_dwShieldTime != 0 )	dShield = (double)(iInitDamage * 0.2);
    else if(pUser->m_dwBigShieldTime !=0 && !pUser->m_bNecklaceOfShield ) dShield = (double)(iInitDamage * 0.25);
	if(pUser->m_bNecklaceOfShield) pUser->SendAccessoriDuration(SID_NECKLACE_OF_SHIELD);

	if( pUser->m_dwAdamantineTime != 0 )
	{
		dAdamantine = (double)( (double)iDefense * 0.1 );
	}

	iDefense = (int)( iDefense + dABDefense + dDefenseUP + dAdamantine );

	iFinalDamage = (int)(iInitDamage - (iDefense + iBasic + dShield + dGuard)); 

	if(iFinalDamage < 0) iFinalDamage = 0;
	if(iFinalDamage <= 15)
	{
		iFinalTemp = iFinalDamage;
		iFinalDamage += (int)((double)iInitDamage * 0.2 + 1.5);	// ÃÖ¼Ò´ë¹ÌÁö¸¦ ÃÖ´ë 15À¸·Î ÇÑ´Ù.
		if(iFinalDamage > 15) iFinalDamage = 15;
		iFinalDamage = max(iFinalDamage, iFinalTemp);
	}

	if(pUser->m_tAbnormalKind == ABNORMAL_BYTE_COLD) iFinalDamage += 10;

	if(iCAttack > 0 && type) 
	{
		iCA = iCAttack;		// ÃÖÁ¾ ¹Ý°Ý µ¥¹ÌÁö

		if(iCA > 0)			// ¹Ý°ÝÀÌ 0º¸´Ù Å¬¶§ À¯Àú ¸®½ºÆ®¿¡ ´õÇÏ°í ºÐ¹è...
		{
//			pUser->SetCounterAttack(m_sNid, iCA);
			
			// alisia
			int iDamage = iCA;

			if( pUser->GetDistance(m_sCurX, m_sCurY, 2) )
			{
				if( SetDamage(iDamage, (pUser->m_uid) + USER_BAND, pUser->m_pCom) == FALSE )
				{
					SendExpToUserList( pUser->m_pCom ); // °æÇèÄ¡ ºÐ¹è!!
					SendDead( pUser->m_pCom );

					if( m_NpcVirtualState == NPC_STANDING )
					{
						CheckMaxValue( pUser->m_dwXP, 1);	// ¸÷ÀÌ Á×À»¶§¸¸ 1 Áõ°¡!	
						pUser->SendXP();
					}
				}
			}

		}
	}

	return iFinalDamage;
}

///////////////////////////////////////////////////////////////////////////////////////
//	NPC Á¤º¸¸¦ ¹öÆÛ¿¡ ÀúÀåÇÑ´Ù.
//
void CNpc::FillNpcInfo(char *temp_send, int &index, BYTE flag)
{
	CPoint t;

	SetByte(temp_send, NPC_INFO, index );
	SetByte(temp_send, flag, index );
	SetShort(temp_send, m_sNid+NPC_BAND, index );

	if(flag != INFO_MODIFY)	return;

	SetShort(temp_send, m_sPid, index);
	SetVarString(temp_send, m_strName, _tcslen(m_strName), index);

	t = ConvertToClient(m_sCurX, m_sCurY);
	
	SetShort(temp_send, t.x, index);
	SetShort(temp_send, t.y, index);

	if(m_sHP <= 0) SetByte(temp_send, 0x00, index);
	else SetByte(temp_send, 0x01, index);

	SetByte(temp_send, m_tNpcType, index);
	SetShort(temp_send, m_sMaxHP, index);
	SetShort(temp_send, m_sHP, index);
	SetByte(temp_send , 0x00, index);
	SetByte(temp_send , 0x00, index);
	SetByte(temp_send , 0x00, index);
	SetByte(temp_send , 0x00, index);
	SetByte(temp_send , 0x00, index);
	SetByte(temp_send , 0x00, index);
	SetByte(temp_send , 0x00, index);
	SetByte(temp_send , 0x00, index);
	SetShort(temp_send, m_sClientSpeed, index);

	SetByte(temp_send, m_byColor, index);

	if(m_tNpcType == NPCTYPE_GUILD_DOOR) 
	{
		SetShort(temp_send, m_sDimension, index);
	}
	SetShort(temp_send, m_sQuestSay, index);
}

///////////////////////////////////////////////////////////////////////////////////////
//	¼­¹öÁÂÇ¥¸¦ Å¬¶óÀÌ¾ðÆ® ÁÂÇ¥·Î ¹Ù²Û´Ù.
//
CPoint CNpc::ConvertToClient(int x, int y)
{
	if(!g_zone[m_ZoneIndex]) return CPoint(-1,-1);

	int tempx, tempy;
	int temph = g_zone[m_ZoneIndex]->m_vMoveCell.m_vDim.cy / 2 - 1;

	if( y >= g_zone[m_ZoneIndex]->m_sizeMap.cy || x >= g_zone[m_ZoneIndex]->m_sizeMap.cx ) return CPoint(-1,-1);

	tempx = x - temph + y;
	tempy = y - x + temph;

	return CPoint( tempx, tempy );
}

//////////////////////////////////////////////////////////////////////////////////////////
//	ÀÏÁ¤ ¿µ¿ªÀÇ À¯Àú¿¡°Ô µ¥ÀÌÅÍ¸¦ º¸³½´Ù.
//
void CNpc::SendToRange(COM *pCom, char *temp_send, int index, int min_x, int min_y, int max_x, int max_y)
{
/*
	if( index <= 0 || index >= SEND_BUF_SIZE ) return;

	SEND_DATA* pNewData = NULL;
	pNewData = new SEND_DATA;

	if( !pNewData ) return;

	pNewData->flag = SEND_RANGE;
	pNewData->len = index;

	::CopyMemory( pNewData->pBuf, temp_send, index );

	pNewData->uid = 0;
	pNewData->z = m_sCurZ;
	pNewData->rect.left		= min_x;
	pNewData->rect.right	= max_x;
	pNewData->rect.top		= min_y;
	pNewData->rect.bottom	= max_y;
	pNewData->zone_index = m_ZoneIndex;

	EnterCriticalSection( &(pCom->m_critSendData) );

	pCom->m_arSendData.Add( pNewData );

	LeaveCriticalSection( &(pCom->m_critSendData) );

	PostQueuedCompletionStatus( pCom->m_hSendIOCP, 0, 0, NULL );
*/

	if( index <= 0 || index >= SEND_BUF_SIZE ) return;

	MAP* pMap = g_zone[m_ZoneIndex];
	if( !pMap ) return;
	
	int tmin_x = min_x;		if(tmin_x < 0 ) tmin_x = 0;
	int tmax_x = max_x;		if(tmax_x >= pMap->m_sizeMap.cx ) tmax_x = pMap->m_sizeMap.cx - 1;
	int tmin_y = min_y;		if(tmin_y < 0 ) tmin_y = 0;
	int tmax_y = max_y;		if(tmax_y >= pMap->m_sizeMap.cy ) tmax_y = pMap->m_sizeMap.cy - 1;

	int temp_uid;
	USER* pUser = NULL;

	for( int i = tmin_x; i < tmax_x; i++ )
	{
		for( int j = tmin_y; j < tmax_y; j++ )
		{
			temp_uid = pMap->m_pMap[i][j].m_lUser;

			if(temp_uid < USER_BAND || temp_uid >= NPC_BAND) continue;
			else temp_uid -= USER_BAND;

			if( temp_uid >= 0 && temp_uid < MAX_USER )
			{
				pUser = pCom->GetUserUid(temp_uid);
				if ( pUser == NULL ) continue;
				
				if( pUser->m_state == STATE_GAMESTARTED )
				{
					if( pUser->m_curx == i && pUser->m_cury == j && pUser->m_curz == m_sCurZ )
					{
						Send( pUser, temp_send, index);
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//	°ø°Ý´ë»ó(Target)À» ÃÊ±âÈ­ ÇÑ´Ù.
//
inline void CNpc::InitTarget()
{
	m_Target.id = -1;
	m_Target.x = 0;
	m_Target.y = 0;
	m_Target.failCount = 0;
//	m_Target.nLen = 0; 
//	::ZeroMemory(m_Target.szName, sizeof(m_Target.szName));
}

/////////////////////////////////////////////////////////////////////////////////////////
//	PathFind ¸¦ ¼öÇàÇÑ´Ù.
//
BOOL CNpc::PathFind(CPoint start, CPoint end)
{
	m_bRandMove = FALSE;

	if(start.x < 0 || start.y < 0 || end.x < 0 || end.y < 0)
	{
		return FALSE;
	}

	int i, j;

	int min_x, max_x;
	int min_y, max_y;

	min_x = m_min_x;
	min_y = m_min_y;
	max_x = m_max_x;
	max_y = m_max_y;

	if(InterlockedCompareExchange((LONG*)&m_lMapUsed, (long)1, (long)0) == (long)0)
	{
		ClearPathFindData();

		m_vMapSize.cx = max_x - min_x + 1;		
		m_vMapSize.cy = max_y - min_y + 1;

	
/*		m_pMap = new int*[m_vMapSize.cx];

		for(i = 0; i < m_vMapSize.cx; i++)
		{
			m_pMap[i] = new int[m_vMapSize.cy];
		}
*/
		for(i = 0; i < m_vMapSize.cy; i++)
		{
			for(j = 0; j < m_vMapSize.cx; j++)
			{
				if( min_x+j == m_sCurX && min_y+i == m_sCurY )
				{
					m_pMap[j*m_vMapSize.cy + i] = 0;
//					m_pMap[j][i] = 0;
				}
				else
				{
					if(m_pOrgMap[min_x + j][min_y + i].m_bMove || m_pOrgMap[min_x + j][min_y + i].m_lUser != 0 )
					{
//						m_pMap[j][i] = 1;
						m_pMap[j*m_vMapSize.cy + i] = 1;
					}
					else
					{
//						m_pMap[j][i] = 0;
						m_pMap[j*m_vMapSize.cy + i] = 0;
					}
				}
			}
		}

		m_vStartPoint  = start;		m_vEndPoint = end;
		m_pPath = NULL;
		m_vPathFind.SetMap(m_vMapSize.cx, m_vMapSize.cy, m_pMap);

		m_pPath = m_vPathFind.FindPath(end.x, end.y, start.x, start.y);

		::InterlockedExchange(&m_lMapUsed, 0);

		if(m_pPath)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else return FALSE; 

}

/////////////////////////////////////////////////////////////////////////////
//	ÆÐ½º ÆÄÀÎµå¿¡¼­ Ã£Àº °æ·Î¸¦ ´Ù ÀÌµ¿ Çß´ÂÁö Ã¼Å©
//
BOOL CNpc::IsStepEnd()
{
	if( !m_pPath )	return FALSE;

	if( m_NpcState != NPC_MOVING && m_NpcState != NPC_TRACING ) return FALSE;

	if( !m_pPath->Parent )	return TRUE;

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//	NPC ±âº»Á¤º¸ ÃÊ±âÈ­
//
void CNpc::Init()
{		
	int i, j;
	m_dLastFind = GetTickCount();
	m_Delay = 0;
	m_dwLastThreadTime = GetTickCount();

	if((m_sOrgX + m_sOrgY) % 2 != 0) m_sOrgX++;
	CPoint pt = ConvertToServer(m_sOrgX, m_sOrgY);

	if(pt.x == -1 || pt.y == -1)
	{
		CString szTemp;
		szTemp.Format(_T("Invalid NPC AXIS : Name = %s, x = %d, y = %d"), m_strName, m_sOrgX, m_sOrgY);
		AfxMessageBox(szTemp);
		InterlockedIncrement(&g_CurrentNPCError);
	}
	else
	{
		m_sTableOrgX = m_sOrgX = pt.x;
		m_sTableOrgY = m_sOrgY = pt.y;

		m_NpcVirtualState = NPC_STANDING;
		
		if(m_sGuild >= NPC_GUILDHOUSE_BAND)			// µµ½Ã¸¦ ±âÁØÀ¸·Î 0¹ø µµ½Ã, 1, 2 ÀÌ·±½ÄÀ¸·Î ÁøÇà m_sGuild = 10000(Ã³À½)
		{											// 0¹øµµ½Ã = »ç³ªµå 1¹øµµ½Ã = Æ÷Æ®½Ã... ÀÌ°Ç 10000¹ø´ëÀÓ
			int index = 0;
			index = GetCityNumForVirtualRoom(m_sCurZ);
			
			if(index >= 0) g_arGuildHouseWar[index]->m_CurrentGuild.arNpcList.Add(m_sNid);

			m_NpcVirtualState = NPC_WAIT;
		}
		else if(m_tNpcType == NPCTYPE_MONSTER && m_sGuild >= FORTRESS_BAND && m_sGuild < NPC_GUILDHOUSE_BAND)	// ÀÌ°Ç 1000¹ø´ëÀÓ
		{
			for(i = 0; i < g_arGuildFortress.GetSize(); i++)
			{
				if(!g_arGuildFortress[i]) continue;

				if(g_arGuildFortress[i]->m_sFortressID == (short)(m_sGuild))
				{
					g_arGuildFortress[i]->m_arViolenceNpcList.Add(m_sNid);

					m_NpcVirtualState = NPC_WAIT;

//					m_pGuardFortress = g_arGuildFortress[i];
					break;
				}
			}			
		}

		switch(m_tNpcType)
		{
		case NPCTYPE_GUILD_GUARD: case NPCTYPE_GUILD_NPC:
			{
				if(m_sGuild < FORTRESS_BAND)				// »óÁ¡¿¡ ¼ÓÇÑ °æºñº´ÀÌ¸é
				{
					CStore *pStore = NULL;
					for(i = 0; i < g_arStore.GetSize(); i++)
					{
						if(g_arStore[i] == NULL) continue;

						pStore = g_arStore[i];					// »óÁ¡ Æ÷ÀÎÅÍ¸¦ ¾ò¾î¿Â´Ù.(±æµåÀü¿¡¼­ ¾²±âÀ§ÇØ)
						if(pStore->m_sStoreID == (short)m_sGuild) 
						{	
							pStore->m_arNpcList.Add(m_sNid);	// ³» ¾ÆÀÌµð¸¦ »óÁ¡¿¡ µî·ÏÇÑ´Ù.
							m_pGuardStore = pStore;	
							break; 
						}
					}
				}
				else											// ¿ä»õ¿¡ ¼ÓÇÑ NPCÀÌ¸é...
				{
					for(i = 0; i < g_arGuildFortress.GetSize(); i++)
					{
						if(!g_arGuildFortress[i]) continue;

						if(g_arGuildFortress[i]->m_sFortressID == (short)(m_sGuild))
						{
							if(m_sEZone >= GUILD_FORTRESS_NPC_BAND)
							{
								for(j = 0; j < FORTRESS_TARGET_MAX_NUM; j++)
								{
									if(InterlockedCompareExchange((long*)&g_arGuildFortress[i]->m_arFortressTarget[j].lUsed, (long)1, (long)0) == (long)0)
									{
										g_arGuildFortress[i]->m_arFortressTarget[j].sTargertID = m_sNid;
										break;
									}
								}
							}
							else if(m_sEZone < GUILD_FORTRESS_NPC_BAND && m_sEZone >= GUILD_REPAIR_NPC_BAND)	// ¼ö¸®µÉ¼ö ÀÖ´Â ¹®, ±¤¼±Æ÷ 
							{
								g_arGuildFortress[i]->m_arRepairNpcList.Add(m_sNid);
							}

							g_arGuildFortress[i]->m_arNpcList.Add(m_sNid);

							m_pGuardFortress = g_arGuildFortress[i];
							break;
						}
					}
				}
			}
			break;

		case NPCTYPE_GUILD_MARK:
			{
				if(m_sGuild >= 0 && m_sGuild < g_arGuildData.GetSize())
				{
					m_sPid = g_arGuildHouse[m_sGuild]->iGuild;		
					g_arGuildHouse[m_sGuild]->iMarkNpc = m_sNid;
					::ZeroMemory(m_strName, sizeof(m_strName));
				
					if( m_sPid >= 0 && m_sPid < g_arGuildData.GetSize())
					{										// ±æµå¿¡ µ¿±âÈ­¸¦ ÇÒÇÊ¿ä°¡ ¾ø´Ù.
						if(g_arGuildData[m_sPid])
						{
							int nLen = 0;
							
							m_sMaxHP = g_arGuildData[m_sPid]->m_sVersion;
							nLen = strlen(g_arGuildData[m_sPid]->m_strGuildName);
							if(nLen > 0)
							{							
								strncpy(m_strName, g_arGuildData[m_sPid]->m_strGuildName, nLen);
							}
						}
					}				
				}
			}
			break;

		case NPCTYPE_GUILD_DOOR:
			{
				for(i = 0; i < g_arGuildFortress.GetSize(); i++)
				{
					if(!g_arGuildFortress[i]) continue;

					if(g_arGuildFortress[i]->m_sFortressID == (short)(m_sGuild))
					{
						if(m_sEZone < GUILD_FORTRESS_NPC_BAND && m_sEZone >= GUILD_REPAIR_NPC_BAND)	// ¼ö¸®µÉ¼ö ÀÖ´Â ¹®, ±¤¼±Æ÷ 
						{
							g_arGuildFortress[i]->m_arRepairNpcList.Add(m_sNid);
						}

						g_arGuildFortress[i]->m_arNpcList.Add(m_sNid);

						m_pGuardFortress = g_arGuildFortress[i];
						break;
					}
				}
			}
/*
		case NPCTYPE_FORTRESS:
			{
				for(i = 0; i < g_arGuildFortress.GetSize(); i++)
				{
					if(!g_arGuildFortress[i]) continue;

					if(g_arGuildFortress[i]->m_sFortressID == (short)(m_sGuild))
					{
						for(j = 0; j < FORTRESS_TARGET_MAX_NUM; j++)
						{
							if(InterlockedCompareExchange(&g_arGuildFortress[i]->m_arFortressTarget[j].lUsed, (LONG)1, (LONG)0) == 0)
							{
								g_arGuildFortress[i]->m_arFortressTarget[j].bChange = FALSE;
								g_arGuildFortress[i]->m_arFortressTarget[j].sTargertID = m_sNid;
								m_pGuardFortress = g_arGuildFortress[i];
								break;
							}
						}
					}
				}
			}
			break;
/*
		case NPCTYPE_REPAIR_GUARD:
			{
				for(i = 0; i < g_arGuildFortress.GetSize(); i++)
				{
					if(!g_arGuildFortress[i]) continue;

					if(g_arGuildFortress[i]->m_sFortressID == (short)(m_sGuild))
					{
						g_arGuildFortress[i]->m_arRepairNpcList.Add(m_sNid);
						m_pGuardFortress = g_arGuildFortress[i];
						break;
					}
				}
			}
			break;
*/		}
/*
	else
	{
		m_sOrgX = pt.x;
		m_sOrgY = pt.y;

		m_NpcVirtualState = NPC_STANDING;

		if(m_sGuild >= NPC_GUILDHOUSE_BAND)			// µµ½Ã¸¦ ±âÁØÀ¸·Î 0¹ø µµ½Ã, 1, 2 ÀÌ·±½ÄÀ¸·Î ÁøÇà m_sGuild = 10000(Ã³À½)
		{											// 0¹øµµ½Ã = »ç³ªµå 1¹øµµ½Ã = Æ÷Æ®½Ã...
			int index = 0;
			index = GetCityNumForVirtualRoom(m_sCurZ);
			
			g_arGuildHouseWar[index]->m_CurrentGuild.arNpcList.Add(m_sNid);

			m_NpcVirtualState = NPC_WAIT;
		}		
		else if(m_tNpcType == NPCTYPE_GUILD_GUARD || m_tNpcType == NPCTYPE_GUILD_NPC)
		{
			if(m_sGuild < FORTRESS_BAND)				// »óÁ¡¿¡ ¼ÓÇÑ °æºñº´ÀÌ¸é
			{
				CStore *pStore = NULL;
				for(i = 0; i < g_arStore.GetSize(); i++)
				{
					if(g_arStore[i] == NULL) continue;

					pStore = g_arStore[i];					// »óÁ¡ Æ÷ÀÎÅÍ¸¦ ¾ò¾î¿Â´Ù.(±æµåÀü¿¡¼­ ¾²±âÀ§ÇØ)
					if(pStore->m_sStoreID == (short)m_sGuild) 
					{	
						pStore->m_arNpcList.Add(m_sNid);	// ³» ¾ÆÀÌµð¸¦ »óÁ¡¿¡ µî·ÏÇÑ´Ù.
						m_pGuardStore = pStore;	
						break; 
					}
				}
			}
			else											// ¿ä»õ¿¡ ¼ÓÇÑ NPCÀÌ¸é...
			{
				for(i = 0; i < g_arGuildFortress.GetSize(); i++)
				{
					if(!g_arGuildFortress[i]) continue;

					if(g_arGuildFortress[i]->m_sFortressID == (short)(m_sGuild))
					{
						g_arGuildFortress[i]->m_arNpcList.Add(m_sNid);
						m_pGuardFortress = g_arGuildFortress[i];
						break;
					}
				}
			}
		}
		else if(m_tNpcType == NPCTYPE_GUILD_MARK)
		{
			if(m_sGuild >= 0 && m_sGuild < g_arGuildData.GetSize())
			{
				m_sPid = g_arGuildHouse[m_sGuild]->iGuild;		
				g_arGuildHouse[m_sGuild]->iMarkNpc = m_sNid;
				::ZeroMemory(m_strName, sizeof(m_strName));
			
				if( m_sPid >= 0 && m_sPid < g_arGuildData.GetSize())
				{										// ±æµå¿¡ µ¿±âÈ­¸¦ ÇÒÇÊ¿ä°¡ ¾ø´Ù.
					if(g_arGuildData[m_sPid])
					{
						int nLen = 0;
						
						m_sMaxHP = g_arGuildData[m_sPid]->m_sVersion;
						nLen = strlen(g_arGuildData[m_sPid]->m_strGuildName);
						if(nLen > 0)
						{							
							strncpy(m_strName, g_arGuildData[m_sPid]->m_strGuildName, nLen);
						}
					}
				}				
			}
		}
		else if(m_tNpcType == NPCTYPE_FORTRESS)
		{
			for(i = 0; i < g_arGuildFortress.GetSize(); i++)
			{
				if(!g_arGuildFortress[i]) continue;

				if(g_arGuildFortress[i]->m_sFortressID == (short)(m_sGuild))
				{
					for(j = 0; j < FORTRESS_TARGET_MAX_NUM; j++)
					{
						if(InterlockedCompareExchange(&g_arGuildFortress[i]->m_arFortressTarget[j].lUsed, (LONG)1, (LONG)0) == 0)
						{
							g_arGuildFortress[i]->m_arFortressTarget[j].bChange = FALSE;
							g_arGuildFortress[i]->m_arFortressTarget[j].sTargertID = m_sNid;
							m_pGuardFortress = g_arGuildFortress[i];
							break;
						}
					}
				}
			}
		}
		else if(m_tNpcType == NPCTYPE_REPAIR_GUARD)
		{
			for(i = 0; i < g_arGuildFortress.GetSize(); i++)
			{
				if(!g_arGuildFortress[i]) continue;

				if(g_arGuildFortress[i]->m_sFortressID == (short)(m_sGuild))
				{
					g_arGuildFortress[i]->m_arRepairNpcList.Add(m_sNid);
					m_pGuardFortress = g_arGuildFortress[i];
					break;
				}
			}
		}
*/	}

	m_pOrgMap = g_zone[m_ZoneIndex]->m_pMap;	// MapInfo Á¤º¸ ¼ÂÆÃ
}

int CNpc::GetCityNumForVirtualRoom(int zone)		// Áö±ÝÀº µµ½Ã¹øÈ£Áö¸¸ ³ªÁß¿¡ VirtualRoomÀÌ °è¼Ó Ãß°¡µÇ¸é..
{													// ¹Ù²Ù¾î¾ß µÈ´Ù. (int zone, int &curGuild)
	int nRet = -1;

	switch(zone)									// Ãß°¡ÇÒ ¿¹Á¤ÀÓ...
	{
	case 1005:										// 1004Á¸ ÀÌ¸é..
		nRet = SANAD;								// µµ½Ã´Â »ç³ªµå, m_CurrentGuild = 0¹øÂ°
		break;

	default:
		break;
	}

	return nRet;
}

////////////////////////////////////////////////////////////////////////////////////
//	Client ÁÂÇ¥¸¦ ¼­¹öÁÂÇ¥·Î º¯È¯ÇÑ´Ù
//
CPoint CNpc::ConvertToServer(int x, int y)
{
	if(!g_zone[m_ZoneIndex]) return CPoint(-1,-1); 

	int tempx, tempy;
	int temph = g_zone[m_ZoneIndex]->m_vMoveCell.m_vDim.cy / 2 - 1;

	if( y >= g_zone[m_ZoneIndex]->m_vMoveCell.m_vDim.cy || x >= g_zone[m_ZoneIndex]->m_vMoveCell.m_vDim.cx ) return CPoint(-1,-1);

	if( (x+y)%2 == 0 )
	{
		tempx = temph - ( y / 2 ) + ( x / 2 );

		if( x % 2 ) tempy = ( y / 2 ) + ( ( x / 2 ) + 1 );
		else        tempy = ( y / 2 ) + ( x / 2 );

		return CPoint( tempx, tempy );
	}
	else return CPoint(-1,-1);
}

////////////////////////////////////////////////////////////////////////////////////
//	µð¹ö±ëÀ» À§ÇØ NPC Á¤º¸¸¦ TRACE ÇÑ´Ù.
//
void CNpc::NpcTrace(TCHAR *pMsg)
{
	if(g_bDebug == FALSE) return;

	CString szMsg = _T("");
	CPoint pt = ConvertToClient(m_sCurX, m_sCurY);
	szMsg.Format(_T("%s : uid = %d, name = %s, xpos = %d, ypos = %d\n"), pMsg, m_sNid, m_strName, pt.x, pt.y);
	TRACE(szMsg);
}

///////////////////////////////////////////////////////////////////////////////////
//	°ø°ÝÀ» ´çÇßÀ»¶§ ÆÐ½ºÆÄÀÎµù¿¡ ½ÇÆÐÇÏ¸é À¯Àú¿¡°Ô °¡±î¿îÂÊÀ¸·Î ¿òÁ÷ÀÎ´Ù.
//
void CNpc::ToTargetMove(COM *pCom, USER *pUser)
{
	if(!pCom) return;
	if(!pUser) return;
	if(!g_zone[m_ZoneIndex]) return;

	int xx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
	int yy[] = {0, -1, -1, -1, 0, 1, 1, 1};

	CPoint ptUser = ConvertToClient(pUser->m_curx, pUser->m_cury);

	struct _min
	{
		int x, y;
		int value;
	}min;

	int minindex;
	int i, j;

	int dx, dy;
	CPoint ptNew;
	int max_dist;
/*
	int test1[8], test2[8];

	for(i = 0; i < 8; i++)
	{
		ptNew = ConvertToClient(m_sCurX + xx[i], m_sCurY + yy[i]);
		dx = abs(ptUser.x - ptNew.x);
		dy = abs(ptUser.y - ptNew.y);
		test1[i] = dx + dy;
	}
*/	
	for(i = 0; i < sizeof(xx)/sizeof(xx[0]) - 1; i++)
	{
		minindex = i;
		
		ptNew = ConvertToClient(m_sCurX + xx[i], m_sCurY + yy[i]);

		if(ptNew.x <= -1 || ptNew.y <= -1) continue;
		if(ptNew.x >= g_zone[m_ZoneIndex]->m_sizeMap.cx || ptNew.y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) continue;

		dx = abs(ptUser.x - ptNew.x);
		dy = abs(ptUser.y - ptNew.y);
		max_dist = dx + dy;

		min.value = max_dist;
		min.x = xx[i];
		min.y = yy[i];

		for(j = i + 1; j < sizeof(xx)/sizeof(xx[0]); j++)
		{
			ptNew = ConvertToClient(m_sCurX + xx[j], m_sCurY + yy[j]);

			if(ptNew.x <= -1 || ptNew.y <= -1) continue;
			if(ptNew.x >= g_zone[m_ZoneIndex]->m_sizeMap.cx || ptNew.y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) continue;

			dx = abs(ptUser.x - ptNew.x);
			dy = abs(ptUser.y - ptNew.y);
			max_dist = dx + dy;

			if(min.value > max_dist)
			{
				min.value = max_dist;
				min.x = xx[j];
				min.y = yy[j];
				minindex = j;
			}
		}

		xx[minindex] = xx[i];
		yy[minindex] = yy[i];

		xx[i] = min.x;
		yy[i] = min.y;
	}
/*
	for(i = 0; i < 8; i++)
	{
		ptNew = ConvertToClient(m_sCurX + xx[i], m_sCurY + yy[i]);
		dx = abs(ptUser.x - ptNew.x);
		dy = abs(ptUser.y - ptNew.y);
		test2[i] = dx + dy;
	}
*/
	MAP* pMap = g_zone[m_ZoneIndex];
	CPoint ptPre(m_sCurX, m_sCurY);
	int will_x, will_y;
	BOOL bMove = FALSE;
	int new_dist = 0, cur_dist = 0;

	CPoint ptCurr = ConvertToClient(m_sCurX, m_sCurY);
	cur_dist = abs(ptUser.x - ptCurr.x) + abs(ptUser.y - ptCurr.y);

	for(i = 0; i < sizeof(xx)/sizeof(xx[0]); i++)
	{
		will_x = m_sCurX + xx[i];
		will_y = m_sCurY + yy[i];

		ptNew = ConvertToClient(m_sCurX + xx[i], m_sCurY + yy[i]);
		new_dist = abs(ptUser.x - ptNew.x) + abs(ptUser.y - ptNew.y);

		if(new_dist > cur_dist) continue;

		if(will_x <= -1 || will_y <= -1) continue;
		if(will_x >= g_zone[m_ZoneIndex]->m_sizeMap.cx || will_y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) continue;

		if(pMap->m_pMap[will_x][will_y].m_bMove != 0 || pMap->m_pMap[will_x][will_y].m_lUser != 0)
		{
			continue;
		}
		else
		{
			if(InterlockedCompareExchange((LONG*)&m_pOrgMap[will_x][will_y].m_lUser,
				(long)m_pOrgMap[m_sCurX][m_sCurY].m_lUser, (long)0) == (long)0)
			{
				::InterlockedExchange(&m_pOrgMap[m_sCurX][m_sCurY].m_lUser, 0);
				m_sCurX = will_x;
				m_sCurY = will_y;
				SightRecalc(pCom);
				bMove = TRUE;
				break;
			}
			else continue;
		}
	}

	if(!bMove) return;

	CBufferEx TempBuf;
	CPoint t = ConvertToClient(m_sCurX, m_sCurY);		// ¿òÁ÷ÀÌ·Á´Â ¼­¹öÁÂÇ¥°¡ Å¬¶óÀÌ¾ðÆ®¿¡¼­ ¸ø¿òÁ÷ÀÌ´Â ÁÂÇ¥¸é ¸®ÅÏ
	if(t.x <= -1 || t.y <= -1) return;

	TempBuf.Add(MOVE_RESULT);

	TempBuf.Add(SUCCESS);
	TempBuf.Add((int)(NPC_BAND + m_sNid));
	TempBuf.Add((short)t.x);
	TempBuf.Add((short)t.y);

	SendInsight(pCom, TempBuf, TempBuf.GetLength());

	m_Delay = m_sSpeed;
}



void CNpc::EventNpcInit(int x, int y)
{
	m_dwLastThreadTime = GetTickCount();

	m_sOrgX = x;
	m_sOrgY = y;

	m_pOrgMap = g_zone[m_ZoneIndex]->m_pMap;	// MapInfo Á¤º¸ ¼ÂÆÃ

	m_Delay = 0;
}

///////////////////////////////////////////////////////////////////////////////////
//	±æµåÀüÀ» À§ÇØ Å¸ÀÔÀ» ¹Ù²Û´Ù. 
//
void CNpc::SetGuildType(COM *pCom)
{
/*	int modify_index = 0;
	char modify_send[2048];	

	::ZeroMemory(modify_send, sizeof(modify_send));

	if(m_tGuildWar == GUILD_WARRING)
	{
		m_tNpcAttType = 1;
		if(m_tNpcType == NPCTYPE_GUARD) m_tNpcType = NPCTYPE_GUILD_GUARD;
		else if(m_tNpcType == NPCTYPE_NPC) m_tNpcType = NPCTYPE_GUILD_NPC;

		// À¯Àú¿¡°Ô NPC Á¤º¸Àü¼Û...
		FillNpcInfo(modify_send, modify_index, INFO_MODIFY);
		SendInsight(pCom, modify_send, modify_index);
	}
	else if(m_tGuildWar == GUILD_WAR_AFFTER)
	{
		m_tNpcAttType = 1;
		if(m_tNpcType == NPCTYPE_GUILD_GUARD) m_tNpcType = NPCTYPE_GUARD;
		else if(m_tNpcType == NPCTYPE_GUILD_NPC) m_tNpcType = NPCTYPE_NPC;

		FillNpcInfo(modify_send, modify_index, INFO_MODIFY);
		SendInsight(pCom, modify_send, modify_index);
	}
*/
}

void CNpc::SetDamagedInGuildWar(int nDamage, USER *pUser)// COM *pCom)
{
	int i, j;
	BOOL flag = FALSE;

	CNpc *pNpc = NULL;
//	int uid = uuid - USER_BAND;
//	USER* pUser = GetUser(pCom, uid);
														// ±æµåÀüÀ» ½ÅÃ»ÇÑ ±æµåÀÎÁö ÆÇ´Ü.
	if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) return;
	if(pUser->m_dwGuild <= 0 || pUser->m_tGuildWar == GUILD_WAR_AFFTER) return;
	if(pUser->m_dwGuild == m_pGuardStore->m_iGuildSid) return;	// ¹æ¾îÃøÀÌ °íÀÇ·Î °ø°ÝÇÏ´Â°ÍÀ» ¹æÁöÇÑ´Ù.

	if(m_pGuardStore->m_lUsed == 0) return;				// ±æµåÀüÀÌ ³¡³µ´Ù.

	for(j = 0; j < GUILD_ATTACK_MAX_NUM; j++)
	{
		if(pUser->m_dwGuild != m_pGuardStore->m_arAttackGuild[j]) continue;

		m_sHP -= nDamage;
		if( m_sHP <= 0 )								// ¿©±â¿¡¼­ ±æµåÀüÀÌ ³¡³­´Ù.
		{
			m_sHP = m_sMaxHP;
			if(InterlockedCompareExchange((LONG*)&m_pGuardStore->m_lUsed, (long)0, (long)1) == (long)1)
			{											// 1¿¡¼­ 0À¸·Î ¸¸µé°í ÇØ´ç »óÁ¡ÀüÀïÀº ³¡³µÀ½À» ¾Ë¸°´Ù.
				if(pUser->StoppingTheGuildWar(m_pGuardStore))
				{										// ÇØ´ç NPC¿¡°Ô ¾Ë·ÁÁØ´Ù.
					for(i =0; i < m_pGuardStore->m_arNpcList.GetSize(); i++)
					{
						pNpc = GetNpc(m_pGuardStore->m_arNpcList[i]);
						if(pNpc) 
						{
							pNpc->m_tGuildWar = GUILD_WAR_AFFTER;
							pNpc->m_tNpcAttType = 0;
						}
					}
					m_tGuildWar = GUILD_WAR_AFFTER;
					flag = TRUE;
					break;
				}
			}
		}
	}

	if(flag)
	{
		for(j = 0; j < GUILD_ATTACK_MAX_NUM; j++)
		{
			m_pGuardStore->m_arAttackGuild[j] = 0;
		}
	}

	return;
}

void CNpc::Send(USER *pUser, TCHAR *pBuf, int nLength)
{
	if ( !pUser ) return;

	pUser->Send( pBuf, nLength );
}

///////////////////////////////////////////////////////////////////////////////////
//	ÀÓ½Ã ÀÌº¥Æ® ÄÚµåÀÓ (±â°£ : 2001³â 12¿ù 29ÀÏ ~~ 2002³â 1¿ù 2ÀÏ)
//
//@@@@@@@@@@@@@@@@@@@@@@@@
void CNpc::GiveEventItemToUser(USER *pUser)
{
	return;

	BOOL bFlag = FALSE;

	int iEventItemSid = 0;
	int iEventNum = -1;
	int iEvent = 0;
	int iSlot = 0;
	
	int j;

	SYSTEMTIME gTime;
	GetLocalTime(&gTime);
//	if(gTime.wYear == 2002 && gTime.wDay >= 2) return;

//	if(gTime.wMonth != 2) return;					// 2¿ù ¼³³¯¿ë ÀÌº¥Æ®
	if(gTime.wDay < 7 || gTime.wDay > 13) return;// 8ÀÏºÎÅÍ 13ÀÏ±îÁö	

	if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) return;
	
	if(abs(m_byClassLevel - pUser->m_sLevel) > 25)
	{
		if(m_byClassLevel < pUser->m_sLevel) return;
	}

	iEventNum = GetEventItemNum(pUser->m_pCom);

	if(iEventNum < 0) return;
	
	int type = (int)g_arAddEventItemTable[iEventNum]->m_tType;
	if(type < 100 || type > 255) return;

	if(!UpdateEventItem(iEventNum)) 
	{
		g_arAddEventItemTable[iEventNum]->m_tEnd = 0;
		return;
	}

	CString strMsg = _T("");

	iSlot = pUser->GetEmptySlot(INVENTORY_SLOT);

	if(iSlot != -1)
	{
		if(NPC_EVENT_ITEM >= g_arItemTable.GetSize())
		{
			int ttt = 0;
		}
		if(pUser->m_iMaxWeight >= pUser->m_iCurWeight + g_arItemTable[NPC_EVENT_ITEM]->m_byWeight) bFlag = TRUE;
	}

	switch(type)
	{
/*	case 1:
		if(bFlag) { iEvent = EVENT_SP1_ITEM; strMsg.Format("ÇöÀç %s´Ô²²¼­ ¹éÈ­Á¡ »óÇ°±Ç¸¦ ¾òÀ¸¼Ì½À´Ï´Ù.", pUser->m_strUserID); }
		else      iEvent = 1001;
		break;
	case 2:
		if(bFlag) { iEvent = EVENT_SP2_ITEM; strMsg.Format("ÇöÀç %s´Ô²²¼­ ¹®È­ »óÇ°±Ç¸¦ ¾òÀ¸¼Ì½À´Ï´Ù.", pUser->m_strUserID); }
		else      iEvent = 1002;
		break;
	case 3:
		if(bFlag) { iEvent = EVENT_DEF_ITEM; strMsg.Format("ÇöÀç %s´Ô²²¼­ ¹æ¾î±¸ ±³È¯±Ç¸¦ ¾òÀ¸¼Ì½À´Ï´Ù.", pUser->m_strUserID); }
		else      iEvent = 1003;
		break;
	case 4:
		if(bFlag) { iEvent = EVENT_ATT_ITEM; strMsg.Format("ÇöÀç %s´Ô²²¼­ ¹«±â ±³È¯±Ç¸¦ ¾òÀ¸¼Ì½À´Ï´Ù.", pUser->m_strUserID); }
		else      iEvent = 1004;
		break;
	case 5:
		if(bFlag) { iEvent = EVENT_POT_ITEM; strMsg.Format("ÇöÀç %s´Ô²²¼­ ¹°¾à ±³È¯±Ç¸¦ ¾òÀ¸¼Ì½À´Ï´Ù.", pUser->m_strUserID); }
		else      iEvent = 1005;
		break;
*/
	case EVENT_ATT7_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_ATT7_ITEM; strMsg.Format(IDS_EVENT_ATT7_ITEM, pUser->m_strUserID); }
		else      iEvent = 1001;
		break;
	case EVENT_DEF7_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_DEF7_ITEM; strMsg.Format(IDS_EVENT_DEF7_ITEM, pUser->m_strUserID); }
		else      iEvent = 1002;
		break;
	case EVENT_ATT6_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_ATT6_ITEM; strMsg.Format(IDS_EVENT_ATT6_ITEM, pUser->m_strUserID); }
		else      iEvent = 1003;
		break;
	case EVENT_DEF6_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_DEF6_ITEM; strMsg.Format(IDS_EVENT_DEF6_ITEM, pUser->m_strUserID); }
		else      iEvent = 1004;
		break;
	case EVENT_ATT_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_ATT_ITEM; strMsg.Format(IDS_EVENT_ATT5_ITEM, pUser->m_strUserID); }
		else      iEvent = 1005;
		break;
	case EVENT_DEF_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_DEF_ITEM; strMsg.Format(IDS_EVENT_DEF5_ITEM, pUser->m_strUserID); }
		else      iEvent = 1006;
		break;
	case EVENT_ATT4_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_ATT4_ITEM; strMsg.Format(IDS_EVENT_ATT4_ITEM, pUser->m_strUserID); }
		else      iEvent = 1007;
		break;
	case EVENT_DEF4_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_DEF4_ITEM; strMsg.Format(IDS_EVENT_DEF4_ITEM, pUser->m_strUserID); }
		else      iEvent = 1008;
		break;
	case EVENT_ATT3_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_ATT3_ITEM; strMsg.Format(IDS_EVENT_ATT3_ITEM, pUser->m_strUserID); }
		else      iEvent = 1009;
		break;
	case EVENT_DEF3_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_DEF3_ITEM; strMsg.Format(IDS_EVENT_DEF3_ITEM, pUser->m_strUserID); }
		else      iEvent = 1010;
		break;

	case EVENT_INIT_STAT_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_INIT_STAT; iEvent = EVENT_INIT_STAT_ITEM; strMsg.Format(IDS_EVENT_RESET_STAT, pUser->m_strUserID); }
		else      iEvent = 1011;
		break;

	case EVENT_USER_GAME_TIME:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_USER_GAME_TIME; strMsg.Format(IDS_EVENT_PERSONAL, pUser->m_strUserID); }
		else      iEvent = 1012;
		break;
		break;
	default:
		return;
		break;
	}

	if(bFlag)								// ÀÚµ¿À¸·Î ÀÎº¥¿¡ Ã£¾Æ¼­ µé¾î°£´Ù.
	{
		if(iEventItemSid == NPC_EVENT_ITEM || iEventItemSid == NPC_EVENT_INIT_STAT)
		{
			pUser->m_UserItem[iSlot].tType = TYPE_ITEM;
			pUser->m_UserItem[iSlot].sLevel = g_arItemTable[iEventItemSid]->m_byRLevel;
			pUser->m_UserItem[iSlot].sSid = g_arItemTable[iEventItemSid]->m_sSid;
			pUser->m_UserItem[iSlot].sCount = 1;
			pUser->m_UserItem[iSlot].sDuration = g_arItemTable[iEventItemSid]->m_sDuration;
			pUser->m_UserItem[iSlot].sBullNum = g_arItemTable[iEventItemSid]->m_sBullNum;
			pUser->m_UserItem[iSlot].tIQ = (BYTE)iEvent;
			pUser->m_UserItem[iSlot].iItemSerial = 0;

			SetISerialToItem(&pUser->m_UserItem[iSlot], iEventNum);
/*			for(j = 0; j < MAGIC_NUM; j++)
			{
				pUser->m_UserItem[iSlot].tMagic[j] = 0;
				pUser->m_UserItem[iSlot].tMagic[j] = tSerial[j];//g_arAddEventItemTable[iEventNum]->m_strSerialNum[j];
			}
*/
			CBufferEx TempBuf;

			TempBuf.Add(ITEM_LOAD_RESULT);
			TempBuf.Add(SUCCESS);
			TempBuf.Add((BYTE)0x01);

			TempBuf.Add((BYTE)iSlot);
			TempBuf.Add(pUser->m_UserItem[iSlot].sLevel);
			TempBuf.Add(pUser->m_UserItem[iSlot].sSid);
			TempBuf.Add(pUser->m_UserItem[iSlot].sDuration);
			TempBuf.Add(pUser->m_UserItem[iSlot].sBullNum);
			TempBuf.Add(pUser->m_UserItem[iSlot].sCount);
			for(j = 0; j < MAGIC_NUM; j++) TempBuf.Add((BYTE)pUser->m_UserItem[iSlot].tMagic[j]);

			TempBuf.Add((BYTE)pUser->m_UserItem[iSlot].tIQ);

			pUser->Send(TempBuf, TempBuf.GetLength());

			pUser->m_iCurWeight += g_arItemTable[iEventItemSid]->m_byWeight;
			pUser->GetRecoverySpeed();			// ¾ÆÀÌÅÛ ¹«°Ô¿¡ º¯µ¿ÀÌ »ý±â¸é È¸º¹¼Óµµ º¯È¯

			pUser->m_pCom->Announce((LPTSTR)(LPCTSTR)strMsg, SYSTEM_NORMAL);
//			pUser->m_pCom->Announce(strMsg.GetBuffer(strMsg.GetLength()), SYSTEM_NORMAL);
		}
		return;
	}
											// ÀÎº¥³Ö±â¿¡ ½ÇÆÐÇÏ¸é ¸Ê¿¡ ¼ÂÆÃ
	GiveItemToMap(pUser->m_pCom, iEvent, TRUE, iEventNum);		// ÀÌº¥Æ® ¾ÆÀÌÅÛ
}

///////////////////////////////////////////////////////////////////////////////////
//	ÀÌº¥Æ® ÄÚµåÀÓ (±â°£ : 2002³â 4¿ù 8ÀÏ ~~ 2002³â 4¿ù 13ÀÏ)
//
//@@@@@@@@@@@@@@@@@@@@@@@@
void CNpc::SetISerialToItem(ItemList *pItem, int iEventSid)
{
	int i, j = 0;
	TCHAR strTemp[3];

	if(!pItem) return;
	if(iEventSid < 0 || iEventSid >= g_arAddEventItemTable.GetSize()) return;

	for(i = 0; i < MAGIC_NUM; i++)
	{	
		::ZeroMemory(strTemp, sizeof(strTemp));
		strncpy(strTemp,g_arAddEventItemTable[iEventSid]->m_strSerialNum+j, 3);

		pItem->tMagic[i] = 0;
		pItem->tMagic[i] = atoi(strTemp);
		j = j + 4;
	}
}

///////////////////////////////////////////////////////////////////////////////////
//	ÀÌº¥Æ® ÄÚµåÀÓ (±â°£ : 2002³â 4¿ù 8ÀÏ ~~ 2002³â 4¿ù 13ÀÏ)
//
//@@@@@@@@@@@@@@@@@@@@@@@@
int CNpc::GetEventItemNum(COM *pCom)
{
	int i, iRet = -1;
	DWORD dwCurTick = 0;
	DWORD dwPreTick = 0;

	EnterCriticalSection( &(pCom->m_critEvent) );

	dwCurTick = GetTickCount();

	for(i = 0; i < g_arAddEventItemTable.GetSize(); i++)
	{
		int tt = g_arAddEventItemTable[i]->m_tEnd;
		if(!g_arAddEventItemTable[i]->m_tEnd)				// ¾ÆÁ÷ ¶³¾îÁöÁö ¾Ê¾Ò´Ù¸é
		{
			if(i == 0) dwPreTick = 0;
			else dwPreTick = g_arAddEventItemTable[i - 1]->m_dwTick;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@22
			if(dwCurTick - dwPreTick >= 60000 * 20)		// 24ºÐÀÌ ³Ñ¾ú´Ù¸é
//			if(dwCurTick - dwPreTick >= 1000)				// 1ºÐÀÌ ³Ñ¾ú´Ù¸é	
			{
				g_arAddEventItemTable[i]->m_dwTick = dwCurTick;
				g_arAddEventItemTable[i]->m_tEnd = 1;
														// ½ÇÁ¦¼ö¸¸ ¹øÈ£¸¦ ¼ÂÆÃÇØ¼­ ÁØ´Ù.	
				if(g_arAddEventItemTable[i]->m_tGiveFlag)	iRet = g_arAddEventItemTable[i]->m_sSid;
			}

			LeaveCriticalSection( &(pCom->m_critEvent) );
			return iRet;
		}
	}

	LeaveCriticalSection( &(pCom->m_critEvent) );
	return iRet;
}

///////////////////////////////////////////////////////////////////////////////////
//	ÀÓ½Ã ÀÌº¥Æ® ÄÚµåÀÓ (±â°£ : 2001³â 12¿ù 29ÀÏ ~~ 2002³â 1¿ù 2ÀÏ)
//
//@@@@@@@@@@@@@@@@@@@@@@@@
BOOL CNpc::UpdateEventItem(int sid)
{
	SQLHSTMT		hstmt = NULL;
	SQLRETURN		retcode = 0;
	BOOL			bQuerySuccess = TRUE;
	TCHAR			szSQL[8000];		

	SQLINTEGER		iRetInd = SQL_NTS;

	SQLSMALLINT		sRet = 0;

	::ZeroMemory(szSQL, sizeof(szSQL));

	_sntprintf(szSQL, sizeof(szSQL), TEXT("{call UPDATE_EVENT_ITEM(%d, ?)}"), sid);

	int db_index = 0;
	CDatabase* pDB = g_DBNew[AUTOMATA_THREAD].GetDB( db_index );
	if( !pDB ) return FALSE;

	retcode = SQLAllocHandle( (SQLSMALLINT)SQL_HANDLE_STMT, pDB->m_hdbc, &hstmt );
	if( retcode != SQL_SUCCESS )
	{
		return FALSE;
	}

	retcode = SQLBindParameter( hstmt, 1 ,SQL_PARAM_OUTPUT,SQL_C_SSHORT, SQL_SMALLINT,0,0, &sRet,0, &iRetInd);
	if( retcode != SQL_SUCCESS )
	{
		SQLFreeHandle((SQLSMALLINT)SQL_HANDLE_STMT, hstmt);
		return FALSE;
	}

	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLExecDirect(hstmt, (unsigned char *)szSQL, SQL_NTS);
		
		if (retcode ==SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
		}
		else if (retcode==SQL_ERROR)
		{
			DisplayErrorMsg( hstmt );
			SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);
			return FALSE;
		}
	}	
	else
	{
		DisplayErrorMsg( hstmt );
		SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);
		return FALSE;
	}

	if (hstmt!=NULL) SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);
	g_DBNew[AUTOMATA_THREAD].ReleaseDB(db_index);
	
	if( !bQuerySuccess ) return FALSE;
	if(sRet = 0) return FALSE;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////
//	¼ö¸®°¡ ¾ÈµÇ¾î ÀÖÀ¸¸é ÇöÀç HP¸¦ À¯ÁöÇÑ´Ù.	
//
void CNpc::SetFortressState()
{
	for(int i = 0; i < GUILD_REPAIR_MAX_NUM; i++)
	{
		if(m_pGuardFortress->m_arRepairDBList[i].sUid == m_sEZone)
		{
			if(m_pGuardFortress->m_arRepairDBList[i].sHP < m_sMaxHP)
			{
				m_sHP = m_pGuardFortress->m_arRepairDBList[i].sHP;

				if(m_sHP == 0)  m_tRepairDamaged = NPC_DEAD_REPAIR_STATE; 
				else			m_tRepairDamaged = NPC_NEED_REPAIR_STATE;

				break;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////
//	N_Circle¿¡ ´ëÇÑ Ã³¸®¸¦ °è»êÇÑ´Ù.
//
//void CNpc::SetDamagedInFortressWar(int nDamage, TCHAR *id, int uuid, COM *pCom)
void CNpc::SetDamagedInFortressWar(int nDamage, USER *pUser)
{
	int i;
	int iCount = 0;
	int index = 0;

	BOOL bSuccess = FALSE;
	
	CBufferEx TempBuf;
	CNpc *pNpc = NULL;
														// ±æµåÀüÀ» ½ÅÃ»ÇÑ ±æµåÀÎÁö ÆÇ´Ü.
	if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) return;
	if(pUser->m_dwGuild <= 0 || !m_pGuardFortress) return;

	if(pUser->m_tFortressWar == GUILD_WAR_AFFTER) return;

	if(m_pGuardFortress->m_lUsed == 0) return;			// ±æµåÀüÀÌ ³¡³µ´Ù.

	if(m_pGuardFortress->m_lChangeUsed == 1) return;

	for(i = 0; i < GUILDFORTRESS_ATTACK_MAX_NUM; i++)
	{
		if(pUser->m_dwGuild == m_pGuardFortress->m_arAttackGuild[i].lGuild)
		{
			bSuccess = TRUE;
			break;
		}
	}

	if(pUser->m_dwGuild == m_pGuardFortress->m_iGuildSid) bSuccess = TRUE;
	
	if(!bSuccess) return;								// ½ÅÃ»ÇÑ ±æµå°¡ ¾Æ´Ô

	if(InterlockedCompareExchange((LONG*)&m_lFortressState, (long)1, (long)0) == (long)0)
	{
		if(pUser->m_dwGuild == m_pGuardFortress->m_iGuildSid)	// ¹æ¾îÃøÀº 
		{
			if(m_tNCircle != NPC_NCIRCLE_ATT_STATE)
			{
				InterlockedExchange(&m_lFortressState, (LONG)0); 
				return;
			}

			m_sHP -= nDamage;									// °ø°ÝÃøÀº - °ª
			if(m_sHP <= 0)
			{
				m_sHP = m_sMaxHP;
				m_byColor = 0;
				m_tNCircle = NPC_NCIRCLE_DEF_STATE;
				SendFortressNCircleColor(pUser->m_pCom);
			}
		}
		else
		{
			if(m_tNCircle != NPC_NCIRCLE_DEF_STATE) 
			{
				InterlockedExchange(&m_lFortressState, (LONG)0); 
				return;
			}

			m_sHP -= nDamage;									// °ø°ÝÃøÀº - °ª
			if(m_sHP <= 0)
			{
				m_sHP = m_sMaxHP;
				m_byColor = 1;
				m_tNCircle = NPC_NCIRCLE_ATT_STATE;
				SendFortressNCircleColor(pUser->m_pCom);
			}
		}

		iCount = 0;
		for(i = 0; i < FORTRESS_TARGET_MAX_NUM; i++)
		{
			pNpc = NULL;
			pNpc = GetNpc(m_pGuardFortress->m_arFortressTarget[i].sTargertID);	
			if(pNpc)
			{
				if(pNpc->m_tNCircle == NPC_NCIRCLE_ATT_STATE) iCount++; 
			}
		}

		if(iCount == FORTRESS_TARGET_MAX_NUM)
		{
			if(pUser->m_dwGuild == m_pGuardFortress->m_iGuildSid)
			{
				InterlockedExchange(&m_lFortressState, (LONG)0); 
				return;
			}

			for(i = 0; i < g_arGuildFortress.GetSize(); i++)
			{
				if(!g_arGuildFortress[i]) continue;

				if(g_arGuildFortress[i]->m_sFortressID == m_pGuardFortress->m_sFortressID)
				{
					if(g_arGuildFortress[i]->m_lUsed == 1)
					{
						if(InterlockedCompareExchange((LONG*)&g_arGuildFortress[i]->m_lChangeUsed, (long)1, (long)0) == (long)0)
						{
							FORTRESSDATAPACKET *pFDP = NULL;
							pFDP = new FORTRESSDATAPACKET;

							pFDP->sFortressIndex = i;
							
							memset(pFDP->FORTRESS, NULL, CHAR_NAME_LENGTH+sizeof(int)+1);
							index = strlen(pUser->m_strGuildName);
							if(index > 0 && index <= CHAR_NAME_LENGTH) memcpy(pFDP->FORTRESS, pUser->m_strGuildName, index );

							EnterCriticalSection( &m_CS_FortressData );
							RecvFortressData.AddTail(pFDP);
 							nFortressDataCount = RecvFortressData.GetCount();
							LeaveCriticalSection( &m_CS_FortressData );	

							pUser->StoppingTheFortressWar(g_arGuildFortress[i]);		// Á¤ÇØÁø ½Ã°£ÀüÀÌ¹Ç·Î °ÔÀÓÀº °è¼ÓµÇ¾î¾ß ÇÑ´Ù. 
							InterlockedExchange(&g_arGuildFortress[i]->m_lChangeUsed, (LONG)0); 
						}
					}
					break;
				}
			}
		}

		InterlockedExchange(&m_lFortressState, (LONG)0); 
	}

	return;
}

//void CNpc::SetDoorDamagedInFortressWar(int nDamage, TCHAR *id, int uuid, COM *pCom)
void CNpc::SetDoorDamagedInFortressWar(int nDamage, USER *pUser)
{													// °ø¼ºÀü ±â°£ÀÌ¶ó¸é ´©±¸³ª °ø°ÝÇÏµµ·Ï.. ´Ü ¹æ¾îÃøÀº ¾ÈµÊ
	if(!pUser || !m_pGuardFortress) return;
	if(pUser->m_dwGuild == m_pGuardFortress->m_iGuildSid) return;	// ¹æ¾îÃøÀÌ °íÀÇ·Î °ø°ÝÇÏ´Â°ÍÀ» ¹æÁöÇÑ´Ù.

	if(m_pGuardFortress->m_lUsed == 0) return;				// ±æµåÀüÀÌ ³¡³µ´Ù.

	m_sHP -= nDamage;

	if( m_sHP <= 0 )
	{
		m_sHP = 0;

		MAP* pMap = g_zone[m_ZoneIndex];
		pMap->m_pMap[m_sCurX][m_sCurY].m_lUser = 0;

		m_NpcState = NPC_DEAD;

		m_Delay = m_sRegenTime;
		m_bFirstLive = FALSE;

		SetMapAfterGuildWar();

		SendDead(pUser->m_pCom);
	}
}

void CNpc::SendFortressNCircleColor(COM *pCom)
{
	int modify_index = 0;
	char modify_send[2048];	

	CBufferEx TempBuf;

	TempBuf.Add(GUILD_FORTRESS_NCIRCLE);
	TempBuf.Add((BYTE)0x00);					// ÇØ´ç N_CircleÀÇ »öÀÌ º¯È­
	TempBuf.Add((int)(m_sNid + NPC_BAND));
	TempBuf.Add(m_tNCircle);

	SendFortressInsight(pCom, TempBuf, TempBuf.GetLength());

	::ZeroMemory(modify_send, sizeof(modify_send));
	FillNpcInfo(modify_send, modify_index, INFO_MODIFY);
	SendFortressInsight(pCom, modify_send, modify_index);

}


void CNpc::SetMapTypeBeforeGuildWar(COM *pCom)
{
	int i;
	int uid = 0;

	USER *pUser = NULL;
	CNpc *pNpc = NULL;

	int x, y;

	long lNpcUid = 0;

//	POINT temp1Map[12] = {{-2,-2}, {-2,-1}, {-2,0}, {-1,-1}, {-1,0}, {0,-1}, {0,0},{1,-1},{1,0}, {2,-1}, {2,0}, {2,1}};
	POINT temp1Map[16] = {{-3,-2}, {-4,-1}, {-3,-1}, {-2,-1}, {-4,0}, {-3,0}, {-2,0},{-1,0},{0,0}, {1,0}, {2,0}, {1,1}, {2,1}, {2,2},{3,2},{3,3}};
	POINT temp2Map[17] = {{-2,-3}, {-1,-3}, {0,-3}, {-1,-2}, {0,-2}, {0,-1}, {0,0},{0,1},{1,1}, {0,2}, {1,2}, {2,2}, {0,3}, {1,3},{2,3},{0,4},{1,4}};
	POINT temp3Map[6] = {{-2,0},{-1,0},{0,0},{1,0},{2,0},{2,1}};
	
//	POINT temp2Map[] = {{1,-2}, {1,-1}, {1,0}, {1,1}, {1,2}, {0,-2},{0,-1},{0,0},{0,1},{0,2}};

	MAP* pMap = g_zone[m_ZoneIndex];

	switch(m_sDimension)
	{
	case 1:
		lNpcUid = m_sNid + NPC_BAND;

		for(i =0; i < sizeof(temp1Map)/sizeof(POINT); i++)
		{
			x = m_sCurX + temp1Map[i].x;
			y = m_sCurY + temp1Map[i].y;
	
			uid = pMap->m_pMap[x][y].m_lUser;

			if(uid >= USER_BAND && uid < NPC_BAND)	// Target ÀÌ User ÀÎ °æ¿ì
			{
				pUser = GetUser(pCom, uid - USER_BAND);
				if( pUser->m_tIsOP != 1 ) pUser->TownPotal();
			}

			::InterlockedExchange(&pMap->m_pMap[x][y].m_lUser, lNpcUid);
		}
		break;
	case 2:
		lNpcUid = m_sNid + NPC_BAND;

		for(i =0; i < sizeof(temp2Map)/sizeof(POINT); i++)
		{
			x = m_sCurX + temp2Map[i].x;
			y = m_sCurY + temp2Map[i].y;
	
			uid = pMap->m_pMap[x][y].m_lUser;

			if(uid >= USER_BAND && uid < NPC_BAND)	// Target ÀÌ User ÀÎ °æ¿ì
			{
				pUser = GetUser(pCom, uid - USER_BAND);
				if( pUser->m_tIsOP != 1 ) pUser->TownPotal();
			}

			::InterlockedExchange(&pMap->m_pMap[x][y].m_lUser, lNpcUid);
		}
		break;
	case 3:
		lNpcUid = m_sNid + NPC_BAND;

		for(i =0; i < sizeof(temp3Map)/sizeof(POINT); i++)
		{
			x = m_sCurX + temp3Map[i].x;
			y = m_sCurY + temp3Map[i].y;
	
			uid = pMap->m_pMap[x][y].m_lUser;

			if(uid >= USER_BAND && uid < NPC_BAND)	// Target ÀÌ User ÀÎ °æ¿ì
			{
				pUser = GetUser(pCom, uid - USER_BAND);
				if( pUser->m_tIsOP != 1 ) pUser->TownPotal();
			}

			::InterlockedExchange(&pMap->m_pMap[x][y].m_lUser, lNpcUid);
		}
		break;

	}
}


void CNpc::SetMapAfterGuildWar()
{
	int i;
	int uid = 0;

	USER *pUser = NULL;

	int x, y;

//	POINT temp1Map[12] = {{-2,-2}, {-2,-1}, {-2,0}, {-1,-1}, {-1,0}, {0,-1}, {0,0},{1,-1},{1,0}, {2,-1}, {2,0}, {2,1}};
//	POINT temp2Map[] = {{1,-2}, {1,-1}, {1,0}, {1,1}, {1,2}, {0,-2},{0,-1},{0,0},{0,1},{0,2}};
	POINT temp1Map[16] = {{-3,-2}, {-4,-1}, {-3,-1}, {-2,-1}, {-4,0}, {-3,0}, {-2,0},{-1,0},{0,0}, {1,0}, {2,0}, {1,1}, {2,1}, {2,2},{3,2},{3,3}};
	POINT temp2Map[17] = {{-2,-3}, {-1,-3}, {0,-3}, {-1,-2}, {0,-2}, {0,-1}, {0,0},{0,1},{1,1}, {0,2}, {1,2}, {2,2}, {0,3}, {1,3},{2,3},{0,4},{1,4}};
	POINT temp3Map[6] = {{-2,0},{-1,0},{0,0},{1,0},{2,0},{2,1}};

	MAP* pMap = g_zone[m_ZoneIndex];

	switch(m_sDimension)
	{
	case 1:
		for(i =0; i < sizeof(temp1Map)/sizeof(POINT); i++)
		{
			x = m_sCurX + temp1Map[i].x;
			y = m_sCurY + temp1Map[i].y;

			InterlockedExchange(&pMap->m_pMap[x][y].m_lUser, 0);
		}
		break;
	case 2:
		for(i =0; i < sizeof(temp2Map)/sizeof(POINT); i++)
		{
			x = m_sCurX + temp2Map[i].x;
			y = m_sCurY + temp2Map[i].y;

			InterlockedExchange(&pMap->m_pMap[x][y].m_lUser, 0);
		}
		break;
	case 3:
		for(i =0; i < sizeof(temp3Map)/sizeof(POINT); i++)
		{
			x = m_sCurX + temp3Map[i].x;
			y = m_sCurY + temp3Map[i].y;

			InterlockedExchange(&pMap->m_pMap[x][y].m_lUser, 0);
		}
		break;
	}
}

void CNpc::SendFortressInsight(COM *pCom, TCHAR *pBuf, int nLength)
{
	if(nLength <= 0 || nLength >= SEND_BUF_SIZE) return;

	int insight_range = 10;

	int sx = m_sCurX / SIGHT_SIZE_X;
	int sy = m_sCurY / SIGHT_SIZE_Y;
	
	int min_x = (sx-8)*(SIGHT_SIZE_X); if( min_x < 0 ) min_x = 0;
	int max_x = (sx+9)*(SIGHT_SIZE_X);
	int min_y = (sy-8)*(SIGHT_SIZE_Y); if( min_y < 0 ) min_y = 0;
	int max_y = (sy+9)*(SIGHT_SIZE_Y);
	
	MAP* pMap = g_zone[m_ZoneIndex];
	if( !pMap ) return;
	
	if( max_x >= pMap->m_sizeMap.cx ) max_x = pMap->m_sizeMap.cx - 1;
	if( max_y >= pMap->m_sizeMap.cy ) max_y = pMap->m_sizeMap.cy - 1;
	
	int temp_uid;
	USER* pUser = NULL;

	for( int i = min_x; i < max_x; i++ )
	{
		for( int j = min_y; j < max_y; j++ )
		{				
			temp_uid = pMap->m_pMap[i][j].m_lUser;

			if(temp_uid < USER_BAND || temp_uid >= NPC_BAND) continue;
			else temp_uid -= USER_BAND;
			
			if( temp_uid >= 0 && temp_uid < MAX_USER )
			{
				pUser = pCom->GetUserUid(temp_uid);
				if(pUser == NULL) continue;
				
				if( pUser->m_state == STATE_GAMESTARTED )
				{
					if( pUser->m_curx == i && pUser->m_cury == j && pUser->m_curz == m_sCurZ )
					{
						Send( pUser, pBuf, nLength );
					}
				}
			}
		}
	}
}

void CNpc::TestCode(COM *pCom, USER *pUser)
{
	int i;
	int uid = 0;

	CNpc *pNpc = NULL;

	int x, y;

	long lNpcUid = 0;

	if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) return;

	POINT temp1Map[12] = {{-2,-2}, {-2,-1}, {-2,0}, {-1,-1}, {-1,0}, {0,-1}, {0,0},{1,-1},{1,0}, {2,-1}, {2,0}, {2,1}};// server
//	POINT temp2Map[8] = {{0,0}, {0,1}, {0,2}, {0,3}, {-1,0}, {-1,1}, {-1,2},{-1,3}};
//	POINT temp1Map[12] = {{147,1183}, {148,1184}, {149,1185}, {149,1183}, {150,1184}, {150,1182}, {151,1183},{151,1181},{152,1182}, {152,1180}, {153,1181}, {154,1182}};
	POINT temp2Map[] = {{-1,-3}, {0,-2}, {1,-1}, {2,0}, {3,1}, {-2,-2}, {-1,-1}, {0,0}, {1,1}, {2,2}};	// client

	MAP* pMap = g_zone[m_ZoneIndex];

	CPoint temp = ConvertToClient(m_sCurX, m_sCurY);
	switch(m_sDimension)
	{
	case 1:
		lNpcUid = m_sNid + NPC_BAND;

		for(i =0; i < 12; i++)
		{
			x = m_sCurX + temp1Map[i].x;
			y = m_sCurY + temp1Map[i].y;
	
			CString strMsg = _T("");
			CPoint pt = ConvertToClient(x, y);
//			CPoint pt = ConvertToServer(temp1Map[i].x, temp1Map[i].y);
			strMsg.Format("1Luinet locked door x = %d, y = %d", pt.x - temp.x, pt.y - temp.y);

//			pUser->NormalChat(strMsg.GetBuffer(strMsg.GetLength()));

//			::InterlockedExchange(&pMap->m_pMap[x][y].m_lUser, lNpcUid);
		}
		break;
	case 2:
		lNpcUid = m_sNid + NPC_BAND;

		for(i =0; i < 10; i++)
		{
			x = temp.x + temp2Map[i].x;
			y = temp.y + temp2Map[i].y;

			CPoint pt = ConvertToServer(x, y);

			CString strMsg = _T("");			
//			CPoint pt = ConvertToServer(temp1Map[i].x, temp1Map[i].y);
			strMsg.Format("1Sanad locked door x = %d, y = %d", pt.x - m_sCurX, pt.y - m_sCurY);

//			pUser->NormalChat(strMsg.GetBuffer(strMsg.GetLength()));

		}
		break;
	}
}

int CNpc::PsiAttack(COM *pCom)
{
	DWORD	dwExp = 0;
	int		nDamage = 0;
	int		nTempHP = 0;

	USER*	pUser = NULL;
	CNpc*	pNpc = NULL;

	BYTE	tWeaponClass = 0;
	BOOL	bCanUseSkill = FALSE;
	int		bSuccessSkill[SKILL_NUM] = {FALSE, FALSE, FALSE, FALSE, FALSE};

	int		nPsiRange = 0;
	int		nTPosX	= 0;
	int		nTPosY	= 0;
	int		nDist	= 100;
	short	sNeedPP	= 25000;
	BYTE	tPsiRegi = 0;
	DWORD	dwPsiCast = 0;

	BOOL	bPsiSuccess = FALSE;

	int index = 0;

	int delay = -1;
	int nTargetID	= m_Target.id;			// Target ID ¸¦ ¾ò´Â´Ù.
	BYTE byPsi		= m_byPsi;				// Psionic sid ¸¦ ¾ò´Â´Ù.

	int nPsiX = -1;							// TeleportÇÒ À§Ä¡
	int nPsiY = -1;
	CPoint ptPsi(-1, -1);

	if( byPsi < 0 || byPsi >= g_arMonsterPsi.GetSize() ) return -1;

	if( nTargetID < USER_BAND || nTargetID >= INVALID_BAND ) return-1;	// Àß¸øµÈ Target ÀÌ¸é return

	pUser = GetUser( pCom, nTargetID - USER_BAND );
	if( !pUser ) return -1;

	CMonsterPsi* pMagic = g_arMonsterPsi[(int)byPsi];
	if( !pMagic ) return -1;
	
	// »çÁ¤°Å¸® °è»ê ------------------------------------------------------------------------//
	if( !IsCloseTarget( pCom, (int)pMagic->m_byRange ) ) return -1;

	double damage, result;

	switch( pMagic->m_sSid )
	{
	case	1:		// ½î´Â ¸¶¹ý
		damage = myrand( pMagic->m_sMinDmg, pMagic->m_sMaxDmg );
	
		result = damage * (double)( m_sVOL * 20 ) / 
			(double)( pUser->m_sMagicVOL * 15 + pUser->m_DynamicUserData[MAGIC_PSI_RESIST_UP]*5 + m_sVOL * 20 );

		pUser->SetDamage((int)result);

//		if(pUser->m_bLive == USER_DEAD || pUser->m_sHP <= 0)//@@@ ³ªÁß¿¡ °íÄ§
		if(pUser->m_lDeadUsed == 1)
		{
			InitTarget();
			m_NpcState = NPC_STANDING;
			delay = m_sStandTime;

			if(m_NpcVirtualState == NPC_STANDING) 
			{
				if(m_sPid == 179) pUser->GetLevelDownExp(FALSE, -1, TRUE,m_strName); // Ä§°ø¿ë ¸ó½ºÅÍÀÏ°æ¿ì °æÇèÄ¡ 1%°¨¼Ò
				else			pUser->GetLevelDownExp(FALSE, -1, FALSE,m_strName);		// °æÇèÄ¡¿Í ±×¿Ü º¯È­·®¸¦ ¹Ý¿µÇÑ´Ù.
			}
		}
//		else
//		{
//			pUser->SetFireDamage();
//		}

		break;

	case	2:		// ºÒ¸¶¹ý
		damage = myrand( pMagic->m_sMinDmg, pMagic->m_sMaxDmg );
	
		result = damage * (double)( m_sVOL * 20 ) / (double)( pUser->m_sMagicVOL * 15 + pUser->m_DynamicUserData[MAGIC_PSI_RESIST_UP]*5 + m_sVOL * 20 );

		pUser->SetDamage((int)result);

//		if(pUser->m_bLive == USER_DEAD || pUser->m_sHP <= 0)//@@@ ³ªÁß¿¡ °íÄ§
		if(pUser->m_lDeadUsed == 1)
		{
			InitTarget();
			m_NpcState = NPC_STANDING;
			delay = m_sStandTime;

			if(m_NpcVirtualState == NPC_STANDING)
			{
				if(m_sPid == 179) pUser->GetLevelDownExp(FALSE, -1, TRUE,m_strName); // Ä§°ø¿ë ¸ó½ºÅÍÀÏ°æ¿ì °æÇèÄ¡ 1%°¨¼Ò
				else			pUser->GetLevelDownExp(FALSE, -1, FALSE,m_strName);		// °æÇèÄ¡¿Í ±×¿Ü º¯È­·®¸¦ ¹Ý¿µÇÑ´Ù.
			}
		}
		else
		{
			pUser->SetFireDamage();
		}

//		È­¿° ¸¶¹ýÀº ¹üÀ§°¡ ¾Æ´Ï·£´Ù
//		GetWideRangeAttack( pCom, pUser->m_curx, pUser->m_cury, (int)damage, nTargetID - USER_BAND );
		break;

	case	3:		// Àü±â ¸¶¹ý
		damage = myrand( pMagic->m_sMinDmg, pMagic->m_sMaxDmg );
	
		result = damage * (double)( m_sVOL * 20 ) / (double)( pUser->m_sMagicVOL * 15 + pUser->m_DynamicUserData[MAGIC_PSI_RESIST_UP]*5 + m_sVOL * 20 );

		pUser->SetDamage((int)result);

//		if(pUser->m_bLive == USER_DEAD || pUser->m_sHP <= 0)//@@@ ³ªÁß¿¡ °íÄ§
		if(pUser->m_lDeadUsed == 1)
		{
			InitTarget();
			m_NpcState = NPC_STANDING;
			delay = m_sStandTime;

			if(m_NpcVirtualState == NPC_STANDING)
			{
				if(m_sPid == 179) pUser->GetLevelDownExp(FALSE, -1, TRUE,m_strName); // Ä§°ø¿ë ¸ó½ºÅÍÀÏ°æ¿ì °æÇèÄ¡ 1%°¨¼Ò
				else			pUser->GetLevelDownExp(FALSE, -1, FALSE,m_strName);		// °æÇèÄ¡¿Í ±×¿Ü º¯È­·®¸¦ ¹Ý¿µÇÑ´Ù.
			}
		}

		GetWideRangeAttack( pCom, pUser->m_curx, pUser->m_cury, (int)damage, nTargetID - USER_BAND );

		break;
	}

	CBufferEx TempBuf;

	TempBuf.Add(PSI_ATTACK_RESULT);
	TempBuf.Add(SUCCESS);

	TempBuf.Add( (BYTE)pMagic->m_sPid );				// Psionic sid
	TempBuf.Add( m_sNid + NPC_BAND );
	TempBuf.Add( nTargetID );

//	SendInsight( pCom, TempBuf, TempBuf.GetLength());
	SendExactScreen(pCom, TempBuf, TempBuf.GetLength());

	delay = (int)pMagic->m_sCasting;

	return (int)delay;
}

void CNpc::GetWideRangeAttack(COM* pCom, int x, int y, int damage, int except_uid)	// Áö±ÝÀº °ø°Ý¸¸ Ã³¸®...
{
	int dir[9][2];
	int ix, iy;
	int nTarget = 0;
	int nDamage = 0;
	double result = 0;

	USER* pUser = NULL;
	MAP* pMap = g_zone[m_ZoneIndex];
	if(!pMap) return;

	dir[0][0]  =  0;		dir[0][1] =  0;		// 
	dir[1][0]  = -1;		dir[1][1] =  0;		// 
	dir[2][0]  = -1;		dir[2][1] =  1;		// 
	dir[3][0]  =  0;		dir[3][1] =  1;		// 
	dir[4][0]  =  1;		dir[4][1] =  1;		// 

	dir[5][0]  =  1;		dir[5][1] =  0;		// 
	dir[6][0]  =  1;		dir[6][1] = -1;		// 
	dir[7][0]  =  0;		dir[7][1] = -1;		// 
	dir[8][0]  = -1;		dir[8][1] = -1;		// 

	for(int i = 1; i < 9; i++)
	{
		ix = x + dir[i][0];
		iy = y + dir[i][1];

		if(ix < 0) ix = 0;
		if(iy < 0) iy = 0;
		if(ix >= pMap->m_sizeMap.cx) ix = pMap->m_sizeMap.cx - 1;
		if(iy >= pMap->m_sizeMap.cy) iy = pMap->m_sizeMap.cy - 1;

		nTarget = pMap->m_pMap[ix][iy].m_lUser;

		if(nTarget >= USER_BAND && nTarget < NPC_BAND)	// USER
		{
			pUser = GetUser( pCom, nTarget - USER_BAND);			// User Pointer ¸¦ ¾ò´Â´Ù.

			if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) continue;						// Àß¸øµÈ USER ÀÌ¸é ¸®ÅÏ
			if(pUser->m_bLive == USER_DEAD)	continue;		// Target User °¡ ÀÌ¹Ì Á×¾îÀÖÀ¸¸é ¸®ÅÏ
			if(pUser->m_uid == except_uid ) continue;	// Áß½É¿¡ ÀÖ´Â À¯Àú´Â °è»êÇÏÁö ¾Ê´Â´Ù

			result = (double)damage * (double)( m_sVOL * 20 ) / (double)( pUser->m_sMagicVOL * 15 + pUser->m_DynamicUserData[MAGIC_PSI_RESIST_UP] + m_sVOL * 20 );
			
			pUser->SetDamage((int)result);

			if(pUser->m_sHP > 0)		// »ìÀº °æ¿ì Àü±âµ¥¹ÌÁö Ãß°¡
			{
//				pUser->SetColdDamage();
			}
			else
			{
//				IsChangeCityRank(pUser);
				if(m_sPid == 179) pUser->GetLevelDownExp(FALSE, -1, TRUE,m_strName); // Ä§°ø¿ë ¸ó½ºÅÍÀÏ°æ¿ì °æÇèÄ¡ 1%°¨¼Ò
				else			pUser->GetLevelDownExp(USER_PK, -1, FALSE,m_strName);			// °æÇèÄ¡¿Í ±×¿Ü º¯È­·®¸¦ ¹Ý¿µÇÑ´Ù.
			}
		}
/*
		else if(nTarget >= NPC_BAND)				// NPC
		{
			pNpc = GetNpc(nTarget - NPC_BAND);				// NPC Point ¸¦ ¾ò´Â´Ù.
			if(pNpc == NULL) continue;					// Àß¸øµÈ NPC ÀÌ¸é ¸®ÅÏ
			if(pNpc->m_NpcState == NPC_DEAD || pNpc->m_tNpcType != NPCTYPE_MONSTER) continue;	// NPC °¡ ÀÌ¹Ì Á×¾î ÀÖÀ¸¸é ¸®ÅÏ
			if(pNpc->m_sHP <= 0) continue;

			nDamage = (int)(damage *  ((double)m_sMagicVOL / (m_sMagicVOL + pNpc->m_sVOL)));
			nDamage = (int)((double)nDamage/2 + 0.5);	// µ¥¹ÌÁöÀÇ 50%¸¸ µé¾î°£´Ù.

			if(pNpc->SetDamage(nDamage, m_strUserID, m_uid + USER_BAND, m_pCom) == FALSE)
			{
				if(m_tGuildHouseWar == GUILD_WARRING && pNpc->m_NpcVirtualState == NPC_WAIT)
				{
					CheckGuildHouseWarEnd();
				}

				pNpc->SendExpToUserList(m_pCom); // °æÇèÄ¡ ºÐ¹è!!
				pNpc->SendDead(m_pCom);
				int diffLevel = abs(m_sLevel - pNpc->m_byClassLevel);
				if(difflevel < 30)
				{
					CheckMaxValue(m_dwXP, 1);		// ¸÷ÀÌ Á×À»¶§¸¸ 1 Áõ°¡!	
					SendXP();
				}
			}
			else									// »ìÀº °æ¿ì Àü±âµ¥¹ÌÁö Ãß°¡
			{
//				pNpc->SetColdDamage();
			}
		}
*/
	}
}

int CNpc::AreaAttack(COM *pCom)
{
	if(!pCom) return 10000;
	if(m_tNpcType == NPCTYPE_GUARD) return -1;
	if(m_tNpcType == NPCTYPE_GUILD_GUARD) return -1;

	int nStandingTime = m_sStandTime;

	// ÃÑ±â°è¿­ ÀÏ¶§´Â Å¸°Ù°úÀÇ °Å¸®°è»êÀ» ´Þ¸®ÇØ¾ß ÇÑ´Ù.
	if(IsCloseTarget(pCom, m_byRange) == FALSE)// Check Code (´ÜÁö ¹æ¾îÀûÀÎ Ãø¸é¿¡¼­ ³ÖÀº ÄÚµå)
	{
		m_NpcState = NPC_TRACING;			// °ø°ÝÇÏ°í µµ¸Á°¡´Â À¯Àú¸¦ µû¶ó Àâ±âÀ§ÇØ(¹ÝÀÀÀ» Á»´õ ºü¸£°Ô) 
		TRACE("AreaAttack - °Å¸® ¸Ö¾î¼­ ½ÇÆÐ\n");
		return -1;							// IsCloseTarget()¿¡ À¯Àú x, y°ªÀ» °»½ÅÇÏ°í Delay = 0À¸·Î ÁÜ
	}

	USER* pUser = NULL;
	int nRange = 1;				// °ø°Ý ¹üÀ§ : 1 - ÁÖÀ§ 8Ä­, 2 - ÁÖÀ§ 24Ä­...
	int nTargetCount = 0;
	int target_uid = -1;

	int center_x = m_sCurX;		// °ø°Ý ¹üÀ§ÀÇ Áß½ÉÁ¡ : Áß½ÉÀÌ °ø°ÝÇÏ´Â NPCÀÏ ¼öµµ ÀÖ°í ¾î¶² Á¡À» ±¸ÇÒ ¼öµµ ÀÖ´Ù.
	int center_y = m_sCurY;		// ÇöÀç´Â ÀÚ±â ÁÖÀ§ °ø°ÝÀ¸·Î ÇÑÁ¤

	switch( (int)m_tSPATRange )
	{
	case	0:
	case	1:
		nRange = 2;
		center_x = m_sCurX;
		center_y = m_sCurY;
		break;

	case	2:
		nRange = 2;
		center_x = m_sCurX;
		center_y = m_sCurY;
		break;

	case	3:
		nRange = 1;
		center_x = m_Target.x;
		center_y = m_Target.y;
		break;

	case	4:
		nRange = 2;
		center_x = m_Target.x;
		center_y = m_Target.y;
		break;

	default:
		nRange = 1;
		center_x = m_sCurX;
		center_y = m_sCurY;
		break;
	}

	MAP* pMap = g_zone[m_ZoneIndex];
	if(!pMap)
	{
		TRACE("AreaAttack - ¸Ê¾ø¾î¼­ ½ÇÆÐ\n");
		return -1;
	}

	int min_x = center_x - nRange;		if( min_x < 0 ) min_x = 0;
	int min_y = center_y - nRange;		if( min_y < 0 ) min_y = 0;
	int max_x = center_x + nRange;
	int max_y = center_y + nRange;

	if(max_x >= pMap->m_sizeMap.cx) max_x = pMap->m_sizeMap.cx - 1;
	if(max_y >= pMap->m_sizeMap.cy) max_y = pMap->m_sizeMap.cy - 1;

	TargetUser tuser[25];


	int		nAvoid = 0;
	int		iRandom = 0;
	int		determine = 0;
	int		iDexHitRate = 0, iLevelHitRate = 0;
	short	sTempHP		= 0;

	int		nHit = 0;

	BOOL	bIsHit = FALSE;
	BOOL	bIsCritical = FALSE;

	int		nDamage		= 0;
	int		nDefense	= 0;

	int nID = m_Target.id;					// Target À» ±¸ÇÑ´Ù.

	// ¸íÁß¿©ºÎ ÆÇ´Ü º¯¼ö ÃÊ±âÈ­
	bIsHit = FALSE;		


	for( int ix = min_x; ix <= max_x; ix++ )
	{
		for( int iy = min_y; iy <= max_y; iy++ )
		{
			target_uid = pMap->m_pMap[ix][iy].m_lUser;

			if( target_uid < USER_BAND || target_uid >= NPC_BAND )
			{
				continue;
			}

			pUser = GetUser(pCom, target_uid - USER_BAND);

			if( !pUser ) continue;
			if( pUser->m_bLive != USER_LIVE ) continue;

			if( ix != pUser->m_curx || iy != pUser->m_cury ) continue;

			if(pUser->m_state == STATE_DISCONNECTED) continue;
			if(pUser->m_tIsOP == 1 ) continue;
			if(pUser->m_bPShopOpen == TRUE) continue;

			// È¸ÇÇ°ª °è»ê 
			nAvoid = pUser->GetAvoid();

			// ¸íÁß¿©ºÎ ÆÇ´Ü
			iRandom = (int)((double)XdY(1, 1000) / 10 + 0.5); 
			
			iDexHitRate = (int)( 30.0 * ( (double)m_sDEX/(m_sDEX + pUser->m_sMagicDEX) ) + 15.0 );
			iLevelHitRate = (int)( 70.0 * ( (double)m_byClassLevel/(pUser->m_sLevel + m_byClassLevel) ) + 15.0);

			determine = iDexHitRate + iLevelHitRate - (nAvoid+pUser->m_Avoid);

			if(determine < ATTACK_MIN) determine = ATTACK_MIN;			// ÃÖ¼Ò 20
			else if(determine > ATTACK_MAX) determine = ATTACK_MAX;		// ÃÖ´ë

			if(iRandom < determine)	bIsHit = TRUE;		// ¸íÁß

			// °ø°Ý ¹Ì½º
			if(bIsHit == FALSE)
			{
				TRACE("AreaAttack - °ø°Ý ¹Ì½º\n");
				continue;
			}

			// ¸íÁßÀÌ¸é //Damage Ã³¸® ----------------------------------------------------------------//

			nDamage = GetFinalDamage(pUser);	// ÃÖÁ¾ ´ë¹ÌÁö

			if(nDamage > 0) pUser->SetDamage(nDamage);

			// ¹æ¾îÃø ³»±¸µµ °¨¼Ò
			pUser->SendDamagedItem(nDamage);

//			if(pUser->m_bLive == USER_DEAD || pUser->m_sHP <= 0)//@@@ ³ªÁß¿¡ °íÄ§
			if(pUser->m_lDeadUsed == 1)
			{
				if(m_NpcVirtualState == NPC_STANDING) 
				{
					if(m_sPid == 179) pUser->GetLevelDownExp(FALSE, -1, TRUE,m_strName); // Ä§°ø¿ë ¸ó½ºÅÍÀÏ°æ¿ì °æÇèÄ¡ 1%°¨¼Ò
					else			pUser->GetLevelDownExp(FALSE, -1, FALSE,m_strName);		// °æÇèÄ¡¿Í ±×¿Ü º¯È­·®¸¦ ¹Ý¿µÇÑ´Ù.
				}
			}

			tuser[nTargetCount].iUid = target_uid;
			tuser[nTargetCount].sHP = pUser->m_sHP;
			tuser[nTargetCount].sMaxHP = pUser->m_sMagicMaxHP;
			pUser->SendHP();

			nTargetCount++;

			if( nTargetCount >= 25 ) break;
		}

		if( nTargetCount >= 25 ) break;
	}

	if( !nTargetCount )
	{
		TRACE("AreaAttack - ¹üÀ§ ¾È¿¡ À¯Àú ¾ø¾î¼­ ½ÇÆÐ\n");
//		return -1;
	}

	CBufferEx TempBuf;
//	2a 0 0 0 ca 1 1 9f 5b 0 0 6a 2c 0 0 0 0
	TempBuf.Add(AREA_ATTACK_RESULT);
	TempBuf.Add(ATTACK_SUCCESS);
	TempBuf.Add( (byte)1 );
	TempBuf.Add((int)(m_sNid + NPC_BAND));
	
	for(int i = 0; i < 1; i++ )
	{
		TempBuf.Add( (int)tuser[i].iUid );
		TempBuf.Add( (short)0 );
		TempBuf.Add( (short)0 );
	}

	SendInsight(pCom, TempBuf, TempBuf.GetLength());
//	SendExactScreen(pCom, TempBuf, TempBuf.GetLength());

	TRACE("AreaAttack - ¼º°ø\n");
	
	return m_sAttackDelay;
}



void CNpc::GiveEventItemNewToUser(USER *pUser)
{
	if( !pUser ) return;
	if( pUser->m_state != STATE_GAMESTARTED ) return;
//	if( pUser->m_iDisplayType == 6 && pUser->m_sLevel > 25) return; //yskang 0.5
	if( pUser->m_iDisplayType == 6) return; //yskang 0.5

	int i;
	CEventItemNew* pNewItem = NULL;

	BOOL bFlag = FALSE;

	int sItemSid = -1;
	BYTE tItemQuality = 0;
	BYTE tItemWear = 0;

	int j;
	int iSlot = -1;

	SYSTEMTIME time;
	GetLocalTime( &time );
	CString strMsg = _T("");

	MYSHORT upper;	upper.i = 0;
	MYINT lower;	lower.i = 0;

	for( i = 0; i < g_arEventItemNew.GetSize(); i++ )
	{
		if( g_arEventItemNew[i] )
		{
			pNewItem = g_arEventItemNew[i];

			if( ::InterlockedCompareExchange( (long*)&(pNewItem->m_lGive), (long)0, (long)1 ) == (long)0 ) continue;

			if( pNewItem->m_sSid != NPC_EVENT_LOTTO )
			{
				// º¹±ÇÀÌ ¾Æ´Ñ °æ¿ì À¯Àú·¦°ú ¸÷ÀÇ ·¦ÀÇ Â÷ÀÌ°¡ 25·¦À» ÃÊ°úÇÏ¸é ÁÖÁö ¾Ê´Â´Ù.
				if(abs(m_byClassLevel - pUser->m_sLevel) > 25)
				{
					if(m_byClassLevel < pUser->m_sLevel) return;
				}
			}
			else
			{
				// º¹±ÇÀº À¯Àú·¦°ú ¸÷ÀÇ ·¦ÀÇ Â÷ÀÌ°¡ 40·¦À» ÃÊ°úÇÏ¸é ÁÖÁö ¾Ê´Â´Ù.
				if(abs(m_byClassLevel - pUser->m_sLevel) > 40)
				{
					if(m_byClassLevel < pUser->m_sLevel) return;
				}
			}

			//////////////////////////////////////////////////////////////////////
			// Ãß°¡µÇ´Â ÀÌº¥Æ® ¾ÆÀÌÅÛÀÌ ÀÖÀ¸¸é ¾Æ·¡¿¡ Ãß°¡ÇÑ´Ù.
			//////////////////////////////////////////////////////////////////////

			// ²É¹Ù±¸´Ï ÀÌº¥Æ®
			if( pNewItem->m_sSid == NPC_EVENT_FLOWER )
			{
				if( time.wYear == 2002 && time.wMonth == 5 && ( time.wDay >= 1 || time.wDay <= 5 ) )
				{
					sItemSid = pNewItem->m_sSid;
					tItemQuality = 0;
				}
				else
				{
					return;
				}
			}

			if( pNewItem->m_sSid == NPC_EVENT_LOTTO )
			{
				if( time.wYear == 2002 && ( ( time.wMonth == 5 && time.wDay >= 16 ) || ( time.wMonth == 6 && time.wDay <= 22 ) ) )
				{
					sItemSid = pNewItem->m_sSid;
					tItemQuality = pNewItem->m_tQuality;
				}
				else
				{
					return;
				}

				if( pUser->m_sLevel < 25 )		// ÀÌº¥Æ® º¹±ÇÀº 25·¹º§ ¹Ì¸¸Àº ÁÖÁö ¾Ê´Â´Ù.
				{
					return;
				}
			}

			/////////////////////////////////////////////////////////////////////

			if( sItemSid < 0 || sItemSid >= g_arItemTable.GetSize() ) return;
			CItemTable* pItemTable = g_arItemTable[sItemSid];

			iSlot = pUser->GetEmptySlot(INVENTORY_SLOT);

			if( iSlot != -1 )
			{
				if(pUser->m_iMaxWeight >= pUser->m_iCurWeight + pItemTable->m_byWeight) bFlag = TRUE;
			}

			switch( sItemSid )
			{
				case NPC_EVENT_FLOWER:
					if(bFlag) { strMsg.Format(IDS_EVENT_FLOWER, pUser->m_strUserID); }
					break;
				case NPC_EVENT_LOTTO:
					if(bFlag) { strMsg.Format(IDS_EVENT_LOTTO); }
					break;
				default:
					return;
			}

			ItemList newItem;
			pUser->ReSetItemSlot( &newItem );

			newItem.tType = TYPE_ITEM;
			newItem.sLevel = pItemTable->m_byRLevel;
			newItem.sSid = sItemSid;
			newItem.sCount = 1;
			newItem.sDuration = pItemTable->m_sDuration;
			newItem.sBullNum = pItemTable->m_sBullNum;
			newItem.tIQ = tItemQuality;
			newItem.iItemSerial = 0;

			for( j = 0; j < MAGIC_NUM; j++ ) newItem.tMagic[j] = 0;

			// ÀÌº¥Æ® ¾ÆÀÌÅÛ ÁÖ±â Å×ÀÌºí¿¡¼­ ³²Àº °³¼ö¸¦ ÇÑ°³ ÁÙ¿©ÁØ´Ù.
			pNewItem->m_sRemain--;

			if( pNewItem->m_sRemain < 0 )
			{
				pNewItem->m_sRemain = 0;
			}
			if( !UpdateEventItemNewRemain( pNewItem ) )
			{
				pNewItem->m_sRemain++;
				::InterlockedExchange( &(pNewItem->m_lGive), 1 );
				return;
			}

			if( pNewItem->m_tSerialExist != 255 )		// ½Ã¸®¾ó ¹øÈ£¸¦ ºÎ¿©ÇØ¾ß ÇÏ´Â »óÈ²ÀÌ¶ó¸é
			{
				upper.i = pNewItem->m_tSerialExist;		// 10000 ¹ø´ë ¹øÈ£
				lower.i = pNewItem->m_sRemain;

				newItem.tMagic[0] = upper.b[0];
				newItem.tMagic[1] = upper.b[1];

				newItem.tMagic[2] = lower.b[0];
				newItem.tMagic[3] = lower.b[1];
				newItem.tMagic[4] = lower.b[2];
				newItem.tMagic[5] = lower.b[3];
			}

			// bFlag - ÀÎº¥¿¡ ºó½½·ÔÀÌ ÀÖ°í, ¹«°ÔÁ¦ÇÑ¿¡ °É¸®Áö ¾Ê¾ÒÀ»¶§ TRUEÀÌ´Ù.
			if(bFlag)
			{
				pUser->m_UserItem[iSlot].tType = newItem.tType;
				pUser->m_UserItem[iSlot].sLevel = newItem.sLevel;
				pUser->m_UserItem[iSlot].sSid = newItem.sSid;
				pUser->m_UserItem[iSlot].sCount = newItem.sCount;
				pUser->m_UserItem[iSlot].sDuration = newItem.sDuration;
				pUser->m_UserItem[iSlot].sBullNum = newItem.sBullNum;
				pUser->m_UserItem[iSlot].tIQ = newItem.tIQ;
				pUser->m_UserItem[iSlot].iItemSerial = newItem.iItemSerial;

				for( j = 0; j < MAGIC_NUM; j++ ) pUser->m_UserItem[iSlot].tMagic[j] = newItem.tMagic[j];

				CBufferEx TempBuf;

				TempBuf.Add(ITEM_LOAD_RESULT);
				TempBuf.Add(SUCCESS);
				TempBuf.Add((BYTE)0x01);

				TempBuf.Add((BYTE)iSlot);
				TempBuf.Add(pUser->m_UserItem[iSlot].sLevel);
				TempBuf.Add(pUser->m_UserItem[iSlot].sSid);
				TempBuf.Add(pUser->m_UserItem[iSlot].sDuration);
				TempBuf.Add(pUser->m_UserItem[iSlot].sBullNum);
				TempBuf.Add(pUser->m_UserItem[iSlot].sCount);
				for(j = 0; j < MAGIC_NUM; j++) TempBuf.Add((BYTE)pUser->m_UserItem[iSlot].tMagic[j]);

				TempBuf.Add((BYTE)pUser->m_UserItem[iSlot].tIQ);

				pUser->Send(TempBuf, TempBuf.GetLength());

				pUser->m_iCurWeight += pItemTable->m_byWeight;
				pUser->GetRecoverySpeed();			// ¾ÆÀÌÅÛ ¹«°Ô¿¡ º¯µ¿ÀÌ »ý±â¸é È¸º¹¼Óµµ º¯È¯

				switch( sItemSid )
				{
					case NPC_EVENT_FLOWER:
						pUser->m_pCom->Announce((LPTSTR)(LPCTSTR)strMsg, SYSTEM_NORMAL);
//						pUser->m_pCom->Announce(strMsg.GetBuffer(strMsg.GetLength()), SYSTEM_NORMAL);
						break;
					case NPC_EVENT_LOTTO:
						pUser->SendSystemMsg( IDS_EVENT_LOTTO, SYSTEM_NORMAL, TO_ME);
						break;
					default:
						return;
				}

				strMsg.Format("(%04d-%02d-%02d %02d:%02d:%02d) %s - Get %d Item(%d)\r\n",
					time.wYear, 
					time.wMonth, 
					time.wDay, 
					time.wHour, 
					time.wMinute, 
					time.wSecond,	
					pUser->m_strUserID, 
					newItem.sSid,
					upper.i * 10000 + lower.i );

				EnterCriticalSection( &m_CS_EventItemLogFileWrite );
				g_fpEventItem.Write( strMsg, strMsg.GetLength() );
				LeaveCriticalSection( &m_CS_EventItemLogFileWrite );
			}
			else
			{
				// ÀÎº¥³Ö±â¿¡ ½ÇÆÐÇÏ¸é ¸Ê¿¡ ¼ÂÆÃ
				GiveItemToMap( pUser->m_pCom, &newItem );

				strMsg.Format("(%04d-%02d-%02d %02d:%02d:%02d) %s - Map %d Item(%d)\r\n",
					time.wYear, 
					time.wMonth, 
					time.wDay, 
					time.wHour, 
					time.wMinute, 
					time.wSecond,	
					pUser->m_strUserID, 
					newItem.sSid,
					upper.i * 10000 + lower.i );

				EnterCriticalSection( &m_CS_EventItemLogFileWrite );
				g_fpEventItem.Write( strMsg, strMsg.GetLength() );
				LeaveCriticalSection( &m_CS_EventItemLogFileWrite );
			}
		}
	}
}

void CNpc::GiveItemToMap(COM *pCom, ItemList *pItem)
{
	CPoint pt = FindNearRandomPointForItem(m_sCurX, m_sCurY);							// ÇöÀç ÀÚ±âÁÂÇ¥¸¦ Á¦¿ÜÇÑ 24Ä­
	if(pt.x <= -1 || pt.y <= -1) return;
	if(pt.x >= g_zone[m_ZoneIndex]->m_sizeMap.cx || pt.y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) return;

	if( InterlockedCompareExchange((LONG*)&g_zone[m_ZoneIndex]->m_pMap[pt.x][pt.y].m_FieldUse, (long)1, (long)0) == (long)0 )
	{
		ItemList* pNewItem = new ItemList;

		memcpy( pNewItem, pItem, sizeof( ItemList ) );

		// ÇØ´ç À¯Àú¿¡°Ô ¾Ë¸°´Ù.			
		//pCom->DelThrowItem();
		pCom->SetThrowItem( pNewItem, pt.x, pt.y, m_ZoneIndex );

		::InterlockedExchange(&g_zone[m_ZoneIndex]->m_pMap[pt.x][pt.y].m_FieldUse, 0);
	}
}

BOOL CNpc::UpdateEventItemNewRemain(CEventItemNew *pEventItem)
{
	SQLSMALLINT	sRet = -1;
	SQLINTEGER	iRetInd = SQL_NTS;

	SQLHSTMT	hstmt = NULL;
	SQLRETURN	retcode;
	TCHAR		szSQL[8000];	::ZeroMemory(szSQL, sizeof(szSQL));

	_sntprintf(szSQL, sizeof(szSQL), TEXT("{call update_event_item_new_remain ( %d, %d, ? )}"), 
		pEventItem->m_sIndex, 
		pEventItem->m_sRemain );

	int db_index = 0;
	CDatabase* pDB = g_DBNew[AUTOMATA_THREAD].GetDB( db_index );
	if( !pDB ) return FALSE;

	retcode = SQLAllocHandle( (SQLSMALLINT)SQL_HANDLE_STMT, pDB->m_hdbc, &hstmt );

	if( retcode != SQL_SUCCESS )
	{
		g_DBNew[AUTOMATA_THREAD].ReleaseDB(db_index);
		return FALSE;
	}

	int i = 1;
	SQLBindParameter( hstmt, i++ ,SQL_PARAM_OUTPUT,SQL_C_SSHORT, SQL_SMALLINT, 0, 0, &sRet, 0, &iRetInd);

	retcode = SQLExecDirect( hstmt, (unsigned char*)szSQL, sizeof(szSQL));
	if( retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO )
	{
	}
	else
	{
		DisplayErrorMsg(hstmt);
		retcode = SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);

		g_DBNew[AUTOMATA_THREAD].ReleaseDB(db_index);
		return FALSE;
	}

	retcode = SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);
	g_DBNew[AUTOMATA_THREAD].ReleaseDB(db_index);

	if( sRet == -1 ) return FALSE;

	return TRUE;
}

void CNpc::UserListSort()
{
	int i, j;
	int total = 0;

	ItemUserRightlist temp;

	for(i = 0; i < NPC_HAVE_USER_LIST; i++)
	{
		m_iHaveItemUid[i].uid = -1;
		m_iHaveItemUid[i].nDamage = 0;

		if( m_DamagedUserList[i].nDamage > 0 )
		{
			m_iHaveItemUid[i].uid = m_DamagedUserList[i].iUid;
			m_iHaveItemUid[i].nDamage = m_DamagedUserList[i].nDamage;
		}
	}

	for(i = 2; i < NPC_HAVE_USER_LIST; i++)
	{
		temp.uid = m_iHaveItemUid[i].uid;
		temp.nDamage = m_iHaveItemUid[i].nDamage;
		
		j = i;

		while(m_iHaveItemUid[j-1].nDamage < temp.nDamage)
		{
			m_iHaveItemUid[j].uid = m_iHaveItemUid[j-1].uid;
			m_iHaveItemUid[j].nDamage = m_iHaveItemUid[j-1].nDamage;
			j--;

			if(j <= 0) break;
		}

		m_iHaveItemUid[j].uid = temp.uid;
		m_iHaveItemUid[j].nDamage = temp.nDamage;
	}

	for(i = 0; i < ITEM_USER_RIGHT_NUM; i++)
	{
		if(m_iHaveItemUid[i].nDamage > 0) total += m_iHaveItemUid[i].nDamage;
	}

	if(total <= 0) total = 1;

	for(i = 0; i < ITEM_USER_RIGHT_NUM; i++)
	{
		j = 0;
		j = (int)( (m_iHaveItemUid[i].nDamage * 100)/total );

		if(j > 100) j = 100;
		else if(j <= 0) j = 1;

		m_iHaveItemUid[i].nDamage = (BYTE)j;	
	}
}

DWORD CNpc::GetItemThrowTime()
{
	DWORD dwCurTime = 0;

	SYSTEMTIME SaveTime;
	GetLocalTime(&SaveTime);
	
	WORD wTemp = 0;
	DWORD dwYear = 0;
	DWORD dwMon = 0;
	DWORD dwDay = 0;
	DWORD dwHour = 0;
	DWORD dwMin = 0;
	DWORD dwSecond = 0;
										// 2 Byte ¹ö¸®°í
	wTemp = SaveTime.wYear << 12;		// »óÀ§ 4 Byte
	wTemp = wTemp >> 12;
	dwYear = (DWORD)wTemp; 
	dwYear = dwYear << 26;

	wTemp = SaveTime.wMonth << 12;		// 4 Byte
	wTemp = wTemp >> 12;
	dwMon = (DWORD)wTemp; 
	dwMon = dwMon << 22;

	wTemp = SaveTime.wDay << 11;		// 5 Byte
	wTemp = wTemp >> 11;
	dwDay = (DWORD)wTemp;
	dwDay = dwDay << 17;

	wTemp = SaveTime.wHour << 11;		// 5 Byte
	wTemp = wTemp >> 11;
	dwHour = (DWORD)wTemp;
	dwHour = dwHour << 12;

	wTemp = SaveTime.wMinute << 10;		// 6 Byte
	wTemp = wTemp >> 10;
	dwMin = (DWORD)wTemp;
	dwMin = dwMin << 6;

	wTemp = SaveTime.wSecond << 10;		// 6 Byte
	wTemp = wTemp >> 10;
	dwSecond = (DWORD)wTemp;

	dwCurTime = dwYear^dwMon^dwDay^dwHour^dwMin^dwSecond;

	return dwCurTime;
}

BOOL CNpc::CheckUserForNpc_Live(int x, int y)
{
	int min_x, min_y, max_x, max_y;

	min_x = m_sCurX - m_bySearchRange;		if( min_x < 0 ) min_x = 0;
	min_y = m_sCurY - m_bySearchRange;		if( min_y < 0 ) min_y = 0;
	max_x = m_sCurX + m_bySearchRange;
	max_y = m_sCurY + m_bySearchRange;

	if(max_x >= g_zone[m_ZoneIndex]->m_sizeMap.cx) max_x = g_zone[m_ZoneIndex]->m_sizeMap.cx - 2;
	if(max_y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) max_y = g_zone[m_ZoneIndex]->m_sizeMap.cy - 2;

	int ix, iy;
	int target_uid;

	int tempLevel = 0, oldLevel = 1000;

	for(ix = min_x; ix <= max_x; ix++)
	{
		for(iy = min_y; iy <= max_y; iy++)
		{
			target_uid = m_pOrgMap[ix][iy].m_lUser;

			if( target_uid >= USER_BAND && target_uid < NPC_BAND ) return FALSE;
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//	Summon À¸·Î ÀÎÇØ º¯°æµÈ À§Ä¡Á¤º¸¸¦ ÁÖº¯¿¡ º¸³½´Ù.
//
void CNpc::SendNpcInfoBySummon(COM *pCom)
{
	int min_x = 0, min_y = 0;
	int max_x = 0, max_y = 0;

	int sx = m_sCurX / SIGHT_SIZE_X;
	int sy = m_sCurY / SIGHT_SIZE_Y;

	int delete_index = 0;
	char delete_send[1024];		::ZeroMemory(delete_send, sizeof(delete_send));
	FillNpcInfo(delete_send, delete_index, INFO_DELETE);

	min_x = (sx-1)*SIGHT_SIZE_X;
	max_x = (sx+2)*SIGHT_SIZE_X;
	min_y = (sy-1)*SIGHT_SIZE_Y;
	max_y = (sy+2)*SIGHT_SIZE_Y;

	SendToRange(pCom, delete_send, delete_index, min_x, min_y, max_x, max_y);
}
