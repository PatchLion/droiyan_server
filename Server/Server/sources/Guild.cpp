// Guild.cpp: implementation of the CGuild class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "Guild.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGuild::CGuild()
{
	InitGuild();
}

CGuild::~CGuild()
{

}

///////////////////////////////////////////////////////////////////////////////
//	UserBankItem 에 Buffer의 내용을 Copy 한다.
//
void CGuild::StrToGuildItem(TCHAR *pBuf)
{
	int index = 0;
	int i, j;
	MYINT64 serial;

	for(i = 0; i < TOTAL_BANK_ITEM_NUM; i++)
	{
		m_UserGuildItem[i].sLevel	= GetShort(pBuf, index);
		m_UserGuildItem[i].sSid		= GetShort(pBuf, index);
		m_UserGuildItem[i].sDuration = GetShort(pBuf, index);
		m_UserGuildItem[i].sBullNum	= GetShort(pBuf, index);
		m_UserGuildItem[i].sCount	= GetShort(pBuf, index);

		if(m_UserGuildItem[i].sCount <= 0) m_UserGuildItem[i].sSid = -1;
		for(j = 0; j < MAGIC_NUM; j++) m_UserGuildItem[i].tMagic[j] = GetByte(pBuf, index);
		
		m_UserGuildItem[i].tIQ = GetByte(pBuf, index);

		for( j = 0; j < 8; j++ ) serial.b[j] = GetByte( pBuf, index );

		m_UserGuildItem[i].iItemSerial = serial.i;
	}	
}

///////////////////////////////////////////////////////////////////////////////
//	Buffer 에 UserBankItem 정보를 Copy 한다.
//
void CGuild::GuildItemToStr(TCHAR *pBuf)
{
	int index = 0;
	int i, j;
	MYINT64 serial;

	for(i = 0; i < TOTAL_BANK_ITEM_NUM; i++)
	{
		SetShort(pBuf, m_UserGuildItem[i].sLevel,	index);
		SetShort(pBuf, m_UserGuildItem[i].sSid,		index);
		SetShort(pBuf, m_UserGuildItem[i].sDuration,	index);
		SetShort(pBuf, m_UserGuildItem[i].sBullNum,	index);
		SetShort(pBuf, m_UserGuildItem[i].sCount,	index);

		for(j = 0; j < MAGIC_NUM; j++) SetByte(pBuf, m_UserGuildItem[i].tMagic[j], index);

		SetByte(pBuf, m_UserGuildItem[i].tIQ, index);

		serial.i = m_UserGuildItem[i].iItemSerial;

		for(j = 0; j < 8; j++ ) SetByte( pBuf, serial.b[j], index );
	}
}

///////////////////////////////////////////////////////////////////////////////
//	Guild Map 에 Buffer의 내용을 Copy 한다.
//
void CGuild::strToGuildMap(TCHAR *pBuf)
{
	int index = 0;
	int i;
	for(i = 0; i < GUILD_MAP_COUNT; i++)
	{
		m_dwHaveMap[i]	= GetDWORD(pBuf, index);
	}	
}

///////////////////////////////////////////////////////////////////////////////
//	Buffer 에 Guild Map 정보를 Copy 한다.
//
void CGuild::GuildMapToStr(TCHAR *pBuf)
{
	int index = 0;
	int i;
	for(i = 0; i < GUILD_MAP_COUNT; i++)
	{
		SetDWORD(pBuf, m_dwHaveMap[i],	index);
	}	
}

///////////////////////////////////////////////////////////////////////////////
//	해당유저 아이디를 반환한다.
//
int CGuild::GetUser(TCHAR *userID)
{
/*	CString ID;

	ID.Format("%s", userID);

	for( int i = 0; i < m_arUser.GetSize(); i++)
	{
		if( m_arUser[i] )
		{
			if( !ID.CompareNoCase( m_arUser[i]->m_strUserId ) )
			{
				return m_arUser[i];
			}
		}
	}
*/
	int nLen = 0;
	nLen = strlen(userID);

	if(nLen <= 0 || nLen > CHAR_NAME_LENGTH) return -1;

	for(int i = 0; i < MAX_GUILD_USER; i++)
	{
		if( m_arUser[i].m_lUsed > 0 )
		{
			if(strcmp(userID, m_arUser[i].m_strUserId) == 0)
			{
				return i;
			}
		}
	}

	return -1;	
}

