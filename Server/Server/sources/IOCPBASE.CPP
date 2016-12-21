///////////////////////////////////////////////////////////////////////////////
// I/O COMPLETION PORT BASE CLASS
//
#include "StdAfx.h"
#include "IOCPSocket.h"
#include "Iocpbase.h"
#include "Cbsocket.h"
#include "Poolbase.h"
#include "Scdefine.h"
#include "Resource.h"
#include "Serverdlg.h"
#include <process.h>

#include "Extern.h"

#define MAX_CONTINUE_SENDING_COUNT	5
//#define MAX_SEND_CONTINUE_TICK		25 // 0.05 sec.
#define MAX_SEND_CONTINUE_TICK		300 // 0.05 sec.


extern CServerDlg *g_pMainDlg;
extern DWORD g_ThreadAliveTime[];

//DWORD WINAPI AcceptListenThread(LPVOID lp)
//unsigned __stdcall AcceptListenThread( void *lp )
UINT AcceptListenThread( void *lp )
{
	struct linger lingerOpt;
	int l_stat;

	THREADPACKET *pThreadPacket = (THREADPACKET *)lp;
	CIOCPBASE *pIocpBase = pThreadPacket->pIocpbase;
	CPoolBaseManager *pSQM = pIocpBase->m_pPBM;

	HANDLE *hListenSockEvent;
	SOCKET *pListenSocket;
	int nSocketType;
	const RHANDLE* pHandle = 0;

	hListenSockEvent = pThreadPacket->phListenSockEvent;
	pListenSocket = pThreadPacket->pListenSock;
	nSocketType = pThreadPacket->iSocketType;

	struct sockaddr_in addr;
	int wait_return, sid, addr_len;
	WSANETWORKEVENTS network_event;

	while( !pIocpBase->m_bAcceptEnableFlag )
	{
		Sleep(1);
	};
	
	while ( 1 )
	{
		wait_return = WaitForSingleObject( *hListenSockEvent, INFINITE);
	
		if ( wait_return == WAIT_FAILED )
		{
			TRACE("]Wait Listen Socket Failed[%d]...", GetLastError());
			return 1;
		}

		WSAEnumNetworkEvents( *pListenSocket, *hListenSockEvent, &network_event );

		if ( network_event.lNetworkEvents & FD_ACCEPT )
		{
			if ( network_event.iErrorCode[FD_ACCEPT_BIT] == 0 ) 
			{
				CBSocket *pSocket;
				int getsocket_count = 0;

getsocket_loop:
				
				pHandle = 0; sid = -1;

				DWORD ret = pSQM->GetFreeResource(&pHandle);
				if ( ret == 0 )
				{
					if ( pHandle == NULL ) 
					{
						Sleep(1);
						TRACE("]GetFreeResource but NULL pointer(pHandle) and continue...\n");
						continue;
					}

					sid = pHandle->pos;
					pSocket = (CBSocket *)pHandle->handle;
					if ( pSocket == NULL )
					{
						Sleep(1);
						TRACE("]GetFreeResource but NULL pointer(pHandle->handle) and continue...\n");
						continue;
					}

					pSocket->m_pIocpBase = NULL;
				}		
				else
				{
					TRACE("]Accepting success but Fail to allocates socket.\n");

					SOCKET s;
					s = accept( *pListenSocket, (struct sockaddr *)&addr, &addr_len );
					if ( s != INVALID_SOCKET )
						closesocket(s);

					getsocket_count++;
					if ( getsocket_count < 3 )
						goto getsocket_loop;

					Sleep(1000);
					continue;
				}

				addr_len = sizeof(addr);
				pSocket->m_Socket = accept( *pListenSocket, (struct sockaddr *)&addr, &addr_len );
				if ( pSocket->m_Socket == INVALID_SOCKET )
				{
					TRACE("]Accept Fail : Invalid socket.\n");
					pSQM->ReleaseResource(pHandle);
					//Sleep(50);
					continue;
				}

				// Linger off -> close socket immediately regardless of existance of data 
				//
				lingerOpt.l_onoff = 1;
				lingerOpt.l_linger = 0;

				l_stat = setsockopt( pSocket->m_Socket, SOL_SOCKET, SO_LINGER, (char *)&lingerOpt, sizeof(lingerOpt) );
				if ( l_stat < 0 )
				{
					TRACE("]Linger opt Failed : sid[%d]\n", sid);
					pSocket->B_OnClose(0);
					pSQM->ReleaseResource(pHandle);
					continue;
				}

				if( g_bShutDown )
				{
					pSocket->B_OnClose(0);
					pSQM->ReleaseResource(pHandle);
					continue;
				}

				int retValue;

				pSocket->m_pIocpBase = pIocpBase;
				pSocket->m_Sid = sid;
				pSocket->m_State = STATE_ACCEPTED;
				pSocket->m_Type = nSocketType;

				// RECV OV : USER I/O COMPLETION PACKET FOR NOTIFY...
				pSocket->m_RecvOverlap.hEvent = NULL;

				// SEND OV : USER STANDARD EVENT MECH.
				//pSocket->m_SendOverlap.hEvent = NULL;
				if ( pSocket->m_SendOverlap.hEvent == NULL )
					pSocket->m_SendOverlap.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
				pSocket->m_SendOverlap.hEvent = (HANDLE)((DWORD)pSocket->m_SendOverlap.hEvent|0x1);

				memcpy( &pSocket->m_Addr, &addr, sizeof(addr) );
				// IKING 2002.6.29
				if ( pSocket->m_hSockEvent == NULL )
					pSocket->m_hSockEvent = WSACreateEvent();

				if ( !pIocpBase->Associate( pSocket ) )
				{
					TRACE("]Associates Failed : sid[%d]\n", sid);
					pSocket->B_OnClose(0);
					pSQM->ReleaseResource(pHandle);
					//Sleep(50);
					continue;
				}

				// Socket Enable...
				pSocket->m_SockFlag = 1;
				pSocket->Init(0);

				retValue = pSocket->RecycleRead();
				if ( retValue == -1 )
				{
					g_pMainDlg->UserFree( pSocket->m_Sid );

					TRACE("]Accepting and recycleread error : sid[%d]\n", sid);
					pSocket->B_OnClose(0);
					pSQM->ReleaseResource(pHandle);
					continue;
				}
				else if ( retValue == -2 )
				{
					g_pMainDlg->UserFree( pSocket->m_Sid );

					pSocket->B_OnClose(0);
					pSQM->ReleaseResource(pHandle);
					continue;
				}

				TRACE("]Accept Socket[%d]...\n", sid);
			
					Sleep(100);
			}
		}
	}

	return 1;
}

