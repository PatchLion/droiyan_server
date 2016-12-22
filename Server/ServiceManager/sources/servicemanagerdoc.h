// ServiceManagerDoc.h : interface of the CServiceManagerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVICEMANAGERDOC_H__E17147FE_20EA_11D2_A546_00A0248552AD__INCLUDED_)
#define AFX_SERVICEMANAGERDOC_H__E17147FE_20EA_11D2_A546_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Count.h"

#define UPDATE_ALL					0
#define UPDATE_ADDSERVER			1
#define UPDATE_DELSERVER			2
#define UPDATE_CONFIGSERVER			3
#define UPDATE_SERVERSTATUS			4
#define UPDATE_INSTALLSERVICE		5
#define UPDATE_REMOVESERVICE		6
#define UPDATE_SERVICESTATUS		7
#define UPDATE_SERVICECONFIG		8
#define UPDATE_ADDFILE				9
#define UPDATE_DELFILE				10
#define UPDATE_UPDATEFILE			11
#define UPDATE_VIEWLOG				12
#define UPDATE_ADDLOG				13
#define UPDATE_VIEWSERIAL			14
#define UPDATE_ADDSERIAL			15
#define UPDATE_UPDATESERIAL			16
#define UPDATE_COUNT				17
#define UPDATE_VIEWBANK				18
#define UPDATE_ADDBANK				19
#define UPDATE_UPDATEBANK			20
#define UPDATE_ADDBADID				21
#define UPDATE_VIEWBADID			22
#define UPDATE_ADDCLIENTLOG			23

//======================================
#define UPDATE_VIEWCLIENT           24
//======================================


class CServer;
class CService;
class CUserManager;
class CFileManager;
class CSession;

class CSerialSet;
class CLogSet;
class CBankSet;
class CBadIDSet;
class CClientSet;
class CClientPaySet;
class CClientLogSet;
class CCurrentUserSet;

class CFileInfo : public CObject  
{
public:
	BOOL CreateCompFile (LPCTSTR lpszPath);
	CString m_strCompName;
	CString m_strFileName;
	BYTE	m_bComp;
	WORD	m_wVer;

	CFileInfo(LPCTSTR lpszFileName, LPCTSTR lpszPathName, BYTE bComp, WORD wVer);
	CFileInfo(LPCTSTR lpszFileName, LPCTSTR lpszCompName, WORD wVer);
	virtual ~CFileInfo();
};

class CSelItem : public CObject  
{
public:
	enum 
	{ 
		selNone, 
		selServerRoot, selServiceRoot, selVersionRoot, selGameRoot, selSessionRoot,
		selServer, selService, selFolder,
		selVersion, selNumFile, selFile
	};
	CObject* m_pObject;
	int m_nType;

	CSelItem(int nType, CObject* pObject);
};

class CGameSet;

class CServiceManagerDoc : public CDocument
{
protected: // create from serialization only
	CServiceManagerDoc();
	DECLARE_DYNCREATE(CServiceManagerDoc)

// Attributes
public:
	CImageList m_imageTree;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServiceManagerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	CView* GetServiceManagerView();
	CView* GetStatusView();

