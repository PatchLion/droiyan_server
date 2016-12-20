#include "stdafx.h"
#include "path.h"

CPath::CPath()
{
	m_NodePool = NULL;			// 새로운 노드를 초기화한다.
	m_NodePool = new POS[MAX_NODE];
	InitNodePool();

	m_pStrLink = (POS *)calloc(1,sizeof(POS));
	m_pEndLink = (POS *)calloc(1,sizeof(POS));

	m_pStrLink->prev = NULL;
	m_pStrLink->next = m_pEndLink;
	m_pEndLink->prev = m_pStrLink;
	m_pEndLink->next = NULL;

	m_PathListNum = 0;
	m_bConer		= FALSE;
	m_Ghost			= FALSE;
	m_Object		= FALSE;	
	m_bRect.bottom	= 0;
	m_bRect.left	= 0;
	m_bRect.right	= 0;
	m_bRect.top		= 0;
	m_StackNum = 0;
	m_BlockTileX = 0;
	m_BlockTileY = 0;
	m_pTile = NULL;
	SettingConer();

	for(int a = 0; a < 150; a++)
	{ 
		m_PathList[a].x = 0; 
		m_PathList[a].y = 0;
	}
}

void CPath::SettingConer()
{
	int i, j;
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)  m_ConerAtt[i][j] = 0;
	}

	m_ConerAtt[1][4] = m_ConerAtt[1][7] = m_ConerAtt[1][8] = 1;
	m_ConerAtt[2][1] = m_ConerAtt[2][5] = m_ConerAtt[2][8] = 1;
	m_ConerAtt[3][2] = m_ConerAtt[3][5] = m_ConerAtt[3][6] = 1;
	m_ConerAtt[4][3] = m_ConerAtt[4][6] = m_ConerAtt[4][7] = 1;
	m_ConerAtt[5][1] = m_ConerAtt[5][4] = m_ConerAtt[5][8] = 1;
	m_ConerAtt[6][1] = m_ConerAtt[6][2] = m_ConerAtt[6][5] = 1;
	m_ConerAtt[7][2] = m_ConerAtt[7][3] = m_ConerAtt[7][6] = 1;
	m_ConerAtt[8][3] = m_ConerAtt[8][4] = m_ConerAtt[8][7] = 1;
}

CPath::~CPath()
{
	free(m_pStrLink);
	free(m_pEndLink);
	DeleteNodePool();			// 할당한 노드를 삭제한다.
}

void CPath::SetTile(MapInfo **ppMap, int x, int y)
{
	m_pTile = ppMap;
	m_nSizeX = x;
	m_nSizeY = y;
}

void CPath:: Setting()
{
	int i;
	for(i = 0; i < STACKNUM; i += 4)
	{
		m_Stack[i] = 0;
		m_Stack[i+1] = 0;
		m_Stack[i+2] = 0;
		m_Stack[i+3] = 0;
	}
	for(i = 0; i < 8; i += 2)
	{
		m_PathConer[i].x = 0;
		m_PathConer[i].y = 0;
		m_PathConer[i].dist = 0;
		m_PathConer[i+1].x = 0;
		m_PathConer[i+1].y = 0;
		m_PathConer[i+1].dist = 0;
	}
	m_BlockTileX = 0;
	m_BlockTileY = 0;
	m_PathListNum = 0;
}


int CPath::CheckDirection(int x, int y)
{
	if(y > 0)
	{
		if(x > 0)		{ return ES; }	// 4
		else if(x < 0)	{ return SW; }	// 6
		else			{ return OS; }	// 5
	}
	else if(y < 0)
	{
		if(x > 0)		{ return NE; }	// 2
		else if(x < 0)	{ return WN; }	// 8
		else			{ return ON; }	// 1
	}
	else
	{
		if(x > 0)		{ return OE; }	// 3
		else			{ return OW; }	// 7
	}
}


CPath::POS *CPath::InsertNode(POS *node, BOOL head)
{
	POS *temp = NULL;
	POS *old = NULL;

	temp = GetNodePool();
	if(temp == NULL) return NULL;

	old = node->next;
	old->prev = temp;
	node->next = temp;
	temp->prev = node;
	temp->next = old;

	return temp;
}

void CPath::DeleteNode(POS *now, POS *end)
{
	POS *Dnode;
	POS *temp = now->next;

	do
	{
		Dnode = temp;
		temp = temp->next;
		FreeNodePool(Dnode);	
		if(temp == end) break;		

	} while(1);

	now->next = end;
	end->prev = now;
}

//------------------------------------------------------------------------
//	Name :	FreeNode(POS *node, int num) 
//	Desc :	시작되는 노드와 해당 숫자	
//	UpDate:	2000, 9, 17
//------------------------------------------------------------------------
void CPath::FreeNode(POS *node)
{
	InitNodePool();
	m_pStrLink->next = m_pEndLink;
	m_pEndLink->prev = m_pStrLink;
}

