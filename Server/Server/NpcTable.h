// NpcTable.h: interface for the CNpcTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPCTABLE_H__C9E9FA22_E50D_4EAD_980F_2A89E9EDC094__INCLUDED_)
#define AFX_NPCTABLE_H__C9E9FA22_E50D_4EAD_980F_2A89E9EDC094__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNpcTable  
{
public:
	int		m_sSid;				// MONSTER(NPC) Serial ID
	int		m_sPid;				// MONSTER(NPC) Picture ID
	TCHAR	m_strName[20];		// MONSTER(NPC) Name

	int		m_sSTR;				// 힘
	int		m_sDEX;				// 민첩
	int		m_sVOL;				// 의지
	int		m_sWIS;				// 지혜

	int		m_sMaxHP;			// 최대 HP
	int		m_sMaxPP;			// 최대 PP
	
	BYTE	m_byClass;			// 무기계열
	BYTE	m_byClassLevel;		// 무기계열 레벨

	int		m_sExp;				// 경험치

	int	m_byAX;				// 공격값 X
	int	m_byAY;				// 공격값 Y
	int	m_byAZ;				// 공격값 Z

	int		m_iDefense;		// 방어값
	BYTE	m_byRange;			// 사정거리

	int		m_sAI;				// 인공지능 인덱스
	int		m_sAttackDelay;		// 공격딜레이
	BYTE	m_byVitalC;			// 신체데미지 크리티컬
	BYTE	m_byWildShot;		// 난사 레벨
	BYTE	m_byExcitedRate;	// 흥분 레벨
	BYTE	m_byIronSkin;		// 방어
	BYTE	m_byReAttack;		// 반격
	BYTE	m_bySubAttack;		// 상태이상 발생(부가공격)
	BYTE	m_byState;			// 몬스터 (NPC) 상태이상
	BYTE	m_byPsi;			// 사이오닉 적용
	BYTE	m_byPsiLevel;		// 사이오닉레벨

	BYTE	m_bySearchRange;	// 적 탐지 범위
	int		m_sSpeed;			// 이동속도	

	int		m_sInclination;		// 성향	(유저에게 시민등급향상을 준다.)
	BYTE	m_byColor;			// 보스급과 일반급
	int		m_sStandTime;		// 서있는 시간
	BYTE	m_tNpcType;			// NPC Type
								// 0 : Monster
								// 1 : Normal NPC

	int		m_sFamilyType;		// 몹들사이에서 가족관계를 결정한다.
	BYTE	m_tItemPer;			// 아이템이 떨어질 확률
	BYTE	m_tDnPer;			// 돈이 떨어질확률
	
/*
//	int		m_sCON;				// 건강
//	int		m_sINT;				// 지능
	BYTE	m_byCritical;		// 크리티컬발생 레벨
	BYTE	m_byDamageC;		// 데미지크리티컬 레벨
	BYTE	m_byDelayC;			// 딜레이크리티컬 레벨
	BYTE	m_byOutRange;		// 범위밖 사격 레벨
	BYTE	m_byBlowRate;		// 연타 레벨
	BYTE	m_byCGuard;			// 크리티컬가드	레벨
	int		m_sEvent;			// 이벤트 번호
	int		m_sHaveItem;		// 몬스터가 줄 당시 줄 아이템 인덱스
*/
	CNpcTable();
	virtual ~CNpcTable();
};

#endif // !defined(AFX_NPCTABLE_H__C9E9FA22_E50D_4EAD_980F_2A89E9EDC094__INCLUDED_)