//DWORD WINAPI WorkerClientSocketThread(LPVOID lp)
unsigned __stdcall WorkerClientSocketThread( void *lp )
//UINT WorkerClientSocketThread( void *lp )
{
	CIOCPBASE *pIocpBase = (CIOCPBASE *)lp;
	CPoolBaseManager *pSQM = pIocpBase->m_pPBM;
	int nModCount;

	nModCount = pIocpBase->m_CurRecvThreadNo++;

	DWORD			WorkIndex;	
	BOOL			b;
	LPOVERLAPPED	pOvl;
	DWORD			nbytes;
	CBSocket		*pBSocket;
	int				retValue;

	if ( pIocpBase->GetSocketType() == SOCKET_FOR_SERVER)
		TRACE(">Server Worker Thread Started :[%d]...\n", nModCount);
	else
		TRACE(">User Worker Thread Started :[%d]...\n", nModCount);

	while ( 1 )
	{
		b = GetQueuedCompletionStatus( 
									  pIocpBase->m_hIOCPort,
									  &nbytes,
									  &WorkIndex,
									  &pOvl,
									  INFINITE
									  );

		if ( b && pOvl ) 
		{
			if ( WorkIndex >= pSQM->m_dwNumCurrentResources )
			{
				TRACE("U1: WorkIndex >= pSQM->m_dwNumCurrentResources...\n");
				goto loop_pass;
			}

			if ( pOvl->Offset != OVL_CLOSE )
			{
				if ( pSQM->m_pResources->IsFree( WorkIndex ) == true ) 
				{
					pBSocket = (CBSocket *)pSQM->m_pResources->GetDataValue( WorkIndex );
					if ( !pBSocket )
					{
						TRACE("U1_1: !pBSocket...\n");
						goto loop_pass;
					}
					pBSocket->m_ActivatedFlag = 1;
					pBSocket->SocketDisConnect();

					TRACE("U2: pSQM->m_pResources->IsFree( WorkIndex ) == true[%d]... \n", WorkIndex );
					goto loop_pass;
				}
			}

			pBSocket = (CBSocket *)pSQM->m_pResources->GetDataValue( WorkIndex );
			if ( !pBSocket )
			{
				TRACE("U3: !pBSocket...\n");
				goto loop_pass;
			}


			switch ( pOvl->Offset )
			{
			case	OVL_RECEIVE:
				if ( !nbytes )
				{
					pBSocket->m_ActivatedFlag = 1;
					pBSocket->SocketDisConnect();
					break;
				}

				pBSocket->m_ActivatedFlag = 1;
				pBSocket->m_iWsaReadIOPendFlag = 0;
				pBSocket->ParseCommand(nbytes);
				retValue = pBSocket->RecycleRead();
				if ( retValue == -1 )
				{
					pBSocket->SocketDisConnect();
					TRACE("RECV-RECYCLEING-ERROR(%d) [%d]...\n", retValue, WorkIndex);
					break;
				}
				else if ( retValue == -2 )
				{

					pBSocket->SocketDisConnect();
					TRACE("RECV-RECYCLEING-ERROR2(%d) [%d]...\n", retValue, WorkIndex);
					break;
				}

				break;

			case	OVL_SEND:
				pBSocket->m_ActivatedFlag = 1;
				pBSocket->B_OnSend(0);
				break;

			case	OVL_CLOSE:
				if ( pSQM->m_pResources->IsFree( WorkIndex ) == true ) 
					break;

				pBSocket->m_ActivatedFlag = 1;

				if ( pBSocket->m_Socket != INVALID_SOCKET )
				{
					closesocket(pBSocket->m_Socket);
					pBSocket->m_Socket = INVALID_SOCKET;
				}
			RHANDLE *pHandle;
				pHandle = pSQM->m_pResources->GetHandle( WorkIndex );
				if ( pHandle )
					pSQM->ReleaseResource(pHandle);
				else
				{
					TRACE("]Iocp closed : sid[%d] Handle Error...\n", WorkIndex );
				}

				TRACE("]IocpClosed : sid[%d]\n", WorkIndex );
				break;

			default:
				TRACE("]Iocp closed for Default: sid[%d]\n", WorkIndex );
				pBSocket->SocketDisConnect();
				break;
			}
		}
		else
		{
			if ( pOvl )
			{
				if ( WorkIndex >= pSQM->m_dwNumCurrentResources ) 
				{
					TRACE("D1: WorkIndex >= pSQM->m_dwNumCurrentResources...[%d]\n", WorkIndex );
					goto loop_pass;
				}

				pBSocket = (CBSocket *)pSQM->m_pResources->GetDataValue( WorkIndex );
				if ( !pBSocket )
				{
					TRACE("D3: !pBSocket...\n");
					goto loop_pass;
				}

				pBSocket->m_ActivatedFlag = 1;
				pBSocket->SocketDisConnect();

				TRACE("]b is NULL : sid[%d]\n", WorkIndex);
			}
			else // ERROR...
			{
				if ( WorkIndex < pSQM->m_dwNumCurrentResources ) 
				{
					pBSocket = (CBSocket *)pSQM->m_pResources->GetDataValue( WorkIndex );
					if ( pBSocket )
					{
//						pBSocket->SessionLogOut();
						pBSocket->m_ActivatedFlag = 1;
						pBSocket->SocketDisConnect();
					}
				}

				int ioError;
				ioError = GetLastError();

				if ( ioError == WAIT_TIMEOUT )
				{
					TRACE ("GETQUEUEDCOMPLETIONSTATUS : TIME-OUT..."); 
				}
				else
				{
					TRACE1("GETQUEUEDCOMPLETIONSTATUS : ERROR CODE=%d", ioError); 
				}
			}
		}

loop_pass:;
	}

	return 1;
}