LIST_POINT* CPath::PathFinder(int starx, int stary, int destx, int desty)
{
//	bool exec = false;
//	bool search = true;-
	int sum = starx + stary;

	if(destx < 3 || desty < 3 || destx >= m_nSizeX-3 || desty >= m_nSizeY-3) return NULL;//search = false;

	if( starx == destx && stary == desty ) return NULL;//&& search) exec = true;

	int lMove = m_pTile[destx][desty].m_bMove;
	sum = destx + desty;
	if(m_Ghost) m_Object = FALSE;
	
	if(m_pTile[destx][desty].m_bMove != 0 && sum%2 != 0 ) return NULL;

	m_PathListNum = 0;
	m_pStrLink->x = starx;
	m_pStrLink->y = stary;
	m_pEndLink->x = destx;
	m_pEndLink->y = desty;
	m_pEndLink->prev = m_pStrLink;
	
	if( SearchBlock(m_pStrLink, m_pEndLink) )
	{
		Generate();
		FreeNode(m_pStrLink->next);
	}
	else
	{
		PutDistance();		
	}
	
	//return m_PathList;
	if (!m_PathListNum) return NULL;
	
	LIST_POINT*	pRoute = new LIST_POINT;
	//		TRACE("NewPath : ");
	
	CPoint ptPos;
	for (int i=0; i<m_PathListNum; i++) {
		ptPos.x = m_PathList[i].x;
		ptPos.y = m_PathList[i].y;
		
		//			TRACE("(%d,%d) ", ptPos.x, ptPos.y);
		pRoute->AddTail(ptPos);
	}
	//		TRACE("\n");
	
	return pRoute;
}


//------------------------------------------------------------------------
//	Name :	Generate() 
//	Desc :	변경 : 탐색 범위 제한을 두지않음
//	UpDate:	2000, 12, 11
//------------------------------------------------------------------------
void CPath::Generate()
{
	int sx = m_pStrLink->x; 
	int sy = m_pStrLink->y; 
	int dx = m_pEndLink->x;
	int dy = m_pEndLink->y;
	
	POS *newNode=NULL, *Node = NULL;
	POS	*tempNode = NULL;

	Node = m_pStrLink;
	newNode = m_pEndLink;

	do
	{
		tempNode = NextNode(Node, newNode);
		if(tempNode == NULL) 
		{
			if( SearchBlock(Node, newNode) ) { Node = ChoiceNode(); break; }
			else
			{
				if(Node->prev == NULL) { Node = m_pEndLink; break; }
				Node = Node->prev;
				newNode = newNode->prev;
			}
		}
		else	Node = tempNode;
		
	} while(1);

	PathList(m_pStrLink, Node);
}

//------------------------------------------------------------------------
//	Name :	NextNode(POS *str, POS *end) 
//	Desc :	주어진 두점사이에서 2개 모서리를 판단하고, 메모리를..
//	UpDate:	2000, 9, 18
//------------------------------------------------------------------------
CPath::POS *CPath::NextNode(POS *str, POS *end)
{
	int num = 0;
	POS *temp = NULL;

	Setting();
	if( SearchBlock(str, end) )
	{
		num = SearchTile(str);
		if(num)
		{
			temp = GenerateSuccessors(str, end, num);
			if(!m_bConer && temp == NULL)
			{
				SearchBlock(end, str);
				num = SearchTile(str);
				if(num)	temp = GenerateSuccessors(str, end, num);
			}
		}

	}

	return temp;
}


//------------------------------------------------------------------------
//	Name :	GenerateSuccessors()
//	Desc :	노드를 추가한다.
//	UpDate:	2000, 9, 18
//------------------------------------------------------------------------
CPath::POS *CPath::GenerateSuccessors(POS *str, POS *end, int num)
{
	int  lean = 0, test = 0;
	BOOL bNode = false;
	int	 type = 0, i;
	int  tempx = 0, tempy = 0;
	int  dirOne = 0, dirTwo = 0;
	POS  *temp = NULL;
	m_bConer = false;

	QSort(m_PathConer, num);

	for(i = 0; i < num; i++)
	{
		if(m_bConer) break;
		tempx = m_PathConer[i].x - str->x;
		tempy = m_PathConer[i].y - str->y;
		dirOne = CheckDirection(tempx, tempy);
		tempx = end->x - m_PathConer[i].x;
		tempy = end->y - m_PathConer[i].y;
		dirTwo = CheckDirection(tempx, tempy);

		if( (dirOne == 6 && dirTwo == 8) || (dirOne == 8 && dirTwo == 6) || (dirOne == 6 && dirTwo == 6) || (dirOne == 5 && dirTwo == 5)) 
		{
			lean = (int)( abs(str->y - m_PathConer[i].y)/abs(str->x - m_PathConer[i].x) );
			test = (int)( abs(end->y - m_PathConer[i].y)/abs(end->x - m_PathConer[i].x) );
			if(test > lean) type = 1;
			else type = 0;
		}
		else if( (dirOne == 5 && dirTwo == 7) || (dirOne == 7 && dirTwo == 5) || (dirOne == 7 && dirTwo == 7) || (dirOne == 8 && dirTwo == 8))
		{
			lean = (int)( abs(str->y - m_PathConer[i].y)/abs(str->x - m_PathConer[i].x) );
			test = (int)( abs(end->y - m_PathConer[i].y)/abs(end->x - m_PathConer[i].x) );
			if(test > lean) type = 0;
			else type = 1;
		}
		else type = m_ConerAtt[dirOne][dirTwo];

		bNode = CompareNode(m_PathConer[i].x, m_PathConer[i].y);
		if( (str->Type == type || str == m_pStrLink) && !m_bConer && bNode) 
		{
			m_bConer = true;
			temp = InsertNode(str, true);
			temp->Type = type;
			temp->x = m_PathConer[i].x;
			temp->y = m_PathConer[i].y;
		}
	}

	return temp;
}


