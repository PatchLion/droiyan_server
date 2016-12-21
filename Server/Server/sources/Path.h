#ifndef _PATH_H_
#define _PATH_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "MAP.h"

#define ON				1	
#define OE				2
#define OS				3
#define OW				4
#define NE				5
#define ES				6
#define SW				7
#define WN				8

#define STACKNUM		40
#define MAX_NODE		40

typedef CList<CPoint, CPoint> LIST_POINT;

class CPath
{
	typedef struct POS_LINK
	{
		int x;
		int y;
		int Type;
		BOOL nFlag;

		POS_LINK *next;
		POS_LINK *prev;
	} POS;
	typedef struct PATH_CONER
	{
		int x;
		int y;
		int dist;
	} PATH;
	typedef struct PATH_LIST
	{
		int x;
		int y;
	} PATHLIST;

public:
	CPath();
	~CPath();

////////////////////////////////////////////////////////////////////////////
//	Add by JJS (2000-11-28)
	MapInfo			**m_pTile;

////////////////////////////////////////////////////////////////////////////
	void	SetTarget(BOOL flag) { m_Object = flag; }	// 목표 좌표면 TRUE, 방황이면 FALSE;를 미리 셋팅한다.
	void	IsGhost(BOOL isDead);						// 유령일때 TRUE;
	BOOL	IsMovable(int x, int y);
//	void	LockCell(int x, int y, int id) { ::InterlockedExchange(&m_pTile[x][y].m_lMove, id); }
//	void	FreeCell(int x, int y) { ::InterlockedExchange(&m_pTile[x][y].m_lMove, 0); }
	LIST_POINT* PathFinder(int starx, int stary, int destx, int desty);
	void	SetTile(MapInfo **ppMap, int x, int y);			//	맵을 셋팅한다

private:
	int		GetPathListNum() { return m_PathListNum; }
////////////////////////////////////////////////////////////////////////////

	POS*	InsertNode(POS *node, BOOL head);
	void	FreeNode(POS *node);
	void	DeleteNode(POS *now, POS *end);
	POS*	ChoiceNode();

	POS*	GetNodePool();
	BOOL	FreeNodePool(POS *Node);
	void	DeleteNodePool();
	void	InitNodePool();

	void	Generate();								//	
	int		CheckDirection(int x, int y);			//	탐색할 방향을 알려줌
	BOOL	SearchBlock(POS *str, POS *end);
	BOOL	IsBlock(POS *pre, POS *next);			//	탐색방향중에 장애물이 있는지..
	BOOL	IsConer(int x, int y);
	POS*	NextNode(POS *str, POS *end);			//	
	int		SearchTile(POS *str);					//	찾은 모서리를 모두 저장한다.
	POS*	GenerateSuccessors(POS *str, POS *end, int num);	//	
	BOOL	CompareNode(int x, int y);				//	모서리값이 이전에 저장이 되지 않아야한다
	BOOL	Boundary(int x, int y);
	void	Setting();								//	초기화
	void	SettingConer();

	void	PathList(POS *pstr, POS *pend);
	void	PutDistance();
	void	PutYPath(POS *str, int x, int y);
	void	PutXPath(POS *str, int x, int y);
	int		PutXPath(PATH *PathList, int x, int y, int ax, int ay);
	int		PutYPath(PATH *PathList, int x, int y, int ax, int ay);

	int		Push(int num);
	int		Pop();
	void	QSort(PATH dist[], int n);

private:
	POS		*m_NodePool;
	POS		*m_pStrLink;
	POS		*m_pEndLink;

	int		m_Stack[STACKNUM];
	int		m_StackNum;

	int		m_BlockTileX;
	int		m_BlockTileY;
	PATH	m_PathConer[8];

//////////////////////////////////////////////////////
	int		m_nSizeX;
	int		m_nSizeY;
//////////////////////////////////////////////////////

	int		m_ConerAtt[9][9];
	BOOL	m_bConer;
	BOOL	m_Ghost;				//	유령모드 ( Default = FALSE )
	BOOL	m_Object;				//	목표 있음
	RECT	m_bRect;

	PATHLIST m_PathList[150];
	int		m_PathListNum;
};


#endif

