// NewBankDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "NewBankDlg.h"
#include "ClientListDlg.h"
#include "ClientDlg.h"

#include "ClientSerialSet.h"
#include "BankSerialSet.h"
#include "BadSerialSet.h"
#include "SerialSet.h"
#include "ClientSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CString g_strName;


/////////////////////////////////////////////////////////////////////////////
// CNewBankDlg dialog


CNewBankDlg::CNewBankDlg( BOOL print_tax, CWnd* pParent /*=NULL*/)
	: CDialog(CNewBankDlg::IDD, pParent)
{
	m_fGetSerial = FALSE;
	//{{AFX_DATA_INIT(CNewBankDlg)
#ifndef _USE_ENGLISH
	m_strBank = _T("±¹¹Î");
#endif
	m_strComment = _T("");
	m_nMoney = 47300;
	m_strName = _T("");
	m_nNumSerial = 1;
	m_strOper = _T("");
	m_strSoc1 = _T("");
	m_strSoc2 = _T("");
	m_nProc = 0;
	m_nType = 0;
	m_timeBank = CTime::GetCurrentTime ();
	m_strTelNo = _T("");
	m_strClient = _T("");
	m_strUserID = _T("");
	m_checkTax = print_tax;
	//}}AFX_DATA_INIT
	m_nClientID = -1;
	IsDeleted = FALSE;
}


void CNewBankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewBankDlg)
	DDX_CBString(pDX, IDC_COMBO_BANK, m_strBank);
	DDX_Text(pDX, IDC_EDIT_COMMENT, m_strComment);
	DDX_Text(pDX, IDC_EDIT_MONEY, m_nMoney);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_NUMSERIAL, m_nNumSerial);
	DDX_Text(pDX, IDC_EDIT_OPER, m_strOper);
	DDX_Text(pDX, IDC_EDIT_SOC1, m_strSoc1);
	DDV_MaxChars(pDX, m_strSoc1, 6);
	DDX_Text(pDX, IDC_EDIT_SOC2, m_strSoc2);
	DDV_MaxChars(pDX, m_strSoc2, 7);
	DDX_CBIndex(pDX, IDC_COMBO_BANKPROC, m_nProc);
	DDX_CBIndex(pDX, IDC_COMBO_BANKTYPE, m_nType);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BANKDATE, m_timeBank);
	DDX_Text(pDX, IDC_EDIT_BANKTEL, m_strTelNo);
	DDX_Text(pDX, IDC_EDIT_CLIENT, m_strClient);
	DDX_Check(pDX, IDC_PRINT_TAX, m_checkTax);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewBankDlg, CDialog)
	//{{AFX_MSG_MAP(CNewBankDlg)
	ON_BN_CLICKED(IDC_BUTTON_SERIAL, OnButtonSerial)
	ON_EN_CHANGE(IDC_EDIT_SOC1, OnChangeEditSoc1)
	ON_EN_CHANGE(IDC_EDIT_SOC2, OnChangeEditSoc2)
	ON_BN_CLICKED(IDC_BUTTON_FINDCLIENT, OnButtonFindclient)
	ON_BN_CLICKED(IDC_BUTTON_CLIENT, OnButtonClient)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewBankDlg message handlers

BOOL CNewBankDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CButton *check;
	
	if (m_strName == _T(""))
		GetDlgItem (IDC_DATETIMEPICKER_BANKDATE)->EnableWindow (FALSE);

	if(!m_checkTax)
	{
		check = (CButton*)GetDlgItem(IDC_PRINT_TAX);
		check->EnableWindow(FALSE);
	}
	if( m_nProc == BANK_PROC_STOP ) IsDeleted = TRUE;
	m_checkTax = FALSE;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewBankDlg::OnButtonSerial() 
{
	m_fGetSerial = TRUE;
	CDialog::OnOK ();
}

void CNewBankDlg::OnChangeEditSoc1() 
{
	CString strSoc;
	GetDlgItemText (IDC_EDIT_SOC1, strSoc);
	if (strSoc.GetLength () == 6)
		GetDlgItem (IDC_EDIT_SOC2)->SetFocus ();
}

void CNewBankDlg::OnChangeEditSoc2() 
{
	CString strSoc;
	GetDlgItemText (IDC_EDIT_SOC2, strSoc);
	if (strSoc.GetLength () == 7)
		GetDlgItem (IDC_EDIT_COMMENT)->SetFocus ();
}

void CNewBankDlg::OnButtonFindclient() 
{
	CClientListDlg dlg;
	if (dlg.DoModal () == IDOK)
	{
		m_strClient = dlg.m_strClient;
		m_nClientID = dlg.m_nClientID;
		SetDlgItemText (IDC_EDIT_CLIENT, m_strClient);
	}
}

