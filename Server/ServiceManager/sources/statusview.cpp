// StatusView.cpp : implementation file
//


#include "stdafx.h"
#include "ServiceManager.h"
#include "SerialSet.h"
#include "LogSet.h"
#include "BankSet.h"
#include "BankSerialSet.h"
#include "BadIDSet.h"
#include "ClientLogSet.h"

#include "../include/UMProtocol.h"
#include "ServiceManagerDoc.h"
#include "StatusView.h"
//#include "LogDBTable.h"		// Modifyed Jaeseung Oh
#include "ColumnTitle.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define VIEW_NONE			0x00000000
#define VIEW_SERIAL			0x00000100
#define VIEW_LOG			0x00000200
#define VIEW_BANK			0x00000400
#define VIEW_BADID			0x00000800

#define SORT_SERIAL_NO		0x00000001
#define SORT_SERIAL_TYPE	0x00000002
#define SORT_SERIAL_PASSWD	0x00000004
#define SORT_SERIAL_START	0x00000008
#define SORT_SERIAL_END		0x00000010
#define SORT_SERIAL_MAXREG	0x00000020
#define SORT_SERIAL_CURREG	0x00000040
#define SORT_SERIAL_VALID	0x00000080

#define SORT_LOG_SERVICE	0x00000001
#define SORT_LOG_USERID		0x00000002
#define SORT_LOG_LOGIN		0x00000004
#define SORT_LOG_LOGOUT		0x00000008
#define SORT_LOG_TIME		0x00000010
#define SORT_LOG_SERIAL		0x00000020
#define SORT_LOG_REASON		0x00000040
#define SORT_LOG_IPADDR		0x00000080

#define SORT_BANK_NO		0x00000001
#define SORT_BANK_DATE		0x00000002
#define SORT_BANK_NAME		0x00000004
#define SORT_BANK_BANK		0x00000008
#define SORT_BANK_MONEY		0x00000010
#define SORT_BANK_OPER		0x00000020
#define SORT_BANK_TYPE		0x00000040
#define SORT_BANK_PROC		0x00000080

#define SORT_BADID_USERID	0x00000001
#define SORT_BADID_FROM		0x00000002
#define SORT_BADID_TO		0x00000004
#define SORT_BADID_OPER		0x00000008


