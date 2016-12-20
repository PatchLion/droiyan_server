// MAP.h: interface for the MAP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAP_H__9D08629D_3A60_11D3_BE0B_00105A6AE68D__INCLUDED_)
#define AFX_MAP_H__9D08629D_3A60_11D3_BE0B_00105A6AE68D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class	ItemList
{
public:
	short	uid[ITEM_USER_RIGHT_NUM];// 우선 순위 3명
	BYTE	SuccessRate[ITEM_USER_RIGHT_NUM];// 우선 순위 3명
	DWORD	dwTime;
//	SYSTEMTIME  ThrowTime;

public:
	BYTE	tType;			// 아이템(1)인지 돈(0)인지 구분
	short	sLevel;			// 매직속성이 붙으면 레벨이 변화한다.(2001_07_13)	
	short	sSid;
	short	sDuration;
	short	sBullNum;
	short	sCount;
	BYTE	tMagic[11];
	BYTE	tIQ;

	DWORD	dwMoney;		// 돈이면... 

	__int64 iItemSerial;	// 아이템 고유번호

	ItemList()
	{
		dwTime = 0;
		uid[0] = uid[1] = uid[2] = -1;
		SuccessRate[0] = SuccessRate[1] = SuccessRate[2] = 0;
	};
};

class BodyInfo				// 시체 처리 Class
{
public:
	int			iId;		// 시체가 가지고 있던 번호
	char		cName[CHAR_NAME_LENGTH+1];	// 시체의 이름
	DWORD		dTime;		// 시체가 된 시간
};

typedef CTypedPtrArray <CPtrArray, ItemList*> ItemInfoArray;

typedef CTypedPtrArray <CPtrArray, int*> ZoneUserArray;
typedef CTypedPtrArray <CPtrArray, BodyInfo*> BodyArray;

class MapInfo					// 각 좌표의 정보
{
public:
	LONG	m_bMove;			// 이동속성(0 : 이동가능, ELSE : 이동불가)  
	LONG	m_lUser;			// 유저정보								
	short	m_sEvent;			// 현좌표의 이벤트 번호
	WORD	m_dwType;			// 도시와 필드 구분


	DWORD			m_FieldDN;	// 맵에 쌓이는 돈								삭제
	ItemInfoArray	m_Item;		// 맵에 쌓이는 아이템 리스트					삭제

	ItemList		*m_pItem;
	int				iIndex;		// 아이템 배열 인덱스
	LONG			m_FieldUse;	// 현재 맵에 아이템을 버리는 중 (1)	
								// 아니면 (0)
	MapInfo();
	virtual ~MapInfo();
};

class MoveCell
{
public:
	void ConvertMapFromATM(MapInfo **tmap);
	void LoadSubInfo(CArchive &ar);
	MoveCell();
	~MoveCell();

	void RemoveData();
	void Initialize(int cx, int cy);
	void ConvertMap(MapInfo **tmap);

	void Load(CArchive& ar);
	void LoadSize(CArchive &ar);

	CSize	m_vDim;				// Cell들의 크기
	int		**m_pMoveInfo;		// 각 Cell들의 정보
};

class MAP  
{
public:
	void SetType(int x, int y, int nType);
	void LoadSubInfo(CArchive &ar);
	BOOL LoadAtm(char *szFileName);
	void Load(CArchive& ar);
	void InitTargetMap(int cx, int cy);		// 맵 Size Initialize
	BOOL LoadImf(char *szFileName);
	BOOL LoadImfSize(char* szFileName);
	BOOL LoadMapByNum(int num);				// 번호에 따른 맵 Load
	BOOL LoadMapSizeByNum(int num);
/*

	void Load(CArchive& ar);
	void InitTargetMap(int cx, int cy);		// 맵 Size Initialize
	BOOL LoadImf(char *szFileName);
	BOOL LoadMapByNum(int num);				// 번호에 따른 맵 Load
*/
	MoveCell		m_vMoveCell;			// IMF에서 맵을 읽기 담당

	CSize			m_sizeMap;				// 맵의 크기
	MapInfo			**m_pMap;
	int				m_Zone;					// 맵이 맡고 있는 존 번호

	ZoneUserArray	m_ZoneUserArray;

	MAP();
	virtual ~MAP();

protected:
	void RemoveMapData();
};

#endif // !defined(AFX_MAP_H__9D08629D_3A60_11D3_BE0B_00105A6AE68D__INCLUDED_)
