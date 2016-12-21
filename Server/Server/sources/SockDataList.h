#ifndef _SOCKDATALIST_H
#define _SOCKDATALIST_H

#include "scdefine.h"
#include "Mcommon.h"

typedef unsigned char byte;

struct _byte16
{
	BYTE b1;
	BYTE b2;
};

typedef _byte16 BYTE16;

union _byte2_word
{
	short i;
	BYTE16 b;
};

typedef _byte2_word BYTE2WORD;


class CJSocket;
class WAIT_SEND_DATA : public CObject  
{
public:
	CJSocket *pSocket;
	int dcount;
	BYTE *pData;

public:
	WAIT_SEND_DATA()
	{
		pSocket = NULL;
		dcount = 0;
		pData = NULL;
	};

	~WAIT_SEND_DATA()
	{
		if (pData != NULL)
		{
			delete[] pData;
			pData = NULL;
		};
	};
};

class WAIT_RECV_DATA : public CObject  
{
public:
	CJSocket *pSocket;
	int usn;
	char Id[MAX_ID+1];
	int dcount;
	BYTE *pData;
	int m_Type;

public:
	WAIT_RECV_DATA()
	{
		pSocket = NULL;
		usn = -1;
		dcount = 0;
		pData = NULL;
		m_Type = -1;
	};

	~WAIT_RECV_DATA()
	{
		if (pData != NULL)
		{
			pSocket = NULL;
			delete[] pData;
			pData = NULL;
		};
	};
};

/*
struct _WAIT_RECV_DATA
{
public:
	CJSocket *pSocket;
	int usn;
	char Id[MAX_ID+1];
	int dcount;
	BYTE *pData;
	int m_Type;

public:
	_WAIT_RECV_DATA()
	{
		pSocket = NULL;
		usn = -1;
		dcount = 0;
		pData = NULL;
		m_Type = -1;
	};

	~_WAIT_RECV_DATA()
	{
		if (pData != NULL)
		{
			pSocket = NULL;
			delete[] pData;
			pData = NULL;
		};
	};
};
typedef _WAIT_RECV_DATA WAIT_RECV_DATA;
*/

class WAIT_ROOM_DATA : public CObject  
{
public:
	int roomNumber;
	int roomDataLength;
	int room_disp_r;
	int room_disp_b;
	char *pRoomData;

public:
	WAIT_ROOM_DATA()
	{
		roomNumber = -1;
		roomDataLength = 0;
		pRoomData = NULL;
	};

	~WAIT_ROOM_DATA()
	{
		if ( pRoomData != NULL )
		{
			delete[] pRoomData;
			pRoomData = NULL;
		}
	};
};

class WAIT_ROOM_STORE_DATA : public CObject  
{
public:
	int gameType;
	int roomNumber;
	int roomDataLength;
	int room_disp_r;
	int room_disp_b;
	char *pRoomData;

public:
	WAIT_ROOM_STORE_DATA()
	{
		roomNumber = -1;
		roomDataLength = 0;
		pRoomData = NULL;
	};

	~WAIT_ROOM_STORE_DATA()
	{
		if ( pRoomData != NULL )
		{
			delete[] pRoomData;
			pRoomData = NULL;
		}
	};
};

class WAIT_USER_DATA : public CObject  
{
public:
	char Id[MAX_ID+1];
	int userDispRange;
	int userDataLength;
	char *pUserData;

public:
	WAIT_USER_DATA()
	{
		Id[0] = '\0';
		userDataLength = 0;
		pUserData = NULL;
	};

	~WAIT_USER_DATA()
	{
		if ( pUserData != NULL )
		{
			delete[] pUserData;
			pUserData = NULL;
		}
	};
};

class WAIT_USER_STORE_DATA : public CObject  
{
public:
	char Id[MAX_ID+1];
	int userDispRange;
	int userDataLength;
	int flag;
	int gameType;
	char *pUserData;

public:
	WAIT_USER_STORE_DATA()
	{
		Id[0] = '\0';
		userDataLength = 0;
		pUserData = NULL;
	};

	~WAIT_USER_STORE_DATA()
	{
		if ( pUserData != NULL )
		{
			delete[] pUserData;
			pUserData = NULL;
		}
	};
};

class CConnMsg : public CObject
{
public:
	char *pData;
	int dLen;

public:
	CConnMsg()
	{
		pData = NULL;
		dLen = 0;
	};

	~CConnMsg()
	{
		if ( pData )
		{
			delete[] pData;
			pData = NULL;
		}

		dLen = 0;
	};

	void SetMsg( char *msg, int dl )
	{
		dLen = dl;
		pData = new char[dl+1];
		memcpy( pData, msg, dl );
	};
};

class GAME_INFO_DATA : public CObject
{
public:
	CBSocket *pSocket;
	char IpAddr[32];
	int iPort;
	int gsn;
	int Type;

public:
	GAME_INFO_DATA()
	{
		pSocket = NULL;
		IpAddr[0] = '\0';
		iPort = -1;
		gsn = -1;
		Type = -1;
	};
};

/*
class CTotalScoreCell : public CObject
{
public:
	int iOrder;
	char Id[MAX_ID+1];
	char Krank[MAX_KRANK+1];
	int iTotalScore;
	//// added by manseek for NetCoin
	int iNetCoin;
	//// 2000.4.30
	int iTotalFight;
	int iTotalFightWin;
	int iTotalFightLost;
	int iTotalFightTie;

public:
	CTotalScoreCell() {};
	~CTotalScoreCell() {};

};
*/

#endif