int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, 
    LPARAM lParamSort)
{
	if (lParamSort & VIEW_SERIAL)
	{
		CSerial* pSerial1 = (CSerial*)lParam1;
		CSerial* pSerial2 = (CSerial*)lParam2;
		if (lParamSort & SORT_SERIAL_NO)
		{
			if (pSerial1->m_wSerial < pSerial2->m_wSerial)
				return -1;
			else if (pSerial1->m_wSerial > pSerial2->m_wSerial)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_SERIAL_TYPE)
		{
			if (pSerial1->m_nType < pSerial2->m_nType)
				return -1;
			else if (pSerial1->m_nType > pSerial2->m_nType)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_SERIAL_PASSWD)
		{
			if (pSerial1->m_strPasswd < pSerial2->m_strPasswd)
				return -1;
			else if (pSerial1->m_strPasswd > pSerial2->m_strPasswd)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_SERIAL_START)
		{
			if (pSerial1->m_fFirstUse || pSerial2->m_fFirstUse)
			{
				if (pSerial1->m_fFirstUse && pSerial2->m_fFirstUse)
					return 0;
				else if (pSerial1->m_fFirstUse)
					return -1;
				else 
					return 1;
			}
			else
			{
				if (pSerial1->m_timeStart < pSerial2->m_timeStart)
					return -1;
				else if (pSerial1->m_timeStart > pSerial2->m_timeStart)
					return 1;
				else
					return 0;
			}
		}
		else if (lParamSort & SORT_SERIAL_END)
		{
			if (pSerial1->m_fFirstUse || pSerial2->m_fFirstUse)
			{
				if (pSerial1->m_fFirstUse && pSerial2->m_fFirstUse)
					return 0;
				else if (pSerial1->m_fFirstUse)
					return -1;
				else 
					return 1;
			}
			else
			{
				if (pSerial1->m_timeEnd < pSerial2->m_timeEnd)
					return -1;
				else if (pSerial1->m_timeEnd > pSerial2->m_timeEnd)
					return 1;
				else
					return 0;
			}
		}
		else if (lParamSort & SORT_SERIAL_MAXREG)
		{
			if (pSerial1->m_nMaxReg < pSerial2->m_nMaxReg)
				return -1;
			else if (pSerial1->m_nMaxReg > pSerial2->m_nMaxReg)
				return 1;
			else
				return 0;
		}
		else if (lParamSort & SORT_SERIAL_CURREG)
		{
			if (pSerial1->m_nCurReg < pSerial2->m_nCurReg)
				return -1;
			else if (pSerial1->m_nCurReg > pSerial2->m_nCurReg)
				return 1;
			else
				return 0;
		}
		else if (lParamSort & SORT_SERIAL_VALID)
		{
			if (pSerial1->m_nValidDay < pSerial2->m_nValidDay)
				return -1;
			else if (pSerial1->m_nValidDay > pSerial2->m_nValidDay)
				return 1;
			else
				return 0;
		}
	}
	else if (lParamSort & VIEW_LOG)
	{
		CLog* pLog1 = (CLog*)lParam1;
		CLog* pLog2 = (CLog*)lParam2;
		if (lParamSort & SORT_LOG_SERVICE)
		{
			if (pLog1->m_nServiceID < pLog2->m_nServiceID)
				return -1;
			else if (pLog1->m_nServiceID > pLog2->m_nServiceID)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_LOG_USERID)
		{
			if (pLog1->m_strUserID < pLog2->m_strUserID)
				return -1;
			else if (pLog1->m_strUserID > pLog2->m_strUserID)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_LOG_LOGIN)
		{
			if (pLog1->m_timeStart < pLog2->m_timeStart)
				return -1;
			else if (pLog1->m_timeStart > pLog2->m_timeStart)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_LOG_LOGOUT)
		{
			if (pLog1->m_timeEnd < pLog2->m_timeEnd)
				return -1;
			else if (pLog1->m_timeEnd > pLog2->m_timeEnd)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_LOG_TIME)
		{
			if (pLog1->m_nUseTime < pLog2->m_nUseTime)
				return -1;
			else if (pLog1->m_nUseTime > pLog2->m_nUseTime)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_LOG_SERIAL)
		{
			if (pLog1->m_wSerial < pLog2->m_wSerial)
				return -1;
			else if (pLog1->m_wSerial > pLog2->m_wSerial)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_LOG_REASON)
		{
			if (pLog1->m_bReason < pLog2->m_bReason)
				return -1;
			else if (pLog1->m_bReason > pLog2->m_bReason)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_LOG_IPADDR)
		{
			if (pLog1->m_strIPAddr < pLog2->m_strIPAddr)
				return -1;
			else if (pLog1->m_strIPAddr > pLog2->m_strIPAddr)
				return 1;
			else 
				return 0;
		}
	}
	else if (lParamSort & VIEW_BANK)
	{
		CBank* pBank1 = (CBank*)lParam1;
		CBank* pBank2 = (CBank*)lParam2;

		if (lParamSort & SORT_BANK_NO)
		{
			if (pBank1->m_nID < pBank2->m_nID)
				return -1;
			else if (pBank1->m_nID > pBank2->m_nID)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_BANK_DATE)
		{
			if (pBank1->m_timeReg < pBank2->m_timeReg)
				return -1;
			else if (pBank1->m_timeReg > pBank2->m_timeReg)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_BANK_NAME)
		{
			if (pBank1->m_strName < pBank2->m_strName)
				return -1;
			else if (pBank1->m_strName > pBank2->m_strName)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_BANK_BANK)
		{
			if (pBank1->m_strBank < pBank2->m_strBank)
				return -1;
			else if (pBank1->m_strBank > pBank2->m_strBank)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_BANK_MONEY)
		{
			if (pBank1->m_nMoney < pBank2->m_nMoney)
				return -1;
			else if (pBank1->m_nMoney > pBank2->m_nMoney)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_BANK_TYPE)
		{
			if (pBank1->m_bType < pBank2->m_bType)
				return -1;
			else if (pBank1->m_bType > pBank2->m_bType)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_BANK_PROC)
		{
			if (pBank1->m_bProcess < pBank2->m_bProcess)
				return -1;
			else if (pBank1->m_bProcess > pBank2->m_bProcess)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_BANK_OPER)
		{
			if (pBank1->m_strOper < pBank2->m_strOper)
				return -1;
			else if (pBank1->m_strOper > pBank2->m_strOper)
				return 1;
			else 
				return 0;
		}
	}
	else if (lParamSort & VIEW_BADID)
	{
		CBadID* pBadID1 = (CBadID*)lParam1;
		CBadID* pBadID2 = (CBadID*)lParam2;

		if (lParamSort & SORT_BADID_USERID)
		{
			if (pBadID1->m_strUserID < pBadID2->m_strUserID)
				return -1;
			else if (pBadID1->m_strUserID > pBadID2->m_strUserID)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_BADID_FROM)
		{
			if (pBadID1->m_timeFrom < pBadID2->m_timeFrom)
				return -1;
			else if (pBadID1->m_timeFrom > pBadID2->m_timeFrom)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_BADID_TO)
		{
			if (pBadID1->m_timeTo < pBadID2->m_timeTo)
				return -1;
			else if (pBadID1->m_timeTo > pBadID2->m_timeTo)
				return 1;
			else 
				return 0;
		}
		else if (lParamSort & SORT_BADID_OPER)
		{
			if (pBadID1->m_strOper < pBadID2->m_strOper)
				return -1;
			else if (pBadID1->m_strOper > pBadID2->m_strOper)
				return 1;
			else 
				return 0;
		}
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CStatusView

IMPLEMENT_DYNCREATE(CStatusView, CListView)

CStatusView::CStatusView()
{
}

CStatusView::~CStatusView()
{
}


BEGIN_MESSAGE_MAP(CStatusView, CListView)
	//{{AFX_MSG_MAP(CStatusView)
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusView drawing

void CStatusView::OnDraw(CDC* pDC)
{
	ASSERT_VALID(pDC);
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CStatusView diagnostics

#ifdef _DEBUG
void CStatusView::AssertValid() const
{
	CListView::AssertValid();
}

void CStatusView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CServiceManagerDoc* CStatusView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CServiceManagerDoc)));
	return (CServiceManagerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatusView message handlers


//======================================================================
// List Controll Update 및 CServiceManagerDoc의 각각의 List Update
//======================================================================

void CStatusView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CListCtrl& list = GetListCtrl ();
	CServiceManagerDoc* pDoc = GetDocument();
	BYTE index;

	list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	switch (lHint)
	{
	case UPDATE_VIEWCLIENT :
		{
			pDoc->m_nListStatus = m_nView = viewPay;

			list.DeleteAllItems ();
			for( index = 0; index < COL_MAX; index++) list.DeleteColumn (0);

			LV_COLUMN	lvc;
			lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

			for( index=0; index < ColInfo[m_nView].nColumnCount; index++ )
			{
				switch(index)
				{
				case 0  : lvc.fmt = LVCFMT_LEFT;   break;
				case 1  :
				case 3  : lvc.fmt = LVCFMT_CENTER; break;
				default : lvc.fmt = LVCFMT_RIGHT;  break;
				}

				lvc.pszText = ColInfo[m_nView].lpColInfo[index].lpstrText;
				lvc.cx = ColInfo[m_nView].lpColInfo[index].ColumnWidth;
				lvc.iSubItem = index;

			    list.InsertColumn ( index, &lvc);
			}

			POSITION pos = pDoc->m_listClient.GetHeadPosition ();
			while (pos)
			{
				CClient* pObj = (CClient*)pDoc->m_listClient.GetNext(pos);
				AddClient( pObj, (CStringList*)pHint);
			}
		}
		break;

	case UPDATE_VIEWLOG : 
		{
			pDoc->m_nListStatus = m_nView = viewLog;

			list.DeleteAllItems ();
			for( index = 0; index < COL_MAX; index++) list.DeleteColumn (0);

			LV_COLUMN	lvc;
			lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			lvc.fmt = LVCFMT_LEFT;

			for( index=0; index < ColInfo[m_nView].nColumnCount; index++ )
			{
				lvc.pszText = ColInfo[m_nView].lpColInfo[index].lpstrText;
				lvc.cx = ColInfo[m_nView].lpColInfo[index].ColumnWidth;
				lvc.iSubItem = index;

			    list.InsertColumn ( index, &lvc);
			}

			POSITION pos = pDoc->m_listLog.GetHeadPosition ();
			while (pos)
			{
				CLog* pLog = (CLog*)pDoc->m_listLog.GetNext (pos);
				AddLog (pLog);
			}
		}
		break;

	case UPDATE_ADDLOG :
		if (m_nView == viewLog)
		{
			AddLog ((CLogSet*)pHint);
		}
		break;

	case UPDATE_VIEWSERIAL :
		{
			pDoc->m_nListStatus = m_nView = viewSerial;

			list.DeleteAllItems ();
			for( index = 0; index < COL_MAX; index++) list.DeleteColumn (0);

			LV_COLUMN	lvc;
			lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			lvc.fmt = LVCFMT_LEFT;

			for( index=0; index < ColInfo[m_nView].nColumnCount; index++ )
			{
				lvc.pszText = ColInfo[m_nView].lpColInfo[index].lpstrText;
				lvc.cx = ColInfo[m_nView].lpColInfo[index].ColumnWidth;
				lvc.iSubItem = index;

			    list.InsertColumn ( index, &lvc);
			}

			POSITION pos = pDoc->m_listSerial.GetHeadPosition ();
			while (pos)
			{
				CSerial* pSerial = (CSerial*)pDoc->m_listSerial.GetNext (pos);
				AddSerial (pSerial);
			}
		}
		break;

	case UPDATE_ADDSERIAL :
		if (m_nView == viewSerial)
		{
			AddSerial ((CSerialSet*)pHint);
		}
		break;

	case UPDATE_UPDATESERIAL :
		if (m_nView == viewSerial)
		{
			UpdateSerial ((CSerialSet*)pHint);
		}
		break;

	case UPDATE_VIEWBANK :
		{
			pDoc->m_nListStatus = m_nView = viewBank;

			list.DeleteAllItems ();
			for( index = 0; index < COL_MAX; index++) list.DeleteColumn (0);

			LV_COLUMN	lvc;
			lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			lvc.fmt = LVCFMT_LEFT;

			for( index=0; index < ColInfo[m_nView].nColumnCount; index++ )
			{
				lvc.pszText = ColInfo[m_nView].lpColInfo[index].lpstrText;
				lvc.cx = ColInfo[m_nView].lpColInfo[index].ColumnWidth;
				lvc.iSubItem = index;

			    list.InsertColumn ( index, &lvc);
			}
			
			POSITION pos = pDoc->m_listBank.GetHeadPosition ();
			while (pos)
			{
				CBank* pBank = (CBank*)pDoc->m_listBank.GetNext (pos);
				AddBank (pBank);
			}
		}
		break;

	case UPDATE_ADDBANK :
		if (m_nView == viewBank)
		{
			AddBank ((CBankSet*)pHint);
		}
		break;

	case UPDATE_UPDATEBANK :
		if (m_nView == viewBank)
		{
			UpdateBank ((CBankSet*)pHint);
		}
		break;

	case UPDATE_VIEWBADID :
		{
			pDoc->m_nListStatus = m_nView = viewBadID;

			list.DeleteAllItems ();
			for( index = 0; index < COL_MAX; index++) list.DeleteColumn (0);

			LV_COLUMN	lvc;
			lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			lvc.fmt = LVCFMT_LEFT;

			for( index=0; index < ColInfo[m_nView].nColumnCount; index++ )
			{
				lvc.pszText = ColInfo[m_nView].lpColInfo[index].lpstrText;
				lvc.cx = ColInfo[m_nView].lpColInfo[index].ColumnWidth;
				lvc.iSubItem = index;
			    list.InsertColumn ( index, &lvc);
			}
		}
		break;

	case UPDATE_ADDBADID :
		if (m_nView == viewBadID)
		{
			AddBadID ((CBadIDSet*)pHint);
		}
		break;
	case UPDATE_ADDCLIENTLOG :
		if (m_nView == viewLog)
		{
			AddClientLog ((CClientLogSet*)pHint);
		}
		break;
	}
}

