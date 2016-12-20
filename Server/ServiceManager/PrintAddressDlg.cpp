// PrintAddressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "servicemanager.h"
#include "PrintAddressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintAddressDlg dialog


CPrintAddressDlg::CPrintAddressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintAddressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrintAddressDlg)
	m_nMonth = -1;
	m_strYear = _T("");
	//}}AFX_DATA_INIT
}


void CPrintAddressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrintAddressDlg)
	DDX_CBIndex(pDX, IDC_FROM_MONTH, m_nMonth);
	DDX_Text(pDX, IDC_FROM_YEAR, m_strYear);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrintAddressDlg, CDialog)
	//{{AFX_MSG_MAP(CPrintAddressDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintAddressDlg message handlers

BOOL CPrintAddressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	CTime ToDay = CTime::GetCurrentTime();

	m_nMonth = ToDay.GetMonth() - 1;
	m_strYear.Format( "%d", ToDay.GetYear());
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
