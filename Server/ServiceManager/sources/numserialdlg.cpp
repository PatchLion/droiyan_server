// NumSerialDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "NumSerialDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNumSerialDlg dialog


CNumSerialDlg::CNumSerialDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNumSerialDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNumSerialDlg)
	m_nNumSerial = 1;
	//}}AFX_DATA_INIT
}


void CNumSerialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNumSerialDlg)
	DDX_Text(pDX, IDC_EDIT_SERIALNO, m_nNumSerial);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNumSerialDlg, CDialog)
	//{{AFX_MSG_MAP(CNumSerialDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumSerialDlg message handlers
