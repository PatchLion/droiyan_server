// CP_IP_MASKTable.cpp: implementation of the CCP_IP_MASKTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Session.h"
#include "CP_IP_MASKTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCP_IP_MASKTable::CCP_IP_MASKTable()
{
	::ZeroMemory(m_StartIP, sizeof(m_StartIP));
	::ZeroMemory(m_EndIP, sizeof(m_EndIP));
}

CCP_IP_MASKTable::~CCP_IP_MASKTable()
{

}
