// ConvSerialDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ConvSerialDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConvSerialDlg dialog


CConvSerialDlg::CConvSerialDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConvSerialDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConvSerialDlg)
	m_strSerial1 = _T("");
	m_strSerial2 = _T("");
	//}}AFX_DATA_INIT
}


void CConvSerialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConvSerialDlg)
	DDX_Text(pDX, IDC_EDIT_SERIAL1, m_strSerial1);
	DDX_Text(pDX, IDC_EDIT_SERIAL2, m_strSerial2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConvSerialDlg, CDialog)
	//{{AFX_MSG_MAP(CConvSerialDlg)
	ON_EN_CHANGE(IDC_EDIT_SERIAL1, OnChangeEditSerial1)
	ON_EN_CHANGE(IDC_EDIT_SERIAL2, OnChangeEditSerial2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConvSerialDlg message handlers

void CConvSerialDlg::OnChangeEditSerial1() 
{
	GetDlgItemText (IDC_EDIT_SERIAL1, m_strSerial1);
	if (m_strSerial1.GetLength () >= 6)
		GetDlgItem (IDC_EDIT_SERIAL2)->SetFocus ();
}

void CConvSerialDlg::OnChangeEditSerial2() 
{
	GetDlgItemText (IDC_EDIT_SERIAL2, m_strSerial2);
	if (m_strSerial2.GetLength () >= 7)
		GetDlgItem (IDOK)->SetFocus ();
}
