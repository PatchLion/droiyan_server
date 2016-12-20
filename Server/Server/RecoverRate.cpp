// RecoverRate.cpp: implementation of the CRecoverRate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "RecoverRate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRecoverRate::CRecoverRate()
{
	m_sSid = 0;
	m_sHpSpeedupTime = 0;
	m_byHpSpeedupLevel = 0;
	m_sSpSpeedupTime = 0;
	m_bySpSpeedupLevel = 0;
	m_sPpSpeedupTime = 0;
	m_byPpSpeedupLevel = 0;
}

CRecoverRate::~CRecoverRate()
{

}
