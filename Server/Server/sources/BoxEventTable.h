// BoxEventTable.h: interface for the CBoxEventTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOXEVENTTABLE_H__8754E2BF_A4CE_4A2B_8043_5EAB5566F9D2__INCLUDED_)
#define AFX_BOXEVENTTABLE_H__8754E2BF_A4CE_4A2B_8043_5EAB5566F9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBoxEventTable  
{
public:
	short	m_sSid;
	BYTE	m_tType;
	short	m_sIid;
	short	m_sCount;
	CString	m_strText;

	CBoxEventTable();
	virtual ~CBoxEventTable();
};

#endif // !defined(AFX_BOXEVENTTABLE_H__8754E2BF_A4CE_4A2B_8043_5EAB5566F9D2__INCLUDED_)