BOOL CPath::CompareNode(int x, int y)
{
	BOOL coner = TRUE;
	POS *temp = m_pStrLink;

	do
	{
		if((temp->x == x) && (temp->y == y))
		{
			coner = FALSE; 
			break;
		}
		temp = temp->next;
		if(temp == NULL) break;

	} while(1);

	return coner;
}

CPath::POS* CPath::ChoiceNode()
{
	int i = 0;
	POS *str = m_pStrLink;
	POS *end = m_pStrLink->next;

	do
	{
		if(SearchBlock(str, end)) 
		{
			if(str->next != m_pEndLink) DeleteNode(str, m_pEndLink);
			str->next = NULL;
			m_pEndLink->prev = NULL;
			break;
		}
		else
		{
			str = str->next;
			end = end->next;
		}
			
	} while(end != NULL);

	return str;
}

//------------------------------------------------------------------------
//	Name :	SearchTile()
//	Desc :	
//	UpDate:	2000, 9, 18
//------------------------------------------------------------------------
int CPath::SearchTile(POS *str)
{
	char    tes = 0;//, dir = 0;
	int		ConerNum = 0;
	int		TileValue = 0;
	int		tempX = m_BlockTileX;
	int		tempY = m_BlockTileY;
	BOOL	ConerTile = FALSE; 

	do
	{
		if(tempY <= 0 || tempX >= m_nSizeX) break;
		TileValue = m_pTile[tempX][tempY].m_bMove;				//	NE
		if(!TileValue) 
		{
			if( IsConer(tempX-1, tempY+1) )
			{
				if((tempX-1 == m_BlockTileX) && (tempY+1 == m_BlockTileY) && ( abs(str->x - tempX-1) == abs(str->y - tempY+1) )) tes = 3;
				m_PathConer[ConerNum].x = tempX; m_PathConer[ConerNum].y = tempY;
				m_PathConer[ConerNum].dist = abs(tempX - m_BlockTileX) + tes + ( abs(tempX - str->x)+abs(tempY - str->y) )/2;
				ConerTile = TRUE; ConerNum++; 
			}
		}
		else	{ tempX++; tempY--; }
	} while(TileValue && (tempX%2 == tempY%2));

	tes = 0;
	tempX = m_BlockTileX;
	tempY = m_BlockTileY;

	do
	{
		if(tempX >= m_nSizeX || tempY >= m_nSizeY) break;
		TileValue = m_pTile[tempX][tempY].m_bMove;				//	ES
		if(!TileValue) 
		{
			if( IsConer(tempX-1, tempY-1) )
			{
				if((tempX-1 == m_BlockTileX) && (tempY-1 == m_BlockTileY) && ( abs(str->x - tempX-1) == abs(str->y - tempY-1) )) tes = 3;
				m_PathConer[ConerNum].x = tempX; m_PathConer[ConerNum].y = tempY;
				m_PathConer[ConerNum].dist = abs(tempX - m_BlockTileX) + tes +( abs(tempX - str->x)+abs(tempY - str->y) )/2;
				ConerTile = TRUE; ConerNum++; 
			}
		}
		else	{ tempX++; tempY++; }
	} while(TileValue && (tempX%2 == tempY%2));

	tes = 0;
	tempX = m_BlockTileX;
	tempY = m_BlockTileY;

	do
	{		
		if(tempX <= 0 || tempY >= m_nSizeY) break;
		TileValue = m_pTile[tempX][tempY].m_bMove;				//	SW
		if(!TileValue) 
		{
			if( IsConer(tempX+1, tempY-1) )
			{
				if((tempX+1 == m_BlockTileX) && (tempY-1 == m_BlockTileY) && ( abs(str->x - tempX+1) == abs(str->y - tempY-1) )) tes = 3;
				m_PathConer[ConerNum].x = tempX; m_PathConer[ConerNum].y = tempY;
				m_PathConer[ConerNum].dist = abs(tempX - m_BlockTileX) + tes +( abs(tempX - str->x)+abs(tempY - str->y) )/2;	
				ConerTile = TRUE; ConerNum++; 
			}
		}
		else	{ tempX--; tempY++; }
	} while(TileValue && (tempX%2 == tempY%2));

	tes = 0;
	tempX = m_BlockTileX;
	tempY = m_BlockTileY;

	do
	{		
		if(tempX < 0 || tempY < 0) break;
		TileValue = m_pTile[tempX][tempY].m_bMove;				//	WN
		if(!TileValue) 
		{
			if( IsConer(tempX+1, tempY+1) )
			{
				if((tempX+1 == m_BlockTileX) && (tempY+1 == m_BlockTileY) && ( abs(str->x - tempX+1) == abs(str->y - tempY+1) )) tes = 3;
				m_PathConer[ConerNum].x = tempX; m_PathConer[ConerNum].y = tempY;
				m_PathConer[ConerNum].dist = abs(tempX - m_BlockTileX) + tes + ( abs(tempX - str->x)+abs(tempY - str->y) )/2;	
				ConerTile = TRUE; ConerNum++; 
			}
		}
		else	{ tempX--; tempY--; }
	} while(TileValue && (tempX%2 == tempY%2));

	if(!ConerTile)
	{
		tempX = m_BlockTileX;
		tempY = m_BlockTileY;
		do
		{
			if(tempY <= 0) break;
			TileValue = m_pTile[tempX][tempY].m_bMove;		//	ON
			if(!TileValue) 
			{
				if( IsConer(tempX, tempY+1) )
				{
					m_PathConer[ConerNum].x = tempX; m_PathConer[ConerNum].y = tempY;
					m_PathConer[ConerNum].dist = m_BlockTileY - tempY; ConerTile = TRUE; ConerNum++; 
				}
			}
			else	tempY -= 2;
		} while(TileValue);
		
		tempX = m_BlockTileX;
		tempY = m_BlockTileY;

		do
		{
			if(tempX >= m_nSizeX) break;
			TileValue = m_pTile[tempX][tempY].m_bMove;		//	OE
			if(!TileValue) 
			{
				if( IsConer(tempX-1, tempY) )
				{ 
					m_PathConer[ConerNum].x = tempX; m_PathConer[ConerNum].y = tempY;
					m_PathConer[ConerNum].dist = tempX - m_BlockTileX; ConerTile = TRUE; ConerNum++; 
				}
			}
			else	tempX += 2;
		} while(TileValue);

		tempX = m_BlockTileX;
		tempY = m_BlockTileY;
		do
		{
			if(tempY >= m_nSizeY) break;
			TileValue = m_pTile[tempX][tempY].m_bMove;		//	OS
			if(!TileValue) 
			{
				if( IsConer(tempX, tempY-1) )
				{ 
					m_PathConer[ConerNum].x = tempX; m_PathConer[ConerNum].y = tempY;
					m_PathConer[ConerNum].dist = tempY - m_BlockTileX; ConerTile = TRUE; ConerNum++; 
				}
			}
			else	tempY += 2;
		} while(TileValue);

		tempX = m_BlockTileX;
		tempY = m_BlockTileY;
		do
		{
			if(tempX <= 0) break;
			TileValue = m_pTile[tempX][tempY].m_bMove;		//	OW
			if(!TileValue) 
			{
				if( IsConer(tempX+1, tempY) )
				{
					m_PathConer[ConerNum].x = tempX; m_PathConer[ConerNum].y = tempY;
					m_PathConer[ConerNum].dist = m_BlockTileX - tempX;	ConerTile = TRUE; ConerNum++; 
				}
			}
			else	tempX -= 2;
		} while(TileValue);
	}

	return ConerNum;
}

