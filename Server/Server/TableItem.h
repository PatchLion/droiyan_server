// TableItem.h: interface for the TableItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLEITEM_H__1A51934E_7C62_45E3_9FE1_AF791407B9BC__INCLUDED_)
#define AFX_TABLEITEM_H__1A51934E_7C62_45E3_9FE1_AF791407B9BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TableItem  
{
public:
	TableItem();
	virtual ~TableItem();

public:
	BOOL GetData(TCHAR* pBuf, int &index);
	int	m_Num;
	int	m_Arm;
	int	m_UseLevel;
	int	m_UseType;
	int	m_PicNum;
	int	m_Wg;
	int	m_Dur;
	int	m_MaxAt;
	int	m_AtDelay;
	int	m_DmgX;
	int	m_DmgY;
	int	m_DmgZ;
	int	m_Df;
	int	m_At;
	int	m_Crit;
	int	m_Range;
	int	m_Out;
	int	m_BullNum;
	int	m_BullType;
	int	m_StErr;
	int	m_StDf;
	int	m_StCure;
	int	m_HP;
	int	m_PP;
	int	m_SP;

	DWORD			m_Cost;			// АЁАн
	char			m_Name[ITEM_NAME_LENGTH];
};

#endif // !defined(AFX_TABLEITEM_H__1A51934E_7C62_45E3_9FE1_AF791407B9BC__INCLUDED_)
