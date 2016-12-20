// ConfigFMPage.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ServiceManagerDoc.h"
#include "ConfigFMPage.h"

#include "Server.h"
#include "FileManager.h"
#include "USerManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigFMPage property page

IMPLEMENT_DYNCREATE(CConfigFMPage, CPropertyPage)

CConfigFMPage::CConfigFMPage(CServiceManagerDoc* pDoc) : CPropertyPage(CConfigFMPage::IDD)
{
	m_pDoc = pDoc;
	//{{AFX_DATA_INIT(CConfigFMPage)
	m_strAddr = (pDoc && pDoc->m_pFileManager) ? pDoc->m_pFileManager->m_strAddr : _T("");
	m_strServer = (pDoc && pDoc->m_pFileManager) ? pDoc->m_pFileManager->m_pServer->m_strName : _T("");
	m_strModule = (pDoc && pDoc->m_pFileManager) ? pDoc->m_pFileManager->m_strModulePath : _T("");
	m_nPort = (pDoc && pDoc->m_pFileManager) ? pDoc->m_pFileManager->m_nPort : 4101;
	m_strSrcPath = (pDoc && pDoc->m_pFileManager) ? pDoc->m_pFileManager->m_strSrcPath : _T("");
	m_nCapacity = (pDoc && pDoc->m_pFileManager) ? pDoc->m_pFileManager->m_nCapacity : 10;
	m_dwBuffer = (pDoc && pDoc->m_pFileManager) ? pDoc->m_pFileManager->m_dwBuffer : 1024;
	m_dwHold = (pDoc && pDoc->m_pFileManager) ? pDoc->m_pFileManager->m_dwHold : 4096;
	//}}AFX_DATA_INIT
}

CConfigFMPage::~CConfigFMPage()
{
}

void CConfigFMPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigFMPage)
	DDX_Control(pDX, IDC_COMBO_FM_SERVER, m_comboServer);
	DDX_Control(pDX, IDC_COMBO_FM_ADDR, m_comboAddr);
	DDX_CBString(pDX, IDC_COMBO_FM_ADDR, m_strAddr);
	DDX_CBString(pDX, IDC_COMBO_FM_SERVER, m_strServer);
	DDX_Text(pDX, IDC_EDIT_FM_MODULE, m_strModule);
	DDX_Text(pDX, IDC_EDIT_FM_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_FM_PATH, m_strSrcPath);
	DDX_Text(pDX, IDC_EDIT_FM_CAPACITY, m_nCapacity);
	DDX_Text(pDX, IDC_EDIT_FM_BUFFER, m_dwBuffer);
	DDX_Text(pDX, IDC_EDIT_FM_HOLD, m_dwHold);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigFMPage, CPropertyPage)
	//{{AFX_MSG_MAP(CConfigFMPage)
	ON_CBN_SELCHANGE(IDC_COMBO_FM_SERVER, OnSelchangeComboFmServer)
	ON_CBN_SELCHANGE(IDC_COMBO_FM_ADDR, OnSelchangeComboFmAddr)
	ON_EN_CHANGE(IDC_EDIT_FM_CAPACITY, OnChangeEditFmCapacity)
	ON_EN_CHANGE(IDC_EDIT_FM_PATH, OnChangeEditFmPath)
	ON_EN_CHANGE(IDC_EDIT_FM_PORT, OnChangeEditFmPort)
	ON_EN_CHANGE(IDC_EDIT_FM_MODULE, OnChangeEditFmModule)
	ON_EN_CHANGE(IDC_EDIT_FM_BUFFER, OnChangeEditFmBuffer)
	ON_EN_CHANGE(IDC_EDIT_FM_HOLD, OnChangeEditFmHold)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigFMPage message handlers

