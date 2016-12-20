// Item.cpp: implementation of the Item class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "Item.h"
#include "extern.h"
#include "ServerDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern TableItemArray  g_DBItemArray;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Item::Item()
{

}

Item::~Item()
{

}

BOOL Item::ParseItemData(char *pBuf)
{
	int index = 0;

	m_TNum = GetShort(pBuf, index);
	m_Dur  = GetShort(pBuf, index);
	m_BullNum = GetByte(pBuf, index);
	m_ItemNum = GetByte(pBuf, index);
	m_Cost = GetDWORD(pBuf, index);

	TableItem* tItem = GetTableItem( m_TNum );	if( !tItem ) return FALSE;

//	m_Type = tItem->;			// 아이템 종류
	m_Arm = tItem->m_Arm;			// 장착위치
	m_Uselevel = tItem->m_UseLevel;		// 사용가능 레벨
	m_UseType = tItem->m_UseType;		// 사용가능 계열

	m_PicNum = tItem->m_PicNum;		// 그림 번호
	m_Wg = tItem->m_Wg;			//  SP감소량
	m_Dur = tItem->m_Dur;			// 내구도
	m_MaxAt = tItem->m_MaxAt;		// 최대 공격력
	m_AtDelay = tItem->m_AtDelay;		// 공격 딜레이

	m_DmgX = tItem->m_DmgX;			// 대미지 X
	m_DmgY = tItem->m_DmgY;			// 대미지Y
	m_DmgZ = tItem->m_DmgZ;			// 대미지Z
	m_Df = tItem->m_Df;			// 방어력
	m_At = tItem->m_At;			// 공격 명중값
	m_Crit = tItem->m_Crit;			// 크리티컬 확률
	m_Range = tItem->m_Range;		// 사정거리
	m_Out = tItem->m_Out;			// 고장률
	m_BullNum = tItem->m_BullNum;		// 탄창수
	m_BullType = tItem->m_BullType;		// 탄창종류
	m_StErr = tItem->m_StErr;		// 상태이상
	m_StDf = tItem->m_StDf;			// 상태이상 방어
	m_StCure = tItem->m_StCure;		// 상태이상 치료

	m_Hp = tItem->m_HP;			// 회복
	m_Pp = tItem->m_PP;			// 회복
	m_Sp = tItem->m_SP;			// 회복

	return TRUE;
}

TableItem* Item::GetTableItem(int num)
{
	if( num < 0 || num >= 1000 ) return NULL;

	return g_DBItemArray[num];
}

void Item::FillItemData(char *pBuf)
{
	int index = 0;

	SetShort(pBuf, m_TNum, index);
	SetShort(pBuf, m_Dur, index);
	SetByte(pBuf, m_BullNum, index);
	SetByte(pBuf, m_ItemNum, index);

	SetDWORD(pBuf, m_Cost, index);
}
