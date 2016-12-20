///////////////////////////////////////////////////////////////////////////////
// SSocket.h 
//
#ifndef __SSOCKET_H
#define __SSOCKET_H

#include "Cbsocket.h"
#include "IOCPSocket.h"

class CIOCPBASE;
class COM;

/////////////////////////////////////////////////////////////////////////////
// CJSocket command target

class CSSocket : public CBSocket
{
// Attributes
public:
	int m_SNumber;
	int m_ReConnectFlag;
	int m_GameType;
	int m_GamePort;
	int m_DisconnectedCount;
	char m_GameName[50];
	char m_GameMsg[50];

// Operations
public:
	CSSocket( CIOCPBASE *pIocpbase = NULL );
	virtual ~CSSocket();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

public:
	void SoftClose();
	void AutomataServer(char *pSBuf, int nByte);
	void ReceiveData(char *pBuf, int nByte);

	int Send( int length, char* pBuf);
	int Send( char* pBuf, int length );
	int Init( int bufCreateFlag = 0 );
	int RecycleRead();
	void StopAction();
	int AcceptProcess();
	int SockCloseProcess(int nError=0);
	int SocketDisConnect();

	BOOL GetPeerName( CString& addr, unsigned int& port);
	void ProcessData();

// Implementation
protected:

};

#endif