BOOL CConfigFMPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	if (m_pDoc)
	{
		POSITION pos = m_pDoc->m_listServer.GetHeadPosition ();
		while (pos)
		{
			CServer* pServer = (CServer*)m_pDoc->m_listServer.GetNext (pos);
			if (pServer->m_fConnect)
			{
				int nIndex = m_comboServer.AddString (pServer->m_strName);
				m_comboServer.SetItemDataPtr (nIndex, pServer);
			}
		}
		m_comboServer.SetCurSel (0);
		OnSelchangeComboFmServer ();
		SetModified (FALSE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigFMPage::OnSelchangeComboFmServer() 
{
	int nIndex = m_comboServer.GetCurSel ();
	if (nIndex != CB_ERR)
	{
		int nIndexAddr = 0;
		CServer* pServer = (CServer*)m_comboServer.GetItemDataPtr (nIndex);
		m_comboAddr.ResetContent ();
		POSITION pos = pServer->m_listAddr.GetHeadPosition ();
		while (pos)
		{
			CString strAddr = pServer->m_listAddr.GetNext (pos);
			nIndex = m_comboAddr.AddString (strAddr);
			if (strAddr == m_strAddr)
				nIndexAddr = nIndex;
		}
		m_comboAddr.SetCurSel (nIndexAddr);
		SetModified (TRUE);
	}
}

BOOL CConfigFMPage::OnSetActive() 
{
	if (m_pDoc)
	{
		if (m_pDoc->m_pFileManager)
		{
			int nIndex = m_comboServer.FindStringExact (-1, 
				m_pDoc->m_pFileManager->m_pServer->m_strName);
			m_comboServer.SetCurSel (nIndex);
			OnSelchangeComboFmServer ();

			m_comboServer.EnableWindow (FALSE);
			GetDlgItem (IDC_EDIT_FM_MODULE)->EnableWindow (FALSE);

			if (m_pDoc->m_pFileManager->m_dwStatus == SERVICE_RUNNING ||
				m_pDoc->m_pFileManager->m_dwStatus == SERVICE_PAUSED)
			{
				m_comboAddr.EnableWindow (FALSE);
				GetDlgItem (IDC_EDIT_FM_PORT)->EnableWindow (FALSE);
				GetDlgItem (IDC_EDIT_FM_CAPACITY)->EnableWindow (FALSE);
				GetDlgItem (IDC_EDIT_FM_PATH)->EnableWindow (FALSE);
				GetDlgItem (IDC_EDIT_FM_BUFFER)->EnableWindow (FALSE);
				GetDlgItem (IDC_EDIT_FM_HOLD)->EnableWindow (FALSE);
			}
		}
	}
	
	return CPropertyPage::OnSetActive();
}

BOOL CConfigFMPage::OnApply() 
{
	CMsg msg;
	CServer* pServer;
	if (m_pDoc->m_pFileManager)
	{
		pServer = m_pDoc->m_pFileManager->m_pServer;
		if (m_pDoc->m_pFileManager->m_dwStatus == SERVICE_STOPPED)
		{
			msg.ID (SC_SETSTRINGVALUE_REQ) 
				<< m_pDoc->m_pFileManager->m_strServiceName
				<< _T("Addr")
				<< m_strAddr;
			pServer->SendMsg (msg);

			msg.ID (SC_SETINTVALUE_REQ) 
				<< m_pDoc->m_pFileManager->m_strServiceName
				<< _T("Port")
				<< m_nPort;
			pServer->SendMsg (msg);

			msg.ID (SC_SETINTVALUE_REQ) 
				<< m_pDoc->m_pFileManager->m_strServiceName
				<< _T("Capacity")
				<< m_nCapacity;
			pServer->SendMsg (msg);

			msg.ID (SC_SETSTRINGVALUE_REQ) 
				<< m_pDoc->m_pFileManager->m_strServiceName
				<< _T("SrcPath")
				<< m_strSrcPath;
			pServer->SendMsg (msg);

			msg.ID (SC_SETINTVALUE_REQ) 
				<< m_pDoc->m_pFileManager->m_strServiceName
				<< _T("Hold")
				<< m_dwHold;
			pServer->SendMsg (msg);

			msg.ID (SC_SETINTVALUE_REQ) 
				<< m_pDoc->m_pFileManager->m_strServiceName
				<< _T("Buf")
				<< m_dwBuffer;
			pServer->SendMsg (msg);

			if (m_pDoc->m_pUserManager)
			{
				msg.ID (SC_SETSTRINGVALUE_REQ) 
					<< m_pDoc->m_pUserManager->m_strServiceName
					<< _T("FMAddr")
					<< m_strAddr;
				m_pDoc->m_pUserManager->m_pServer->SendMsg (msg);

				msg.ID (SC_SETINTVALUE_REQ) 
					<< m_pDoc->m_pUserManager->m_strServiceName
					<< _T("FMPort")
					<< m_nPort;
				m_pDoc->m_pUserManager->m_pServer->SendMsg (msg);
			}
		}
	}
	else
	{
		switch (AfxMessageBox (IDS_MSG_INSTALLFM, MB_YESNOCANCEL))
		{
		case IDYES :
			pServer= m_pDoc->FindServer (m_strServer);
			if (pServer)
			{
				CFileManager fm (pServer, m_strModule + _T("\\FileManager.exe"),
					m_strAddr, m_nPort, m_nCapacity);
				msg.ID (SC_INSTALL_REQ) 
					<< fm.m_strServiceName
					<< fm.m_strGameID
					<< fm.m_strUserID
					<< fm.m_strPassword
					<< fm.m_strModule
					<< fm.m_strDisplayName
					<< fm.m_nServerID
					<< fm.m_strAddr
					<< fm.m_nPort
					<< fm.m_nCapacity
					<< fm.m_dwTimer
					<< fm.m_dwTimeOuts;
				pServer->SendMsg (msg);

				msg.ID (SC_SETSTRINGVALUE_REQ) 
					<< fm.m_strServiceName
					<< _T("SrcPath")
					<< m_strSrcPath;
				pServer->SendMsg (msg);

				msg.ID (SC_SETINTVALUE_REQ) 
					<< fm.m_strServiceName
					<< _T("Hold")
					<< m_dwHold;
				pServer->SendMsg (msg);

				msg.ID (SC_SETINTVALUE_REQ) 
					<< fm.m_strServiceName
					<< _T("Buf")
					<< m_dwBuffer;
				pServer->SendMsg (msg);

				if (m_pDoc->m_pUserManager)
				{
					msg.ID (SC_SETSTRINGVALUE_REQ) 
						<< m_pDoc->m_pUserManager->m_strServiceName
						<< _T("FMAddr")
						<< fm.m_strAddr;
					m_pDoc->m_pUserManager->m_pServer->SendMsg (msg);

					msg.ID (SC_SETINTVALUE_REQ) 
						<< m_pDoc->m_pUserManager->m_strServiceName
						<< _T("FMPort")
						<< fm.m_nPort;
					m_pDoc->m_pUserManager->m_pServer->SendMsg (msg);
				}
			}
		case IDCANCEL :
			return FALSE;
		}
	}
	
	return CPropertyPage::OnApply();
}

void CConfigFMPage::OnSelchangeComboFmAddr() 
{
	SetModified (TRUE);
}

void CConfigFMPage::OnChangeEditFmCapacity() 
{
	SetModified (m_pDoc->m_pFileManager != NULL && 
		m_pDoc->m_pFileManager->m_dwStatus != SERVICE_RUNNING);
}

void CConfigFMPage::OnChangeEditFmPath() 
{
	SetModified (m_pDoc->m_pFileManager != NULL && 
		m_pDoc->m_pFileManager->m_dwStatus != SERVICE_RUNNING);
}

void CConfigFMPage::OnChangeEditFmPort() 
{
	SetModified (m_pDoc->m_pFileManager != NULL && 
		m_pDoc->m_pFileManager->m_dwStatus != SERVICE_RUNNING);
}

void CConfigFMPage::OnChangeEditFmModule() 
{
	SetModified (m_pDoc->m_pFileManager != NULL && 
		m_pDoc->m_pFileManager->m_dwStatus != SERVICE_RUNNING);
}

void CConfigFMPage::OnChangeEditFmBuffer() 
{
	SetModified (m_pDoc->m_pFileManager != NULL && 
		m_pDoc->m_pFileManager->m_dwStatus != SERVICE_RUNNING);
}

void CConfigFMPage::OnChangeEditFmHold() 
{
	SetModified (m_pDoc->m_pFileManager != NULL && 
		m_pDoc->m_pFileManager->m_dwStatus != SERVICE_RUNNING);
}
