// UserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "UserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog


CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserDlg::IDD, pParent)
{
	m_fSerialSearch = FALSE;
	//{{AFX_DATA_INIT(CUserDlg)
	m_strUserID = _T("");
	m_strPasswd = _T("");
	m_strSoc1 = _T("");
	m_strSoc2 = _T("");
	m_strName = _T("");
	m_strEMail = _T("");
	m_wSerial = 0;
	m_strTel = _T("");
	m_strAddr1 = _T("");
	m_strAddr2 = _T("");
	m_timeLog = 0;
	m_timeReg = 0;
	//}}AFX_DATA_INIT
}


void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserDlg)
	DDX_Text(pDX, IDC_EDIT_REG_USERID, m_strUserID);
	DDV_MaxChars(pDX, m_strUserID, 12);
	DDX_Text(pDX, IDC_EDIT_REG_PASSWD, m_strPasswd);
	DDV_MaxChars(pDX, m_strPasswd, 10);
	DDX_Text(pDX, IDC_EDIT_REG_SOCNUM1, m_strSoc1);
	DDV_MaxChars(pDX, m_strSoc1, 6);
	DDX_Text(pDX, IDC_EDIT_REG_SOCNUM2, m_strSoc2);
	DDV_MaxChars(pDX, m_strSoc2, 7);
	DDX_Text(pDX, IDC_EDIT_REG_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 10);
	DDX_Text(pDX, IDC_EDIT_REG_EMAIL, m_strEMail);
	DDV_MaxChars(pDX, m_strEMail, 30);
	DDX_Text(pDX, IDC_EDIT_SERIAL, m_wSerial);
	DDX_Text(pDX, IDC_EDIT_REG_TELNO, m_strTel);
	DDX_Text(pDX, IDC_EDIT_REG_ADDRESS1, m_strAddr1);
	DDX_Text(pDX, IDC_EDIT_REG_ADDRESS2, m_strAddr2);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_LOG, m_timeLog);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_REG, m_timeReg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserDlg, CDialog)
	//{{AFX_MSG_MAP(CUserDlg)
	ON_BN_CLICKED(IDC_BUTTON_SERIAL, OnButtonSerial)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserDlg message handlers


BOOL CUserDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_strSocNo.GetLength () >= 14)
	{
		SetDlgItemText (IDC_EDIT_REG_SOCNUM1, m_strSocNo.Left (6));
		SetDlgItemText (IDC_EDIT_REG_SOCNUM2, m_strSocNo.Right (7));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUserDlg::OnOK() 
{
	GetDlgItemText (IDC_EDIT_REG_SOCNUM1, m_strSoc1);
	GetDlgItemText (IDC_EDIT_REG_SOCNUM2, m_strSoc2);

	if(m_strSoc1.IsEmpty() || m_strSoc2.IsEmpty())
	{
		m_strSocNo.Empty();
	}
	else
	{
		m_strSocNo = m_strSoc1 + _T("-") + m_strSoc2;
	}

	CDialog::OnOK();
}

void CUserDlg::OnButtonSerial() 
{
	m_fSerialSearch = TRUE;

	OnOK ();
}
