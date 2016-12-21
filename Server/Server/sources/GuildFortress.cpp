// GuildFortress.cpp: implementation of the CGuildFortress class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "USER.h"
#include "GuildFortress.h"
#include "Extern.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGuildFortress::CGuildFortress()
{
	int i;

	m_dwRepairCost = 0;
//	m_iCityDegree = 0;
	m_sFortressID = 0;
	m_iGuildSid = 0;

	::ZeroMemory(m_strGuildName, sizeof(m_strGuildName));
	::ZeroMemory(m_strMasterName, sizeof(m_strMasterName));

	m_tTaxRate = 0;
	arStoreTax.RemoveAll();

	m_iGuildDN = 0;

	m_bHaveGuild = 0;						  // 현재 길드에 속한 상점이다	TRUE	
	m_lUsed = 0;							  // 길드전 수행중인지 아닌지 표시...
	m_lChangeUsed = 0;

	m_tWarType = 0;	

	m_lListUsed = 0;						  // 길드전에 참가하는 길드 리스트	
	m_lListCount = 0;

	m_dwStartTick = 0;
	m_iStandingTime = 50;

	m_iZone = 0;							  // 포탈존
	m_iPotalX = 0;
	m_iPotalY = 0;

	m_arNpcList.RemoveAll();
	m_arWarNpcList.RemoveAll();
	m_arRepairNpcList.RemoveAll();

	for(i = 0; i < GUILDFORTRESS_ATTACK_MAX_NUM; i++)
	{
		m_arAttackGuild[i].lUsed = 0;
		m_arAttackGuild[i].lGuild = 0;
		::ZeroMemory(m_arAttackGuild[i].strGuildName, sizeof(m_arAttackGuild[i].strGuildName));
	}

	for(i = 0; i < GUILD_GUARD_MAX_NUM; i++) m_iGuardList[i] = 0;

	for(i = 0; i < FORTRESS_TARGET_MAX_NUM; i++)
	{
		m_arFortressTarget[i].lUsed = 0;
		m_arFortressTarget[i].sTargertID = 0;
	}

	for(i = 0; i < GUILD_REPAIR_MAX_NUM; i++)
	{
		m_arRepairDBList[i].sHP = 0;
		m_arRepairDBList[i].sNid = 0;
		m_arRepairDBList[i].sUid = 0;
	}

	for(i = 0; i < MAX_GUILD_USER; i++)
	{
		m_arCityRankList[i].lUsed = 0;
		m_arCityRankList[i].lCityRank = 0;
		::ZeroMemory(m_arCityRankList[i].strUserID, sizeof(m_arCityRankList[i].strUserID));
	}

	m_lViolenceUsed = 0;	
	m_dwViolenceTick = 0;
	m_arViolenceNpcList.RemoveAll();

	InitMsgTime();
}

CGuildFortress::~CGuildFortress()
{

}

///////////////////////////////////////////////////////////////////////////////
//	 에 Buffer 의 내용을 카피한다.
//
void CGuildFortress::StrToGuildAttList(TCHAR *pBuf, int iguild)
{
/*	int i, index = 0;
	int nLen = 0, gid = 0;

	for(i = 0; i < GUILDFORTRESS_ATTACK_MAX_NUM; i++)
	{
		gid = GetInt(pBuf, index);
		m_arAttackGuild[i].lGuild = gid;
		::ZeroMemory(m_arAttackGuild[i].strGuildName, sizeof(m_arAttackGuild[i].strGuildName));

		if(gid > 0 && gid < g_arGuildData.GetSize())
		{
			nLen = strlen(g_arGuildData[gid]->m_strGuildName);
			if(nLen > 0) 
			{
				InterlockedIncrement(&m_lListCount);
				strncpy(m_arAttackGuild[i].strGuildName, g_arGuildData[gid]->m_strGuildName, nLen);
			}
		}
	}
*/
	int i, j;
	int nLen = 0;

	nLen = strlen(pBuf);
	if(nLen <= 0 || nLen > CHAR_NAME_LENGTH) return;

	for(i = 0; i < g_arGuildData.GetSize(); i++)
	{
		if(!g_arGuildData[i]) continue;

		if(strcmp(g_arGuildData[i]->m_strGuildName, pBuf) == 0)
		{
			for(j = 0; j < GUILDFORTRESS_ATTACK_MAX_NUM; j++)
			{
				if(InterlockedCompareExchange((LONG*)&m_arAttackGuild[j].lUsed, (long)1, (long)0) == (long)0)
				{
					::ZeroMemory(m_arAttackGuild[j].strGuildName, sizeof(m_arAttackGuild[j].strGuildName));
					m_arAttackGuild[j].lGuild = iguild;
					strncpy(m_arAttackGuild[j].strGuildName, g_arGuildData[i]->m_strGuildName, nLen);
					return;
				}
			}
		}
	}
}

