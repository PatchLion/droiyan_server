// ServiceManagerDoc.cpp : implementation of the CServiceManagerDoc class
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ServiceManagerDoc.h"

#include "Server.h"
#include "Service.h"
#include "FileManager.h"
#include "UserManager.h"
#include "Session.h"

#include "ServerConfigDlg.h"
#include "SelServiceDlg.h"
#include "SelServerDlg.h"
#include "LoginDlg.h"
#include "AddFileDlg.h"
#include "DelFileDlg.h"
#include "VersionDlg.h"
#include "SearchLogDlg.h"
#include "NewSerialDlg.h"
#include "FindUserDlg.h"
#include "RegDlg.h"
#include "ConvSerialDlg.h"
#include "NumSerialDlg.h"
#include "UserDlg.h"
#include "NewBankDlg.h"
#include "BankSerialDlg.h"
#include "ClientDlg.h"
#include "ClientListDlg.h"
#include "FindBankDlg.h"
#include "BadIDDlg.h"
#include "ClientSelectDlg.h"
#include "NoticeSetDialog.h"

#include "ConfigFMPage.h"
#include "ConfigGSPage.h"
#include "ConfigSMPage.h"
#include "ConfigUMPage.h"
#include "ConfigSheet.h"

#include "UserSet.h"
#include "SerialSet.h"
#include "LogSet.h"
#include "VerSet.h"
#include "BankSet.h"
#include "BankSerialSet.h"
#include "ClientSet.h"
#include "ClientSerialSet.h"
#include "BadIDSet.h"
#include "LogDataSet.h"
#include "ClientPaySet.h"
#include "ClientLogSet.h"
#include "CurrentUserSet.h"
#include "UserCountSet.h"

#include "PrintAddressDlg.h"
#include "ClientPayDlg.h"
#include "PayDetailDlg.h"
#include "StatusConst.h"
#include "PrintBillDlg.h"
#include "BillDate.h"

#include "ServiceManagerView.h"
#include "StatusView.h"
#include "MainFrm.h"

#include "ZipFileViewDlg.h"		// 파일 압축 클래스를 호출

extern CServiceManagerApp theApp;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSerial::CSerial (CSerialSet* pSet)
{
	m_wSerial = pSet->m_wSerial;
	m_strPasswd = pSet->m_strPasswd;
	m_fFirstUse = pSet->IsFirstUse ();
	if (!m_fFirstUse)
	{
		m_timeStart = pSet->m_timeStart;
		m_timeEnd = pSet->m_timeEnd;
		m_strPasswd = pSet->m_strPasswd;
	}
	m_nMaxReg = pSet->m_nMaxReg;
	m_nCurReg = pSet->m_nCurReg;
	m_nValidDay = pSet->m_nValidDay;
	m_nType = pSet->GetType ();
}

CBank::CBank (CBankSet* pSet)
{
	m_nID = pSet->m_nID;
	m_strBank = pSet->m_strBank;
	m_strName = pSet->m_strName;
	m_strOper = pSet->m_strOper;
	m_timeReg = pSet->m_timeReg;
	m_nMoney = pSet->m_nMoney;
	m_bType = pSet->m_bType;
	m_bProcess = pSet->m_bProcess;
	m_strComment = pSet->m_strComment;
}

CLog::CLog (CLogSet* pSet)
{
	m_nServiceID = pSet->m_nServiceID;
	m_strUserID = pSet->m_strUserID;
	m_timeStart = pSet->m_timeLogin;
	m_nUseTime = pSet->m_nUseTime;
	if (pSet->IsFieldNull (&pSet->m_wSerial))
		m_wSerial = 0;
	else
		m_wSerial = pSet->m_wSerial;
	m_bReason = pSet->m_bReason;
	m_strIPAddr = pSet->m_strIPAddr;
	m_timeEnd = pSet->m_timeLogin + CTimeSpan (pSet->m_nUseTime);
}

CLog::CLog (CClientLogSet* pSet)
{
	m_nServiceID = -1;
	m_strUserID = pSet->m_strUserID;
	m_timeStart = pSet->m_timeLogin;
	m_nUseTime = pSet->m_nUseTime;
	m_wSerial = pSet->m_wSerial;
	m_bReason = 255;
	m_strIPAddr = pSet->m_strIPAddr;
	m_timeEnd = pSet->m_timeLogin + CTimeSpan (pSet->m_nUseTime);
}

CLog::CLog(CCurrentUserSet *pSet)
{
	m_nServiceID = pSet->m_nServiceID;
	m_strUserID = pSet->m_strClientID;
	m_timeStart = pSet->m_timeLogin;
	m_nUseTime = 0;
	if (pSet->IsFieldNull (&pSet->m_nAccountID))//(&pSet->m_wSerial))
		m_wSerial = 0;
	else
		m_wSerial = pSet->m_nAccountID;
	m_bReason = 255;
	m_strIPAddr = pSet->m_strIPAddr;
	m_timeEnd = pSet->m_timeLogin;
}

CBadID::CBadID (CBadIDSet* pSet)
{
	m_strUserID = pSet->m_strUserID;
	m_timeFrom = pSet->m_timeReg;
	m_timeTo = pSet->m_timeReturn;
	m_strOper = pSet->m_strOper;
	m_strComment = pSet->m_strComment;
}

CClientPay::CClientPay( CClientPaySet* pSet)
{
	m_strSerialCode = pSet->m_strSerialCode;
	m_wClientID     = pSet->m_wClientID;
	m_nUseTime      = pSet->m_nUseTime;
	m_wSerial       = pSet->m_CLIENT_PAY_wSerial;
	m_nBankID       = pSet->m_nBankID;
	m_nMonth        = pSet->m_nMonth;
}

CClientPay::CClientPay()
{
	m_strSerialCode = _T("");
	m_wClientID     = 0;
	m_nUseTime      = 0;
	m_wSerial       = 0;
	m_nBankID       = 0;
	m_nMonth        = 0;
}

CClient::CClient( CClientSet* pSet)
{
	m_strAddress = pSet->m_strAddress;
	m_strUseLine = pSet->m_strUseLine;
	m_strZipCode = pSet->m_strZipCode;
	m_strEMail   = pSet->m_strEMail;
	m_strRegNo   = pSet->m_strRegNo;
	m_strTelNo   = pSet->m_strTelNo;
	m_strHost    = pSet->m_strHost;
	m_strKind    = pSet->m_strKind;
	m_strName    = pSet->m_strName;
	m_strType    = pSet->m_strType;
	m_timeReg    = pSet->m_timeReg;
	m_nNumPC     = pSet->m_nNumPC;
	m_wLoc       = pSet->m_wLoc;
	m_wID        = pSet->m_wID;
	m_strIPAddress = pSet->m_strIPAddress;
	m_strEtc     = pSet->m_strEtc;	
	m_nTotalTime = 0;
}

CClient::CClient()
{
	m_strAddress = _T("");
	m_strUseLine = _T("");
	m_strZipCode = _T("");
	m_strEMail   = _T("");
	m_strRegNo   = _T("");
	m_strTelNo   = _T("");
	m_strHost    = _T("");
	m_strKind    = _T("");
	m_strName    = _T("");
	m_strType    = _T("");
	m_timeReg    = 0;
	m_nNumPC     = 0;
	m_wLoc       = 0;
	m_wID        = 0;
	m_nTotalTime = 0;
	m_strIPAddress = _T("");
	m_strEtc     = _T("");	
}

//////////////////////////////////////////////////////////////////////
// CSelItem Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSelItem::CSelItem(int nType, CObject* pObject) 
{ 
	m_nType = nType; 
	m_pObject = pObject; 
}

//////////////////////////////////////////////////////////////////////
// CFileInfo Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileInfo::CFileInfo(LPCTSTR lpszFileName, 
					 LPCTSTR lpszPathName, 
					 BYTE bComp, WORD wVer)
{
	m_strFileName = lpszFileName;
	if (bComp)
	{
		CString strPath;
		strPath.Format (_T("%s\\%s"), lpszPathName, lpszFileName);

		TCHAR szShortPath[MAX_PATH];
		if (!::GetShortPathName (strPath, szShortPath, MAX_PATH))
		{
			LPVOID lpMsgBuf;
			::FormatMessage (
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
				GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR) &lpMsgBuf, 0, NULL);
			CString strMsg = (LPTSTR)lpMsgBuf;
			::LocalFree( lpMsgBuf );
			AfxMessageBox (strMsg);
		}
		else
		{
			TCHAR drive[_MAX_DRIVE];
			TCHAR dir[_MAX_DIR];
			TCHAR fname[_MAX_FNAME];
			TCHAR ext[_MAX_EXT];
			_splitpath(szShortPath, drive, dir, fname, ext);
			if (dir[0])
				dir[strlen(dir) - 1] = 0;
			if (!ext[1])
				ext[2] = 0;
			ext[1] = '_';
			m_strCompName.Format (_T("%s%s"), fname, ext);
		}
	}
	m_strFileName.MakeUpper ();
	m_strCompName.MakeUpper ();
	m_wVer = wVer;
}

CFileInfo::CFileInfo(LPCTSTR lpszFileName, 
					 LPCTSTR lpszCompName, 
					 WORD wVer)
{
	m_strFileName = lpszFileName;
	m_strCompName = lpszCompName;
	m_strFileName.MakeUpper ();
	m_strCompName.MakeUpper ();
	m_wVer = wVer;
}

CFileInfo::~CFileInfo()
{

}

BOOL CFileInfo::CreateCompFile(LPCTSTR lpszPath)
{
	CString strPath;
	strPath.Format (_T("%s\\%s"), lpszPath, m_strFileName);

	TCHAR szShortPath[MAX_PATH];
	if (!::GetShortPathName (strPath, szShortPath, MAX_PATH))
		return FALSE;

	CString strCmdLine;
	strCmdLine.Format (_T("compress.exe %s %s"), szShortPath, m_strCompName);

	STARTUPINFO			sui;
	PROCESS_INFORMATION	pi;

	memset (&sui, 0, sizeof (STARTUPINFO));
	sui.cb			= sizeof (STARTUPINFO);

	return CreateProcess (NULL, (char*)LPCTSTR (strCmdLine),
		NULL, NULL, FALSE, 0, NULL, lpszPath, &sui, &pi);
}

/////////////////////////////////////////////////////////////////////////////
// CServiceManagerDoc

IMPLEMENT_DYNCREATE(CServiceManagerDoc, CDocument)

