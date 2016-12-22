// Session.h : main header file for the SESSION application
//

#if !defined(AFX_SERVER_H__3FB54859_F644_11D1_A521_00A0248552AD__INCLUDED_)
#define AFX_SERVER_H__3FB54859_F644_11D1_A521_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "SMProtocol.h"
#include "UMProtocol.h"
#include "FMProtocol.h"
#include "BProtocol.h"

#include "Database.h"
#include "Recordset.h"
#include "CBSocket.h"
#include "MCommon.h"

#define ERROR_INVALID		1
#define ERROR_CLIENTSEND	2
#define ERROR_CLIENTRECV	3
#define ERROR_SERVERSEND	4
#define ERROR_SERVERRECV	5
#define ERROR_RECVTIMEOUT	6
#define ERROR_SUSPEND		7
#define ERROR_SERVERFULL	8
#define ERROR_DENYOPEN		9
#define ERROR_UNLINK		10

#define ERROR_USER			100

#define	DEFAULT_SIZE		8192
#define	MAX_BUF				8192
#define DUPLICATED_USER		3

#define MAX_NAME_LENGTH		30

class CMsg;
class CSessDesc;
class CBaseCom;

/////////////////////////////////////////////////////////////////////////////
// CMsg:
// See Msg.cpp for the implementation of this class
//

class CMsg : public CObject
{
protected:
	BYTE	m_buf[DEFAULT_SIZE];
	BYTE*	m_pHead;	
	BYTE*	m_pData;	
	WORD	m_nRdOff;
	WORD	m_nWrOff;

public:
	CMsg();
	CMsg(CMsg& msg);
	CMsg(void* pBuf);

	CMsg& ID( WORD id );
	WORD  ID();

	void ReadData (void* pData, int n);
	void WriteData (void* pData, int n);

	void* GetBuf ();
	void SetBuf (BYTE* pBuf);
	WORD GetSize ();
	BOOL IsReadAll ();
	void Copy(void* pBuf);
	void Clear() { m_nRdOff = 0; m_nWrOff = 0; }

// Archive Operators
	CMsg&		operator<<( char		arg );
	CMsg&		operator<<( BYTE		arg );
	CMsg&		operator<<( short		arg );
	CMsg&		operator<<( WORD		arg );
	CMsg&		operator<<( int			arg );
	CMsg&		operator<<( DWORD		arg );
	CMsg&		operator<<( LPCTSTR		arg );

	CMsg&		operator>>( char&		arg );
	CMsg&		operator>>( BYTE&		arg );
	CMsg&		operator>>( short&		arg );	
	CMsg&		operator>>( WORD&		arg );	
	CMsg&		operator>>( int&		arg );	
	CMsg&		operator>>( DWORD&		arg );	
	CMsg&		operator>>( CString&	arg );	

	CMsg&		operator=( CMsg&		msg );	
};

/////////////////////////////////////////////////////////////////////////////
// CSessDesc:
// See SessDesc.cpp for the implementation of this class
//

class CSessDesc : public CBSocket
{
public:
	int			m_bConnectFlag;
	int			m_nRdCnt;
	char*		m_buf;
	int			m_nState;
	BYTE		m_bLogin;

public:
	BOOL m_bUM;
	// IKING 2000.1.
	DWORD m_ConnectTimeTick;
	int m_UserStatus;
	int m_bLogOutFlag;
	int m_SNumber;
	int m_LinkedFlag;
	int m_HeartBitCount;
	int m_nLinkedSid;
	CBSocket *pLinkedDesc;
	//

	int m_nLinkPort;
	CString m_strLinkAddr;
	CString m_strUserID;
	CString m_strIPAddr;

	//@@@@@ by zi_gi 02-03-22
	int		m_iLoginFlag;		// 기본 : 0, CurrentUser Table에 Insert : 1, Update ServerIP가 끝났으면 : 2, Duplicated User : 3 
	CString	m_strDupIPAddr;
	BYTE	m_bDisplay;


	// IKING 1999.1.
	int m_bPay;
	//
	int m_vServerNumber;
	enum { stateNone, stateDown, stateStart, stateGame };
	enum { CLIENT, SERVER };

	DWORD		m_dwLastTime;
	DWORD		m_dwTimeOut;
	HANDLE		m_hThread;
	CBaseCom	*m_pCom;
	CMsg		m_msg;

	CSessDesc();
	~CSessDesc();

	void ReceiveData(char *pBuf, int nByte);
	int SockCloseProcess(int nError = 0);
	int SocketDisConnect();

	int Link(CBaseCom* pCom, int nType, LPCTSTR lpszAddr, int nPort);
	void Unlink();
	int IsLinked() { return m_LinkedFlag; }

	BOOL IsValid()
	{
		return ( m_Socket != INVALID_SOCKET);
	};

	int GetState () { return m_nState; }

	BOOL IsTimeOut (DWORD dwCurTime) 
	{ 
		return ( m_dwTimeOut && m_dwTimeOut < dwCurTime - m_dwLastTime );
	}

	BOOL CheckMsg();
	void Copy();
	int Hear(BYTE *pData, int rBytes);
	int Say(CMsg& msg);

	// IKING 2000.1.
	void Send(int length, char* pBuf);
	int Init( int bufCreateFlag = 0 );
	//
};

/////////////////////////////////////////////////////////////////////////////
// CBaseCom:
// See Session.cpp for the implementation of this class
//

class CBaseCom
{
protected:
	HKEY		m_hKey;

public :
	CString		m_strGameID;
	CString		m_strUserID;
	CString		m_strPassword;
	BOOL		m_fSuspend;
	int			m_nServerID;
	CString		m_strServerName;
	CString		m_strServerAddr;
	int			m_nServerPort;
	int			m_nCapacity;
	DWORD		m_dwLastTime;
	DWORD		m_dwTimer;
	DWORD		m_dwTimeOut;

protected:
	BOOL GetConfigString( LPCTSTR lpszKey, LPCTSTR lpszName, CString& strValue );
	BOOL GetConfigInt( LPCTSTR lpszKey, LPCTSTR lpszName, int & nValue );

public :
	CBaseCom(LPCTSTR lpszServerName);
	~CBaseCom();

	// Service Routine
	virtual BOOL Process();
	virtual void OnPauseService();
	virtual BOOL OnContinueService();
	virtual void OnStopService();
	virtual BOOL OnStartService();

	virtual void OnTimer ();
	virtual BOOL OnOpenSession (CSessDesc* pDes);
	virtual void OnCloseSession (CSessDesc* pDes, int nCode);
	virtual int OnReceiveMsg (CSessDesc* pDes, CMsg& msg);
};

/////////////////////////////////////////////////////////////////////////////
// CSessionApp:
// See Session.cpp for the implementation of this class
//

class CSessionApp : public CWinApp
{
public:
	CSessionApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSessionApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSessionApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

extern SOCKET OpenClient (LPCTSTR servIP, int servPort);
extern SOCKET OpenServer (LPCTSTR servIP, int servPort, BOOL fUDP);
extern void WINAPI ServiceMain (DWORD dwArgc, LPTSTR* lpszArgv);
extern void WINAPI ServiceHandler (DWORD dwControl);


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVER_H__3FB54859_F644_11D1_A521_00A0248552AD__INCLUDED_)
