#if !defined ___STATUSVIEW_H
#define ___STATUSVIEW_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StatusView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatusView view

class CSerialSet;
class CLogSet;
class CBankSet;
class CBadIDSet;
class CClientLogSet;
class CClientPaySet;

class CClientPay;

class CStatusView : public CListView
{
protected:
	CStatusView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CStatusView)

// Attributes
public:
	enum { viewLog, viewSerial, viewBank, viewBadID, viewPay, viewNone};
	int m_nView;
	CServiceManagerDoc* GetDocument();

// Operations
public:
	void AddClientLog (CClientLogSet* pSet);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CStatusView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	void AddClient( CClient*, CStringList*);
	void GetSerialTypeString (int nType, CString& strType);
	void UpdateBank (CBankSet* pBankSet);
	void UpdateSerial (CSerialSet* serialset);
	void AddBank (CBankSet* pBankSet);
	void AddSerial (CSerialSet* serialset);
	void AddLog (CLogSet* plogset);
	void AddBank (CBank* pBank);
	void AddSerial (CSerial* pSerial);
	void AddLog (CLog* pLog);
	void AddBadID (CBadIDSet* pSet);
	void AddPay (CClientPaySet* pSet);

	//{{AFX_MSG(CStatusView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ServiceManagerView.cpp
inline CServiceManagerDoc* CStatusView::GetDocument()
   { return (CServiceManagerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined ___STATUSVIEW_H