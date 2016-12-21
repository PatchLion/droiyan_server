// MagicItemTable.cpp: implementation of the CMagicItemTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "MagicItemTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMagicItemTable::CMagicItemTable()
{

}

CMagicItemTable::~CMagicItemTable()
{

}

int CMagicItemTable::GetMagicItemValue()
{
	return m_sChangeValue;
}
