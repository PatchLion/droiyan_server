// RemodelingTable.h: interface for the CRemodelingTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REMODELINGTABLE_H__3C8B8550_81F4_46C3_87F6_1CA1ACB31020__INCLUDED_)
#define AFX_REMODELINGTABLE_H__3C8B8550_81F4_46C3_87F6_1CA1ACB31020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRemodelingTable  
{
public:
	CRemodelingTable();
	virtual ~CRemodelingTable();

	int		m_sRid;
	int		m_sSid;
	BYTE	m_tWearInfo;
	BYTE	m_tNeedClass;
	int		m_sPlan;
	BYTE	m_tRandom1;
	BYTE	m_tRandom2;
	BYTE	m_tReplace;
};

#endif // !defined(AFX_REMODELINGTABLE_H__3C8B8550_81F4_46C3_87F6_1CA1ACB31020__INCLUDED_)
