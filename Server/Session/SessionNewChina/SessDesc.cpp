// SessDesc.cpp: implementation of the CSessDesc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Session.h"
#include "SessionCom.h"
#include "Mcommon.h"
#include "Iocp.h"
#include "../LibsIncs/SockDataList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BOARD_TYPE_SESSION

CSessDesc* GetUserServerSocket( CIOCPBASE *pIocpBase );
CSessDesc* GetUserSocketUid( int uid );
CSessDesc* GetUserServerSocketUid( int uid );

extern CIOCP<CSessDesc> m_UserBase;
extern CIOCP<CSessDesc> m_UserServerBase;
extern CIOCP<CSessDesc> m_ServerBase;
extern CSessionCom	*g_pCom;

///////////////////////////////////////////////////////////////////////////////
// PROGRAM CODE START
//
CSessDesc::CSessDesc()
{
	m_pCom = NULL;
	m_hThread = NULL;
	m_dwTimeOut = 0;

	m_buf = (char*)m_msg.GetBuf();
	m_nRdCnt = 0;
	m_nState = stateNone;

	// IKING 1999.1.
	m_bPay = 1;
	m_LinkedFlag = 0;
	m_nLinkedSid = -1;
	pLinkedDesc = NULL;
	//

	m_iLoginFlag = 0;		// zi_gi
	m_bDisplay = 0;


	m_bUM = FALSE;
}

CSessDesc::~CSessDesc()
{
	Close ();
}

int CSessDesc::Link(CBaseCom* pCom, int nType, LPCTSTR lpszAddr, int nPort)
{
	CSessDesc *pSessDesc;
	CMsg msgSend;

	m_nState = nType;
	m_strLinkAddr = lpszAddr;
	m_nLinkPort = nPort;

	pSessDesc = GetUserServerSocket( &m_UserServerBase );

	if ( pSessDesc == NULL )
	{
		switch ( m_nState )
		{
			case CSessDesc::stateDown :
				msgSend.ID (SM_DOWN_ACK) << (BYTE)0;
				Say(msgSend);
				break;
			case CSessDesc::stateStart :
				msgSend.ID (SM_GAME_ACK) << (BYTE)0;
				Say(msgSend);
				break;
		}
		return 1;
	}

	if ( !pSessDesc->Create() )
	{
		switch ( m_nState )
		{
			case CSessDesc::stateDown :
				msgSend.ID (SM_DOWN_ACK) << (BYTE)0;
				Say(msgSend);
				break;
			case CSessDesc::stateStart :
				msgSend.ID (SM_GAME_ACK) << (BYTE)0;
				Say(msgSend);
				break;
		}

		pSessDesc->SoftClose();
		return 1;
	}

	if ( !pSessDesc->Connect( lpszAddr, nPort ) )
	{
		switch ( m_nState )
		{
			case CSessDesc::stateDown :
				msgSend.ID (SM_DOWN_ACK) << (BYTE)0;
				Say(msgSend);
				break;
			case CSessDesc::stateStart :
				msgSend.ID (SM_GAME_ACK) << (BYTE)0;
				Say(msgSend);
				break;
		}

		pSessDesc->SoftClose();
		return 1;
	}

	// m_pTBuf 생성...
	pSessDesc->Init( 0 );
	//

	pLinkedDesc = pSessDesc;
	m_nLinkedSid = pSessDesc->m_Sid;
	m_LinkedFlag = 1;

	pSessDesc->pLinkedDesc = this;
	pSessDesc->m_nLinkedSid = m_Sid;
	pSessDesc->m_LinkedFlag = 1;

	pSessDesc->m_State = STATE_CONNECTED;
	pSessDesc->m_dwTimeOut = pCom->m_dwTimeOut;
	pSessDesc->m_hThread = NULL;

	switch ( m_nState )
	{
	case CSessDesc::stateDown :
		msgSend.ID (SM_DOWN_ACK) << (BYTE)1;
		Say(msgSend);
		break;
	case CSessDesc::stateStart :
		msgSend.ID (SM_GAME_ACK) << (BYTE)1;
		Say(msgSend);
		m_nState = CSessDesc::stateGame;
		break;
/*
	case CSessDesc::stateGame:
		{
			char packet[50];
			BYTE temp, start1, start2;
			MYSHORT len;
			BYTE sum = 1;
			int index = 0, length;
			char pBuf[12+1];

			start1 = 0xfe, start2 = 0xff;
			strcpy(pBuf, (LPCTSTR)m_strUserID );

			length = m_strUserID.GetLength();
			len.i = length+8;
			
			packet[index++] = start1;
			packet[index++] = start2;
			packet[index++] = 0x01;
			
			temp = (BYTE) len.b[0];		//	Filter( temp, index);
			packet[index++] = temp;
			sum = sum + temp;
			
			temp = (BYTE) len.b[1];		//	Filter( temp, index);
			packet[index++] = temp;
			sum = sum + temp;

			temp = 0xaa;			//	Filter( temp, index);
			packet[index++] = temp;
			sum = sum + temp;

			temp = 0x55;			//	Filter( temp, index);
			packet[index++] = temp;
			sum = sum + temp;

			temp = 0xff;			//	Filter( temp, index);
			packet[index++] = temp;
			sum = sum + temp;
			
			for ( int i = 0; i < length; i++ )
			{
				temp = pBuf[i];			//	Filter( temp, index);
				packet[index++] = temp;
				sum = sum + pBuf[i];
			}

			temp = 0x00;			//	Filter( temp, index);
			packet[index++] = temp;
			sum = sum + temp;

			// 유료/무료 모드...
			//{
			len.i = m_bPay;

			temp = (BYTE) len.b[0];		//	Filter( temp, index);
			packet[index++] = temp;
			sum = sum + temp;
			
			temp = (BYTE) len.b[1];		//	Filter( temp, index);
			packet[index++] = temp;
			sum = sum + temp;
			//}

			temp = 0x55;			//	Filter( temp, index);
			packet[index++] = temp;
			sum = sum + temp;

			temp = 0xaa;			//	Filter( temp, index);
			packet[index++] = temp;
			sum = sum + temp;
			
			packet[index++] = sum;
			//	Filter( sum, index);
			packet[index++] = start2;
			packet[index++] = start1;

			::send(pDes->m_sockServer, packet, index, 0);
		}
		break;
*/
	};

	return 0;
}