BEGIN_MESSAGE_MAP(CServiceManagerDoc, CDocument)
	//{{AFX_MSG_MAP(CServiceManagerDoc)
	ON_COMMAND(ID_SERVER_ADD, OnServerAdd)
	ON_UPDATE_COMMAND_UI(ID_SERVER_ADD, OnUpdateServerAdd)
	ON_COMMAND(ID_SERVER_DEL, OnServerDel)
	ON_UPDATE_COMMAND_UI(ID_SERVER_DEL, OnUpdateServerDel)
	ON_COMMAND(ID_SERVER_CONNECT, OnServerConnect)
	ON_UPDATE_COMMAND_UI(ID_SERVER_CONNECT, OnUpdateServerConnect)
	ON_COMMAND(ID_SERVER_CONFIG, OnServerConfig)
	ON_UPDATE_COMMAND_UI(ID_SERVER_CONFIG, OnUpdateServerConfig)
	ON_COMMAND(ID_SERVICE_CONFIG, OnServiceConfig)
	ON_UPDATE_COMMAND_UI(ID_SERVICE_CONFIG, OnUpdateServiceConfig)
	ON_COMMAND(ID_SERVICE_DEL, OnServiceDel)
	ON_UPDATE_COMMAND_UI(ID_SERVICE_DEL, OnUpdateServiceDel)
	ON_COMMAND(ID_CONTROL_START, OnControlStart)
	ON_COMMAND(ID_CONTROL_STOP, OnControlStop)
	ON_COMMAND(ID_CONTROL_PAUSE, OnControlPause)
	ON_COMMAND(ID_CONTROL_CONTINUE, OnControlContinue)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_START, OnUpdateControlStart)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_STOP, OnUpdateControlStop)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_PAUSE, OnUpdateControlPause)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_CONTINUE, OnUpdateControlContinue)
	ON_UPDATE_COMMAND_UI(ID_VERSION_SET, OnUpdateVersion)
	ON_COMMAND(ID_VERSION_SET, OnVersionSet)
	ON_COMMAND(ID_VERSION_DEL, OnVersionDel)
	ON_COMMAND(ID_VERSION_CONFIG, OnVersionConfig)
	ON_COMMAND(ID_VERSION_COMPRESS, OnVersionCompress)
	ON_COMMAND(ID_VERSION_ADD, OnVersionAdd)
	ON_COMMAND(ID_MANAGE_NEWSERIAL, OnManageNewserial)
	ON_COMMAND(ID_MANAGE_FINDUSER, OnManageFinduser)
	ON_UPDATE_COMMAND_UI(ID_SERVICE_VALUE, OnUpdateServiceValue)
	ON_COMMAND(ID_SERVICE_VALUE, OnServiceValue)
	ON_COMMAND(ID_MANAGE_CONVSERIAL, OnManageConvserial)
	ON_COMMAND(ID_CONTROL_STARTALL, OnControlStartall)
	ON_COMMAND(ID_CONTROL_STOPALL, OnControlStopall)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_STARTALL, OnUpdateControlAll)
	ON_UPDATE_COMMAND_UI(ID_MANAGE_CONUSER, OnUpdateManageConuser)
	ON_COMMAND(ID_MANAGE_CONUSER, OnManageConuser)
	ON_COMMAND(ID_MANAGE_BANK, OnManageBank)
	ON_COMMAND(ID_MANAGE_DISCONNECT, OnManageDisconnect)
	ON_COMMAND(ID_SERVICE_GETVALUE, OnServiceGetvalue)
	ON_COMMAND(ID_VIEW_SERIAL, OnViewSerial)
	ON_COMMAND(ID_VIEW_LOG, OnViewLog)
	ON_COMMAND(ID_VIEW_BANK, OnViewBank)
	ON_COMMAND(ID_CLIENT_NEW, OnClientNew)
	ON_COMMAND(ID_CLIENT_SEARCH, OnClientSearch)
	ON_COMMAND(ID_MANAGE_SERIALUSE, OnManageSerialuse)
	ON_UPDATE_COMMAND_UI(ID_MANAGE_CONVSERIAL, OnUpdateManage)
	ON_COMMAND(ID_LOG_SEARCH, OnLogSearch)
	ON_COMMAND(ID_MANAGE_BADID, OnManageBadid)
	ON_COMMAND(ID_MANAGE_BADIDLIST, OnManageBadidlist)
	ON_COMMAND(ID_MANAGE_CLIENTLOG, OnManageClientlog)
	ON_COMMAND(ID_FILE_SAVELOG, OnFileSavelog)
	ON_COMMAND(ID_MANAGE_CURRENTUSER, OnManageCurrentuser)
	ON_COMMAND(ID_MANAGE_CLIENTPAYLIST, OnManageClientpaylist)
	ON_UPDATE_COMMAND_UI(ID_MANAGE_CLIENTPAYLIST, OnUpdateManageClientpaylist)
	ON_COMMAND(ID_MANAGE_PRINTBILL, OnManagePrintbill)
	ON_COMMAND(ID_LIST_PRINT, OnListPrint)
	ON_COMMAND(ID_LIST_PRINT_PREVIEW, OnListPrintPreview)
	ON_COMMAND(ID_SAVE_LIST, OnSaveList)
	ON_COMMAND(ID_PRINT_ADDRESS, OnPrintAddress)
	ON_COMMAND(ID_FINISHDAY, OnFinishday)
	ON_UPDATE_COMMAND_UI(ID_FINISHDAY, OnUpdateFinishday)
	ON_COMMAND(ID_CLIENT_BANK, OnClientBank)
	ON_COMMAND(ID_PRINT_BANK, OnPrintBank)
	ON_COMMAND(ID_NOTICE_SET, OnNoticeSet)
	ON_COMMAND(ID_NOTICE_SESSION, OnNoticeSession)
	ON_COMMAND(ID_FILE_DIR_COMPRESS, OnFileDirCompress)
	ON_UPDATE_COMMAND_UI(ID_VERSION_DEL, OnUpdateVersion)
	ON_UPDATE_COMMAND_UI(ID_VERSION_CONFIG, OnUpdateVersion)
	ON_UPDATE_COMMAND_UI(ID_VERSION_COMPRESS, OnUpdateVersion)
	ON_UPDATE_COMMAND_UI(ID_VERSION_ADD, OnUpdateVersion)
	ON_UPDATE_COMMAND_UI(ID_MANAGE_FINDUSER, OnUpdateManage)
	ON_UPDATE_COMMAND_UI(ID_MANAGE_NEWSERIAL, OnUpdateManage)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_STOPALL, OnUpdateControlAll)
	ON_UPDATE_COMMAND_UI(ID_MANAGE_BANK, OnUpdateManage)
	ON_UPDATE_COMMAND_UI(ID_MANAGE_DISCONNECT, OnUpdateManage)
	ON_UPDATE_COMMAND_UI(ID_SERVICE_GETVALUE, OnUpdateServiceValue)
	ON_UPDATE_COMMAND_UI(ID_CLIENT_NEW, OnUpdateManage)
	ON_UPDATE_COMMAND_UI(ID_CLIENT_SEARCH, OnUpdateManage)
	ON_UPDATE_COMMAND_UI(ID_MANAGE_SERIALUSE, OnUpdateManageConuser)
	ON_UPDATE_COMMAND_UI(ID_LOG_SEARCH, OnUpdateManage)
	ON_UPDATE_COMMAND_UI(ID_MANAGE_BADID, OnUpdateManage)
	ON_UPDATE_COMMAND_UI(ID_MANAGE_BADIDLIST, OnUpdateManage)
	ON_UPDATE_COMMAND_UI(ID_MANAGE_CLIENTLOG, OnUpdateManage)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVELOG, OnUpdateManage)
	ON_UPDATE_COMMAND_UI(ID_MANAGE_CURRENTUSER, OnUpdateManage)
	ON_UPDATE_COMMAND_UI(ID_CLIENT_BANK, OnUpdateManage)
	ON_UPDATE_COMMAND_UI(ID_PRINT_BANK, OnUpdateManage)
	ON_UPDATE_COMMAND_UI(ID_FILE_DIR_COMPRESS, OnUpdateFileDirCompress)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServiceManagerDoc construction/destruction

CServiceManagerDoc::CServiceManagerDoc()
{
	m_imageTree.Create (IDB_TREEIMAGE, 16, 1, RGB (255, 255, 255));
	m_pUserManager = NULL;
	m_pFileManager = NULL;
	m_nListStatus = 0;
	m_wGameVer = 0;
	m_pSelItem = NULL;
	m_nCountScale = 100;
	m_nCountRange = 60;
	m_wPrintType = PRINT_DEFAULT;
	::srand (GetTickCount ());
}

CServiceManagerDoc::~CServiceManagerDoc()
{

}

BOOL CServiceManagerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void CServiceManagerDoc::DeleteContents() 
{
	while (!m_listServer.IsEmpty ())
		delete m_listServer.RemoveHead ();

	while (!m_listFile.IsEmpty ())
		delete m_listFile.RemoveHead ();

	while (!m_listSelItem.IsEmpty ())
		delete m_listSelItem.RemoveHead ();

	while (!m_listLog.IsEmpty ())
		delete m_listLog.RemoveHead ();

	while (!m_listCount.IsEmpty ())
		delete m_listCount.RemoveHead ();

	while (!m_listBank.IsEmpty ())
		delete m_listBank.RemoveHead ();

	while (!m_listSerial.IsEmpty ())
		delete m_listSerial.RemoveHead ();

	while (!m_listLog.IsEmpty ())
		delete m_listLog.RemoveHead ();

	while (!m_listBadID.IsEmpty ())
		delete m_listBadID.RemoveHead ();

	while (!m_listClient.IsEmpty ())
		delete m_listClient.RemoveHead ();

	while (!m_listClientPay.IsEmpty ())
		delete m_listClientPay.RemoveHead ();


	m_listSession.RemoveAll ();
	m_listGame.RemoveAll ();

	m_strGameID = m_strPasswd = _T("");

	m_pUserManager = NULL;
	m_pFileManager = NULL;
	m_wGameVer = 0;
	m_pSelItem = NULL;
	m_fSearchNow = FALSE;
	
	CDocument::DeleteContents();
}

/////////////////////////////////////////////////////////////////////////////
// CServiceManagerDoc serialization

void CServiceManagerDoc::Serialize(CArchive& ar)
{
	m_listServer.Serialize (ar);
	if (ar.IsStoring())
	{
		ar << m_strGameID;
	}
	else
	{
		ar >> m_strGameID;
		m_strGameID.MakeUpper ();

		POSITION pos = m_listServer.GetHeadPosition ();
		while (pos)
		{
			CServer* pServer = (CServer*)m_listServer.GetNext (pos);
			pServer->m_pDoc = this;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CServiceManagerDoc diagnostics

#ifdef _DEBUG
void CServiceManagerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CServiceManagerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CServiceManagerDoc Operations

CServer* CServiceManagerDoc::FindServer(LPCTSTR lpszServerName)
{
	POSITION pos = m_listServer.GetHeadPosition ();
	while (pos)
	{
		CServer* pServer = (CServer*)m_listServer.GetNext (pos);
		if (pServer->m_strName == lpszServerName)
			return pServer;
	}
	return NULL;
}

CString CServiceManagerDoc::GetSessionName(int nSessionID)
{
	POSITION pos = m_listSession.GetHeadPosition ();
	while (pos)
	{
		CSession* pSession = (CSession*)m_listSession.GetNext (pos);
		if (pSession->m_nServerID == nSessionID)
			return pSession->m_strName;
	}
	return CString (_T("Unknown"));
}

/////////////////////////////////////////////////////////////////////////////
// CServiceManagerDoc commands


void CServiceManagerDoc::OnServerAdd() 
{
	CServer* pServer = new CServer (this);

	CServerConfigDlg dlg;
	dlg.m_pListAddr = &pServer->m_listAddr;
	if (dlg.DoModal () == IDOK)
	{
		pServer->m_strName = dlg.m_strName;
		pServer->m_strAddr = dlg.m_strAddr;
		m_listServer.AddTail (pServer);

		UpdateAllViews (NULL, UPDATE_ADDSERVER, pServer);
	}
}

void CServiceManagerDoc::OnUpdateServerAdd(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (TRUE);
}

void CServiceManagerDoc::OnServerDel() 
{
	CServer* pServer = NULL;
	if (m_pSelItem && m_pSelItem->m_nType == CSelItem::selServer)
		pServer = (CServer*)m_pSelItem->m_pObject;
	else
	{
		CSelServerDlg dlg;
		dlg.m_nCheck = 0;
		dlg.m_pListServer = &m_listServer;
		if (dlg.DoModal () == IDCANCEL)
			return;
		pServer = FindServer (dlg.m_strServer);
	}
	if (!pServer)
		return;
	POSITION pos = m_listServer.Find (pServer);
	m_listServer.RemoveAt (pos);
	UpdateAllViews (NULL, UPDATE_DELSERVER, pServer);
	delete pServer;
}

void CServiceManagerDoc::OnUpdateServerDel(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_listServer.GetCount () != 0);
}

void CServiceManagerDoc::OnServerConnect() 
{
	CLoginDlg dlg;
	dlg.m_strGameID = m_strGameID;
	if (dlg.DoModal () == IDOK)
	{
		m_nSeed = 1;

		m_strGameID = dlg.m_strGameID;
		m_strUserID = dlg.m_strUserID;
		m_strPasswd = dlg.m_strPasswd;

		int nLen = m_strGameID.GetLength ();
		if (nLen > 4)
			nLen = 4;
		for (int i = 0; i < 4; i++)
			m_nSeed *= (int)m_strGameID[i];

		CString strConnect;
		strConnect.Format (_T("DSN=%s;UID=%s;PWD=%s"), 
			m_strGameID, m_strUserID, m_strPasswd);
		g_db.SetLoginTimeout (30);
		g_db.SetQueryTimeout (60);
		if (!g_db.OpenEx (strConnect))
			return;

		POSITION pos = m_listServer.GetHeadPosition ();
		while (pos)
		{
			CServer* pServer = (CServer*)m_listServer.GetNext (pos);
			if (!pServer->m_fConnect)
				pServer->ConnectToServer ();
		}

		UpdateAllViews (NULL, UPDATE_SERVICECONFIG, this);

		CStatusBar* pBar = (CStatusBar*)(((CFrameWnd*)AfxGetMainWnd ())->GetMessageBar ());
		if (pBar)
			pBar->SetPaneText (5, m_strUserID);

		CVerSet verset (&g_db);
		if (verset.Open ())
		{
			m_nNumVer = 0;
			while (!verset.IsEOF ())
			{
				CFileInfo* pInfo = new CFileInfo (verset.m_strFileName, 
					verset.m_strCompName, verset.m_wVersion);
				m_listFile.AddTail (pInfo);
				UpdateAllViews (NULL, UPDATE_ADDFILE, pInfo);
				m_nNumVer++;
				verset.MoveNext ();
			}
			verset.Close ();
		}
	}
}

void CServiceManagerDoc::OnUpdateServerConnect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_listServer.GetCount () != 0);
}

void CServiceManagerDoc::OnServerConfig() 
{
	CServer* pServer = NULL;
	if (m_pSelItem && m_pSelItem->m_nType == CSelItem::selServer)
		pServer = (CServer*)m_pSelItem->m_pObject;
	else
	{
		CSelServerDlg dlg;
		dlg.m_nCheck = 0;
		dlg.m_pListServer = &m_listServer;
		if (dlg.DoModal () == IDCANCEL)
			return;
		pServer = FindServer (dlg.m_strServer);
	}
	if (!pServer || pServer->m_fConnect)
		return;

	CServerConfigDlg dlg;
	dlg.m_pListAddr = &pServer->m_listAddr;
	dlg.m_strName = pServer->m_strName;
	dlg.m_strAddr = pServer->m_strAddr;
	if (dlg.DoModal () == IDOK)
	{
		pServer->m_strName = dlg.m_strName;
		pServer->m_strAddr = dlg.m_strAddr;

		UpdateAllViews (NULL, UPDATE_CONFIGSERVER, pServer);
	}
}

void CServiceManagerDoc::OnUpdateServerConfig(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_listServer.GetCount () != 0);
}