void CNewBankDlg::OnButtonClient() 
{
	if (m_nClientID == -1)
		return;

	CClientSet clientset (&g_db);
	clientset.m_strFilter.Format (_T("wID=%d"),m_nClientID);
	if (!clientset.Open ())
		return;

	CClientDlg dlg;
	dlg.m_nID = clientset.m_wID;
	dlg.m_timeReg = clientset.m_timeReg;
	dlg.m_strRegNo1 = clientset.m_strRegNo.Left (3);
	dlg.m_strRegNo2 = clientset.m_strRegNo.Mid (4, 2);
	dlg.m_strRegNo3 = clientset.m_strRegNo.Right (5);
	dlg.m_strName = clientset.m_strName;
	dlg.m_strHost = clientset.m_strHost;
	dlg.m_strAddress = clientset.m_strAddress;
	dlg.m_strKind = clientset.m_strKind;
	dlg.m_strType = clientset.m_strType;
	dlg.m_strTelNo = clientset.m_strTelNo;
	dlg.m_strZip1 = clientset.m_strZipCode.Left (3);
	dlg.m_strZip2 = clientset.m_strZipCode.Right (3);
	dlg.m_strEMail = clientset.m_strEMail;
	dlg.m_nLoc = clientset.m_wLoc;
	dlg.m_nNumPC = clientset.m_nNumPC;
	dlg.m_strLine = clientset.m_strUseLine;
	dlg.m_strIPAddress = clientset.m_strIPAddress;
	dlg.m_strEtc = clientset.m_strEtc;	

	if (dlg.DoModal () == IDOK)
	{
		clientset.Edit ();
		clientset.SetFieldDirty (&clientset.m_wID, FALSE);
		clientset.SetFieldDirty (&clientset.m_timeReg, FALSE);
		clientset.m_strRegNo.Format (_T("%s-%s-%s"), 
			dlg.m_strRegNo1, dlg.m_strRegNo2, dlg.m_strRegNo3);
		clientset.m_strName = dlg.m_strName;
		clientset.m_strHost = dlg.m_strHost;
		clientset.m_strAddress = dlg.m_strAddress;
		clientset.m_strType = dlg.m_strType;
		clientset.m_strKind = dlg.m_strKind;
		clientset.m_strTelNo = dlg.m_strTelNo;
		clientset.m_strUseLine = dlg.m_strLine;
		clientset.m_strEMail = dlg.m_strEMail;
		if(dlg.m_strZip1.IsEmpty() || dlg.m_strZip2.IsEmpty())
		{
			clientset.m_strZipCode.Empty();
		}
		else
		{
			clientset.m_strZipCode = dlg.m_strZip1 + _T("-") + dlg.m_strZip2;
		}
		clientset.m_nNumPC = dlg.m_nNumPC;
		clientset.m_wLoc = dlg.m_nLoc;
		clientset.m_strIPAddress = dlg.m_strIPAddress;
		clientset.m_strEtc = dlg.m_strEtc;		

		clientset.Update ();
	}
}

void CNewBankDlg::OnOK() 
{
	// TODO: Add extra validation here
	CDeleteClientDlg dlg;
	UpdateData(TRUE);

	if( m_nProc != BANK_PROC_STOP || IsDeleted )
	{
		CDialog::OnOK();
		return;
	}
	if( dlg.DoModal() != IDOK ) return;

	DeleteClient(&dlg);
	CDialog::OnOK();
}

void CNewBankDlg::DeleteClient( CDeleteClientDlg *dlg)
{
	CClientSerialSet clientserialset(&g_db);

	clientserialset.m_strFilter.Format( " wClientID = %ld ", m_nClientID);
	if(!clientserialset.Open()) return;

	if(!clientserialset.IsEOF())
	{
		clientserialset.Edit ();
		clientserialset.m_bProcess = 1;
		clientserialset.Update ();
	}
	if(clientserialset.IsOpen()) clientserialset.Close();

	CBankSerialSet bankserialset(&g_db);
	bankserialset.m_strFilter.Format (_T("nBankID=%u"), m_nBankID);
	if (!bankserialset.Open ())
	{
		AfxMessageBox (IDS_MSG_BANKSERIALFAIL);
		return;
	}

	CUIntArray arraySerial;
	while(!bankserialset.IsEOF())
	{
		arraySerial.Add (bankserialset.m_wSerial);
		bankserialset.MoveNext ();
	}
	if(bankserialset.IsOpen()) bankserialset.Close();

	CBadSerialSet badserialset(&g_db);
	CSerialSet serialset(&g_db);
	int index;

	for( index=0; index<arraySerial.GetSize(); index++)
	{
		serialset.m_strFilter.Format(_T("wSerial=%u"), arraySerial[index]);
		if(!serialset.Open())
		{
			AfxMessageBox (IDS_MSG_BANKSERIALFAIL);
			return;
		}
		if(!serialset.IsEOF())
		{
			serialset.Edit ();
			serialset.m_nValidDay = 0;
			serialset.Update ();
		}
		if(serialset.IsOpen()) serialset.Close();

		badserialset.m_strFilter.Format(_T("wSerial=%u"), arraySerial[index]);
		if(!badserialset.Open())
		{
			AfxMessageBox (IDS_MSG_BANKSERIALFAIL);
			return;
		}

		if(badserialset.IsEOF()) badserialset.AddNew();
		else badserialset.Edit();

		badserialset.m_strReasion = dlg->m_strReasion;
		badserialset.SetFieldNull(&badserialset.m_dateStop);
		badserialset.m_strOper = m_strUserID;
		badserialset.m_wSerial = arraySerial[index];

		badserialset.Update ();
		if(badserialset.IsOpen()) badserialset.Close();
	}
}