void CSessDesc::Unlink()
{
	m_nState = stateNone;
	m_nRdCnt = 0;
	m_LinkedFlag = 0;

	m_nLinkedSid = -1;
}

BOOL CSessDesc::CheckMsg()
{
	if (m_nRdCnt < 4)
		return FALSE;

	int nSize = m_msg.GetSize();
	if (DEFAULT_SIZE < nSize)
	{
		m_msg.Clear();
		m_nRdCnt = 0;
		return FALSE;
	}

	if (m_nRdCnt < nSize)
	{
		// 오류 신호 정정하기..
		// 기준 ALIVE 신호...
		if ( m_buf[0] < 0x80 )
		{
			int i, c = 0;
			for ( i = 0; i < m_nRdCnt; i++ )
			{
				if ( m_buf[c++] == 0x00 )
					break;
			}

			if ( i == m_nRdCnt )
			{
				m_msg.Clear ();
				m_nRdCnt = 0;
				return FALSE;
			}

			m_msg.Clear ();

			m_nRdCnt -= c;
			if (m_nRdCnt > 0)
				memmove (m_buf, m_buf + c, m_nRdCnt);
			else
				m_nRdCnt = 0;
		}
		//

		return FALSE;
	}

	return TRUE;
}

int CSessDesc::Hear(BYTE *pData, int rBytes)
{
	if ( m_SockFlag != 1 )
		return ERROR_CLIENTRECV;

	if ( m_Socket == INVALID_SOCKET )
		return ERROR_INVALID;

	if ( rBytes )
	{
		if ( (m_nRdCnt+rBytes) < MAX_BUF )
		{
			memcpy( (m_buf+m_nRdCnt), pData, rBytes );
			m_nRdCnt += rBytes;
		}
	}

	return 0;
}

void CSessDesc::Send(int length, char *pBuf)
{
	if ( m_SockFlag != 1 ) return;

	int rv;

	rv = CBSocket::Send( length, pBuf );
	
	if ( m_SockFlag == 0 || rv == -2 )
	{
		//SockCloseProcess();
		return;
	}
}

int CSessDesc::Say( CMsg& msg )
{
	if ( m_Socket == INVALID_SOCKET )
		return ERROR_INVALID;

	Send( msg.GetSize(), (char *)msg.GetBuf() );

	return 0;
}

void CSessDesc::Copy()
{
	int nSize = m_msg.GetSize ();

	m_msg.Clear ();
	m_nRdCnt -= nSize;
	if (m_nRdCnt > 0)
		memmove (m_buf, m_buf + nSize, m_nRdCnt);
	else
		m_nRdCnt = 0;

}

int CSessDesc::Init( int bufCreateFlag )
{
	m_pCom = g_pCom;

	CBSocket::Init( bufCreateFlag );

	m_HeartBitCount = 0;
	m_SNumber = m_Sid;

	m_bLogOutFlag = FALSE;
	m_nRdCnt = 0;
	m_nState = stateNone;

	// IKING 1999.1.
	m_bPay = 1;
	m_LinkedFlag = 0;
	m_nLinkedSid = -1;
	pLinkedDesc = NULL;
	m_UserStatus = USER_CONNECTED;
	m_ConnectTimeTick = GetTickCount();
	m_bConnectFlag = TRUE;
	//

	return m_pCom->OnOpenSession(this);
}

