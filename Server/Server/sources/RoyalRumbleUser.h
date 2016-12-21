// RoyalRumbleUser.h: interface for the CRoyalRumbleUser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROYALRUMBLEUSER_H__02F26B5D_9D33_4DC6_969D_D976DB2C9363__INCLUDED_)
#define AFX_ROYALRUMBLEUSER_H__02F26B5D_9D33_4DC6_969D_D976DB2C9363__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRoyalRumbleUser  
{
public:
	CRoyalRumbleUser();
	virtual ~CRoyalRumbleUser();

public:
	int				m_iUID;
	char			m_strUserID[CHAR_NAME_LENGTH+1];
	BOOL			m_bLive;
};

#endif // !defined(AFX_ROYALRUMBLEUSER_H__02F26B5D_9D33_4DC6_969D_D976DB2C9363__INCLUDED_)
