// CELL.h: interface for the CELL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CELL_H__7D2BEDEF_A182_41DA_AF05_C6E84849FFB3__INCLUDED_)
#define AFX_CELL_H__7D2BEDEF_A182_41DA_AF05_C6E84849FFB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CELL_XSIZE		30
#define CELL_YSIZE		38

#include "MAP.h"
#include "COM.h"
#include "Npc.h"

typedef CArray<int, int> CCellUidArray;
typedef CArray<CPoint,CPoint> CCellItemArray;
//typedef CTypedPtrArray <CPtrArray, ItemList*> MapItemArray;


class CellInfo				// 각 Cell 의 유저 정보
{
public:
	void AddItem(CPoint nUid);
	void DeleteItem(CPoint nUid);
	void GetItem(CArray<CPoint,CPoint>& arItemCopy);	

	void Delete(int nUid);
	void Add(int nUid);
	void Get(CArray<int, int>& arCopy);

	CCellItemArray		m_arItemCell;
	CCellUidArray		m_arCell;
	CRITICAL_SECTION	m_cs;
	CRITICAL_SECTION	m_Itemcs;

	CellInfo();
	~CellInfo();
};

class CELL  
{
public:
	void DeleteCellFromTownPotal(CPoint pt, int nUid);
	void AddCellFromTownPotal(CPoint pt, int nUid);
	void DeleteCellCoordinate(CPoint ptCell, CPoint pt);
	void ChangeMoneyCell(DWORD dwDN, CPoint pt, CPoint ptMap, int uid = -1);
	void DeleteItemCell(CPoint pt, CPoint MapPt);
	void ChangeItemCell(ItemInfoArray &arItem, CPoint pt, CPoint ptMap, int uid);
	void AddItemCell(int uid, CPoint itemPt, int isReg);
	BOOL GetMapItemList(ItemInfoArray &arMapItem, DWORD &dwDN, CPoint pt, int zoneIndex);
	BOOL GetViewMapItemList(ItemInfoArray &arMapItem, DWORD &dwDN, CPoint pt, int zoneIndex);

	CNpc* GetNpc(int nid);
	int GetDirection(CPoint ptOld, CPoint ptNew);
	void ChangeCell(CPoint ptOld, CPoint ptNew, int nUid);
	void DeleteCell(CPoint pt, int nUid);
	void AddCell(CPoint pt, int nUid);
	int GetDirection(int sx, int sy, int ex, int ey);
	CPoint GetCellIndex(int xpos, int ypos);

	CellInfo			**m_pCell;

	CSize				m_sizeCell;
	CSize				m_sizeMap;
	int					m_Zone;

	COM*				m_pCom;

	CELL(CSize size, int nZone, COM *pCom);
	~CELL();

protected:
	void RemoveCellData();

};
#endif // !defined(AFX_CELL_H__7D2BEDEF_A182_41DA_AF05_C6E84849FFB3__INCLUDED_)
