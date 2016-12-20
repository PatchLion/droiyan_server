// MemUser.cpp: implementation of the CMemUser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemUser.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMemGuildHouseRank::CMemGuildHouseRank()
{
	tSid = 0;
	lGuild = 0;
	iLastValue = 0;
}

CMemGuildHouseRank::~CMemGuildHouseRank()
{
}

CMemStore::CMemStore()
{
	m_sStoreID = -1;
	m_iGuildSid = 0;

	m_sTaxRate = 0;
	m_dwStoreDN = 0;
	m_tWarType = 0;
}

CMemStore::~CMemStore()
{

}


CMemBank::CMemBank()
{
	m_uid = -1;
	m_dwBankDN = 0;
}

CMemBank::~CMemBank()
{

}

CMemAccountBank::CMemAccountBank()
{
	m_uid = -1;
	m_dwBankDN = 0;
}

CMemAccountBank::~CMemAccountBank()
{

}

CMemUser::CMemUser()
{
	m_uid = -1;
	ZeroMemory(m_strLoveName,sizeof(m_strLoveName));
}

CMemUser::~CMemUser()
{

}
