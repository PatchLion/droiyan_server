// NoticeSetDialog.cpp : implementation file
//

#include "stdafx.h"
#include "servicemanager.h"
#include "NoticeSetDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNoticeSetDialog dialog


CNoticeSetDialog::CNoticeSetDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CNoticeSetDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNoticeSetDialog)
	m_vNoticeValue = FALSE;
	m_strNoticeMessage = _T("");
	//}}AFX_DATA_INIT
}


void CNoticeSetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNoticeSetDialog)
	DDX_Check(pDX, IDC_NOTICE_VALUE, m_vNoticeValue);
	DDX_Text(pDX, IDC_NOTICE_MESSAGE, m_strNoticeMessage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNoticeSetDialog, CDialog)
	//{{AFX_MSG_MAP(CNoticeSetDialog)
	ON_BN_CLICKED(IDC_NOTICE_VALUE, OnNoticeValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNoticeSetDialog message handlers

BOOL CNoticeSetDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(m_vNoticeValue == FALSE)
	{
		GetDlgItem(IDC_NOTICE_MESSAGE)->EnableWindow(FALSE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNoticeSetDialog::OnNoticeValue() 
{
	CButton *button = (CButton *)GetDlgItem(IDC_NOTICE_VALUE);
	CWnd *wnd = GetDlgItem(IDC_NOTICE_MESSAGE);

	if(button->GetCheck() == 0)
	{
		wnd->EnableWindow(FALSE);
	}
	else
	{
		wnd->EnableWindow(TRUE);
	}
}
