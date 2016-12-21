// BadukDirCom.h: interface for the CBadukDirCom class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERCOM_H__D3616D71_F365_11D1_A51F_00A0248552AD__INCLUDED_)
#define AFX_SERVERCOM_H__D3616D71_F365_11D1_A51F_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Database.h"

class CBadukDirCom : public CBaseCom  
{
public:
	int **m_pZoneNumber, **m_pCurrentPos;
	char ****m_pAddress;
	int ***m_pPort;
	int *m_pSvrKindCount;
	int m_vServerCount;
	void RemoveData();
	BOOL LoadGameAddr();
	CDatabase m_db;
	int m_nCurServer;
	int m_nNumServer;
	CDWordArray m_arrayGSPort;
	CStringArray m_arrayGSAddr;
	CBadukDirCom(LPCTSTR lpszServerName);
	virtual ~CBadukDirCom();

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
	int OnSMDirReq (CSessDesc* pDes, CMsg& msg);
};

#endif // !defined(AFX_SERVERCOM_H__D3616D71_F365_11D1_A51F_00A0248552AD__INCLUDED_)
