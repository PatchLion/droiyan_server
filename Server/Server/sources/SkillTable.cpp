// SkillTable.cpp: implementation of the CSkillTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "SkillTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSkillTable::CSkillTable()
{

}

CSkillTable::~CSkillTable()
{
	m_arInc.RemoveAll();
	m_arRepair.RemoveAll();
	m_arSuccess.RemoveAll();
}
