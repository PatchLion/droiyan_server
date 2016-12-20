// ValItemTable.h: interface for the CValItemTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VALITEMTABLE_H__599082F5_F9E2_43A9_952E_C1C419C4599B__INCLUDED_)
#define AFX_VALITEMTABLE_H__599082F5_F9E2_43A9_952E_C1C419C4599B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CValItemTable  
{
public:
	CValItemTable();
	virtual ~CValItemTable();

	int		m_sSid;
	int		m_sValItem01;
	BYTE	m_tPersentVal01;
	int		m_sValItem02;
	BYTE	m_tPersentVal02;
	int		m_sValItem03;
	BYTE	m_tPersentVal03;
	int		m_sValItem04;
	BYTE	m_tPersentVal04;
	int		m_sValItem05;
	BYTE	m_tPersentVal05;
	int		m_sValItem06;
	BYTE	m_tPersentVal06;
};

#endif // !defined(AFX_VALITEMTABLE_H__599082F5_F9E2_43A9_952E_C1C419C4599B__INCLUDED_)
