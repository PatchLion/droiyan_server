// GuildHouseWar.cpp: implementation of the CGuildHouseWar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "USER.h"
#include "GuildHouseWar.h"
#include "Extern.h"
#include "ServerDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CServerDlg *g_pMainDlg;
extern CRITICAL_SECTION m_CS_FileWrite;
extern int g_ChatEnable[];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGuildHouseWar::CGuildHouseWar()
{
	m_iCity = 0;

	m_CurrentGuild.lUsed = 0;
	m_CurrentGuild.iWarZone = -1;
	m_CurrentGuild.dwIntervalTick = 0;
	m_CurrentGuild.arNpcList.RemoveAll();

	for(int i = 0; i < MAX_GUILD_HOUSE_NUM; i++)
	{
		m_TopList[i].iLastValue = 0;	
		m_TopList[i].lGuild = 0;
		m_TopList[i].dwLastTime = 0;
		m_TopList[i].iGuildLevel = 0;
		m_TopList[i].iGuildNum = 0;

		::ZeroMemory(m_TopList[i].strGuildName, sizeof(m_TopList[i].strGuildName));
	}
}

CGuildHouseWar::~CGuildHouseWar()
{

}

void CGuildHouseWar::InitGuild()
{
	for(int i = 0;  i< MAX_GUILD_HOUSE_USER; i++)
	{
		m_CurrentGuild.arUserList[i].uid = 0;
		::ZeroMemory(m_CurrentGuild.arUserList[i].strUserName, sizeof(m_CurrentGuild.arUserList[i].strUserName));
	}

	m_CurrentGuild.dwTimer = 0;
	m_CurrentGuild.dwIntervalTick = 0;
	m_CurrentGuild.iCurValue = 0;	
	m_CurrentGuild.lGuild = 0;	
	m_CurrentGuild.iGuildLevel = 0;	
}


BOOL CGuildHouseWar::CheckGuildHouseWarEnd(USER** user_array)
{
	int i, j;
	int uid = 0, nLen = 0;
	int nCount = 0;

	USER* pUser = NULL;

	for(i = 0; i < MAX_GUILD_HOUSE_USER; i++)
	{
		nLen = strlen(m_CurrentGuild.arUserList[i].strUserName);
		if(nLen <= 0 || nLen > CHAR_NAME_LENGTH) continue;

		uid = m_CurrentGuild.arUserList[i].uid;

		pUser = user_array[uid];

		if(strcmp(pUser->m_strUserID, m_CurrentGuild.arUserList[i].strUserName) != 0)
		{
			CString szSource = m_CurrentGuild.arUserList[i].strUserName;

			pUser = NULL;

			for(j = 0; j < MAX_USER; j++)
			{
				if(user_array[j]->m_state == STATE_DISCONNECTED || user_array[j]->m_state == STATE_LOGOUT ) continue;

				if(!szSource.CompareNoCase(user_array[j]->m_strUserID ) ) pUser = user_array[j];
			}
		}

		if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) continue;

		if(pUser->m_curz == m_CurrentGuild.iWarZone) nCount++;
	}

	if(nCount <= 0) return FALSE;
	
	return TRUE;
}

