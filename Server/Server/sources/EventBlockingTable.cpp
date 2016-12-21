// EventBlockingTable.cpp: implementation of the CEventBlockingTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "EventBlockingTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEventBlockingTable::CEventBlockingTable()
{

}

CEventBlockingTable::~CEventBlockingTable()
{

}

BOOL CEventBlockingTable::CheckUserEvent(int z, int x, int y, int type)
{
	int i = 0; 
	BOOL bSuccess = FALSE;	

	switch(type)
	{
	case SELL_BLOCK:
		for(i = 0; i < m_arSellBlock.GetSize(); i++)
		{
			if(z != m_arSellBlock[i]->sZone) continue;
			if( abs( x - m_arSellBlock[i]->sX ) + abs( y - m_arSellBlock[i]->sY ) <= ITEM_MAX_RANGE ) bSuccess = TRUE;
		}
		break;
	case BUY_BLOCK:
		for(i = 0; i < m_arBuyBlock.GetSize(); i++)
		{
			if(z != m_arBuyBlock[i]->sZone) continue;
			if( abs( x - m_arBuyBlock[i]->sX ) + abs( y - m_arBuyBlock[i]->sY ) <= ITEM_MAX_RANGE ) bSuccess = TRUE;
		}
		break;
	case REPAIR_BLOCK:
		for(i = 0; i < m_arRepaireBlock.GetSize(); i++)
		{
			if(z != m_arRepaireBlock[i]->sZone) continue;
			if( abs( x - m_arRepaireBlock[i]->sX ) + abs( y - m_arRepaireBlock[i]->sY ) <= ITEM_MAX_RANGE ) bSuccess = TRUE;
		}
		break;
	case CURE_BLOCK:
		for(i = 0; i < m_arCureBlock.GetSize(); i++)
		{
			if(z != m_arCureBlock[i]->sZone) continue;
			if( abs( x - m_arCureBlock[i]->sX ) + abs( y - m_arCureBlock[i]->sY ) <= ITEM_MAX_RANGE ) bSuccess = TRUE;
		}
		break;
	case TEL_BLOCK:
		for(i = 0; i < m_arTelBlock.GetSize(); i++)
		{
			if(z != m_arTelBlock[i]->sZone) continue;
			if( abs( x - m_arTelBlock[i]->sX ) + abs( y - m_arTelBlock[i]->sY ) <= ITEM_MAX_RANGE ) bSuccess = TRUE;
		}
		break;
	default:
		break;
	}

	return bSuccess;
}