void CServiceManagerDoc::OnServiceConfig() 
{
	if (GetAccessCode () != 2)
	{
		AfxMessageBox (IDS_MSG_ACCESSNOTPERMITTED);
		return;
	}

	CConfigFMPage pageFM (this);
	CConfigGSPage pageGS (this);
	CConfigUMPage pageUM (this);
	CConfigSMPage pageSM (this);

	int nSelPage = 0;
	if (m_pSelItem && m_pSelItem->m_nType == CSelItem::selService)
	{
		CService* pService = (CService*)m_pSelItem->m_pObject;
		switch (pService->m_nType)
		{
		case CService::typeFM : nSelPage = 0; break;
		case CService::typeGS : nSelPage = 1; break;
		case CService::typeUM : nSelPage = 2; break;
		case CService::typeSM : nSelPage = 3; break;
		}
	}

	CConfigSheet sheet (IDS_TITLE_CONFIG, NULL, nSelPage);

	sheet.AddPage (&pageFM);
	sheet.AddPage (&pageGS);
	sheet.AddPage (&pageUM);
	sheet.AddPage (&pageSM);

	sheet.DoModal ();
}

void CServiceManagerDoc::OnUpdateServiceConfig(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_listServer.GetCount () != 0);
}

void CServiceManagerDoc::OnServiceDel() 
{
	CService* pService = NULL;
	if (m_pSelItem && m_pSelItem->m_nType == CSelItem::selService)
		pService = (CService*)m_pSelItem->m_pObject;
	else
	{
		CSelServiceDlg dlg;
		dlg.m_pListServer = &m_listServer;
		if (dlg.DoModal () == IDOK)
		{
			CServer* pServer = FindServer (dlg.m_strServer);
			if (!pServer)
				return;
			pService = pServer->FindService (dlg.m_strService);
		}
		else
			return;
	}
	
	if (!pService)
		return;

	if (pService->m_pServer->m_nAccess != 2)
	{
		AfxMessageBox (IDS_MSG_ACCESSNOTPERMITTED);
		return;
	}

	CMsg msg;
	msg.ID (SC_REMOVE_REQ) << pService->m_strServiceName;
	pService->m_pServer->SendMsg (msg);
}

void CServiceManagerDoc::OnUpdateServiceDel(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_listServer.GetCount () != 0);
}

void CServiceManagerDoc::OnControlStart() 
{
	CService* pService = NULL;
	if (m_pSelItem && m_pSelItem->m_nType == CSelItem::selService)
		pService = (CService*)m_pSelItem->m_pObject;

	if (!pService)
		return;

	if (!pService->Start ())
	{
		AfxMessageBox (IDS_MSG_STOPFAIL);
		return;
	}
}

void CServiceManagerDoc::OnControlStop() 
{
	CService* pService = NULL;
	if (m_pSelItem && m_pSelItem->m_nType == CSelItem::selService)
		pService = (CService*)m_pSelItem->m_pObject;

	if (!pService)
		return;

	if (!pService->Stop ())
	{
		AfxMessageBox (IDS_MSG_STOPFAIL);
		return;
	}
}

void CServiceManagerDoc::OnControlPause() 
{
	CService* pService = NULL;
	if (m_pSelItem && m_pSelItem->m_nType == CSelItem::selService)
		pService = (CService*)m_pSelItem->m_pObject;

	if (!pService)
		return;

	if (!pService->Pause ())
	{
		AfxMessageBox (IDS_MSG_STOPFAIL);
		return;
	}
}

void CServiceManagerDoc::OnControlContinue() 
{
	CService* pService = NULL;
	if (m_pSelItem && m_pSelItem->m_nType == CSelItem::selService)
		pService = (CService*)m_pSelItem->m_pObject;

	if (!pService)
		return;

	if (!pService->Continue ())
	{
		AfxMessageBox (IDS_MSG_STOPFAIL);
		return;
	}
}

void CServiceManagerDoc::OnUpdateControlStart(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_pSelItem && 
		m_pSelItem->m_nType == CSelItem::selService &&
		((CService*)m_pSelItem->m_pObject)->m_dwStatus == SERVICE_STOPPED);
}

void CServiceManagerDoc::OnUpdateControlStop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_pSelItem && 
		m_pSelItem->m_nType == CSelItem::selService &&
		((CService*)m_pSelItem->m_pObject)->m_dwStatus != SERVICE_STOPPED);
}

void CServiceManagerDoc::OnUpdateControlPause(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_pSelItem && 
		m_pSelItem->m_nType == CSelItem::selService &&
		((CService*)m_pSelItem->m_pObject)->m_dwStatus == SERVICE_RUNNING);
}

void CServiceManagerDoc::OnUpdateControlContinue(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_pSelItem && 
		m_pSelItem->m_nType == CSelItem::selService &&
		((CService*)m_pSelItem->m_pObject)->m_dwStatus == SERVICE_PAUSED);
}

void CServiceManagerDoc::OnVersionSet() 
{
	CVersionDlg dlg;
	dlg.m_wGameVer = m_wGameVer;
	if (dlg.DoModal () == IDOK)
	{
		m_wGameVer = dlg.m_wGameVer;
		CMsg msg;
		msg.ID (SC_SETINTVALUE_REQ) 
			<< m_pUserManager->m_strServiceName
			<< _T("GameVer")
			<< (int)m_wGameVer;
		m_pUserManager->m_pServer->SendMsg (msg);
	}
}

void CServiceManagerDoc::OnVersionConfig() 
{
}

void CServiceManagerDoc::OnVersionCompress() 
{
	if (m_pSelItem && m_pSelItem->m_nType == CSelItem::selFile)
	{
		CFileInfo* pInfo = (CFileInfo*)m_pSelItem->m_pObject;
		if (pInfo->m_strCompName != _T(""))
		{
			pInfo->CreateCompFile (m_strSrcPath);
		}
	}
}

void CServiceManagerDoc::OnVersionAdd() 
{
	CObList listAdd;
	CAddFileDlg dlg;
	dlg.m_wGameVer = m_wGameVer;
	if (dlg.DoModal () == IDOK)
	{
		CVerSet verset (&g_db);
		if (!verset.Open ())
		{
			AfxMessageBox (IDS_MSG_INSERTFILEFAIL);
			return;
		}
		m_strSrcPath = dlg.m_strSrcPath;
		POSITION pos = dlg.m_listFileName.GetHeadPosition ();
		while (pos)
		{
			BOOL bAdd;
			CString strFileName = dlg.m_listFileName.GetNext (pos);
			verset.m_strFilter.Format (_T("strFileName=\'%s\'"), strFileName);
			verset.Requery ();

			bAdd = TRUE;
			if (!verset.IsEOF ())
			{
				if(AfxMessageBox (IDS_MSG_DUPFILE, MB_YESNO) == IDYES)
				{
					CServiceManagerView *view = (CServiceManagerView *)GetServiceManagerView();
					HTREEITEM hTreeItem = view->FindFile(view->m_hVersion, strFileName);
					if(hTreeItem)
					{
						CTreeCtrl& tree = view->GetTreeCtrl();
						CFileInfo *info = (CFileInfo *)((CSelItem *)tree.GetItemData(hTreeItem))->m_pObject;
						if(info)
						{
							verset.Delete();
							POSITION pos = m_listFile.Find (info);
							if (pos)
								m_listFile.RemoveAt (pos);
							UpdateAllViews(NULL, UPDATE_DELFILE, info);
							delete info;
						}
						else
						{
							bAdd = FALSE;
							AfxMessageBox(IDS_MSG_DELFILEFAIL);
						}
					}
					else
					{
						bAdd = FALSE;
						AfxMessageBox(IDS_MSG_DELFILEFAIL);
					}
				}
				else
				{
					bAdd = FALSE;
					AfxMessageBox(IDS_MSG_DELFILEFAIL);
				}
			}

			if(bAdd == TRUE)
			{
				CFileInfo* pInfo = new CFileInfo (strFileName, dlg.m_strSrcPath,
					(BYTE)dlg.m_fComp, (WORD)dlg.m_wGameVer);

				verset.AddNew ();
				verset.m_strFileName = pInfo->m_strFileName;
				verset.m_strCompName = pInfo->m_strCompName;
				verset.m_wVersion = pInfo->m_wVer;
				if (verset.Update ())
				{
					m_listFile.AddTail (pInfo);
					UpdateAllViews (NULL, UPDATE_ADDFILE, pInfo);
				}
			}
		}
		verset.Close ();
	}
}

void CServiceManagerDoc::OnVersionDel() 
{
	CVerSet verset (&g_db);
	if (m_pSelItem && m_pSelItem->m_nType == CSelItem::selFile)
	{
		CFileInfo* pInfo = (CFileInfo*)m_pSelItem->m_pObject;
		verset.m_strFilter.Format (_T("strFileName=\'%s\'"), 
			pInfo->m_strFileName);
		if (!verset.Open ())
		{
			AfxMessageBox (IDS_MSG_DELFILEFAIL);
			return;
		}

		if (verset.IsEOF ())
			AfxMessageBox (IDS_MSG_DELFILEFAIL);
		else
		{
			verset.Delete ();
			POSITION pos = m_listFile.Find (pInfo);
			if (pos)
				m_listFile.RemoveAt (pos);
			UpdateAllViews (NULL, UPDATE_DELFILE, pInfo);
			delete pInfo;
		}
		verset.Close ();
	}
	else
	{
		CDelFileDlg dlg;
		POSITION pos = m_listFile.GetHeadPosition ();
		while (pos)
		{
			CFileInfo* pInfo = (CFileInfo*)m_listFile.GetNext (pos);
			dlg.m_listCurFile.AddTail (pInfo);
		}
		if (dlg.DoModal () == IDOK)
		{
			if (!verset.Open ())
			{
				AfxMessageBox (IDS_MSG_DELFILEFAIL);
				return;
			}
			POSITION pos = dlg.m_listDelFile.GetHeadPosition ();
			while (pos)
			{
				CFileInfo* pInfo = (CFileInfo*)dlg.m_listDelFile.GetNext (pos);
				verset.m_strFilter.Format (_T("strFileName=\'%s\'"), 
					pInfo->m_strFileName);
				verset.Requery ();
				if (!verset.IsEOF ())
				{
					verset.Delete ();
					POSITION pos1 = m_listFile.Find (pInfo);
					if (pos1)
						m_listFile.RemoveAt (pos1);
					UpdateAllViews (NULL, UPDATE_DELFILE, pInfo);
					delete pInfo;
				}
			}
		}
	}
}

void CServiceManagerDoc::OnUpdateVersion(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (g_db.IsOpen ());
}


void CServiceManagerDoc::OnUpdateManage(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (g_db.IsOpen ());
}

