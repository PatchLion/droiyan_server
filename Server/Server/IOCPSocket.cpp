///////////////////////////////////////////////////////////////////////////////
// CIOCPSocket Class Define
//
#include "StdAfx.h"
#include "Iocpbase.h"
#include "IOCPSocket.h"

CIOCPSocket::CIOCPSocket()
{
	m_SockAliveFlag = 0;
	m_iWsaReadIOPendFlag = 0;
	m_iWsaWriteIOPendFlag = 0;
	m_iWsaWouldBlockFlag = 0;
	m_pIocpBase = NULL;
	m_sConnectAddress = "";
	m_rByte = 0;
	m_RecvOverlap.hEvent = NULL;
	m_SendOverlap.hEvent = NULL;
	m_nIoPendingCount = 0;
	m_Socket = INVALID_SOCKET;
	m_hSockEvent = NULL;
	m_Sid = 0;
	m_ioPendingEnableFlag = 0;

	// WSA_IO_PENDING 상태를 리셋 상태로 초기화... 
	ResetEvent(m_SendOverlap.hEvent);

	// IKING 2002.6.29
	InitializeCriticalSection(&m_CS_CloseTime);
}

CIOCPSocket::~CIOCPSocket()
{
	if ( m_RecvOverlap.hEvent )
		CloseHandle(m_RecvOverlap.hEvent);

	if ( m_SendOverlap.hEvent )
		CloseHandle(m_SendOverlap.hEvent);

	// IKING 2002.6.29
	DeleteCriticalSection(&m_CS_CloseTime);
}

BOOL CIOCPSocket::Create( UINT nSocketPort,
						  int nSocketType, 
						  long lEvent,
						  LPCTSTR lpszSocketAddress)
{
	// 소켓 생성...
	//m_Socket = socket( AF_INET, nSocketType/*SOCK_STREAM*/, 0 );
	
	m_Socket = WSASocket( AF_INET,
						  nSocketType/*SOCK_STREAM*/,
						  0,
						  NULL,
						  0,
						  WSA_FLAG_OVERLAPPED
						  );

	// 이벤트 설정...
	// IKING 2002.6.29
	if ( m_hSockEvent == NULL )
		m_hSockEvent = WSACreateEvent();

	m_SockAliveFlag = 0;

	return TRUE;
}