UINT WorkerSocketThreadWrapper( void *lp )
{
	UINT dwExitCode = 0;

	__try
	{
		dwExitCode = WorkerClientSocketThread( lp );
	}
	__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{}

	return (dwExitCode);
}


UINT WorkerDataProcThread( void *lp )
{
	DATAPROCTHREADPACKET *pDPTP = (DATAPROCTHREADPACKET *)lp;
	CIOCPBASE *pIocpBase = pDPTP->pIocpbase;
	CPoolBaseManager *pSQM = pIocpBase->m_pPBM;

	int nThreadNo = 0;
	nThreadNo = pIocpBase->m_CurDataProcThreadNo;
	pIocpBase->m_CurDataProcThreadNo++;
	CBSocket *pSocket;


start_loop:;
	if ( pIocpBase->m_CurDataProcThreadNo < pIocpBase->m_ThreadCount )
	{
		Sleep(1);
		goto start_loop;
	}

	TRACE("Thread Started [%d][%d]...\n", nThreadNo, pIocpBase->m_CurDataProcThreadNo-1 );

	WAIT_RECV_DATA *wrd;


	for (;;)
	{
		if ( pIocpBase->m_nHeadPtr[nThreadNo] == pIocpBase->m_nTailPtr[nThreadNo] )
		{
			Sleep(1);
			continue;
		}

		wrd = pIocpBase->m_pRecvData[nThreadNo][pIocpBase->m_nTailPtr[nThreadNo]];
		pIocpBase->m_pRecvData[nThreadNo][pIocpBase->m_nTailPtr[nThreadNo]] = NULL;
		pIocpBase->m_nTailPtr[nThreadNo]++;
		pIocpBase->m_nTailPtr[nThreadNo] %= WAIT_RECV_DATA_BUFFER;

		if ( wrd == NULL ) continue;


		if ( wrd->m_Type == SOCKET_FOR_DISCONNECT )
		{
			if ( wrd->usn >= 0 && wrd->usn < 32767 )
			{
				CPoolBaseManager *pSQM = pIocpBase->m_pPBM;
				if(!pSQM)
				{
					delete wrd;
					continue;
				}
				else
				{
					if ( pSQM->m_pResources->IsFree( wrd->usn ) == false ) 
					{
						pSocket = (CBSocket *)pSQM->m_pResources->GetDataValue( wrd->usn );
						if ( !pSocket )
						{
							delete wrd;
							continue;
						}
					}
					else
					{
						delete wrd;
						continue;
					}

				}
			}
			else
			{
				delete wrd;
				continue;
			}

			if ( pSocket == NULL )
			{
				delete wrd;
				continue;
			}

			pSocket->SockCloseProcess();
			
			delete wrd;
			continue;
		}

		pDPTP->fn(wrd);

		delete wrd;
	}


	return 1;
}

