///////////////////////////////////////////////////////////////////////////////
// I/O COMPLETION PORT
//

#ifndef _IOCOMPLETIONSOCKET_H
#define _IOCOMPLETIONSOCKET_H

//#include "..\common\jangdef.h"
#define SOCKET_BUF_SIZE	10000
#define MAX_RECV_BUFF_SIZE SOCKET_BUF_SIZE
//#define MAX_SEND_BUFF_SIZE	(SOCKET_BUF_SIZE*10)	// (1024*8)

#define OVL_RECEIVE				0X01
#define OVL_SEND				0X02
#define OVL_CLOSE				0X03

//	State Value
//
#define STATE_ACCEPTED			0X01
#define STATE_CONNECTED			0X02
#define STATE_DISCONNECTED		0X03
#define STATE_CONNECT			0X04

#define receives				0
#define sends					1
#define both					2 

#define USER_TYPE				1
#define SERVER_TYPE				2

#define UM_PROCESS_REMOVESOCKET	30000
#define UM_PROCESS_SOCKETACCEPT	30001

class CIOCPBASE;

class CIOCPSocket
{
protected:
	int m_ioPendingEnableFlag;
	int m_SockAliveFlag;
	DWORD m_IocpLastError;
	WSABUF m_in;
	WSABUF m_out;
	char m_RecvBuf[MAX_RECV_BUFF_SIZE+1];

public:
	HANDLE m_hSockEvent;
	int m_iWsaReadIOPendFlag;
	int m_iWsaWriteIOPendFlag;
	int m_iWsaWouldBlockFlag;
	int m_nIoPendingCount;

	int m_rByte;
	CString m_sConnectAddress;
	CIOCPBASE *m_pIocpBase;
	int m_Sid;
	SOCKET m_Socket;
	int m_State;
	struct sockaddr_in m_Addr;
	OVERLAPPED m_RecvOverlap;
	OVERLAPPED m_SendOverlap;
	CRITICAL_SECTION m_CS_CloseTime;

public:
	CIOCPSocket();
	virtual ~CIOCPSocket();

	long IOCP_Send(char* pBuf, long length, int dwFlag = 0);
	void IOCP_OnSend(int nErrorCode);
	void Receive(int rBytes);
	void IOCP_OnClose( int nErrorCode );
	void IOCP_Close();
	int IOCP_RecycleRead();

	virtual void StopAction();

	BOOL Create( UINT nSocketPort = 0,
				 int nSocketType = SOCK_STREAM, 
				 long lEvent = FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE,
				 LPCTSTR lpszSocketAddress = NULL );

	BOOL Connect( LPCTSTR lpszHostAddress, UINT nHostPort );

	BOOL AsyncSelect( long lEvent = FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE );
	BOOL SetSockOpt( int nOptionName, const void* lpOptionValue, int nOptionLen, int nLevel = SOL_SOCKET );
	BOOL ShutDown( int nHow = sends );

	DWORD GetIOCPLastError() { return m_IocpLastError; };
	void SetIOCPLastError(DWORD le) { m_IocpLastError = le; };
	void SetIocpBasePtr(CIOCPBASE *iocpbptr) { m_pIocpBase = iocpbptr; };

};

#endif
