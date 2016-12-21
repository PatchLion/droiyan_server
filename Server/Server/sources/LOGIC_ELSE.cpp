// LOGIC_ELSE.cpp: implementation of the LOGIC_ELSE class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LOGIC_ELSE.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LOGIC_ELSE::LOGIC_ELSE()
{

}

LOGIC_ELSE::~LOGIC_ELSE()
{

}

void LOGIC_ELSE::Init()
{
	for( int i = 0; i < MAX_LOGIC_ELSE_INT; i++)
	{
		m_LogicElseInt[i] = -1;
	}

	m_LogicElseChar[0] = 0;

	m_bAnd = TRUE;
}

void LOGIC_ELSE::Parse_and(char *pBuf)
{
	int index = 0, i = 0;
	char temp[1024];

	index += ParseSpace( temp, pBuf+index );

	if( !strcmp( temp, "LEVEL" ) )
	{
		m_LogicElse = LOGIC_LEVEL;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "EXIST_ITEM" ) )
	{
		m_LogicElse = LOGIC_EXIST_ITEM;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "EXIST_EVENT_ITEM" ) )
	{
		m_LogicElse = LOGIC_EXIST_EVENT_ITEM;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "ABSENT_ITEM" ) )
	{
		m_LogicElse = LOGIC_ABSENT_ITEM;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "EXIST_EVENT" ) )
	{
		m_LogicElse = LOGIC_EXIST_EVENT;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "ABSENT_EVENT" ) )
	{
		m_LogicElse = LOGIC_ABSENT_EVENT;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CLASS" ) )
	{
		m_LogicElse = LOGIC_CLASS;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "WEIGHT" ) )
	{
		m_LogicElse = LOGIC_WEIGHT;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// SAY
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// Item uid
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// No
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// Item uid	
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// No
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// Item uid
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHECK_ITEMSLOT" ) )
	{
		m_LogicElse = LOGIC_CHECK_ITEMSLOT;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// SAY
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// Item uid
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// No
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// Item uid	
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// No
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// Item uid
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "EXIST_GM" ) )
	{
		m_LogicElse = LOGIC_EXIST_GM;
	}
	else if( !strcmp( temp, "OVER_GUILD_USER_COUNT" ) )
	{
		m_LogicElse = LOGIC_OVER_GUILD_USER_COUNT;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// guild user count
	}
	else if( !strcmp( temp, "ZONE_WHO" ) )
	{
		m_LogicElse = LOGIC_ZONE_WHO;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// 해당 존
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// 0 : 사람없음면 통과
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// 이벤트 존 포인터 접근 타입(이벤트 마다 구조가 달라서 ..)
	}
	else if( !strcmp( temp, "KILL_GH" ) )
	{
		m_LogicElse = LOGIC_KILL_GH;
	}
	else if( !strcmp( temp, "MASS_ZONE_MOVE" ) )
	{
		m_LogicElse = LOGIC_MASS_ZONE_MOVE;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// 해당 존
	}
	else if( !strcmp( temp, "TERM" ) )
	{
		m_LogicElse = LOGIC_TERM;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// 시작날짜
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// 끝나는 날짜
	}
	else if( !strcmp( temp, "GUILD_HOUSE_NUMBER" ) )
	{
		m_LogicElse = LOGIC_GUILD_HOUSE_NUMBER;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// 해당 길드하우스 번호
	}
	else if( !strcmp( temp, "CHECK_CV" ) )
	{
		m_LogicElse = LOGIC_CHECK_CV;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// Min City Value
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// Max City Value
	}
	else if( !strcmp( temp, "MONEY" ) )
	{
		m_LogicElse = LOGIC_MONEY;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp ); // min
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp ); // max
	}
	else if( !strcmp( temp, "RAND" ) )
	{
		m_LogicElse = LOGIC_RAND;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "RR_TIME" ) )
	{
		m_LogicElse = LOGIC_RR_TIME;
	}
	else if( !strcmp( temp, "RR_MAX_USER" ) )
	{
		m_LogicElse = LOGIC_RR_MAX_USER;
	}else if( !strcmp( temp, "EXIST_SKILL" ) )
	{
		m_LogicElse = LOGIC_EXIST_SKILL;
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}