void CGuildHouseWar::CheckGuildHouseRank()
{	
	int i;	
	TopGuildList value;

	DWORD tick = GetTickCount();

	if(m_CurrentGuild.lGuild <= 0) return;
	if(m_CurrentGuild.iCurValue <= 0) return;
	if(tick < m_CurrentGuild.dwTimer) return;

	value.iLastValue = m_CurrentGuild.iCurValue;
	value.dwLastTime = tick - m_CurrentGuild.dwTimer;
	value.iGuildLevel = m_CurrentGuild.iGuildLevel;
	value.iGuildNum = m_CurrentGuild.iGuildNum;
	value.lGuild = m_CurrentGuild.lGuild;

	if(value.lGuild > 0 && value.lGuild < g_arGuildData.GetSize())
	{
		::ZeroMemory(value.strGuildName, sizeof(value.strGuildName));

		int nLen = strlen(g_arGuildData[value.lGuild]->m_strGuildName);
		strncpy(value.strGuildName, g_arGuildData[value.lGuild]->m_strGuildName, nLen);
	}
	else return;

	for(i = 0; i < MAX_GUILD_HOUSE_NUM; i++)				// 순위중에 먼저 있는지 검색한다.
	{
		if(m_TopList[i].lGuild == value.lGuild)				// 같은길드가 있으면 값을 비교한다.
		{													// 작으면 그냥 리턴...
			if(value.iLastValue < m_TopList[i].iLastValue) return;
			else if(value.iLastValue == m_TopList[i].iLastValue)
			{												// 같으면 이하 비교값을 찾아서 갱신할 필요성을 찾는다.			
				if(value.dwLastTime > m_TopList[i].dwLastTime) return;
				else if(value.dwLastTime == m_TopList[i].dwLastTime)
				{
					if(value.iGuildLevel > m_TopList[i].iGuildLevel) return;
					else if(value.iGuildLevel == m_TopList[i].iGuildLevel){
						if(value.iGuildNum > m_TopList[i].iGuildNum) return;
					}
				}
			}
			m_TopList[i] = value;
			break;
		}
	}
	if(i==MAX_GUILD_HOUSE_NUM){//루프가 제한길드 수를 다 돌고 나왔을때 같은 길드가 없다는 의미이므로...
		m_TopList[MAX_GUILD_HOUSE_NUM - 1] = value;			
	}
																// 비교해서 순위를 바꾼다.
	for(i = 0; i < MAX_GUILD_HOUSE_NUM-1 ; i++)
	{
		for(int j=i+1;j<MAX_GUILD_HOUSE_NUM;j++){
			if(m_TopList[i].iLastValue < m_TopList[j].iLastValue){
				SwapTopGuildList(m_TopList[i],m_TopList[j]);//몹잡은수가 비교대상보다 많으면 바꿔
			}
			else if(m_TopList[i].iLastValue == m_TopList[j].iLastValue){//같으면?
				if(m_TopList[i].dwLastTime > m_TopList[j].dwLastTime){
					SwapTopGuildList(m_TopList[i],m_TopList[j]);//시간이 더 적게 걸렸음 바꿔
				}
				else if(m_TopList[i].dwLastTime == m_TopList[j].dwLastTime){//같으면?
					if(m_TopList[i].iGuildLevel > m_TopList[j].iGuildLevel){
						SwapTopGuildList(m_TopList[i],m_TopList[j]);//레벨이 더 낮으면 바꿔
					}
					else if(m_TopList[i].iGuildLevel == m_TopList[j].iGuildLevel){//같으면?
						if(m_TopList[i].iGuildNum > m_TopList[j].iGuildNum){
							SwapTopGuildList(m_TopList[i],m_TopList[j]);//그럼 인원수가 적거나 같으면 바꿔
						}	
					}
				} 
			}
		}
	}

	/*if(m_TopList[i].iLastValue < value.iLastValue)
		{
			SwapTopGuildList(m_TopList[i], value);
		}
		else if(m_TopList[i].iLastValue == value.iLastValue)
		{
			if(m_TopList[i].dwLastTime > value.dwLastTime) SwapTopGuildList(m_TopList[i], value);
			else if(m_TopList[i].dwLastTime == value.dwLastTime) 
			{
				if(m_TopList[i].iGuildLevel > value.iGuildLevel) SwapTopGuildList(m_TopList[i], value);
				else if(m_TopList[i].iGuildLevel == value.iGuildLevel)
				{
					if(m_TopList[i].iGuildNum > value.iGuildNum) SwapTopGuildList(m_TopList[i], value);
				}
			}
		}
	}
	*/
	CString	str;

	SYSTEMTIME time;
	GetLocalTime(&time);

	CMemGuildHouseRank*	pMDGuildHouse = NULL;
	int	nGuildHouseSize = g_arGuildHouseSharedMemory.GetSize();
	
	for(i = 0; i < nGuildHouseSize; i++)
	{
		pMDGuildHouse = (CMemGuildHouseRank*) g_arGuildHouseSharedMemory[i]->m_lpData;
		if(!pMDGuildHouse) continue;
		
		pMDGuildHouse->tSid = i + 1;
		pMDGuildHouse->lGuild = m_TopList[i].lGuild;
		pMDGuildHouse->iLastValue = m_TopList[i].iLastValue;
		pMDGuildHouse->iGuildNum = m_TopList[i].iGuildNum;
		pMDGuildHouse->iGuildLevel = m_TopList[i].iGuildLevel;
		pMDGuildHouse->dwLastTime = m_TopList[i].dwLastTime;

		// IKING 2002.1.
		// 파일에 쓴다
		/*
		str.Format( "(%dM %dD %dH %dMIN)\tSid-%d iGuildID-%d tNum-%d sValue-%d sGuildLevel-%d iLevelTime-%d\r\n",
			time.wMonth, time.wDay, time.wHour, time.wMinute, pMDGuildHouse->tSid, pMDGuildHouse->lGuild, 
			pMDGuildHouse->iGuildNum, pMDGuildHouse->iLastValue, pMDGuildHouse->iGuildLevel, pMDGuildHouse->dwLastTime );

		EnterCriticalSection( &m_CS_FileWrite );
		g_fpGuildHouseRank.Write( str, str.GetLength() );
		LeaveCriticalSection( &m_CS_FileWrite );
		*/
		//
	}

}

