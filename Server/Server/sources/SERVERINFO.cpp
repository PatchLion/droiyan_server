/////////////////////////////////////////////////////////////////////
//	SERVERINFO.cpp : implementation file of the the SERVERINFO class
//  Copyright (C) 2000,  Jin-Soo Jeon
//
//	If this code works, it was written by Jin-Soo Jeon.
//	If not, I don't know who wrote it.
//

#include "stdafx.h"
#include "Server.h"
#include "SERVERINFO.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] =__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SERVERINFO::SERVERINFO()
{
	m_szAddr = _T("");
	m_nPort = 0;
	m_strGTime = _T("");
}

SERVERINFO::~SERVERINFO()
{
	for( int i = 0; i < m_zone.GetSize(); i++)
	{
		if(m_zone[i]) delete m_zone[i];
	}

	m_zone.RemoveAll();
}
