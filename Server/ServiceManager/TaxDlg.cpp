// TaxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "servicemanager.h"
#include "TaxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaxDlg dialog


CTaxDlg::CTaxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTaxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTaxDlg)
	m_strGoodName = _T("");
	m_datePrint = 0;
	//}}AFX_DATA_INIT
}


void CTaxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTaxDlg)
	DDX_Text(pDX, IDC_GOOD_NAME, m_strGoodName);
	DDX_DateTimeCtrl(pDX, IDC_TAX_DATE, m_datePrint);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTaxDlg, CDialog)
	//{{AFX_MSG_MAP(CTaxDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaxDlg message handlers

BOOL CTaxDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_strGoodName = _T("게임방 종량");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}