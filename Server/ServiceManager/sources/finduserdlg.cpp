// FindUserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "FindUserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindUserDlg dialog


CFindUserDlg::CFindUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindUserDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindUserDlg)
#ifdef _USE_ENGLISH
	m_strCaption = _T("Find user");
#else
	m_strCaption = _T("사용자 찾기");
#endif
	m_strUserID = _T("");
	//}}AFX_DATA_INIT
}


void CFindUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindUserDlg)
	DDX_Text(pDX, IDC_EDIT_USERID, m_strUserID);
	DDV_MaxChars(pDX, m_strUserID, 13);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindUserDlg, CDialog)
	//{{AFX_MSG_MAP(CFindUserDlg)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindUserDlg message handlers

int CFindUserDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetWindowText(m_strCaption);
	// TODO: Add your specialized creation code here
	
	return 0;
}
