// LOGIC.cpp: implementation of the LOGIC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LOGIC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LOGIC::LOGIC()
{

}

LOGIC::~LOGIC()
{

}

void LOGIC::Parse(char *pBuf)
{
	int index = 0, i = 0;
	char temp[1024];

	index += ParseSpace( temp, pBuf+index );

	if( !strcmp( temp, "POSITION" ) )
	{
		m_Logic = LOGIC_POSITION;

		index += ParseSpace( temp, pBuf+index );	m_LogicInt[i] = atoi( temp );	i++;
		index += ParseSpace( temp, pBuf+index );	m_LogicInt[i] = atoi( temp );	i++;
		index += ParseSpace( temp, pBuf+index );	m_LogicInt[i] = atoi( temp );	i++;
	}
//	else if( !strcmp( temp, "" )
//	{
//	}
}

void LOGIC::Init()
{
	for( int i = 0; i < MAX_LOGIC_INT; i++)
	{
		m_LogicInt[i] = -1;
	}

	m_LogicChar[0] = 0;
}
