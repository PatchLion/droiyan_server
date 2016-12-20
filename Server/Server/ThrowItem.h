// ThrowItem.h: interface for the CThrowItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THROWITEM_H__D4630979_CF80_4456_92D1_F090B85F12B4__INCLUDED_)
#define AFX_THROWITEM_H__D4630979_CF80_4456_92D1_F090B85F12B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Map.h"

class CThrowItem  
{
public:
	int		m_z;
	int		m_x;
	int		m_y;
	int		ID;

//	LONG	lRef;
//	LONG	lExistRef;
	DWORD	dTime;//物品产生时间
	ItemList*	m_pItem;
	class CThrowItem  *next;//下一个结点
	class CThrowItem  *front;//上一个结点
	CThrowItem();
	virtual ~CThrowItem();
};

#endif // !defined(AFX_THROWITEM_H__D4630979_CF80_4456_92D1_F090B85F12B4__INCLUDED_)
