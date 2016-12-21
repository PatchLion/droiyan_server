///////////////////////////////////////////////////////////////////////////////
// Define.h
//
#ifndef _DEFINE_H
#define _DEFINE_H


#define WM_SOCKET_DATARECEIVE	7000

//
//	Defines About Communication
#define USER_SOCKET_PORT		12000

#define OVL_RECEIVE				0X01
#define OVL_SEND				0X02
#define OVL_CLOSE				0X03

#define PACKET_START1			0XAA
#define PACKET_START2			0X55
#define PACKET_END1				0X55
#define PACKET_END2				0XAA

#define SOCKET_BUF_SIZE			10000
// PROTOCAL
#define PROTOCOL_VER			1
#define PACKET_DATA_SIZE		SOCKET_BUF_SIZE

//
// DEFINE MACRO PART...
#define MAX_SEND_BUFF_SIZE	(SOCKET_BUF_SIZE*10)	// (1024*8)
#define MAX_RECV_BUFF_SIZE	SOCKET_BUF_SIZE

//
//CJSocket Protocol Parsing Data
#define JS_SOCKET_BUF_SIZE				SOCKET_BUF_SIZE
#define JS_PACKET_DATA_SIZE				SOCKET_BUF_SIZE
#define JS_PACKET_START1				0XFE
#define JS_PACKET_START2				0XFF
#define JS_PACKET_END1					0XFF
#define JS_PACKET_END2					0XFE
#define JS_PROTOCOL_VER					0X01

#define J_PACKET_START1			0XFE
#define J_PACKET_START2			0XFF
#define J_PACKET_END1			0XFF
#define J_PACKET_END2			0XFE



#define BufInc(x) (x)++;(x) %= JS_SOCKET_BUF_SIZE;

//	State Value
//
#define STATE_ACCEPTED			0X01
#define STATE_CONNECTED			0X02
#define STATE_DISCONNECTED		0X03
#define STATE_CONNECT			0X04

#define receives				0
#define sends					1
#define both					2 

#define UM_PROCESS_REMOVESOCKET	30000
#define UM_PROCESS_SOCKETACCEPT	30001

///////////////////////////////////////////////////////////////////////////////
// SESSION PROTOCOL DEFINE...
//
#define ERROR_INVALID		1
#define ERROR_CLIENTSEND	2
#define ERROR_CLIENTRECV	3
#define ERROR_SERVERSEND	4
#define ERROR_SERVERRECV	5
#define ERROR_RECVTIMEOUT	6
#define ERROR_SUSPEND		7
#define ERROR_SERVERFULL	8
#define ERROR_DENYOPEN		9
#define ERROR_UNLINK		10

#define ERROR_USER			100

/*
typedef union
{
	short int	i;
	BYTE		b[2];
} MYSHORT;
*/

typedef union
{
	int			i;
	BYTE		b[4];
} MYINT;

typedef union
{
	DWORD		w;
	BYTE		b[4];
} MYDWORD;

#endif
///////////////////////////////////////////////////////////////////////////////
