// SelServiceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ServiceManagerDoc.h"
#include "SelServiceDlg.h"

#include "Service.h"
#include "Server.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelServiceDlg dialog


CSelServiceDlg::CSelServiceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelServiceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelServiceDlg)
	m_strServer = _T("");
	//}}AFX_DATA_INIT
	m_pListServer = NULL;
	m_strService = _T("");
}


void CSelServiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelServiceDlg)
	DDX_Control(pDX, IDC_LIST_SERVICE, m_listService);
	DDX_Control(pDX, IDC_COMBO_SERVER, m_comboServer);
	DDX_CBString(pDX, IDC_COMBO_SERVER, m_strServer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelServiceDlg, CDialog)
	//{{AFX_MSG_MAP(CSelServiceDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_SERVER, OnSelchangeComboServer)
	ON_LBN_DBLCLK(IDC_LIST_SERVICE, OnDblclkListService)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelServiceDlg message handlers

BOOL CSelServiceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_pListServer)
	{
		POSITION pos = m_pListServer->GetHeadPosition ();
		while (pos)
		{
			CServer* pServer = (CServer*)m_pListServer->GetNext (pos);
			if (pServer->m_fConnect)
			{
				int nIndex = m_comboServer.AddString (pServer->m_strName);
				m_comboServer.SetItemDataPtr (nIndex, pServer);
			}
		}
		m_comboServer.SetCurSel (0);
		OnSelchangeComboServer ();
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelServiceDlg::OnSelchangeComboServer() 
{
	int nIndex = m_comboServer.GetCurSel ();
	if (nIndex != CB_ERR)
	{
		CServer* pServer = (CServer*)m_comboServer.GetItemDataPtr (nIndex);
		m_listService.ResetContent ();
		POSITION pos = pServer->m_listService.GetHeadPosition ();
		while (pos)
		{
			CService* pService = (CService*)pServer->m_listService.GetNext (pos);
			int nIndex = m_listService.AddString (pService->m_strDisplayName);
			m_listService.SetItemDataPtr (nIndex, pService);
		}
		m_listService.SetCurSel (0);
	}
}

void CSelServiceDlg::OnDblclkListService() 
{
	OnOK ();
}

void CSelServiceDlg::OnOK() 
{
	int nIndex = m_listService.GetCurSel ();
	if (nIndex != LB_ERR)
	{
		CService* pService = (CService*)m_listService.GetItemDataPtr (nIndex);
		m_strService = pService->m_strServiceName;
	}
	CDialog::OnOK();
}

