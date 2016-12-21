#if !defined(AFX_SESSTHREAD_H__E6554034_2834_11D2_A54E_00A0248552AD__INCLUDED_)
#define AFX_SESSTHREAD_H__E6554034_2834_11D2_A54E_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SessThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CSessThread thread

class CSessThread : public CWinThread
{
	DECLARE_DYNCREATE(CSessThread)
protected:
	CSessThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSessThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	virtual BOOL OnIdle(LONG lCount);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSessThread();

	// Generated message map functions
	//{{AFX_MSG(CSessThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SESSTHREAD_H__E6554034_2834_11D2_A54E_00A0248552AD__INCLUDED_)
