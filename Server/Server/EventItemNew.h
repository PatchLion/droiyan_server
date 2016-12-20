// EventItemNew.h: interface for the CEventItemNew class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTITEMNEW_H__FEA39E3A_EC00_48E6_BCA2_17DA11B9AB37__INCLUDED_)
#define AFX_EVENTITEMNEW_H__FEA39E3A_EC00_48E6_BCA2_17DA11B9AB37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEventItemNew  
{
public:
	CEventItemNew();
	virtual ~CEventItemNew();

public:
	short		m_sIndex;
	short		m_sSid;

	BYTE		m_tQuality;

	short		m_sRemain;

	BYTE		m_tSerialExist;

	int			m_iThrowTerm;
	int			m_iThrowRandom;

	short		m_sNextYear;
	short		m_sNextMonth;
	short		m_sNextDay;
	short		m_sNextHour;
	short		m_sNextMin;

	long		m_lGive;
};

#endif // !defined(AFX_EVENTITEMNEW_H__FEA39E3A_EC00_48E6_BCA2_17DA11B9AB37__INCLUDED_)