//------------------------------------------------------------------------
//	Name :	IsConer()
//	Desc :	모서리인지 판단(변경 : 그 외지점이 1인지 판단)
//	UpDate:	2000, 9, 18
//------------------------------------------------------------------------
BOOL CPath::IsConer(int x, int y)
{
	BOOL bConer = FALSE;

	if( (!m_pTile[x-1][y-1].m_bMove) && (!m_pTile[x+1][y-1].m_bMove ))	//   ^
	{
		if((m_pTile[x-2][y].m_bMove) && (m_pTile[x-1][y+1].m_bMove) && (m_pTile[x+1][y+1].m_bMove) && (m_pTile[x+2][y].m_bMove)) bConer = FALSE;
		else bConer = TRUE;
	}

	if(!bConer && (!m_pTile[x+1][y-1].m_bMove) && (!m_pTile[x+1][y+1].m_bMove) )//	>	
	{
		if((m_pTile[x][y-2].m_bMove) && (m_pTile[x-1][y-1].m_bMove) && (m_pTile[x-1][y+1].m_bMove) && (m_pTile[x][y+2].m_bMove)) bConer = FALSE;
		else bConer = TRUE;
	}

	if(!bConer &&  (!m_pTile[x-1][y+1].m_bMove) && (!m_pTile[x+1][y+1].m_bMove) )//	
	{
		if((m_pTile[x-2][y].m_bMove) && (m_pTile[x-1][y-1].m_bMove) && (m_pTile[x+1][y-1].m_bMove) && (m_pTile[x+2][y].m_bMove)) bConer = FALSE;
		else bConer = TRUE;
	}

	if(!bConer && (!m_pTile[x-1][y-1].m_bMove) && (!m_pTile[x-1][y+1].m_bMove) )//	<
	{
		if((m_pTile[x][y-2].m_bMove) && (m_pTile[x+1][y-1].m_bMove) && (m_pTile[x+1][y+1].m_bMove) && (m_pTile[x][y+2].m_bMove)) bConer = FALSE;
		else bConer = TRUE;
	}

	return bConer;
}

//-----------------------------------------------------------------------------
// Name: IsShortDistance
// Desc: 양쪽으로부터 검색하면서 방해물이 있는지검색(변동 : 현재 지점은 무시)
// UpDate : 2000, 12, 11
//-----------------------------------------------------------------------------
BOOL CPath::SearchBlock(POS *str, POS *end)
{
	int bx = 0, by = 0;

	if(IsBlock(str, end))
	{
		bx = m_BlockTileX;
		by = m_BlockTileY;

		if(IsBlock(end, str)) 
		{
			m_BlockTileX = bx;
			m_BlockTileY = by;
			return TRUE;
		}
		else return FALSE;
	}
	else return FALSE;
}