CIOCPBASE::CIOCPBASE()
{
	int i,j;
	m_ThreadCount = 1;
	m_CurThreadNo = 0;
	m_pPBM = NULL;
	m_pIopendingData = NULL;
	m_nIopendingDataCount = 0;
	m_bIOPendingStop = FALSE;

	for ( i = 0; i < MAX_WORKER_THREAD; i++ )
	{
		InitializeCriticalSection(&m_CS_ReceiveData[i]);
	}

	m_CurRecvThreadNo = 0;
	m_CurDataProcThreadNo = 0;

	// IKING 2002.7.3
	for ( i = 0; i < MAX_WORKER_THREAD+1; i++ )
	{
		m_nHeadPtr[i] = 0;
		m_nTailPtr[i] = 0;
	};

	for ( i = 0; i < MAX_WORKER_THREAD+1; i++ )
	{
		for ( j = 0; j < WAIT_RECV_DATA_BUFFER+1; j++ )
		{
			m_pRecvData[i][j] = NULL;
		}
	};
}

CIOCPBASE::~CIOCPBASE()
{
	int i;
	// Listen Socket Array 지우기...
	for (  i = 0; i < m_ListenSocketArray.GetSize(); i++ )
	{
		if ( m_ListenSocketArray[i] )
		{
			delete m_ListenSocketArray[i];
			m_ListenSocketArray[i] = NULL;
		}
	}
	m_ListenSocketArray.RemoveAll();

	// Event Array 지우기...
	for ( i = 0; i < m_hListenEventArray.GetSize(); i++ )
	{
		if ( m_hListenEventArray[i] )
		{
			delete m_hListenEventArray[i];
			m_hListenEventArray[i] = NULL;
		}
	}
	m_hListenEventArray.RemoveAll();

	// Thread Packet Array 지우기...
	for ( i = 0; i < m_ThreadPacketArray.GetSize(); i++ )
	{
		if ( m_ThreadPacketArray[i] )
		{
			delete m_ThreadPacketArray[i];
			m_ThreadPacketArray[i] = NULL;
		}
	}
	m_ThreadPacketArray.RemoveAll();
	//

	for ( i = 0; i < MAX_WORKER_THREAD; i++ )
	{
		DeleteCriticalSection(&m_CS_ReceiveData[i]);
	}

	if ( m_pIopendingData )
	{
		delete[] m_pIopendingData;
		m_pIopendingData = NULL;
	}

	CloseHandle( m_CreateSignalEvent );
}

