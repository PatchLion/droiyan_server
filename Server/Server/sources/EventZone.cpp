// EventZone.cpp: implementation of the CEventZone class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "USER.h"
#include "EventZone.h"
#include "ServerDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CServerDlg *g_pMainDlg;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEventZone::CEventZone()
{
	SingleInit();
	m_arEventZone.RemoveAll();
	m_arEventZone.Add(60);
	m_arEventZone.Add(64);
	m_arEventZone.Add(65);
	m_arEventZone.Add(66);
	m_arEventZone.Add(67);
}

CEventZone::~CEventZone()
{

}

int CEventZone::GetEmptyEventZone()
{
	for(int i = 0; i < MAX_SINGLE_EVENT; i++)
	{
		if(InterlockedCompareExchange((LONG*)&m_SingleEventZone[i].m_lUsed, (long)1, (long)0) == (long)0)
		{
			m_SingleEventZone[i].m_lCurNum = 0;
			m_SingleEventZone[i].m_sEventZone = 0;
			m_SingleEventZone[i].m_tSuccessType = 0;
			m_SingleEventZone[i].m_tStartType = 0;
			m_SingleEventZone[i].m_tEventTime = 0;
			m_SingleEventZone[i].m_dwStartTime = 0;
			m_SingleEventZone[i].m_dwInterTick = 0;

			for(int j = 0; j < MAX_EVENT_USER; j++)
			{
				m_SingleEventZone[i].m_arUserList[j].uid = -1;
				::ZeroMemory(m_SingleEventZone[i].m_arUserList[j].strUserName, sizeof(m_SingleEventZone[i].m_arUserList[j].strUserName));		
			}

			m_SingleEventZone[i].m_arNpcList.RemoveAll();
			m_SingleEventZone[i].m_dwStartTime = GetTickCount();

			return i;
		}
	}

	return -1;
}

void CEventZone::SingleInit()
{
	for(int i = 0; i < MAX_SINGLE_EVENT; i++)
	{
		m_SingleEventZone[i].m_lUsed = 0;
		m_SingleEventZone[i].m_lCurNum = 0;
		m_SingleEventZone[i].m_sEventZone = 0;
		m_SingleEventZone[i].m_tSuccessType = 0;
		m_SingleEventZone[i].m_tStartType = 0;
		m_SingleEventZone[i].m_tEventTime = 0;
		m_SingleEventZone[i].m_dwStartTime = 0;
		m_SingleEventZone[i].m_dwInterTick = 0;

		for(int j = 0; j < MAX_EVENT_USER; j++)
		{
			m_SingleEventZone[i].m_arUserList[j].uid = -1;
			::ZeroMemory(m_SingleEventZone[i].m_arUserList[j].strUserName, sizeof(m_SingleEventZone[i].m_arUserList[j].strUserName));		
		}

		m_SingleEventZone[i].m_arNpcList.RemoveAll();
	}
}

