#ifndef __CBASESOCKET_H
#define __CBASESOCKET_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "IOCPSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CBSocket command target
class CBSocket : public CIOCPSocket
{
// Attributes
public:
	int m_iSidMod;
	int m_ActivatedFlag;
	int m_socket_buffer_size_kiro;

// Operations
public:
	CBSocket();
	CBSocket( int nBufSize );
	virtual ~CBSocket();

// Overrides
public:
	int m_Type;
	BOOL m_SockFlag;
	char m_pBuf[SOCKET_BUF_SIZE+1];
	int m_BufHead, m_BufTail, m_BufCount;

	BOOL IsSocketAlive() { return m_SockFlag; };
	int Send( int length, char* pBuf);
	int DxSend(int length, char* pBuf);
	virtual int Init(int bufCreateFlag = 0);

	void ParseCommand(int rBytes);
	virtual void ReceiveData(char *pBuf, int nByte);
	int RecycleRead();
	void Close();
	void SoftClose();

	virtual int SockCloseProcess(int nError = 0 );
	virtual int SendSockCloseProcess(int nError = 0 );
	virtual int SocketDisConnect();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnSend(int nErrorCode);
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