//------------------------------------------------------------------------
//	Name :	IsBlock()
//	Desc :	변동 : 현재좌표와 목표좌표을 제외( 유령모드 추가 : if(m_Ghost && TileValue > 1) 무시 )
//	UpDate:	2000, 3, 5
//------------------------------------------------------------------------
BOOL CPath::IsBlock(POS *pre, POS *next)
{
	BOOL BlockTile = FALSE;
	int TileValue = 0, num = 0;
	int i = pre->x;
	int j = pre->y;
	int ax = next->x - pre->x;
	int ay = next->y - pre->y;
	int x, y, Ln = 0, On = 0, pDEST;
	int DEST = CheckDirection(ax, ay);
	x = abs(abs(ax) - 1);		//	for testing 하나씩 뺀다.
	y = abs(abs(ay) - 1);		//	for testing 하나씩 뺀다.

	if(DEST > 4)
	{
		Ln = (x + y)/2;
		if(!(x - y)) { num = 1; }
		else
		{
			On = abs(x - y)/2;
			Ln = abs(On - Ln);
			pDEST = DEST;
			if(x > y)	DEST = CheckDirection(ax, 0);
			else		DEST = CheckDirection(0, ay); 
		}
	}
	else
	{
		num = 1;
		if(x) On = x/2; 
		else	On = y/2;
	}


	for(x = num; x < 2; x++)
	{
		switch(DEST)
		{
		case ON:
			{
				do
				{
					j -= 2; On -= 1;
					TileValue = m_pTile[i][j].m_bMove;
					if(TileValue)
					{
						if(j == pre->y || j == next->y) break;
//						if(m_Ghost && TileValue > 1) ;
						else if(m_pEndLink->x == i && m_pEndLink->y == j && m_Object) ;
						else { m_BlockTileX = i; m_BlockTileY = j; BlockTile = TRUE; break; }
					}
				} while(On > 0);
			}
			break;
		case OE:
			{
				do
				{
					i += 2; On -= 1;
					TileValue = m_pTile[i][j].m_bMove;
					if(TileValue)
					{
						if(i == pre->x || i == next->x) break;
//						if(m_Ghost && TileValue > 1) ;
						else if(m_pEndLink->x == i && m_pEndLink->y == j && m_Object) ;
						else { m_BlockTileX = i; m_BlockTileY = j; BlockTile = TRUE; break; }
					}
				} while(On > 0);
			}
			break;
		case OS:
			{
				do
				{
					j += 2; On -= 1;
					TileValue = m_pTile[i][j].m_bMove;
					if(TileValue)
					{
						if((j == pre->y || j == next->y)) break;
//						if(m_Ghost && TileValue > 1) ;
						else if(m_pEndLink->x == i && m_pEndLink->y == j && m_Object) ;
						else { m_BlockTileX = i; m_BlockTileY = j; BlockTile = TRUE; break; }
					}
				} while(On > 0);
			}
			break;
		case OW:
			{
				do
				{
					i -= 2; On -= 1;
					TileValue = m_pTile[i][j].m_bMove;
					if(TileValue)
					{
						if(i == pre->x || i == next->x) break;
//						if(m_Ghost && TileValue > 1) ;
						else if(m_pEndLink->x == i && m_pEndLink->y == j && m_Object) ;
						else { m_BlockTileX = i; m_BlockTileY = j; BlockTile = TRUE; break; }
					}
				} while(On > 0);
			}
			break;
		case NE:
			{
				do
				{
					i += 1;	j -= 1; Ln -= 1;
					TileValue = m_pTile[i][j].m_bMove;
					if(TileValue)
					{
						if((i ==pre->x && j == pre->y)||(i == next->x && j == next->y)) break;
//						if(m_Ghost && TileValue > 1) ;
						else if(m_pEndLink->x == i && m_pEndLink->y == j && m_Object) ;
						else { m_BlockTileX = i; m_BlockTileY = j; BlockTile = TRUE; break; }
					}
				} while(Ln > 0);
			}
			break;
		case ES:
			{
				do
				{
					i += 1; j += 1; Ln -= 1;
					TileValue = m_pTile[i][j].m_bMove;
					if(TileValue)
					{
						if((i ==pre->x && j == pre->y)||(i == next->x && j == next->y)) break;
//						if(m_Ghost && TileValue > 1) ;
						else if(m_pEndLink->x == i && m_pEndLink->y == j && m_Object) ;
						else { m_BlockTileX = i; m_BlockTileY = j; BlockTile = TRUE; break; }
					}
				} while(Ln > 0);
			}
			break;
		case SW:
			{
				do
				{
					i -= 1; j += 1;Ln -= 1;
					TileValue = m_pTile[i][j].m_bMove;
					if(TileValue)
					{
						if((i ==pre->x && j == pre->y)||(i == next->x && j == next->y)) break;
//						if(m_Ghost && TileValue > 1) ;
						else if(m_pEndLink->x == i && m_pEndLink->y == j && m_Object) ;
						else { m_BlockTileX = i; m_BlockTileY = j; BlockTile = TRUE; break; }
					}
				} while(Ln > 0);
			}
			break;
		case WN:
			{
				do
				{
					i -= 1; j -= 1;Ln -= 1;
					TileValue = m_pTile[i][j].m_bMove;
					if(TileValue)
					{
						if((i ==pre->x && j == pre->y)||(i == next->x && j == next->y)) break;
//						if(m_Ghost && TileValue > 1) ;
						else if(m_pEndLink->x == i && m_pEndLink->y == j && m_Object) ;
						else { m_BlockTileX = i; m_BlockTileY = j; BlockTile = TRUE; break; }
					}
				} while(Ln > 0);
			}
			break;
		}
		if(DEST > 4 || BlockTile) break;
		else { DEST = pDEST; }
	}
	return BlockTile;
}