void CGuildHouseWar::CheckGuildUserEnd()
{
	
}

BOOL CGuildHouseWar::CheckGuildMopEnd()
{
	int uid = 0;
	int nCount = m_CurrentGuild.arNpcList.GetSize();

	for(int i = 0; i < m_CurrentGuild.arNpcList.GetSize(); i++)
	{
		uid = m_CurrentGuild.arNpcList[i];

		if(uid < 0 || uid >= g_arNpc.GetSize()) continue;

//		TRACE("%s MOP, state %d\n", g_arNpc[uid]->m_strName, g_arNpc[uid]->m_NpcVirtualState);
		if(g_arNpc[uid]->m_NpcVirtualState == NPC_WAIT)
		{
//			TRACE("%s MOP\n", g_arNpc[uid]->m_strName);
			nCount--;
		}
	}

	if(nCount <= 0) return TRUE;

	return FALSE;
}

void CGuildHouseWar::SwapTopGuildList(TopGuildList &s, TopGuildList &d)
{
	int nLen = 0;
	TopGuildList temp;

	temp.iLastValue	 = s.iLastValue;
	temp.dwLastTime	 = s.dwLastTime;
	temp.iGuildLevel = s.iGuildLevel;
	temp.iGuildNum	 = s.iGuildNum;
	temp.lGuild		 = s.lGuild;

	::ZeroMemory(temp.strGuildName, sizeof(temp.strGuildName));
	nLen = strlen(s.strGuildName);
	strncpy(temp.strGuildName, s.strGuildName, nLen);

	s.iLastValue = d.iLastValue;
	s.dwLastTime = d.dwLastTime;
	s.iGuildLevel= d.iGuildLevel;
	s.iGuildNum	 = d.iGuildNum;
	s.lGuild	 = d.lGuild;

	::ZeroMemory(s.strGuildName, sizeof(s.strGuildName));
	nLen = strlen(d.strGuildName);
	strncpy(s.strGuildName, d.strGuildName, nLen);

	d.iLastValue = temp.iLastValue;
	d.dwLastTime = temp.dwLastTime;
	d.iGuildLevel= temp.iGuildLevel;
	d.iGuildNum	 = temp.iGuildNum;
	d.lGuild	 = temp.lGuild;

	::ZeroMemory(d.strGuildName, sizeof(d.strGuildName));
	nLen = strlen(temp.strGuildName);
	strncpy(d.strGuildName, temp.strGuildName, nLen);

}

