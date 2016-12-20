// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ClientDlg.h"
#include "ClientSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog


CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
	m_strLine = _T("");
	m_nLoc = -1;
	m_timeReg = CTime::GetCurrentTime ();
	m_strAddress = _T("");
	m_strEMail = _T("");
	m_strHost = _T("");
	m_strKind = _T("");
	m_strName = _T("");
	m_nNumPC = 0;
	m_strRegNo1 = _T("");
	m_strRegNo2 = _T("");
	m_strRegNo3 = _T("");
	m_strTelNo = _T("");
	m_strType = _T("");
	m_strZip1 = _T("");
	m_strZip2 = _T("");
	m_nID = 0;
	m_strEtc = _T("");
	m_strIPAddress = _T("");
	//}}AFX_DATA_INIT
}


void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
	DDX_CBString(pDX, IDC_COMBO_CLIENT_LINE, m_strLine);
	DDX_CBIndex(pDX, IDC_COMBO_CLIENT_LOC, m_nLoc);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_CLIENT_REGDATE, m_timeReg);
	DDX_Text(pDX, IDC_EDIT_CLIENT_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_EDIT_CLIENT_EMAIL, m_strEMail);
	DDX_Text(pDX, IDC_EDIT_CLIENT_HOST, m_strHost);
	DDX_Text(pDX, IDC_EDIT_CLIENT_KIND, m_strKind);
	DDX_Text(pDX, IDC_EDIT_CLIENT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_CLIENT_NUMPC, m_nNumPC);
	DDX_Text(pDX, IDC_EDIT_CLIENT_REGNO1, m_strRegNo1);
	DDV_MaxChars(pDX, m_strRegNo1, 3);
	DDX_Text(pDX, IDC_EDIT_CLIENT_REGNO2, m_strRegNo2);
	DDV_MaxChars(pDX, m_strRegNo2, 2);
	DDX_Text(pDX, IDC_EDIT_CLIENT_REGNO3, m_strRegNo3);
	DDV_MaxChars(pDX, m_strRegNo3, 5);
	DDX_Text(pDX, IDC_EDIT_CLIENT_TELNO, m_strTelNo);
	DDX_Text(pDX, IDC_EDIT_CLIENT_TYPE, m_strType);
	DDX_Text(pDX, IDC_EDIT_CLIENT_ZIP1, m_strZip1);
	DDV_MaxChars(pDX, m_strZip1, 3);
	DDX_Text(pDX, IDC_EDIT_CLIENT_ZIP2, m_strZip2);
	DDV_MaxChars(pDX, m_strZip2, 3);
	DDX_Text(pDX, IDC_EDIT_CLIENT_ID, m_nID);
	DDX_Text(pDX, IDC_EDIT_CLIENT_ETC, m_strEtc);
	DDV_MaxChars(pDX, m_strEtc, 255);
	DDX_Text(pDX, IDC_EDIT_CLIENT_IPADDRESS, m_strIPAddress);
	DDV_MaxChars(pDX, m_strIPAddress, 50);	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_EN_CHANGE(IDC_EDIT_CLIENT_REGNO1, OnChangeEditClientRegno1)
	ON_EN_CHANGE(IDC_EDIT_CLIENT_REGNO2, OnChangeEditClientRegno2)
	ON_EN_CHANGE(IDC_EDIT_CLIENT_REGNO3, OnChangeEditClientRegno3)
	ON_EN_CHANGE(IDC_EDIT_CLIENT_ZIP1, OnChangeEditClientZip1)
	ON_EN_CHANGE(IDC_EDIT_CLIENT_ZIP2, OnChangeEditClientZip2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers


void CClientDlg::OnChangeEditClientRegno1() 
{
	CString strRegNo;
	GetDlgItemText (IDC_EDIT_CLIENT_REGNO1, strRegNo);
	if (strRegNo.GetLength () == 3)
		GetDlgItem (IDC_EDIT_CLIENT_REGNO2)->SetFocus ();
}

void CClientDlg::OnChangeEditClientRegno2() 
{
	CString strRegNo;
	GetDlgItemText (IDC_EDIT_CLIENT_REGNO2, strRegNo);
	if (strRegNo.GetLength () == 2)
		GetDlgItem (IDC_EDIT_CLIENT_REGNO3)->SetFocus ();
}

void CClientDlg::OnChangeEditClientRegno3() 
{
	CString strRegNo;
	GetDlgItemText (IDC_EDIT_CLIENT_REGNO3, strRegNo);
	if (strRegNo.GetLength () == 5)
		GetDlgItem (IDC_EDIT_CLIENT_NAME)->SetFocus ();
}

void CClientDlg::OnChangeEditClientZip1() 
{
	CString strZip;
	GetDlgItemText (IDC_EDIT_CLIENT_ZIP1, strZip);
	if (strZip.GetLength () == 3)
		GetDlgItem (IDC_EDIT_CLIENT_ZIP2)->SetFocus ();
}

void CClientDlg::OnChangeEditClientZip2() 
{
	CString strZip;
	GetDlgItemText (IDC_EDIT_CLIENT_ZIP2, strZip);
	if (strZip.GetLength () == 3)
		GetDlgItem (IDC_COMBO_CLIENT_LOC)->SetFocus ();
}