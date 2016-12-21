#ifndef __CBASESOCKET_H
#define __CBASESOCKET_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "IOCPSocket.h"

/*
class SEND_DATA_STRU : public CObject
{
public:
	BYTE *m_pData;
	int m_nDataLength;
	int m_sid;

public:
	SEND_DATA_STRU()
	{
		m_pData = NULL;
		m_nDataLength = 0;
		m_sid = -1;
	};
	SEND_DATA_STRU(int len, BYTE *pD, int sid)
	{
		m_pData = pD;
		m_nDataLength = len;
		m_sid = sid;
	};

	~SEND_DATA_STRU()
	{
		if ( m_pData )
		{
			delete[] m_pData;
			m_pData = NULL;
		}

		m_nDataLength = 0;
		m_sid = -1;
	};
};
*/

struct _SEND_DATA_STRU
{
public:
	BYTE *m_pData;
	int m_nDataLength;
	int m_sid;

public:
	_SEND_DATA_STRU()
	{
		m_pData = NULL;
		m_nDataLength = 0;
		m_sid = -1;
	};
	_SEND_DATA_STRU(int len, BYTE *pD, int sid)
	{
		m_pData = pD;
		m_nDataLength = len;
		m_sid = sid;
	};

	~_SEND_DATA_STRU()
	{
		if ( m_pData )
		{
			delete[] m_pData;
			m_pData = NULL;
		}

		m_nDataLength = 0;
		m_sid = -1;
	};
};

typedef _SEND_DATA_STRU SEND_DATA_STRU;

/////////////////////////////////////////////////////////////////////////////
// CBSocket command target
class CBSocket : public CIOCPSocket
{
// Attributes
public:
	int m_iSidMod;
	int m_ActivatedFlag;
	// 전송 버퍼크기 정의...
	// default value : m_sizeSendBuffer = SOCKET_BUF_SIZE;
	int m_sizeSendBuffer;

	// default value : m_socket_buffer_size_kiro = 8
	int m_socket_buffer_size_kiro;

// Operations
public:
	CBSocket();
	CBSocket( int nBufSize );
	virtual ~CBSocket();

// Overrides
public:
	void ReceiveData(char *pBuf, int nByte);

	int m_Type;
	BOOL m_SockFlag;
	char m_pBuf[SOCKET_BUF_SIZE+1];
	int m_BufHead, m_BufTail, m_BufCount;

	BOOL IsSocketAlive() { return m_SockFlag; };
	int B_Send( int length, char* pBuf);
	int DxSend(int length, char* pBuf);

	virtual int Init(int bufCreateFlag = 0);
	virtual void SessionLogOut();
	virtual int SockCloseProcess(int nError = 0 );
	virtual int SocketDisConnect();

	void ParseCommand(int rBytes);
	int RecycleRead();
	void B_SoftClose();
	void B_Close();
	int PostSendData();
	void SetIOPendingEnableFlag(int flag)
	{
		if (flag == TRUE)
			m_ioPendingEnableFlag = 1;
		else
			m_ioPendingEnableFlag = 0;
	};
	int GetIOPendingEnableFlag()
	{
		if (m_ioPendingEnableFlag == 1)
			return TRUE;

		return FALSE;
	};

	int SendSockCloseProcess(int nError = 0 );
	void B_OnClose(int nErrorCode);
	void B_OnSend(int nErrorCode);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBSocket)
	public:
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CBSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
