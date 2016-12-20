// ValItemTable.cpp: implementation of the CValItemTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "ValItemTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CValItemTable::CValItemTable()
{
	m_sSid = 0;
	m_sValItem01 = 0;
	m_tPersentVal01 = 0;
	m_sValItem02 = 0;
	m_tPersentVal02 = 0;
	m_sValItem03 = 0;
	m_tPersentVal03 = 0;
	m_sValItem04 = 0;
	m_tPersentVal04 = 0;
	m_sValItem05 = 0;
	m_tPersentVal05 = 0;
	m_sValItem06 = 0;
	m_tPersentVal06 = 0;
}

CValItemTable::~CValItemTable()
{

}
