// NpcSayTable.cpp: implementation of the CNpcSayTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "NpcSayTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNpcSayTable::CNpcSayTable()
{
	iSid = 0;
	Say = _T("");
}

CNpcSayTable::~CNpcSayTable()
{

}
