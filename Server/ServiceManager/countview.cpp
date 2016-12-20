// CountView.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ServiceManagerDoc.h"
#include "CountView.h"
#include "Service.h"
#include "Session.h"
#include "UserManager.h"
#include "UserCountSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _ENGLISH
#define FONT_NAME	_T("Arial")
#else
#define FONT_NAME	_T("±¼¸²Ã¼")
#endif

/////////////////////////////////////////////////////////////////////////////
// CCountView

IMPLEMENT_DYNCREATE(CCountView, CScrollView)

CCountView::CCountView()
{
	m_penGrid.CreatePen (PS_DOT, 0, RGB (0, 0, 0));
	m_penAxe.CreatePen (PS_SOLID, 0, RGB (0, 0, 0));
	m_penCount.CreatePen (PS_SOLID, 0, RGB (0, 0, 255));
	m_Font.CreateFont(-8, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FONT_NAME);
}

CCountView::~CCountView()
{
	m_penGrid.DeleteObject();
	m_penAxe.DeleteObject();
	m_penCount.DeleteObject();
	m_Font.DeleteObject();
}


BEGIN_MESSAGE_MAP(CCountView, CScrollView)
	//{{AFX_MSG_MAP(CCountView)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCountView drawing

void CCountView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CServiceManagerDoc* pDoc = GetDocument();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = pDoc->m_nCountRange * 60;
	sizeTotal.cy = 110;
	SetScaleToFitSize(sizeTotal);

	SetTimer (1, 30000, NULL);
}

void CCountView::OnDraw(CDC* pDC)
{
	CServiceManagerDoc* pDoc = GetDocument();

	pDC->SetBkMode (TRANSPARENT);
	int nRange = pDoc->m_nCountRange * 60;
	pDC->FillSolidRect (CRect (0, 0, nRange, 120), RGB (192, 192, 192));

	CObList* pList;
	CSession* pSession;
	if (pDoc->m_pSelItem &&
		pDoc->m_pSelItem->m_nType == CSelItem::selService &&
		((CService*)pDoc->m_pSelItem->m_pObject)->m_nType == CService::typeSM)
	{
		pSession = (CSession*)pDoc->m_pSelItem->m_pObject;
		pList = &pSession->m_listCount;
	}
	else
	{
		pSession = NULL;
		pList = &pDoc->m_listCount;
	}

	if (pList->IsEmpty ())
		return;

	CCount* pCountTail = (CCount*)pList->RemoveTail ();
	CString strCount;
	if (pSession)
		strCount.FormatMessage (IDS_FMT_COUNTSESSION, pSession->m_strName, pCountTail->m_nNum);
	else
#ifdef _USE_ENGLISH
		strCount.FormatMessage (IDS_FMT_COUNTSESSION, _T("Total"), pCountTail->m_nNum);
#else
		strCount.FormatMessage (IDS_FMT_COUNTSESSION, _T("ÀüÃ¼"), pCountTail->m_nNum);
#endif

	CFont *old_font = pDC->SelectObject(&m_Font);

	pDC->TextOut (4, 2, strCount);

	CPen* pPenSave = pDC->SelectObject (&m_penGrid);
	for (int i = 0; i < 100; i += 10)
	{
		pDC->MoveTo (0, i);
		pDC->LineTo (nRange, i);
	}
	pDC->SelectObject (&m_penAxe);
	pDC->MoveTo (nRange, 100);
	pDC->LineTo (0, 100);

	pDC->SetTextAlign (TA_RIGHT);
	strCount.Format (_T("%d"), pDoc->m_nCountScale);
	pDC->TextOut (nRange, 0, strCount);
	strCount.Format (_T("%d"), pDoc->m_nCountScale / 2);
	pDC->TextOut (nRange, 45, strCount);
	pDC->SetTextAlign (TA_BOTTOM | TA_RIGHT);
	pDC->TextOut (nRange, 100, _T("0"));

	CTime timeStart = pCountTail->m_time;

	pDC->SelectObject (&m_penGrid);
	pDC->SetTextAlign (TA_CENTER);
	int nOffset = (timeStart.GetMinute () % 10) * 60;
	while (nOffset < nRange)
	{
		CTime timeGrid = timeStart - CTimeSpan (0, 0, 0, nOffset);
		CString strTime = timeGrid.Format (_T("%H:%M"));
		pDC->TextOut (nOffset, 100, strTime);
		pDC->MoveTo (nOffset, 0);
		pDC->LineTo (nOffset, 100);

		nOffset += nRange / 6;
	}

	pDC->SelectObject (&m_penCount);
	pDC->MoveTo (0, 100 - (pCountTail->m_nNum * 100 / pDoc->m_nCountScale));
	POSITION pos = pList->GetTailPosition ();
	while (pos)
	{
		CCount* pCount = (CCount*)pList->GetPrev (pos);
		CTimeSpan timeSpan = timeStart - pCount->m_time;
		pDC->LineTo (timeSpan.GetTotalSeconds (), 
			100 - (pCount->m_nNum * 100 / pDoc->m_nCountScale));
	}

	pList->AddTail (pCountTail);

	pDC->SelectObject (pPenSave);
	pDC->SelectObject(old_font);
}