/*	else if( !strcmp( temp, "GENDER" ) )
	{
		m_LogicElse = LOGIC_GENDER;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "DN" ) )
	{
		m_LogicElse = LOGIC_DN;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "HP" ) )
	{
		m_LogicElse = LOGIC_HP;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "MP" ) )
	{
		m_LogicElse = LOGIC_MP;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "STR" ) )
	{
		m_LogicElse = LOGIC_STR;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "DEX" ) )
	{
		m_LogicElse = LOGIC_DEX;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "INT" ) )
	{
		m_LogicElse = LOGIC_INT;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "WISDOM" ) )
	{
		m_LogicElse = LOGIC_WISDOM;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHARM" ) )
	{
		m_LogicElse = LOGIC_CHARM;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CON" ) )
	{
		m_LogicElse = LOGIC_CON;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "DMAIGC" ) )
	{
		m_LogicElse = LOGIC_DMAGIC;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "WMAGIC" ) )
	{
		m_LogicElse = LOGIC_WMAGIC;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "BMAGIC" ) )
	{
		m_LogicElse = LOGIC_BMAGIC;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "SWORD" ) )
	{
		m_LogicElse = LOGIC_SWORD;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "SPEAR" ) )
	{
		m_LogicElse = LOGIC_SPEAR;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "AXE" ) )
	{
		m_LogicElse = LOGIC_AXE;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "BOW" ) )
	{
		m_LogicElse = LOGIC_BOW;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "KNUCKLE" ) )
	{
		m_LogicElse = LOGIC_KNUCKLE;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "WEAPONMAKE" ) )
	{
		m_LogicElse = LOGIC_WEAPONMAKE;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "ARMORMAKE" ) )
	{
		m_LogicElse = LOGIC_ARMORMAKE;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "ACCMAKE" ) )
	{
		m_LogicElse = LOGIC_ACCMAKE;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "POTIONMAKE" ) )
	{
		m_LogicElse = LOGIC_POTIONMAKE;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "COOKING" ) )
	{
		m_LogicElse = LOGIC_COOKING;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "EXIST_ITEM_TYPE" ) )
	{
		m_LogicElse = LOGIC_EXIST_ITEM_TYPE;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "ABSENT_ITEM_TYPE" ) )
	{
		m_LogicElse = LOGIC_ABSENT_ITEM_TYPE;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "EXIST_MAGIC" ) )
	{
		m_LogicElse = LOGIC_EXIST_MAGIC;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "ABSENT_MAGIC" ) )
	{
		m_LogicElse = LOGIC_ABSENT_MAGIC;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "TIME" ) )
	{
		m_LogicElse = LOGIC_TIME;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "RAND" ) )
	{
		m_LogicElse = LOGIC_RAND;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
*/
	m_bAnd = TRUE;
}

