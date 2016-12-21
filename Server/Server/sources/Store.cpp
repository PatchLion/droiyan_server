// Store.cpp: implementation of the CStore class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "Store.h"
#include "Extern.h"
#include "Mcommon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStore::CStore()
{
	m_iStandingTime = 50;		// 길드전 10분 전부터 계산하기 시작한다.	

	m_sRate = 0;
	m_lUsed = 0;
	m_lAreaUsed = 0;
	m_lListUsed = 0;
	m_lListCount = 0;
	m_dwStartTick = 0;

	m_bHaveGuild = FALSE;		// 현재 길드에 속한 상점이다	TRUE	
	m_iGuildSid = 0;		// 해당 길드 인덱스
	::ZeroMemory(m_strGuildName, sizeof(m_strGuildName)); // 해당 길드 이름
	::ZeroMemory(m_strMasterName, sizeof(m_strMasterName));// 해당 길드 짱 이름
	m_iGuildDN = 0;							  // 누적된 금액	

	m_tWarType = GUILD_WAR_PREPARE;

	for(int j = 0; j < GUILD_ATTACK_MAX_NUM; j++)
	{
		m_arAttackGuild[j] = 0;
	}
//	m_arNpcList.RemoveAll();
}

CStore::~CStore()
{
	m_arItems.RemoveAll();
	m_arSellList.RemoveAll();
	m_arRepairList.RemoveAll();
	m_arNpcList.RemoveAll();
}

///////////////////////////////////////////////////////////////////////
//	해당 Sid의 아이템이 해당상점에 팔 수 있는것인지 확인한다. 
//
BOOL CStore::IsCanSell(short sSid)
{
	if(sSid < 0) return FALSE;

	for(int i = 0; i < m_arSellList.GetSize(); i++)
	{
		if(m_arSellList[i] == sSid) return TRUE;
	}

	return FALSE;
}

int CStore::IsCanBuyPsi(CStore *pStore, int iClass)
{
	short sSid = -1;

	if(iClass < 0) return -1;

	switch(iClass)
	{
	case BRAWL:
		sSid = 0;
		break;
	case STAFF:
		sSid = BRAWL_PSI_NUM;
		break;
	case EDGED:
		sSid = BRAWL_PSI_NUM + STAFF_PSI_NUM;
		break;
	case FIREARMS:
		sSid = BRAWL_PSI_NUM + STAFF_PSI_NUM + EDGED_PSI_NUM;
		break;
	case NOCLASS:		// 무계열 사이오닉 (현재는 100랩이상 사이오닉밖에 없다)
		sSid = BRAWL_PSI_NUM + STAFF_PSI_NUM + EDGED_PSI_NUM + FIREARMS_PSI_NUM;
		break;
	}

	for(int i = 0; i < pStore->m_arItems.GetSize(); i++)
	{
		if(pStore->m_arItems[i] == sSid) return i;
	}

	return -1;
}

BOOL CStore::IsCanRepair(short sSid)
{
	if(sSid < 0) return FALSE;

	for(int i = 0; i < m_arRepairList.GetSize(); i++)
	{
		if(m_arRepairList[i] == sSid) return TRUE;
	}

	return FALSE;
}

void CStore::InitStoreInfo(int sid)
{
//	CTime	curTime;
//	curTime = CTime::GetCurrentTime();

	SYSTEMTIME st;
	GetLocalTime(&st);

	m_bHaveGuild = TRUE;		// 새로운 길드가 점령했다.
	m_iGuildDN = 0;
	m_lAreaUsed = 0;

	m_sRate = 0;
	m_bHaveGuild = TRUE;

	m_iGuildSid = sid;

	m_iGuildDN = 0;

	m_tWarType = GUILD_WAR_PREPARE;
	m_lListCount = 0;			// 최대 길드전을 신청한 길드수

	for(int i = 0; i < GUILD_ATTACK_MAX_NUM; i++)
	{
		m_arAttackGuild[i] = 0;
	}

	m_iStandingTime = 50;

	m_wLastWarTime.wYear = st.wYear;
	m_wLastWarTime.wMonth = st.wMonth;
	m_wLastWarTime.wDay = st.wDay;
	m_wLastWarTime.wHour = st.wHour;
	m_wLastWarTime.wMinute = 0;

//	CTime planTime = curTime + CTimeSpan( 3, 0, 0, 0 );    // 3 Day later
	COleDateTime planTime(st.wYear, st.wMonth, st.wDay, st.wHour, 0, 0);
	planTime += 3;

	m_wPlanWarTime.wYear = planTime.GetYear();
	m_wPlanWarTime.wMonth = planTime.GetMonth();
	m_wPlanWarTime.wDay = planTime.GetDay();
	m_wPlanWarTime.wHour = planTime.GetHour();
	m_wPlanWarTime.wMinute = 0;
}