//------------------------------------------------------------------------
//	Name :	PathList(POS *pstr, POS *pend)
//	Desc :	필요없는 노드를 제거한다.
//	UpDate:	2000, 9, 18
//------------------------------------------------------------------------
void CPath::PathList(POS *pstr, POS *pend)
{
	POS *now = pstr;
	POS *end = pend;

	if(pstr != pend)
	{
		do
		{
			do
			{
				if( !SearchBlock(now, end) && (now != end->prev) )
				{
					DeleteNode(now, end);
					break;
				}
				else
				{
					if(end->prev == now || (end == now)) break;
					end = end->prev;
				}

			} while(1);
			
			now = now->next;
			end = pend;
			if(now->next == end || (end == now)) break;

		} while(1);

		if(SearchBlock(pstr, pend) && pstr->next == pend) { m_PathList[0].x = pstr->x; m_PathList[0].y = pstr->y; }
		else PutDistance();
	}
	else { m_PathList[0].x = pstr->x; m_PathList[0].y = pstr->y; }
}

void CPath::PutDistance()
{
	PATH PathList[100];
	POS *str = m_pStrLink;
	POS *end = m_pStrLink->next;

	BOOL nObj = FALSE;
	int x, y, a, b;
	int num = 0;
	m_PathListNum = 0;
	m_PathList[m_PathListNum].x = m_pStrLink->x;
	m_PathList[m_PathListNum].y = m_pStrLink->y;
	m_PathListNum++;

	do
	{
		if(m_pEndLink->x == end->x && m_pEndLink->y == end->y && m_Object) nObj = TRUE;
		if(IsBlock(str, end))
		{
			x = str->x - end->x; y =str->y - end->y;
			a = abs(x); b = abs(y);
			if(a > b) num = PutXPath(PathList, end->x, end->y, x, y);
			else	  num = PutYPath(PathList, end->x, end->y, x, y);
			
			do
			{
				m_PathList[m_PathListNum].x = PathList[num].x;
				m_PathList[m_PathListNum].y = PathList[num].y;
				m_PathListNum++; num--;
			} while(num > -1);
			
		}
		else
		{

			x = end->x - str->x; y =end->y - str->y;
			a = abs(x); b = abs(y);
			if(a > b) PutXPath(str, x, y);
			else	  PutYPath(str, x, y);
		}

		str = str->next;
		end = end->next;
		if(end == NULL) break;
	} while(1);
}

int CPath::PutXPath(PATH *PathList, int x, int y, int ax, int ay)
{
	int PathListNum = 0;
	int index = CheckDirection(ax, ay);
	int i = 0;
	int j = 0;
	int test = abs(ay);
	int sum = abs(ax);
	int loop = (sum + test)/2;
	int Ln = abs(test - sum)/2;

	switch(index)
	{
		case OE:
			do
			{
				PathList[PathListNum].x = x + i;
				PathList[PathListNum].y = y;
				i += 2;
				sum -= 1;
				PathListNum++;
			}while(sum > 0);
			break;
		
		case OW:
			do
			{
				PathList[PathListNum].x = x + i;
				PathList[PathListNum].y = y;
				i -= 2;
				sum -= 1;
				PathListNum++;
			}while(sum > 0);
			break;

		case ON:
			do
			{
				PathList[PathListNum].x = x;
				PathList[PathListNum].y = y + j;
				j -= 2;
				test -= 1;
				PathListNum++;
			}while(test > 0);
			break;

		case OS:
			do
			{
				PathList[PathListNum].x = x;
				PathList[PathListNum].y = y + j;					
				j += 2;
				test -= 1;
				PathListNum++;
			}while(test > 0);
			break;


		case ES:
			do
			{
				PathList[PathListNum].x = x + i;
				PathList[PathListNum].y = y + j;
				if(Ln > 0) { j; i += 2; }
				else  { j++; i++; }
				Ln--;
				loop--;
				PathListNum++;
			}while(loop > 0);
			break;

		case WN:
			do
			{
				PathList[PathListNum].x = x + i;
				PathList[PathListNum].y = y + j;
				if(Ln > 0) { j; i -= 2; }
				else { j--; i--; }
				Ln--;
				loop--;
				PathListNum++;
			}while(loop > 0);
			break;


		case SW:
			do
			{
				PathList[PathListNum].x = x + i;
				PathList[PathListNum].y = y + j;
				if(Ln > 0) { j; i -= 2; }
				else  { j++; i--; }
				Ln--;
				loop--;
				PathListNum++;
			}while(loop > 0);
			break;

		case NE:
			do
			{
				PathList[PathListNum].x = x + i;
				PathList[PathListNum].y = y + j;
				if(Ln > 0) { j; i += 2; }
				else { j--; i++; }
				Ln--;
				loop--;
				PathListNum++;
			}while(loop > 0);
			break;
	}
	return PathListNum-1;
}


