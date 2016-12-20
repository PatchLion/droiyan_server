// DNTable.h: interface for the CDNTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DNTABLE_H__1FFF660F_50C7_40CD_8F95_AE8D128E2A64__INCLUDED_)
#define AFX_DNTABLE_H__1FFF660F_50C7_40CD_8F95_AE8D128E2A64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDNTable  
{
public:
	CDNTable();
	virtual ~CDNTable();

	int		m_sIndex;
	int		m_sMinDn;
	int		m_sMaxDn;
};

#endif // !defined(AFX_DNTABLE_H__1FFF660F_50C7_40CD_8F95_AE8D128E2A64__INCLUDED_)
