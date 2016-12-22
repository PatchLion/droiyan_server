// ClientListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ClientListDlg.h"
#include "SearchClientDlg.h"
#include "ClientDlg.h"
#include "NewBankDlg.h"

#include "ClientSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientListDlg dialog


CClientListDlg::CClientListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientListDlg)
	m_strClient = _T("");
	//}}AFX_DATA_INIT
}


void CClientListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientListDlg)
	DDX_Control(pDX, IDC_LIST_CLIENT, m_listClient);
	DDX_LBString(pDX, IDC_LIST_CLIENT, m_strClient);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClientListDlg, CDialog)
	//{{AFX_MSG_MAP(CClientListDlg)
	ON_BN_CLICKED(IDC_BUTTON_CLIENT, OnButtonClient)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_NEWCLIENT, OnButtonNewclient)
	ON_LBN_DBLCLK(IDC_LIST_CLIENT, OnButtonClient)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientListDlg message handlers

void CClientListDlg::OnButtonClient() 
{
	int nIndex = m_listClient.GetCurSel ();
	if (nIndex != LB_ERR)
	{
		int nClientID = m_listClient.GetItemData (nIndex);

		CClientSet clientset (&g_db);
		clientset.m_strFilter.Format (_T("wID=%d"),nClientID);
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
}

void CClientListDlg::OnButtonSearch() 
{
	CSearchClientDlg dlg;
	if (dlg.DoModal () == IDOK)
	{
		m_listClient.ResetContent ();

		CClientSet clientset (&g_db);
		BOOL fFirst = TRUE;
		if (dlg.m_nLoc != -1)
		{
			CString strFilter;
			strFilter.Format (_T("wLoc=%d"), dlg.m_nLoc);
			clientset.m_strFilter += strFilter;
			fFirst = FALSE;
		}
		if (dlg.m_strName != _T(""))
		{
			if (!fFirst)
				clientset.m_strFilter += _T(" AND ");
			clientset.m_strFilter.Format (_T("strName like '%%%s%%'"), dlg.m_strName);
			fFirst = FALSE;
		}
		if (dlg.m_strHost != _T(""))
		{
			if (!fFirst)
				clientset.m_strFilter += _T(" AND ");
			CString strFilter;
			strFilter.Format (_T("strHost='%s'"), dlg.m_strHost);
			clientset.m_strFilter += strFilter;
			fFirst = FALSE;
		}
		if (dlg.m_strTelNo != _T(""))
		{
			if (!fFirst)
				clientset.m_strFilter += _T(" AND ");
			CString strFilter;
			strFilter.Format (_T("strTelNo='%s'"), dlg.m_strTelNo);
			clientset.m_strFilter += strFilter;
			fFirst = FALSE;
		}

		if (dlg.m_time != NULL)
		{
			if (!fFirst)
				clientset.m_strFilter += _T(" AND ");
			CString strFilter;
			//strFilter.Format (_T("timeReg >'%s' AND timeReg <='%s'"), dlg.m_time.Format(_T("%Y/%m/%d")), dlg.m_time.Format(_T("%Y/%m/%d")));
			strFilter.Format (_T("timeReg >='%s'"), dlg.m_time.Format(_T("%Y/%m/%d")));
			clientset.m_strFilter += strFilter;
			fFirst = FALSE;
		}

		if (dlg.m_strSearchRegNo1 != _T("") && dlg.m_strSearchRegNo2 != _T("") && dlg.m_strSearchRegNo3 != _T(""))
		{
			if (!fFirst)
				clientset.m_strFilter += _T(" AND ");
			CString strFilter;
			strFilter.Format (_T("strRegNo='%s-%s-%s'"), dlg.m_strSearchRegNo1, dlg.m_strSearchRegNo2, dlg.m_strSearchRegNo3);
			clientset.m_strFilter += strFilter;
			fFirst = FALSE;
		}

		if (!clientset.Open ())
		{
			AfxMessageBox (IDS_MSG_SEARCHCLIENTFAIL);
			return;
		}

		while (!clientset.IsEOF ())
		{
			int nIndex = m_listClient.AddString (clientset.m_strName);
			m_listClient.SetItemData (nIndex, clientset.m_wID);
			clientset.MoveNext ();
		}
	}
}

void CClientListDlg::OnButtonNewclient() 
{
	CClientDlg dlg;
	if (dlg.DoModal () == IDOK)
	{
		CClientSet clientset (&g_db);
		if (!clientset.Open ())
		{
			AfxMessageBox (IDS_MSG_NEWCLIENTFAIL);
			return;
		}

		clientset.AddNew ();
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
		if (!clientset.Update ())
			AfxMessageBox (IDS_MSG_NEWCLIENTFAIL);
		else
		{
			m_listClient.ResetContent ();

			clientset.MoveLast ();
			int nIndex = m_listClient.AddString (dlg.m_strName);
			m_listClient.SetItemData (nIndex, clientset.m_wID);
		}
	}
}

void CClientListDlg::OnOK() 
{
	int nIndex = m_listClient.GetCurSel ();
	if (nIndex != LB_ERR)
		m_nClientID = m_listClient.GetItemData (nIndex);
	else
		m_nClientID = -1;
	CDialog::OnOK();
}