///////////////////////////////////////////////////////////////////////////////
//	UserSkill 에 Buffer 의 내용을 카피한다.
//
void CStore::StrToGuildList(TCHAR *pBuf)
{
	int index = 0;
	for(int i = 0; i < GUILD_ATTACK_MAX_NUM; i++)
	{
		m_arAttackGuild[i]	= GetInt(pBuf, index);
		if(m_arAttackGuild[i] > 0) 
		{
			InterlockedIncrement(&m_lListCount);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//	Buffer 에 UserSkill 정보를 Copy 한다.
//
void CStore::GuildListToStr(TCHAR *pBuf)
{
	int	index = 0;
	for(int i = 0; i < GUILD_ATTACK_MAX_NUM; i++)
	{
		SetInt(pBuf, m_arAttackGuild[i],index);
	}
}

BOOL CStore::UpdateGuildStore()
{
	SQLHSTMT		hstmt = NULL;
	SQLRETURN		retcode = 0;
	BOOL			bQuerySuccess = TRUE;
	TCHAR			szSQL[8000];		

	if(m_iGuildSid <= 0) return FALSE;

	::ZeroMemory(szSQL, sizeof(szSQL));

	_sntprintf(szSQL, sizeof(szSQL), TEXT("{call INSERT_GUILD_STORE(%d,%d,\'%s\',\'%s\')}"), m_sStoreID, m_iGuildSid, m_strGuildName, m_strMasterName);

	int db_index = 0;
	CDatabase* pDB = g_DBNew[AUTOMATA_THREAD].GetDB( db_index );
	if( !pDB ) return FALSE;

	retcode = SQLAllocHandle( (SQLSMALLINT)SQL_HANDLE_STMT, pDB->m_hdbc, &hstmt );
	if( retcode != SQL_SUCCESS )
	{
		TRACE("Fail To Update Guild_Store Data Only!!\n");

		//g_DBNew[AUTOMATA_THREAD].ReleaseDB(db_index);
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

			g_DBNew[AUTOMATA_THREAD].ReleaseDB(db_index);
			return FALSE;
		}
	}	
	else
	{
//		DisplayErrorMsg( hstmt );
//		SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);
//		BREAKPOINT();

//		g_DBNew[AUTOMATA_THREAD].ReleaseDB(db_index);
		return FALSE;
	}

	if (hstmt!=NULL) SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);
	g_DBNew[AUTOMATA_THREAD].ReleaseDB(db_index);
	
	if( !bQuerySuccess ) return FALSE;

	return TRUE;
}

void CStore::SetGuildStoreTex()
{
/*	m_sRate = 0;

	//UpdateMemStoreTax(iSid, iRate);
	int nSize = g_arStoreSharedMemory.GetSize();
	CSharedMemory* pShared = NULL;
	CMemStore* pData = NULL;

	pShared = g_arStoreSharedMemory[m_sStoreID];
	
	if(pShared == NULL) return;
	if(pShared->m_hMapping == NULL) return;
	
	pData = (CMemStore*) pShared->m_lpData;
	
	if(pData == NULL) return;
	if(pData->m_sStoreID == -1) return;
	if(pData->m_iGuildSid <= 0) return;
	
	pData->m_sStoreID = m_sStoreID;
	pData->m_iGuildSid = m_iGuildSid;
	pData->m_sTaxRate = 0;
	pData->m_dwStoreDN = 0;
	pData->m_tWarType = GUILD_WAR_PREPARE;

	GuildListToStr(pData->m_AttackList);
*/
}

BOOL CStore::IsCanBuy(short sSid)
{
	if(sSid < 0) return FALSE;

	if (sSid == 908)
	{
		return FALSE;
	}
	for(int i = 0; i < m_arItems.GetSize(); i++)
	{
		if(m_arItems[i] == sSid) return TRUE;
	}

	return FALSE;

}