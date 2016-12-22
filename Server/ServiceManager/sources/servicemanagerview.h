// ServiceManagerView.h : interface of the CServiceManagerView class
//
/////////////////////////////////////////////////////////////////////////////
 
#if !defined(AFX_SERVICEMANAGERVIEW_H__E1714800_20EA_11D2_A546_00A0248552AD__INCLUDED_)
#define AFX_SERVICEMANAGERVIEW_H__E1714800_20EA_11D2_A546_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Server.h"
#include "Service.h"

class CServiceManagerView : public CTreeView
{
protected: // create from serialization only
	CServiceManagerView();
	DECLARE_DYNCREATE(CServiceManagerView)

// Attributes
public:
	enum 
	{ 
		selNone, 
		selServerRoot, selServiceRoot, selVersionRoot, selGameRoot, selSessionRoot,
		selServer, selService, selFolder,
		selVersion, selNumFile, selFile
	};
	CServiceManagerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServiceManagerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	HTREEITEM FindFile (HTREEITEM hParent, CString fileName);
	HTREEITEM m_hVersion;
	virtual ~CServiceManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	HTREEITEM InsertItem (LPCTSTR lpszText, int nImage1, int nImage2,
		HTREEITEM hParent = NULL, int nType = selNone, CObject* pObject = NULL);
	CSelItem* GetItemData (HTREEITEM hItem);

	HTREEITEM m_hFolder;
	HTREEITEM FindFile (HTREEITEM hParent, CFileInfo* pInfo);
	HTREEITEM FindServiceItem (HTREEITEM hParent, CService* pService);
	HTREEITEM FindServerItem (CServer* pServer);
	void OnUpdateFile (CFileInfo* pInfo);
	void OnAddFile (CFileInfo* pInfo);
	void OnDeleteFile (CFileInfo* pInfo);
	void OnServiceConfig (CService* pService);
	void OnServiceStatus (CService* pService);
	void OnRemoveService (CService* pService);
	void OnInstallService (CService* pService);
	void OnServerStatus (CServer* pServer);
	void OnDelServer (CServer* pServer);
	void OnAddServer (CServer* pServer);
	void OnUpdateAll ();
	HTREEITEM m_hCurrentVer;
	HTREEITEM m_hNumFile;
	HTREEITEM m_hServer;
	HTREEITEM m_hService;
	HTREEITEM m_hSession;
	HTREEITEM m_hGame;
	//{{AFX_MSG(CServiceManagerView)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DrawNumber( int, int, CString&, CDC*);
	long GetLabelPageNum();
	void PrintLabel( CDC* pDC, CPrintInfo* pInfo);
	void PrintTax( CDC*);
	void DrawDetail( CDC*);
	CClient *m_pClient;

	void DrawBillForm( CDC*);
	void DrawTitle( CDC*);
	long GetListPageNum();
	void DrawItem( CDC*);
	CListCtrl *m_plistData;
	BOOL PrintList( UINT, CDC*, CListCtrl*);
	CListCtrl& GetList();
};

#ifndef _DEBUG  // debug version in ServiceManagerView.cpp
inline CServiceManagerDoc* CServiceManagerView::GetDocument()
   { return (CServiceManagerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVICEMANAGERVIEW_H__E1714800_20EA_11D2_A546_00A0248552AD__INCLUDED_)
