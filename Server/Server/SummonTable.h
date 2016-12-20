// SummonTable.h: interface for the CSummonTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUMMONTABLE_H__DE5E7D37_DF4E_4389_A24D_6F7654DE742E__INCLUDED_)
#define AFX_SUMMONTABLE_H__DE5E7D37_DF4E_4389_A24D_6F7654DE742E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSummonTable  
{
public:
	CSummonTable();
	virtual ~CSummonTable();

	short	m_sSid;
	CString m_strName;
};

#endif // !defined(AFX_SUMMONTABLE_H__DE5E7D37_DF4E_4389_A24D_6F7654DE742E__INCLUDED_)