int CPath::PutYPath(PATH *PathList, int x, int y, int ax, int ay)
{
	int PathListNum = 0;
	int index = CheckDirection(ax, ay);
	int i = 0;
	int j = 0;
	int test = abs(ax);
	int sum = abs(ay);
	int loop = (sum + test)/2;
	int Ln = abs(test - sum)/2;

	switch(index)
	{
		case OE:
			do
			{
				PathList[PathListNum].x = x + i;
				PathList[PathListNum].y = y;
				i += 2;
				test -= 1;
				PathListNum++;
			}while(test > 0);
			break;
		
		case OW:
			do
			{
				PathList[PathListNum].x = x + i;
				PathList[PathListNum].y = y;
				i -= 2;
				test -= 1;
				PathListNum++;
			}while(test > 0);
			break;

		case ON:
			do
			{
				PathList[PathListNum].x = x;
				PathList[PathListNum].y = y + j;
				j -= 2;
				sum -= 1;
				PathListNum++;
			}while(sum > 0);
			break;

		case OS:
			do
			{
				PathList[PathListNum].x = x;
				PathList[PathListNum].y = y + j;
				j += 2;
				sum -= 1;
				PathListNum++;
			}while(sum > 0);
			break;


		case ES:
			do
			{
				PathList[PathListNum].x = x + i;
				PathList[PathListNum].y = y + j;
				if(Ln > 0) { i; j += 2; }
				else  { i++; j++; }
				Ln--; loop--;
				PathListNum++;
			}while(loop > 0);
			break;

		case WN:
			do
			{
				PathList[PathListNum].x = x + i;
				PathList[PathListNum].y = y + j;
				if(Ln > 0) { i; j -= 2; }
				else  { i--; j--; }
				Ln--;	loop--;
				PathListNum++;
			}while(loop > 0);
			break;


		case SW:
			do
			{
				PathList[PathListNum].x = x + i;
				PathList[PathListNum].y = y + j;
				if(Ln > 0) { i; j += 2; }
				else { i--; j++; }
				Ln--; loop--;
				PathListNum++;
			}while(loop > 0);
			break;

		case NE:
			do
			{
				PathList[PathListNum].x = x + i;
				PathList[PathListNum].y = y + j;
				if(Ln > 0) { i; j -= 2; }
				else { i++;j--; }
				Ln--;
				loop--;
				PathListNum++;
			}while(loop > 0);
			break;
	}
	return PathListNum-1;
}

void CPath::PutXPath(POS *str, int x, int y)
{
	int index = CheckDirection(x, y);
	int i = 0;
	int j = 0;
	int test = abs(y);
	int sum = abs(x);
	int loop = (test + sum)/2;
	int Ln = abs(test - sum)/2;

	switch(index)
	{
		case OE:
			do
			{
				i += 2;
				sum -= 2;
				m_PathList[m_PathListNum].x = str->x + i;
				m_PathList[m_PathListNum].y = str->y;
				m_PathListNum++;
			}while(sum > 0);
			break;
		
		case OW:
			do
			{
				i -= 2;
				sum -= 2;
				m_PathList[m_PathListNum].x = str->x + i;
				m_PathList[m_PathListNum].y = str->y;
				m_PathListNum++;
			}while(sum > 0);
			break;

		case ON:
			do
			{
				j -= 2;
				test -= 2;
				m_PathList[m_PathListNum].x = str->x;
				m_PathList[m_PathListNum].y = str->y + j;
				m_PathListNum++;
			}while(test > 0);
			break;

		case OS:
			do
			{
				j += 2;
				test -= 2;
				m_PathList[m_PathListNum].x = str->x;
				m_PathList[m_PathListNum].y = str->y + j;					
				m_PathListNum++;
			}while(test > 0);
			break;


		case ES:
			do
			{
				if(Ln > 0) { j; i += 2; }
				else  { j++; i++; }
				Ln -= 1;
				loop--;
				m_PathList[m_PathListNum].x = str->x + i;
				m_PathList[m_PathListNum].y = str->y + j;
				m_PathListNum++;
			}while(loop > 0);
			break;

		case WN:
			do
			{
				if(Ln > 0) { j; i -= 2; }
				else  { j--; i--; }
				Ln -= 1;
				loop -= 1;
				m_PathList[m_PathListNum].x = str->x + i;
				m_PathList[m_PathListNum].y = str->y + j;
				m_PathListNum++;
			}while(loop > 0);
			break;


		case SW:
			do
			{
				if(Ln > 0) { j; i -= 2; }
				else  { j++; i--; }
				Ln -= 1;
				loop -= 1;
				m_PathList[m_PathListNum].x = str->x + i;
				m_PathList[m_PathListNum].y = str->y + j;
				m_PathListNum++;
			}while(loop > 0);
			break;

		case NE:
			do
			{
				if(Ln > 0) { j; i += 2; }
				else  { j--; i++; }
				Ln -= 1;
				loop -= 1;
				m_PathList[m_PathListNum].x = str->x + i;
				m_PathList[m_PathListNum].y = str->y + j;
				m_PathListNum++;
			}while(loop > 0);
			break;
	}
}


