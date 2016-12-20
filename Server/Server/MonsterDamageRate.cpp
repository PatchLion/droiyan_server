// MonsterDamageRate.cpp: implementation of the CMonsterDamageRate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MonsterDamageRate.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMonsterDamageRate::CMonsterDamageRate()
{
	pRate = NULL;
	x = y = 0;
}

CMonsterDamageRate::~CMonsterDamageRate()
{
	int i = 0;
	if(pRate)
	{
		for(i = 0; i < x; i++)
		{
			delete[] pRate[i];
		}
		delete pRate;
	}

	pRate = NULL;
}