BOOL CStatusView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= LVS_REPORT | LVS_SINGLESEL | LVS_SORTASCENDING;
	return CListView::PreCreateWindow(cs);
}

void CStatusView::AddLog(CLogSet * plogset)
{
	CListCtrl& list = GetListCtrl ();
	CServiceManagerDoc* pDoc = GetDocument();

	CLog* pLog = new CLog (plogset);
	pDoc->m_listLog.AddTail (pLog);

	LV_ITEM		item;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = 0;
	item.iSubItem = 0;
	item.pszText = (char*)LPCTSTR(pDoc->GetSessionName (plogset->m_nServiceID));
	item.lParam = (LPARAM)pLog;

	int nIndex = list.InsertItem (&item);

	list.SetItemText (nIndex, 1, plogset->m_strUserID);

	CString strText = plogset->m_timeLogin.Format (_T("%Y/%m/%d %H:%M"));
	list.SetItemText (nIndex, 2, strText);

	CTimeSpan timeUse (plogset->m_nUseTime);
	strText = timeUse.Format (_T("%H:%M:%S"));
	list.SetItemText (nIndex, 4, strText);

	CTime timeEnd = plogset->m_timeLogin + timeUse;
	strText = timeEnd.Format (_T("%Y/%m/%d %H:%M"));
	list.SetItemText (nIndex, 3, strText);

	if (plogset->IsFieldNull (&plogset->m_wSerial))
#ifdef _USE_ENGLISH
		strText = _T("None");
#else
		strText = _T("없음");
#endif
	else
		strText.Format (_T("%05d"), plogset->m_wSerial);
	list.SetItemText (nIndex, 5, strText);

	CString strReason;
	switch (plogset->m_bReason)
	{
	case DR_NORMAL :	strReason.LoadString (IDS_REASON_NORMAL); break;
	case DR_DUPLICATE :	strReason.LoadString (IDS_REASON_DUPLICATE); break;
	case DR_CANCEL :	strReason.LoadString (IDS_REASON_CANCEL); break;
	case DR_CLIENT :	strReason.LoadString (IDS_REASON_CLIENT); break;
	case DR_TIMEOUT :	strReason.LoadString (IDS_REASON_TIMEOUT); break;
	case DR_LINK :		strReason.LoadString (IDS_REASON_LINK); break;
	case DR_SESSION :	strReason.LoadString (IDS_REASON_SESSION); break;
	}
	list.SetItemText (nIndex, 6, strReason);
	list.SetItemText (nIndex, 7, plogset->m_strIPAddr);

}