void CServiceManagerDoc::OnManageNewserial() 
{
	CNewBankDlg dlgBank;
	dlgBank.m_strOper = m_strUserID;
	if (dlgBank.DoModal () != IDOK)
		return;

	if (dlgBank.m_nProc != BANK_PROC_IN)
		return;

	if (dlgBank.m_nClientID == -1 && 
		(dlgBank.m_nType == BANK_TYPE_PAYLATER || dlgBank.m_nType == BANK_TYPE_PAY))
	{
#ifdef _USE_ENGLISH
		AfxMessageBox (_T("Specific billing requires game room designation."));
#else
		AfxMessageBox (_T("종량제 과금은 게임방이 지정되어야 합니다."));
#endif
		return;
	}

	CBankSet bankset (&g_db);
	CSerialSet serialset (&g_db);
	CBankSerialSet bankserialset (&g_db);

	if (!bankset.Open () ||
		!serialset.Open () || 
		!bankserialset.Open ())
	{
		AfxMessageBox (IDS_MSG_NEWSERIALFAIL);
		return;
	}

	bankset.AddNew ();
	bankset.SetFieldDirty (&bankset.m_nID, FALSE);
	bankset.SetFieldDirty (&bankset.m_timeReg, FALSE);
	bankset.m_strBank = dlgBank.m_strBank;
	bankset.m_strName = dlgBank.m_strName;
	bankset.m_strOper = dlgBank.m_strOper;
	bankset.m_strComment = dlgBank.m_strComment;
	bankset.m_nMoney = dlgBank.m_nMoney;
	bankset.m_bType = dlgBank.m_nType;
	bankset.m_bProcess = dlgBank.m_nProc;
	if(dlgBank.m_strSoc1.IsEmpty() || dlgBank.m_strSoc2.IsEmpty())
	{
		bankset.m_strSocNo.Empty();
	}
	else
	{
		bankset.m_strSocNo = dlgBank.m_strSoc1 + _T("-") + dlgBank.m_strSoc2;
	}
	bankset.m_strTelNo = dlgBank.m_strTelNo;
	if (dlgBank.m_nClientID == -1)
		bankset.SetFieldNull (&bankset.m_wClientID, TRUE);
	else
		bankset.m_wClientID = dlgBank.m_nClientID;

	if (!bankset.Update ())
	{
		AfxMessageBox (IDS_MSG_NEWSERIALFAIL);
		return;
	}
	bankset.MoveLast ();

	if (dlgBank.m_nType == BANK_TYPE_PAY)
		return;

	for (int i = 0; i < dlgBank.m_nNumSerial; i++)
	{
		CNewSerialDlg dlg;
		if (serialset.IsEOF ())
			dlg.m_wSerial = 1;
		else
		{
			serialset.MoveLast ();
			dlg.m_wSerial = serialset.m_wSerial + 1;
			if(dlg.m_wSerial > 999999)
			{
				AfxMessageBox(IDS_MSG_NEWSERIALFAIL);
				return;
			}			
		}
		switch (bankset.m_bType)
		{
		case BANK_TYPE_ETC :	
		case BANK_TYPE_PRIVATE :	
			dlg.m_nType = 0; 
			dlg.m_nMaxReg = 1;
			dlg.m_nCurReg = 0;
			break;
		case BANK_TYPE_GAMEROOM :	
		case BANK_TYPE_PAYLATER :	
			dlg.m_nType = 1; 
			dlg.m_nMaxReg = 0;
			dlg.m_nCurReg = 1;
			break;
		}
		
		if (dlg.DoModal () != IDOK)
			return;

		serialset.AddNew ();

		serialset.SetFieldDirty (&serialset.m_wSerial);
		switch(dlg.m_nType)
		{
		case 0:
			{
				if(dlg.m_nMonth)
				{
					serialset.m_nValidDay = dlg.m_nValidTime * -3600;
				}
				else
				{
					serialset.m_nValidDay = dlg.m_nValidDay;
				}
				serialset.SetFieldNull (&serialset.m_strPasswd);
				serialset.SetFieldNull (&serialset.m_timeStart);
				serialset.SetFieldNull (&serialset.m_timeEnd);
				serialset.m_nMaxReg = dlg.m_nMaxReg;
				serialset.m_nCurReg = 0;
				serialset.m_nType = 0;
				break;
			}
		case 1:
			{
				if(dlg.m_nMonth)
				{
					serialset.m_nValidDay = dlg.m_nValidTime * -3600;
				}
				else
				{
					serialset.m_nValidDay = dlg.m_nValidDay;
				}
				serialset.m_strPasswd = dlg.m_strIPNumber;
				serialset.m_addrStart = dlg.m_nIPStart;
				serialset.m_addrEnd = dlg.m_nIPEnd;
				serialset.SetFieldNull (&serialset.m_timeStart);
				serialset.SetFieldNull (&serialset.m_timeEnd);
				serialset.m_nMaxReg = 0;
				serialset.m_nCurReg = dlg.m_nCurReg;
				serialset.m_nType = 0;
				break;
			}
		case 2:
			{
				serialset.m_nValidDay = dlg.m_nCustom1ValidDay;
				serialset.m_nMaxReg = 0;
				serialset.m_nCurReg = 0;
				serialset.m_nType = 1;
				serialset.m_timeStart = dlg.m_timeStart;
				serialset.m_timeEnd = dlg.m_timeEnd;
				break;
			}
		}

		if (serialset.Update ())
		{
			serialset.MoveLast ();

			int nDigit;
			CString strSerial2 = GetSerial2 (serialset.m_wSerial, m_nSeed, nDigit);
			CString strSerial1 = GetSerial1 (strSerial2, nDigit);

			bankserialset.AddNew ();
			bankserialset.m_nBankID = bankset.m_nID;
			bankserialset.m_strSerialCode = strSerial1 + _T("-") + strSerial2;
			bankserialset.m_wSerial = serialset.m_wSerial;
			bankserialset.Update ();
		}
	}

	ViewSerialByBank (bankset.m_nID);
}

void CServiceManagerDoc::OnManageFinduser() 
{
	CFindUserDlg dlg;
	if (dlg.DoModal () == IDOK)
	{
		CUserSet userset (&g_db);
		userset.m_strFilter.Format (_T("strUserID=\'%s\'"), dlg.m_strUserID);
		if (!userset.Open ())
			AfxMessageBox (IDS_MSG_USERFINDFAIL);
		else
		{
			if (userset.IsEOF ())
				AfxMessageBox (IDS_MSG_USERFINDFAIL);
			else
			{
				CUserDlg dlg;

				dlg.m_strUserID = userset.m_strUserID;
				dlg.m_strPasswd = userset.m_strPasswd;
				if (userset.IsFieldNull (&userset.m_wSerial))
					dlg.m_wSerial = 0;
				else
					dlg.m_wSerial = userset.m_wSerial;
				dlg.m_strName = userset.m_strName;
				dlg.m_strSocNo = userset.m_strSocNo;
				dlg.m_strAddr1 = userset.m_strAddr1;
				dlg.m_strAddr2 = userset.m_strAddr2;
				dlg.m_strTel = userset.m_strPhoneNo;
				dlg.m_strEMail = userset.m_strEMail;
				dlg.m_timeReg = userset.m_timeReg;
				dlg.m_timeLog = userset.m_timeLog;

				if (dlg.DoModal () == IDOK)
				{
					userset.Edit ();
					userset.SetFieldDirty (&userset.m_strUserID, FALSE);
					userset.SetFieldDirty (&userset.m_timeReg, FALSE);
					userset.SetFieldDirty (&userset.m_timeLog, FALSE);

					if (dlg.m_wSerial)
						userset.m_wSerial = dlg.m_wSerial;
					else
						userset.SetFieldNull (&userset.m_wSerial);
					userset.m_strPasswd = dlg.m_strPasswd;
					userset.m_strName = dlg.m_strName;
					userset.m_strSocNo = dlg.m_strSocNo;
					userset.m_strAddr1 = dlg.m_strAddr1;
					userset.m_strAddr2 = dlg.m_strAddr2;
					userset.m_strPhoneNo = dlg.m_strTel;
					userset.m_strEMail = dlg.m_strEMail;

					userset.Update ();

					if (dlg.m_fSerialSearch && dlg.m_wSerial)
					{
						if (!UpdateSerial (dlg.m_wSerial))
							AfxMessageBox (IDS_MSG_FINDSERIALFAIL);
					}
				}
			}
			userset.Close ();
		}
	}
}

void CServiceManagerDoc::OnUpdateServiceValue(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_pSelItem && 
		m_pSelItem->m_nType == CSelItem::selService);
}

void CServiceManagerDoc::OnServiceValue() 
{
	CService* pService = NULL;
	if (m_pSelItem && m_pSelItem->m_nType == CSelItem::selService)
		pService = (CService*)m_pSelItem->m_pObject;

	if (!pService)
		return;

	CRegDlg dlg;
	if (dlg.DoModal () == IDOK)
	{
		if (dlg.m_nType == 0)
		{
			CMsg msg;
			msg.ID (SC_SETSTRINGVALUE_REQ) 
				<< pService->m_strServiceName
				<< dlg.m_strName
				<< dlg.m_strValue;
			pService->m_pServer->SendMsg (msg);
		}
		else
		{
			CMsg msg;
			msg.ID (SC_SETINTVALUE_REQ) 
				<< pService->m_strServiceName
				<< dlg.m_strName
				<< dlg.m_nValue;
			pService->m_pServer->SendMsg (msg);
		}
	}
}

CFileInfo* CServiceManagerDoc::FindFileInfo (LPCTSTR lpszFileName)
{
	POSITION pos = m_listFile.GetHeadPosition ();
	while (pos)
	{
		CFileInfo* pInfo = (CFileInfo*)m_listFile.GetNext (pos);
		if (pInfo->m_strFileName = lpszFileName)
			return pInfo;
	}
	return NULL;
}

DWORD CServiceManagerDoc::CheckSerial(LPCTSTR lpszSerial1, LPCTSTR lpszSerial2)
{
	CString strID1 = lpszSerial1;
	CString strID2 = lpszSerial2;
    CString strStringCode;

	strStringCode.Format(_T("%s-%s"), lpszSerial1, lpszSerial2);

	if (strID1.GetLength () != 6 ||
		strID2.GetLength () != 7)
		return 0;

	int nNumDigit = atoi(strID1.Left (1));
	DWORD wSerial = atoi(strID2.Right (nNumDigit));

	CString strID2Check;

	//bluesky 시리얼 1000000까지 처리 
	if (wSerial > 99999)
	{
		CBankSerialSet BankSerialSet(&g_db);
		BankSerialSet.m_strFilter.Format(_T("strSerialCode=%s"), strStringCode);

		if(BankSerialSet.Open())
		{
			if(!BankSerialSet.IsEOF())
			{
				wSerial = BankSerialSet.m_wSerial;
			}
			else wSerial = 0;
			BankSerialSet.Close();
		}
		else wSerial = 0;
	}
	else
	{
		if (wSerial > 9999)
		{
			strID2Check.Format ("%02d%u", m_nSeed % 100, wSerial);
			nNumDigit = 5;
		}
		else if (wSerial > 999)
		{
			strID2Check.Format ("%03d%u", m_nSeed % 1000, wSerial);
			nNumDigit = 4;
		}
		else if (wSerial > 99)
		{
			strID2Check.Format ("%04d%u", m_nSeed % 10000, wSerial);
			nNumDigit = 3;
		}
		else if (wSerial > 9)
		{
			strID2Check.Format ("%05d%u", m_nSeed % 100000, wSerial);
			nNumDigit = 2;
		}
		else 
		{
			strID2Check.Format ("%06d%u", m_nSeed % 1000000, wSerial);
			nNumDigit = 1;
		}

		CString strID1Check;
		int nDigit[7];
		for (int i = 0; i < 7; i++)
			nDigit[i] = atoi (strID2Check.Mid (i, 1));

		int nTemp[5];
		for (int i = 0; i < 5; i++)
		{
			nTemp[i] = 0;
			for (int j = 0; j < 7; j++)
				nTemp[i] += (nDigit[j] + i + j) * (nDigit[j] + i + j);
			nTemp[i] %= 10;
		}

		strID1Check.Format ("%d%d%d%d%d%d", nNumDigit, 
			nTemp[0], nTemp[1], nTemp[2], nTemp[3], nTemp[4]);

		if (strID1Check != strID1 || strID2Check != strID2)
			return 0;
	}

	return wSerial;
}

void CServiceManagerDoc::OnManageConvserial() 
{
	CConvSerialDlg dlg;
	if (dlg.DoModal () == IDOK)
	{
		DWORD wSerial = CheckSerial (dlg.m_strSerial1, dlg.m_strSerial2);
		if (!wSerial)
		{
			AfxMessageBox (IDS_ERR_INVALIDSERIAL);
			return;
		}
		CString strMsg;
		strMsg.FormatMessage (IDS_FMT_QUERYSERIAL, wSerial);
		if (AfxMessageBox (strMsg, MB_YESNO) == IDYES)
		{
			if (!UpdateSerial (wSerial))
				AfxMessageBox (IDS_MSG_FINDSERIALFAIL);
		}
	}
}

