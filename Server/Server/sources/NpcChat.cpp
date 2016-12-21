// NpcChat.cpp: implementation of the CNpcChat class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "NpcChat.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNpcChat::CNpcChat()
{
	m_sCid = 0;
	m_sSize = 0;
//	::ZeroMemory(m_strTalk, MAX_LENGTH);
//	m_strTalk = _T("");
	m_strTalk = NULL;
}

CNpcChat::~CNpcChat()
{
	if(m_strTalk != NULL)
	{
		delete [] m_strTalk;
		m_strTalk = NULL;
	}
}
