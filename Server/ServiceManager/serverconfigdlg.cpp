// ServerConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ServerConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerConfigDlg dialog


CServerConfigDlg::CServerConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServerConfigDlg)
	m_strAddr = _T("");
	m_strName = _T("");
	//}}AFX_DATA_INIT
	m_pListAddr = NULL;
}


void CServerConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerConfigDlg)
	DDX_Control(pDX, IDC_LIST_ADDR, m_listAddr);
	DDX_Text(pDX, IDC_EDIT_ADDR, m_strAddr);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServerConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CServerConfigDlg)
	ON_BN_CLICKED(IDC_BUTTON_SETDEFAULT, OnButtonSetdefault)
	ON_BN_CLICKED(IDC_BUTTON_ADDIPADDR, OnButtonAddipaddr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerConfigDlg message handlers

void CServerConfigDlg::OnButtonSetdefault() 
{
	int nIndex = m_listAddr.GetCurSel ();
	if (nIndex != LB_ERR)
	{
		CString strAddr;
		m_listAddr.GetText (nIndex, strAddr);
		SetDlgItemText (IDC_EDIT_ADDR, strAddr);
	}
}

void CServerConfigDlg::OnButtonAddipaddr() 
{
	CString strAddr;
	GetDlgItemText (IDC_EDIT_ADDR, strAddr);
	m_listAddr.AddString (strAddr);
}

BOOL CServerConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_pListAddr)
	{
		POSITION pos = m_pListAddr->GetHeadPosition ();
		while (pos)
		{
			CString strAddr = m_pListAddr->GetNext (pos);
			m_listAddr.AddString (strAddr);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CServerConfigDlg::OnOK() 
{
	if (m_pListAddr)
	{
		m_pListAddr->RemoveAll ();
		int nNumAddr = m_listAddr.GetCount ();
		for (int i = 0; i < nNumAddr; i++)
		{
			CString strAddr;
			m_listAddr.GetText (i, strAddr);
			m_pListAddr->AddTail (strAddr);
		}
	}

	CDialog::OnOK();
}