BOOL CServiceManagerDoc::UpdateSerial(DWORD wSerial) 
{
	CSerialSet serialset (&g_db);
	serialset.m_strFilter.Format (_T("wSerial=%u"), wSerial);
	if (!serialset.Open ())
		return FALSE;

	if (serialset.IsEOF ())
	{
		serialset.Close ();
		return FALSE;
	}
	BOOL fFirstUse = serialset.IsFirstUse ();
	CNewSerialDlg dlg (!fFirstUse);

	dlg.m_wSerial = serialset.m_wSerial;
	if(serialset.m_nType == 0)
	{
		if(serialset.m_nValidDay > 0)
		{
			dlg.m_nValidDay = serialset.m_nValidDay;
			dlg.m_nValidTime = 0;
		}
		else
		{
			dlg.m_nValidTime = serialset.m_nValidDay / -3600;
			dlg.m_nValidDay = 0;
		}
		dlg.m_nType = (serialset.m_nMaxReg) ? 0 : 1;
		if(fFirstUse == 1)
		{
			dlg.m_strPasswd = _T("");
			dlg.m_strIPNumber = _T("");
		}
		else if(fFirstUse == 2)
		{
			dlg.m_strPasswd = _T("");
			dlg.m_strIPNumber = serialset.m_strPasswd;
		}
		else
		{
			if(serialset.m_nMaxReg)
			{
				dlg.m_strPasswd = serialset.m_strPasswd;
				dlg.m_strIPNumber = _T("");
			}
			else
			{
				dlg.m_strPasswd = _T("");
				dlg.m_strIPNumber = serialset.m_strPasswd;
			}
		}
		dlg.m_nIPStart = serialset.m_addrStart;
		dlg.m_nIPEnd = serialset.m_addrEnd;
		dlg.m_nMaxReg = serialset.m_nMaxReg;
		dlg.m_nCurReg = serialset.m_nCurReg;
		dlg.m_nMonth = (serialset.m_nValidDay > 0) ? 0 : 1;
		
		if (fFirstUse == 0)
		{
			dlg.m_timeStart = serialset.m_timeStart;
			dlg.m_timeEnd = serialset.m_timeEnd;
		}
	}
	else if(serialset.m_nType == 1)
	{
		dlg.m_nValidDay = 0;
		dlg.m_nValidTime = 0;
		dlg.m_nCustom1ValidDay = serialset.m_nValidDay;
		dlg.m_nType = 2;
		dlg.m_timeStart = serialset.m_timeStart;
		dlg.m_timeEnd = serialset.m_timeEnd;
	}
	else if(serialset.m_nType == 2)
	{
		dlg.m_nValidDay = serialset.m_nValidDay;
		dlg.m_nValidTime = 0;
		dlg.m_nType = 0;
		dlg.m_strPasswd = serialset.m_strPasswd;
		dlg.m_nIPStart = serialset.m_addrStart;
		dlg.m_nIPEnd = serialset.m_addrEnd;
		dlg.m_nMaxReg = serialset.m_nMaxReg;
		dlg.m_nCurReg = serialset.m_nCurReg;
		dlg.m_nMonth = 2;
		dlg.m_timeStart = serialset.m_timeStart;
		dlg.m_timeEnd = serialset.m_timeEnd;
	}

	if (dlg.DoModal () == IDOK)
	{
		serialset.Edit ();

		serialset.SetFieldDirty (&serialset.m_wSerial, FALSE);
		if(dlg.m_nType == 0 || dlg.m_nType == 1)
		{
			if(dlg.m_nMonth == 2)
			{
				serialset.m_nType = 2;
				serialset.m_nMaxReg = dlg.m_nMaxReg;
				serialset.m_nCurReg = 0;
				serialset.m_nValidDay = dlg.m_nValidDay;
				serialset.m_strPasswd = dlg.m_strPasswd;
				serialset.m_timeStart = dlg.m_timeStart;
				if(dlg.m_nCheckClose)
					serialset.m_timeEnd = dlg.m_timeEnd;
				else
					serialset.SetFieldNull (&serialset.m_timeEnd);
			}
			else
			{
				serialset.m_nType = 0;
				if(dlg.m_nType == 0)
				{
					serialset.m_nMaxReg = dlg.m_nMaxReg;
					serialset.m_nCurReg = 0;
				}
				else
				{
					serialset.m_nMaxReg = 0;
					serialset.m_nCurReg = dlg.m_nCurReg;
				}
				if(dlg.m_nMonth == 0)
				{
					serialset.m_nValidDay = dlg.m_nValidDay;
				}
				else
				{
					serialset.m_nValidDay = dlg.m_nValidTime * -3600;
				}
				if (fFirstUse)
				{
					if(dlg.m_nType == 0)
					{
						serialset.SetFieldNull (&serialset.m_strPasswd);
						serialset.m_addrStart = 0;
						serialset.m_addrEnd = 255;
					}
					else
					{
						serialset.m_strPasswd = dlg.m_strIPNumber;
						serialset.m_addrStart = dlg.m_nIPStart;
						serialset.m_addrEnd = dlg.m_nIPEnd;
					}
					serialset.SetFieldNull (&serialset.m_timeStart);
					serialset.SetFieldNull (&serialset.m_timeEnd);
				}
				else
				{
					if(dlg.m_nType == 0)
					{
						serialset.m_strPasswd = dlg.m_strPasswd;
					}
					else
					{
						serialset.m_strPasswd = dlg.m_strIPNumber;
						serialset.m_addrStart = dlg.m_nIPStart;
						serialset.m_addrEnd = dlg.m_nIPEnd;
					}
					serialset.m_timeStart = dlg.m_timeStart;
					serialset.m_timeEnd = dlg.m_timeEnd;
				}
			}
		}
		else if(dlg.m_nType == 2)
		{
			serialset.m_nType = 1;
			serialset.m_nValidDay = dlg.m_nCustom1ValidDay;
			serialset.m_timeStart = dlg.m_timeStart;
			serialset.m_timeEnd = dlg.m_timeEnd;
		}

		serialset.Update ();

		CBankSerialSet bss(&g_db);
		bss.m_strFilter.Format(_T("wSerial=%u"), wSerial);
		if(bss.Open())
		{
			if(!bss.IsEOF())
			{
				int bank_id = bss.m_nBankID;
				CBankSet bs(&g_db);
				bs.m_strFilter.Format(_T("nID=%u"), bank_id);
				if(bs.Open())
				{
					if(!bs.IsEOF())
					{
						bs.Edit();
						bs.m_strOper = m_strUserID;
						bs.Update();
					}
					bs.Close();
				}
			}
			bss.Close();
		}

		if (dlg.m_fGetBank)
			ViewBankBySerial (dlg.m_wSerial);
	}
	serialset.Close ();
	return TRUE;
}

CString CServiceManagerDoc::GetSerial2(DWORD wSerial, DWORD nSeed, int & nNumDigit)
{
	CString strID2;
	CString query;
	char g_szSaverDSN[256];
	
	// bluesky
	if (wSerial > 99999)
	{
		DWORD Serialkey;
		Serialkey = rand();
		strID2.Format ("%u%u", nSeed % 10, wSerial + Serialkey);
		nNumDigit = 6;

		strcpy(g_szSaverDSN,"ODBC;DSN=saver;UID=saver;PWD=dufmadldirl");
		if( g_db.Open(NULL,FALSE,FALSE, g_szSaverDSN)==0) 
			throw "Fail to load SAVER_DB";
		query.Format("{call insert_serial_key('%u' ,'%u')}", wSerial, Serialkey);
		TRY
		{
			g_db.ExecuteSQL(query);
		}
		CATCH(CDBException, e)
		{
#ifdef _USE_ENGLISH
			AfxMessageBox("Serial Registration Failed.\nDo not use this serial code.");
#else
            AfxMessageBox("시리얼키 등록 실패\n과금번호를 사용하지 마세요");
#endif
		}
		END_CATCH
	}
	else
	{
		if (wSerial > 9999)
		{
			strID2.Format ("%02u%u", nSeed % 100, wSerial);
			nNumDigit = 5;
		}
		else if (wSerial > 999)
		{
			strID2.Format ("%03u%u", nSeed % 1000, wSerial);
			nNumDigit = 4;
		}
		else if (wSerial > 99)
		{
			strID2.Format ("%04u%u", nSeed % 10000, wSerial);
			nNumDigit = 3;
		}
		else if (wSerial > 9)
		{
			strID2.Format ("%05u%u", nSeed % 100000, wSerial);
			nNumDigit = 2;
		}
		else 
		{
			strID2.Format ("%06u%u", nSeed % 1000000, wSerial);
			nNumDigit = 1;
		}
	}
	return strID2;
}

CString CServiceManagerDoc::GetSerial1(LPCTSTR lpszSerial2, int nNumDigit)
{
	CString strSerial1, strSerial2;
	strSerial2 = lpszSerial2;

	int nDigit[7];
	for (int i = 0; i < 7; i++)
		nDigit[i] = atoi (strSerial2.Mid (i, 1));

	int nTemp[5];
	for (int i = 0; i < 5; i++)
	{
		nTemp[i] = 0;
		for (int j = 0; j < 7; j++)
			nTemp[i] += (nDigit[j] + i + j) * (nDigit[j] + i + j);
		nTemp[i] %= 10;
	}
	strSerial1.Format ("%d%d%d%d%d%d", nNumDigit, 
		nTemp[0], nTemp[1], nTemp[2], nTemp[3], nTemp[4]);
	return strSerial1;
}

CSession* CServiceManagerDoc::FindSession(int nServID)
{
	POSITION pos = m_listSession.GetHeadPosition ();
	while (pos)
	{
		CSession* pSession = (CSession*)m_listSession.GetNext (pos);
		if (pSession->m_nServerID == nServID)
			return pSession;
	}
	return NULL;
}

void CServiceManagerDoc::OnControlStartall() 
{
	if (!m_pSelItem || m_pSelItem->m_nType != CSelItem::selServer)
		return;

	CServer* pServer = (CServer*)m_pSelItem->m_pObject;
	POSITION pos = pServer->m_listService.GetHeadPosition ();
	while (pos)
	{
		CService* pService = (CService*)pServer->m_listService.GetNext (pos);
		switch (pService->m_dwStatus)
		{
		case SERVICE_STOPPED :
			pService->Start ();
			break;
		case SERVICE_PAUSED :
			pService->Continue ();
			break;
		}
	}
}

void CServiceManagerDoc::OnControlStopall() 
{
	if (!m_pSelItem || m_pSelItem->m_nType != CSelItem::selServer)
		return;

	CServer* pServer = (CServer*)m_pSelItem->m_pObject;
	POSITION pos = pServer->m_listService.GetHeadPosition ();
	while (pos)
	{
		CService* pService = (CService*)pServer->m_listService.GetNext (pos);
		if (pService->m_dwStatus != SERVICE_STOPPED)
			pService->Stop ();
	}
}

void CServiceManagerDoc::OnUpdateControlAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_pSelItem && 
		m_pSelItem->m_nType == CSelItem::selServer &&
		((CServer*)m_pSelItem->m_pObject)->m_fConnect);
}

void CServiceManagerDoc::OnUpdateManageConuser(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_pUserManager && m_pUserManager->m_fConnect);
}

void CServiceManagerDoc::OnManageConuser() 
{
	CFindUserDlg dlg;

#ifdef _USE_ENGLISH
	dlg.m_strCaption = _T("Find connected user");
#else
	dlg.m_strCaption = _T("접속 사용자 찾기");
#endif
	if (dlg.DoModal () == IDOK)
		GetCurrentUser (dlg.m_strUserID, 0);
}

void CServiceManagerDoc::OnManageDisconnect() 
{
	CFindUserDlg dlg;

#ifdef _USE_ENGLISH
	dlg.m_strCaption = _T("Disconnect");
#else
	dlg.m_strCaption = _T("접속 강제 종료");
#endif

	if (dlg.DoModal () == IDOK)
	{
		DisconnectUser (dlg.m_strUserID);

#ifdef _USE_ENGLISH
		if (AfxMessageBox( "Add it to user ID stop list?", MB_YESNO) == IDYES)
#else
		if (AfxMessageBox( "사용자ID 정지 목록에 추가하시겠습니까?", MB_YESNO) == IDYES)
#endif
		{
			RegBadID (dlg.m_strUserID);
			return;
		}
	}
}

int CServiceManagerDoc::GetAccessCode()
{
	int nAccess = 2;
	POSITION pos = m_listServer.GetHeadPosition ();
	while (pos)
	{
		CServer* pServer = (CServer*)m_listServer.GetNext (pos);
		if (pServer->m_nAccess < nAccess)
			nAccess = pServer->m_nAccess;
	}
	return nAccess;
}

void CServiceManagerDoc::OnManageBank() 
{
	CFindBankDlg dlg;
	if (dlg.DoModal () == IDCANCEL)
		return;

	while (!m_listBank.IsEmpty ())
		delete m_listBank.RemoveHead ();

	UpdateAllViews (NULL, UPDATE_VIEWBANK);

	CBankSet bankset(&g_db);
	BOOL fFirst = TRUE;
	if (dlg.m_timeStart < dlg.m_timeEnd)
	{
		CString strStart = dlg.m_timeStart.Format (_T("%m/%d/%Y"));
		CTime timeEnd = dlg.m_timeEnd + CTimeSpan (1, 0, 0, 0);
		CString strEnd = timeEnd.Format (_T("%m/%d/%Y"));
		bankset.m_strFilter.Format (_T("'%s'<=timeReg AND timeReg<'%s' "), strStart, strEnd);
		fFirst = FALSE;
	}
	if (dlg.m_nProc != CB_ERR)
	{
		if (!fFirst)
			bankset.m_strFilter += _T("AND ");
		CString strFilter;
		strFilter.Format (_T("bProcess=%d "), dlg.m_nProc);
		bankset.m_strFilter += strFilter;
		fFirst = FALSE;
	}
	if (dlg.m_nType != CB_ERR)
	{
		if (!fFirst)
			bankset.m_strFilter += _T("AND ");
		CString strFilter;
		strFilter.Format (_T("bType=%d "), dlg.m_nType);
		bankset.m_strFilter += strFilter;
		fFirst = FALSE;
	}
	if (dlg.m_strName != _T(""))
	{
		if (!fFirst)
			bankset.m_strFilter += _T("AND ");
		CString strFilter;
		strFilter.Format (_T("strName like '%%%s%%' "), dlg.m_strName);
		bankset.m_strFilter += strFilter;
		fFirst = FALSE;
	}
	if (dlg.m_strBank != _T(""))
	{
		if (!fFirst)
			bankset.m_strFilter += _T("AND ");
		CString strFilter;
		strFilter.Format (_T("strBank='%s' "), dlg.m_strBank);
		bankset.m_strFilter += strFilter;
		fFirst = FALSE;
	}
	if (dlg.m_nClientID != -1)
	{
		if (!fFirst)
			bankset.m_strFilter += _T("AND ");
		CString strFilter;
		strFilter.Format (_T("wClientID=%d "), dlg.m_nClientID);
		bankset.m_strFilter += strFilter;
		fFirst = FALSE;
	}

	if (bankset.Open ())
	{
		while (!bankset.IsEOF ())
		{
			UpdateAllViews (NULL, UPDATE_ADDBANK, &bankset);
			bankset.MoveNext ();
		}
		bankset.Close ();
	}
}

