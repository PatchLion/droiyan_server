// PathFind.cpp: implementation of the CPathFind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PathFind.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define LEVEL_ONE_FIND_CROSS			2
#define LEVEL_ONE_FIND_DIAGONAL			3
#define LEVEL_TWO_FIND_CROSS			11
#define LEVEL_TWO_FIND_DIAGONAL			10

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPathFind::CPathFind()
{
	m_pStack = (STACK *)calloc(1, sizeof(STACK));
	m_pOpen = NULL;
	m_pClosed = NULL;
	m_pMap = NULL;
	m_lMapUse = 0;
#ifdef _DEBUG
	m_pDC = NULL;
#endif
}

CPathFind::~CPathFind()
{
/*	int i;

	if(m_pMap)
	{
		for(i = 0; i < m_vMapSize.cx; i++)
		{
			delete[] m_pMap[i];
		}
		delete[] m_pMap;
		m_pMap = NULL;
	}
*/	ClearData();
	free(m_pStack);
}

void CPathFind::ClearData()
{
	NODE *t_node1, *t_node2;

	if(m_pOpen)
	{
		t_node1 = m_pOpen->NextNode;
		while(t_node1)
		{
			t_node2 = t_node1->NextNode;
			free(t_node1);
			t_node1 = t_node2;
		}
		free(m_pOpen);
		m_pOpen = NULL;
	}

	if(m_pClosed)
	{
		t_node1 = m_pClosed->NextNode;
		while(t_node1)
		{
			t_node2 = t_node1->NextNode;
			free(t_node1);
			t_node1 = t_node2;
		}
		free(m_pClosed);
		m_pClosed = NULL;
	}
}

//void CPathFind::SetMap(int x, int y, int **map)
void CPathFind::SetMap(int x, int y, int *map)
{
//	int i, j;

	if(InterlockedCompareExchange((LONG*)&m_lMapUse, (long)1, (long)0) == (long)0)
	{
/*		if(m_pMap)
		{
			for(i = 0; i < m_vMapSize.cx; i++)
			{
				delete[] m_pMap[i];
			}
			delete[] m_pMap;
			m_pMap = NULL;
		}
		ClearData();
*/
		m_vMapSize.cx = x;
		m_vMapSize.cy = y;

/*		m_pMap = new int*[m_vMapSize.cx];
		for(i = 0; i < m_vMapSize.cx; i++)
		{
			m_pMap[i] = new int[m_vMapSize.cy];
		}

		for(i = 0; i < m_vMapSize.cx; i++)
		{
			for(j = 0; j < m_vMapSize.cy; j++)
			{
				m_pMap[i][j] = map[i][j];
			}
		}
*/
		m_pMap = map;
		::InterlockedExchange(&m_lMapUse, 0);
	}
	else TRACE("잘못된 맵셋팅\n");
}

NODE *CPathFind::FindPath(int start_x, int start_y, int dest_x, int dest_y)
{
	NODE *t_node, *r_node = NULL;
	
	if(!m_pMap) return NULL;

	ClearData();
	m_pOpen = (NODE *)calloc(1, sizeof(NODE));
	m_pClosed = (NODE *)calloc(1, sizeof(NODE));
	
	t_node = (NODE *)calloc(1, sizeof(NODE));
	t_node->g = 0;
//	t_node->h = (int)sqrt((start_x-dest_x)*(start_x-dest_x) + (start_y-dest_y)*(start_y-dest_y));
	t_node->h = 10 * (int)max( abs(start_x-dest_x), abs(start_y-dest_y) );
	t_node->f = t_node->g + t_node->h;
	t_node->x = start_x;
	t_node->y = start_y;

//	int maxtry = (X 이동폭 * 최대 X구간 ) + (Y 이동폭 * 최대 Y구간) + 1;
	int maxtry = abs(start_x-dest_x)*m_vMapSize.cx + abs(start_y-dest_y)*m_vMapSize.cy + 1;
	int count = 0;
	
	m_pOpen->NextNode = t_node;
	while(1) {
		if( count > maxtry * 2 )
		{
//			BREAKPOINT();
//			TRACE("패스파인드 중도포기...%d\n", count);
			return NULL;
		}
		count += 1;
		r_node = (NODE *)ReturnBestNode();
		if(r_node == NULL) break;
		if(r_node->x == dest_x && r_node->y == dest_y)
			break;
		FindChildPath(r_node, dest_x, dest_y);
	}

	return r_node;
}

