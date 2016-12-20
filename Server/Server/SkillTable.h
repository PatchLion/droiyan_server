// SkillTable.h: interface for the CSkillTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKILLTABLE_H__C0DA93A2_84E6_4200_92B9_09D1E13ECEBA__INCLUDED_)
#define AFX_SKILLTABLE_H__C0DA93A2_84E6_4200_92B9_09D1E13ECEBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSkillTable  
{
public:
	short	m_sPid;
	short	m_sSid;
	BYTE	m_tClass;

	CByteArray m_arInc;
	CByteArray m_arRepair;
	CByteArray m_arSuccess;

	CSkillTable();
	~CSkillTable();
};

#endif // !defined(AFX_SKILLTABLE_H__C0DA93A2_84E6_4200_92B9_09D1E13ECEBA__INCLUDED_)
