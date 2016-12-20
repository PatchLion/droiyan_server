// GuildHouse.h: interface for the CGuildHouse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUILDHOUSE_H__A5E786E0_7209_4C84_8A14_039ACFFEF5CD__INCLUDED_)
#define AFX_GUILDHOUSE_H__A5E786E0_7209_4C84_8A14_039ACFFEF5CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGuildHouse  
{
public:
	void UpdateGuildHouse();
	CGuildHouse();
	virtual ~CGuildHouse();

	int		iSid;
	int		iGuild;
	int		iZone;
	int		iPotalX;
	int		iPotalY;

	int		iMarkNpc;
	long	lUsed;
};

#endif // !defined(AFX_GUILDHOUSE_H__A5E786E0_7209_4C84_8A14_039ACFFEF5CD__INCLUDED_)
