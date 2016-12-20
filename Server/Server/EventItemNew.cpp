// EventItemNew.cpp: implementation of the CEventItemNew class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "EventItemNew.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEventItemNew::CEventItemNew()
{
	m_sIndex		= -1;
	m_sSid			= -1;

	m_tQuality		= 0;

	m_sRemain		= 0;

	m_tSerialExist	= 0;

	m_iThrowTerm	= 0;
	m_iThrowRandom	= 0;

	m_sNextYear		= 0;
	m_sNextMonth	= 0;
	m_sNextDay		= 0;
	m_sNextHour		= 0;
	m_sNextMin		= 0;

	m_lGive		= 0;
}

CEventItemNew::~CEventItemNew()
{

}
