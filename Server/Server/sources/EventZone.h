// EventZone.h: interface for the CEventZone class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTZONE_H__682FC698_6EF0_4D7D_8E16_3F4FB2D094FA__INCLUDED_)
#define AFX_EVENTZONE_H__682FC698_6EF0_4D7D_8E16_3F4FB2D094FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GuildHouseWar.h"

#define MAX_EVENT_USER	4		// 현재 최대 인원수는 버디인원수로 제한한다.
#define MAX_SINGLE_EVENT	5		// 

struct	_EVENT_ZONE
{
	long		m_lUsed;
	long		m_lCurNum;
	short		m_sEventZone;
	BYTE		m_tSuccessType;
	BYTE		m_tStartType;
	BYTE		m_tEventTime;
	DWORD		m_dwStartTime;
	DWORD		m_dwInterTick;

	UserList	m_arUserList[MAX_EVENT_USER];
	CWordArray	m_arNpcList;
};

class CEventZone  
{
public:
	void SingleInit();
	int GetEmptyEventZone();
	void RemoveUserInEventZone(int iEventZone);
	void CheckSingleEventZoneWarEnd(int iZone);

	CEventZone();
	virtual ~CEventZone();

public:
	void CheckUserStateInEventZone(int iZone);

	CWordArray	m_arEventZone;
	_EVENT_ZONE	m_SingleEventZone[MAX_SINGLE_EVENT];		
};

#endif // !defined(AFX_EVENTZONE_H__682FC698_6EF0_4D7D_8E16_3F4FB2D094FA__INCLUDED_)
