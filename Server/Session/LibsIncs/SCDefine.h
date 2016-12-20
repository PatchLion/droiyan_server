///////////////////////////////////////////////////////////////////////////////
// SCDefine.h
//
#ifndef _SCDEFINE_H
#define _SCDEFINE_H

// 전체 스레드 컨트롤 상수...
#define AUTOMATA_THREAD			4

// 버퍼 크기 변수...
#define SOCKET_BUF_SIZE			10000

// Defines About Communication
//
#define OVL_RECEIVE				0X01
#define OVL_SEND				0X02
#define OVL_CLOSE				0X03

//	State Value
//
#define STATE_ACCEPTED			0X01
#define STATE_CONNECTED			0X02
#define STATE_DISCONNECTED		0X03
#define STATE_CONNECT			0X04

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

// 송신 스레드 조절 상수...
#define MAX_CONTINUE_SENDING_COUNT	5
#define MAX_SEND_CONTINUE_TICK		25 // 0.05 sec.

#define MAXWORKERTHREAD	10
#define MAX_WORKER_THREAD	10

// 소켓 관련 메시지...
#define SOCKET_FOR_DISCONNECT	7
#define SOCKET_FOR_APPLICATION	9

#endif
///////////////////////////////////////////////////////////////////////////////