void CIOCPBASE::CreateAcceptThread()
{
	

	m_pThreadPacket = new THREADPACKET;
	m_pThreadPacket->pIocpbase = this;
	m_pThreadPacket->phListenSockEvent = m_phListenSocketEvent;
	m_pThreadPacket->pListenSock = m_pSocketListen;
	m_pThreadPacket->iSocketType = m_Type;
	m_ThreadPacketArray.Add(m_pThreadPacket);

	//acceptThread = ::CreateThread( NULL, 0, AcceptListenThread, (LPVOID)m_pThreadPacket, 0, &id);
	m_acceptThread = AfxBeginThread( AcceptListenThread, (LPVOID)m_pThreadPacket );

	
}

void CIOCPBASE::CreateWorkerThread()
{
	SYSTEM_INFO		SystemInfo;

	HANDLE			hWorkerThread[MAXWORKERTHREAD];
	unsigned int 	WorkerId[MAXWORKERTHREAD];

	SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
	GetSystemInfo (&SystemInfo);

	m_dwNumberOfWorkers = 2 * SystemInfo.dwNumberOfProcessors + 2;
	m_dwConcurrency = 0;
	
	m_hIOCPort = CreateIoCompletionPort( INVALID_HANDLE_VALUE,
		                                 NULL,
										 (DWORD)-1,
										 m_dwConcurrency );
	
	// 스레드 생성하기...
	for ( DWORD i = 0; i < m_dwNumberOfWorkers; i++ )
	{
		/*
		hWorkerThread[i] = ::CreateThread(
										NULL,
										0,
										WorkerClientSocketThread,
										(LPVOID)this,
										CREATE_SUSPENDED,
										&WorkerId[i]
										);
		*/

		hWorkerThread[i] = (HANDLE)_beginthreadex(
										NULL,
										0,
										WorkerClientSocketThread,
										(LPVOID)this,
										CREATE_SUSPENDED,
										&WorkerId[i]
										);

		SetThreadPriority( hWorkerThread[i], THREAD_PRIORITY_ABOVE_NORMAL);
	}

	// 스레드 활성화...
	for ( DWORD j = 0; j < m_dwNumberOfWorkers; j++ )
	{
		ResumeThread( hWorkerThread[j] );
	}
}

BOOL CIOCPBASE::Associate(CIOCPSocket *pIocpSock)
{
	HANDLE hTemp;

	if (!m_hIOCPort)
	{
		return FALSE;
	}
	
	hTemp = CreateIoCompletionPort( (HANDLE)pIocpSock->m_Socket, m_hIOCPort, (DWORD)pIocpSock->m_Sid, m_dwConcurrency);
	if ( hTemp == NULL )
	{
		#ifdef _DEBUG		
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);

		TRACE("CreateIoCompletionPort Error : %s\n", lpMsgBuf );
		LocalFree( lpMsgBuf );
		#endif

		return FALSE;

	}
	
	return (hTemp == m_hIOCPort);
}

