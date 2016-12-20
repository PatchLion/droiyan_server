///////////////////////////////////////////////////////////////////////////////
// I/O COMPLETION PORT BASE HEADER FILE
//

#ifndef _IOCOMPLETIONPORTBASE_H
#define _IOCOMPLETIONPORTBASE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Scdefine.h"
#include "Cbsocket.h"
#include "Search.h"

#define BELOW_NORMAL_PRIORITY_CLASS 0x00004000
#define ABOVE_NORMAL_PRIORITY_CLASS 0x00008000

class CDBSocket;
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


class CIOCPBASE
{
public:
	int					m_bNaglingOffFlag;
	int					m_MaxResources;
	CSearch				*m_pSearchList;
	int					m_bAcceptEnableFlag;
	int					m_ThreadCount;
	int					m_CurThreadNo;
	int					m_CurRecvThreadNo;
	CPoolBaseManager	*m_pPBM;
	HANDLE				m_hIOCPort[8+1];

	CLSocketArray		m_ListenSocketArray;
	CLEventArray		m_hListenEventArray;
	CThreadPacketArray	m_ThreadPacketArray;
	SOCKET				*m_pSocketListen;
	HANDLE				*m_phListenSocketEvent;
	THREADPACKET		*m_pThreadPacket;
	BYTE				*m_pIopendingData;
	int					m_nIopendingDataCount;
	int					m_bIOPendingStop;
	HANDLE				m_hStopEventForResourceManager;
	DWORD				m_nRMIntervalTick;

protected:
	DWORD				m_dwNumberOfWorkers;
	DWORD				m_dwConcurrency;
	int					m_Type;
						
public:
	CIOCPBASE();
	~CIOCPBASE();

	// 스레드 관련 함수...
	void SetThreadCount(int tc = 1) { m_ThreadCount = tc; };

	void NaglingStatusOn() { m_bNaglingOffFlag = 0; };
	void NaglingStatusOff() { m_bNaglingOffFlag = 1; };
	void CreateAcceptThread();
	void CreateWorkerThread();
	void SetupResourceKeeper(DWORD intervaltick = 60000);
	void SetStopForResourceKeeper();

	// 소켓 관련 함수...
	BOOL Associate(CIOCPSocket *pUser);
	int GetSocketType() { return m_Type; };
	void SetSocketType(int type) { m_Type = type; };
	BOOL Listen(int port, char *svrAddress = NULL);
	int Init( int type, CPoolBaseManager *pPBM );
	int MakeThreadSafeMessage( int cmd_code, int wparam, long lparam );

	// 서치 함수...
	CBSocket *GetUser(int uid);
	void UserFree(int uid);
};

#endif