void CGuildFortress::StrGuildGuardList(TCHAR *pBuf)
{
	int index = 0;
	for(int i = 0; i < GUILD_GUARD_MAX_NUM; i++)
	{
		m_iGuardList[i] = GetInt(pBuf, index);
	}
}

///////////////////////////////////////////////////////////////////////////////
//	Buffer 에 GuildAttList 정보를 Copy 한다.
//
void CGuildFortress::GuildAttListToStr(TCHAR *pBuf)
{
	int	index = 0;
	for(int i = 0; i < GUILDFORTRESS_ATTACK_MAX_NUM; i++)
	{
		SetInt(pBuf, m_arAttackGuild[i].lGuild,index);
	}
}

void CGuildFortress::GuildGuardListToStr(TCHAR *pBuf)
{
	int	index = 0;
	for(int i = 0; i < GUILD_GUARD_MAX_NUM; i++)
	{
		SetInt(pBuf, m_iGuardList[i],index);
	}
}

///////////////////////////////////////////////////////////////////////////////
//	각 NPC에 길드전임을 알린다.
//
void CGuildFortress::SetNpcToFortressWarBegin()
{
	int i, j;
	int nid = 0;

	CNpc* pNpc = NULL;

	for(i = 0; i < m_arNpcList.GetSize(); i++)
	{
		nid = m_arNpcList[i];

		pNpc = GetNpc(nid);
		if(!pNpc) continue;

		if(pNpc->m_sEZone >= GUILD_FORTRESS_NPC_BAND)
		{
			for(j = 0; j < FORTRESS_TARGET_MAX_NUM; j++)
			{
				if(m_arFortressTarget[j].sTargertID == pNpc->m_sNid)
				{
					m_arWarNpcList.Add(pNpc->m_sNid);
					pNpc->m_tGuildWar = GUILD_WARRING;
					pNpc->m_tNCircle = NPC_NCIRCLE_DEF_STATE;
					pNpc->m_sHP = pNpc->m_sMaxHP;
					pNpc->m_lFortressState = 0;
					break;
				}
			}
		}
		else if(pNpc->m_tNpcType == NPCTYPE_GUILD_GUARD || pNpc->m_sEZone >= GUILD_REPAIR_NPC_BAND)
		{
			m_arWarNpcList.Add(pNpc->m_sNid);
			pNpc->m_tGuildWar = GUILD_WARRING;
			pNpc->m_lFortressState = 0;

			if(pNpc->m_tNpcType == NPCTYPE_GUILD_GUARD) pNpc->m_tNpcAttType = 1;
		}
	}
}