void CStatusView::AddLog(CLog* pLog)
{
	CListCtrl& list = GetListCtrl ();
	CServiceManagerDoc* pDoc = GetDocument();

	LV_ITEM		item;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = 0;
	item.iSubItem = 0;
	item.pszText = (char*)LPCTSTR(pDoc->GetSessionName (pLog->m_nServiceID));
	item.lParam = (LPARAM)pLog;

	int nIndex = list.InsertItem (&item);

	list.SetItemText (nIndex, 1, pLog->m_strUserID);

	CString strText = pLog->m_timeStart.Format (_T("%Y/%m/%d %H:%M"));
	list.SetItemText (nIndex, 2, strText);

	if (pLog->m_timeStart < pLog->m_timeEnd)
		strText = pLog->m_timeEnd.Format (_T("%Y/%m/%d %H:%M"));
	else
		strText = _T("");
	list.SetItemText (nIndex, 3, strText);

	CTimeSpan timeUse (pLog->m_nUseTime);
	if (pLog->m_nUseTime > 0)
		strText = timeUse.Format (_T("%H:%M:%S"));
	else
		strText = _T("");
	list.SetItemText (nIndex, 4, strText);

	if (!pLog->m_wSerial)
#ifdef _USE_ENGLISH
		strText = _T("None");
#else
		strText = _T("없음");
#endif
	else
		strText.Format (_T("%05d"), pLog->m_wSerial);
	list.SetItemText (nIndex, 5, strText);

	CString strReason;
	switch (pLog->m_bReason)
	{
	case DR_NORMAL :	strReason.LoadString (IDS_REASON_NORMAL); break;
	case DR_DUPLICATE :	strReason.LoadString (IDS_REASON_DUPLICATE); break;
	case DR_CANCEL :	strReason.LoadString (IDS_REASON_CANCEL); break;
	case DR_CLIENT :	strReason.LoadString (IDS_REASON_CLIENT); break;
	case DR_TIMEOUT :	strReason.LoadString (IDS_REASON_TIMEOUT); break;
	case DR_LINK :		strReason.LoadString (IDS_REASON_LINK); break;
	case DR_SESSION :	strReason.LoadString (IDS_REASON_SESSION); break;
	}
	list.SetItemText (nIndex, 6, strReason);
	list.SetItemText (nIndex, 7, pLog->m_strIPAddr);
}

void CStatusView::AddSerial(CSerialSet* pserialset)
{
	CListCtrl& list = GetListCtrl ();
	CServiceManagerDoc* pDoc = GetDocument();

	CSerial* pSerial = new CSerial (pserialset);
	pDoc->m_listSerial.AddTail (pSerial);

	CString strText;
	strText.Format (_T("%05u"), pserialset->m_wSerial);
	LV_ITEM		item;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = 0;
	item.iSubItem = 0;
	item.pszText = (char*)LPCTSTR(strText);
	item.lParam = (LPARAM)pSerial;

	int nIndex = list.InsertItem (&item);

	CString strType;
	GetSerialTypeString (pserialset->GetType (), strType);
	list.SetItemText (nIndex, 1, strType);
	list.SetItemText (nIndex, 2, pserialset->m_strPasswd);

	if (!pserialset->IsFirstUse ())
	{
		strText = pserialset->m_timeStart.Format (_T("%Y/%m/%d %H:%M"));
		list.SetItemText (nIndex, 3, strText);

		strText = pserialset->m_timeEnd.Format (_T("%Y/%m/%d %H:%M"));
		list.SetItemText (nIndex, 4, strText);
	}

	strText.Format (_T("%d"), pserialset->m_nMaxReg);
	list.SetItemText (nIndex, 5, strText);

	strText.Format (_T("%d"), pserialset->m_nCurReg);
	list.SetItemText (nIndex, 6, strText);

#ifdef _USE_ENGLISH
	if (pserialset->m_nValidDay > 0)
		strText.Format (_T("%d day(s)"), pserialset->m_nValidDay);
	else if (pserialset->m_nValidDay < 0)
		strText.Format (_T("%d hour(s)"), -pserialset->m_nValidDay/3600);
	else
		strText = _T("");
#else
	if (pserialset->m_nValidDay > 0)
		strText.Format (_T("%d일"), pserialset->m_nValidDay);
	else if (pserialset->m_nValidDay < 0)
		strText.Format (_T("%d시간"), -pserialset->m_nValidDay/3600);
	else
		strText = _T("");
#endif
	list.SetItemText (nIndex, 7, strText);
}

