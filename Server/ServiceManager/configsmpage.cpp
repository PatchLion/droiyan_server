// ConfigSMPage.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ServiceManagerDoc.h"
#include "ConfigSMPage.h"

#include "SessionDlg.h"

#include "Server.h"
#include "Service.h"
#include "Session.h"
#include "UserManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigSMPage property page

IMPLEMENT_DYNCREATE(CConfigSMPage, CPropertyPage)

CConfigSMPage::CConfigSMPage(CServiceManagerDoc* pDoc) : CPropertyPage(CConfigSMPage::IDD)
{
	m_pDoc = pDoc;
	//{{AFX_DATA_INIT(CConfigSMPage)
	//}}AFX_DATA_INIT
}

CConfigSMPage::~CConfigSMPage()
{
}

void CConfigSMPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigSMPage)
	DDX_Control(pDX, IDC_LIST_SM, m_listSM);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigSMPage, CPropertyPage)
	//{{AFX_MSG_MAP(CConfigSMPage)
	ON_BN_CLICKED(IDC_BUTTON_SM_ADD, OnButtonSmAdd)
	ON_BN_CLICKED(IDC_BUTTON_SM_DEL, OnButtonSmDel)
	ON_BN_CLICKED(IDC_BUTTON_SM_UPDATE, OnButtonSmUpdate)
	ON_BN_CLICKED(IDC_BUTTON_SM_REFRESH, OnButtonSmRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigSMPage message handlers

BOOL CConfigSMPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	if (!m_pDoc)
	{
		GetDlgItem (IDC_BUTTON_SM_ADD)->EnableWindow (FALSE);
		GetDlgItem (IDC_BUTTON_SM_DEL)->EnableWindow (FALSE);
		GetDlgItem (IDC_BUTTON_SM_UPDATE)->EnableWindow (FALSE);
		GetDlgItem (IDC_BUTTON_SM_REFRESH)->EnableWindow (FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigSMPage::OnButtonSmAdd() 
{
	if (!m_pDoc->m_pUserManager)
	{
		AfxMessageBox (IDS_MSG_NOTINSTALLSM);
		return;
	}

	CSessionDlg dlg;
	dlg.m_pListServer = &m_pDoc->m_listServer;
	if (dlg.DoModal () == IDOK)
	{
		CServer* pServer = m_pDoc->FindServer (dlg.m_strServer);
		if (pServer)
		{
			CString strDisplayName;
			strDisplayName.Format (_T("%s Session#%d"), 
				m_pDoc->m_strGameID, dlg.m_nID);
			CSession sm (pServer, dlg.m_strModule + _T("\\Session.exe"), 
				strDisplayName, dlg.m_nID, dlg.m_strAddr, 
				dlg.m_nPort, dlg.m_nCapacity, dlg.m_dwTimeOuts);

			CMsg msg;
			msg.ID (SC_INSTALL_REQ) 
				<< sm.m_strServiceName
				<< sm.m_strGameID
				<< sm.m_strUserID
				<< sm.m_strPassword
				<< sm.m_strModule
				<< sm.m_strDisplayName
				<< sm.m_nServerID
				<< sm.m_strAddr
				<< sm.m_nPort
				<< sm.m_nCapacity
				<< sm.m_dwTimer
				<< sm.m_dwTimeOuts;
			pServer->SendMsg (msg);

			msg.ID (SC_SETSTRINGVALUE_REQ) 
				<< sm.m_strServiceName
				<< _T("UMAddr")
				<< m_pDoc->m_pUserManager->m_strAddr;
			pServer->SendMsg (msg);

			msg.ID (SC_SETINTVALUE_REQ) 
				<< sm.m_strServiceName
				<< _T("UMPort")
				<< m_pDoc->m_pUserManager->m_nPort;
			pServer->SendMsg (msg);

			msg.ID (SC_SETSTRINGVALUE_REQ) 
				<< sm.m_strServiceName
				<< _T("ServName")
				<< dlg.m_strName;
			pServer->SendMsg (msg);

			msg.ID (SC_SETINTVALUE_REQ) 
				<< sm.m_strServiceName
				<< _T("Pay")
				<< dlg.m_nPay;
			pServer->SendMsg (msg);
		}
	}
}

void CConfigSMPage::OnButtonSmDel() 
{
	int nIndex = m_listSM.GetCurSel ();
	if (nIndex != LB_ERR)
	{
		CSession* pSession = (CSession*)m_listSM.GetItemDataPtr (nIndex);
		CMsg msg;
		msg.ID (SC_REMOVE_REQ) << pSession->m_strServiceName;
		pSession->m_pServer->SendMsg (msg);
	}
}

void CConfigSMPage::OnButtonSmUpdate() 
{
	int nIndex = m_listSM.GetCurSel ();
	if (nIndex != LB_ERR)
	{
		CSession* pSession = (CSession*)m_listSM.GetItemDataPtr (nIndex);
		CSessionDlg dlg;
		dlg.m_pListServer = &m_pDoc->m_listServer;
		dlg.m_nID = pSession->m_nServerID;
		dlg.m_strName = pSession->m_strName;
		dlg.m_strModule = pSession->m_strModulePath;
		dlg.m_strServer = pSession->m_pServer->m_strName;
		dlg.m_strAddr = pSession->m_strAddr;
		dlg.m_nPort = pSession->m_nPort;
		dlg.m_nCapacity = pSession->m_nCapacity;
		dlg.m_dwTimeOuts = pSession->m_dwTimeOuts;
		dlg.m_nPay = pSession->m_fPay;
		if (dlg.DoModal () == IDOK)
		{
			CMsg msg;
			msg.ID (SC_SETSTRINGVALUE_REQ) 
				<< pSession->m_strServiceName
				<< _T("Addr")
				<< dlg.m_strAddr;
			pSession->m_pServer->SendMsg (msg);

			msg.ID (SC_SETINTVALUE_REQ) 
				<< pSession->m_strServiceName
				<< _T("Port")
				<< dlg.m_nPort;
			pSession->m_pServer->SendMsg (msg);

			msg.ID (SC_SETINTVALUE_REQ) 
				<< pSession->m_strServiceName
				<< _T("Capacity")
				<< dlg.m_nCapacity;
			pSession->m_pServer->SendMsg (msg);

			msg.ID (SC_SETINTVALUE_REQ) 
				<< pSession->m_strServiceName
				<< _T("TimeOut")
				<< dlg.m_dwTimeOuts;
			pSession->m_pServer->SendMsg (msg);

			msg.ID (SC_SETSTRINGVALUE_REQ) 
				<< pSession->m_strServiceName
				<< _T("ServName")
				<< dlg.m_strName;
			pSession->m_pServer->SendMsg (msg);

			msg.ID (SC_SETINTVALUE_REQ) 
				<< pSession->m_strServiceName
				<< _T("Pay")
				<< dlg.m_nPay;
			pSession->m_pServer->SendMsg (msg);
		}
	}
}

void CConfigSMPage::OnButtonSmRefresh() 
{
	if (m_pDoc)
	{
		m_listSM.ResetContent ();
		POSITION pos = m_pDoc->m_listSession.GetHeadPosition ();
		while (pos)
		{
			CSession* pSession = (CSession*)m_pDoc->m_listGame.GetNext (pos);
			int nIndex = m_listSM.AddString (pSession->m_strName);
			m_listSM.SetItemDataPtr (nIndex, pSession);
		}
	}
}

BOOL CConfigSMPage::OnSetActive() 
{
	OnButtonSmRefresh ();
	return CPropertyPage::OnSetActive();
}