void CPath::PutYPath(POS *str, int x, int y)
{
	int index = CheckDirection(x, y);
	int i = 0;
	int j = 0;
	int test = abs(x);
	int sum = abs(y);
	int loop = (sum + test)/2;
	int Ln = abs(test - sum)/2;

	switch(index)
	{
		case OE:
			do
			{
				i += 2;
				test -= 2;
				m_PathList[m_PathListNum].x = str->x + i;
				m_PathList[m_PathListNum].y = str->y;
				m_PathListNum++;
			}while(test > 0);
			break;
		
		case OW:
			do
			{
				i -= 2;
				test -= 2;
				m_PathList[m_PathListNum].x = str->x + i;
				m_PathList[m_PathListNum].y = str->y;
				m_PathListNum++;
			}while(test > 0);
			break;

		case ON:
			do
			{
				j -= 2;
				sum -= 2;
				m_PathList[m_PathListNum].x = str->x;
				m_PathList[m_PathListNum].y = str->y + j;
				m_PathListNum++;
			}while(sum > 0);
			break;

		case OS:
			do
			{
				j += 2;
				sum -= 2;
				m_PathList[m_PathListNum].x = str->x;
				m_PathList[m_PathListNum].y = str->y + j;
				m_PathListNum++;
			}while(sum > 0);
			break;


		case ES:
			do
			{
				if(Ln > 0) { i; j += 2; }
				else  { i++; j++; }
				Ln -= 1;
				loop--;
				m_PathList[m_PathListNum].x = str->x + i;
				m_PathList[m_PathListNum].y = str->y + j;
				m_PathListNum++;
			}while(loop > 0);
			break;

		case WN:
			do
			{
				if(Ln > 0)  { i; j -= 2; }
				else  { i--; j--; }
				Ln -= 1;
				loop--;
				m_PathList[m_PathListNum].x = str->x + i;
				m_PathList[m_PathListNum].y = str->y + j;
				m_PathListNum++;
			}while(loop > 0);
			break;


		case SW:
			do
			{
				if(Ln > 0) { i; j += 2; }
				else  { i--; j++; }
				Ln -= 1;
				loop--;
				m_PathList[m_PathListNum].x = str->x + i;
				m_PathList[m_PathListNum].y = str->y + j;
				m_PathListNum++;
			}while(loop > 0);
			break;

		case NE:
			do
			{
				if(Ln > 0) { i; j -= 2; }
				else  { i++; j--; } 
				Ln -= 1;
				loop--;
				m_PathList[m_PathListNum].x = str->x + i;
				m_PathList[m_PathListNum].y = str->y + j;
				m_PathListNum++;
			}while(loop > 0);
			break;
	}
}


int CPath::Push(int num)
{
	m_StackNum++;

	if(m_StackNum > 8) return 0;

	m_Stack[m_StackNum] = num;

	return 1;
}

int CPath::Pop()
{
	if(m_StackNum < 0) return 0;
	else return m_Stack[m_StackNum--];
}

void CPath::QSort(PATH dist[], int n)
{
	int i, j;
	PATH key[1];
	PATH temp[1];
	int left = 0, right = n-1;

	Push(left);
	Push(right);

	while(m_StackNum >= 0)
	{
		right = Pop();
		left = Pop();

		if(right - left > 0)
		{
			key[0].dist = dist[left].dist; key[0].x = dist[left].x; key[0].y = dist[left].y;
			i = left;
			j = right+1;

			while(1)
			{
				while(dist[++i].dist < key[0].dist) { if(i >8) break; }
				while(dist[--j].dist > key[0].dist)
					;
				if(i >= j) break;

				temp[0].x = dist[i].x; temp[0].y = dist[i].y; temp[0].dist = dist[i].dist;
				dist[i].x = dist[j].x; dist[i].y = dist[j].y; dist[i].dist = dist[j].dist;
				dist[j].x = temp[0].x; dist[j].y = temp[0].y; dist[j].dist = temp[0].dist;
			}

			dist[left].x = dist[j].x; dist[left].y = dist[j].y; dist[left].dist = dist[j].dist;
			dist[j].dist = key[0].dist; dist[j].x = key[0].x; dist[j].y = key[0].y;

			Push(left);
			Push(j-1);
			Push(j+1);
			Push(right);
		}
	}
}

BOOL CPath::IsMovable(int x, int y)
// m_pMap 0 : 움직일수 있다. 1: 움직일수 없다.
{
	if(x < 0 || y < 0 || x >= m_nSizeX || y >= m_nSizeY) return FALSE;

	return (BOOL)!m_pTile[x][y].m_bMove;
}


void CPath::IsGhost(BOOL isDead)
{
	m_Ghost = isDead;
}

void CPath::InitNodePool()
{
	if(m_NodePool == NULL) return;
	_ASSERT(m_NodePool != NULL);

	for(int i = 0; i < MAX_NODE; i++)
	{
		m_NodePool[i].x 	  = 0;
		m_NodePool[i].y 	  = 0;
		m_NodePool[i].nFlag = FALSE;
		m_NodePool[i].Type  = -1;
		m_NodePool[i].next  = NULL;
		m_NodePool[i].prev  = NULL;
	}	
}

void CPath::DeleteNodePool()
{
	if(m_NodePool) delete []m_NodePool;
}

CPath::POS* CPath::GetNodePool()
{
	if(m_NodePool == NULL) return NULL;

	for(int i = 0; i < MAX_NODE; i++)
	{
		if(!m_NodePool[i].nFlag) 
		{
			m_NodePool[i].nFlag = TRUE;
			return &m_NodePool[i];	
		}
	}
	return NULL;
}

BOOL CPath::FreeNodePool(POS *Node)
{
	if(Node == NULL) FALSE;
	Node->x     = 0;
	Node->y     = 0;
	Node->nFlag = FALSE;
	Node->Type  = -1;
	Node->next  = NULL;
	Node->prev  = NULL;
	return TRUE;
}