void LOGIC_ELSE::Parse_or(char *pBuf)
{
	int index = 0, i = 0;
	char temp[1024];

	index += ParseSpace( temp, pBuf+index );

	if( !strcmp( temp, "LEVEL" ) )
	{
		m_LogicElse = LOGIC_LEVEL;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "EXIST_ITEM" ) )
	{
		m_LogicElse = LOGIC_EXIST_ITEM;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "EXIST_EVENT_ITEM" ) )
	{
		m_LogicElse = LOGIC_EXIST_EVENT_ITEM;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "ABSENT_ITEM" ) )
	{
		m_LogicElse = LOGIC_ABSENT_ITEM;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "EXIST_EVENT" ) )
	{
		m_LogicElse = LOGIC_EXIST_EVENT;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "ABSENT_EVENT" ) )
	{
		m_LogicElse = LOGIC_ABSENT_EVENT;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "WEIGHT" ) )
	{
		m_LogicElse = LOGIC_WEIGHT;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// SAY
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// Item uid
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// No
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// Item uid	
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// No
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// Item uid
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHECK_ITEMSLOT" ) )
	{
		m_LogicElse = LOGIC_CHECK_ITEMSLOT;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// SAY
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// Item uid
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// No
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// Item uid	
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// No
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );	// Item uid
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "MONEY" ) )
	{
		m_LogicElse = LOGIC_MONEY;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp ); // min
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp ); // max
	}
	else if( !strcmp( temp, "RAND" ) )
	{
		m_LogicElse = LOGIC_RAND;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "RR_TIME" ) )
	{
		m_LogicElse = LOGIC_RR_TIME;
	}
	else if( !strcmp( temp, "EXIST_SKILL" ) )
	{
		m_LogicElse = LOGIC_EXIST_SKILL;
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}

/*	else if( !strcmp( temp, "GENDER" ) )
	{
		m_LogicElse = LOGIC_GENDER;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "DN" ) )
	{
		m_LogicElse = LOGIC_DN;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "HP" ) )
	{
		m_LogicElse = LOGIC_HP;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "MP" ) )
	{
		m_LogicElse = LOGIC_MP;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "STR" ) )
	{
		m_LogicElse = LOGIC_STR;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "DEX" ) )
	{
		m_LogicElse = LOGIC_DEX;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "INT" ) )
	{
		m_LogicElse = LOGIC_INT;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "WISDOM" ) )
	{
		m_LogicElse = LOGIC_WISDOM;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHARM" ) )
	{
		m_LogicElse = LOGIC_CHARM;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CON" ) )
	{
		m_LogicElse = LOGIC_CON;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "DMAIGC" ) )
	{
		m_LogicElse = LOGIC_DMAGIC;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "WMAGIC" ) )
	{
		m_LogicElse = LOGIC_WMAGIC;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "BMAGIC" ) )
	{
		m_LogicElse = LOGIC_BMAGIC;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "SWORD" ) )
	{
		m_LogicElse = LOGIC_SWORD;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "SPEAR" ) )
	{
		m_LogicElse = LOGIC_SPEAR;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "AXE" ) )
	{
		m_LogicElse = LOGIC_AXE;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "BOW" ) )
	{
		m_LogicElse = LOGIC_BOW;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "KNUCKLE" ) )
	{
		m_LogicElse = LOGIC_KNUCKLE;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "WEAPONMAKE" ) )
	{
		m_LogicElse = LOGIC_WEAPONMAKE;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "ARMORMAKE" ) )
	{
		m_LogicElse = LOGIC_ARMORMAKE;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "ACCMAKE" ) )
	{
		m_LogicElse = LOGIC_ACCMAKE;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "POTIONMAKE" ) )
	{
		m_LogicElse = LOGIC_POTIONMAKE;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "COOKING" ) )
	{
		m_LogicElse = LOGIC_COOKING;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "EXIST_ITEM_TYPE" ) )
	{
		m_LogicElse = LOGIC_EXIST_ITEM_TYPE;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "ABSENT_ITEM_TYPE" ) )
	{
		m_LogicElse = LOGIC_ABSENT_ITEM_TYPE;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "EXIST_MAGIC" ) )
	{
		m_LogicElse = LOGIC_EXIST_MAGIC;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "ABSENT_MAGIC" ) )
	{
		m_LogicElse = LOGIC_ABSENT_MAGIC;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "TIME" ) )
	{
		m_LogicElse = LOGIC_TIME;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "RAND" ) )
	{
		m_LogicElse = LOGIC_RAND;

		index += ParseSpace( temp, pBuf+index );	m_LogicElseInt[i++] = atoi( temp );
	}
*/
	m_bAnd = FALSE;
}