void CEventZone::RemoveUserInEventZone(int iEventZone)
{
	int i, j;
	int uid = 0, nLen = 0;
	USER *pUser = NULL;

	for(i = 0; i < MAX_EVENT_USER; i++)
	{
		uid = m_SingleEventZone[iEventZone].m_arUserList[i].uid;
		if(uid < 0) continue;

		COM *pCom = g_pMainDlg->GetCOM();
		if ( pCom )
			pUser = pCom->GetUserUid(uid);
		else
			return;

		// IKING 2001.1.
		if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) continue;
		//

		if(strcmp(pUser->m_strUserID, m_SingleEventZone[iEventZone].m_arUserList[i].strUserName) != 0)
		{
			CString szSource = m_SingleEventZone[iEventZone].m_arUserList[i].strUserName;

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

//		pUser->m_tGuildHouseWar = GUILD_WAR_AFFTER;

		pUser->m_tQuestWar = GUILD_WAR_AFFTER;
		if(m_SingleEventZone[iEventZone].m_sEventZone == pUser->m_curz && pUser->m_bLive == USER_LIVE) pUser->TownPotal();
	}

	for(i = 0; i < m_SingleEventZone[iEventZone].m_arNpcList.GetSize(); i++)
	{
		uid = m_SingleEventZone[iEventZone].m_arNpcList[i];
		if(uid < 0 || uid >= g_arNpc.GetSize()) continue;

		if(g_arNpc[uid]->m_NpcState != NPC_DEAD)
		{
			g_arNpc[uid]->Dead();
		}
	}

	m_SingleEventZone[iEventZone].m_lCurNum = 0;
	m_SingleEventZone[iEventZone].m_sEventZone = 0;
	m_SingleEventZone[iEventZone].m_tSuccessType = 0;
	m_SingleEventZone[iEventZone].m_tStartType = 0;
	m_SingleEventZone[iEventZone].m_tEventTime = 0;
	m_SingleEventZone[iEventZone].m_dwStartTime = 0;
	m_SingleEventZone[iEventZone].m_dwInterTick = 0;

	for(j = 0; j < MAX_EVENT_USER; j++)
	{
		m_SingleEventZone[iEventZone].m_arUserList[j].uid = -1;
		::ZeroMemory(m_SingleEventZone[iEventZone].m_arUserList[j].strUserName, sizeof(m_SingleEventZone[iEventZone].m_arUserList[j].strUserName));		
	}

	m_SingleEventZone[iEventZone].m_arNpcList.RemoveAll();

}

void CEventZone::CheckSingleEventZoneWarEnd(int iZone)
{
	int i, j;

	for(i = 0; i < MAX_SINGLE_EVENT; i++)
	{
		if(iZone == m_SingleEventZone[i].m_sEventZone)
		{
			if(m_SingleEventZone[i].m_lUsed == 1)
			{
				InterlockedIncrement(&m_SingleEventZone[i].m_lCurNum);

				if(m_SingleEventZone[i].m_lCurNum >= m_SingleEventZone[i].m_arNpcList.GetSize())
				{
					int uid = 0, nLen = 0;
					USER *pUser = NULL;

					for(j = 0; j < MAX_EVENT_USER; j++)
					{
						uid = m_SingleEventZone[i].m_arUserList[j].uid;
						if(uid < 0) continue;

						nLen = strlen(m_SingleEventZone[i].m_arUserList[j].strUserName);
						if(nLen <= 0 || nLen > CHAR_NAME_LENGTH) continue;

						uid = m_SingleEventZone[i].m_arUserList[j].uid;

						COM *pCom = g_pMainDlg->GetCOM();
						if ( pCom )
							pUser = pCom->GetUserUid(uid);
						else
							return;

						pUser = pCom->GetUserUid(uid);
						// IKING 2001.1.
						if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) continue;
						//

						if(strcmp(pUser->m_strUserID, m_SingleEventZone[i].m_arUserList[j].strUserName) != 0)
						{
							CString szSource = m_SingleEventZone[i].m_arUserList[j].strUserName;

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

						pUser->m_tQuestWar = GUILD_WAR_AFFTER;
						if(m_SingleEventZone[i].m_sEventZone == pUser->m_curz && pUser->m_bLive == USER_LIVE)
						{
							pUser->SendSystemMsg( IDS_USER_QUEST_END, SYSTEM_NORMAL, TO_ME);
						}
					}

					m_SingleEventZone[i].m_dwInterTick = GetTickCount();
				}
			}
		}
	}
}

void CEventZone::CheckUserStateInEventZone(int iZone)
{
	int i;
	int iNum = 0;

	for(i = 0; i < MAX_SINGLE_EVENT; i++)
	{
		if(iZone == m_SingleEventZone[i].m_sEventZone)
		{
			if(m_SingleEventZone[i].m_lUsed == 1)
			{
				RemoveUserInEventZone(i);
				m_SingleEventZone[i].m_lUsed = 0;
			}
		}
	}
}
