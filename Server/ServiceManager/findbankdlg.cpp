// FindBankDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "FindBankDlg.h"
#include "ClientListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindBankDlg dialog


CFindBankDlg::CFindBankDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindBankDlg::IDD, pParent)
{
	m_nClientID = -1;
	//{{AFX_DATA_INIT(CFindBankDlg)
	m_strBank = _T("");
	m_nProc = -1;
	m_nType = -1;
	m_timeEnd = m_timeStart = CTime::GetCurrentTime ();
	m_strClient = _T("");
	m_strName = _T("");
	//}}AFX_DATA_INIT
}


void CFindBankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindBankDlg)
	DDX_CBString(pDX, IDC_COMBO_BANK, m_strBank);
	DDX_CBIndex(pDX, IDC_COMBO_BANKPROC, m_nProc);
	DDX_CBIndex(pDX, IDC_COMBO_BANKTYPE, m_nType);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_SEARCHEND, m_timeEnd);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_SEARCHSTART, m_timeStart);
	DDX_Text(pDX, IDC_EDIT_CLIENT, m_strClient);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindBankDlg, CDialog)
	//{{AFX_MSG_MAP(CFindBankDlg)
	ON_BN_CLICKED(IDC_BUTTON_FINDCLIENT, OnButtonFindclient)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindBankDlg message handlers

void CFindBankDlg::OnButtonFindclient() 
{
	CClientListDlg dlg;
	if (dlg.DoModal () == IDOK)
	{
		m_strClient = dlg.m_strClient;
		m_nClientID = dlg.m_nClientID;
		SetDlgItemText (IDC_EDIT_CLIENT, m_strClient);
	}
}