void CSessDesc::ReceiveData(char *pBuf, int nByte)
{
	if ( m_SockFlag != 1 ) return;
	if ( nByte == 0 ) return;

	int nError;

	if ( m_Type == SOCKET_FOR_USER )
	{
		nError = Hear((BYTE *)pBuf, nByte);
		if ( nError )
		{
			SoftClose();
			return;
		}

		m_dwLastTime = ::GetTickCount();

		if ( !m_LinkedFlag )
		{
			while ( !nError && CheckMsg() )
			{
				nError = m_pCom->OnReceiveMsg( this, m_msg );
				if ( nError )
					SoftClose();
				else if ( GetState() == CSessDesc::stateNone || GetState() == CSessDesc::stateDown )
					Copy();
			}
		}
		else
		{
			if ( pLinkedDesc )
			{
				pLinkedDesc->Send( m_nRdCnt, m_buf );
				m_nRdCnt = 0;
			}
		}
	}
	else if ( m_Type == SOCKET_FOR_USERSERVER )
	{
		nError = Hear((BYTE *)pBuf, nByte);
		if ( nError )
		{
			SoftClose();
			return;
		}

		m_dwLastTime = ::GetTickCount();

		if ( !m_LinkedFlag )
		{
			while ( !nError && CheckMsg() )
			{
				nError = m_pCom->OnReceiveMsg( this, m_msg );
				if ( nError )
					SoftClose();
				else if ( GetState() == CSessDesc::stateNone || GetState() == CSessDesc::stateDown )
					Copy();
			}
		}
		else
		{
			if ( pLinkedDesc )
			{
				pLinkedDesc->Send( m_nRdCnt, m_buf );
				m_nRdCnt = 0;
			}
		}
	}
	else if ( m_Type == SOCKET_FOR_SERVER )
	{
		nError = Hear( (BYTE *)pBuf, nByte );
		if ( nError )
		{
			SoftClose();
			return;
		}

		m_dwLastTime = ::GetTickCount();

		while ( !nError && CheckMsg() )
		{
			nError = m_pCom->OnReceiveMsg( this, m_msg );
			if ( nError )
				SoftClose();
			else if ( GetState() == CSessDesc::stateNone || GetState() == CSessDesc::stateDown )
				Copy();
		}
	}
}

int CSessDesc::SockCloseProcess(int nError)
{
	if ( m_nState == -1 ) return 0;

	if ( m_Type == SOCKET_FOR_USER )
	{
		// 서버측 소켓 지우기...
		if ( m_nLinkedSid >= 0 ) 
		{
			if ( pLinkedDesc )
				pLinkedDesc->SoftClose();
		}

		// 클라이언트측 소켓 지우기...
		if ( nError == ERROR_UNLINK )
			nError = ERROR_CLIENTRECV;

		// 클라이언트측 소켓 지우기...
		m_pCom->OnCloseSession ( this, nError );
	}
	else if ( m_Type == SOCKET_FOR_USERSERVER )
	{
		// 클라이언트측 소켓 지우기...
		if ( m_nLinkedSid >= 0 ) 
		{
			if ( pLinkedDesc && m_pCom )
			{
				int userstatus;
				userstatus = ((CSessDesc *)pLinkedDesc)->m_nState;

				if ( nError == ERROR_UNLINK || nError == 0)
					nError = ERROR_CLIENTRECV;

				m_pCom->OnCloseSession ( (CSessDesc *)pLinkedDesc , nError );

				// 서치 구조에서 지우기...
				if ( userstatus != CSessDesc::stateDown ) 
					pLinkedDesc->SoftClose();
			}
		}
	}
	else
	{
		if ( m_pCom == NULL )
		{
			CBSocket::SockCloseProcess();

			m_msg.Clear();
			m_nRdCnt = 0;
			m_dwTimeOut = 0;
			m_nState = -1;
			return 1;
		}

		if ( ((CSessionCom *)m_pCom)->m_pDesUM == this )
		{
			m_UserBase.m_bAcceptEnableFlag = FALSE;	

			if ( ((CSessionCom *)m_pCom)->m_pDesUM )
				((CSessionCom *)m_pCom)->m_pDesUM->m_bConnectFlag = FALSE;
		}
		else if ( ((CSessionCom *)m_pCom)->m_pDesGS == this )
		{
			if ( ((CSessionCom *)m_pCom)->m_pDesGS )
				((CSessionCom *)m_pCom)->m_pDesGS->m_bConnectFlag = FALSE;
		}
	}

	// 소켓 지우기...
	CBSocket::SockCloseProcess(nError);

	m_msg.Clear();
	m_nState = -1;
	m_nRdCnt = 0;
	m_dwTimeOut = 0;

	return 1;
}

int CSessDesc::SocketDisConnect()
{
	SockCloseProcess();
	return 1;
}