void CStatusView::AddSerial(CSerial* pSerial)
{
	CListCtrl& list = GetListCtrl ();
	CServiceManagerDoc* pDoc = GetDocument();

	CString strText;
	strText.Format (_T("%05u"), pSerial->m_wSerial);
	LV_ITEM		item;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = 0;
	item.iSubItem = 0;
	item.pszText = (char*)LPCTSTR(strText);
	item.lParam = (LPARAM)pSerial;

	int nIndex = list.InsertItem (&item);

	CString strType;
	GetSerialTypeString (pSerial->m_nType, strType);
	list.SetItemText (nIndex, 1, strType);
	list.SetItemText (nIndex, 2, pSerial->m_strPasswd);

	if (!pSerial->m_fFirstUse)
	{
		strText = pSerial->m_timeStart.Format (_T("%Y/%m/%d %H:%M"));
		list.SetItemText (nIndex, 3, strText);

		strText = pSerial->m_timeEnd.Format (_T("%Y/%m/%d %H:%M"));
		list.SetItemText (nIndex, 4, strText);
	}

	strText.Format (_T("%d"), pSerial->m_nMaxReg);
	list.SetItemText (nIndex, 5, strText);

	strText.Format (_T("%d"), pSerial->m_nCurReg);
	list.SetItemText (nIndex, 6, strText);

#ifdef _USE_ENGLISH
	if (pSerial->m_nValidDay > 0)
		strText.Format (_T("%d day(s)"), pSerial->m_nValidDay);
	else if (pSerial->m_nValidDay < 0)
		strText.Format (_T("%d hour(s)"), - pSerial->m_nValidDay / 3600);
	else
		strText = _T("");
#else
	if (pSerial->m_nValidDay > 0)
		strText.Format (_T("%d일"), pSerial->m_nValidDay);
	else if (pSerial->m_nValidDay < 0)
		strText.Format (_T("%d시간"), - pSerial->m_nValidDay / 3600);
	else
		strText = _T("");
#endif
	list.SetItemText (nIndex, 7, strText);
}

void CStatusView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	m_nView = viewNone;
}

void CStatusView::UpdateSerial(CSerialSet *pserialset)
{
	CListCtrl& list = GetListCtrl ();

	CString strText;
	strText.Format (_T("%05u"), pserialset->m_wSerial);

	LVFINDINFO fi;
	fi.flags = LVFI_STRING;
	fi.psz = (char*)LPCTSTR(strText);
	int nIndex = list.FindItem (&fi);
	if (nIndex >= 0)
	{
		CString strType;
		GetSerialTypeString (pserialset->GetType (), strType);
		list.SetItemText (nIndex, 1, strType);
		list.SetItemText (nIndex, 2, pserialset->m_strPasswd);

		if (!pserialset->IsFirstUse ())
		{
			strText = pserialset->m_timeStart.Format (_T("%Y/%m/%d %H:%M"));
			list.SetItemText (nIndex, 3, strText);

			strText = pserialset->m_timeEnd.Format (_T("%Y/%m/%d %H:%M"));
			list.SetItemText (nIndex, 4, strText);
		}

		strText.Format (_T("%d"), pserialset->m_nMaxReg);
		list.SetItemText (nIndex, 5, strText);

		strText.Format (_T("%d"), pserialset->m_nCurReg);
		list.SetItemText (nIndex, 6, strText);

#ifdef _USE_ENGLISH
		if (pserialset->m_nValidDay > 0)
			strText.Format (_T("%d day(s)"), pserialset->m_nValidDay);
		else if (pserialset->m_nValidDay < 0)
			strText.Format (_T("%d hour(s)"), -pserialset->m_nValidDay/3600);
		else
			strText = _T("");
#else
		if (pserialset->m_nValidDay > 0)
			strText.Format (_T("%d일"), pserialset->m_nValidDay);
		else if (pserialset->m_nValidDay < 0)
			strText.Format (_T("%d시간"), -pserialset->m_nValidDay/3600);
		else
			strText = _T("");
#endif
		list.SetItemText (nIndex, 7, strText);
	}
}

