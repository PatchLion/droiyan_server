// GuildUser.cpp: implementation of the CGuildUser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "GuildUser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGuildUser::CGuildUser()
{
	::ZeroMemory(m_strUserId, sizeof(m_strUserId));
	m_lSid = -1;
	m_lUsed = 0;
}

CGuildUser::~CGuildUser()
{

}
