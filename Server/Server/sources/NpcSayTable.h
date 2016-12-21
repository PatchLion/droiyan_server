// NpcSayTable.h: interface for the CNpcSayTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPCSAYTABLE_H__3894E9FC_C509_4B70_87F5_6122AA54A925__INCLUDED_)
#define AFX_NPCSAYTABLE_H__3894E9FC_C509_4B70_87F5_6122AA54A925__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNpcSayTable  
{
public:
	CNpcSayTable();
	virtual ~CNpcSayTable();

	int		iSid;
	CString Say;	
};

#endif // !defined(AFX_NPCSAYTABLE_H__3894E9FC_C509_4B70_87F5_6122AA54A925__INCLUDED_)