void CStatusView::AddBank(CBankSet *pBankSet)
{
	CListCtrl& list = GetListCtrl ();
	CServiceManagerDoc* pDoc = GetDocument();

	CBank* pBank = new CBank (pBankSet);
	pDoc->m_listBank.AddTail (pBank);

	CString strText;
	strText.Format (_T("%05d"), pBankSet->m_nID);
	LV_ITEM		item;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = 0;
	item.iSubItem = 0;
	item.pszText = (char*)LPCTSTR(strText);
	item.lParam = (LPARAM)pBank;

	int nIndex = list.InsertItem (&item);

	strText = pBankSet->m_timeReg.Format (_T("%Y/%m/%d"));
	list.SetItemText (nIndex, 1, strText);

	list.SetItemText (nIndex, 2, pBankSet->m_strName);

	list.SetItemText (nIndex, 3, pBankSet->m_strBank);

	strText.Format (_T("%d"), pBankSet->m_nMoney);
	list.SetItemText (nIndex, 4, strText);

#ifdef _USE_ENGLISH
	CString strType;
	switch (pBankSet->m_bType)
	{
	case BANK_TYPE_PRIVATE :	strType = _T("Private"); break;
	case BANK_TYPE_GAMEROOM :	strType = _T("Game Room"); break;
	case BANK_TYPE_PAYLATER :	strType = _T("Limited"); break;
	case BANK_TYPE_PAY :		strType = _T("Time"); break;
	case BANK_TYPE_ETC :		strType = _T("Other"); break;
	}
	list.SetItemText (nIndex, 5, strType);

	CString strProc;
	switch (pBankSet->m_bProcess)
	{
	case BANK_PROC_IN :		strProc = _T("Deposit"); break;
	case BANK_PROC_CONF :	strProc = _T("Confirm"); break;
	case BANK_PROC_STOP :	strProc = _T("Stop"); break;
	case BANK_PROC_ETC :	strProc = _T("Other"); break;
	}
	list.SetItemText (nIndex, 6, strProc);
#else
	CString strType;
	switch (pBankSet->m_bType)
	{
	case BANK_TYPE_PRIVATE :	strType = _T("개인"); break;
	case BANK_TYPE_GAMEROOM :	strType = _T("게임방"); break;
	case BANK_TYPE_PAYLATER :	strType = _T("한정시간제"); break;
	case BANK_TYPE_PAY :		strType = _T("시간제"); break;
	case BANK_TYPE_ETC :		strType = _T("기타"); break;
	}
	list.SetItemText (nIndex, 5, strType);

	CString strProc;
	switch (pBankSet->m_bProcess)
	{
	case BANK_PROC_IN :		strProc = _T("입금"); break;
	case BANK_PROC_CONF :	strProc = _T("확인"); break;
	case BANK_PROC_STOP :	strProc = _T("정지"); break;
	case BANK_PROC_ETC :	strProc = _T("기타"); break;
	}
	list.SetItemText (nIndex, 6, strProc);
#endif

	list.SetItemText (nIndex, 7, pBankSet->m_strOper);

	list.SetItemText (nIndex, 8, pBankSet->m_strComment);
}

void CStatusView::AddBank(CBank *pBank)
{
	CListCtrl& list = GetListCtrl ();
	CServiceManagerDoc* pDoc = GetDocument();

	CString strText;
	strText.Format (_T("%05d"), pBank->m_nID);
	LV_ITEM		item;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = 0;
	item.iSubItem = 0;
	item.pszText = (char*)LPCTSTR(strText);
	item.lParam = (LPARAM)pBank;

	int nIndex = list.InsertItem (&item);

	strText = pBank->m_timeReg.Format (_T("%Y/%m/%d"));
	list.SetItemText (nIndex, 1, strText);

	list.SetItemText (nIndex, 2, pBank->m_strName);

	list.SetItemText (nIndex, 3, pBank->m_strBank);

	strText.Format (_T("%d"), pBank->m_nMoney);
	list.SetItemText (nIndex, 4, strText);

#ifdef _USE_ENGLISH
	CString strType;
	switch (pBank->m_bType)
	{
	case BANK_TYPE_PRIVATE :	strType = _T("Private"); break;
	case BANK_TYPE_GAMEROOM :	strType = _T("Game Room"); break;
	case BANK_TYPE_PAYLATER :	strType = _T("Limited"); break;
	case BANK_TYPE_PAY :		strType = _T("Time"); break;
	case BANK_TYPE_ETC :		strType = _T("Other"); break;
	}
	list.SetItemText (nIndex, 5, strType);

	CString strProc;
	switch (pBank->m_bProcess)
	{
	case BANK_PROC_IN :		strProc = _T("Deposit"); break;
	case BANK_PROC_CONF :	strProc = _T("Comfirm"); break;
	case BANK_PROC_STOP :	strProc = _T("Stop"); break;
	case BANK_PROC_ETC :	strProc = _T("Other"); break;
	}
	list.SetItemText (nIndex, 6, strProc);
#else
	CString strType;
	switch (pBank->m_bType)
	{
	case BANK_TYPE_PRIVATE :	strType = _T("개인"); break;
	case BANK_TYPE_GAMEROOM :	strType = _T("게임방"); break;
	case BANK_TYPE_PAYLATER :	strType = _T("한정시간제"); break;
	case BANK_TYPE_PAY :		strType = _T("시간제"); break;
	case BANK_TYPE_ETC :		strType = _T("기타"); break;
	}
	list.SetItemText (nIndex, 5, strType);

	CString strProc;
	switch (pBank->m_bProcess)
	{
	case BANK_PROC_IN :		strProc = _T("입금"); break;
	case BANK_PROC_CONF :	strProc = _T("확인"); break;
	case BANK_PROC_STOP :	strProc = _T("정지"); break;
	case BANK_PROC_ETC :	strProc = _T("기타"); break;
	}
	list.SetItemText (nIndex, 6, strProc);
#endif

	list.SetItemText (nIndex, 7, pBank->m_strOper);

	list.SetItemText (nIndex, 8, pBank->m_strComment);
}

