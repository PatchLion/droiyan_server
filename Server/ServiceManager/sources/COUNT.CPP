// Count.cpp: implementation of the CCount class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServiceManager.h"
#include "Count.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCount::CCount(int nNum)
{
	m_nNum = nNum;
	m_nUserNum = 0;
	m_time = CTime::GetCurrentTime ();
}