BOOL CIOCPSocket::Connect( LPCTSTR lpszHostAddress, UINT nHostPort )
{
	struct sockaddr_in addr;

	//m_Socket = socket(AF_INET,SOCK_STREAM,0);
	memset((void *)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(lpszHostAddress);
	addr.sin_port = htons(nHostPort);


	int socklen, len, err;
	socklen = 1024*32;
	setsockopt( m_Socket, SOL_SOCKET, SO_RCVBUF, (char*)&socklen, sizeof(socklen) );
	
	len = sizeof(socklen);
	err = getsockopt( m_Socket, SOL_SOCKET, SO_RCVBUF, (char*)&socklen, &len );
	if (err == SOCKET_ERROR)
	{
		TRACE("]Set Socket RecvBuf of port(%d) as %d : Fail\n", nHostPort, socklen);
		return FALSE;
	}

	socklen = 1024*32;
	setsockopt( m_Socket, SOL_SOCKET, SO_SNDBUF, (char*)&socklen, sizeof(socklen) );
	len = sizeof(socklen);
	err = getsockopt( m_Socket, SOL_SOCKET, SO_SNDBUF, (char*)&socklen, &len );

	if (err == SOCKET_ERROR)
	{
		TRACE("]Set Socket SendBuf of port(%d) as %d : Fail\n", nHostPort, socklen);
		return FALSE;
	}
	//

	int result=connect( m_Socket,(struct sockaddr *)&addr,sizeof(addr) );

	if ( result==SOCKET_ERROR )
	{
		int err = WSAGetLastError();
		TRACE("]CONNECTION FAIL : ErrorCode[%d].\n", err);
		return FALSE;
	}

	m_sConnectAddress = lpszHostAddress;
	m_State = STATE_CONNECT;
	memcpy( &m_Addr, &addr , sizeof(addr) );

	if ( !m_pIocpBase->Associate(this) )
	{
		return FALSE;
	}

	// IKING 1999.1.
	m_RecvOverlap.hEvent = NULL;
	m_SendOverlap.hEvent = NULL;

	IOCP_RecycleRead();

	return TRUE;
}

long CIOCPSocket::IOCP_Send(char *pBuf, long length, int dwFlag)
{
	if ( m_SockAliveFlag == 1 )
		return -2;

	if ( m_iWsaWriteIOPendFlag == 1 )
	{
		// 에러 저장...
		m_nIoPendingCount++;
		SetIOCPLastError( WSA_IO_PENDING );
		//return 0;
	}

	if ( m_iWsaWouldBlockFlag == 1 )
	{
		// 에러 저장...
		SetIOCPLastError( WSAEWOULDBLOCK );
		return 0;
	}

	if ( length < 0 || length > SOCKET_BUF_SIZE )
	{
		return 0;
	}

	int RetValue, s_length;
	DWORD sent;
	OVERLAPPED *pOvl;

	sent = 0;
	pOvl = &m_SendOverlap;
	pOvl->Offset = OVL_SEND;
	//pOvl->OffsetHigh = length;

	char pSendBuf[SOCKET_BUF_SIZE+1];
	memcpy( pSendBuf, pBuf, length );
	//m_out.buf = m_SendBuf;
	//m_out.len = length;
	//memcpy( m_SendBuf, pBuf, length );

	s_length = length;

	do
	{
		m_out.buf = &pSendBuf[length-s_length];
		m_out.len = s_length;
		pOvl->OffsetHigh = s_length;

		RetValue = WSASend( m_Socket, &m_out, 1, &sent, dwFlag, pOvl, NULL);
		
		if ( RetValue != 0 )
		{
			int last_err;
			last_err = WSAGetLastError();

			// 에러 저장...
			SetIOCPLastError(last_err);

			if ( last_err == WSA_IO_PENDING )
			{
				// WSA_IO_PENDING 체크...
				int ret;
				DWORD transfer;
				DWORD dwFlag;

				DWORD tick_count = GetTickCount();
				do
				{
					ret = WSAGetOverlappedResult(m_Socket,
												 pOvl,
												 &transfer,
												 FALSE,
												 &dwFlag);
				} while( ret == FALSE && (GetTickCount() - tick_count) < 5 );

				if ( ret == TRUE )
				{
					TRACE("]SEND : WSA_IO_PENDING BUT ADJUST TO CONTINUE[SID=%d, C=%d]\n", m_Sid, m_nIoPendingCount);
					RetValue = transfer;
				}
				else
				{
					m_nIoPendingCount++;
					m_SockAliveFlag = 1;
					RetValue = -2;
					m_iWsaWriteIOPendFlag = 1;

					TRACE("]SEND : WSA_IO_PENDING[SID=%d, C=%d]\n", m_Sid, m_nIoPendingCount);
				}
			

				return RetValue;
			}
			else if ( last_err == WSAEWOULDBLOCK )
			{
				TRACE("]SEND : WSAEWOULDBLOCK\n");

				m_iWsaWouldBlockFlag = 1;
				return RetValue;
			}
			else
			{
				TRACE("]SEND : Error In Sending[%d] = %d\n", m_Sid, last_err);

				m_SockAliveFlag = 1;
				RetValue = -2;
				return RetValue;
			}
		}
		s_length -= sent;

	} while ( s_length > 0 );

	return sent;
}

void CIOCPSocket::IOCP_OnSend(int nErrorCode)
{
	m_iWsaWriteIOPendFlag = 0;
	m_iWsaWouldBlockFlag = 0;
}

int CIOCPSocket::IOCP_RecycleRead()
{
	if ( m_SockAliveFlag != 0 )
	{
		TRACE("]SOCKET IS DEAD[%d]...\n", m_Sid);
		return -2;
	}

	int RetValue;
	DWORD insize, dwFlag=0;
	OVERLAPPED *pOvl;

	memset(m_RecvBuf, NULL, MAX_RECV_BUFF_SIZE );
	m_in.len = MAX_RECV_BUFF_SIZE;
	m_in.buf = m_RecvBuf;

	pOvl = &m_RecvOverlap;
	pOvl->Offset = OVL_RECEIVE;

	RetValue = WSARecv( m_Socket, &m_in, 1, &insize, &dwFlag, pOvl, NULL );

 	if ( RetValue == SOCKET_ERROR )
	{
		int last_err;
		last_err = WSAGetLastError();

		// 에러 저장...
		SetIOCPLastError(last_err);

		if ( last_err == WSA_IO_PENDING )
		{
			//TRACE("RECV : WSA_IO_PENDING=%d.\n", last_err);
			m_iWsaReadIOPendFlag = 1;
			return 0;
		}
		else if ( last_err == WSAEWOULDBLOCK )
		{
			//TRACE("]RECV[%d] : WSAEWOULDBLOCK=%d.\n", m_Sid, last_err);
			return 0;
		}
		else
		{
			TRACE("]RECV[%d] : ERROR CODE = %d\n", m_Sid, last_err);
			m_SockAliveFlag = 1;

			return -1;
		}
	}

	m_iWsaReadIOPendFlag = 0;

	return RetValue;
}

void CIOCPSocket::Receive(int rBytes)
{
	if ( m_SockAliveFlag != 0 )
		return;

	int RetValue;
	//WSABUF in;
	DWORD insize, dwFlag=0;
	OVERLAPPED *pOvl;

	memset(m_RecvBuf, NULL, MAX_RECV_BUFF_SIZE );

	m_in.len = MAX_RECV_BUFF_SIZE;
	m_in.buf = m_RecvBuf;

	pOvl = &m_RecvOverlap;
	pOvl->Offset = OVL_RECEIVE;

	RetValue = WSARecv( m_Socket, &m_in, 1, &insize, &dwFlag, pOvl, NULL );	// Completion Port에 Associate된 Socket에 버퍼를 건다

 	if ( RetValue == SOCKET_ERROR )
	{
		int last_err;
		last_err = WSAGetLastError();

		// 에러 저장...
		SetIOCPLastError(last_err);

		if ( last_err == WSA_IO_PENDING )
		{
			TRACE("]RECV : WSA_IO_PENDING=%d.\n", last_err);

			m_iWsaReadIOPendFlag = 1;
			return;
		}
		else if ( last_err == WSAEWOULDBLOCK )
		{
			return;
		}
		else
		{
			TRACE("]RECV : ERROR CODE = %d\n", last_err);
			m_SockAliveFlag = 1;
		}
	}
}

BOOL CIOCPSocket::AsyncSelect( long lEvent )
{
	int retEventResult;

	retEventResult = WSAEventSelect( m_Socket, m_hSockEvent, lEvent );

	return ( !retEventResult );
}

BOOL CIOCPSocket::SetSockOpt( int nOptionName, const void* lpOptionValue, int nOptionLen, int nLevel )
{
	int retValue;
	retValue = setsockopt( m_Socket, nLevel, nOptionName, (char *)lpOptionValue, nOptionLen );

	return ( !retValue );
}

BOOL CIOCPSocket::ShutDown( int nHow )
{
	int retValue;
	retValue = shutdown( m_Socket, nHow );

	return ( !retValue );
}

void CIOCPSocket::IOCP_OnClose( int nErrorCode )
{
	if ( m_Socket != INVALID_SOCKET )
	{
		closesocket( m_Socket );
		m_Socket = INVALID_SOCKET;
	}
}

void CIOCPSocket::IOCP_Close()
{
	// 소켓에 한번 Close 신호를 보냈으면 다시 보내지 못하게...
	if ( m_SockAliveFlag == -1 ) return;

	// IKING 2002.6.29
	EnterCriticalSection(&m_CS_CloseTime);
	if ( m_SockAliveFlag == -1 )
	{
		LeaveCriticalSection(&m_CS_CloseTime);
		return;
	}
	// 소켓을 죽은 상태로...
	m_SockAliveFlag = -1;
	LeaveCriticalSection(&m_CS_CloseTime);

	if ( m_Socket != INVALID_SOCKET )
	{
		closesocket(m_Socket);
		m_Socket = INVALID_SOCKET;
	}

}

void CIOCPSocket::StopAction()
{
}

