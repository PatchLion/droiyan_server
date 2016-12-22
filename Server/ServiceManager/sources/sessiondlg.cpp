// SessionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "SessionDlg.h"

#include "Server.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSessionDlg dialog


CSessionDlg::CSessionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSessionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSessionDlg)
	m_strAddr = _T("");
	m_strServer = _T("");
	m_nCapacity = 0;
	m_nID = 0;
	m_strModule = _T("");
	m_strName = _T("");
	m_nPort = 0;
	m_dwTimeOuts = 0;
	m_nPay = 1;
	//}}AFX_DATA_INIT
	m_pListServer = NULL;
}


void CSessionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSessionDlg)
	DDX_Control(pDX, IDC_COMBO_SM_SERVER, m_comboServer);
	DDX_Control(pDX, IDC_COMBO_SM_ADDR, m_comboAddr);
	DDX_CBString(pDX, IDC_COMBO_SM_ADDR, m_strAddr);
	DDX_CBString(pDX, IDC_COMBO_SM_SERVER, m_strServer);
	DDX_Text(pDX, IDC_EDIT_SM_CAPACITY, m_nCapacity);
	DDX_Text(pDX, IDC_EDIT_SM_ID, m_nID);
	DDX_Text(pDX, IDC_EDIT_SM_MODULE, m_strModule);
	DDX_Text(pDX, IDC_EDIT_SM_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_SM_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_SM_TIMEOUT, m_dwTimeOuts);
	DDX_Radio(pDX, IDC_RADIO_SM_PAY, m_nPay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSessionDlg, CDialog)
	//{{AFX_MSG_MAP(CSessionDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_SM_SERVER, OnSelchangeComboSmServer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSessionDlg message handlers

void CSessionDlg::OnSelchangeComboSmServer() 
{
	int nIndex = m_comboServer.GetCurSel ();
	if (nIndex != CB_ERR)
	{
		CServer* pServer = (CServer*)m_comboServer.GetItemDataPtr (nIndex);
		m_comboAddr.ResetContent ();
		POSITION pos = pServer->m_listAddr.GetHeadPosition ();
		int nIndexSel = 0;
		while (pos)
		{
			CString strAddr = pServer->m_listAddr.GetNext (pos);
			nIndex = m_comboAddr.AddString (strAddr);
			if (strAddr == m_strAddr)
				nIndexSel = nIndex;
		}
		m_comboAddr.SetCurSel (nIndexSel);
	}
}

BOOL CSessionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_pListServer)
	{
		int nIndexSel = 0;
		POSITION pos = m_pListServer->GetHeadPosition ();
		while (pos)
		{
			CServer* pServer = (CServer*)m_pListServer->GetNext (pos);
			if (pServer->m_fConnect)
			{
				int nIndex = m_comboServer.AddString (pServer->m_strName);
				m_comboServer.SetItemDataPtr (nIndex, pServer);
				if (pServer->m_strName == m_strServer)
					nIndexSel = nIndex;
			}
		}
		m_comboServer.SetCurSel (nIndexSel);
		OnSelchangeComboSmServer ();
	}

	if (m_strName != _T(""))
	{
		m_comboServer.EnableWindow (FALSE);
		GetDlgItem (IDC_EDIT_SM_ID)->EnableWindow (FALSE);
		GetDlgItem (IDC_EDIT_SM_MODULE)->EnableWindow (FALSE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
