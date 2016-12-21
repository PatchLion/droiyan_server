// NpcChat.h: interface for the CNpcChat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPCCHAT_H__2033A1CA_AB41_483C_8F44_E2AC297E091C__INCLUDED_)
#define AFX_NPCCHAT_H__2033A1CA_AB41_483C_8F44_E2AC297E091C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_LENGTH		1024

class CNpcChat  
{
public:
	CNpcChat();
	virtual ~CNpcChat();

	int		m_sCid;
	int		m_sSize;
//	CByteArray m_strTalk;
//	CString m_strTalk;
	TCHAR	*m_strTalk;//[MAX_LENGTH];
};

#endif // !defined(AFX_NPCCHAT_H__2033A1CA_AB41_483C_8F44_E2AC297E091C__INCLUDED_)
