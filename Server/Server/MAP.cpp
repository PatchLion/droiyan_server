// MAP.cpp: implementation of the MAP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MAP.h"
//#include "MapSet.h"
//#include "Item.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MapInfo::MapInfo()
{
	m_bMove		= 0;
	m_lUser		= 0;
	m_sEvent	= -1;
}

MapInfo::~MapInfo()
{
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MoveCell::MoveCell()
{
	m_vDim.cx = 0;
	m_vDim.cy = 0;
	m_pMoveInfo = NULL;
}

MoveCell::~MoveCell()
{
	RemoveData();
}

void MoveCell::RemoveData()
{
	if(m_pMoveInfo)
	{
		for(int i = 0; i < m_vDim.cx; i++) 
		{
			delete[] m_pMoveInfo[i];
		}
		delete[] m_pMoveInfo;
		m_pMoveInfo = NULL;
	}
}

void MoveCell::Initialize(int cx, int cy)
{
	RemoveData();

	int x, y;

	m_vDim.cx = cx;
	m_vDim.cy = cy;

	m_pMoveInfo = new int *[m_vDim.cx];
	for(int i = 0; i < m_vDim.cx; i++) 
	{
		m_pMoveInfo[i] = new int[m_vDim.cy];
	}

	for(y = 0; y < m_vDim.cy-1; y++)
	{
		for(x = 0; x < m_vDim.cx-1; x++)
		{
			m_pMoveInfo[x][y] = 1;
		}
	}
}

void MoveCell::Load(CArchive& ar)
{
	BYTE BitMask[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

	int cx, cy, roll;
	BYTE *t_buf = NULL;
	CPoint cell_limit;
	int load_count, read_count, tmp_int;
	int x, y;

	ar >> cx >> cy;

	Initialize(cx, cy);

	cell_limit.x = (cx+1)/2;
	cell_limit.y = (cy+1)/2;
	tmp_int = cell_limit.x*cell_limit.y+(cell_limit.x-1)*(cell_limit.y-1);
	load_count = tmp_int / 8;
	if(tmp_int % 8) load_count++;
	t_buf = new BYTE[load_count];

	// 이동정보를 읽어온다.
	roll = 0;
	read_count = 0;
	ar.Read(t_buf, load_count);
	for(y = 0; y < m_vDim.cy-1; y++)
	{
		for(x = 0; x < m_vDim.cx-1; x++)
		{
			if((x+y)%2==0)
			{
				m_pMoveInfo[x][y] = !((t_buf[read_count] & BitMask[roll]) >> roll);
				roll++;
				if(roll == 8)
				{
					roll = 0;
					read_count++;
				}
			}
		}
	}

	if(t_buf) delete[] t_buf;
}

void MoveCell::LoadSize(CArchive &ar)
{
	int cx, cy;
	CPoint cell_limit;

	ar >> cx >> cy;

	// Initialize함수를 대신한다.
	RemoveData();

	m_vDim.cx = cx;
	m_vDim.cy = cy;
	//
}

void MoveCell::LoadSubInfo(CArchive &ar)
{
	WORD *t_buf;

	int cx, cy;
	int x, y;
	ar >> cx >> cy;

	
	// int nCount = m_vDim.cx*m_vDim.cy;
	int nCount = m_vDim.cx*(m_vDim.cy/2 + m_vDim.cy%2);


	for(y = 0; y < m_vDim.cy-1; y++)
	{
		for(x = 0; x < m_vDim.cx-1; x++)
		{
			m_pMoveInfo[x][y] = 0;
		}
	}

	if (nCount>0)
	{
		t_buf = new WORD[nCount];
		ar.Read((BYTE*)t_buf, sizeof(WORD)*nCount);

		int nOffset = 0;
		for (y=0; y<m_vDim.cy; y++) 
		{
			for (x=0; x<m_vDim.cx; x++) 
			{
				if ((x+y)%2==0) 
				{
					m_pMoveInfo[x][y] = t_buf[nOffset];
					nOffset++;
					ASSERT(nOffset<=nCount);
				}
			}
		}
		delete []t_buf;
	}	
}

void MoveCell::ConvertMapFromATM(MapInfo **tmap)
{
	int nType = 0;
	int tempx, tempy;
	int temph = m_vDim.cy / 2 - 1;

	for( int y = 0; y < m_vDim.cy - 1; y++)
	{
		for( int x = 0; x < m_vDim.cx - 1; x++)
		{
			if( (x+y)%2 == 0 )
			{
				tempx = temph - ( y / 2 ) + ( x / 2 );

				if( x % 2 ) tempy = ( y / 2 ) + ( ( x / 2 ) + 1 );
				else        tempy = ( y / 2 ) + ( x / 2 );

				nType = m_pMoveInfo[x][y];
				tmap[tempx][tempy].m_dwType = (tmap[tempx][tempy].m_dwType & 0x03) | (nType & 0xFFFC);
/*
				int nNum = (tmap[tempx][tempy].m_dwType&0xFF00)>>8;
				ASSERT(nNum>=0);
				ASSERT(nNum<8);
*/			}
		}
	}
}

void MoveCell::ConvertMap(MapInfo **tmap)
{
	int tempx, tempy;
	int temph = m_vDim.cy / 2 - 1;

	for( int y = 0; y < m_vDim.cy - 1; y++)
	{
		for( int x = 0; x < m_vDim.cx - 1; x++)
		{
			if( (x+y)%2 == 0 )
			{
				tempx = temph - ( y / 2 ) + ( x / 2 );

				if( x % 2 ) tempy = ( y / 2 ) + ( ( x / 2 ) + 1 );
				else        tempy = ( y / 2 ) + ( x / 2 );

				if(m_pMoveInfo[x][y] == 0 )
				{
					tmap[tempx][tempy].m_bMove = 0;
				}
				else
				{
					tmap[tempx][tempy].m_bMove = 1;
				}

				tmap[tempx][tempy].iIndex = -1;
				tmap[tempx][tempy].m_lUser = 0;
				tmap[tempx][tempy].m_FieldDN = 0;
				tmap[tempx][tempy].m_FieldUse = 0;
				tmap[tempx][tempy].m_dwType = 0;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MAP::MAP()
{
	m_Zone = 1;	// 맵이 맡게될 존의 번호
	m_pMap = NULL;
}

MAP::~MAP()
{
	RemoveMapData();	
}

void MAP::RemoveMapData()
{
	int i, j;

	if(m_pMap)
	{
		for(i = 0; i < m_sizeMap.cx; i++)
		{
			for(j = 0; j < m_pMap[i]->m_Item.GetSize(); j++)			// 맵에 쌓여 있는 아이템 정보를 삭제
			{
				if(m_pMap[i]->m_Item[j]) delete m_pMap[i]->m_Item[j];
			}
			m_pMap[i]->m_Item.RemoveAll();

			delete[] m_pMap[i];
		}

		delete[] m_pMap;
	}
}

///////////////////////////////////////////////////////////////////////
//	각 서버가 담당하고 있는 zone의 Map(.Imf 파일)을 로드한다.
//
BOOL MAP::LoadMapByNum(int num)
{
	char filename[128], mapfilename[128];
	wsprintf(filename, ".\\MAP\\DR_MAP%d.imf", num);
	wsprintf(mapfilename, ".\\MAP\\DR_MAP%d.atm", num);

	if(!LoadImf(filename)) return FALSE;

	if(!LoadAtm(mapfilename)) return FALSE;

	m_Zone = num;

	return TRUE;
}

BOOL MAP::LoadMapSizeByNum(int num)
{
	char filename[128], mapfilename[128];
	wsprintf(filename, ".\\MAP\\DR_MAP%d.imf", num);
	wsprintf(mapfilename, ".\\MAP\\DR_MAP%d.atm", num);

	if(!LoadImfSize(filename)) return FALSE;

	m_Zone = num;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
//	Atm 파일을 메모리로 로드한다.
//	Atm 파일는 SafeZone 정보를 가지고 있다.
//
BOOL MAP::LoadAtm(char *szFileName)
{
	CFile newfile;
	int		nVersionInfo;

	if(newfile.Open( szFileName, CFile::modeRead ) )
	{
		CArchive newar(&newfile, CArchive::load);
		newar >> nVersionInfo;
		m_vMoveCell.LoadSubInfo(newar);
		newar.Close();
		newfile.Close();

		m_vMoveCell.ConvertMapFromATM(m_pMap);
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
//	Imf 파일을 메모리로 로드한다.
//	Imf 파일는 Move, Hidden, Event 정보를 가지고 있다.
//
BOOL MAP::LoadImf(char *szFileName)
{
	CFile	newfile;
	int		nVersionInfo;

	if(newfile.Open( szFileName, CFile::modeRead ) )
	{
		CArchive newar(&newfile, CArchive::load);
		newar >> nVersionInfo;
		m_vMoveCell.Load(newar);
		newar.Close();
		newfile.Close();

		InitTargetMap( m_vMoveCell.m_vDim.cx, m_vMoveCell.m_vDim.cy );
		m_vMoveCell.ConvertMap( m_pMap );
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

BOOL MAP::LoadImfSize(char *szFileName)
{
	CFile	newfile;
	int		nVersionInfo;

	if(newfile.Open( szFileName, CFile::modeRead ) )
	{
		CArchive newar(&newfile, CArchive::load);
		newar >> nVersionInfo;
		m_vMoveCell.LoadSize(newar);
		newar.Close();
		newfile.Close();

//		InitTargetMap( m_vMoveCell.m_vDim.cx, m_vMoveCell.m_vDim.cy );
//		m_vMoveCell.ConvertMap( m_pMap );
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////
//	Imf 파일의 정보를 실제로 로드한다.
//
void MAP::Load(CArchive &ar)
{
	BYTE BitMask[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

	int cx, cy, roll;
	BYTE *t_buf;
	CPoint cell_limit;
	int load_count, read_count, tmp_int;
	int x, y, i;

	ar >> cx >> cy;

	InitTargetMap(cx, cy);

	cell_limit.x = (cx+1)/2;
	cell_limit.y = (cy+1)/2;
	tmp_int = cell_limit.x*cell_limit.y+(cell_limit.x-1)*(cell_limit.y-1);
	load_count = tmp_int / 8;
	if(tmp_int % 8) load_count++;
	t_buf = new BYTE[load_count];

	// 이동정보를 읽어온다.
	roll = 0;
	read_count = 0;
	ar.Read(t_buf, load_count);

	for(y = 0; y < m_sizeMap.cy - 1; y++)
	{
		for(x = 0; x < m_sizeMap.cx - 1; x++)
		{
			if((x+y)%2==0)
			{
				ASSERT(read_count < load_count);
				m_pMap[x][y].m_bMove = !((t_buf[read_count] & BitMask[roll]) >> roll);
				m_pMap[x][y].m_lUser = 0;
				m_pMap[x][y].m_FieldDN = 0;
				m_pMap[x][y].m_FieldUse = 0;
				m_pMap[x][y].m_dwType = 0;

				m_pMap[x][y].m_Item.RemoveAll();
				roll++;
				if(roll == 8)
				{
					roll = 0;
					read_count++;
				}
			}
		}
	}
	delete[] t_buf;

	// 이벤트정보를 읽어온다.
	short data_x, data_y, data_event;
	ar >> load_count;
	for(i = 0; i < load_count; i++)
	{
		ar >> data_x;
		ar >> data_y;
		ar >> data_event;
		m_pMap[data_x][data_y].m_sEvent = data_event;
	}
}

////////////////////////////////////////////////////////////////////////
//	Atm 파일의 정보를 실제로 로드한다.
//
void MAP::LoadSubInfo(CArchive &ar)
{
/*	WORD *t_buf;

	int cx, cy;
	ar >> cx >> cy;

	int nCount = m_vDim.cx*m_vDim.cy;
	if (nCount>0)
	{
		t_buf = new WORD[nCount];
		ar.Read((BYTE*)t_buf, sizeof(WORD)*nCount);

		int nOffset = 0;
		for (int y=0; y<m_sizeMap.cy; y++) 
		{
			for (int x=0; x<m_sizeMap.cx; x++) 
			{
				if ((x+y)%2==0) 
				{
					SetType(x, y, t_buf[nOffset]);

					nOffset++;
					ASSERT(nOffset<=nCount);
				}
			}
		}
		delete []t_buf;
	}	
/*	int nCount = m_sizeMap.cx*m_sizeMap.cy;
	if (nCount>0)
	{
		t_buf = new WORD[nCount];
		ar.Read((BYTE*)t_buf, sizeof(WORD)*nCount);

		int nOffset = 0;
		for (int y=0; y<m_sizeMap.cy; y++) 
		{
			for (int x=0; x<m_sizeMap.cx; x++) 
			{
				if ((x+y)%2==0) 
				{
					SetType(x, y, t_buf[nOffset]);

					nOffset++;
					ASSERT(nOffset<=nCount);
				}
			}
		}
		delete []t_buf;
	}
	*/
}

void MAP::InitTargetMap(int cx, int cy)
{
	int wh = (cx+1)/2 + (cy+1)/2 - 1,i;

	m_pMap			= new MapInfo*[wh];

	for( i = 0; i < wh; i++)
	{
		m_pMap[i] = new MapInfo[wh];
	}

	for( i = 0; i < wh; i++)
	{
		for( int j = 0; j < wh; j++)
		{
			m_pMap[j][i].m_bMove	= 1;
			m_pMap[j][i].m_lUser	= 0;
			// 부가적인 추가
			m_pMap[j][i].iIndex = -1;
			m_pMap[j][i].m_FieldUse = 0;
			m_pMap[j][i].m_dwType = 0;
		}
	}

	TRACE( "Size Of MapInfo - %d\n", sizeof( MapInfo ) );
	TRACE( "Size Of MAP - %d\n", sizeof( MapInfo ) * wh * wh );

	m_sizeMap.cx = m_sizeMap.cy = wh;

}



void MAP::SetType(int x, int y, int nType)
{
	if(x < 0 || x >= m_sizeMap.cx || y < 0 || y >= m_sizeMap.cy) return;

	if (nType) {
		int i=0;
		i++;
	}

	m_pMap[x][y].m_dwType = (m_pMap[x][y].m_dwType & 0x03) | (nType & 0xFFFC);
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
MAP::MAP()
{
	m_Zone = 1;	// 맵이 맡게될 존의 번호
	m_pMap = NULL;
}

MAP::~MAP()
{
	RemoveMapData();	
}

void MAP::RemoveMapData()
{
	int i, j;

	if(m_pMap)
	{
		for(i = 0; i < m_sizeMap.cx; i++)
		{
			for(j = 0; j < m_pMap[i]->m_Item.GetSize(); j++)			// 맵에 쌓여 있는 아이템 정보를 삭제
			{
				if(m_pMap[i]->m_Item[j]) delete m_pMap[i]->m_Item[j];
			}
			m_pMap[i]->m_Item.RemoveAll();

			delete[] m_pMap[i];
		}

		delete[] m_pMap;
	}
}

///////////////////////////////////////////////////////////////////////
//	각 서버가 담당하고 있는 zone의 Map(.Imf 파일)을 로드한다.
//
BOOL MAP::LoadMapByNum(int num)
{
	char filename[128];
	wsprintf(filename, ".\\MAP\\DR_MAP%d.imf", num);

	if(!LoadImf(filename)) return FALSE;

	m_Zone = num;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
//	Imf 파일을 메모리로 로드한다.
//	Imf 파일는 Move, Hidden, Event 정보를 가지고 있다.
//
BOOL MAP::LoadImf(char *szFileName)
{
	CFile	newfile;
	int		nVersionInfo;

	if(newfile.Open( szFileName, CFile::modeRead ) )
	{
		CArchive newar(&newfile, CArchive::load);
		newar >> nVersionInfo;
		m_vMoveCell.Load(newar);
		newar.Close();
		newfile.Close();

		InitTargetMap( m_vMoveCell.m_vDim.cx, m_vMoveCell.m_vDim.cy );
		m_vMoveCell.ConvertMap( m_pMap );
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////
//	Imf 파일의 정보를 실제로 로드한다.
//
void MAP::Load(CArchive &ar)
{
	BYTE BitMask[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

	int cx, cy, roll;
	BYTE *t_buf;
	CPoint cell_limit;
	int load_count, read_count, tmp_int;
	int x, y, i;

	ar >> cx >> cy;

	InitTargetMap(cx, cy);

	cell_limit.x = (cx+1)/2;
	cell_limit.y = (cy+1)/2;
	tmp_int = cell_limit.x*cell_limit.y+(cell_limit.x-1)*(cell_limit.y-1);
	load_count = tmp_int / 8;
	if(tmp_int % 8) load_count++;
	t_buf = new BYTE[load_count];

	// 이동정보를 읽어온다.
	roll = 0;
	read_count = 0;
	ar.Read(t_buf, load_count);

	for(y = 0; y < m_sizeMap.cy - 1; y++)
	{
		for(x = 0; x < m_sizeMap.cx - 1; x++)
		{
			if((x+y)%2==0)
			{
				ASSERT(read_count < load_count);
				m_pMap[x][y].m_bMove = !((t_buf[read_count] & BitMask[roll]) >> roll);
				m_pMap[x][y].m_lUser = 0;
				m_pMap[x][y].m_FieldDN = 0;
				m_pMap[x][y].m_FieldUse = 0;
				m_pMap[x][y].m_Item.RemoveAll();
				roll++;
				if(roll == 8)
				{
					roll = 0;
					read_count++;
				}
			}
		}
	}
	delete[] t_buf;

	// 이벤트정보를 읽어온다.
	short data_x, data_y, data_event;
	ar >> load_count;
	for(i = 0; i < load_count; i++)
	{
		ar >> data_x;
		ar >> data_y;
		ar >> data_event;
		m_pMap[data_x][data_y].m_sEvent = data_event;
	}
}

void MAP::InitTargetMap(int cx, int cy)
{
	int wh = (cx+1)/2 + (cy+1)/2 - 1;

	m_pMap			= new MapInfo*[wh];

	for( int i = 0; i < wh; i++)
	{
		m_pMap[i] = new MapInfo[wh];
	}

	for( i = 0; i < wh; i++)
	{
		for( int j = 0; j < wh; j++)
		{
			m_pMap[j][i].m_bMove	= 1;
			m_pMap[j][i].m_lUser	= 0;
		}
	}

	TRACE( "Size Of MapInfo - %d\n", sizeof( MapInfo ) );
	TRACE( "Size Of MAP - %d\n", sizeof( MapInfo ) * wh * wh );

	m_sizeMap.cx = m_sizeMap.cy = wh;

	/*
	m_pMap = new MapInfo* [cx];
	for(int i = 0; i < cx; i++) 
	{
		m_pMap[i] = new MapInfo[cy];
	}

	TRACE( "Size Of MapInfo - %d\n", sizeof( MapInfo ) );
	TRACE( "Size Of MAP - %d * %d \n", cx, cy);

	m_sizeMap.cx = cx;
	m_sizeMap.cy = cy;
	*/
//}


