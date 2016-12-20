#ifndef __COMMON_H
#define __COMMON_H

#define	WAIT_RECV_DATA_BUFFER		4096

// 파라미터...
//#define	PACKET_DATA_SIZE	SOCKET_BUF_SIZE
#define MAX_USER_IN_WAIT			100	
//#define AUTOMATA_THREAD			8
#define AUTOMATA_THREAD				4
#define	MAX_ID						12

#define RECEIVE_BUF_SIZE			SOCKET_BUF_SIZE
#define DATA_BUF_SIZE_FOR_THREAD	8192

// USER STATUS
#define	USER_EXIST_IN_WAIT			0X01
#define USER_EXIST_IN_ROOM			0X02
#define USER_JUST_LOG_IN			0X03
#define USER_JUST_CONNECTED			0x04
#define USER_EXIST_IN_NEWUSER		0X05

// 스레드 명령어 파라메터...
#define CMD_SERVER_CLOSE			1000
#define CMD_USER_CLOSE				2000
#define CMD_NEWWAITSERVER_CONNECTED 3000
#define CMD_ROOM_CLOSE				4000

// SOCKET TYPE...
#define SOCKET_FOR_NONESTATE	0
#define SOCKET_FOR_SERVER		1
#define SOCKET_FOR_USER			2
#define SOCKET_FOR_USERSERVER	3
#define SOCKET_FOR_BUDDYSERVER	4
#define SOCKET_FOR_DBSERVER		5
#define SOCKET_FOR_ZONESERVER	6	// Add by JJS 2002.02.28
#define SOCKET_FOR_DISCONNECT	7
#define SOCKET_FOR_APPLICATION	9

struct __LOGINOUTTHREAD
{
	int UID;
	BYTE CODE;
	char ID[CHAR_NAME_LENGTH+sizeof(int)+1];

	__LOGINOUTTHREAD()
	{
		UID = -1;
		CODE = -1;
		ID[0] = '\0';
	};
};

typedef __LOGINOUTTHREAD LOGINOUTTHREADDATA;


struct __SQLDATAPACKET
{
	int UID;
	BYTE code;
	int dcount;
	BYTE *pData;

	__SQLDATAPACKET()
	{
		UID = -1;
		code = -1;
		dcount = 0;
		pData = NULL;
	};

	~__SQLDATAPACKET()
	{
		if ( pData )
			delete[] pData;
		pData = NULL;
	};
};

typedef __SQLDATAPACKET SQLDATAPACKET;

struct __CHATDATAPACKET
{
	int UID;
	BYTE code;
	int dcount;
	BYTE *pData;

	__CHATDATAPACKET()
	{
		UID = -1;
		code = -1;
		dcount = 0;
		pData = NULL;
	};

	~__CHATDATAPACKET()
	{
		if ( pData )
			delete[] pData;
		pData = NULL;
	};
};

typedef __CHATDATAPACKET CHATDATAPACKET;

//-----------------------------------------------------------------------------
// FORTRESS PROTOCOL PART
struct __FORTRESSDATAPACKET
{
	short sFortressIndex;
	TCHAR FORTRESS[CHAR_NAME_LENGTH+sizeof(int)+1];		// GuildName

	__FORTRESSDATAPACKET()
	{
		sFortressIndex = -1;
		FORTRESS[0] = '\0';
	};
};

typedef __FORTRESSDATAPACKET FORTRESSDATAPACKET;

//-----------------------------------------------------------------------------
// DB SERVER PROTOCOL PART
#define DB_SERVER_IN_REQ	((BYTE)0x10)
#define DB_SERVER_IN_RES	((BYTE)0x11)

#endif