BOOL CIOCPBASE::Listen(int port, char *pStrSvrAddr )
{
	int opt;
	struct sockaddr_in addr;

	m_pSocketListen = new SOCKET;
	if ( m_pSocketListen == NULL ) return FALSE;

	*m_pSocketListen = WSASocket(AF_INET,
		                         SOCK_STREAM,
								 0,
								 NULL,
								 0,
								 WSA_FLAG_OVERLAPPED);

	if ( *m_pSocketListen < 0 ) 
	{
		TRACE("]Error(01) - Can't Open Stream Socket\n");
		return FALSE;
	}

	memset((void *)&addr, 0, sizeof(addr));
	addr.sin_family	= AF_INET;
	
	if ( pStrSvrAddr == NULL )
		addr.sin_addr.s_addr	= htonl(INADDR_ANY);
	else
		addr.sin_addr.s_addr	= inet_addr( pStrSvrAddr );

	addr.sin_port			= htons(port);

	opt = 1;
	setsockopt( *m_pSocketListen, SOL_SOCKET, SO_KEEPALIVE, (char *)&opt, sizeof(opt));
	
	opt = 1;
	setsockopt( *m_pSocketListen, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
	
	if ( bind( *m_pSocketListen, (struct sockaddr *)&addr, sizeof(addr)) < 0 )
	{
		TRACE("]Error(02)- Can't bind local address\n");
		return FALSE;
	}

	int socklen, len, err;

	socklen = 8192 * 8;
	setsockopt( *m_pSocketListen, SOL_SOCKET, SO_RCVBUF, (char*)&socklen, sizeof(socklen) );
	
	len = sizeof(socklen);
	err = getsockopt( *m_pSocketListen, SOL_SOCKET, SO_RCVBUF, (char*)&socklen, &len );
	if (err == SOCKET_ERROR)
	{
		TRACE("]Set Socket RecvBuf of port(%d) as %d : Fail\n", port, socklen);
		return FALSE;
	}

	socklen = 8192 * 8;
	setsockopt( *m_pSocketListen, SOL_SOCKET, SO_SNDBUF, (char*)&socklen, sizeof(socklen) );
	len = sizeof(socklen);
	err = getsockopt( *m_pSocketListen, SOL_SOCKET, SO_SNDBUF, (char*)&socklen, &len );

	if (err == SOCKET_ERROR)
	{
		TRACE("]Set Socket SendBuf of port(%d) as %d : Fail\n", port, socklen);
		return FALSE;
	}
	
	listen( *m_pSocketListen, 5 );
	m_ListenSocketArray.Add( m_pSocketListen );

	m_phListenSocketEvent = new HANDLE;
	*m_phListenSocketEvent = WSACreateEvent();
	m_hListenEventArray.Add(m_phListenSocketEvent);

	WSAEventSelect( *m_pSocketListen, *m_phListenSocketEvent, FD_ACCEPT);

	TRACE("]Port[%05d] initialzed\n", port);

	CreateAcceptThread();

	return TRUE;
}

int CIOCPBASE::Init( int type, CPoolBaseManager *pPBM, DWORD (*fn)(LPVOID lp) )
{
	int i;
	m_Type = type;
	m_pPBM = pPBM;

	m_bAcceptEnableFlag = FALSE;

	// 변수 초기화...
	for (i = 0; i < m_ThreadCount; i++ )
	{
		m_nDataListLength[i] = 0;
	}

	m_CreateSignalEvent = CreateEvent( NULL, TRUE, FALSE, NULL );

	CreateWorkerThread();

	// 데이타 처리 그레드 만들기...
	if ( fn )
	{
		//HANDLE hWorkerDataProcThread[MAXWORKERTHREAD];
		//unsigned int WorkerDataProcId[MAXWORKERTHREAD];

		m_Dptp.pIocpbase = this;
		m_Dptp.fn = fn;

		for ( i = 0; i < m_ThreadCount; i++ )
		{
		
			m_hWorkerThread[i] = AfxBeginThread( WorkerDataProcThread, (LPVOID)&m_Dptp, THREAD_PRIORITY_ABOVE_NORMAL );

		}
	}

	return 1;
}

void CIOCPBASE::SetAliveTimeUpdate(int uid, DWORD ctick )
{
	if ( m_pPBM )
		m_pPBM->m_pResources->SetTimeStamp( uid, ctick );
}
