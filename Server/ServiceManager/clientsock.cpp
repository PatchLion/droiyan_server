// ClientSock.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ClientSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSock

CClientSock::CClientSock()
{
	m_nRdCnt = 0;
	m_fConnect = FALSE;
}

CClientSock::~CClientSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CClientSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSock member functions

void CClientSock::OnConnect(int nErrorCode) 
{
	if (!nErrorCode)
		m_fConnect = TRUE;
	else
		m_fConnect = FALSE;
	
	CAsyncSocket::OnConnect(nErrorCode);
}

void CClientSock::OnClose(int nErrorCode) 
{
	m_fConnect = FALSE;

	CAsyncSocket::OnClose(nErrorCode);
}

void CClientSock::OnReceive(int nErrorCode) 
{
	if (!nErrorCode)
	{
		int nRecv = Receive (&m_buf[m_nRdCnt], DEFAULT_SIZE - m_nRdCnt);
		if (nRecv <= 0)
			CAsyncSocket::Close ();
		else
		{
			m_nRdCnt += nRecv;
			while (4 <= m_nRdCnt && *((WORD*)(&m_buf[2])) + 4 <= m_nRdCnt)
			{
				CMsg msg;
				msg.Copy (m_buf);
				int nSize = msg.GetSize ();
				m_nRdCnt -= nSize;
				if (m_nRdCnt)
					memmove (m_buf, &m_buf[nSize], m_nRdCnt);
				OnReceiveMsg (msg);
			}
		}
	}
	
	CAsyncSocket::OnReceive(nErrorCode);
}

void CClientSock::OnReceiveMsg(CMsg & msg)
{

}

void CClientSock::SendMsg(CMsg & msg)
{
	CAsyncSocket::Send (msg.GetBuf (), msg.GetSize ());
}
