// BankSerialDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "BankSerialDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBankSerialDlg dialog


CBankSerialDlg::CBankSerialDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBankSerialDlg::IDD, pParent)
{
	m_fReg = FALSE;
	//{{AFX_DATA_INIT(CBankSerialDlg)
	m_nIndex = -1;
	//}}AFX_DATA_INIT
}


void CBankSerialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBankSerialDlg)
	DDX_Control(pDX, IDC_LIST_SERIAL, m_listSerial);
	DDX_LBIndex(pDX, IDC_LIST_SERIAL, m_nIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBankSerialDlg, CDialog)
	//{{AFX_MSG_MAP(CBankSerialDlg)
	ON_BN_CLICKED(IDC_BUTTON_REG, OnButtonReg)
	ON_BN_CLICKED(IDC_COPY_SERIAL, OnCopySerial)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBankSerialDlg message handlers

BOOL CBankSerialDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	for (int i = 0; i < m_arrayCode.GetSize (); i++)
		m_listSerial.AddString (m_arrayCode[i]);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBankSerialDlg::OnButtonReg() 
{
	m_fReg = TRUE;
	CDialog::OnOK ();
}

void CBankSerialDlg::OnCopySerial() 
{
	if(OpenClipboard())
	{
		CString m_str;
		HANDLE hData;
		LPTSTR lpData;

		for(int i = 0; i < m_arrayCode.GetSize(); i++)
		{
			m_str += m_arrayCode[i];
			m_str.TrimRight();
			m_str += "\r\n";
		}
		if(!(hData = GlobalAlloc(GMEM_DDESHARE, m_str.GetLength()+1))) {
#ifdef _USE_ENGLISH
			MessageBox("Out of Memory", "Serial Copy", MB_ICONHAND|MB_OK);
#else
			MessageBox("메모리가 부족합니다.", "시리얼 복사", MB_ICONHAND|MB_OK);
#endif
			return;
		}
		if (!(lpData = (LPTSTR)GlobalLock(hData))) {
#ifdef _USE_ENGLISH
			MessageBox("Out of Memory", "Serial Copy", MB_ICONHAND|MB_OK);
#else
			MessageBox("메모리가 부족합니다.", "시리얼 복사", MB_ICONHAND|MB_OK);
#endif
			return;
		}
		strcpy(lpData, (LPCTSTR)m_str);
		GlobalUnlock(hData);
		EmptyClipboard();
		SetClipboardData(CF_TEXT, hData);
		CloseClipboard();
	}
	else
	{
#ifdef _USE_ENGLISH
		MessageBox("Copy failed.", "Serial Copy", MB_ICONHAND|MB_OK);
#else
		MessageBox("복사하는 데 실패했습니다.", "시리얼 복사", MB_ICONHAND|MB_OK);
#endif
	}
}