	void MainViewActivate();
	int m_nType;
	int m_wID;
	int m_nMoney;
	CTime m_timeDead;
	CTime m_timeFrom;
	CTime m_timeTo;
	BYTE m_wPrintType;
	void GetPayDetail( CString&, CString&);
	void MonyForm( CString*);
	BYTE m_nListStatus;
	CObList* m_pPrnList;
	void GetCurrentUser (LPCTSTR lpszUserID, DWORD wSerial);
	void OnNumUserUpdated (CService* pService, int nNum);
	void DisconnectUser (LPCTSTR lpszUserID);
	void ReturnBadID (LPCTSTR lpszUserID);
	BOOL RegBadID (LPCTSTR lpszUserID);
	void ViewBankBySerial (DWORD wSerial);
	void ViewSerialByBank (int nBankID);
	BOOL UpdateBank (int nID);
	int GetAccessCode ();
	int m_nCountRange;
	int m_nCountScale;
	CSession* FindSession (int nServID);
	CObList m_listCount;
	DWORD m_nSeed;
	CString GetSerial1 (LPCTSTR lpszSerial2, int nNumDigit);
	CString GetSerial2 (DWORD wSerial, DWORD nSeed, int& nNumDigit);
	BOOL UpdateSerial (DWORD wSerial);
	WORD m_wGameID;
	DWORD CheckSerial(LPCTSTR lpszSerial1, LPCTSTR lpszSerial2);
	CString GetSessionName (int nSessionID);
	CTime m_timeEnd;
	CTime m_timeStart;
	BOOL m_fSearchNow;
	CString m_strSrcPath;
	CObList m_listSelItem;
	CSelItem* m_pSelItem;
	CObList m_listDel;
	CObList m_listFile;
	int m_nNumVer;
	WORD m_wGameVer;
	CObList m_listServer;
	CUserManager* m_pUserManager;
	CFileManager* m_pFileManager;
	CObList m_listSession;
	CObList m_listGame;
	CObList m_listBank;
	CObList	m_listSerial;
	CObList m_listLog;
	CObList	m_listBadID;

	CObList	m_listClientPay;
	CObList	m_listClient;

	CString m_strGameID;
	CString	m_strUserID;
	CString m_strPasswd;

	int		m_vNoticeValue;
	CString	m_strNoticeMessage;
	int		m_vNoticeSessionValue;
	CString	m_strNoticeSessionMessage;

