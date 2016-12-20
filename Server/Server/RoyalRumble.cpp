// RoyalRumble.cpp: implementation of the CRoyalRumble class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "RoyalRumble.h"
#include "ServerDlg.h"
#include "extern.h"
#include "bufferex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CServerDlg *g_pMainDlg;
extern CString			g_strARKRRWinner;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRoyalRumble::CRoyalRumble()
{
	m_iMaxApplyNum = 200;		// 최대 신청 허용

	m_iMinLevel = 26;			// 최소 필요 레벨

	m_bRRStatus = RR_EMPTY;		// 로얄 럼블의 현재 상태

	m_iStartCount = 3;			// 시작시에 세주는 카운트
	m_iPlayMinute = 30;			// 로얄 럼블 경기 시간(분)

	m_iZoneNum = 59;			// 로얄 럼블 개최 존

	m_iBravoSecond = 60;		// 경기 후 자축 시간(초)

	m_bNextRRInit = FALSE;		// 다음 경기를 설정했는지에 대한 플래그

	m_iItemSid = 840;			// 상품으로 주는 아이템의 SID
}

CRoyalRumble::~CRoyalRumble()
{
	m_bRRStatus = RR_EMPTY;

	for( int i = 0; i < m_arRRUser.GetSize(); i++ )
	{
		if( m_arRRUser[i] )
		{
			delete m_arRRUser[i];
		}
	}
	m_arRRUser.RemoveAll();
}

void CRoyalRumble::Init(int year, int month, int day)
{
	MAP* pMap = NULL;

	for( int i = 0; i < g_zone.GetSize(); i++ )
	{
		if( g_zone[i] )
		{
			if( g_zone[i]->m_Zone == m_iZoneNum )
			{
				pMap = g_zone[i];
				break;
			}
		}
	}

	if( !pMap )	// 로열럼블 맵을 안가지고 있다. 초기화 실패
	{
		return;
	}

	m_pRRMap = pMap;
	m_iCurrentStartCount = m_iStartCount;
	m_bRRStatus = RR_IDLE;
	m_iCurrentPlaySecond = 0;
	m_iCurrentBravoSecond = 0;
	m_bNextRRInit = FALSE;

	// 신청 가능 시간
	m_timeApplyStart	= CTime( year, month, day, 19, 0, 0 );
	m_timeApplyEnd		= CTime( year, month, day, 19, 50, 0 );

	// 입장 가능 시간
	m_timeEnterStart	= CTime( year, month, day, 19, 50, 0 );
	m_timeEnterEnd		= CTime( year, month, day, 20, 0, 0 );

	m_dwLastEnterMsg = GetTickCount();
	m_dwLastStartMsg = GetTickCount();

	m_ItemRR.sSid = m_iItemSid;

	m_ItemRR.sLevel		= g_arItemTable[m_ItemRR.sSid]->m_byRLevel;
	m_ItemRR.sCount		= 1;
	m_ItemRR.sDuration	= g_arItemTable[m_ItemRR.sSid]->m_sDuration;
	m_ItemRR.sBullNum	= g_arItemTable[m_ItemRR.sSid]->m_sBullNum;

	m_ItemRR.tMagic[0]	= (BYTE)137;
	m_ItemRR.tMagic[1]	= (BYTE)141;
	m_ItemRR.tMagic[2]	= (BYTE)128;
	m_ItemRR.tMagic[3]	= (BYTE)42;
	m_ItemRR.tMagic[4]	= (BYTE)31;
	m_ItemRR.tMagic[5]	= (BYTE)33;
	m_ItemRR.tIQ		= UNIQUE_ITEM;

	m_ItemRR.iItemSerial= 0;
	m_ItemRR.dwMoney	= 0;
}