void CGuildHouseWar::SetNpcListToWarEnd()
{
	int i;
	int uid = 0;

	for(i = 0; i < m_CurrentGuild.arNpcList.GetSize(); i++)
	{
		uid = m_CurrentGuild.arNpcList[i];
		if(uid < 0 || uid >= g_arNpc.GetSize()) continue;

		if(g_arNpc[uid]->m_NpcState != NPC_DEAD)
		{
			g_arNpc[uid]->Dead();
		}

		g_arNpc[uid]->m_NpcVirtualState = NPC_WAIT;
	}

}

void CGuildHouseWar::SetUserListToWarEnd(COM *pCom)
{
	int i, j;
	int uid = 0, nLen = 0;
	USER *pUser = NULL;

	for(i = 0; i < MAX_GUILD_HOUSE_USER; i++)
	{
		nLen = strlen(m_CurrentGuild.arUserList[i].strUserName);
		if(nLen <= 0 || nLen > CHAR_NAME_LENGTH) continue;

		uid = m_CurrentGuild.arUserList[i].uid;

		pUser = pCom->GetUserUid(uid);
		// IKING 2001.1.
		if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) continue;
		//

		if(strcmp(pUser->m_strUserID, m_CurrentGuild.arUserList[i].strUserName) != 0)
		{
			CString szSource = m_CurrentGuild.arUserList[i].strUserName;

			pUser = NULL;

			// IKING 2001.1.
			USER *pTUser;
			for(j = 0; j < MAX_USER; j++)
			{
				pTUser = pCom->GetUserUid(j);
				if ( pTUser == NULL ) continue;

				if ( pTUser->m_state == STATE_DISCONNECTED || pTUser->m_state == STATE_LOGOUT ) continue;

				if(!szSource.CompareNoCase(pTUser->m_strUserID)) pUser = pTUser;
			}
			//
		}

		if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) continue;

		pUser->m_tGuildHouseWar = GUILD_WAR_AFFTER;

		if(m_CurrentGuild.iWarZone == pUser->m_curz && pUser->m_bLive == USER_LIVE && pUser->m_tIsOP != 1 )	pUser->TownPotal();
	}
}

//void CGuildHouseWar::SetUserListToWarEnd(USER** user_array)
void CGuildHouseWar::SetUserListToWarEnd()
{
	int i, j;
	int uid = 0, nLen = 0;
	USER *pUser = NULL;

	for(i = 0; i < MAX_GUILD_HOUSE_USER; i++)
	{
		nLen = strlen(m_CurrentGuild.arUserList[i].strUserName);
		if(nLen <= 0 || nLen > CHAR_NAME_LENGTH) continue;

		uid = m_CurrentGuild.arUserList[i].uid;

		COM *pCom = g_pMainDlg->GetCOM();
		if ( pCom )
			pUser = pCom->GetUserUid(uid);
		else
			return;

		// IKING 2001.1.
		if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) continue;
		//

		if(strcmp(pUser->m_strUserID, m_CurrentGuild.arUserList[i].strUserName) != 0)
		{
			CString szSource = m_CurrentGuild.arUserList[i].strUserName;

			pUser = NULL;

			// IKING 2001.1.
			USER *pTUser;
			for(j = 0; j < MAX_USER; j++)
			{
				pTUser = pCom->GetUserUid(j);
				if ( pTUser == NULL ) continue;

				if(pTUser->m_state == STATE_DISCONNECTED || pTUser->m_state == STATE_LOGOUT ) continue;

				if(!szSource.CompareNoCase(pTUser->m_strUserID ) ) pUser = pTUser;
			}
			//
		}

		if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) continue;

		pUser->m_tGuildHouseWar = GUILD_WAR_AFFTER;

		if(m_CurrentGuild.iWarZone == pUser->m_curz && pUser->m_bLive == USER_LIVE && pUser->m_tIsOP != 1 ) pUser->TownPotal();
	}
}


