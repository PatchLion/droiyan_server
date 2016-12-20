// User.cpp: implementation of the CUser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UserManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUser::CUser(int nID, LPCTSTR lpszIPAddr)
{
	m_nID = nID;
	m_strIPAddr = lpszIPAddr;

	m_bLoginResult = LR_USER_INVALID;
	m_bCheckResult = LR_SN_NOSN;
	m_wSerial = 0;
}

CUser::~CUser()
{

}

void CUser::Login(LPCTSTR lpszUserID, LPCTSTR lpszPasswd, CTime timeLogin)
{
	m_strUserID = lpszUserID;
	m_strPasswd = lpszPasswd;
	m_timeLog = timeLogin;
}
