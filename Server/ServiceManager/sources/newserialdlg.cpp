// NewSerialDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "NewSerialDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewSerialDlg dialog


CNewSerialDlg::CNewSerialDlg(int fUpdate/*=0*/, CWnd* pParent /*=NULL*/)
	: CDialog(CNewSerialDlg::IDD, pParent)
{
	m_fUpdate = fUpdate;
	m_fGetBank = FALSE;
	//{{AFX_DATA_INIT(CNewSerialDlg)
	m_wSerial = 0;
	m_strPasswd = _T("");
	m_nMaxReg = 1;
	m_nType = 0;
	m_timeEnd = CTime::GetCurrentTime();
	m_timeStart = CTime::GetCurrentTime();
	m_nCurReg = 0;
	m_strIPNumber = _T("");
	m_nValidDay = 30;
	m_nValidTime = 1000;
	m_nIPStart = 0;
	m_nIPEnd = 255;
	m_nCustom1ValidDay = 0;
	m_nMonth = 0;
	m_nCheckClose = FALSE;
	//}}AFX_DATA_INIT
}

void CNewSerialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewSerialDlg)
	DDX_Control(pDX, IDC_SPIN_VALIDTIME, m_spinValidTime);
	DDX_Control(pDX, IDC_SPIN_VALIDDAY, m_spinValidDay);
	DDX_Control(pDX, IDC_SPIN_MAXREGUSER, m_spinMaxRegUser);
	DDX_Control(pDX, IDC_SPIN_CUSTOM1DAY, m_spinCustom1Day);
	DDX_Control(pDX, IDC_SPIN_CURREGUSER, m_spinCurRegUser);
	DDX_Text(pDX, IDC_EDIT_SERIALNO, m_wSerial);
	DDX_Text(pDX, IDC_EDIT_SERIALPASSWD, m_strPasswd);
	DDX_Text(pDX, IDC_EDIT_MAXREGUSER, m_nMaxReg);
	DDX_Radio(pDX, IDC_RADIO_TYPE, m_nType);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END, m_timeEnd);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START, m_timeStart);
	DDX_Text(pDX, IDC_EDIT_CURREGUSER, m_nCurReg);
	DDX_Text(pDX, IDC_EDIT_IPNUMBER, m_strIPNumber);
	DDX_Text(pDX, IDC_EDIT_VALIDDAY, m_nValidDay);
	DDX_Text(pDX, IDC_EDIT_VALIDTIME, m_nValidTime);
	DDX_Text(pDX, IDC_EDIT_IPSTART, m_nIPStart);
	DDX_Text(pDX, IDC_EDIT_IPEND, m_nIPEnd);
	DDX_Text(pDX, IDC_EDIT_CUSTOM1DAY, m_nCustom1ValidDay);
	DDX_Radio(pDX, IDC_RADIO_MONTH, m_nMonth);
	DDX_Check(pDX, IDC_CHECK_CLOSE, m_nCheckClose);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewSerialDlg, CDialog)
	//{{AFX_MSG_MAP(CNewSerialDlg)
	ON_BN_CLICKED(IDC_RADIO_TYPE, OnRadioTypeMember)
	ON_BN_CLICKED(IDC_RADIO_TYPEGAME, OnRadioTypeGame)
	ON_BN_CLICKED(IDC_BUTTON_BANK, OnButtonBank)
	ON_BN_CLICKED(IDC_RADIO_MONTH, OnRadioMonth)
	ON_BN_CLICKED(IDC_RADIO_TIME, OnRadioTime)
	ON_BN_CLICKED(IDC_RADIO_TYPECUSTOM1, OnRadioTypecustom1)
	ON_BN_CLICKED(IDC_RADIO_EXTENSION, OnRadioExtension)
	ON_BN_CLICKED(IDC_CHECK_CLOSE, OnCheckClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewSerialDlg message handlers

BOOL CNewSerialDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_spinValidTime.SetRange(0, UD_MAXVAL);
	m_spinValidDay.SetRange(0, UD_MAXVAL);
	m_spinMaxRegUser.SetRange(0, UD_MAXVAL);
	m_spinCustom1Day.SetRange(0, UD_MAXVAL);
	m_spinCurRegUser.SetRange(0, UD_MAXVAL);
	if (m_fUpdate == 1)
	{
		GetDlgItem (IDC_DATETIMEPICKER_START)->EnableWindow (TRUE);
		GetDlgItem (IDC_DATETIMEPICKER_END)->EnableWindow (TRUE);
		GetDlgItem (IDC_RADIO_TYPE)->EnableWindow (FALSE);
		GetDlgItem (IDC_RADIO_TYPEGAME)->EnableWindow (FALSE);
		GetDlgItem (IDC_RADIO_TYPECUSTOM1)->EnableWindow (FALSE);
		GetDlgItem (IDC_CHECK_CLOSE)->EnableWindow (FALSE);
	}

	if(m_nMonth == 1) // 시간 정액제
	{
		GetDlgItem (IDC_EDIT_VALIDDAY)->EnableWindow (FALSE);
		m_spinValidDay.EnableWindow (FALSE);
	}
	else if(m_nMonth == 0) // 기간 정액제 
	{
		GetDlgItem (IDC_EDIT_VALIDTIME)->EnableWindow (FALSE);
		m_spinValidTime.EnableWindow (FALSE);
	}
	else if(m_nMonth == 2) // 기간 연장제 
	{
		GetDlgItem (IDC_EDIT_VALIDDAY)->EnableWindow (FALSE);
		m_spinValidDay.EnableWindow (FALSE);
		GetDlgItem (IDC_EDIT_VALIDTIME)->EnableWindow (FALSE);
		m_spinValidTime.EnableWindow (FALSE);
		GetDlgItem (IDC_DATETIMEPICKER_END)->EnableWindow (FALSE);
	}

	switch(m_nType)
	{
	case 0:
		{
			GetDlgItem (IDC_EDIT_CURREGUSER)->EnableWindow (FALSE);
			m_spinCurRegUser.EnableWindow (FALSE);
			GetDlgItem (IDC_EDIT_IPNUMBER)->EnableWindow (FALSE);
			GetDlgItem (IDC_EDIT_IPSTART)->EnableWindow (FALSE);
			GetDlgItem (IDC_EDIT_IPEND)->EnableWindow (FALSE);
			GetDlgItem (IDC_EDIT_CUSTOM1DAY)->EnableWindow (FALSE);
			m_spinCustom1Day.EnableWindow (FALSE);
			if(!m_fUpdate)
			{
				GetDlgItem (IDC_RADIO_EXTENSION)->EnableWindow (FALSE);
				GetDlgItem (IDC_CHECK_CLOSE)->EnableWindow (FALSE);
			}
			break;
		}
	case 1:
		{
			GetDlgItem (IDC_EDIT_MAXREGUSER)->EnableWindow (FALSE);
			m_spinMaxRegUser.EnableWindow (FALSE);
			GetDlgItem (IDC_EDIT_SERIALPASSWD)->EnableWindow (FALSE);
			GetDlgItem (IDC_EDIT_CUSTOM1DAY)->EnableWindow (FALSE);
			m_spinCustom1Day.EnableWindow (FALSE);
			break;
		}
	case 2:
		{
			GetDlgItem (IDC_EDIT_CURREGUSER)->EnableWindow (FALSE);
			m_spinCurRegUser.EnableWindow (FALSE);
			GetDlgItem (IDC_EDIT_IPNUMBER)->EnableWindow (FALSE);
			GetDlgItem (IDC_EDIT_IPSTART)->EnableWindow (FALSE);
			GetDlgItem (IDC_EDIT_IPEND)->EnableWindow (FALSE);
			GetDlgItem (IDC_EDIT_MAXREGUSER)->EnableWindow (FALSE);
			m_spinMaxRegUser.EnableWindow (FALSE);
			GetDlgItem (IDC_EDIT_SERIALPASSWD)->EnableWindow (FALSE);
			break;
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewSerialDlg::OnRadioTypeMember() 
{	
	GetDlgItem (IDC_EDIT_MAXREGUSER)->EnableWindow (TRUE);
	m_spinMaxRegUser.EnableWindow (TRUE);
	GetDlgItem (IDC_EDIT_SERIALPASSWD)->EnableWindow (TRUE);
	GetDlgItem (IDC_RADIO_MONTH)->EnableWindow (TRUE);
	GetDlgItem (IDC_RADIO_TIME)->EnableWindow (TRUE);
	if(m_nMonth == 0)
	{
		GetDlgItem (IDC_EDIT_VALIDDAY)->EnableWindow (TRUE);
		m_spinValidDay.EnableWindow (TRUE);
	}
	else
	{
		GetDlgItem (IDC_EDIT_VALIDTIME)->EnableWindow (TRUE);
		m_spinValidTime.EnableWindow (TRUE);
	}

	GetDlgItem (IDC_EDIT_CURREGUSER)->EnableWindow (FALSE);
	m_spinCurRegUser.EnableWindow (FALSE);
	GetDlgItem (IDC_EDIT_IPNUMBER)->EnableWindow (FALSE);
	GetDlgItem (IDC_EDIT_IPSTART)->EnableWindow (FALSE);
	GetDlgItem (IDC_EDIT_IPEND)->EnableWindow (FALSE);
	GetDlgItem (IDC_EDIT_CUSTOM1DAY)->EnableWindow (FALSE);
	m_spinCustom1Day.EnableWindow (FALSE);
	GetDlgItem (IDC_DATETIMEPICKER_START)->EnableWindow (FALSE);
	GetDlgItem (IDC_DATETIMEPICKER_END)->EnableWindow (FALSE);
	GetDlgItem (IDC_RADIO_EXTENSION)->EnableWindow(FALSE);
	GetDlgItem (IDC_CHECK_CLOSE)->EnableWindow (FALSE);
}

void CNewSerialDlg::OnRadioTypeGame() 
{
	GetDlgItem (IDC_EDIT_CURREGUSER)->EnableWindow (TRUE);
	m_spinCurRegUser.EnableWindow (TRUE);
	GetDlgItem (IDC_EDIT_IPNUMBER)->EnableWindow (TRUE);
	GetDlgItem (IDC_EDIT_IPSTART)->EnableWindow (TRUE);
	GetDlgItem (IDC_EDIT_IPEND)->EnableWindow (TRUE);
	GetDlgItem (IDC_RADIO_MONTH)->EnableWindow (TRUE);
	GetDlgItem (IDC_RADIO_TIME)->EnableWindow (TRUE);
	if(m_nMonth == 0)
	{
		GetDlgItem (IDC_EDIT_VALIDDAY)->EnableWindow (TRUE);
		m_spinValidDay.EnableWindow (TRUE);
	}
	else
	{
		GetDlgItem (IDC_EDIT_VALIDTIME)->EnableWindow (TRUE);
		m_spinValidTime.EnableWindow (TRUE);
	}

	GetDlgItem (IDC_EDIT_MAXREGUSER)->EnableWindow (FALSE);
	m_spinMaxRegUser.EnableWindow (FALSE);
	GetDlgItem (IDC_EDIT_SERIALPASSWD)->EnableWindow (FALSE);
	GetDlgItem (IDC_EDIT_CUSTOM1DAY)->EnableWindow (FALSE);
	m_spinCustom1Day.EnableWindow (FALSE);
	GetDlgItem (IDC_DATETIMEPICKER_START)->EnableWindow (FALSE);
	GetDlgItem (IDC_DATETIMEPICKER_END)->EnableWindow (FALSE);
	GetDlgItem (IDC_RADIO_EXTENSION)->EnableWindow(FALSE);
	GetDlgItem (IDC_CHECK_CLOSE)->EnableWindow (FALSE);
}

void CNewSerialDlg::OnButtonBank() 
{
	m_fGetBank = TRUE;
	CDialog::OnOK ();
}

void CNewSerialDlg::OnRadioMonth() 
{
	m_nMonth = 0;
	GetDlgItem (IDC_EDIT_VALIDDAY)->EnableWindow (TRUE);
	m_spinValidDay.EnableWindow (TRUE);
	GetDlgItem (IDC_EDIT_VALIDTIME)->EnableWindow (FALSE);
	m_spinValidTime.EnableWindow (FALSE);
	if(!m_fUpdate)
	{
		GetDlgItem (IDC_RADIO_EXTENSION)->EnableWindow(FALSE);
	}
	else
		GetDlgItem (IDC_DATETIMEPICKER_END)->EnableWindow (TRUE);
	GetDlgItem (IDC_CHECK_CLOSE)->EnableWindow (FALSE);
}

void CNewSerialDlg::OnRadioTime() 
{
	m_nMonth = 1;
	GetDlgItem (IDC_EDIT_VALIDDAY)->EnableWindow (FALSE);
	m_spinValidDay.EnableWindow (FALSE);
	GetDlgItem (IDC_EDIT_VALIDTIME)->EnableWindow (TRUE);
	m_spinValidTime.EnableWindow (TRUE);
	GetDlgItem (IDC_RADIO_EXTENSION)->EnableWindow(TRUE);
	if(!m_fUpdate)
	{
		GetDlgItem (IDC_RADIO_EXTENSION)->EnableWindow(FALSE);
	}
	else
		GetDlgItem (IDC_DATETIMEPICKER_END)->EnableWindow (TRUE);
	GetDlgItem (IDC_CHECK_CLOSE)->EnableWindow (FALSE);
}

void CNewSerialDlg::OnRadioExtension() 
{
	// TODO: Add your control notification handler code here
	m_nMonth = 2;
	GetDlgItem (IDC_EDIT_VALIDDAY)->EnableWindow (FALSE);
	m_spinValidDay.EnableWindow (FALSE);
	GetDlgItem (IDC_EDIT_VALIDTIME)->EnableWindow (FALSE);
	m_spinValidTime.EnableWindow (FALSE);
	GetDlgItem (IDC_RADIO_EXTENSION)->EnableWindow(TRUE);
	GetDlgItem (IDC_DATETIMEPICKER_END)->EnableWindow (FALSE);
	GetDlgItem (IDC_CHECK_CLOSE)->EnableWindow (TRUE);
}

void CNewSerialDlg::OnOK() 
{
	UpdateData();

	switch(m_nType)
	{
	case 1:
		{
			if(m_nIPStart < 0 || m_nIPStart > 255)
			{
#ifdef _USE_ENGLISH
				MessageBox("Fill the beginning number of IP with between 0 and 255", "Charge code registration", MB_OK|MB_ICONINFORMATION);
#else
				MessageBox("IP시작 번호를 0에서 255사이로 넣어주십시요", "과금코드 등록", MB_OK|MB_ICONINFORMATION);
#endif
				GetDlgItem(IDC_EDIT_IPSTART)->SetFocus();
				return;
			}
			if(m_nIPEnd < 0 || m_nIPEnd > 255)
			{
#ifdef _USE_ENGLISH
				MessageBox("Fill the ending number of IP with between 0 and 255", "Charge code registration", MB_OK|MB_ICONINFORMATION);
#else
				MessageBox("IP끝 번호를 0에서 255사이로 넣어주십시요", "과금코드 등록", MB_OK|MB_ICONINFORMATION);
#endif
				GetDlgItem(IDC_EDIT_IPEND)->SetFocus();
				return;
			}
			if(m_nIPStart > m_nIPEnd)
			{
#ifdef _USE_ENGLISH
				MessageBox("Fill the beginning number of IP smaller than the ending number of IP", "Charge code registration", MB_OK|MB_ICONINFORMATION);
#else
				MessageBox("IP시작 번호가 IP끝 번호보다 작게 넣어주십시요", "과금코드 등록", MB_OK|MB_ICONINFORMATION);
#endif
				return;
			}
			break;
		}
	case 2:
		{
			if(m_timeEnd <= m_timeStart)
			{
#ifdef _USE_ENGLISH
				MessageBox("Wrong indication of beginning and ending date.", "Charge code registration", MB_OK|MB_ICONINFORMATION);
#else
				MessageBox("시작, 종료 날짜를 잘못 지정하셨습니다.", "과금코드 등록", MB_OK|MB_ICONINFORMATION);
#endif
				return;
			}
			if(m_nCustom1ValidDay <= 0)
			{
#ifdef _USE_ENGLISH
				MessageBox("Wrong indication of use time.", "Charge code registration", MB_OK|MB_ICONINFORMATION);
#else
				MessageBox("사용 시간을 잘못 지정하셨습니다.", "과금코드 등록", MB_OK|MB_ICONINFORMATION);
#endif
				GetDlgItem(IDC_EDIT_CUSTOM1DAY)->SetFocus();
				return;
			}
			break;
		}
	}
	
	CDialog::OnOK();
}

void CNewSerialDlg::OnRadioTypecustom1() 
{
	GetDlgItem (IDC_EDIT_CUSTOM1DAY)->EnableWindow (TRUE);
	m_spinCustom1Day.EnableWindow (TRUE);
	GetDlgItem (IDC_DATETIMEPICKER_START)->EnableWindow (TRUE);
	GetDlgItem (IDC_DATETIMEPICKER_END)->EnableWindow (TRUE);

	GetDlgItem (IDC_EDIT_CURREGUSER)->EnableWindow (FALSE);
	m_spinCurRegUser.EnableWindow (FALSE);
	GetDlgItem (IDC_EDIT_IPNUMBER)->EnableWindow (FALSE);
	GetDlgItem (IDC_EDIT_IPSTART)->EnableWindow (FALSE);
	GetDlgItem (IDC_EDIT_IPEND)->EnableWindow (FALSE);
	GetDlgItem (IDC_EDIT_MAXREGUSER)->EnableWindow (FALSE);
	m_spinMaxRegUser.EnableWindow (FALSE);
	GetDlgItem (IDC_EDIT_SERIALPASSWD)->EnableWindow (FALSE);
	GetDlgItem (IDC_RADIO_MONTH)->EnableWindow (FALSE);
	GetDlgItem (IDC_RADIO_TIME)->EnableWindow (FALSE);
	GetDlgItem (IDC_EDIT_VALIDDAY)->EnableWindow (FALSE);
	m_spinValidDay.EnableWindow (FALSE);
	GetDlgItem (IDC_EDIT_VALIDTIME)->EnableWindow (FALSE);
	m_spinValidTime.EnableWindow (FALSE);
	GetDlgItem (IDC_RADIO_EXTENSION)->EnableWindow(FALSE);
	GetDlgItem (IDC_CHECK_CLOSE)->EnableWindow (FALSE);
}

void CNewSerialDlg::OnCheckClose() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_nCheckClose)
	{
		GetDlgItem (IDC_DATETIMEPICKER_END)->EnableWindow (TRUE);
	}
	else
	{
		GetDlgItem (IDC_DATETIMEPICKER_END)->EnableWindow (FALSE);
	}
}