#ifdef _DEBUG
NODE *CPathFind::FindPath(CDC& dc, int cellx, int celly, int start_x, int start_y, int dest_x, int dest_y)
{
	NODE *t_node, *r_node;
	
	if(!m_pMap) return NULL;

	CFont *old_font, font;
	m_pDC = &dc;
	m_vCell.cx = cellx;
	m_vCell.cy = celly;
	font.CreateFont(-20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH, "System");
	old_font = m_pDC->SelectObject(&font);

	ClearData();
	m_pOpen = (NODE *)calloc(1, sizeof(NODE));
	m_pClosed = (NODE *)calloc(1, sizeof(NODE));
	
	t_node = (NODE *)calloc(1, sizeof(NODE));
	t_node->g = 0;
	t_node->h = (int)sqrt((double)((start_x-dest_x)*(start_x-dest_x) + (start_y-dest_y)*(start_y-dest_y)));
	t_node->f = t_node->g + t_node->h;
	t_node->x = start_x;
	t_node->y = start_y;
	
	m_pOpen->NextNode = t_node;
	while(1) {
		r_node = (NODE *)ReturnBestNode();
		if(r_node == NULL) break;
		if(r_node->x == dest_x && r_node->y == dest_y)
			break;
		FindChildPath(r_node, dest_x, dest_y);
	}

	m_pDC->SelectObject(old_font);
	font.DeleteObject();
	m_pDC = NULL;

	return r_node;
}

