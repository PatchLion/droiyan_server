///////////////////////////////////////////////////////////////////
//	ServerDlg.h : header file for the CServerDlg class
//  Copyright (C) 2000,  Jin-Soo Jeon
//
//	If this code works, it was written by JinSoo Jeon.
//	If not, I don't know who wrote it.
//

#if !defined(AFX_SERVERDLG_H__AAE3FDA5_0147_46D1_837F_A6D48525B731__INCLUDED_)
#define AFX_SERVERDLG_H__AAE3FDA5_0147_46D1_837F_A6D48525B731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "COM.h"
#include "SharedMemory.h"
#include "MemUser.h"

#include "SInstance.h"
#include "Iocpbase.h"
#include "SockDataList.h"
#include "SSocket.h"

#include "GuildFortress.h"
#include "resource.h"
#include "EventItemNew.h"

#define	WM_CLOSE_PROCESS		(WM_USER + 10)

/////////////////////////////////////////////////////////////////////////////
// CServerDlg dialog

class CServerDlg : public CDialog
{
// IKING 2001.1.
public:
	COM			m_Com;
	CIOCPBASE	m_ServerBase;
	CIOCPBASE	m_UserBase;
	int			m_nThreadCount;
	int			m_bLogOutExit;
	int			m_CurUserCount;			// 현재 사용자 
	HANDLE		m_amThread[AUTOMATA_THREAD+1];
	HANDLE		m_ctThread[AUTOMATA_THREAD+1];
	int			m_ThreadNo[AUTOMATA_THREAD+1];
	
	char		m_strBridgeIP[20];
	int			m_nBridgePort;

	DWORD		m_dwBSAlive;

	// IKING 2002.1.
	CWinThread	*m_hLoginThread;
	CWinThread	*m_hLogoutThread;
	CWinThread	*m_hSqlThread;
	CWinThread	*m_hFortressThread;

//	HANDLE		m_hLoginThread;
//	HANDLE		m_hLogoutThread;
//	HANDLE		m_hSqlThread;

	CSSocket	*m_pDBSocket;
	char		m_DBAddr[100];
	int			m_nDBPort;
	//

	// JJS	2002.02.28
	CSSocket*	m_pBridgeSocket;
	TCHAR		m_strZoneAddr[256];
	//

public:
	void Send2DBsvr( TCHAR *pBuf, int length );
	BOOL InitEnv();
	void InitThreads();

	int MakeThreadSafeUserMessage( int cmd_code, int wparam, long lparam );
	int MakeThreadSafeMessage( int cmd_code, int wparam, long lparam );
	void ServerCloseMessage(int wparam, long lparam);
	void UserCloseMessage(int wparam, long lparam); 

	LRESULT OnStartAutomata( WPARAM wparam, LPARAM lparam );
	BOOL AutoMataAppCmd(WAIT_RECV_DATA *wrd);
	void UserFree(int uid);
	COM *GetCOM() { return &m_Com; }
	void SetAliveSignalFill();

	CSSocket* GetServerSocket( CIOCPBASE *pIocpBase );

	//-------------------------------------------------------------------------
	// DB PART...
	void DBGameStartResult( char *pBuf, int index, int length );
	void DBAccountLoginResult(char *pBuf, int index, int length );
	BOOL DBSocketConnect();
	void DBjobPhasor( CSSocket* pServerSock, char *pTBuf, int length );