///////////////////////////////////////////////////////////////////////////////
//	해당유저 아이디를 리스트에서 삭제..
//
BOOL CGuild::RemoveUser(TCHAR *userID)
{
/*	CString ID;

	ID.Format( "%s", userID );

	for(int i = 0; i < m_arUser.GetSize(); i++)
	{
		if( m_arUser[i] )
		{
			if( !ID.CompareNoCase( m_arUser[i]->m_strUserId ) )
			{
				delete m_arUser[i];
				m_arUser.RemoveAt(i);
				break;
			}
		}
	}
*/
	int nLen = 0;
	nLen = strlen(userID);

	if(nLen <= 0 || nLen > CHAR_NAME_LENGTH) return FALSE;

	for(int i = 0; i < MAX_GUILD_USER; i++)
	{
		if( m_arUser[i].m_lUsed > 0 )
		{
			if(strcmp(userID, m_arUser[i].m_strUserId) == 0)
			{
				if(InterlockedCompareExchange((LONG*)&m_arUser[i].m_lUsed, (long)0, (long)1) == (long)1)
				{
					::ZeroMemory(m_arUser[i].m_strUserId, sizeof(m_arUser[i].m_strUserId));
					InterlockedExchange(&m_arUser[i].m_lSid, 0);
					return TRUE;
				}				
			}
		}
	}

	return FALSE;
}


///////////////////////////////////////////////////////////////////////////////
//	버젼 정보만 빼고 모두 초기화 (Client에서 Update하기위해 버젼은 계속 남아야한다.)
//
void CGuild::InitGuild()
{
	int i = 0;
	m_lUsed = 0;
	m_lSid = 0;	
	m_dwGuildDN = 0;
	m_sVersion = -1;
	m_lSubMaster = 0;
//	m_dwExp = 0;

//	m_arUser.RemoveAll();
	m_iUsedUser = -1;
	::ZeroMemory(m_strUsedUser, sizeof(m_strUsedUser));
	::ZeroMemory(m_strGuildName, sizeof(m_strGuildName));
	::ZeroMemory(m_strMasterName, sizeof(m_strMasterName));
	::ZeroMemory(m_strSubMasterName, sizeof(m_strSubMasterName));
//	::ZeroMemory(m_strMark, sizeof(m_strMark));
	::ZeroMemory(m_dwHaveMap, sizeof(m_dwHaveMap));
	::ZeroMemory(m_UserGuildItem, sizeof(m_UserGuildItem));

	WORD *pwMark = (WORD*)(&m_strMark[0]);
	for (i=0; i<GUILD_MARK_SIZE/sizeof(WORD); i++) {
		pwMark[i] = (0x1f<<11 | 0x1f);	// Client에서 사용하는 투명색으로 초기화한다.
	}

	for(i = 0; i < MAX_GUILD_USER; i++)
	{
		m_arUser[i].m_lSid = 0;
		m_arUser[i].m_lUsed = 0;
		::ZeroMemory(m_arUser[i].m_strUserId, sizeof(m_arUser[i].m_strUserId));
	}
}

BOOL CGuild::AddUser(TCHAR *userID, int iGuildID)
{
	int nLen = 0;
	nLen = strlen(userID);

	if(nLen <= 0 || nLen > CHAR_NAME_LENGTH) return FALSE;

	for(int i = 0; i < MAX_GUILD_USER; i++)
	{
		if(InterlockedCompareExchange((long*)&m_arUser[i].m_lUsed, (long)1, (long)0) == (long)0)
		{
			m_arUser[i].m_lSid = iGuildID;
			strncpy(m_arUser[i].m_strUserId, userID, nLen);
			return TRUE;
		}
	}

	return FALSE;
}

void CGuild::SetSubGuildMaster(TCHAR *strName)
{
	int nLen = 0;
	nLen = strlen(strName);

	if(nLen <= 0 || nLen > CHAR_NAME_LENGTH) return;

	::ZeroMemory(m_strSubMasterName, sizeof(m_strSubMasterName));
	CopyMemory(m_strSubMasterName, strName, sizeof(m_strSubMasterName));
}

void CGuild::RemoveSubGuildMaster()
{
	InterlockedExchange(&m_lSubMaster, (LONG)0);
	::ZeroMemory(m_strSubMasterName, CHAR_NAME_LENGTH + 1);
}

BOOL CGuild::IsMasterPower(TCHAR *strUserID)
{
	int nLen = 0;
	nLen = strlen(strUserID);

	if(nLen <= 0 || nLen > CHAR_NAME_LENGTH) return FALSE;

	nLen = 0;
	nLen = strlen(m_strMasterName);
	if(nLen <= 0 || nLen > CHAR_NAME_LENGTH) return FALSE;

	if( strcmp(m_strMasterName, strUserID) == 0 ) return TRUE;

	nLen = 0;
	nLen = strlen(m_strSubMasterName);
	if(nLen <= 0 || nLen > CHAR_NAME_LENGTH) return FALSE;

	if( strcmp(m_strSubMasterName, strUserID) == 0 ) return TRUE;

	return FALSE;
}

BOOL CGuild::CheckGuildSubMaster()
{
	if(InterlockedCompareExchange((long*)&m_lSubMaster, (long)1, (long)0) == (long)0) return TRUE;
	
	return FALSE;
}

