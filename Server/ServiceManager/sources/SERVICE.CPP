// Service.cpp: implementation of the CService class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServiceManager.h"
#include "ServiceManagerDoc.h"

#include "Server.h"
#include "Service.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CService::CService(CServer* pServer,
				   int nType,
				   LPCTSTR lpszModule,
				   LPCTSTR lpszDisplayName,
				   int nServerID,
				   LPCTSTR lpszAddr,
				   int nPort,
				   int nCapacity,
				   DWORD dwTimer,
				   DWORD dwTimeOuts,
				   DWORD dwStatus/*=SERVICE_STOPPED*/)
{
	m_pServer = pServer;
	m_nType = nType;
	m_strModule = lpszModule;
	m_strDisplayName = lpszDisplayName;
	m_nServerID = nServerID;
	m_strAddr = lpszAddr;
	m_nPort = nPort;
	m_nCapacity = nCapacity;
	m_dwTimer = dwTimer;
	m_dwTimeOuts = dwTimeOuts;
	m_dwStatus = dwStatus;
	m_strGameID = pServer->m_pDoc->m_strGameID;
	m_strUserID = pServer->m_pDoc->m_strUserID;
	m_strPassword = pServer->m_pDoc->m_strPasswd;
	m_bSuspend = 0;
	m_nNumUser = 0;

	switch (nType)
	{
	case typeUM :
		m_strServiceName.Format (_T("UM_%s"), m_strGameID);
		break;
	case typeFM :
		m_strServiceName.Format (_T("FM_%s"), m_strGameID);
		break;
	case typeGS :
		m_strServiceName.Format (_T("GS_%s_%s"), m_strGameID, lpszDisplayName);
		break;
	case typeSM :
		m_strServiceName.Format (_T("SM_%s_%d"), m_strGameID, nServerID);
		break;
	}

	if (nType == typeUM && dwStatus == SERVICE_RUNNING && Create ())
		Connect (m_strAddr, m_nPort);
}

CService::~CService()
{

}

BOOL CService::Start()
{
	if (m_dwStatus != SERVICE_STOPPED || !m_pServer->m_fConnect)
		return FALSE;

	CMsg msg;
	msg.ID (SC_START_REQ) << m_strServiceName;
	m_pServer->SendMsg (msg);

	return TRUE;
}

BOOL CService::Stop()
{
	if (m_dwStatus == SERVICE_STOPPED || !m_pServer->m_fConnect)
		return FALSE;

	if (m_fConnect)
		CClientSock::Close ();

	CMsg msg;
	msg.ID (SC_STOP_REQ) << m_strServiceName;
	m_pServer->SendMsg (msg);

	return TRUE;
}

BOOL CService::Pause()
{
	if (m_dwStatus != SERVICE_RUNNING || !m_pServer->m_fConnect)
		return FALSE;

	CMsg msg;
	msg.ID (SC_PAUSE_REQ) << m_strServiceName;
	m_pServer->SendMsg (msg);

	return TRUE;
}

BOOL CService::Continue()
{
	if (m_dwStatus != SERVICE_PAUSED || !m_pServer->m_fConnect)
		return FALSE;

	CMsg msg;
	msg.ID (SC_CONTINUE_REQ) << m_strServiceName;
	m_pServer->SendMsg (msg);

	return TRUE;
}

void CService::OnReceiveMsg(CMsg &msg)
{
	switch (msg.ID ())
	{
	case 0 : 
		msg >> m_bSuspend >> m_nNumUser;
		break;
	}

}

void CService::GetStatus()
{
	CMsg msg;
	msg.ID (0);
	SendMsg (msg);
}

void CService::OnConnect(int nErrorCode) 
{
	CClientSock::OnConnect(nErrorCode);
	if (m_fConnect)
		GetStatus ();
}
