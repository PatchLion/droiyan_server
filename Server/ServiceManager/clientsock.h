#if !defined(AFX_CLIENTSOCK_H__3731D1A3_2242_11D2_A549_00A0248552AD__INCLUDED_)
#define AFX_CLIENTSOCK_H__3731D1A3_2242_11D2_A549_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ClientSock.h : header file
//

#define MAX_BUF		8192

/////////////////////////////////////////////////////////////////////////////
// CClientSock command target

class CClientSock : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CClientSock();
	virtual ~CClientSock();

// Overrides
public:
	BOOL m_fConnect;
	void SendMsg (CMsg& msg);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSock)
	public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	virtual void OnReceiveMsg (CMsg& msg);
	int m_nRdCnt;
	BYTE m_buf[MAX_BUF];
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCK_H__3731D1A3_2242_11D2_A549_00A0248552AD__INCLUDED_)
