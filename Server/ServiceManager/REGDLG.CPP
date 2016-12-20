// RegDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "RegDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CString g_strName = _T("");
int g_nType = 0;
int g_nValue = 0;
CString g_strValue = _T("");

/////////////////////////////////////////////////////////////////////////////
// CRegDlg dialog


CRegDlg::CRegDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegDlg)
	m_strName = g_strName;
	m_nType = g_nType;
	//}}AFX_DATA_INIT
}


void CRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegDlg)
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Radio(pDX, IDC_RADIO_TYPE, m_nType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegDlg, CDialog)
	//{{AFX_MSG_MAP(CRegDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegDlg message handlers

void CRegDlg::OnOK() 
{
	// TODO: Add extra validation here
	GetDlgItemText (IDC_EDIT_VALUE, m_strValue);
	m_nValue = GetDlgItemInt (IDC_EDIT_VALUE);
	g_strValue = m_strValue;
	g_nValue = m_nValue;

	CDialog::OnOK();
}

BOOL CRegDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_nType)
		SetDlgItemInt (IDC_EDIT_VALUE, g_nValue);
	else
		SetDlgItemText (IDC_EDIT_VALUE, g_strValue);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CRegDlg::~CRegDlg()
{
	g_strName = m_strName;
	g_nType = m_nType;
}
