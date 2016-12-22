// FindSerialDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "FindSerialDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindSerialDlg dialog


CFindSerialDlg::CFindSerialDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindSerialDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindSerialDlg)
	m_wSerial = 1;
	//}}AFX_DATA_INIT
}


void CFindSerialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindSerialDlg)
	DDX_Text(pDX, IDC_EDIT_SERIAL, m_wSerial);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindSerialDlg, CDialog)
	//{{AFX_MSG_MAP(CFindSerialDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindSerialDlg message handlers