CNpc* CGuildFortress::GetNpc(int nid)
{
	if( nid < 0 || nid >= g_arNpc.GetSize() ) return NULL;

	return g_arNpc[nid];

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//	각 NPC에 길드전이 끝났음을 알린다.
//
void CGuildFortress::SetNpcToFortressWarEnd(COM *pCom)
{
	int i, j;
	int nid = 0;

	m_dwRepairCost = 0;

	DWORD dwCost = 0;
	CNpc* pNpc = NULL;

	BOOL bRepair = FALSE;

	for(i = 0; i < m_arWarNpcList.GetSize(); i++)
	{
		nid = m_arWarNpcList[i];

		pNpc = GetNpc(nid);
		if(!pNpc) continue;

		bRepair = FALSE;

		for(j = 0; j < GUILD_REPAIR_MAX_NUM; j++)
		{
			if(m_arRepairDBList[j].sUid == pNpc->m_sEZone)
			{
				if(m_arRepairDBList[j].sHP < pNpc->m_sMaxHP)
				{
					m_arRepairDBList[j].sHP = pNpc->m_sHP;
					pNpc->m_tRepairDamaged = NPC_NEED_REPAIR_STATE;					

					dwCost += (pNpc->m_sMaxHP - pNpc->m_sHP) * 100;

					bRepair = TRUE;
					break;
				}				
			}
		}

		if(!bRepair) pNpc->m_sHP = pNpc->m_sMaxHP;

		pNpc->m_tGuildWar = GUILD_WAR_AFFTER;		
		pNpc->m_tNpcAttType = 0;
		pNpc->m_byColor = 0;
		pNpc->m_lFortressState = 0;

		if(pNpc->m_tNpcType == NPCTYPE_GUILD_DOOR)
		{
			if(pNpc->m_sHP <= 0)
			{
				pNpc->m_sHP = 1;		// Dead상태 --> Live상태로(공성전에서 부서진 문으로 일단 다른 유저의 접근을 막기위해) 
				pNpc->m_bFirstLive = TRUE;
			}
		}
	}

	InitMsgTime();						// Msg 시간을 다시 셋팅
	m_dwRepairCost = dwCost;
	m_arWarNpcList.RemoveAll();
}

void CGuildFortress::FortressRepairListToStr(TCHAR *pBuf)
{
	int	index = 0;
	for(int i = 0; i < GUILD_REPAIR_MAX_NUM; i++)
	{
		SetShort(pBuf, m_arRepairDBList[i].sUid,index);
		SetShort(pBuf, m_arRepairDBList[i].sHP,index);
	}
}

void CGuildFortress::StrFortressRepairList(CByteArray &Buf)//(TCHAR *pBuf)
{
	int i, index = 0;

	TCHAR TempBuf[1024];
	::ZeroMemory(TempBuf, sizeof(TempBuf));

	for(i = 0; i < Buf.GetSize(); i++)
	{
		TempBuf[i] = Buf[i];
	}

	for(i = 0; i < GUILD_REPAIR_MAX_NUM; i++)
	{
		m_arRepairDBList[i].sUid = GetShort(TempBuf, index);
		m_arRepairDBList[i].sHP = GetShort(TempBuf, index);
	}
}

void CGuildFortress::InitMsgTime()
{
	m_MsgTimer[0].iMsgTime = 60;
	m_MsgTimer[0].iUsed = 0;

	m_MsgTimer[1].iMsgTime = 30;
	m_MsgTimer[1].iUsed = 0;

	m_MsgTimer[2].iMsgTime = 20;
	m_MsgTimer[2].iUsed = 0;

	m_MsgTimer[3].iMsgTime = 10;
	m_MsgTimer[3].iUsed = 0;

	m_MsgTimer[4].iMsgTime = 5;
	m_MsgTimer[4].iUsed = 0;

	m_MsgTimer[5].iMsgTime = 3;
	m_MsgTimer[5].iUsed = 0;
}

void CGuildFortress::UpdateInitFortress()
{
	int i;

//	m_iCityDegree = 0;
	m_tTaxRate = 0;
	m_iGuildDN = 0;

	m_tWarType = GUILD_WAR_PREPARE;
	m_tGuildWar = GUILD_WAR_AFFTER;

	m_iStandingTime = 50;

	m_bHaveGuild = TRUE;				  // 현재 길드에 속한 Fortress = TRUE	
	m_lUsed = 0;						  // 길드전 수행중인지 아닌지 표시...
	m_lChangeUsed = 0;

	m_lListUsed = 0;
	m_lListCount = 0;

	for(i = 0; i < GUILDFORTRESS_ATTACK_MAX_NUM; i++)
	{
		m_arAttackGuild[i].lUsed = 0;
		m_arAttackGuild[i].lGuild = 0;
		::ZeroMemory(m_arAttackGuild[i].strGuildName, sizeof(m_arAttackGuild[i].strGuildName));
	}

	// 지금 무조건 끝나면 민심은 초기화가 된다.
	// 따라서 서버를 다시 재 가동 되는 시점에 맞추어서 다시 셋팅된다.
	// 이문제를 해결하려면 g_arGuildUserData에 해당 시민 등급을 셋팅해주어야한다.
	// 추후 보강 요망
	for(i = 0; i < MAX_GUILD_USER; i++)
	{
		m_arCityRankList[i].lUsed = 0;
		m_arCityRankList[i].lCityRank = 0;
		::ZeroMemory(m_arCityRankList[i].strUserID, sizeof(m_arCityRankList[i].strUserID));
	}

	InitMemFortress(GUILD_WAR_PREPARE);
}

/////////////////////////////////////////////////////////////////////////////////////////
//	요새에 대한 메모리 DB의 내용을 초기화 한다.
//
void CGuildFortress::InitMemFortress(BYTE tGuildWarType)
{
	int i;
	int nSize = g_arFortressSharedMemory.GetSize();
	CSharedMemory* pShared = NULL;
	CMemFortress* pData = NULL;

	for(i = 0; i < nSize; i++)
	{
		pShared = g_arFortressSharedMemory[i];
		
		if(pShared == NULL) return;
		if(pShared->m_hMapping == NULL) return;
		
		pData = (CMemFortress*) pShared->m_lpData;
		
		if(pData == NULL) return;
		
		if(pData->m_sFortressID == m_sFortressID)
		{
			pData->m_iGuildSid = m_iGuildSid;
			pData->m_sTaxRate = 0;
			pData->m_dwStoreDN = 0;
			pData->m_tWarType = tGuildWarType;

			GuildAttListToStr(pData->m_AttackList);
			FortressRepairListToStr(pData->m_RepairList);
			break;
		}
	}
}

void CGuildFortress::SetInitFortress()
{
//	m_iCityDegree = 0;
	m_iGuildSid = 900000;

	::ZeroMemory(m_strGuildName, sizeof(m_strGuildName));
	::ZeroMemory(m_strMasterName, sizeof(m_strMasterName));
	m_tTaxRate = 0;
	m_iGuildDN = 0;

	m_bHaveGuild = FALSE;					  // 현재 길드에 속한 상점이다	TRUE	
	m_lUsed = 0;							  // 길드전 수행중인지 아닌지 표시...
	m_lViolenceUsed = 0;
	m_lChangeUsed = 0;

	m_tWarType = GUILD_WAR_DECISION;
	m_tGuildWar = GUILD_WAR_AFFTER;

	m_dwStartTick = 0;
	m_iStandingTime = 50;

//	m_wPlanWarTime.wDay = m_wPlanWarTime.wDay + 7;
	m_wMopPartyTime.wYear = 2030;		// 길드가 해산되면서 나머지는 모두 초기화를
}


void CGuildFortress::ApplyTaxToStore()
{
	int i, j;

	for(i = 0; i < arStoreTax.GetSize(); i++)
	{
		for(j = 0; j < g_arStore.GetSize(); j++)
		{
			if(g_arStore[j] == NULL) continue;

			if(g_arStore[j]->m_sStoreID == arStoreTax[i])
			{
				g_arStore[j]->m_sRate = (short)m_tTaxRate;
				break;
			}
		}
	}
}

int CGuildFortress::GetTotalCityValue()
{
	int iCount=  0;
	int i, sum = 0;
	int avg = 0;

	for(i = 0; i < MAX_GUILD_USER; i++)
	{
		if(m_arCityRankList[i].lUsed == 1)
		{
			sum += m_arCityRankList[i].lCityRank;
			iCount++;
		}
	}

	if(iCount <= 0) return 0;

	avg = (int)(sum / iCount);
	sum = 0;

	switch(avg)
	{
	case -5: case -4:
		sum = 40;
		break;
	case -3: case -2: case -1:
		sum = 30;
		break;
	case 0: case 1:
		sum = 20;
		break;
	case 2: case 3:
		sum = 10;
		break;
	case 4: case 5:
		sum = 0;
		break;
	default:
		sum = 0;
		break;
	}

	sum += m_tTaxRate;

	return sum;
}

void CGuildFortress::AddGuildUserForFortressCityRank(TCHAR *strUserID, int sCityRank)
{
	int nLen = strlen(strUserID);

	if(nLen <= 0 || nLen > CHAR_NAME_LENGTH) return;

	for(int i = 0; i < MAX_GUILD_USER; i++)
	{
		if(InterlockedCompareExchange((LONG*)&m_arCityRankList[i].lUsed, (long)1, (long)0) == (long)0)
		{
			::ZeroMemory(m_arCityRankList[i].strUserID, sizeof(m_arCityRankList[i].strUserID));
			m_arCityRankList[i].lCityRank = sCityRank;
			strncpy(m_arCityRankList[i].strUserID, strUserID, nLen);
			return;
		}
	}
}

void CGuildFortress::SetNpcToFortressViolenceBegin()//(COM *pCom)
{
	int i;
	int nid = 0;

	CNpc* pNpc = NULL;

	for(i = 0; i < m_arViolenceNpcList.GetSize(); i++)
	{
		nid = m_arViolenceNpcList[i];

		pNpc = GetNpc(nid);
		if(!pNpc) continue;

		pNpc->m_NpcVirtualState = NPC_MOVING;
		pNpc->m_NpcState = NPC_LIVE;			
	}
}

BOOL CGuildFortress::SetNpcToFortressViolenceEnd(COM *pCom)
{
	int i;
	int nid = 0;

	BOOL bAlive = FALSE;

	CNpc* pNpc = NULL;

	for(i = 0; i < m_arViolenceNpcList.GetSize(); i++)
	{
		nid = m_arViolenceNpcList[i];

		pNpc = GetNpc(nid);
		if(!pNpc) continue;
		pNpc->m_tGuildWar = GUILD_WAR_AFFTER;

		if(pNpc->m_NpcState != NPC_DEAD || pNpc->m_sHP > 0)
		{
			pNpc->m_NpcVirtualState = NPC_WAIT;
			pNpc->m_NpcState = NPC_DEAD;
			pNpc->m_sHP = 0;
			pNpc->SendDead(pCom);

			bAlive = TRUE;
		}
	}

	return bAlive;
}

void CGuildFortress::SetInitFortressViolence()
{
	m_iGuildSid = 900000;

	::ZeroMemory(m_strGuildName, sizeof(m_strGuildName));
	::ZeroMemory(m_strMasterName, sizeof(m_strMasterName));
	m_tTaxRate = 0;
	m_iGuildDN = 0;

	m_bHaveGuild = FALSE;					  // 현재 길드에 속한 상점이다	TRUE	
	m_lUsed = 0;							  // 길드전 수행중인지 아닌지 표시...
	m_lViolenceUsed = 0;
	m_lChangeUsed = 0;

	m_tWarType = GUILD_WAR_DECISION;
	m_tGuildWar = GUILD_WAR_AFFTER;

	m_dwStartTick = 0;
	m_iStandingTime = 50;

	m_wMopPartyTime.wYear = 2030;		// 길드가 해산되면서 나머지는 모두 초기화를
}

void CGuildFortress::GetOutof(COM *pCom)
{
	int mapindex;
	int type = 0;
	int nLen = 0;

	USER *pUser = NULL;

	for(int i = 0; i < MAX_USER; i++)				// 모든 유저를 튕긴다.
	{
		mapindex = -1;
		type = 0;
		pUser = pCom->GetUserUid(i);

		if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) continue;		

		type = pUser->CheckInvalidMapType();
		mapindex = pUser->GetGuildMapIndex(type);
		if(mapindex >= 0)
		{												//길드전이 일어나는 상점지역이면
			if(m_iZone == pUser->m_curz && pUser->m_tIsOP != 1 )
			{
				pUser->TownPotal();				
			}
			else if(g_arMapTable[mapindex]->m_sStoreZone && pUser->m_tIsOP != 1)		
			{											// 방어길드원이 아니면 모두 마을로	
				pUser->TownPotal();				
			}
		}
	}
}