BOOL CServiceManagerDoc::UpdateBank(int nID)
{
	CBankSet bankset (&g_db);
	BOOL b_check = FALSE;
	CBillDate timeBill;

	bankset.m_strFilter.Format (_T("nID=%d"), nID);
	if (!bankset.Open ())
		return FALSE;
	if (bankset.IsEOF ())
		return FALSE;

	if( bankset.m_bType == BANK_TYPE_PAY ) b_check = TRUE;
	CNewBankDlg dlgBank(b_check);

	bankset.m_strSocNo.TrimRight ();

	dlgBank.m_strUserID = m_strUserID;
	dlgBank.m_nBankID = nID;
	dlgBank.m_strBank = bankset.m_strBank;
	dlgBank.m_strName = bankset.m_strName;
	dlgBank.m_strOper = bankset.m_strOper;
	dlgBank.m_strComment = bankset.m_strComment;
	dlgBank.m_nMoney = bankset.m_nMoney;
	dlgBank.m_timeBank = bankset.m_timeReg;
	dlgBank.m_strTelNo = bankset.m_strTelNo;
	dlgBank.m_strSoc1 = bankset.m_strSocNo.Left(6);
	dlgBank.m_strSoc2 = bankset.m_strSocNo.Right (7);

	if (!bankset.IsFieldNull (&bankset.m_bType))
		dlgBank.m_nType = bankset.m_bType;
	else
		dlgBank.m_nType = BANK_TYPE_ETC;
	if (!bankset.IsFieldNull (&bankset.m_bProcess))
		dlgBank.m_nProc = bankset.m_bProcess;
	else
		dlgBank.m_nProc = BANK_PROC_IN;
	if (!bankset.IsFieldNull (&bankset.m_wClientID))
	{
		CClientSet clientset(&g_db);
		clientset.m_strFilter.Format (_T("wID = %d"), bankset.m_wClientID);
		if (clientset.Open () && !clientset.IsEOF())
		{
			dlgBank.m_nClientID = bankset.m_wClientID;
			dlgBank.m_strClient = clientset.m_strName;
		}

		if(clientset.IsOpen()) clientset.Close();
	}

	if (dlgBank.DoModal () == IDOK)
	{
		if (dlgBank.m_fGetSerial)
			ViewSerialByBank (nID);
		else
		{
			bankset.Edit();
			bankset.m_strBank = dlgBank.m_strBank;
			bankset.m_strName = dlgBank.m_strName;
			bankset.m_strOper = m_strUserID;
			bankset.m_strComment = dlgBank.m_strComment;
			bankset.m_nMoney = dlgBank.m_nMoney;
			bankset.m_timeReg = dlgBank.m_timeBank;
			bankset.m_strTelNo = dlgBank.m_strTelNo;
			if(dlgBank.m_strSoc1.IsEmpty() || dlgBank.m_strSoc2.IsEmpty())
			{
				bankset.m_strSocNo.Empty();
			}
			else
			{
				bankset.m_strSocNo = dlgBank.m_strSoc1 + _T("-") + dlgBank.m_strSoc2;
			}
			bankset.m_bType = dlgBank.m_nType;
			bankset.m_bProcess = dlgBank.m_nProc;
			if (dlgBank.m_nClientID == -1)
				bankset.SetFieldNull (&bankset.m_wClientID);
			else
				bankset.m_wClientID = dlgBank.m_nClientID;

			bankset.Update();
			UpdateAllViews( NULL, UPDATE_UPDATEBANK, &bankset);
		}

		if( dlgBank.m_checkTax && dlgBank.m_nProc != BANK_PROC_STOP && timeBill.DoModal() == IDOK )
		{
			m_timeStart = timeBill.m_timeBill;
			m_nMoney = dlgBank.m_nMoney;
			m_nType = dlgBank.m_nType;
			m_wID = bankset.m_wClientID;
			m_wPrintType = PRINT_TAX;

			MainViewActivate();
			AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_FILE_PRINT_PREVIEW);
		}
	}
	if(bankset.IsOpen()) bankset.Close();

	return TRUE;
}

void CServiceManagerDoc::ViewBankBySerial(DWORD wSerial)
{
	CBankSerialSet bankserialset (&g_db);
	bankserialset.m_strFilter.Format (_T("wSerial=%u"), wSerial);
	if (!bankserialset.Open ())
	{
		AfxMessageBox (IDS_MSG_BANKSERIALFAIL);
		return;
	}
	if (bankserialset.IsEOF ())
	{
		AfxMessageBox (IDS_MSG_BANKSERIALFAIL);
		return;
	}

	UpdateBank (bankserialset.m_nBankID);
}

void CServiceManagerDoc::ViewSerialByBank(int nBankID)
{
	CBankSerialSet bankserialset (&g_db);
	bankserialset.m_strFilter.Format (_T("nBankID=%u"), nBankID);
	if (!bankserialset.Open ())
	{
		AfxMessageBox (IDS_MSG_BANKSERIALFAIL);
		return;
	}

	CBankSerialDlg dlg;
	CDWordArray arraySerial;
	while (!bankserialset.IsEOF ())
	{
		dlg.m_arrayCode.Add (bankserialset.m_strSerialCode);
		arraySerial.Add (bankserialset.m_wSerial);

		bankserialset.MoveNext ();
	}

	if (dlg.DoModal () == IDOK && dlg.m_nIndex != LB_ERR)
	{
		DWORD wSerial = arraySerial[dlg.m_nIndex];
		if (dlg.m_fReg)
		{
			CBankSet bankset (&g_db);
			bankset.m_strFilter.Format (_T("nID = %u"), nBankID);
			if (!bankset.Open ())
			{
				AfxMessageBox (IDS_MSG_BANKSERIALFAIL);
				return;
			}
			if (bankset.IsEOF () || bankset.IsFieldNull (&bankset.m_wClientID))
			{
				AfxMessageBox (IDS_MSG_BANKSERIALFAIL);
				return;
			}
			
			CClientSerialSet clientserialset (&g_db);
			if (!clientserialset.Open ())
			{
				AfxMessageBox (IDS_MSG_CLIENTSERIALFAIL);
				return;
			}
			clientserialset.AddNew ();
			clientserialset.m_wSerial = wSerial;
			clientserialset.m_wClientID = bankset.m_wClientID;
			clientserialset.m_nLastLogID = 0;
			clientserialset.m_bProcess = CLIENT_SERIAL_USE;
			if (!clientserialset.Update ())
			{
				AfxMessageBox (IDS_MSG_CLIENTSERIALFAIL);
				return;
			}
		}
		else
		{
			CSerialSet serialset (&g_db);
			serialset.m_strFilter.Format (_T("wSerial=%u"), bankserialset.m_wSerial);
			if (!serialset.Open () || serialset.IsEOF ())
			{
				AfxMessageBox (IDS_MSG_BANKSERIALFAIL);
				return;
			}
			UpdateSerial (wSerial);
		}
	}
}

void CServiceManagerDoc::OnServiceGetvalue() 
{
	CService* pService = NULL;
	if (m_pSelItem && m_pSelItem->m_nType == CSelItem::selService)
		pService = (CService*)m_pSelItem->m_pObject;

	if (!pService)
		return;

	CRegDlg dlg;
	if (dlg.DoModal () == IDOK)
	{
		if (dlg.m_nType == 0)
		{
			CMsg msg;
			msg.ID (SC_GETSTRINGVALUE_REQ) 
				<< pService->m_strServiceName
				<< dlg.m_strName;
			pService->m_pServer->SendMsg (msg);
		}
		else
		{
			CMsg msg;
			msg.ID (SC_GETINTVALUE_REQ) 
				<< pService->m_strServiceName
				<< dlg.m_strName;
			pService->m_pServer->SendMsg (msg);
		}
	}
}

void CServiceManagerDoc::OnViewSerial() 
{
	UpdateAllViews (NULL, UPDATE_VIEWSERIAL);
}

void CServiceManagerDoc::OnViewLog() 
{
	UpdateAllViews (NULL, UPDATE_VIEWLOG);
}

void CServiceManagerDoc::OnViewBank() 
{
	UpdateAllViews (NULL, UPDATE_VIEWBANK);
}

void CServiceManagerDoc::OnClientNew() 
{
	CClientDlg dlg;
	if (dlg.DoModal () == IDOK)
	{
		CClientSet clientset (&g_db);
		if (!clientset.Open ())
		{
			AfxMessageBox (IDS_MSG_NEWCLIENTFAIL);
			return;
		}
		if(!clientset.CanAppend())
		{
			AfxMessageBox (IDS_MSG_NEWCLIENTFAIL);
			return;
		}		

		clientset.AddNew ();
		clientset.SetFieldDirty (&clientset.m_wID, FALSE);
		clientset.SetFieldDirty (&clientset.m_timeReg, FALSE);
		clientset.m_strRegNo.Format (_T("%s-%s-%s"), dlg.m_strRegNo1, dlg.m_strRegNo2, dlg.m_strRegNo3);
		clientset.m_strName = dlg.m_strName;
		clientset.m_strHost = dlg.m_strHost;
		clientset.m_strAddress = dlg.m_strAddress;
		clientset.m_strType = dlg.m_strType;
		clientset.m_strKind = dlg.m_strKind;
		clientset.m_strTelNo = dlg.m_strTelNo;
		clientset.m_strUseLine = dlg.m_strLine;
		clientset.m_strEMail = dlg.m_strEMail;
		if(dlg.m_strZip1.IsEmpty() || dlg.m_strZip2.IsEmpty())
		{
			clientset.m_strZipCode.Empty();
		}
		else
		{
			clientset.m_strZipCode = dlg.m_strZip1 + _T("-") + dlg.m_strZip2;
		}
		clientset.m_nNumPC = dlg.m_nNumPC;
		clientset.m_wLoc = dlg.m_nLoc;
		clientset.m_strIPAddress = dlg.m_strIPAddress;
		clientset.m_strEtc = dlg.m_strEtc;		
		if (!clientset.Update ())
			AfxMessageBox (IDS_MSG_NEWCLIENTFAIL);
	}
}

void CServiceManagerDoc::OnClientSearch() 
{
	CClientListDlg dlg;
	dlg.DoModal ();
}

void CServiceManagerDoc::OnManageSerialuse() 
{
	CConvSerialDlg dlg;
	if (dlg.DoModal () == IDOK)
	{
		DWORD wSerial = CheckSerial (dlg.m_strSerial1, dlg.m_strSerial2);
		if (!wSerial)
			AfxMessageBox (IDS_ERR_INVALIDSERIAL);
		else
			GetCurrentUser (NULL, wSerial);
	}
}

void CServiceManagerDoc::OnLogSearch() 
{
	CSearchLogDlg dlg;
	if (dlg.DoModal () == IDOK)
	{
		CString strStart = dlg.m_timeStart.Format (_T("%m/%d/%Y"));
		CTime timeEnd = dlg.m_timeStart + CTimeSpan (1, 0, 0, 0);
		CString strEnd = timeEnd.Format (_T("%m/%d/%Y"));

		while (!m_listLog.IsEmpty ())
			delete m_listLog.RemoveHead ();
		UpdateAllViews (NULL, UPDATE_VIEWLOG);

		CLogSet logset (&g_db);

		logset.m_strFilter.Format (_T("'%s'<=timeLogin AND timeLogin<'%s'"), strStart, strEnd);
		if (dlg.m_strUserID != _T(""))
		{
			CString strTemp;
			strTemp.Format (_T(" AND strUserID='%s'"), dlg.m_strUserID);
			logset.m_strFilter += strTemp;
		}
		if (dlg.m_strSerial1 != _T("") &&
			dlg.m_strSerial2 != _T(""))
		{
			DWORD wSerial = CheckSerial (dlg.m_strSerial1, dlg.m_strSerial2);
			if (wSerial)
			{
				CString strTemp;
				strTemp.Format (_T(" AND wSerial=%u"), wSerial);
				logset.m_strFilter += strTemp;
			}
		}

		if (!logset.Open ())
		{
			AfxMessageBox (IDS_MSG_SEARCHLOGFAIL);
			return;
		}

		while (!logset.IsEOF ())
		{
			UpdateAllViews (NULL, UPDATE_ADDLOG, &logset);
			logset.MoveNext ();
		}
		logset.Close ();
	}
}

void CServiceManagerDoc::OnManageBadid() 
{
	CFindUserDlg dlg;

#ifdef _USE_ENGLISH
	dlg.m_strCaption = _T("Stop User ID");
#else
	dlg.m_strCaption = _T("사용자ID 정지");
#endif
	if (dlg.DoModal () == IDOK)
		RegBadID (dlg.m_strUserID);
}

BOOL CServiceManagerDoc::RegBadID(LPCTSTR lpszUserID)
{
	CUserSet userset (&g_db);
	userset.m_strFilter.Format (_T("strUserID='%s'"), lpszUserID);
	if (!userset.Open () || userset.IsEOF ())
	{
		AfxMessageBox (IDS_MSG_USERFINDFAIL);
		return FALSE;
	}
	CBadIDDlg baddlg;
	if (baddlg.DoModal () == IDOK)
	{
		CBadIDSet badidset (&g_db);
		badidset.m_strFilter.Format (_T("strUserID='%s'"), userset.m_strUserID);
		if (!badidset.Open ())
		{
			AfxMessageBox (IDS_ERR_DBOPEN);
			return FALSE;
		}
		else if (!badidset.IsEOF ())
		{
			AfxMessageBox (IDS_ERR_BADIDEXIST);
			return FALSE;
		}
		else
		{
			badidset.AddNew ();
			badidset.m_timeReg = CTime::GetCurrentTime ();
			badidset.m_strUserID = userset.m_strUserID;
			badidset.m_strPasswd = userset.m_strPasswd;
			badidset.m_strOper = m_strUserID;
			badidset.m_strComment = baddlg.m_strComment;
			badidset.m_timeReturn = badidset.m_timeReg + CTimeSpan (baddlg.m_nDueDay, 0, 0, 0);
			badidset.Update ();

			userset.Edit ();
#ifdef _USE_ENGLISH
			userset.m_strPasswd = _T("Completion by force");
#else
			userset.m_strPasswd = _T("강제종료");
#endif
			userset.Update ();
		}
	}
	return TRUE;
}