void CRoyalRumble::CheckRRStatus()
{
	CTime curTime = CTime::GetCurrentTime();
	CString strMsg;

	switch( m_bRRStatus )
	{
/*	case	RR_IDLE:	// 현재 경기가 벌어지고 있지 않다
		if( curTime >= m_timeApplyStart && curTime < m_timeApplyEnd )	// 경기 시작 시간이라면
		{
			m_bRRStatus = RR_APPLY;		// 현재 상태를 신청상태로 바꾸고
		}
		break;
*/
	case	RR_EMPTY:	// 이서버는 로얄럼블 대회가 없다.
		break;

	case	RR_IDLE:	// 현재 경기가 벌어지고 있지 않다
		if( curTime >= m_timeEnterStart && curTime < m_timeEnterEnd )	// 입장 시간이라면
		{
			m_bRRStatus = RR_ENTERING;		// 현재 상태를 입장상태로 바꾼다
			break;
		}

		if( curTime >= m_timeApplyStart && curTime < m_timeApplyEnd )
		{
			Apply();
		}
		break;

	case	RR_ENTERING:
		if( curTime >= m_timeEnterEnd )
		{
			m_bRRStatus = RR_ENTERING_END;
			strMsg = _T("로얄럼블 격투가 시작됩니다.");
			g_pMainDlg->AnnounceZone( (LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE, m_iZoneNum );
			break;
		}

		if( GetTickCount() - m_dwLastEnterMsg > 2 * 60 * 1000 )
		{
			strMsg.Format( "로열럼블에 참여하실 분들은 %d시 %02d분 이전까지 경기장으로 입장해주시기 바랍니다", m_timeEnterEnd.GetHour(), m_timeEnterEnd.GetMinute() );
			g_pMainDlg->AnnounceAllServer( (LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE );
			m_dwLastEnterMsg = GetTickCount();
		}
		break;

	case	RR_ENTERING_END:
		CountDownStart();
		break;

	case	RR_START:
		if( GetTickCount() - m_dwLastStartMsg > 2 * 60 * 1000 )
		{
			strMsg = _T("현재 NEO A.R.K 격투장에서 로열럼블 격투가 열리고 있습니다");
			g_pMainDlg->AnnounceAllServer( (LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE );
			m_dwLastStartMsg = GetTickCount();
		}

		CheckRREnd();
		break;

	case	RR_END:
		CheckRRBravoEnd();
		break;
	}
}

void CRoyalRumble::CountDownStart()
{
	if( m_bRRStatus != RR_ENTERING_END )
	{
		return;
	}

	if( m_iCurrentStartCount <= 0 && m_bRRStatus != RR_START )	// 카운트를 다 세었는데도 시작되지 않은 상황
	{
		Start();
		return;
	}

	CString strMsg;

	if( m_iCurrentStartCount <= 0 )		// 카운트를 다 세었다. 시작 시킨다.
	{
		m_bRRStatus = RR_START;
		m_iCurrentStartCount = m_iStartCount;

		Start();
		return;
	}

	strMsg.Format("%d", m_iCurrentStartCount );		m_iCurrentStartCount--;
	g_pMainDlg->AnnounceZone( (LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE, m_iZoneNum );
}

void CRoyalRumble::Start()
{
	CString strMsg;

	strMsg = _T("시작 !!!");
	g_pMainDlg->AnnounceZone( (LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE, m_iZoneNum );

	m_dwLastStartMsg = GetTickCount();

	m_bRRStatus = RR_START;
}

void CRoyalRumble::CheckRREnd()
{
	m_iCurrentPlaySecond++;

	CString strMsg;
	int iRemainSecond = (m_iPlayMinute * 60) - m_iCurrentPlaySecond;

	if( iRemainSecond == 5 * 60 )		// 끝나기 5분전
	{
		strMsg = _T("5분 후 로열럼블 경기가 종료됩니다");
		g_pMainDlg->AnnounceZone( (LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE, m_iZoneNum );
	}
	else if( iRemainSecond == 1 * 60 )
	{
		strMsg = _T("1분 후 로열럼블 경기가 종료됩니다");
		g_pMainDlg->AnnounceZone( (LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE, m_iZoneNum );
	}
	else if( iRemainSecond <= 5 && iRemainSecond > 0 )
	{
		strMsg.Format( "%d", iRemainSecond );
		g_pMainDlg->AnnounceZone( (LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE, m_iZoneNum );
	}

	if( m_iCurrentPlaySecond >= m_iPlayMinute * 60 )
	{
		End();
	}

	GetWinner();
}

void CRoyalRumble::End()
{
	CString strMsg;
	char strTitle[128];
	char strContent[2048];

	CTime time = CTime::GetCurrentTime();

	sprintf( strTitle, "%d월 %d일 로열럼블 대회 우승자", time.GetMonth(), time.GetDay() );

	m_bRRStatus = RR_END;
	g_strARKRRWinner = _T("");
	m_bNextRRInit = FALSE;

	USER* pUser = GetWinner();

	if( !pUser )
	{
		strMsg = _T("로열럼블 경기가 종료되었습니다");
		g_pMainDlg->AnnounceAllServer( (LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE );

		sprintf( strContent, "\r\n %d월 %d일 로열럼블 대회는\r\n\r\n우승자가 없습니다.", time.GetMonth(), time.GetDay() );

		BBSWrite( strTitle, strContent );

		UpdateRoyalRumbleWinner();
		InitRRUser();

		return;
	}

	strMsg.Format( "%s님이 로열럼블 우승자가 되셨습니다. 축하드립니다", pUser->m_strUserID );
	g_pMainDlg->AnnounceAllServer( (LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE );

	sprintf( strContent, "\r\n %d월 %d일 로열럼블 대회 우승자는\r\n\r\n %s 님 입니다\r\n\r\n *** 축하드립니다 ***", time.GetMonth(), time.GetDay(), pUser->m_strUserID );

	BBSWrite( strTitle, strContent );

	g_strARKRRWinner.Format( "%s", pUser->m_strUserID );

	UpdateRoyalRumbleWinner();

	GiveItemToWinner( pUser );

	InitRRUser();
}

USER* CRoyalRumble::GetWinner()
{
	int i = 0;
	int iCount = 0;

	USER* pUser = NULL;
	USER* pWinner = NULL;

	COM* pCom = g_pMainDlg->GetCOM();
	if( !pCom ) return NULL;

	if( m_bRRStatus == RR_END )	// 게임이 끝났을 경우 처리
	{
		for( i = 0; i < m_arRRUser.GetSize(); i++ )
		{
			if( m_arRRUser[i] )
			{
				if( !m_arRRUser[i]->m_bLive ) continue;
				if( m_arRRUser[i]->m_iUID < 0 || m_arRRUser[i]->m_iUID > MAX_USER ) continue;

				pUser = pCom->GetUserUid( m_arRRUser[i]->m_iUID );

				if( !pUser ) continue;
				if( pUser->m_state != STATE_GAMESTARTED ) continue;
				if( pUser->m_curz != m_iZoneNum ) continue;
				if( strcmp( pUser->m_strUserID, m_arRRUser[i]->m_strUserID ) ) continue;
				if( pUser->m_bLive == FALSE ) continue;
				if( pUser->m_sHP <= 0 ) continue;

				iCount++;	// 이 사람은 살아남은 사람이다.
				pWinner = pUser;
			}
		}

		// 단 1명만 살아남아야 우승자로 처리
		if( iCount == 1 )
		{
			return pWinner;
		}
		else
			return NULL;
	}
	else if( m_bRRStatus == RR_START )	// 게임 중 처리
	{
		for( i = 0; i < m_arRRUser.GetSize(); i++ )
		{
			if( m_arRRUser[i] )
			{
				if( !m_arRRUser[i]->m_bLive ) continue;
				if( m_arRRUser[i]->m_iUID < 0 || m_arRRUser[i]->m_iUID > MAX_USER ) continue;

				iCount++;
			}
		}

		if( iCount <= 1 )
		{
			m_bRRStatus = RR_END;
			End();
			return NULL;
		}
	}

	return NULL;
}

BOOL CRoyalRumble::CheckEnteringByTime()
{
	if( m_bRRStatus == RR_ENTERING ) return TRUE;

	return FALSE;
}

BOOL CRoyalRumble::CheckEnteringByMaxUser()
{
	if( m_arRRUser.GetSize() < m_iMaxApplyNum ) return TRUE;

	return FALSE;
}

BOOL CRoyalRumble::Enter(USER *pUser)
{
	if( !pUser ) return FALSE;

	CRoyalRumbleUser* pNewUser = new CRoyalRumbleUser;

	pNewUser->m_iUID		= pUser->m_uid;
	strcpy( pNewUser->m_strUserID, pUser->m_strUserID );

	m_arRRUser.Add( pNewUser );

	return TRUE;
}

void CRoyalRumble::Exit(USER* pUser)
{
	if( !pUser ) return;

	int i;

	for( i = 0; i < m_arRRUser.GetSize(); i++ )
	{
		if( m_arRRUser[i] )
		{
			if( m_arRRUser[i]->m_iUID == pUser->m_uid )
			{
				if( !strcmp( m_arRRUser[i]->m_strUserID, pUser->m_strUserID ) )
				{
					m_arRRUser[i]->m_bLive = FALSE;
				}
			}
		}
	}

	GetWinner();
}

void CRoyalRumble::CheckRRBravoEnd()
{
	m_iCurrentBravoSecond++;

	if( m_iCurrentBravoSecond >= m_iBravoSecond )
	{
		m_bRRStatus = RR_IDLE;
		ForceExit();
	}
}

void CRoyalRumble::ForceExit()
{
	USER* pUser = NULL;
	COM* pCom = g_pMainDlg->GetCOM();
	if( !pCom ) return;

	for( int i = 0; i < MAX_USER; i++ )
	{
		pUser = pCom->GetUserUid( i );

		if( !pUser ) continue;

		if( pUser->m_state != STATE_GAMESTARTED ) continue;

		if( pUser->m_curz != m_iZoneNum ) continue;

		if( pUser->CheckInvalidMapType() != 12 ) continue;

		pUser->TownPotal();
	}
}

void CRoyalRumble::BBSWrite(char *strTitle, char *strContent)
{
	char strWriter[128];
	sprintf( strWriter, "노먼" );

	SDWORD sTitleLen	= _tcslen(strTitle);
	SDWORD sContentLen	= _tcslen(strContent);
	SDWORD sIDLen		= _tcslen(strWriter);

	SQLHSTMT	hstmt = NULL;
	SQLRETURN	retcode;
	TCHAR		szSQL[8000];	::ZeroMemory(szSQL, sizeof(szSQL));

	int bbsnum = 3;		// 로열럼블용 게시판

	_sntprintf(szSQL, sizeof(szSQL), TEXT( "{call BBS_WRITE ( %d, ?, ?, ? )}" ), bbsnum );

	int db_index = 0;
	CDatabase* pDB = g_DBNew[AUTOMATA_THREAD].GetDB( db_index );
	if( !pDB ) { return; }

	retcode = SQLAllocHandle( (SQLSMALLINT)SQL_HANDLE_STMT, pDB->m_hdbc, &hstmt );

	if( retcode != SQL_SUCCESS )
	{
		return;
	}

	int i = 1;
	SQLBindParameter( hstmt, i++, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, 20,		0, (TCHAR*)strWriter,	0, &sIDLen );
	SQLBindParameter( hstmt, i++, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, 50,		0, (TCHAR*)strTitle,	0, &sTitleLen );
	SQLBindParameter( hstmt, i++, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, 5000,	0, (TCHAR*)strContent,	0, &sContentLen );

	retcode = SQLExecDirect( hstmt, (unsigned char*)szSQL, sizeof(szSQL));
	if( retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO )
	{
	}
	else if (retcode == SQL_ERROR)
	{
		DisplayErrorMsg(hstmt);
		SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);

		g_DBNew[AUTOMATA_THREAD].ReleaseDB(db_index);
		return;
	}
	
	SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);
	g_DBNew[AUTOMATA_THREAD].ReleaseDB(db_index);

	return;
}

void CRoyalRumble::UpdateRoyalRumbleData()
{
	if( m_bNextRRInit )		// 다음 경기 일정이 설정되었으므로 업데이트 하지 않는다.
	{
		return;
	}

	m_bNextRRInit = TRUE;	// 다음 경기 일정이 설정되었다.

	CTime curtime = CTime::GetCurrentTime();
	CTimeSpan addtime( 28, 0, 0, 0 );

	curtime = curtime + addtime;

	SQLHSTMT		hstmt = NULL;
	SQLRETURN		retcode;
	TCHAR			szSQL[1024];

	int i = 0;

	SQLINTEGER	sInd;
	SQLSMALLINT sYear, sMonth, sDay;
	SQLCHAR		strWinner[CHAR_NAME_LENGTH+1];

	::ZeroMemory(szSQL, sizeof(szSQL));
	::ZeroMemory(strWinner, sizeof(strWinner));

	sYear = curtime.GetYear();
	sMonth = curtime.GetMonth();
	sDay = curtime.GetDay();

	sInd = 0;

	_sntprintf(szSQL, sizeof(szSQL), TEXT("update royal_rumble set nYear = %d, nMonth = %d, nDay = %d, strWinner = \'%s\'"), sYear, sMonth, sDay, g_strARKRRWinner);

	int db_index = 0;
	CDatabase* pDB = g_DB[AUTOMATA_THREAD].GetDB( db_index );
	if( !pDB ) return;

	retcode = SQLAllocHandle( (SQLSMALLINT)SQL_HANDLE_STMT, pDB->m_hdbc, &hstmt );

	if( retcode != SQL_SUCCESS )
	{
		TRACE("Fail To Update Royal Rumble Data !!\n");

		return;
	}

	retcode = SQLExecDirect( hstmt, (unsigned char*)szSQL, SQL_NTS);

	if( retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO )
	{
	}
	else
	{
		DisplayErrorMsg(hstmt);
		retcode = SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);

		g_DB[AUTOMATA_THREAD].ReleaseDB(db_index);
		return;
	}

	retcode = SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);
	g_DB[AUTOMATA_THREAD].ReleaseDB(db_index);

	BridgeServerARKWinnerChangeReq();
	return;
}

void CRoyalRumble::RobItem()
{
	return;

	if( g_strARKRRWinner.GetLength() <= 0 ) return;

	USER* pUser = NULL;
	COM* pCom = g_pMainDlg->GetCOM();
	if( !pCom ) return;

	char tempUserID[CHAR_NAME_LENGTH+1];
	strcpy( tempUserID, g_strARKRRWinner );

	pUser = pCom->GetUser( tempUserID );

	if( !pUser ) return;
	if( pUser->m_state != STATE_GAMESTARTED ) return;

	CBufferEx TempBuf;

	int i, j;

	for( i = 0; i < TOTAL_ITEM_NUM; i++ )
	{
		if( pUser->m_UserItem[i].sSid != m_iItemSid ) continue;

		pUser->ReSetItemSlot( &(pUser->m_UserItem[i]) );
		pUser->CheckMagicItemMove();
		pUser->UpdateUserItemDN();

		pUser->GetRecoverySpeed();			// 다시 회복속도를 계산

		TempBuf.Add(ITEM_GIVE_RESULT);
		TempBuf.Add(SUCCESS);
		TempBuf.Add((BYTE)i);
		TempBuf.Add(pUser->m_UserItem[i].sLevel);
		TempBuf.Add(pUser->m_UserItem[i].sSid);
		TempBuf.Add(pUser->m_UserItem[i].sDuration);
		TempBuf.Add(pUser->m_UserItem[i].sBullNum);
		TempBuf.Add(pUser->m_UserItem[i].sCount);
		for(j = 0; j < MAGIC_NUM; j++) TempBuf.Add(pUser->m_UserItem[i].tMagic[j]);

		TempBuf.Add(pUser->m_UserItem[i].tIQ);

		pUser->Send(TempBuf, TempBuf.GetLength());
	}

	for( i = 0; i < TOTAL_BANK_ITEM_NUM; i++ )
	{
		if( pUser->m_UserBankItem[i].sSid != 840 ) continue;

		pUser->ReSetItemSlot( &(pUser->m_UserBankItem[i]) );
		pUser->UpdateUserBank();

		pUser->GetRecoverySpeed();			// 다시 회복속도를 계산

		TempBuf.Add(ITEM_GIVE_RESULT);
		TempBuf.Add(SUCCESS);
		TempBuf.Add((BYTE)i);
		TempBuf.Add(pUser->m_UserBankItem[i].sLevel);
		TempBuf.Add(pUser->m_UserBankItem[i].sSid);
		TempBuf.Add(pUser->m_UserBankItem[i].sDuration);
		TempBuf.Add(pUser->m_UserBankItem[i].sBullNum);
		TempBuf.Add(pUser->m_UserBankItem[i].sCount);
		for(j = 0; j < MAGIC_NUM; j++) TempBuf.Add(pUser->m_UserBankItem[i].tMagic[j]);

		TempBuf.Add(pUser->m_UserBankItem[i].tIQ);

		pUser->Send(TempBuf, TempBuf.GetLength());
	}

	pUser->SendSystemMsg( "로열럼블 상품 아이템이 회수 되었습니다", SYSTEM_NORMAL, TO_ME);
}

void CRoyalRumble::GiveItemToWinner(USER *pUser)
{
	return;

	int iWeight = 0;
	int iSlot;

	iWeight = g_arItemTable[m_ItemRR.sSid]->m_byWeight;

	CWordArray		arEmptySlot, arSameSlot;

	iSlot = pUser->GetEmptySlot( INVENTORY_SLOT );

	if( iSlot < 0 ) return;

	pUser->ReSetItemSlot( &(pUser->m_UserItem[iSlot]) );

	pUser->m_UserItem[iSlot].sLevel			= m_ItemRR.sLevel;
	pUser->m_UserItem[iSlot].sSid			= m_ItemRR.sSid;
	pUser->m_UserItem[iSlot].sCount			= m_ItemRR.sCount;
	pUser->m_UserItem[iSlot].sDuration		= m_ItemRR.sDuration;
	pUser->m_UserItem[iSlot].sBullNum		= m_ItemRR.sBullNum;
	pUser->m_UserItem[iSlot].tIQ			= m_ItemRR.tIQ;

	pUser->m_UserItem[iSlot].iItemSerial	= m_ItemRR.iItemSerial;
	pUser->m_UserItem[iSlot].dwMoney		= m_ItemRR.dwMoney;

	for( int i = 0; i < MAGIC_NUM; i++ ) pUser->m_UserItem[iSlot].tMagic[i] = m_ItemRR.tMagic[i];

	arEmptySlot.Add(iSlot); 

	pUser->m_iCurWeight += iWeight;
	pUser->GetRecoverySpeed();					// 아이템 무게에 변동이 생기면 회복속도 변환

	pUser->UpdateInvenSlot(&arEmptySlot, &arSameSlot);

	return;
}

void CRoyalRumble::UpdateRoyalRumbleWinner()
{
	SQLHSTMT		hstmt = NULL;
	SQLRETURN		retcode;
	TCHAR			szSQL[1024];

	int i = 0;

	SQLINTEGER	sInd;
	SQLCHAR		strWinner[CHAR_NAME_LENGTH+1];

	::ZeroMemory(szSQL, sizeof(szSQL));
	::ZeroMemory(strWinner, sizeof(strWinner));

	sInd = 0;

	_sntprintf(szSQL, sizeof(szSQL), TEXT("update royal_rumble set strWinner = \'%s\'"), g_strARKRRWinner);

	int db_index = 0;
	CDatabase* pDB = g_DB[AUTOMATA_THREAD].GetDB( db_index );
	if( !pDB ) return;

	retcode = SQLAllocHandle( (SQLSMALLINT)SQL_HANDLE_STMT, pDB->m_hdbc, &hstmt );

	if( retcode != SQL_SUCCESS )
	{
		TRACE("Fail To Update Royal Rumble Data !!\n");

		return;
	}

	retcode = SQLExecDirect( hstmt, (unsigned char*)szSQL, SQL_NTS);

	if( retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO )
	{
	}
	else
	{
		DisplayErrorMsg(hstmt);
		retcode = SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);

		g_DB[AUTOMATA_THREAD].ReleaseDB(db_index);
		return;
	}

	retcode = SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);
	g_DB[AUTOMATA_THREAD].ReleaseDB(db_index);

	BridgeServerARKWinnerChangeReq();

	return;
}

void CRoyalRumble::ForceInit()
{
	RobItem();
	g_strARKRRWinner = _T("");
	UpdateRoyalRumbleWinner();
	m_bNextRRInit = TRUE;

	InitRRUser();

	m_iCurrentStartCount = m_iStartCount;
	m_bRRStatus = RR_IDLE;
	m_iCurrentPlaySecond = 0;
	m_iCurrentBravoSecond = 0;

	CTime curtime = CTime::GetCurrentTime();
	CTimeSpan addtime( 0, 0, 10, 0 );

	m_timeApplyStart	= curtime;
	m_timeApplyEnd		= curtime;

	// 입장 가능 시간
	m_timeEnterStart	= curtime;
	m_timeEnterEnd		= curtime + addtime;

	m_dwLastEnterMsg = 0;
	m_dwLastStartMsg = 0;

	MAP* pMap = NULL;

	for( int i = 0; i < g_zone.GetSize(); i++ )
	{
		if( g_zone[i] )
		{
			if( g_zone[i]->m_Zone == m_iZoneNum )
			{
				pMap = g_zone[i];
				break;
			}
		}
	}

	if( !pMap )	// 이상상태 발생
	{
		AfxMessageBox( "Can't find RR Map" );
		return;
	}

	m_pRRMap = pMap;

	m_ItemRR.sSid = m_iItemSid;

	m_ItemRR.sLevel		= g_arItemTable[m_ItemRR.sSid]->m_byRLevel;
	m_ItemRR.sCount		= 1;
	m_ItemRR.sDuration	= g_arItemTable[m_ItemRR.sSid]->m_sDuration;
	m_ItemRR.sBullNum	= g_arItemTable[m_ItemRR.sSid]->m_sBullNum;

	m_ItemRR.tMagic[0]	= (BYTE)137;
	m_ItemRR.tMagic[1]	= (BYTE)141;
	m_ItemRR.tMagic[2]	= (BYTE)128;
	m_ItemRR.tMagic[3]	= (BYTE)42;
	m_ItemRR.tMagic[4]	= (BYTE)31;
	m_ItemRR.tMagic[5]	= (BYTE)33;
	m_ItemRR.tIQ		= UNIQUE_ITEM;

	m_ItemRR.iItemSerial= 0;
	m_ItemRR.dwMoney	= 0;
}

void CRoyalRumble::InitRRUser()
{
	int i;

	for( i = 0; i < m_arRRUser.GetSize(); i++ )
	{
		if( m_arRRUser[i] )
		{
			delete m_arRRUser[i];
		}
	}
	m_arRRUser.RemoveAll();
}

void CRoyalRumble::Apply()	// 원래 신청을 받는 함순데... 사전 공지와 상태 초기화에 쓰이는 것으로 용도 변경
{
	RobItem();
	g_strARKRRWinner = _T("");

	UpdateRoyalRumbleData();

	CString strMsg;
	CTime time = CTime::GetCurrentTime();

	if( ( time.GetMinute() % 10 ) == 5 ||  ( time.GetMinute() % 10 ) == 0 )		// 5분 마다 한번씩
	{
		strMsg.Format( "오늘 8시 NEO A.R.K 격투장에서 로열럼블경기가 열립니다. 많은 참여 부탁드립니다" );
		g_pMainDlg->AnnounceAllServer( (LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE );
	}
}

void CRoyalRumble::BridgeServerARKWinnerChangeReq()
{
	int index = 0;
	TCHAR TempBuf[SEND_BUF_SIZE];

	char strWinner[CHAR_NAME_LENGTH+1];		memset( strWinner, NULL, CHAR_NAME_LENGTH+1 );
	strcpy( strWinner, g_strARKRRWinner );

	SetByte( TempBuf, SERVER_ARK_WINNER, index );
	SetByte( TempBuf, strlen( strWinner ), index );
	SetString( TempBuf, strWinner, strlen( strWinner ), index );

	g_pMainDlg->m_pBridgeSocket->Send( TempBuf, index );
}