void CStatusView::UpdateBank(CBankSet *pBankSet)
{
	CListCtrl& list = GetListCtrl ();

	CString strText;
	strText.Format (_T("%05d"), pBankSet->m_nID);

	LVFINDINFO fi;
	fi.flags = LVFI_STRING;
	fi.psz = (char*)LPCTSTR(strText);
	int nIndex = list.FindItem (&fi);
	if (nIndex >= 0)
	{
		strText = pBankSet->m_timeReg.Format (_T("%Y/%m/%d"));
		list.SetItemText (nIndex, 1, strText);

		list.SetItemText (nIndex, 2, pBankSet->m_strName);

		list.SetItemText (nIndex, 3, pBankSet->m_strBank);

		strText.Format (_T("%d"), pBankSet->m_nMoney);
		list.SetItemText (nIndex, 4, strText);

#ifdef _USE_ENGLISH
		CString strType;
		switch (pBankSet->m_bType)
		{
		case BANK_TYPE_PRIVATE :	strType = _T("Private"); break;
		case BANK_TYPE_GAMEROOM :	strType = _T("Game Room"); break;
		case BANK_TYPE_PAYLATER :	strType = _T("Limited"); break;
		case BANK_TYPE_PAY :		strType = _T("Time"); break;
		case BANK_TYPE_ETC :		strType = _T("Other"); break;
		}
		list.SetItemText (nIndex, 5, strType);

		CString strProc;
		switch (pBankSet->m_bProcess)
		{
		case BANK_PROC_IN :		strProc = _T("Deposit"); break;
		case BANK_PROC_CONF :	strProc = _T("Comfirm"); break;
		case BANK_PROC_STOP :	strProc = _T("Stop"); break;
		case BANK_PROC_ETC :	strProc = _T("Other"); break;
		}
		list.SetItemText (nIndex, 6, strProc);
#else
		CString strType;
		switch (pBankSet->m_bType)
		{
		case BANK_TYPE_PRIVATE :	strType = _T("개인"); break;
		case BANK_TYPE_GAMEROOM :	strType = _T("게임방"); break;
		case BANK_TYPE_PAYLATER :	strType = _T("한정시간제"); break;
		case BANK_TYPE_PAY :		strType = _T("시간제"); break;
		case BANK_TYPE_ETC :		strType = _T("기타"); break;
		}
		list.SetItemText (nIndex, 5, strType);

		CString strProc;
		switch (pBankSet->m_bProcess)
		{
		case BANK_PROC_IN :		strProc = _T("입금"); break;
		case BANK_PROC_CONF :	strProc = _T("확인"); break;
		case BANK_PROC_STOP :	strProc = _T("정지"); break;
		case BANK_PROC_ETC :	strProc = _T("기타"); break;
		}
		list.SetItemText (nIndex, 6, strProc);
#endif

		list.SetItemText (nIndex, 7, pBankSet->m_strOper);

		list.SetItemText (nIndex, 8, pBankSet->m_strComment);
	}
}

void CStatusView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CListCtrl& list = GetListCtrl ();
	POSITION pos = list.GetFirstSelectedItemPosition();
	CServiceManagerDoc* pDoc = GetDocument();

	if (pos)
	{
		int nIndex = list.GetNextSelectedItem(pos);
		CString strText, strInterval;
		int nNo;

		strText = list.GetItemText (nIndex, 0);
		switch (m_nView)
		{
		case viewSerial :
			nNo = ::atoi (strText);
			if (!pDoc->UpdateSerial (nNo))
				AfxMessageBox(IDS_MSG_UPDATESERIALFAIL);
			break;
		case viewBank :
			nNo = ::atoi (strText);
			if (!pDoc->UpdateBank (nNo))
				AfxMessageBox(IDS_MSG_UPDATEBANKFAIL);
			break;
		case viewBadID :
			pDoc->ReturnBadID (strText);
			break;
		case viewPay :
			strInterval = list.GetItemText (nIndex, 3);
			strText = list.GetItemText (nIndex, 1);
			pDoc->GetPayDetail( strText, strInterval);

			break;
			
		default :
			break;
		}
	}

	CListView::OnLButtonDblClk(nFlags, point);
}

void CStatusView::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if (pNMListView->iItem == -1)
	{
		CListCtrl& list = GetListCtrl ();
		CServiceManagerDoc* pDoc = GetDocument();

		DWORD dwFlag = 0;
		switch (m_nView)
		{
		case viewSerial :
			dwFlag = VIEW_SERIAL;
			switch (pNMListView->iSubItem)
			{
			case 0 : dwFlag |= SORT_SERIAL_NO; break;
			case 1 : dwFlag |= SORT_SERIAL_TYPE; break;
			case 2 : dwFlag |= SORT_SERIAL_PASSWD; break;
			case 3 : dwFlag |= SORT_SERIAL_START; break;
			case 4 : dwFlag |= SORT_SERIAL_END; break;
			case 5 : dwFlag |= SORT_SERIAL_MAXREG; break;
			case 6 : dwFlag |= SORT_SERIAL_CURREG; break;
			case 7 : dwFlag |= SORT_SERIAL_VALID; break;
			}
			break;
		case viewLog :
			dwFlag = VIEW_LOG;
			switch (pNMListView->iSubItem)
			{
			case 0 : dwFlag |= SORT_LOG_SERVICE; break;
			case 1 : dwFlag |= SORT_LOG_USERID; break;
			case 2 : dwFlag |= SORT_LOG_LOGIN; break;
			case 3 : dwFlag |= SORT_LOG_LOGOUT; break;
			case 4 : dwFlag |= SORT_LOG_TIME; break;
			case 5 : dwFlag |= SORT_LOG_SERIAL; break;
			case 6 : dwFlag |= SORT_LOG_REASON; break;
			case 7 : dwFlag |= SORT_LOG_IPADDR; break;
			}
			break;
		case viewBank :
			dwFlag = VIEW_BANK;
			switch (pNMListView->iSubItem)
			{
			case 0 : dwFlag |= SORT_BANK_NO; break;
			case 1 : dwFlag |= SORT_BANK_DATE; break;
			case 2 : dwFlag |= SORT_BANK_NAME; break;
			case 3 : dwFlag |= SORT_BANK_BANK; break;
			case 4 : dwFlag |= SORT_BANK_MONEY; break;
			case 5 : dwFlag |= SORT_BANK_TYPE; break;
			case 6 : dwFlag |= SORT_BANK_PROC; break;
			case 7 : dwFlag |= SORT_BANK_OPER; break;
			}
			break;
		case viewBadID :
			dwFlag = VIEW_BADID;
			switch (pNMListView->iSubItem)
			{
			case 0 : dwFlag |= SORT_BADID_USERID; break;
			case 1 : dwFlag |= SORT_BADID_FROM; break;
			case 2 : dwFlag |= SORT_BADID_TO; break;
			case 3 : dwFlag |= SORT_BADID_OPER; break;
			}
			break;
		}
		if (dwFlag)
			list.SortItems (CompareFunc, dwFlag);
	}
	
	*pResult = 0;
}

