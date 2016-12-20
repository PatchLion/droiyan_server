// ConfigGSPage.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ServiceManagerDoc.h"
#include "ConfigGSPage.h"
#include "ServiceConfigDlg.h"

#include "Server.h"
#include "Service.h"
#include "UserManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigGSPage property page

IMPLEMENT_DYNCREATE(CConfigGSPage, CPropertyPage)

CConfigGSPage::CConfigGSPage(CServiceManagerDoc* pDoc) : CPropertyPage(CConfigGSPage::IDD)
{
	m_pDoc = pDoc;
	m_nDefaultIndex = LB_ERR;
	//{{AFX_DATA_INIT(CConfigGSPage)
	//}}AFX_DATA_INIT
}

CConfigGSPage::~CConfigGSPage()
{
}

void CConfigGSPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigGSPage)
	DDX_Control(pDX, IDC_LIST_GS, m_listGS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigGSPage, CPropertyPage)
	//{{AFX_MSG_MAP(CConfigGSPage)
	ON_BN_CLICKED(IDC_BUTTON_GS_ADD, OnButtonGsAdd)
	ON_BN_CLICKED(IDC_BUTTON_GS_DEL, OnButtonGsDel)
	ON_BN_CLICKED(IDC_BUTTON_GS_UPDATE, OnButtonGsUpdate)
	ON_BN_CLICKED(IDC_BUTTON_GS_REFRESH, OnButtonGsRefresh)
	ON_BN_CLICKED(IDC_BUTTON_GS_DEFAULT, OnButtonGsDefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigGSPage message handlers

BOOL CConfigGSPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	if (!m_pDoc)
	{
		GetDlgItem (IDC_BUTTON_GS_ADD)->EnableWindow (FALSE);
		GetDlgItem (IDC_BUTTON_GS_DEL)->EnableWindow (FALSE);
		GetDlgItem (IDC_BUTTON_GS_UPDATE)->EnableWindow (FALSE);
		GetDlgItem (IDC_BUTTON_GS_DEFAULT)->EnableWindow (FALSE);
		GetDlgItem (IDC_BUTTON_GS_REFRESH)->EnableWindow (FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigGSPage::OnButtonGsAdd() 
{
	CServiceConfigDlg dlg;
	dlg.m_pListServer = &m_pDoc->m_listServer;
	if (dlg.DoModal () == IDOK)
	{
		CServer* pServer = m_pDoc->FindServer (dlg.m_strServer);
		if (pServer)
		{
			CService gs (pServer, CService::typeGS, dlg.m_strModule, 
				dlg.m_strName, dlg.m_nID, dlg.m_strAddr, 
				dlg.m_nPort, dlg.m_nCapacity, 
				dlg.m_dwTimer, dlg.m_dwTimeOuts);

			CMsg msg;
			msg.ID (SC_INSTALL_REQ) 
				<< gs.m_strServiceName
				<< gs.m_strGameID
				<< gs.m_strUserID
				<< gs.m_strPassword
				<< gs.m_strModule
				<< gs.m_strDisplayName
				<< gs.m_nServerID
				<< gs.m_strAddr
				<< gs.m_nPort
				<< gs.m_nCapacity
				<< gs.m_dwTimer
				<< gs.m_dwTimeOuts;
			pServer->SendMsg (msg);
		}
	}
}

void CConfigGSPage::OnButtonGsDel() 
{
	int nIndex = m_listGS.GetCurSel ();
	if (nIndex != LB_ERR)
	{
		CService* pService = (CService*)m_listGS.GetItemDataPtr (nIndex);
		CMsg msg;
		msg.ID (SC_REMOVE_REQ) << pService->m_strServiceName;
		pService->m_pServer->SendMsg (msg);
	}
}

void CConfigGSPage::OnButtonGsUpdate() 
{
	int nIndex = m_listGS.GetCurSel ();
	if (nIndex != LB_ERR)
	{
		CService* pService = (CService*)m_listGS.GetItemDataPtr (nIndex);
		CServiceConfigDlg dlg;
		dlg.m_pListServer = &m_pDoc->m_listServer;
		dlg.m_nID = pService->m_nServerID;
		dlg.m_strName = pService->m_strDisplayName;
		dlg.m_strModule = pService->m_strModule;
		dlg.m_strServer = pService->m_pServer->m_strName;
		dlg.m_strAddr = pService->m_strAddr;
		dlg.m_nPort = pService->m_nPort;
		dlg.m_nCapacity = pService->m_nCapacity;
		dlg.m_dwTimer = pService->m_dwTimer;
		dlg.m_dwTimeOuts = pService->m_dwTimeOuts;
		if (dlg.DoModal () == IDOK)
		{
			CMsg msg;
			msg.ID (SC_SETSTRINGVALUE_REQ) 
				<< pService->m_strServiceName
				<< _T("Addr")
				<< dlg.m_strAddr;
			pService->m_pServer->SendMsg (msg);

			msg.ID (SC_SETINTVALUE_REQ) 
				<< pService->m_strServiceName
				<< _T("Port")
				<< dlg.m_nPort;
			pService->m_pServer->SendMsg (msg);

			msg.ID (SC_SETINTVALUE_REQ) 
				<< pService->m_strServiceName
				<< _T("Capacity")
				<< dlg.m_nCapacity;
			pService->m_pServer->SendMsg (msg);

			msg.ID (SC_SETINTVALUE_REQ) 
				<< pService->m_strServiceName
				<< _T("Timer")
				<< dlg.m_dwTimer;
			pService->m_pServer->SendMsg (msg);

			msg.ID (SC_SETINTVALUE_REQ) 
				<< pService->m_strServiceName
				<< _T("TimeOut")
				<< dlg.m_dwTimeOuts;
			pService->m_pServer->SendMsg (msg);
		}
	}
}

void CConfigGSPage::OnButtonGsRefresh() 
{
	if (m_pDoc)
	{
		m_nDefaultIndex = LB_ERR;
		CString strAddr;
		int nPort = 0;
		if (m_pDoc->m_pUserManager)
		{
			strAddr = m_pDoc->m_pUserManager->m_strGSAddr;
			nPort = m_pDoc->m_pUserManager->m_nGSPort;
		}
		else
			GetDlgItem (IDC_BUTTON_GS_DEFAULT)->EnableWindow (FALSE);

		m_listGS.ResetContent ();
		POSITION pos = m_pDoc->m_listGame.GetHeadPosition ();
		while (pos)
		{
			CService* pService = (CService*)m_pDoc->m_listGame.GetNext (pos);
			CString strName;
			int nIndex;
			if (strAddr == pService->m_strAddr && nPort == pService->m_nPort)
			{
				strName.Format (_T("%s(default)"), pService->m_strDisplayName);
				nIndex = m_listGS.AddString (strName);
				m_nDefaultIndex = nIndex;
			}
			else
			{
				strName = pService->m_strDisplayName;
				nIndex = m_listGS.AddString (strName);
			}
			m_listGS.SetItemDataPtr (nIndex, pService);
		}
	}
}

BOOL CConfigGSPage::OnSetActive() 
{
	OnButtonGsRefresh ();
	
	return CPropertyPage::OnSetActive();
}


void CConfigGSPage::OnButtonGsDefault() 
{
	int nIndex = m_listGS.GetCurSel ();
	if (nIndex != LB_ERR && nIndex != m_nDefaultIndex)
	{
		CService* pService = (CService*)m_listGS.GetItemDataPtr (nIndex);
		CUserManager* pUserManager = m_pDoc->m_pUserManager;

		CMsg msg;
		msg.ID (SC_SETSTRINGVALUE_REQ) 
			<< pUserManager->m_strServiceName
			<< _T("GSAddr")
			<< pService->m_strAddr;
		pUserManager->m_pServer->SendMsg (msg);

		msg.ID (SC_SETINTVALUE_REQ) 
			<< pUserManager->m_strServiceName
			<< _T("GSPort")
			<< pService->m_nPort;
		pUserManager->m_pServer->SendMsg (msg);
	}
}
