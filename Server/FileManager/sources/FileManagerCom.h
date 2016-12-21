// FileManagerCom.h: interface for the CFileManagerCom class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERCOM_H__D3616D71_F365_11D1_A51F_00A0248552AD__INCLUDED_)
#define AFX_SERVERCOM_H__D3616D71_F365_11D1_A51F_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CFileInfo;
class CFileManagerCom : public CBaseCom  
{
	CString		m_strFilePath;
	CObList		m_listFile;
	CFileInfo*	m_pInfoInst;

public:
	BOOL LoadFileZipInfo();
	CFileManagerCom(LPCTSTR lpszServerName);
	virtual ~CFileManagerCom();

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
	int OnFMVersioninfoReq (CSessDesc *pDes, CMsg &msg);
	int OnFMDownAck (CSessDesc* pDes, CMsg& msg);
	BOOL LoadInstallFile ();
	BOOL LoadFileInfo ();

	int OnFMDownReq(CSessDesc * pDes, CMsg & msg);
	int OnFMEnddownReq (CSessDesc* pDes, CMsg& msg);
	int OnFMFileinfoReq(CSessDesc * pDes, CMsg & msg);
	int OnFMDowninfoReq(CSessDesc * pDes, CMsg & msg);
};

#endif // !defined(AFX_SERVERCOM_H__D3616D71_F365_11D1_A51F_00A0248552AD__INCLUDED_)