	CServer* FindServer (LPCTSTR lpszServerName);
	virtual ~CServiceManagerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CFileInfo* FindFileInfo (LPCTSTR lpszFileName);

// Generated message map functions
protected:
	//{{AFX_MSG(CServiceManagerDoc)
	afx_msg void OnServerAdd();
	afx_msg void OnUpdateServerAdd(CCmdUI* pCmdUI);
	afx_msg void OnServerDel();
	afx_msg void OnUpdateServerDel(CCmdUI* pCmdUI);
	afx_msg void OnServerConnect();
	afx_msg void OnUpdateServerConnect(CCmdUI* pCmdUI);
	afx_msg void OnServerConfig();
	afx_msg void OnUpdateServerConfig(CCmdUI* pCmdUI);
	afx_msg void OnServiceConfig();
	afx_msg void OnUpdateServiceConfig(CCmdUI* pCmdUI);
	afx_msg void OnServiceDel();
	afx_msg void OnUpdateServiceDel(CCmdUI* pCmdUI);
	afx_msg void OnControlStart();
	afx_msg void OnControlStop();
	afx_msg void OnControlPause();
	afx_msg void OnControlContinue();
	afx_msg void OnUpdateControlStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateControlStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateControlPause(CCmdUI* pCmdUI);
	afx_msg void OnUpdateControlContinue(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVersion(CCmdUI* pCmdUI);
	afx_msg void OnVersionSet();
	afx_msg void OnVersionDel();
	afx_msg void OnVersionConfig();
	afx_msg void OnVersionCompress();
	afx_msg void OnVersionAdd();
	afx_msg void OnManageNewserial();
	afx_msg void OnManageFinduser();
	afx_msg void OnUpdateServiceValue(CCmdUI* pCmdUI);
	afx_msg void OnServiceValue();
	afx_msg void OnManageConvserial();
	afx_msg void OnControlStartall();
	afx_msg void OnControlStopall();
	afx_msg void OnUpdateControlAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateManageConuser(CCmdUI* pCmdUI);
	afx_msg void OnManageConuser();
	afx_msg void OnManageBank();
	afx_msg void OnManageDisconnect();
	afx_msg void OnServiceGetvalue();
	afx_msg void OnViewSerial();
	afx_msg void OnViewLog();
	afx_msg void OnViewBank();
	afx_msg void OnClientNew();
	afx_msg void OnClientSearch();
	afx_msg void OnManageSerialuse();
	afx_msg void OnUpdateManage(CCmdUI* pCmdUI);
	afx_msg void OnLogSearch();
	afx_msg void OnManageBadid();
	afx_msg void OnManageBadidlist();
	afx_msg void OnManageClientlog();
	afx_msg void OnFileSavelog();
	afx_msg void OnManageCurrentuser();
	afx_msg void OnManageClientpaylist();
	afx_msg void OnUpdateManageClientpaylist(CCmdUI* pCmdUI);
	afx_msg void OnManagePrintbill();
	afx_msg void OnListPrint();
	afx_msg void OnListPrintPreview();
	afx_msg void OnSaveList();
	afx_msg void OnPrintAddress();
	afx_msg void OnFinishday();
	afx_msg void OnUpdateFinishday(CCmdUI* pCmdUI);
	afx_msg void OnClientBank();
	afx_msg void OnPrintBank();
	afx_msg void OnNoticeSet();
	afx_msg void OnNoticeSession();
	afx_msg void OnFileDirCompress();
	afx_msg void OnUpdateFileDirCompress(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void IntegerForm( CString* strSource);
	void SetClientList( long&);
	void AddClient( CClientSet*, int, int);
	void SetPayList( long MonthFilter = 0, int IDFilter = 0);
};

/////////////////////////////////////////////////////////////////////////////

class CSerial : public CObject
{
public :
	BOOL	m_fFirstUse;
	int		m_nType;
	DWORD	m_wSerial;
	CString	m_strPasswd;
	CTime	m_timeStart;
	CTime	m_timeEnd;
	long	m_nMaxReg;
	long	m_nCurReg;
	long	m_nValidDay;

	CSerial (CSerialSet* pSerialSet);
};

class CBank : public CObject
{
public:
	long	m_nID;
	CTime	m_timeReg;
	CString	m_strName;
	CString	m_strBank;
	long	m_nMoney;
	BYTE	m_bType;
	BYTE	m_bProcess;
	CString	m_strOper;
	CString m_strComment;

	CBank (CBankSet* pBankSet);
};

class CLog : public CObject  
{
public:
	CLog(CCurrentUserSet* pSet);
	int		m_nServiceID;
	CString m_strUserID;
	CTime	m_timeStart;
	CTime	m_timeEnd;
	int		m_nUseTime;
	DWORD	m_wSerial;
	BYTE	m_bReason;
	CString m_strIPAddr;

	CLog (CLogSet* pLogSet);
	CLog (CClientLogSet* pLogSet);
};

class CBadID : public CObject
{
public:
	CString	m_strUserID;
	CTime	m_timeFrom;
	CTime	m_timeTo;
	CString	m_strOper;
	CString	m_strComment;

	CBadID (CBadIDSet* pBadIDSet);
};

class CClientPay : public CObject
{
public:
	int		m_wClientID;
	DWORD	m_wSerial;
	long	m_nMonth;
	long	m_nUseTime;
	long	m_nBankID;
	CString	m_strSerialCode;

	CClientPay( CClientPaySet*);
	CClientPay();
};

class CClient : public CObject
{
public:
	long	m_nNumPC;
	CString	m_strAddress;
	CString	m_strEMail;
	CString	m_strHost;
	CString	m_strKind;
	CString	m_strName;
	CString	m_strRegNo;
	CString	m_strTelNo;
	CString	m_strType;
	CString	m_strUseLine;
	CString	m_strZipCode;
	CTime	m_timeReg;
	ULONG   m_nTotalTime;
	int	    m_wMonth;
	int  	m_wYear;
	int		m_wID;
	BYTE	m_wLoc;
	CString m_strIPAddress;
	CString m_strEtc;	

	CClient( CClientSet*);
	CClient();
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVICEMANAGERDOC_H__E17147FE_20EA_11D2_A546_00A0248552AD__INCLUDED_)
