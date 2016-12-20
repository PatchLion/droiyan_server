// ConfigUMPage.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ServiceManagerDoc.h"
#include "ConfigUMPage.h"

#include "Server.h"
#include "UserManager.h"
#include "FileManager.h"
#include "Session.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigUMPage property page

IMPLEMENT_DYNCREATE(CConfigUMPage, CPropertyPage)

CConfigUMPage::CConfigUMPage(CServiceManagerDoc* pDoc) : CPropertyPage(CConfigUMPage::IDD)
{
	m_pDoc = pDoc;
	//{{AFX_DATA_INIT(CConfigUMPage)
	m_strAddr = (pDoc && pDoc->m_pUserManager) ? pDoc->m_pUserManager->m_strAddr : _T("");
	m_strServer = (pDoc && pDoc->m_pUserManager) ? pDoc->m_pUserManager->m_pServer->m_strName : _T("");
	m_nCapacity = (pDoc && pDoc->m_pUserManager) ? pDoc->m_pUserManager->m_nCapacity : 0;
	m_strModule = (pDoc && pDoc->m_pUserManager) ? pDoc->m_pUserManager->m_strModulePath : _T("");
	m_nPort = (pDoc && pDoc->m_pUserManager) ? pDoc->m_pUserManager->m_nPort : 4100;
	//}}AFX_DATA_INIT
}

CConfigUMPage::~CConfigUMPage()
{
}

void CConfigUMPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigUMPage)
	DDX_Control(pDX, IDC_COMBO_UM_SERVER, m_comboServer);
	DDX_Control(pDX, IDC_COMBO_UM_ADDR, m_comboAddr);
	DDX_CBString(pDX, IDC_COMBO_UM_ADDR, m_strAddr);
	DDX_CBString(pDX, IDC_COMBO_UM_SERVER, m_strServer);
	DDX_Text(pDX, IDC_EDIT_UM_CAPACITY, m_nCapacity);
	DDX_Text(pDX, IDC_EDIT_UM_MODULE, m_strModule);
	DDX_Text(pDX, IDC_EDIT_UM_PORT, m_nPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigUMPage, CPropertyPage)
	//{{AFX_MSG_MAP(CConfigUMPage)
	ON_CBN_SELCHANGE(IDC_COMBO_UM_SERVER, OnSelchangeComboUmServer)
	ON_CBN_SELCHANGE(IDC_COMBO_UM_ADDR, OnSelchangeComboUmAddr)
	ON_EN_CHANGE(IDC_EDIT_UM_CAPACITY, OnChangeEditUmCapacity)
	ON_EN_CHANGE(IDC_EDIT_UM_MODULE, OnChangeEditUmModule)
	ON_EN_CHANGE(IDC_EDIT_UM_PORT, OnChangeEditUmPort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigUMPage message handlers

BOOL CConfigUMPage::OnInitDialog() 
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
		OnSelchangeComboUmServer ();
		SetModified (FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigUMPage::OnSelchangeComboUmServer() 
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

void CConfigUMPage::OnSelchangeComboUmAddr() 
{
	SetModified (TRUE);
}

void CConfigUMPage::OnChangeEditUmCapacity() 
{
	SetModified (m_pDoc->m_pUserManager != NULL && 
		m_pDoc->m_pUserManager->m_dwStatus != SERVICE_RUNNING);
}

void CConfigUMPage::OnChangeEditUmModule() 
{
	SetModified (m_pDoc->m_pUserManager != NULL && 
		m_pDoc->m_pUserManager->m_dwStatus != SERVICE_RUNNING);
}

void CConfigUMPage::OnChangeEditUmPort() 
{
	SetModified (m_pDoc->m_pUserManager != NULL && 
		m_pDoc->m_pUserManager->m_dwStatus != SERVICE_RUNNING);
}

BOOL CConfigUMPage::OnApply() 
{
	CMsg msg;
	CServer* pServer;
	if (m_pDoc->m_pUserManager)
	{
		pServer = m_pDoc->m_pUserManager->m_pServer;
		if (m_pDoc->m_pUserManager->m_dwStatus == SERVICE_STOPPED)
		{
			msg.ID (SC_SETSTRINGVALUE_REQ) 
				<< m_pDoc->m_pUserManager->m_strServiceName
				<< _T("Addr")
				<< m_strAddr;
			pServer->SendMsg (msg);

			msg.ID (SC_SETINTVALUE_REQ) 
				<< m_pDoc->m_pUserManager->m_strServiceName
				<< _T("Port")
				<< m_nPort;
			pServer->SendMsg (msg);

			msg.ID (SC_SETINTVALUE_REQ) 
				<< m_pDoc->m_pUserManager->m_strServiceName
				<< _T("Capacity")
				<< m_nCapacity;
			pServer->SendMsg (msg);

			POSITION pos = m_pDoc->m_listSession.GetHeadPosition ();
			while (pos)
			{
				CSession* pSession = (CSession*)m_pDoc->m_listSession.GetNext (pos);
				msg.ID (SC_SETSTRINGVALUE_REQ)
					<< pSession->m_strServiceName
					<< _T("UMAddr")
					<< m_strAddr;
				pSession->m_pServer->SendMsg (msg);

				msg.ID (SC_SETINTVALUE_REQ)
					<< pSession->m_strServiceName
					<< _T("UMPort")
					<< m_nPort;
				pSession->m_pServer->SendMsg (msg);
			}
		}
	}
	else
	{
		switch (AfxMessageBox (IDS_MSG_INSTALLUM, MB_YESNOCANCEL))
		{
		case IDYES :
			pServer= m_pDoc->FindServer (m_strServer);
			if (pServer)
			{
				CUserManager um (pServer, m_strModule + _T("\\UserManager.exe"),
					m_strAddr, m_nPort, m_nCapacity);
				msg.ID (SC_INSTALL_REQ) 
					<< um.m_strServiceName
					<< um.m_strGameID
					<< um.m_strUserID
					<< um.m_strPassword
					<< um.m_strModule
					<< um.m_strDisplayName
					<< um.m_nServerID
					<< um.m_strAddr
					<< um.m_nPort
					<< um.m_nCapacity
					<< um.m_dwTimer
					<< um.m_dwTimeOuts;
				pServer->SendMsg (msg);

				if (m_pDoc->m_pFileManager)
				{
					msg.ID (SC_SETSTRINGVALUE_REQ) 
						<< um.m_strServiceName
						<< _T("FMAddr")
						<< m_pDoc->m_pFileManager->m_strAddr;
					pServer->SendMsg (msg);

					msg.ID (SC_SETINTVALUE_REQ) 
						<< um.m_strServiceName
						<< _T("FMPort")
						<< m_pDoc->m_pFileManager->m_nPort;
					pServer->SendMsg (msg);
				}
			}
		case IDCANCEL :
			return FALSE;
		}
	}
	
	return CPropertyPage::OnApply();
}

BOOL CConfigUMPage::OnSetActive() 
{
	if (m_pDoc)
	{
		if (m_pDoc->m_pUserManager)
		{
			int nIndex = m_comboServer.FindStringExact (-1, 
				m_pDoc->m_pUserManager->m_pServer->m_strName);
			m_comboServer.SetCurSel (nIndex);
			OnSelchangeComboUmServer ();

			m_comboServer.EnableWindow (FALSE);
			GetDlgItem (IDC_EDIT_UM_MODULE)->EnableWindow (FALSE);

			if (m_pDoc->m_pUserManager->m_dwStatus == SERVICE_RUNNING ||
				m_pDoc->m_pUserManager->m_dwStatus == SERVICE_PAUSED)
			{
				m_comboAddr.EnableWindow (FALSE);
				GetDlgItem (IDC_EDIT_UM_PORT)->EnableWindow (FALSE);
				GetDlgItem (IDC_EDIT_UM_CAPACITY)->EnableWindow (FALSE);
			}
		}
	}
	
	return CPropertyPage::OnSetActive();
}
