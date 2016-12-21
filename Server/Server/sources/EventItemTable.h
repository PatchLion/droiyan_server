// EventItemTable.h: interface for the CEventItemTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTITEMTABLE_H__183DD812_8C74_489D_AA89_A74DCA3300C8__INCLUDED_)
#define AFX_EVENTITEMTABLE_H__183DD812_8C74_489D_AA89_A74DCA3300C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEventItemTable  
{
public:
	CEventItemTable();
	virtual ~CEventItemTable();

	int		m_sSid;
	BYTE	m_tEnd;
	BYTE	m_tType;
	BYTE	m_tGiveFlag;
	TCHAR	m_strSerialNum[EVENT_ITEM_LENGTH + 1];

	BYTE	m_tGiveItem;

	DWORD	m_dwTick;
	long	m_lUsed;

};

#endif // !defined(AFX_EVENTITEMTABLE_H__183DD812_8C74_489D_AA89_A74DCA3300C8__INCLUDED_)
