// UserLevelUpTable.cpp: implementation of the CUserLevelUpTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "UserLevelUpTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserLevelUpTable::CUserLevelUpTable()
{
	m_sLevel = 0;
	m_sHP = 0;
	m_sPP = 0;
	m_sDamage = 0;
	m_sDefense = 0;
	m_sWeight = 0;
}

CUserLevelUpTable::~CUserLevelUpTable()
{

}
