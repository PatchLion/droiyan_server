// UserManagerCom.h: interface for the CUserManagerCom class.
//
//////////////////////////////////////////////////////////////////////
 
#if !defined(AFX_SERVERCOM_H__D3616D71_F365_11D1_A51F_00A0248552AD__INCLUDED_)
#define AFX_SERVERCOM_H__D3616D71_F365_11D1_A51F_00A0248552AD__INCLUDED_

#include "UserManager.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CUserManagerCom : public CBaseCom  
{
public:
	CUserManagerCom(LPCTSTR lpszServerName);
	virtual ~CUserManagerCom();

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

protected:
	int m_nSeed;
	int m_nGameVer;
	int m_nFMPort;
	int m_nGSPort;
	CString m_strFMAddr;
	CString m_strGSAddr;

	int OnUMIdentifyReq (CSessDesc* pDes, CMsg& msg);
	int OnUMKickoutReq (CSessDesc* pDes, CMsg& msg);
	int OnUMCurStatusReq(CSessDesc* pDes, CMsg& msg);
	int OnUMCurStatus1Req(CSessDesc* pDes, CMsg& msg);
};

#endif // !defined(AFX_SERVERCOM_H__D3616D71_F365_11D1_A51F_00A0248552AD__INCLUDED_)
