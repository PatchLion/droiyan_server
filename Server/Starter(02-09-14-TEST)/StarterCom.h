// StarterCom.h: interface for the CStarterCom class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERCOM_H__D3616D71_F365_11D1_A51F_00A0248552AD__INCLUDED_)
#define AFX_SERVERCOM_H__D3616D71_F365_11D1_A51F_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

extern TCHAR g_szAppName[];

class CService;
class CStarterCom : public CBaseCom  
{
public:
	CString m_strAdminPasswd;
	void GetErrorMessage (CString& strMsg);
	CService* FindService (LPCTSTR lpszService);
	void BroadcastMsg (CMsg& msg);
	CObList m_listService;
	CStarterCom(LPCTSTR lpszServerName);
	virtual ~CStarterCom();

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
	void OnSCLoginReq (CSessDesc* pDes, CMsg& msg);
	void OnSCStatusReq (CSessDesc* pDes, CMsg& msg);
	void OnSCListReq (CSessDesc* pDes, CMsg& msg);
	void OnSCSetIntValueReq (CSessDesc* pDes, CMsg& msg);
	void OnSCSetStringValueReq (CSessDesc* pDes, CMsg& msg);
	void OnSCGetIntValueReq (CSessDesc* pDes, CMsg& msg);
	void OnSCGetStringValueReq (CSessDesc* pDes, CMsg& msg);
	void OnSCPauseReq (CSessDesc* pDes, CMsg& msg);
	void OnSCContinueReq (CSessDesc* pDes, CMsg& msg);
	void OnSCStopReq (CSessDesc* pDes, CMsg& msg);
	void OnSCStartReq (CSessDesc* pDes, CMsg& msg);
	void OnSCRemoveReq (CSessDesc* pDes, CMsg& msg);
	void OnSCInstallReq (CSessDesc* pDes, CMsg& msg);
};

#endif // !defined(AFX_SERVERCOM_H__D3616D71_F365_11D1_A51F_00A0248552AD__INCLUDED_)
