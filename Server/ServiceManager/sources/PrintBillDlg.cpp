// PrintBillDlg.cpp : implementation file
//

#include "stdafx.h"
#include "servicemanager.h"
#include "PrintBillDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintBillDlg dialog


CPrintBillDlg::CPrintBillDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintBillDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrintBillDlg)
	m_timeDead = CTime::GetCurrentTime();
	m_timeFrom = CTime::GetCurrentTime();
	m_timeTo = CTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CPrintBillDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrintBillDlg)
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_INTERVAL_DEAD, m_timeDead);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_INTERVAL_FROM, m_timeFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_INTERVAL_TO, m_timeTo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrintBillDlg, CDialog)
	//{{AFX_MSG_MAP(CPrintBillDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintBillDlg message handlers
