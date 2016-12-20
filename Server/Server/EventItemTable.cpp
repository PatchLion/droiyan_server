// EventItemTable.cpp: implementation of the CEventItemTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "EventItemTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEventItemTable::CEventItemTable()
{
	m_tEnd = 0;
	m_sSid = 0;
	m_tType = 0;
	m_tGiveFlag = 0;
	m_tGiveItem = 0;

	::ZeroMemory(m_strSerialNum, sizeof(m_strSerialNum));

	m_dwTick = 0;
	m_lUsed = 0;
}

CEventItemTable::~CEventItemTable()
{

}
