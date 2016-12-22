// PayDetailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "servicemanager.h"
#include "PayDetailDlg.h"
#include "BankSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPayDetailDlg dialog


CPayDetailDlg::CPayDetailDlg( char* strName, long nMonth, int wID, CWnd* pParent /*=NULL*/)
	: CDialog(CPayDetailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPayDetailDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strName = strName;
	m_nMonth = nMonth;
	m_wID = wID;
}


void CPayDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPayDetailDlg)
	DDX_Control(pDX, IDC_DETAIL_LIST, m_listDetail);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPayDetailDlg, CDialog)
	//{{AFX_MSG_MAP(CPayDetailDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPayDetailDlg message handlers

BOOL CPayDetailDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	CClientPaySet clientpayset( &g_db, m_nMonth, m_wID);
	unsigned long total_cost, total_pay;
	CString dumy, strText = m_strName;
	LV_COLUMN lvc;

	m_listDetail.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.fmt = LVCFMT_CENTER;
#ifdef _USE_ENGLISH
	lvc.pszText = _T("Charge Code");
#else
	lvc.pszText = _T("과금코드");
#endif
	lvc.cx = 115;
	lvc.iSubItem = 0;
	m_listDetail.InsertColumn( 0, &lvc);
	m_listDetail.SetColumn( 0, &lvc );

	lvc.fmt = LVCFMT_RIGHT;
#ifdef _USE_ENGLISH
	lvc.pszText = _T("Charge");
#else
	lvc.pszText = _T("사용금액");
#endif
	lvc.cx = 120;
	lvc.iSubItem = 1;
	m_listDetail.InsertColumn ( 1, &lvc);

	if(!clientpayset.Open ())
	{
		AfxMessageBox (IDS_ERR_DBOPEN);
		return TRUE;
	}

	m_nTotal = 0;
	while(!clientpayset.IsEOF ())
	{
		m_nTotal += clientpayset.m_nUseTime;
		AddDetail(&clientpayset);
		clientpayset.MoveNext();
	}
	clientpayset.Close();

	dumy.Format( " : %ld/%d", m_nMonth/100, m_nMonth - (m_nMonth/100)*100);
	strText = _T(" ") + strText + dumy;
	SetDlgItemText( IDC_CLIENT_NAME, strText);

	strText.Format( "%ld", m_nTotal*10);
	MonyForm(&strText);
#ifdef _USE_ENGLISH
	strText = _T(" Total Sum : ") + strText + _T(" Won");
#else
	strText = _T(" 합  계 : ") + strText + _T(" 원");
#endif
	SetDlgItemText( IDC_TOTAL_COST, strText);

	total_cost = GetTotalTime();
	total_pay = GetTotalMoney();

	if( total_cost*11 < total_pay) strText.Format( "%ld", total_pay - total_cost*11 );
	else strText.Format( "%ld", total_cost*11 - total_pay );
	MonyForm(&strText);

#ifdef _USE_ENGLISH
	if( total_cost*11 < total_pay) strText = _T(" Excess amount of money : ") + strText + _T(" Won");
	else strText = _T(" Amount in arrears : ") + strText + _T(" Won");
#else
	if( total_cost*11 < total_pay) strText = _T(" 초과액 : ") + strText + _T(" 원");
	else strText = _T(" 미납액 : ") + strText + _T(" 원");
#endif

	SetDlgItemText( IDC_DELEY_PAY, strText);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPayDetailDlg::AddDetail( CClientPaySet* pSet)
{
	CString strText;
	LV_ITEM	item;
	int nIndex;

	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = 0;
	item.iSubItem = 0;
	item.pszText = (char*)LPCTSTR(pSet->m_strSerialCode);

	nIndex = m_listDetail.InsertItem(&item);
	strText.Format( "%ld", (pSet->m_nUseTime)*10 );

	MonyForm(&strText);
	strText += _T(" 원");
	m_listDetail.SetItemText( nIndex, 1, strText);
}

void CPayDetailDlg::MonyForm( CString *strSource)
{
	int index, pos, nCount = (strSource->GetLength() - 1 ) / 3;

	strSource->MakeReverse();
	for( pos = 3, index = 0; index < nCount; index++, pos += 4 ) strSource->Insert( pos, ',');
	strSource->MakeReverse();
}

unsigned long CPayDetailDlg::GetTotalTime()
{
	CClientPaySet clientpayset( &g_db, 0, m_wID);
	unsigned long nTotal = 0;

	if(!clientpayset.Open ())
	{
		AfxMessageBox (IDS_ERR_DBOPEN);
		return nTotal;
	}

	while(!clientpayset.IsEOF ())
	{
		nTotal += clientpayset.m_nUseTime;
		clientpayset.MoveNext();
	}

	return nTotal;
}

unsigned long CPayDetailDlg::GetTotalMoney()
{
	CBankSet bankset( &g_db, m_wID);
	unsigned long nTotal = 0;

	if(!bankset.Open())
	{
		AfxMessageBox (IDS_ERR_DBOPEN);
		return nTotal;
	}

	while(!bankset.IsEOF())
	{
		if( bankset.m_bType == BANK_TYPE_PAY && bankset.m_bProcess == BANK_PROC_CONF ) nTotal += bankset.m_nMoney;
		bankset.MoveNext();
	}

	return nTotal;
}