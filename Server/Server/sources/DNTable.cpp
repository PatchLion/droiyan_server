// DNTable.cpp: implementation of the CDNTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "DNTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDNTable::CDNTable()
{
	m_sIndex = 0;
	m_sMinDn = 0;
	m_sMaxDn = 0;
}

CDNTable::~CDNTable()
{

}
