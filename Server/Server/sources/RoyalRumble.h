// RoyalRumble.h: interface for the CRoyalRumble class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROYALRUMBLE_H__A03B2299_DE11_4F49_9C84_1B8DC79A4966__INCLUDED_)
#define AFX_ROYALRUMBLE_H__A03B2299_DE11_4F49_9C84_1B8DC79A4966__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "map.h"
#include "user.h"
#include "RoyalRumbleUser.h"

typedef CTypedPtrArray <CPtrArray, CRoyalRumbleUser*> RoyalRumbleUserArray;

class CRoyalRumble  
{
public:
	void Init(int year, int month, int day);

	CRoyalRumble();
	virtual ~CRoyalRumble();

public:
	void BridgeServerARKWinnerChangeReq();
	void Apply();
	void InitRRUser();
	void ForceInit();
	void UpdateRoyalRumbleWinner();
	void GiveItemToWinner(USER* pUser);
	void RobItem();
	void UpdateRoyalRumbleData();
	void BBSWrite(char* strTitle, char* strContent);
	void ForceExit();
	void CheckRRBravoEnd();
	void Exit(USER* pUser);
	BOOL Enter(USER* pUser);
	BOOL CheckEnteringByMaxUser();
	BOOL CheckEnteringByTime();
	USER* GetWinner();
	void End();
	void CheckRREnd();
	void Start();
	void CountDownStart();
	void CheckRRStatus();

	RoyalRumbleUserArray		m_arRRUser;
	MAP*						m_pRRMap;

	int							m_iMaxApplyNum;
	int							m_iMinLevel;
	int							m_iStartYear;
	int							m_iStartMonth;
	int							m_iStartDay;
	int							m_iZoneNum;

	int							m_iItemSid;

	int							m_iStartCount;
	int							m_iCurrentStartCount;
	int							m_iPlayMinute;
	int							m_iCurrentPlaySecond;
	int							m_iBravoSecond;
	int							m_iCurrentBravoSecond;

	BYTE						m_bRRStatus;
	CTime						m_timeApplyStart;
	CTime						m_timeApplyEnd;
	CTime						m_timeEnterStart;
	CTime						m_timeEnterEnd;

	BOOL						m_bNextRRInit;

	DWORD						m_dwLastEnterMsg;
	DWORD						m_dwLastStartMsg;

	ItemList					m_ItemRR;
};

#endif // !defined(AFX_ROYALRUMBLE_H__A03B2299_DE11_4F49_9C84_1B8DC79A4966__INCLUDED_)
