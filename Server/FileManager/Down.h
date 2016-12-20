// Down.h: interface for the CDown class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOWN_H__352C5473_1406_11D2_A53B_00A0248552AD__INCLUDED_)
#define AFX_DOWN_H__352C5473_1406_11D2_A53B_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define DEF_DOWN_SIZE	1024

class CDown : public CObject  
{
protected:
	CSessDesc*	m_pDes;	
	BYTE		m_buf[DEF_DOWN_SIZE];
	
public:
	DWORD		m_dwCurrentDown;
	DWORD		m_dwCurrentSend;

	BOOL IsDownState ();
	CFileInfo* GetFileInfo ();
	int GetNumDownFile();
	CDown();
	virtual ~CDown();

	void AddFileInfo (CFileInfo* pInfo);
	BOOL ProcDown();
	BOOL StartDown ();
	void Reset();
	DWORD GetLengthTotalFile ();
	void SetDesc (CSessDesc* pDes);
};

#endif // !defined(AFX_DOWN_H__352C5473_1406_11D2_A53B_00A0248552AD__INCLUDED_)
