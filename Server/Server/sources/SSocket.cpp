///////////////////////////////////////////////////////////////////////////////
// CSSocket.cpp : implementation file
//
#include "stdafx.h"
#include "scdefine.h"
#include "Poolbase.h"
#include "Iocpbase.h"
#include "Sockdatalist.h"
#include "SSocket.h"
#include "resource.h"
#include "ServerDlg.h"
#include "Mcommon.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void myputs(int x,int y,char* str);

extern int socket_buffer_size_kiro; // = 32;
extern int cur_svr_connected_pos;

// 전송 버퍼크기 정의...
extern long sizeServerBuffer; // = SOCKET_BUF_SIZE*3;	// SERVER 는 30 KBYTE.
extern long sizeUserBuffer; // = SOCKET_BUF_SIZE*3;		// USER 는 30 KBYTE.
extern int data_overflow_flag;
extern CServerDlg *g_pMainDlg;
extern HANDLE g_CreateSignalEvent;

/////////////////////////////////////////////////////////////////////////////
// CJSocket

CSSocket::CSSocket(CIOCPBASE *pIocpbase)
{
	m_pIocpBase = pIocpbase;
}

CSSocket::~CSSocket()
{
}

int CSSocket::Init( int bufCreateFlag )
{
	CBSocket::Init( bufCreateFlag );

	m_SNumber = m_Sid;
	m_DisconnectedCount = 0;
	m_GameName[0] = '\0';
	m_GameMsg[0] = '\0';

	return 1;
}

int CSSocket::Send( char *pBuf, int length )
{
	return Send( length, pBuf );
}

int CSSocket::Send(int length, char* pBuf)
{
	int rv;

	if ( m_SockFlag != 1 ) return -2;

	int index = 0;
	char pTBuf[JS_SOCKET_BUF_SIZE+1];
	BYTE temp, start1, start2;
	MYSHORT len;
	BYTE sum = 1;
	start1 = 0xfe, start2 = 0xff;

	// 패킷 만들기...
	len.i = length;
	if ( length >= JS_SOCKET_BUF_SIZE ) return FALSE;
	
	index = 0;
	pTBuf[index++] = start1;
	pTBuf[index++] = start2;
	pTBuf[index++] = 0x01;
	
	temp = (BYTE) len.b[0];		//	Filter( temp, index);
	pTBuf[index++] = temp;
	sum = sum + temp;
	
	temp = (BYTE) len.b[1];		//	Filter( temp, index);
	pTBuf[index++] = temp;
	sum = sum + temp;
	
	for ( int i = 0; i < len.i; i++ )
	{
		temp = pBuf[i];			//	Filter( temp, index);
		pTBuf[index++] = temp;
		sum = sum + pBuf[i];
	}
	
	pTBuf[index++] = sum;		//	Filter( sum, index);
	pTBuf[index++] = start2;
	pTBuf[index++] = start1;

	rv = CBSocket::B_Send( index, pTBuf );
	
	if ( m_SockFlag == 0 || rv == -2 )
	{
		SoftClose();
		//Close();
		return rv;
	}

	return rv;
}

void CSSocket::OnSend(int nErrorCode) 
{
	if ( m_SockFlag != 1 ) return;

	CBSocket::B_OnSend( nErrorCode );

	if ( m_SockFlag == 0 )
	{
		SoftClose();
		//Close();
	}
}

void CSSocket::StopAction()
{
	return;
}

void CSSocket::OnClose(int nErrorCode) 
{
	CBSocket::B_OnClose(nErrorCode);
}

int CSSocket::AcceptProcess()
{
	return 1;
}

int CSSocket::SockCloseProcess(int nError)
{
	CBSocket::SockCloseProcess();

	return 1;
}

int CSSocket::SocketDisConnect()
{
	SockCloseProcess();

	return 1;
}

BOOL CSSocket::GetPeerName( CString& addr, unsigned int& port )
{
	port = ntohs(m_Addr.sin_port);
	addr = inet_ntoa(m_Addr.sin_addr);

	return TRUE;
}

