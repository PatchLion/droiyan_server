// GuildUser.h: interface for the CGuildUser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUILDUSER_H__1623FC3A_0913_46E0_B891_57E63EAD8845__INCLUDED_)
#define AFX_GUILDUSER_H__1623FC3A_0913_46E0_B891_57E63EAD8845__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGuildUser  
{
public:
	char	m_strUserId[CHAR_NAME_LENGTH + 1];
	long	m_lSid;						// 길드인덱스
	long	m_lUsed;					// 여기에 길드원이 셋팅되어있다.

	CGuildUser();
	virtual ~CGuildUser();
};

#endif // !defined(AFX_GUILDUSER_H__1623FC3A_0913_46E0_B891_57E63EAD8845__INCLUDED_)