void CStatusView::GetSerialTypeString(int nType, CString &strType)
{
#ifdef _USE_ENGLISH
	switch (nType)
	{
	case SERIAL_PRIVATE_MONTH :
		strType = _T("Private flat-rate system");
		break;
	case SERIAL_GAMEROOM_MONTH :
		strType = _T("Flat-rate game room");
		break;
	case SERIAL_PRIVATE_TIME :
		strType = _T("Private time");
		break;
	case SERIAL_GAMEROOM_TIME :
		strType = _T("Game room time");
		break;
	default :
		strType = _T("Stop of use");
		break;
	}
#else
	switch (nType)
	{
	case SERIAL_PRIVATE_MONTH :
		strType = _T("개인정액");
		break;
	case SERIAL_GAMEROOM_MONTH :
		strType = _T("게임방정액");
		break;
	case SERIAL_PRIVATE_TIME :
		strType = _T("개인시간");
		break;
	case SERIAL_GAMEROOM_TIME :
		strType = _T("게임방시간");
		break;
	default :
		strType = _T("사용중지");
		break;
	}
#endif
}

void CStatusView::AddBadID(CBadIDSet *pSet)
{
	CListCtrl& list = GetListCtrl ();
	CServiceManagerDoc* pDoc = GetDocument();

	CBadID* pBadID = new CBadID (pSet);
	pDoc->m_listBadID.AddTail (pBadID);

	CString strText;
	LV_ITEM		item;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = 0;
	item.iSubItem = 0;
	item.pszText = (char*)LPCTSTR(pSet->m_strUserID);
	item.lParam = (LPARAM)pBadID;

	int nIndex = list.InsertItem (&item);

	strText = pSet->m_timeReg.Format (_T("%Y/%m/%d"));
	list.SetItemText (nIndex, 1, strText);
	strText = pSet->m_timeReturn.Format (_T("%Y/%m/%d"));
	list.SetItemText (nIndex, 2, strText);

	list.SetItemText (nIndex, 3, pSet->m_strOper);
	list.SetItemText (nIndex, 4, pSet->m_strComment);
}

void CStatusView::AddClientLog(CClientLogSet *plogset)
{
	CListCtrl& list = GetListCtrl ();
	CServiceManagerDoc* pDoc = GetDocument();

	CLog* pLog = new CLog (plogset);
	pDoc->m_listLog.AddTail (pLog);

	LV_ITEM		item;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = 0;
	item.iSubItem = 0;
	item.pszText = _T("");
	item.lParam = (LPARAM)pLog;

	int nIndex = list.InsertItem (&item);

	list.SetItemText (nIndex, 1, plogset->m_strUserID);

	CString strText = plogset->m_timeLogin.Format (_T("%Y/%m/%d %H:%M"));
	list.SetItemText (nIndex, 2, strText);

	CTimeSpan timeUse (plogset->m_nUseTime);
	strText = timeUse.Format (_T("%H:%M:%S"));
	list.SetItemText (nIndex, 4, strText);

	CTime timeEnd = plogset->m_timeLogin + timeUse;
	strText = timeEnd.Format (_T("%Y/%m/%d %H:%M"));
	list.SetItemText (nIndex, 3, strText);

	strText.Format (_T("%05d"), plogset->m_wSerial);
	list.SetItemText (nIndex, 5, strText);

	list.SetItemText (nIndex, 6, _T(""));
	list.SetItemText (nIndex, 7, plogset->m_strIPAddr);
}

void CStatusView::AddClient( CClient *pObj, CStringList *plistClient)
{
	CListCtrl& list = GetListCtrl();
	CServiceManagerDoc* pDoc = GetDocument();
	CString strText;
	LV_ITEM item;

	if(!plistClient->IsEmpty())
	{
		strText = pObj->m_strRegNo;
		if(!plistClient->Find(LPCTSTR(strText))) return;
	}

	item.mask = LVIF_TEXT;
	item.iItem = 0;
	item.iSubItem = 0;
	item.pszText = (char*)LPCTSTR(pObj->m_strName);

	int nIndex = list.InsertItem (&item);

	list.SetItemText( nIndex, 1, pObj->m_strRegNo);

	strText.Format("%ld", pObj->m_nTotalTime);
	pDoc->MonyForm(&strText);
#ifdef _USE_ENGLISH
	strText += _T(" minute");
#else
	strText += _T(" 분");
#endif
	list.SetItemText( nIndex, 2, strText);

#ifdef _USE_ENGLISH
	strText.Format("%ld Year %2d Month ~ %ld Year %2d Month",
		           pObj->m_wYear, pObj->m_wMonth - 1, pObj->m_wYear, pObj->m_wMonth);
#else
	strText.Format("%ld년 %2d월 ~ %ld년 %2d월",
		           pObj->m_wYear, pObj->m_wMonth - 1, pObj->m_wYear, pObj->m_wMonth);
#endif
	list.SetItemText( nIndex, 3, strText);

	strText.Format("%ld", (pObj->m_nTotalTime) * 10);
	pDoc->MonyForm(&strText);
#ifdef _USE_ENGLISH
	strText += _T(" Won");
#else
	strText += _T(" 원");
#endif
	list.SetItemText( nIndex, 4, strText);

	strText.Format("%ld", pObj->m_nTotalTime);
	pDoc->MonyForm(&strText);
#ifdef _USE_ENGLISH
	strText += _T(" Won");
#else
	strText += _T(" 원");
#endif
	list.SetItemText( nIndex, 5, strText);
}

void CStatusView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

	if( nChar == 13 ) SendMessage(WM_LBUTTONDBLCLK);
	CListView::OnChar(nChar, nRepCnt, nFlags);
}
