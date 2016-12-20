// DeleteClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "servicemanager.h"
#include "DeleteClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeleteClientDlg dialog


CDeleteClientDlg::CDeleteClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeleteClientDlg)
	m_strReasion = _T("");
	//}}AFX_DATA_INIT
}


void CDeleteClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeleteClientDlg)
	DDX_Text(pDX, IDC_REASION, m_strReasion);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeleteClientDlg, CDialog)
	//{{AFX_MSG_MAP(CDeleteClientDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeleteClientDlg message handlers
