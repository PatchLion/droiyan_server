// PathFind.h: interface for the CPathFind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATHFIND_H__04C22295_0166_11D3_B49A_00C02615866B__INCLUDED_)
#define AFX_PATHFIND_H__04C22295_0166_11D3_B49A_00C02615866B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class NODE {
public:
    int f;
	int h;
    int g;
    int x;
	int y;
    NODE *Parent;
    NODE *Child[8];
    NODE *NextNode;
};

class STACK {
public:
    NODE *NodePtr;
    STACK *NextStackPtr;
};

class CPathFind
{
public:
	BOOL IsBlankMap(int x, int y);
//	void SetMap(int x, int y, int **map);
	void SetMap(int x, int y, int *map);
	void PropagateDown(NODE *old);
	void Insert(NODE *node);
	NODE *CheckOpen(int x, int y);
	NODE *CheckClosed(int x, int y);
	void FindChildPathSub(NODE *node, int x, int y, int dx, int dy, int arg);
	void FindChildPath(NODE *node, int dx, int dy);
	void ClearData();
	NODE *ReturnBestNode();
	NODE *FindPath(int start_x, int start_y, int dest_x, int dest_y);
	CPathFind();
	virtual ~CPathFind();

	void Push(NODE *node);
	NODE *Pop();

#ifdef _DEBUG
	NODE *FindPath(CDC& dc, int cellx, int celly, int start_x, int start_y, int dest_x, int dest_y);
	void DisplayData(int x, int y, int value);
#endif
protected:
	LONG	m_lMapUse;	
	NODE *m_pOpen, *m_pClosed;
	STACK *m_pStack;
//	int **m_pMap;
	int *m_pMap;
	CSize m_vMapSize;
#ifdef _DEBUG
	CDC *m_pDC;
	CSize m_vCell;
#endif
};

#endif // !defined(AFX_PATHFIND_H__04C22295_0166_11D3_B49A_00C02615866B__INCLUDED_)
