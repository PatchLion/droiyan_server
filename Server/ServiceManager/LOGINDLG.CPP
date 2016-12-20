// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_strGameID = _T("");
	m_strPasswd = _T("");
	m_strUserID = _T("");
	//}}AFX_DATA_INIT
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Text(pDX, IDC_EDIT_GAMEID, m_strGameID);
	DDX_Text(pDX, IDC_EDIT_PASSWD, m_strPasswd);
	DDX_Text(pDX, IDC_EDIT_USERID, m_strUserID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

void CLoginDlg::OnOK() 
{
	GetDlgItemText (IDC_EDIT_GAMEID, m_strGameID);	
	GetDlgItemText (IDC_EDIT_USERID, m_strUserID);	
	GetDlgItemText (IDC_EDIT_PASSWD, m_strPasswd);	
	if (m_strGameID == _T("") || 
		m_strUserID == _T("") ||
		m_strPasswd == _T(""))
	{
		AfxMessageBox (IDS_MSG_NULL);
		return;
	}
	CDialog::OnOK();
}