void CSSocket::AutomataServer(char *pSBuf, int nByte)
{
	char pPhaseBuf[RECEIVE_BUF_SIZE+1];

	if ( m_Socket == INVALID_SOCKET )
		return;

	if ( IsSocketAlive() != TRUE )
		return;

	for ( long j = 0; j < nByte; j++ )
	{
		if ( m_BufCount >= RECEIVE_BUF_SIZE - 1 )
		{
			m_BufHead = 0;
			m_BufTail = 0;
			m_BufCount = 0;
			return;
		}

		m_BufCount++;
		m_pBuf[m_BufHead] = pSBuf[j];
		BufInc(m_BufHead);
	}
	//

	int	tail = m_BufTail, head = m_BufHead;
	char *pBuf = m_pBuf;
	MYSHORT	length;
	BYTE sum;

	while ( (m_BufHead + RECEIVE_BUF_SIZE - m_BufTail) % RECEIVE_BUF_SIZE != 0 )
	{
		sum = PROTOCOL_VER;

		if ( (BYTE)pBuf[tail] != J_PACKET_START1 )
		{
			BufInc(m_BufTail);
			m_BufCount--;
			tail = m_BufTail; if (head == tail) return;
			continue;
		}
		BufInc(tail); if (head == tail) return;

		if ( (BYTE)pBuf[tail] != J_PACKET_START2 )
		{
			BufInc( m_BufTail );
			m_BufCount--;
			tail = m_BufTail; if (head == tail) return;
			continue;
		}
		BufInc(tail); if (head == tail) return;

		if ( (BYTE)pBuf[tail] != PROTOCOL_VER )		
		{
			BufInc(m_BufTail);
			m_BufCount--;
			tail = m_BufTail; if (head == tail) return;
			continue;
		}
		
		BufInc(tail); if (head == tail) return;

		length.b[0] = pBuf[tail]; sum += (BYTE)length.b[0];
		BufInc(tail); if (head == tail) return;
		length.b[1] = pBuf[tail]; sum += (BYTE)length.b[1];
		BufInc(tail); if (head == tail) return;
		if ( length.i > RECEIVE_BUF_SIZE || length.i <= 0 )
		{
			m_BufCount = 0;
			m_BufHead = 0;
			m_BufTail = 0;
			return;
		}
int i;
		for ( i = 0; i < length.i; i++ )
		{
			pPhaseBuf[i] = pBuf[tail];
			sum += pPhaseBuf[i];
			BufInc(tail); if ( head == tail ) return;
		}
		pPhaseBuf[i] = (BYTE) 0;

		if ( (BYTE)pBuf[tail] != sum )
		{
			BufInc( m_BufTail);
			m_BufCount--;
			tail = m_BufTail; if (head == tail) return;
			continue;
		}
		BufInc(tail); if ( head == tail ) return;

		if ( (BYTE)pBuf[tail] != J_PACKET_END1 )
		{
			BufInc(m_BufTail);
			m_BufCount--;
			tail = m_BufTail; if (head == tail) return;
			continue;
		}
		BufInc(tail); if ( head == tail ) return;

		if ( (BYTE)pBuf[tail] != J_PACKET_END2 )
		{
			BufInc(m_BufTail);
			m_BufCount--;
			tail = m_BufTail; if (head == tail) return;
			continue;
		}
		BufInc(tail);

		m_BufTail = tail;
		
		if ( head == tail )
			m_BufCount = 0;
		else if ( head > tail )
		{
			m_BufCount = head - tail;
		}
		else
		{
			m_BufCount = head + (SOCKET_BUF_SIZE-tail);
		}
		
		switch(m_Type)
		{
		case SOCKET_FOR_DBSERVER:	//  DB 서버인 경우....
			g_pMainDlg->DBjobPhasor( this, pPhaseBuf, length.i );
			break;

		case SOCKET_FOR_SERVER:	// Zone 서버인 경우
			g_pMainDlg->BridgeServerPhasor( this, pPhaseBuf, length.i );
			break;
		}

		if (head == tail)  return;
	}
}

void CSSocket::SoftClose()
{
	CBSocket::B_SoftClose();
}

//