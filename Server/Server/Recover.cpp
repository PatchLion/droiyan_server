// Recover.cpp: implementation of the CRecover class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "Recover.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRecover::CRecover()
{
	m_sSid = 0;
	m_byHPDivide = 0;
	m_bySPDivide = 0;
	m_byPPDivide = 0;
	m_byTown = 0;
}

CRecover::~CRecover()
{

}
