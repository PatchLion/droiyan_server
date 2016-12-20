// VirtualRoom.h: interface for the CVirtualRoom class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIRTUALROOM_H__716F2B61_0DCD_49D9_9279_A58C294C3AE6__INCLUDED_)
#define AFX_VIRTUALROOM_H__716F2B61_0DCD_49D9_9279_A58C294C3AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVirtualRoom  
{
public:
	int		m_iCity;
	short	m_sZone;

	POINT	m_Move[MAX_GUILD_HOUSE_USER];

	CVirtualRoom();
	virtual ~CVirtualRoom();

};

#endif // !defined(AFX_VIRTUALROOM_H__716F2B61_0DCD_49D9_9279_A58C294C3AE6__INCLUDED_)