	//-------------------------------------------------------------------------
	// Zone Server PART...
	BOOL ZoneSocketConnect();

//
// Construction
public:
	BOOL LoadGuildFortressUserData(CGuildFortress *pFort);
	void UpdateFortressMem2DB(CMemFortress *pMDFortress);
	BOOL UpdateBankMem2DB(CMemUser *pMD);
	BOOL LoadGuildStoreAttackList(CStore *pStore, CMemStore* pData);
	void UpdateStoreMem2DB(CMemStore *pMDStore);
	BOOL GetGuildMapInfoTable();
	BOOL GetGuildStoreTable();
	BOOL GetEBodyStoreTable();
	BOOL GetEBodyTable();
	BOOL GetEBodyUpgradeTable();
	BOOL GetEBodyIdentifyTable();
	BOOL GetGuildUserData();
	BOOL GetGuildTable();
	BOOL GetValItemTable();
	BOOL GetMonHaveDNTable();
	BOOL GetCityNpcTableData();
	BOOL GetUserRecoverRateTable();
	BOOL GetUserRecoverTable();
	void AddSkillTable();
	BOOL GetMagicItemTable();
	BOOL GetIntiItemTable();
	BOOL GetZoneInfoData();
	BOOL GetPsiStoreTable();
	void SetClientWorldTime(CString strTime);
	void SetWeatherZone(int iZone);
	void OnAnnounce(void);
	BOOL GetDBItemData();
	CServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CServerDlg)
	enum { IDD = IDD_SERVER_DIALOG };
	CStatic	m_staticZone;
	CStatic	m_staticPort;
	CStatic	m_staticIndex;
	CStatic	m_staticClientVer;
	CString	m_editCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerDlg)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL GetEventBlockData();
	void BridgeRemoveGuildMasterOfPowerReq(int muid, char *strMasterID, int guildnum);
	void BridgeDeputeGuildMasterOfPowerReq(int muid, int guid, char *strMasterID, char *strSubMasterID, int guildnum);
	void BridgeDeputeGuildMasterOfPowerResult(TCHAR *pBuf);
	void BridgeRemoveGuildMasterOfPowerResult(TCHAR *pBuf);
	void BridgeServerArkWinnerChangeResult(TCHAR* pBuf);
	void AnnounceZone(TCHAR* pBuf, BYTE sysType, int iZone);
	void BridgeServerAnnounce(TCHAR* pBuf);
	void AnnounceAllServer(TCHAR* pBuf, BYTE sysType);
	BOOL GetRoyalRumbleData();
	void Announce(TCHAR* pBuf, BYTE sysType);
	void BridgeServerUserZoneLogOutResult(TCHAR* pBuf);
	void BridgeServerUserZoneLogOut(int uid, char* strUserID, int z, int x, int y);
	void BridgeServerUserRestartResult(TCHAR* pBuf);
	void BridgeServerGuildMarkResult(TCHAR* pBuf);
	void BridgeServerGuildMarkReq(int uid, char* strUserID, int guildnum, char* pGuildMark);
	void BridgeServerGuildOffResult(TCHAR* pBuf);
	void BridgeServerGuildOffReq(int uid, char* strUserID, char* strOffID, int guildnum);
	void BridgeServerGuildInviteResult(TCHAR* pBuf);
	void BridgeServerGuildInviteReq(int muid, int guid, char* strMasterID, char* strGuestID, int guildnum);
	void BridgeServerGuildDisperseResult(TCHAR* pBuf);
	void BridgeServerGuildDisperseReq(int uid, char* strUserID, int guildnum);
	void BridgeServerGuildNewResult(TCHAR* pBuf);
	void BridgeServerGuildNewReq(int uid, char* strUserID, int guildnum, char* strGuildName);
	void BridgeServerUserGuildChatResult(TCHAR* pBuf);
	void BridgeServerUserGuildChatReq(int uid, int guildnum, char* strUserID, char* strMsg);
	void BridgeServerUserWhisperResult(TCHAR* pBuf);
	void BridgeServerUserWhisperReq(TCHAR* pBuf);
	void BridgeServerUserWhisperOnOff(int uid, BYTE onoff);
	void BridgeServerDoubleIDClose(TCHAR* pBuf);
	void BridgeServerDoubleAccountClose(TCHAR* pBuf);
	void BridgeServerUserZoneLoginResult(TCHAR* pBuf);
	void BridgeServerUserZoneLogIn(int uid, char* strAccount, char* strUserID);
	void BridgeServerUserLogOut(int uid, char* strUserID);
	void BridgeServerUserRestart(int uid, char *strUserID);
	void BridgeServerUserLoginResult(TCHAR* pBuf);
	void BridgeServerUserLogIn(int uid, char* strAccount, char* strUserID);
	void BridgeServerWhisperChatReq(int uid, char* pSendID, char* pRecvID, char* strMsg);
	void BridgeServerLoginResult(TCHAR* pBuf);
	void BridgeServerPhasor(CSSocket* pServerSock, char* pTBuf, int length);
	BOOL InitBridgeServerConnection();
	BOOL UpdateEventItemNew(CEventItemNew* pEventItem);
	void SetEventItemNew();
	BOOL GetEventItemNewTable();
	BOOL RemoveSessionCurrentUser();
	BOOL GetLocalIPAddress();
	BOOL UpdateAccountBankMem2DB(CMemUser* pMD);
	BOOL GetDressingTable();
	void CloseGuildWhareHouse();
	BOOL GetMonsterPsiTable();
	BOOL GetAddEventItemTable();
	BOOL GetTownPotalTable();
	int m_iUserCountCount;
	BOOL LoadGuildFortressList(CGuildFortress *pFort);
	void LoadDynamicMap();
	void SetStoreTaxForGuildFortress();
	BOOL GetGuildFortressTaxTable();
	BOOL LoadGuildFortressList(CGuildFortress *pFort, CMemFortress* pData);
	BOOL GetGuildFortressTable();
	BOOL GetNpcSayEventTable();
	BOOL GetEventItemTable();
	BOOL GetUserLevelUpTable();
	BOOL CheckGuildHouseData();
	BOOL GetGuildHouseTable();
	void UpdateGuildHouseMem2DB(CMemGuildHouseRank *pMD);
	BOOL GetVirtualRoomTable();
	BOOL GetGuildHouseRankTable();
	CInstanceChecker m_InstanceChecker;

protected:
	BOOL CheckSummonException(short sSid);
	BOOL GetBoxEventTable(void);
	BOOL GetRemodelingTable(void);
	void UpdateMem2DB(CMemUser* pMD);
	void CheckRollBack(void);
	BOOL OpenRollBack(void);
	BOOL OpenMemoryDB(void);
	BOOL OpenMailQueue(void);
	BOOL CloseMailQueue(void);
	BOOL GetStoreTable();
	BOOL GetNpcChatTable();
	void ResumeAI();
	BOOL GetPAMAExpTable();
	BOOL GetLevelUpTable();
	BOOL GetPsiTable();
	BOOL GetSkillTable();
	BOOL GetItemTable();
	BOOL GetNpcItemTable();
	BOOL GetNpcItemNewTable();
	BOOL get_convert_table();
	BOOL GetOneNpcItemNewTable(struct drop_info *dropItem);
	BOOL CreateNpcThread();
	BOOL GetNpcTableData();
	void SetZoneText(CString szList);
	void SetPortText(int nPort);
	void SetIndexText(int nIndex);
	BOOL GetServerInfoData();
	void DefaultInit();

	CSharedMemory	m_MemRollBack;
	UINT			m_nTimerID;
	UINT			m_nEventItemTimerID;
	UINT			m_nBridgeTimerID;
	UINT			m_nAliveTimerID;
	HICON			m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRefresh();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()	
	LONG OnCloseProcess(UINT wParam, LONG lParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERDLG_H__AAE3FDA5_0147_46D1_837F_A6D48525B731__INCLUDED_)
