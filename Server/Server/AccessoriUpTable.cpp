// AccessoriUpTable.cpp: implementation of the CAccessoriUpTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "AccessoriUpTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CRipel::CRipel()
{
	
}

CRipel::~CRipel()
{
	m_arRipelTop.RemoveAll();
	m_arRipelBottom.RemoveAll();
	m_arRipelLeft.RemoveAll();
	m_arRipelRight.RemoveAll();
	m_arRipelCrest.RemoveAll();
}

CAccessoriUpTable::CAccessoriUpTable()
{

}

CAccessoriUpTable::~CAccessoriUpTable()
{

}