void CCountView::RefreshCount(BOOL bAddList)
{
}
/////////////////////////////////////////////////////////////////////////////
// CCountView diagnostics

#ifdef _DEBUG
void CCountView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CCountView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CServiceManagerDoc* CCountView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CServiceManagerDoc)));
	return (CServiceManagerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCountView message handlers

void CCountView::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == 1)
	{
		CUserCountSet countset (&g_db);
		if (countset.Open ())
		{
			CServiceManagerDoc* pDoc = GetDocument();
			int nTotal = 0;
			while (!countset.IsEOF ())
			{
				CSession* pSession = pDoc->FindSession (countset.m_nServiceID);
				if (pSession)
				{
					CCount* pCount = new CCount (countset.m_nNumUser);
					while (!pSession->m_listCount.IsEmpty ())
					{
						CCount* pCountFirst = (CCount*)pSession->m_listCount.GetHead ();
						CTimeSpan timeSpan = pCount->m_time - pCountFirst->m_time;
						if (timeSpan.GetTotalMinutes () >= pDoc->m_nCountRange)
							delete pSession->m_listCount.RemoveHead ();
						else
							break;
					}
					pSession->m_listCount.AddTail (pCount);
					nTotal += countset.m_nNumUser;
				}
				countset.MoveNext ();
			}
			
			CCount *pCountTotal = new CCount (nTotal);
			while (!pDoc->m_listCount.IsEmpty ())
			{
				CCount* pCountFirst = (CCount*)pDoc->m_listCount.GetHead ();
				CTimeSpan timeSpan = pCountTotal->m_time - pCountFirst->m_time;
				if (timeSpan.GetTotalMinutes () >= pDoc->m_nCountRange)
					delete pDoc->m_listCount.RemoveHead ();
				else
					break;
			}
			if (pCountTotal->m_nNum > pDoc->m_nCountScale * 7 / 10)
				pDoc->m_nCountScale *= 2;
			else if (pCountTotal->m_nNum < pDoc->m_nCountScale * 3 / 10)
				pDoc->m_nCountScale /= 2;
			
			CString strCount;
			strCount.FormatMessage (IDS_FMT_COUNT, nTotal);
			CStatusBar* pBar = (CStatusBar*)(((CFrameWnd*)AfxGetMainWnd ())->GetMessageBar ());
			if (pBar)
				pBar->SetPaneText (4, strCount);
			pDoc->m_listCount.AddTail (pCountTotal);
			pDoc->UpdateAllViews(this, UPDATE_COUNT);
		}
	}
	CScrollView::OnTimer(nIDEvent);
}

void CCountView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (lHint == UPDATE_COUNT)
	{
		Invalidate();
		UpdateWindow();
	}
}
