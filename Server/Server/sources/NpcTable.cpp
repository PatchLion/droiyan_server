// NpcTable.cpp: implementation of the CNpcTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "NpcTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNpcTable::CNpcTable()
{
	m_sSid				= 0;				// MONSTER(NPC) Serial ID
	m_sPid				= 0;				// MONSTER(NPC) Picture ID
	::ZeroMemory(m_strName, sizeof(m_strName));		// MONSTER(NPC) Name

	m_sSTR				= 0;				// 힘
	m_sDEX				= 0;				// 민첩
	m_sVOL				= 0;				// 의지
	m_sWIS				= 0;				// 지혜
	m_sMaxHP			= 0;				// 최대 HP
	m_sMaxPP			= 0;				// 최대 PP

	m_byClass			= 0;				// 무기계열
	m_byClassLevel		= 0;				// 무기계열 레벨
	m_sExp				= 0;				// 경험치
	m_byAX				= 0;				// 공격값 X
	m_byAY				= 0;				// 공격값 Y
	m_byAZ				= 0;				// 공격값 Z
	
	m_iDefense			= 0;				// 방어값
	m_byRange			= 0;
	m_sAI				= 0;				// 인공지능 인덱스
	m_sAttackDelay		= 0;				// 공격딜레이
	m_byVitalC			= 0;				// 신체데미지 크리티컬
	m_byWildShot		= 0;				// 난사 레벨
	m_byExcitedRate		= 0;				// 흥분 레벨
	m_byIronSkin		= 0;
	m_byReAttack		= 0;
	m_bySubAttack		= 0;				// 상태이상 발생(부가공격)
	m_byState			= 0;				// 몬스터 (NPC) 상태이상
	m_byPsi				= 0;				// 사이오닉 적용
	m_byPsiLevel		= 0;				// 사이오닉레벨
	m_bySearchRange		= 0;				// 적 탐지 범위
	m_sSpeed			= 0;				// 이동속도	
	m_sInclination		= 0;
	m_byColor			= 0;
	
	m_sStandTime		= 0;
	m_tNpcType			= 0;				// NPC Type

	m_sFamilyType		= 0;		// 몹들사이에서 가족관계를 결정한다.
	m_tItemPer			= 0;			// 아이템이 떨어질 확률
	m_tDnPer			= 0;			// 돈이 떨어질확률
}

CNpcTable::~CNpcTable()
{

}
