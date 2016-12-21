// SummonTable.cpp: implementation of the CSummonTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "SummonTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSummonTable::CSummonTable()
{
	m_sSid = 0;
	m_strName = _T("");
}

CSummonTable::~CSummonTable()
{

}