void CServiceManagerDoc::OnManageBadidlist() 
{
	CBadIDSet badset (&g_db);
	if (!badset.Open ())
		AfxMessageBox (IDS_ERR_DBOPEN);

	UpdateAllViews ( NULL, UPDATE_VIEWBADID);

	while (!badset.IsEOF ())
	{
		UpdateAllViews (NULL, UPDATE_ADDBADID, &badset);
		badset.MoveNext ();
	}
}

void CServiceManagerDoc::ReturnBadID(LPCTSTR lpszUserID)
{
	CBadIDSet badset (&g_db);
	CUserSet userset(&g_db);
	badset.m_strFilter.Format (_T("strUserID='%s'"), lpszUserID);
	userset.m_strFilter.Format (_T("strUserID='%s'"), lpszUserID);
	if (!badset.Open () || !userset.Open ())
		AfxMessageBox (IDS_ERR_DBOPEN);
	else if (badset.IsEOF () || userset.IsEOF ())
		AfxMessageBox (IDS_MSG_USERFINDFAIL);
	else
	{
		userset.Edit ();
		userset.m_strPasswd = badset.m_strPasswd;
		userset.Update ();

		badset.Delete ();

		AfxMessageBox (IDS_MSG_RETURNBADID);
	}
}

void CServiceManagerDoc::OnManageClientlog() 
{
	CConvSerialDlg dlg;
	if (dlg.DoModal () == IDOK)
	{
		DWORD wSerial = CheckSerial (dlg.m_strSerial1, dlg.m_strSerial2);
		if (!wSerial)
		{
			AfxMessageBox (IDS_ERR_INVALIDSERIAL);
			return;
		}

		CClientLogSet logset (&g_db);
		logset.m_strFilter.Format (_T("wSerial=%u"), wSerial);
		if (!logset.Open ())
		{
			AfxMessageBox (IDS_ERR_DBOPEN);
			return;
		}

		while (!m_listLog.IsEmpty ())
			delete m_listLog.RemoveHead ();
		UpdateAllViews (NULL, UPDATE_VIEWLOG);

		while (!logset.IsEOF ())
		{
			UpdateAllViews (NULL, UPDATE_ADDCLIENTLOG, &logset);
			logset.MoveNext ();
		}
		logset.Close ();
	}
}

void CServiceManagerDoc::OnFileSavelog() 
{
	CFileDialog dlg (FALSE, _T("txt"), NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Text Files (*.TXT)|*.txt||"));
	if (dlg.DoModal () == IDOK)
	{
		CStdioFile file (dlg.GetPathName (), CFile::modeCreate | CFile::modeWrite);
#ifdef _USE_ENGLISH
		file.WriteString (_T("User ID\tLogin\tLogout\tUse Time(sec.)\tIP Address\n"));
#else
		file.WriteString (_T("사용자ID\t로그인\t로그아웃\t이용시간(초)\tIP주소\n"));
#endif
		POSITION pos = m_listLog.GetHeadPosition ();
		while (pos)
		{
			CLog* pLog = (CLog*)m_listLog.GetNext (pos);
			CString strLog, strLogin, strLogout;
			strLogin = pLog->m_timeStart.Format (_T("%m/%d %H:%M"));
			strLogout = pLog->m_timeEnd.Format (_T("%m/%d %H:%M"));
			strLog.Format (_T("%s\t%s\t%s\t%d\t%s\n"),
				pLog->m_strUserID, strLogin, strLogout, pLog->m_nUseTime, pLog->m_strIPAddr);
			file.WriteString (strLog);
		}
	}
}

void CServiceManagerDoc::OnManageCurrentuser() 
{
	GetCurrentUser( NULL, 0);
}


void CServiceManagerDoc::DisconnectUser(LPCTSTR lpszUserID)
{
	CCurrentUserSet curset (&g_db);
	curset.m_strFilter.Format (_T("strClientID='%s'"), lpszUserID);
	if (!curset.Open ())
	{
		AfxMessageBox (IDS_ERR_DBOPEN);
		return;
	}
	if (curset.IsEOF ())
	{
		AfxMessageBox (IDS_MSG_CONUSERNOTFOUND);
		return;
	}

	if (m_pUserManager)
		m_pUserManager->KickoutUser (curset.m_strClientID, curset.m_nServiceID);
}

void CServiceManagerDoc::GetCurrentUser(LPCTSTR lpszUserID, DWORD wSerial)
{
	while (!m_listLog.IsEmpty ())
		delete m_listLog.RemoveHead ();

	CCurrentUserSet curuser (&g_db);
	if (lpszUserID)
		curuser.m_strFilter.Format (_T("strClientID='%s' "), lpszUserID);
	if (wSerial)
	{
		if (lpszUserID)
			curuser.m_strFilter += _T("AND ");
		curuser.m_strFilter.Format (_T("wSerial=%u "), wSerial);
	}

	if (!curuser.Open ())
	{
		AfxMessageBox (IDS_ERR_DBOPEN);
		return;
	}

	while (!curuser.IsEOF ())
	{
		CLog* pLog = new CLog (&curuser);
		m_listLog.AddTail (pLog);
		curuser.MoveNext ();
	}
	curuser.Close ();

	UpdateAllViews (NULL, UPDATE_VIEWLOG);
}

void CServiceManagerDoc::OnManageClientpaylist() 
{
	// TODO: Add your command handler code here
	CClientPayDlg dlg;
	long nMonth;

	if( dlg.DoModal() != IDOK ) return;
	m_listClient.RemoveAll();

	for( nMonth=dlg.m_nFrom; nMonth <=dlg.m_nTo; nMonth++) SetClientList(nMonth);
	UpdateAllViews( NULL, UPDATE_VIEWCLIENT, &(dlg.m_listClient));
}

void CServiceManagerDoc::OnUpdateManageClientpaylist(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(g_db.IsOpen ());
}

void CServiceManagerDoc::MonyForm( CString* strSource)
{
	int index, pos, nCount = (strSource->GetLength() - 1 ) / 3;

	strSource->MakeReverse();
	for( pos = 3, index = 0; index < nCount; index++, pos += 4 ) strSource->Insert( pos, ',');
	strSource->MakeReverse();
}

void CServiceManagerDoc::SetPayList( long MonthFilter, int IDFilter)
{
	CClientPaySet payset( &g_db, MonthFilter, IDFilter);

	m_listClientPay.RemoveAll();
	if (!payset.Open ())
	{
		AfxMessageBox (IDS_ERR_DBOPEN);
		return;
	}

	while (!payset.IsEOF ())
	{
		CClientPay* pObj = new CClientPay(&payset);
		m_listClientPay.AddTail(pObj);

		payset.MoveNext ();
	}
	payset.Close();
}

void CServiceManagerDoc::AddClient( CClientSet* pSet, int Year, int Month)
{
	CClient* pObj = new CClient(pSet);
	CClientPay *pFind;
	POSITION pos;

	pObj->m_nTotalTime = 0;
	pObj->m_wMonth = Month;
	pObj->m_wYear = Year;

	for( pos = m_listClientPay.GetHeadPosition(); pos != NULL; )
	{
		pFind = (CClientPay*) m_listClientPay.GetNext(pos);
		if( pFind->m_wClientID == pObj->m_wID ) pObj->m_nTotalTime += pFind->m_nUseTime;
	}
	if(pObj->m_nTotalTime) m_listClient.AddTail(pObj);
}

void CServiceManagerDoc::GetPayDetail( CString& strRegNo, CString& strMonth)
{
	CClient* pObj;
	POSITION pos;
	CString dumy;
	long nMonth;
	int wID = 0;

	strMonth = strMonth.Mid( 19, 9);
	dumy = strMonth.Left(4);
	strMonth = strMonth.Right(2);

	nMonth = atol(dumy)*100 + atoi(strMonth);

	for( pos = m_listClient.GetHeadPosition(); pos != NULL && !wID; )
	{
		pObj = (CClient*) m_listClient.GetNext(pos);
		if( strRegNo.Compare(pObj->m_strRegNo) == 0 ) wID = pObj->m_wID;
	}

	if(!wID)
	{
#ifdef _USE_ENGLISH
		AfxMessageBox(_T("Can't find use history by billing."));
#else
		AfxMessageBox(_T("과금별 사용내역을 찾을 수 없읍니다."));
#endif
		return;
	}

	CPayDetailDlg dlg( (char*) LPCTSTR(pObj->m_strName), nMonth, wID);
	dlg.DoModal();
}

void CServiceManagerDoc::SetClientList( long& nMonth)
{
	CClientSet clientset(&g_db);
	int Year, Month;

	Year  = nMonth/100;
	Month = nMonth - Year*100;

	if( Month > 12 )
	{
		Year++; Month = 1;
		nMonth = Year*100 + Month;
	}
	SetPayList(nMonth);

	if (!clientset.Open ())
	{
		AfxMessageBox (IDS_ERR_DBOPEN);
		return;
	}

	while(!clientset.IsEOF())
	{
		AddClient( &clientset, Year, Month);
		clientset.MoveNext ();
	}
	clientset.Close();
}

void CServiceManagerDoc::OnManagePrintbill() 
{
	// TODO: Add your command handler code here
	CPrintBillDlg dlg;
	long nMonth;

	if( dlg.DoModal() != IDOK ) return;
	m_listClient.RemoveAll();
	m_timeDead = dlg.m_timeDead;
	m_timeFrom = dlg.m_timeFrom;
	m_timeTo = dlg.m_timeTo;

	nMonth = m_timeTo.GetYear() * 100 + m_timeTo.GetMonth();
	SetClientList(nMonth);

	m_wPrintType = PRINT_BILL_ALL;

	MainViewActivate();
	AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_FILE_PRINT_PREVIEW);
}

void CServiceManagerDoc::OnListPrint() 
{
	// TODO: Add your command handler code here
	m_wPrintType = PRINT_DEFAULT;

	MainViewActivate();
	AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_FILE_PRINT);
}

void CServiceManagerDoc::OnListPrintPreview() 
{
	// TODO: Add your command handler code here
	m_wPrintType = PRINT_DEFAULT;

	MainViewActivate();
	AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_FILE_PRINT_PREVIEW);
}

CView* CServiceManagerDoc::GetServiceManagerView()
{
	POSITION pos = GetFirstViewPosition();
	CView *pView;

	do pView = GetNextView(pos);
	while(!pView->IsKindOf(RUNTIME_CLASS(CServiceManagerView)) || pos==NULL );

	return pView;
}

void CServiceManagerDoc::MainViewActivate()
{
	((CMainFrame*)(theApp.m_pMainWnd))->SetActiveView(GetServiceManagerView());
}

void CServiceManagerDoc::OnSaveList() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg( FALSE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					 _T("Text Files (*.Txt)|*.txt|All Files (*.*)|*.*||"));
	CView* pView = GetStatusView();
	CListCtrl& listctrl = ((CStatusView *)pView)->GetListCtrl();

#ifdef _USE_ENGLISH
	LPTSTR strTitle[] = { "Current User List\n", "Billing Info List\n",
						  "Deposit History\n", "Stopped ID List\n", "Specific use history of game room\n"};

	dlg.m_ofn.lpstrTitle = _T("Save List");
#else
	LPTSTR strTitle[] = { "현재 이용자 List\n", "과금정보 List\n",
		                  "입금내역\n", "정지된 ID List\n", "게임방 종량이용내역\n"};

	dlg.m_ofn.lpstrTitle = _T("리스트 저장");
#endif

	if (dlg.DoModal () == IDOK)
	{
		CStdioFile file( dlg.GetPathName(), CFile::modeCreate|CFile::modeWrite);
		CString ItemText;
		int index, col;

		file.WriteString(strTitle[m_nListStatus]);

		for( index=0; index<ColInfo[m_nListStatus].nColumnCount; index++)
		{
			ItemText.Format("%s\t", ColInfo[m_nListStatus].lpColInfo[index].lpstrText );
			file.WriteString(ItemText);
		}

		for( index=0; index<listctrl.GetItemCount(); index++)
		{
			file.WriteString("\n");

			for( col=0; col<ColInfo[m_nListStatus].nColumnCount; col++)
			{
				ItemText = listctrl.GetItemText( index, col);
				if( m_nListStatus == 4 && ( col == 2 || col == 4 || col == 5 )) IntegerForm(&ItemText);
				ItemText += _T("\t");
				file.WriteString(ItemText);
			}
		}
	}
}

CView* CServiceManagerDoc::GetStatusView()
{
	POSITION pos = GetFirstViewPosition();
	CView *pView;

	do pView = GetNextView(pos);
	while(!pView->IsKindOf( RUNTIME_CLASS(CStatusView)) || pos==NULL );

	return pView;
}

void CServiceManagerDoc::IntegerForm(CString *strSource)
{
	int index, pos, nCount;

	strSource->MakeReverse();
	strSource->Delete( 0, 3);
	nCount = (strSource->GetLength() - 1 ) / 3;

	for( pos = 3, index = 0; index < nCount; index++, pos += 3 ) strSource->Delete(pos);
	strSource->MakeReverse();
}

void CServiceManagerDoc::OnPrintAddress() 
{
	// TODO: Add your command handler code here
	CPrintAddressDlg dlg;
	long nMonth;

	if( dlg.DoModal() != IDOK ) return;
	nMonth = atoi(dlg.m_strYear)*100 + dlg.m_nMonth + 1;
	SetClientList(nMonth);

	m_wPrintType = PRINT_ADDR;

	MainViewActivate();
	AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_FILE_PRINT_PREVIEW);
}

