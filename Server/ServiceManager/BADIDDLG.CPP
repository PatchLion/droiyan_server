// BadIDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "BadIDDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBadIDDlg dialog


CBadIDDlg::CBadIDDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBadIDDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBadIDDlg)
	m_strComment = _T("");
	m_nDueDay = 0;
	//}}AFX_DATA_INIT
}


void CBadIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBadIDDlg)
	DDX_Text(pDX, IDC_EDIT_BADID_COMMENT, m_strComment);
	DDX_Text(pDX, IDC_EDIT_BADID_DUE, m_nDueDay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBadIDDlg, CDialog)
	//{{AFX_MSG_MAP(CBadIDDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBadIDDlg message handlers
