// TableItem.cpp: implementation of the TableItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "TableItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TableItem::TableItem()
{

}

TableItem::~TableItem()
{

}

BOOL TableItem::GetData(TCHAR *pBuf, int &index)
{
	int strNameLen = 0;

	if(!m_Num) return FALSE;

	SetShort(pBuf, m_Num, index);
	SetByte(pBuf, m_Arm, index);
	SetByte(pBuf, m_UseLevel, index);
	SetByte(pBuf, m_UseType, index);

	SetShort(pBuf, m_PicNum, index);
	SetShort(pBuf, m_Wg, index);
	SetShort(pBuf, m_Dur, index);
	SetShort(pBuf, m_MaxAt, index);
	SetShort(pBuf, m_AtDelay, index);

	SetByte(pBuf, m_DmgX, index);
	SetByte(pBuf, m_DmgY, index);
	SetByte(pBuf, m_DmgZ, index);
	SetByte(pBuf, m_Df, index);
	SetByte(pBuf, m_At, index);
	SetByte(pBuf, m_Crit, index);
	SetByte(pBuf, m_Range, index);
	SetByte(pBuf, m_Out, index);
	SetByte(pBuf, m_BullNum, index);
	SetByte(pBuf, m_BullType, index);
	SetByte(pBuf, m_StErr, index);
	SetByte(pBuf, m_StDf, index);
	SetByte(pBuf, m_StCure, index);

	SetByte(pBuf, m_HP, index);
	SetByte(pBuf, m_PP, index);

	SetShort(pBuf, m_SP, index);

	SetInt(pBuf, m_Cost, index);

	strNameLen = strlen(m_Name);
	SetString(pBuf, m_Name, strNameLen, index);

	return TRUE;
}
