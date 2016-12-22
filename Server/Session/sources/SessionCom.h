// SessionCom.h: interface for the CSessionCom class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERCOM_H__D3616D71_F365_11D1_A51F_00A0248552AD__INCLUDED_)
#define AFX_SERVERCOM_H__D3616D71_F365_11D1_A51F_00A0248552AD__INCLUDED_

#include "Session.h"	// Added by ClassView
#include "Scdefine.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSessionCom : public CBaseCom  
{
public:
	int m_bServiceStartFlag;
	int m_bServiceContinueFlag;

	CSessDesc *m_pDesUM;
	CSessDesc *m_pDesGS;
	CRITICAL_SECTION m_CS_db;

public:
	int OnSMGameConnectionReq(CSessDesc *pDes, CMsg& msg);
	int OnSMChangePasswdReq(CSessDesc * pDes, CMsg & msg);

	BOOL CheckPwdValid( CString strPasswd );
	BOOL CheckIDValid(CString str_id);
	int OnSMIDExistReq(CSessDesc *pDes, CMsg& msg);
	int OnSMCPLoginReq(CSessDesc * pDes, CMsg & msg);
	int OnSMCPLogoutReq(CSessDesc * pDes, CMsg & msg);

	BOOL CheckSocNum (LPCTSTR lpszSocNo);
	DWORD CheckSerial (LPCTSTR lpszSerial1, LPCTSTR lpszSerial2);
	BOOL CheckFilterAddress (LPCTSTR lpszAddr);
	void LoadFilterAddress();
	BOOL ConnectUM ();
	BOOL ReConnectUM();
	BOOL ReConnectGS();

	CSessionCom(LPCTSTR lpszServerName);
	virtual ~CSessionCom();

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
	void OnDupCloseSession(CSessDesc* pDes, int nCode);
	BOOL ConnectDir();
	BOOL m_fPay;
	WORD m_wGameVer;
	CString m_strDBPasswd;
	CString m_strServName;
	CString m_strUMAddr;
	CString m_strFMAddr;
	CString m_strGSAddr;
	CString m_ServerNames[10];
	int m_nGameServers;
	int m_nUMPort;
	int m_nFMPort;
	int m_nGSPort;

	CDatabase m_db[AUTOMATA_THREAD2+1];
	CStringList m_listFilter;
	int m_nSeed;
	CString m_strNotice;

	int CheckSerial (LPCTSTR lpszSerial1, LPCTSTR lpszSerial2, DWORD& dwSerial);

	int OnSMGameInfoReq (CSessDesc* pDes, CMsg& msg);
	int OnSMGameInfo2Req (CSessDesc* pDes, CMsg& msg);
	int OnSMGameReq (CSessDesc* pDes, CMsg& msg);
	int OnSMDownReq (CSessDesc* pDes, CMsg& msg);
	int OnSMRegSNReq (CSessDesc* pDes, CMsg& msg);
	int OnSMSetInfoReq (CSessDesc* pDes, CMsg& msg);
	int OnSMGetInfoReq (CSessDesc* pDes, CMsg& msg);
	int OnSMRegUserReq (CSessDesc* pDes, CMsg& msg);
	int OnSMLoginReq (CSessDesc* pDes, CMsg& msg);
	int OnSMDirAck (CMsg & msg);

	int OnUMKickoutAck (CMsg& msg);
	int OnUMIdentifyAck (CMsg& msg);
	int OnUMReIdentifyAck (CMsg& msg);

	// IKING 1999.1.
	int OnSMGameEndReq(CSessDesc *pDes, CMsg &msg);
	int OnSMReconnectReq( CSessDesc *pDes, CMsg &msg );
	int OnSMServerListReq( CSessDesc *pDes, CMsg &msg );

	int OnUMCurStatusAck(CMsg& msg);
	int OnUMCurStatus1Ack(CMsg& msg);
	int OnSMUpgradingAck( CSessDesc *pDes, CMsg &msg );
	//
};

#endif // !defined(AFX_SERVERCOM_H__D3616D71_F365_11D1_A51F_00A0248552AD__INCLUDED_)