void CPathFind::DisplayData(int x, int y, int value)
{
	if(!m_pDC) return;

	CRect t_rect(x*m_vCell.cx, y*m_vCell.cy, (x+1)*m_vCell.cx, (y+1)*m_vCell.cy);
	CString str;

	str.Format("%d", value);
	m_pDC->DrawText(str, &t_rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}
#endif

NODE *CPathFind::ReturnBestNode()
{
	NODE *tmp;
	
	if(m_pOpen->NextNode == NULL) {
		return NULL;
	}
	
	tmp=m_pOpen->NextNode;   // point to first node on m_pOpen
	m_pOpen->NextNode=tmp->NextNode;    // Make m_pOpen point to nextnode or NULL.
	
	tmp->NextNode=m_pClosed->NextNode;
	m_pClosed->NextNode=tmp;
	
	return(tmp);
}

void CPathFind::FindChildPath(NODE *node, int dx, int dy)
{
	int x, y;
/*
	// UpperLeft
	if(IsBlankMap(x=node->x-1,y=node->y-1))
		FindChildPathSub(node, x, y, dx, dy, LEVEL_ONE_FIND_DIAGONAL);
	// Upper
	if(IsBlankMap(x=node->x,y=node->y-1))
		FindChildPathSub(node, x, y, dx, dy, LEVEL_ONE_FIND_CROSS		);
	// UpperRight
	if(IsBlankMap(x=node->x+1,y=node->y-1))
		FindChildPathSub(node, x, y, dx, dy, LEVEL_ONE_FIND_DIAGONAL	);
	// Right
	if(IsBlankMap(x=node->x+1,y=node->y))
		FindChildPathSub(node, x, y, dx, dy, LEVEL_ONE_FIND_CROSS		);
	// LowerRight
	if(IsBlankMap(x=node->x+1,y=node->y+1))
		FindChildPathSub(node, x, y, dx, dy, LEVEL_ONE_FIND_DIAGONAL	);
	// Lower
	if(IsBlankMap(x=node->x,y=node->y+1))
		FindChildPathSub(node, x, y, dx, dy, LEVEL_ONE_FIND_CROSS		);
	// LowerLeft
	if(IsBlankMap(x=node->x-1,y=node->y+1))
		FindChildPathSub(node, x, y, dx, dy, LEVEL_ONE_FIND_DIAGONAL	);
	// Left
	if(IsBlankMap(x=node->x-1,y=node->y))
		FindChildPathSub(node, x, y, dx, dy, LEVEL_ONE_FIND_CROSS		);
*/
	// UpperLeft
	if(IsBlankMap(x=node->x-1,y=node->y-1))
		FindChildPathSub(node, x, y, dx, dy, LEVEL_TWO_FIND_CROSS		);
	// Upper
	if(IsBlankMap(x=node->x,y=node->y-1))
		FindChildPathSub(node, x, y, dx, dy, LEVEL_TWO_FIND_DIAGONAL	);
	// UpperRight
	if(IsBlankMap(x=node->x+1,y=node->y-1))
		FindChildPathSub(node, x, y, dx, dy, LEVEL_TWO_FIND_CROSS		);
	// Right
	if(IsBlankMap(x=node->x+1,y=node->y))
		FindChildPathSub(node, x, y, dx, dy, LEVEL_TWO_FIND_DIAGONAL	);
	// LowerRight
	if(IsBlankMap(x=node->x+1,y=node->y+1))
		FindChildPathSub(node, x, y, dx, dy, LEVEL_TWO_FIND_CROSS		);
	// Lower
	if(IsBlankMap(x=node->x,y=node->y+1))
		FindChildPathSub(node, x, y, dx, dy, LEVEL_TWO_FIND_DIAGONAL	);
	// LowerLeft
	if(IsBlankMap(x=node->x-1,y=node->y+1))
		FindChildPathSub(node, x, y, dx, dy, LEVEL_TWO_FIND_CROSS		);
	// Left
	if(IsBlankMap(x=node->x-1,y=node->y))
		FindChildPathSub(node, x, y, dx, dy, LEVEL_TWO_FIND_DIAGONAL	);
}

void CPathFind::FindChildPathSub(NODE *node, int x, int y, int dx, int dy, int arg)
{
	int g, c=0;
	NODE *old_node,*t_node;
	
	g = node->g + arg;
	
	if((old_node = CheckOpen(x, y)) != NULL)
	{
		for(c = 0; c < 8; c++)
		{
			if(node->Child[c] == NULL)
			{
				break;
			}
		}
		node->Child[c] = old_node;
		if(g < old_node->g)
		{
			old_node->Parent = node;
			old_node->g = g;
			old_node->f = g + old_node->h;
#ifdef _DEBUG
			DisplayData(old_node->x, old_node->y, old_node->g);
#endif
		}
	}
	else if((old_node = CheckClosed(x, y)) != NULL)
	{
		for(c = 0; c < 8; c++)
		{
			if(node->Child[c] == NULL)
			{
				break;
			}
		}
		node->Child[c] = old_node;
		if(g < old_node->g)
		{
			old_node->Parent = node;
			old_node->g = g;
			old_node->f = g + old_node->h;
#ifdef _DEBUG
			DisplayData(old_node->x, old_node->y, old_node->g);
#endif
			PropagateDown(old_node);
		}
	}
	else
	{
		t_node = (NODE *)calloc(1, sizeof(NODE));
		t_node->Parent = node;
		t_node->g = g;
//		t_node->h = (int)sqrt((x-dx)*(x-dx) + (y-dy)*(y-dy));
		t_node->h = (int)max( x-dx, y-dy );
		t_node->f = g + t_node->h;
		t_node->x = x;
		t_node->y = y;
#ifdef _DEBUG
		DisplayData(t_node->x, t_node->y, t_node->g);
#endif
		Insert(t_node);
		for(c = 0; c < 8; c++)
		{
			if(node->Child[c] == NULL)
			{
				break;
			}
		}
		node->Child[c] = t_node;
	}
}

NODE *CPathFind::CheckOpen(int x, int y)
{
	NODE *tmp;
	
	tmp = m_pOpen->NextNode;
	while(tmp != NULL)
	{
		if(tmp->x == x && tmp->y == y)
		{
			return tmp;
		}
		else
		{
			tmp = tmp->NextNode;
		}
	}

	return NULL;
}

NODE *CPathFind::CheckClosed(int x, int y)
{
	NODE *tmp;
	
	tmp = m_pClosed->NextNode;
	
	while(tmp != NULL)
	{
		if(tmp->x == x && tmp->y == y)
		{
			return tmp;
		}
		else
		{
			tmp = tmp->NextNode;
		}
	}

	return NULL;
}

void CPathFind::Insert(NODE *node)
{
	NODE *tmp1, *tmp2;
	int f;
	
	if(m_pOpen->NextNode == NULL)
	{
		m_pOpen->NextNode = node;
		return;
	}
	
	f = node->f;
	tmp1 = m_pOpen;
	tmp2 = m_pOpen->NextNode;
	while((tmp2 != NULL) && (tmp2->f < f))
	{
		tmp1 = tmp2;
		tmp2 = tmp2->NextNode;
	}
	node->NextNode = tmp2;
	tmp1->NextNode = node;
}

void CPathFind::PropagateDown(NODE *old)
{
	int c, g;
	NODE *child, *parent;
	
	g = old->g;
	for(c = 0; c < 8; c++)
	{
		if((child = old->Child[c]) == NULL)
		{
			break;
		}
		if(g+1 < child->g)
		{
			child->g = g+1;
			child->f = child->g + child->h;
			child->Parent = old;
			Push(child);
		}
	}
	
	while (m_pStack->NextStackPtr != NULL)
	{
		parent = Pop();
		for(c = 0; c < 8; c++)
		{
			if((child = parent->Child[c])==NULL)
			{
				break;
			}
			if(parent->g+1 < child->g)
			{
				child->g = parent->g+1;
				child->f = parent->g + parent->h;
				child->Parent = parent;
				Push(child);
			}
		}
	}
}

void CPathFind::Push(NODE *node)
{
	STACK *tmp;
	
	tmp = (STACK *)calloc(1, sizeof(STACK));
	tmp->NodePtr = node;
	tmp->NextStackPtr = m_pStack->NextStackPtr;
	m_pStack->NextStackPtr = tmp;
}

NODE *CPathFind::Pop()
{
	NODE *t_node;
	STACK *t_stack;
	
	t_stack = m_pStack->NextStackPtr;
	t_node = t_stack->NodePtr;
	
	m_pStack->NextStackPtr = t_stack->NextStackPtr;
	free(t_stack);

	return t_node;
}

BOOL CPathFind::IsBlankMap(int x, int y)
{
	if(x < 0 || y < 0 || x >= m_vMapSize.cx || y >= m_vMapSize.cy) return FALSE;

//	return (BOOL)!m_pMap[x][y];
	return (BOOL)!m_pMap[x*m_vMapSize.cy + y];
/*	if(!m_pMap[x][y]) return TRUE;
//	else if(m_pMap[x][y] >= NPC_BAND) return TRUE;
	else return FALSE;
*/
}