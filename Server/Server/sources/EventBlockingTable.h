// EventBlockingTable.h: interface for the CEventBlockingTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTBLOCKINGTABLE_H__D3D9F2C1_E343_4F92_B8BB_43CD0B341E1B__INCLUDED_)
#define AFX_EVENTBLOCKINGTABLE_H__D3D9F2C1_E343_4F92_B8BB_43CD0B341E1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _EVENT
{
	short sBlockType;
	short sX;
	short sY;
	short sZone;
} Event;

typedef CTypedPtrArray <CPtrArray, Event*>	_EventBlockArray;

class CEventBlockingTable  
{
public:
	BOOL CheckUserEvent(int z, int x, int y, int type);
	CEventBlockingTable();
	virtual ~CEventBlockingTable();

public:	
	_EventBlockArray	m_arSellBlock;
	_EventBlockArray	m_arBuyBlock;
	_EventBlockArray	m_arRepaireBlock;
	_EventBlockArray	m_arCureBlock;
	_EventBlockArray	m_arTelBlock;
};

#endif // !defined(AFX_EVENTBLOCKINGTABLE_H__D3D9F2C1_E343_4F92_B8BB_43CD0B341E1B__INCLUDED_)
