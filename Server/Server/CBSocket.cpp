///////////////////////////////////////////////////////////////////////////////
// CBase Socket Class define Part : implementation file 
//
#include "stdafx.h"
#include "SCDefine.h"
#include "Cbsocket.h"
#include "Poolbase.h"
#include "IocpBase.h"
#include "SockDataList.h"


CBSocket::CBSocket()
{
	m_SockFlag = FALSE;
	m_iSidMod = 0;

	m_BufHead = 0;
	m_BufTail = 0;
	m_BufCount = 0;

	m_sizeSendBuffer = SOCKET_BUF_SIZE;	// SERVER 는 20 KBYTE.

	m_socket_buffer_size_kiro = 32;

	m_pIocpBase = NULL;
}

CBSocket::CBSocket(int nBufSize )
{
	m_SockFlag = FALSE;
	m_iSidMod = 0;

	m_BufHead = 0;
	m_BufTail = 0;
	m_BufCount = 0;

	if ( nBufSize == -1 ) 
		m_sizeSendBuffer = SOCKET_BUF_SIZE;	// SERVER 는 20 KBYTE.
	else
		m_sizeSendBuffer = nBufSize;

	m_socket_buffer_size_kiro = 32;

	m_pIocpBase = NULL;
}

CBSocket::~CBSocket()
{
}

int CBSocket::Init( int bufCreateFlag )
{
	m_SockFlag = TRUE;

	if ( m_pIocpBase )
		m_iSidMod = m_Sid % m_pIocpBase->m_ThreadCount;
	else
		m_iSidMod = 0;

	m_SockAliveFlag = 0;
	m_iWsaReadIOPendFlag = 0;
	m_iWsaWriteIOPendFlag = 0;
	m_iWsaWouldBlockFlag = 0;
	m_nIoPendingCount = 0;

	m_BufHead = 0;
	m_BufTail = 0;
	m_BufCount = 0;

	m_ActivatedFlag = 0;

	return 1;
}

int CBSocket::DxSend(int length, char* pBuf)
{
	if ( m_SockFlag != 1 ) return -2;

	long ret, nSendBufferData;
	
	nSendBufferData = length;

	ret = CIOCPSocket::IOCP_Send( pBuf, nSendBufferData, 0 );
		
	if ( ret == -2 ) // 죽은 소켓...
	{
		m_SockFlag = 0;
		return -1;
	}
	else if ( ret == 0 || ret == SOCKET_ERROR )
	{
		int err = GetIOCPLastError();

		if ( err == WSAEWOULDBLOCK )
		{
			m_SockFlag = 0;
			return -1;
		}

		if ( err == WSA_IO_PENDING )
		{
			m_SockFlag = 0;
			return -1;
		}
		
		switch ( err )
		{
			case WSAENETDOWN:
			case WSAEINPROGRESS:
			case WSAENETRESET:
			case WSAENOBUFS:
			case WSAESHUTDOWN:
				break;

			case WSAENOTCONN:
			case WSAECONNABORTED:
				break;

			case WSAENOTSOCK:
			case WSAECONNRESET:
				break;
		};

		m_SockFlag = 0;
		return -1;
	}

	m_nIoPendingCount = 0;

	return nSendBufferData;
}

int CBSocket::B_Send(int length, char *pBuf)
{
	if ( m_SockFlag != 1 ) return -1;

	int retValue;
	retValue = DxSend( length, pBuf );
	if ( retValue == -1 && m_SockFlag != 1 )
	{
		SendSockCloseProcess();
		return -1;
	}

	return length;
}

void CBSocket::B_OnSend( int nErrorCode ) 
{
	if ( m_SockFlag != 1 ) return;

	if ( m_iWsaWouldBlockFlag == 0 && m_iWsaWriteIOPendFlag == 0 ) return;

	CIOCPSocket::IOCP_OnSend(nErrorCode);
}

void CBSocket::B_OnClose(int nErrorCode) 
{
	CIOCPSocket::IOCP_OnClose(nErrorCode);
}

void CBSocket::ParseCommand(int rBytes)
{
	char pBuf[SOCKET_BUF_SIZE+1];

	if ( rBytes )
	{
		m_rByte = rBytes;
		memcpy( pBuf, m_RecvBuf, m_rByte );
		ReceiveData( pBuf, m_rByte );
	}
}

