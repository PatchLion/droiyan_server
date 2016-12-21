///////////////////////////////////////////////////////////////////////////////
// I/O COMPLETION PORT BASE HEADER FILE
//

#ifndef _IOCOMPLETIONPORTBASE_H
#define _IOCOMPLETIONPORTBASE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXWORKERTHREAD		1000

#define SOCKET_FOR_NONE		0
#define SOCKET_FOR_JANG		1
#define SOCKET_FOR_GAME		2
#define SOCKET_FOR_GIBO		3

#define MAX_WORKER_THREAD	AUTOMATA_THREAD*2+2

#include "Cbsocket.h"
#include "Mcommon.h"

class CBSocket;
class CIOCPBASE;
struct _ThreadPacket
{
	CIOCPBASE *pIocpbase;
	HANDLE *phListenSockEvent;
	SOCKET *pListenSock;
	int iSocketType;
};

typedef _ThreadPacket THREADPACKET;

struct _DataProcThreadPacket
{
	CIOCPBASE *pIocpbase;
	DWORD (*fn)(LPVOID);
};
typedef _DataProcThreadPacket DATAPROCTHREADPACKET;

typedef CTypedPtrArray <CPtrArray, SOCKET*> CLSocketArray;
typedef CTypedPtrArray <CPtrArray, HANDLE*> CLEventArray;
typedef CTypedPtrArray <CPtrArray, THREADPACKET*> CThreadPacketArray;

class CIOCPSocket;
class CPoolBaseManager;
class WAIT_RECV_DATA; //IKING 2002.7.3

class CIOCPBASE
{
public:
	// IKING 2002.7.3
	CRITICAL_SECTION	m_CS_ReceiveData[MAX_WORKER_THREAD+1];
	int					m_nHeadPtr[MAX_WORKER_THREAD+1];
	int					m_nTailPtr[MAX_WORKER_THREAD+1];
	WAIT_RECV_DATA		*m_pRecvData[MAX_WORKER_THREAD+1][WAIT_RECV_DATA_BUFFER+1];

	DATAPROCTHREADPACKET m_Dptp;
	int	m_CurDataProcThreadNo;

	CWinThread *m_acceptThread;
	CWinThread *m_hWorkerThread[MAX_WORKER_THREAD+1];

	int m_bAcceptEnableFlag;
	int m_ThreadCount;
	int m_CurThreadNo;
	int m_CurRecvThreadNo;
	int m_nDataListLength[MAX_WORKER_THREAD+1];
	CPtrList m_pSendDataList[MAX_WORKER_THREAD+1];

	CPoolBaseManager *m_pPBM;
	CRITICAL_SECTION m_SendDataCriticalSection[MAX_WORKER_THREAD+1];
	HANDLE m_CreateSignalEvent;

	HANDLE m_hIOCPort;

	CLSocketArray m_ListenSocketArray;
	CLEventArray m_hListenEventArray;
	CThreadPacketArray m_ThreadPacketArray;
	SOCKET *m_pSocketListen;
	HANDLE *m_phListenSocketEvent;
	THREADPACKET *m_pThreadPacket;
	BYTE *m_pIopendingData;
	int m_nIopendingDataCount;
	int m_bIOPendingStop;

protected:
	DWORD m_dwNumberOfWorkers;
	DWORD m_dwConcurrency;
	int m_Type;

public:
	CIOCPBASE();
	~CIOCPBASE();

	void SetThreadCount(int tc = 1) { m_ThreadCount = tc; };
	BOOL Listen(int port, char *svrAddress = NULL);
	void CreateAcceptThread();
	void CreateWorkerThread();
	BOOL Associate(CIOCPSocket *pUser);

	int GetSocketType() { return m_Type; };
	void SetSocketType(int type) { m_Type = type; };

	int Init( int type, CPoolBaseManager *pPBM, DWORD (*fn)(LPVOID lp) = NULL );

	void SetAliveTimeUpdate(int uid, DWORD ctick );
};

#endif