void CGuildHouseWar::SendTownPotalMsg(COM *pCom)
{
	int i, j;
	int uid = 0, nLen = 0;
	USER *pUser = NULL;

	for(i = 0; i < MAX_GUILD_HOUSE_USER; i++)
	{
		nLen = strlen(m_CurrentGuild.arUserList[i].strUserName);
		if(nLen <= 0 || nLen > CHAR_NAME_LENGTH) continue;

		uid = m_CurrentGuild.arUserList[i].uid;

		pUser = pCom->GetUserUid(uid);
		// IKING 2001.1.
		if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) continue;
		//

		if(strcmp(pUser->m_strUserID, m_CurrentGuild.arUserList[i].strUserName) != 0)
		{
			CString szSource = m_CurrentGuild.arUserList[i].strUserName;

			pUser = NULL;

			// IKING 2001.1.
			USER *pTUser;
			for(j = 0; j < MAX_USER; j++)
			{
				pTUser = pCom->GetUserUid(j);
				if ( pTUser == NULL ) continue;

				if(pTUser->m_state == STATE_DISCONNECTED || pTUser->m_state == STATE_LOGOUT ) continue;

				if(!szSource.CompareNoCase(pTUser->m_strUserID)) pUser = pTUser;
			}
			//
		}

		if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) continue;

		if(m_CurrentGuild.iWarZone == pUser->m_curz && pUser->m_bLive == USER_LIVE)
		{
			pUser->SendSystemMsg( IDS_USER_QUEST_END, SYSTEM_NORMAL, TO_ME);
		}
	}

	m_CurrentGuild.dwIntervalTick = GetTickCount();
}

void CGuildHouseWar::ResetGuildHouseRank()
{
	CString str = _T("");

	SYSTEMTIME time;
	GetLocalTime(&time);

	CMemGuildHouseRank*	pMDGuildHouse = NULL;
	int	nGuildHouseSize = g_arGuildHouseSharedMemory.GetSize();
	
	for(int i = 0; i < nGuildHouseSize; i++)
	{
		pMDGuildHouse = (CMemGuildHouseRank*) g_arGuildHouseSharedMemory[i]->m_lpData;
		if(!pMDGuildHouse) continue;

		// IKING 2002.1.
		// 파일에 쓴다
		
		str.Format( "(%dM %dD %dH %dMIN)\tSid-%d iGuildID-%d tNum-%d sValue-%d sGuildLevel-%d iLevelTime-%d\r\n",
			time.wMonth, time.wDay, time.wHour, time.wMinute, pMDGuildHouse->tSid, pMDGuildHouse->lGuild, 
			pMDGuildHouse->iGuildNum, pMDGuildHouse->iLastValue, pMDGuildHouse->iGuildLevel, pMDGuildHouse->dwLastTime );

		EnterCriticalSection( &m_CS_FileWrite );
		g_fpGuildHouseRank.Write( str, str.GetLength() );
		LeaveCriticalSection( &m_CS_FileWrite );
		
		//
		
		m_TopList[i].iLastValue = 0;	
		m_TopList[i].lGuild = 0;
		m_TopList[i].dwLastTime = 0;
		m_TopList[i].iGuildLevel = 0;
		m_TopList[i].iGuildNum = 0;

		::ZeroMemory(m_TopList[i].strGuildName, sizeof(m_TopList[i].strGuildName));

		pMDGuildHouse->tSid = i + 1;
		pMDGuildHouse->lGuild = 0;
		pMDGuildHouse->iLastValue = 0;
		pMDGuildHouse->iGuildNum = 0;
		pMDGuildHouse->iGuildLevel = 0;
		pMDGuildHouse->dwLastTime = 0;
	}
}
