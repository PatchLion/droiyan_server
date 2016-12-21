// MonsterDamageRate.h: interface for the CMonsterDamageRate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONSTERDAMAGERATE_H__9AEA53CF_5371_4209_AA20_CC54085BAD17__INCLUDED_)
#define AFX_MONSTERDAMAGERATE_H__9AEA53CF_5371_4209_AA20_CC54085BAD17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMonsterDamageRate  
{
public:
	CMonsterDamageRate();
	virtual ~CMonsterDamageRate();

	short** pRate;
	int x, y;
};

#endif // !defined(AFX_MONSTERDAMAGERATE_H__9AEA53CF_5371_4209_AA20_CC54085BAD17__INCLUDED_)
