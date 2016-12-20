// NpcThread.h: interface for the CNpcThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPCTHRED_H__ACE39ADA_BAFB_4EA8_A953_AD9FD18C2918__INCLUDED_)
#define AFX_NPCTHRED_H__ACE39ADA_BAFB_4EA8_A953_AD9FD18C2918__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Npc.h"
#include "COM.h"

UINT NpcThreadProc(LPVOID pParam /* NPC_THREAD_INFO ptr */);

typedef struct _NPC_THREAD_INFO
{
	COM*	pCom;
	CNpc*	pNpc[NPC_NUM];
	long	m_lNpcUsed[NPC_NUM];	//&&&&&&&&&&&& Test Code	

	HWND	hWndMsg;
} NPC_THREAD_INFO;

class CNpcThread  
{
public:
	
	CNpcThread();
	virtual ~CNpcThread();

public:
	void InitThreadInfo(HWND hwnd);
//	USER*	m_pUser;
	COM*	m_pCom;
	CNpc*	m_pNpc[NPC_NUM];
	
	NPC_THREAD_INFO		m_ThreadInfo;
	CWinThread*			m_pThread;
};

#endif // !defined(AFX_NPCTHRED_H__ACE39ADA_BAFB_4EA8_A953_AD9FD18C2918__INCLUDED_)
