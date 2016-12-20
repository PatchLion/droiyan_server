// RoyalRumbleUser.cpp: implementation of the CRoyalRumbleUser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "RoyalRumbleUser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRoyalRumbleUser::CRoyalRumbleUser()
{
	m_iUID = -1;
	memset( m_strUserID, NULL, CHAR_NAME_LENGTH+1 );
	m_bLive = TRUE;
}

CRoyalRumbleUser::~CRoyalRumbleUser()
{

}
