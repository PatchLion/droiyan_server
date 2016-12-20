// Item.h: interface for the Item class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEM_H__59D3FA6E_13EE_49E1_9995_9D1878750A76__INCLUDED_)
#define AFX_ITEM_H__59D3FA6E_13EE_49E1_9995_9D1878750A76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TableItem;

class Item  
{
public:
	Item();
	virtual ~Item();
	TableItem* GetTableItem(int num);
	BOOL ParseItemData(char* pBuf);
	void FillItemData(char* pBuf);

public:
	short			m_TNum;			// 테이블 아이템 번호

	BYTE			m_ItemNum;		// 해당 item의 중복수
	BYTE			m_Type;			// 아이템 종류
	BYTE			m_Arm;			// 장착위치
	BYTE			m_Uselevel;		// 사용가능 레벨
	BYTE			m_UseType;		// 사용가능 계열

	short			m_PicNum;		// 그림 번호
	short			m_Wg;			//  SP감소량
	short			m_Dur;			// 내구도
	short			m_MaxAt;		// 최대 공격력
	short			m_AtDelay;		// 공격 딜레이

	BYTE			m_DmgX;			// 대미지 X
	BYTE			m_DmgY;			// 대미지Y
	BYTE			m_DmgZ;			// 대미지Z
	BYTE			m_Df;			// 방어력
	BYTE			m_At;			// 공격 명중값
	BYTE			m_Crit;			// 크리티컬 확률
	BYTE			m_Range;		// 사정거리
	BYTE			m_Out;			// 고장률
	BYTE			m_BullNum;		// 탄창수
	BYTE			m_BullType;		// 탄창종류
	BYTE			m_StErr;		// 상태이상
	BYTE			m_StDf;			// 상태이상 방어
	BYTE			m_StCure;		// 상태이상 치료

	BYTE			m_Hp;			// 회복
	BYTE			m_Pp;			// 회복
	short			m_Sp;;			// 회복

	DWORD			m_Cost;			// 가격
	char			m_Name[ITEM_NAME_LENGTH];
};

#endif // !defined(AFX_ITEM_H__59D3FA6E_13EE_49E1_9995_9D1878750A76__INCLUDED_)
