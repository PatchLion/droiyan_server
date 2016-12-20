// Server.h: interface for the CServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVER_H__3731D1A5_2242_11D2_A549_00A0248552AD__INCLUDED_)
#define AFX_SERVER_H__3731D1A5_2242_11D2_A549_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ClientSock.h"

class CService;
class CServiceManagerDoc;

class CServer : public CClientSock  
{
protected:
	CServer ();
	DECLARE_SERIAL (CServer)

public:
	int m_nAccess;
	CServiceManagerDoc* m_pDoc;
	CObList m_listService;
	CStringList m_listAddr;
	CString m_strName;
	CString m_strAddr;

	CServer(CServiceManagerDoc* pDoc);
	virtual ~CServer();
	BOOL ConnectToServer ();
	CService* FindService (LPCTSTR lpszServiceName);

	virtual void OnConnect (int nErrorCode);
	virtual void OnClose (int nErrorCode);
	virtual void Serialize (CArchive& ar);

protected:
	void OnSCLoginAck (CMsg& msg);
	void OnSCStatusAck(CMsg& msg);
	void OnSCListAck(CMsg& msg);
	void OnSCStringValueAck(CMsg& msg);
	void OnSCIntValueAck(CMsg& msg);
	void OnSCPauseAck(CMsg& msg);
	void OnSCContinueAck(CMsg& msg);
	void OnSCStopAck(CMsg& msg);
	void OnSCStartAck(CMsg& msg);
	void OnSCRemoveAck(CMsg& msg);
	void OnSCInstallAck (CMsg& msg);
	virtual void OnReceiveMsg (CMsg& msg);
};

#endif // !defined(AFX_SERVER_H__3731D1A5_2242_11D2_A549_00A0248552AD__INCLUDED_)
