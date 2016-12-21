// FileManager.h : main header file for the FILEMANAGER application
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
#include "..\include\FMProtocol.h"

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

#define	DEFAULT_SIZE	8192

class CMsg;
class CSessDesc;
class CBaseCom;
class CFileInfo;

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
	void Copy (void* pBuf);
	void Clear () { m_nRdOff = 0; m_nWrOff = 0; }

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

	CMsg&		operator=( CMsg&	msg );	
};

/////////////////////////////////////////////////////////////////////////////
// CSessDesc:
// See SessDesc.cpp for the implementation of this class
//

class CSessDesc : public CObject
{
protected:
	enum { stateNone, stateDown };
	CString		m_strFileName;
	int			m_nState;
	CObList		m_listFile;
	CFile		m_file;
	SOCKET		m_sockClient;
	int			m_nRdCnt;
	char*		m_buf;

public:
	HANDLE		m_hThread;
	CBaseCom*	m_pCom;
	CMsg		m_msg;
	DWORD		m_dwTimeOut;
	DWORD		m_dwCurrentDown;
	DWORD		m_dwCurrentSend;
	BOOL		m_bInstFlag;

	CSessDesc(CBaseCom* pCom = NULL);
	~CSessDesc();

	BOOL Create (SOCKET sockListen);
	void Close();
	BOOL Connect (CBaseCom* pCom, LPCTSTR lpszAddr, int nPort);
	BOOL IsValid () { return (m_sockClient != INVALID_SOCKET); }
	SOCKET GetClientSock () { return m_sockClient; }

	BOOL CheckMsg ();
	void Copy ();
	int Hear ();
	int Say (CMsg& msg);

	BOOL IsDownState () { return (m_nState == stateDown); }
	CFileInfo* GetFileInfo ();
	int GetNumDownFile();
	void AddFileInfo (CFileInfo* pInfo);
	BOOL ProcDown();
	BOOL StartDown ();
	DWORD GetLengthTotalFile ();
};

/////////////////////////////////////////////////////////////////////////////
// CBaseCom:
// See FileManager.cpp for the implementation of this class
//

class CBaseCom
{
protected:
	BOOL GetConfigString (LPCTSTR lpszKey, LPCTSTR lpszName, CString& strValue);
	BOOL GetConfigInt (LPCTSTR lpszKey, LPCTSTR lpszName, int & nValue);
	SOCKET		m_sockListen;
	HKEY		m_hKey;

public :
	CObList		m_listInactive;
	CObList		m_listActive;

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
	DWORD		m_dwThreadHold;
	DWORD		m_dwSendHold;

public :
	CRITICAL_SECTION m_Section;
	CBaseCom (LPCTSTR lpszServerName);
	~CBaseCom ();

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
// CFileManagerApp:
// See FileManager.cpp for the implementation of this class
//

class CFileManagerApp : public CWinApp
{
public:
	CFileManagerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileManagerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFileManagerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

extern SOCKET OpenClient (LPCTSTR servIP, int servPort);
extern SOCKET OpenServer (LPCTSTR servIP, int servPort);
extern void WINAPI ServiceMain (DWORD dwArgc, LPTSTR* lpszArgv);
extern void WINAPI ServiceHandler (DWORD dwControl);



//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVER_H__3FB54859_F644_11D1_A521_00A0248552AD__INCLUDED_)
