// LevelUpTable.cpp: implementation of the CLevelUpTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "LevelUpTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLevelUpTable::CLevelUpTable()
{
	m_sLevel	= 1;
	m_dwExp		= 0;
}

CLevelUpTable::~CLevelUpTable()
{

}
