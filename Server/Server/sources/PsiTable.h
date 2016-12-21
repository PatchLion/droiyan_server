// PsiTable.h: interface for the CPsiTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PSITABLE_H__89EA456F_CFAC_4163_BBA4_38FC183C0CE5__INCLUDED_)
#define AFX_PSITABLE_H__89EA456F_CFAC_4163_BBA4_38FC183C0CE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPsiTable  
{
public:
	short	m_sSid;
	short	m_sPid;
	CString	m_strName;
	DWORD	m_iNeedDN;
	DWORD	m_iNeedXP;
	short	m_sDelayTime;
	short	m_sHoldTime;
	BYTE	m_tClass;
	BYTE	m_tNeedLevel;
	BYTE	m_tNeedPP;
	BYTE	m_tRange;
	BYTE	m_tRegi;
	BYTE	m_tTarget;
	CString	m_strText;
	short	m_sBasic;
	short	m_sLevelUp;

	CPsiTable();
	~CPsiTable();
};

#endif // !defined(AFX_PSITABLE_H__89EA456F_CFAC_4163_BBA4_38FC183C0CE5__INCLUDED_)
