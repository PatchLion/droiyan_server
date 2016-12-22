#if !defined(AFX_COUNTVIEW_H__C95DC843_6183_11D2_A57C_00A0248552AD__INCLUDED_)
#define AFX_COUNTVIEW_H__C95DC843_6183_11D2_A57C_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CountView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCountView view

class CCountView : public CScrollView
{
protected:
	CCountView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCountView)

// Attributes
public:
	CServiceManagerDoc* GetDocument();

	void RefreshCount(BOOL bAddList);
// Operations
public:
	CPen m_penCount;
	CPen m_penGrid;
	CPen m_penAxe;
	CFont m_Font;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCountView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCountView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CCountView)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ServiceManagerView.cpp
inline CServiceManagerDoc* CCountView::GetDocument()
   { return (CServiceManagerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COUNTVIEW_H__C95DC843_6183_11D2_A57C_00A0248552AD__INCLUDED_)