void CBSocket::ReceiveData(char *pBuf, int nByte)
{
	if ( m_SockFlag != 1 ) return;

	if ( nByte == 0 ) return;

	BYTE *pdata = NULL;
	try
	{
		pdata = new BYTE[nByte+1];
	}
	catch(...)
	{
		TRACE("]MEMORY ALLOC STEP1 FAILED AND RETRY...\n");

		try
		{
			pdata = new BYTE[nByte+1];
		}
		catch(...)
		{
			TRACE("]MEMORY ALLOC STEP1 FAILED AND IGNORE...\n");
			return;
		}
	}

	memcpy( pdata, pBuf, nByte ); 
	WAIT_RECV_DATA *wrd;
	try
	{
		wrd = new WAIT_RECV_DATA;
	}
	catch(...)
	{
		TRACE("]MEMORY ALLOC STEP2 FAILED AND RETRY...\n");

		try
		{
			wrd = new WAIT_RECV_DATA;
		}
		catch(...)
		{
			TRACE("]MEMORY ALLOC STEP2 FAILED AND RETURN...\n");

			if ( pdata )
				delete pdata;

			return;
		}
	}

	wrd->pData = pdata;
	wrd->dcount = nByte;
	wrd->usn = m_Sid;
	wrd->m_Type = m_Type;

	// IKING 2002.7.3
	EnterCriticalSection(&m_pIocpBase->m_CS_ReceiveData[m_iSidMod]);
	m_pIocpBase->m_pRecvData[m_iSidMod][m_pIocpBase->m_nHeadPtr[m_iSidMod]] = wrd;
	if ( m_pIocpBase->m_nHeadPtr[m_iSidMod] >= WAIT_RECV_DATA_BUFFER-1)
		m_pIocpBase->m_nHeadPtr[m_iSidMod] = 0;
	else
	{
		m_pIocpBase->m_nHeadPtr[m_iSidMod]++;
	}
	LeaveCriticalSection(&m_pIocpBase->m_CS_ReceiveData[m_iSidMod]);
}

int CBSocket::RecycleRead()
{
	return CIOCPSocket::IOCP_RecycleRead();
}

int CBSocket::SockCloseProcess(int nError)
{
	B_Close();
	return 1;
}

int CBSocket::SendSockCloseProcess(int nError)
{
	B_SoftClose();
	return 1;
}

void CBSocket::B_Close()
{
	if ( m_pIocpBase == NULL )
	{
		m_SockFlag = FALSE;
		m_ActivatedFlag = 1;
		return;
	}
	if ( m_SockAliveFlag == -1 ) return;

	// IKING 2002.6.29
	EnterCriticalSection(&m_CS_CloseTime);
	if ( m_SockAliveFlag == -1 )
	{
		LeaveCriticalSection(&m_CS_CloseTime);
		return;
	}
	LeaveCriticalSection(&m_CS_CloseTime);

	m_SockFlag = FALSE;
	m_ActivatedFlag = 1;

	CIOCPSocket::IOCP_Close();

	RHANDLE *pHandle;
	pHandle = m_pIocpBase->m_pPBM->m_pResources->GetHandle( m_Sid );
	if ( pHandle )
		m_pIocpBase->m_pPBM->ReleaseResource(pHandle);
	else
	{
		TRACE("]Iocp closed : sid[%d] Handle Error...\n", m_Sid );
	}
}

int CBSocket::PostSendData()
{
	if ( m_SockFlag != 1 ) return -2;
	if ( m_pIocpBase == NULL ) return -1;

	SetEvent(m_pIocpBase->m_CreateSignalEvent);

	return 0;
}

int CBSocket::SocketDisConnect()
{
	return 1;
}

void CBSocket::B_SoftClose()
{
	if ( m_pIocpBase == NULL ) return;
	if ( m_SockAliveFlag == -1 ) return;

	// IKING 2002.6.29
	EnterCriticalSection(&m_CS_CloseTime);
	if ( m_SockAliveFlag == -1 )
	{
		LeaveCriticalSection(&m_CS_CloseTime);
		return;
	}
	LeaveCriticalSection(&m_CS_CloseTime);

	OVERLAPPED		*pOvl;
	pOvl = &m_RecvOverlap;
	pOvl->Offset = OVL_RECEIVE;

	int retValue;
	retValue = PostQueuedCompletionStatus( m_pIocpBase->m_hIOCPort, (DWORD)0, (DWORD)m_Sid, pOvl );
	if ( !retValue )
	{
		int errValue;
		errValue = GetLastError();
		TRACE("]PostQueuedCompletionStatus Error := %d\n", errValue);

		switch ( errValue )
		{
		case ERROR_IO_PENDING:
			TRACE(">>PQCS : ERROR_IO_PENDING\n");
			break;

		default :
			break;
		};

		return;
	}
}

void CBSocket::SessionLogOut()
{
	return;
}
