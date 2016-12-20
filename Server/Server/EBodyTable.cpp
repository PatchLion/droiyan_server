// EBodyTable.cpp: implementation of the CEBodyTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "EBodyTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEBodyTable::CEBodyTable()
{
	m_sChangeValue = 0;
	m_sRandom = 0;
	m_sSubType = 0;
	m_tLevel = 0;
	m_tNeedClass = 0;
	m_tSid = 0;
	m_tUpgrade = 0;
	m_tWearInfo = 0;
}

CEBodyTable::~CEBodyTable()
{

}
