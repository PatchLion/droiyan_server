// BillDate.cpp : implementation file
//

#include "stdafx.h"
#include "servicemanager.h"
#include "BillDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBillDate dialog


CBillDate::CBillDate(CWnd* pParent /*=NULL*/)
	: CDialog(CBillDate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBillDate)
	m_timeBill = CTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CBillDate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBillDate)
	DDX_DateTimeCtrl(pDX, IDC_BILL_DATE, m_timeBill);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBillDate, CDialog)
	//{{AFX_MSG_MAP(CBillDate)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBillDate message handlers