void CServiceManagerDoc::OnFinishday() 
{
	// TODO: Add your command handler code here
	CTime curTime = CTime::GetCurrentTime();
	CString strMessage, strFlag;

#ifdef _USE_ENGLISH
	if( curTime.GetHour() < 12 ) strFlag.Format("AM");
	else strFlag.Format("PM");

	strMessage.Format("Today's closing time is %s\n%s %s.",
		curTime.Format("%Y Year %m Month %d Date"),
		strFlag, curTime.Format("%Ihours %Mminutes %Sseconds"));
#else
	if( curTime.GetHour() < 12 ) strFlag.Format("오전");
	else strFlag.Format("오후");

	strMessage.Format("오늘의 마감시간은 %s\n%s %s 입니다.",
		               curTime.Format("%Y년 %m월 %d일"),
					   strFlag, curTime.Format("%I시 %M분 %S초"));
#endif
	AfxMessageBox(strMessage);
}

void CServiceManagerDoc::OnUpdateFinishday(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable (g_db.IsOpen ());
}

void CServiceManagerDoc::OnClientBank() 
{
	CClientSelectDlg dlg;

	if(dlg.DoModal() == IDOK)
	{
		CBankSet bankset(&g_db);
		BOOL b_check = FALSE;
		CBillDate timeBill;
		
		bankset.m_strFilter.Format(_T("wClientID=%d"), dlg.m_vClientID);
		if(!bankset.Open()) return;
		if (bankset.IsEOF())
		{
			bankset.Close();
			return;
		}
		
		if( bankset.m_bType == BANK_TYPE_PAY ) b_check = TRUE;
		CNewBankDlg dlgBank(b_check);
		
		bankset.m_strSocNo.TrimRight ();
		
		dlgBank.m_strUserID = bankset.m_strOper;
		dlgBank.m_nBankID = bankset.m_nID;
		dlgBank.m_strBank = bankset.m_strBank;
		dlgBank.m_strName = bankset.m_strName;
		dlgBank.m_strOper = bankset.m_strOper;
		dlgBank.m_strComment = bankset.m_strComment;
		dlgBank.m_nMoney = bankset.m_nMoney;
		dlgBank.m_timeBank = bankset.m_timeReg;
		dlgBank.m_strTelNo = bankset.m_strTelNo;
		dlgBank.m_strSoc1 = bankset.m_strSocNo.Left(6);
		dlgBank.m_strSoc2 = bankset.m_strSocNo.Right (7);
		
		if (!bankset.IsFieldNull (&bankset.m_bType))
			dlgBank.m_nType = bankset.m_bType;
		else
			dlgBank.m_nType = BANK_TYPE_ETC;
		if (!bankset.IsFieldNull (&bankset.m_bProcess))
			dlgBank.m_nProc = bankset.m_bProcess;
		else
			dlgBank.m_nProc = BANK_PROC_IN;

		dlgBank.m_nClientID = dlg.m_vClientID;
		dlgBank.m_strClient = dlg.m_vClientName;
		
		if (dlgBank.DoModal () == IDOK)
		{
			if (dlgBank.m_fGetSerial)
				ViewSerialByBank (dlgBank.m_nBankID);
			else
			{
				bankset.Edit();
				bankset.m_strBank = dlgBank.m_strBank;
				bankset.m_strName = dlgBank.m_strName;
				bankset.m_strOper = m_strUserID;
				bankset.m_strComment = dlgBank.m_strComment;
				bankset.m_nMoney = dlgBank.m_nMoney;
				bankset.m_timeReg = dlgBank.m_timeBank;
				bankset.m_strTelNo = dlgBank.m_strTelNo;
				if(dlgBank.m_strSoc1.IsEmpty() || dlgBank.m_strSoc2.IsEmpty())
				{
					bankset.m_strSocNo.Empty();
				}
				else
				{
					bankset.m_strSocNo = dlgBank.m_strSoc1 + _T("-") + dlgBank.m_strSoc2;
				}
				bankset.m_bType = dlgBank.m_nType;
				bankset.m_bProcess = dlgBank.m_nProc;
				if (dlgBank.m_nClientID == -1)
					bankset.SetFieldNull (&bankset.m_wClientID);
				else
					bankset.m_wClientID = dlgBank.m_nClientID;
				
				bankset.Update();
				UpdateAllViews( NULL, UPDATE_UPDATEBANK, &bankset);
			}
			
			if( dlgBank.m_checkTax && dlgBank.m_nProc != BANK_PROC_STOP && timeBill.DoModal() == IDOK )
			{
				m_timeStart = timeBill.m_timeBill;
				m_nMoney = dlgBank.m_nMoney;
				m_nType = dlgBank.m_nType;
				m_wID = bankset.m_wClientID;
				m_wPrintType = PRINT_TAX;
				
				MainViewActivate();
				AfxGetMainWnd()->SendMessage( WM_COMMAND, ID_FILE_PRINT_PREVIEW);
			}
		}
		if(bankset.IsOpen()) bankset.Close();
	}
}

void CServiceManagerDoc::OnPrintBank() 
{
	CFindBankDlg dlg;
	if (dlg.DoModal () == IDCANCEL)
		return;

	CBankSet bankset(&g_db);
	BOOL fFirst = TRUE;
	if (dlg.m_timeStart < dlg.m_timeEnd)
	{
		CString strStart = dlg.m_timeStart.Format (_T("%m/%d/%Y"));
		CTime timeEnd = dlg.m_timeEnd + CTimeSpan (1, 0, 0, 0);
		CString strEnd = timeEnd.Format (_T("%m/%d/%Y"));
		bankset.m_strFilter.Format (_T("'%s'<=timeReg AND timeReg<'%s' "), strStart, strEnd);
		fFirst = FALSE;
	}
	if (dlg.m_nProc != CB_ERR)
	{
		if (!fFirst)
			bankset.m_strFilter += _T("AND ");
		CString strFilter;
		strFilter.Format (_T("bProcess=%d "), dlg.m_nProc);
		bankset.m_strFilter += strFilter;
		fFirst = FALSE;
	}
	if (dlg.m_nType != CB_ERR)
	{
		if (!fFirst)
			bankset.m_strFilter += _T("AND ");
		CString strFilter;
		strFilter.Format (_T("bType=%d "), dlg.m_nType);
		bankset.m_strFilter += strFilter;
		fFirst = FALSE;
	}
	if (dlg.m_strName != _T(""))
	{
		if (!fFirst)
			bankset.m_strFilter += _T("AND ");
		CString strFilter;
		strFilter.Format (_T("strName='%s' "), dlg.m_strName);
		bankset.m_strFilter += strFilter;
		fFirst = FALSE;
	}
	if (dlg.m_strBank != _T(""))
	{
		if (!fFirst)
			bankset.m_strFilter += _T("AND ");
		CString strFilter;
		strFilter.Format (_T("strBank='%s' "), dlg.m_strBank);
		bankset.m_strFilter += strFilter;
		fFirst = FALSE;
	}
	if (dlg.m_nClientID != -1)
	{
		if (!fFirst)
			bankset.m_strFilter += _T("AND ");
		CString strFilter;
		strFilter.Format (_T("wClientID=%d "), dlg.m_nClientID);
		bankset.m_strFilter += strFilter;
		fFirst = FALSE;
	}

	if (bankset.Open ())
	{
		CString line_str, strText;
		CStdioFile sf;
		if(!sf.Open("bank.txt", CFile::modeCreate|CFile::modeWrite|CFile::typeText))
		{
#ifdef _DEBUG
#ifdef _USE_ENGLISH
			afxDump << "Can't open a file." << "\n";
#else
			afxDump << "파일을 열 수 없습니다." << "\n";
#endif
#endif
			bankset.Close();
			return;
		}
#ifdef _USE_ENGLISH
		sf.WriteString("No.\tDeposit Date\tDepositor\tDeposit Bank\tDeposit Amount\tType\t Process\tWorker\t Remarks\n");
#else
		sf.WriteString("번호\t입금일자\t입금자\t입금은행\t입금액\t종류\t처리\t작업자\t비고\n");
#endif
		while (!bankset.IsEOF ())
		{
			line_str.Format("%05d", bankset.m_nID);
			line_str += '\t';
			line_str += bankset.m_timeReg.Format(_T("%Y/%m/%d"));
			line_str += '\t';
			line_str += bankset.m_strName;
			line_str += '\t';
			line_str += bankset.m_strBank;
			line_str += '\t';
			strText.Format (_T("%d"), bankset.m_nMoney);
			line_str += strText;
			line_str += '\t';
#ifdef _USE_ENGLISH
			switch (bankset.m_bType)
			{
			case BANK_TYPE_PRIVATE :	line_str += _T("Personnel\t"); break;
			case BANK_TYPE_GAMEROOM :	line_str += _T("Game Room\t"); break;
			case BANK_TYPE_PAYLATER :	line_str += _T("Guaranty\t"); break;
			case BANK_TYPE_PAY :		line_str += _T("Charge\t"); break;
			case BANK_TYPE_ETC :		line_str += _T("Etc.\t"); break;
			default: line_str += _T("Unknown\t"); break;
			}
			switch (bankset.m_bProcess)
			{
			case BANK_PROC_IN :		line_str += _T("Deposit\t"); break;
			case BANK_PROC_CONF :	line_str += _T("OK\t"); break;
			case BANK_PROC_STOP :	line_str += _T("Suspension\t"); break;
			case BANK_PROC_ETC :	line_str += _T("Etc.\t"); break;
			default: line_str += _T("Unknown\t"); break;
			}
#else
			switch (bankset.m_bType)
			{
			case BANK_TYPE_PRIVATE :	line_str += _T("개인\t"); break;
			case BANK_TYPE_GAMEROOM :	line_str += _T("게임방\t"); break;
			case BANK_TYPE_PAYLATER :	line_str += _T("한정시간제\t"); break;
			case BANK_TYPE_PAY :		line_str += _T("시간제\t"); break;
			case BANK_TYPE_ETC :		line_str += _T("기타\t"); break;
			default: line_str += _T("모름\t"); break;
			}
			switch (bankset.m_bProcess)
			{
			case BANK_PROC_IN :		line_str += _T("입금\t"); break;
			case BANK_PROC_CONF :	line_str += _T("확인\t"); break;
			case BANK_PROC_STOP :	line_str += _T("정지\t"); break;
			case BANK_PROC_ETC :	line_str += _T("기타\t"); break;
			default: line_str += _T("모름\t"); break;
			}
#endif
			line_str += bankset.m_strOper;
			line_str += '\t';
			strText = bankset.m_strComment;
			strText.Replace('\r', ' ');
			strText.Replace('\n', ' ');
			line_str += strText;
			line_str += '\n';
			sf.WriteString(line_str);
			bankset.MoveNext ();
		}
		bankset.Close ();
		sf.Close();
#ifdef _USE_ENGLISH
		AfxMessageBox("Deposit history saved.", MB_OK);
#else
		AfxMessageBox("입금 내역을 저장하였습니다.", MB_OK);
#endif
	}
}

void CServiceManagerDoc::OnNoticeSet() 
{
	CNoticeSetDialog notice_dialog;
	notice_dialog.m_vNoticeValue = m_vNoticeValue;
	notice_dialog.m_strNoticeMessage = m_strNoticeMessage;

	if(notice_dialog.DoModal() == IDOK)
	{
		CMsg msg;
		CString strField;

		strField = _T("NoticeStatus");
		msg.ID (SC_SETINTVALUE_REQ) 
			<< m_pUserManager->m_strServiceName
			<< strField
			<< notice_dialog.m_vNoticeValue;
		m_pUserManager->m_pServer->SendMsg (msg);

		strField = _T("NoticeMessage");
		msg.ID (SC_SETSTRINGVALUE_REQ)
			<< m_pUserManager->m_strServiceName
			<< strField
			<< notice_dialog.m_strNoticeMessage;
		m_pUserManager->m_pServer->SendMsg (msg);

		m_vNoticeValue = notice_dialog.m_vNoticeValue;
		m_strNoticeMessage = notice_dialog.m_strNoticeMessage;
	}
}

void CServiceManagerDoc::OnNoticeSession() 
{
	CNoticeSetDialog notice_dialog;
	notice_dialog.m_vNoticeValue = m_vNoticeSessionValue;
	notice_dialog.m_strNoticeMessage = m_strNoticeSessionMessage;

	if(notice_dialog.DoModal() == IDOK)
	{
		CMsg msg;
		CString strField;

		strField = _T("NoticeSessionStatus");
		msg.ID (SC_SETINTVALUE_REQ) 
			<< m_pUserManager->m_strServiceName
			<< strField
			<< notice_dialog.m_vNoticeValue;
		m_pUserManager->m_pServer->SendMsg (msg);

		strField = _T("NoticeSessionMessage");
		msg.ID (SC_SETSTRINGVALUE_REQ)
			<< m_pUserManager->m_strServiceName
			<< strField
			<< notice_dialog.m_strNoticeMessage;
		m_pUserManager->m_pServer->SendMsg (msg);

		m_vNoticeSessionValue = notice_dialog.m_vNoticeValue;
		m_strNoticeSessionMessage = notice_dialog.m_strNoticeMessage;
	}
}

void CServiceManagerDoc::OnFileDirCompress() 
{
	// TODO: Add your command handler code here
	CZipFileViewDlg zdlg;

	zdlg.DoModal();
}

void CServiceManagerDoc::OnUpdateFileDirCompress(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->Enable (g_db.IsOpen ());
}
