// NpcThread.cpp: implementation of the CNpcThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "NpcThread.h"

#include "Extern.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DELAY				250
//#define STEP_DELAY			250

DWORD	g_dwLastTimeCount	= GetTickCount();
DWORD	g_dwCurrTimeCount	= GetTickCount();
//////////////////////////////////////////////////////////////////////
// NPC Thread Callback Function
//
UINT NpcThreadProc(LPVOID pParam /* NPC_THREAD_INFO ptr */)
{
	NPC_THREAD_INFO*	pInfo	= (NPC_THREAD_INFO*)pParam;
	CNpc*				pNpc	= NULL;
	COM*				pCom	= NULL;
	CPoint				pt;

	int					i			= 0;
	DWORD				dwDiffTime	= 0;

	DWORD				dwSleep		= 250;

	srand( GetCurrentThreadId() );
	myrand( 1, 10000 ); myrand( 1, 10000 );

	if(!pInfo) return 0;

	while(!g_bNpcExit)
	{
		if( g_bShutDown )
		{
			Sleep( 250 );
			continue;
		}

		for(i = 0; i < NPC_NUM; i++)
		{
			pNpc = pInfo->pNpc[i];
			pCom = pInfo->pCom;
			if( !pNpc ) continue;
			if(pNpc->m_NpcVirtualState == NPC_WAIT) continue; 
			if(pNpc->m_tNpcType == NPCTYPE_DOOR && !pNpc->m_bFirstLive) continue;
//			if(pNpc->m_tNpcType == NPCTYPE_GUILD_MARK && !pNpc->m_bFirstLive) continue;
			
			g_dwCurrTimeCount = GetTickCount();

			if(pNpc->m_lNowSummoning) continue;		// Summon 중이면 아무짓 안한다.

			if(pNpc->m_Delay > (int)dwSleep && !pNpc->m_bFirstLive && pNpc->m_Delay != 0) 
			{
				pNpc->m_Delay -= (int)dwSleep;
				if(pNpc->m_Delay < 0) pNpc->m_Delay = 0;

				//적발견시...
				if(pNpc->m_NpcState == NPC_STANDING && pNpc->FindEnemy(pCom))
				{
					pNpc->m_NpcState = NPC_ATTACKING;
					pNpc->m_Delay = 0;
				}

				continue;
			}
			
			if(g_dwCurrTimeCount - g_dwLastTimeCount >= 900)
			{
				g_dwLastTimeCount = g_dwCurrTimeCount;
				
				int index = 0;
				BYTE tAbnormalType		= pNpc->m_tAbnormalKind;	//GetByte(pNpc->m_strAbnormal, index);
				DWORD dwAbnormalTime	= pNpc->m_dwAbnormalTime;	//GetDWORD(pNpc->m_strAbnormal, index);
				
				switch(tAbnormalType)
				{
				case ABNORMAL_NONE:
					break;
				case ABNORMAL_POISON:
					break;
				case ABNORMAL_CONFUSION:
					break;
				case ABNORMAL_PARALYSIS:
					break;
				case ABNORMAL_BLIND:
					break;
				case ABNORMAL_LIGHT:
					break;
				case ABNORMAL_FIRE:
					dwDiffTime = g_dwCurrTimeCount - pNpc->m_dwLastAbnormalTime;
					if(dwDiffTime >= 5000)	
					{
						if(pNpc->SetDamage((dwDiffTime / 5) * 4) == FALSE)
						{
							pNpc->SendExpToUserList(pCom); // 경험치 분배!!
							pNpc->SendDead(pCom);
						}
					}
					break;
				case ABNORMAL_COLD:
					if((g_dwCurrTimeCount - pNpc->m_dwLastAbnormalTime) > dwAbnormalTime)	// 상태이상이 풀릴 시간이 됬으면
					{
						pNpc->m_tAbnormalKind = ABNORMAL_BYTE_NONE;
						pNpc->m_dwAbnormalTime = 0;
						pNpc->m_dwLastAbnormalTime = GetTickCount();
					}
					break;
				}
			}

			switch(pNpc->m_NpcState)
			{
			case NPC_LIVE:					// 방금 살아난 경우
				pNpc->NpcLive(pCom);
				break;

			case NPC_STANDING:						// 하는 일 없이 서있는 경우
				pNpc->NpcStanding(pCom);
				break;
			
			case NPC_MOVING:
				pNpc->NpcMoving(pCom);
				break;

			case NPC_ATTACKING:
				pNpc->NpcAttacking(pCom);
				break;

			case NPC_TRACING:
				pNpc->NpcTracing(pCom);
				break;

			case NPC_FIGHTING:
				pNpc->NpcFighting(pCom);
				break;

			case NPC_BACK:
				pNpc->NpcBack(pCom);
				break;

			case NPC_STRATEGY:
				break;

			case NPC_DEAD:
				pNpc->NpcTrace(_T("NpcDead"));
				pNpc->m_NpcState = NPC_LIVE;
				break;

			default:
				break;
			}

			pNpc->m_dwLastThreadTime = GetTickCount();
		}

//		if(dwSleep < 10) dwSleep = 10;
		dwSleep = 100;
		Sleep(dwSleep);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNpcThread::CNpcThread()
{
	m_pCom =	NULL;
//	m_pNpc =	NULL;
	m_pThread = NULL;

	for( int i = 0; i < NPC_NUM; i++ )
	{
		m_pNpc[i] = NULL;
		m_ThreadInfo.m_lNpcUsed[i] = 0;	//&&&&&&&&&&&&&&&&&&& Test Code
	}

}

CNpcThread::~CNpcThread()
{
	for( int i = 0; i < NPC_NUM; i++ )
	{
		if(m_pNpc[i])
		{
			delete m_pNpc[i];
			m_pNpc[i] = NULL;
		}
	}
}

void CNpcThread::InitThreadInfo(HWND hwnd)
{
	m_ThreadInfo.hWndMsg	= hwnd;
	m_ThreadInfo.pCom		= m_pCom;
}
