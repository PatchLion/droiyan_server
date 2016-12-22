// Session.h: interface for the CSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SESSION_H__5589653A_178D_11D2_A53D_00A0248552AD__INCLUDED_)
#define AFX_SESSION_H__5589653A_178D_11D2_A53D_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSession : public CObject  
{
public:
	int	m_nServID;

	CSession(int nServID)
	{
		m_nServID = nServID;
	}
};

#endif // !defined(AFX_SESSION_H__5589653A_178D_11D2_A53D_00A0248552AD__INCLUDED_)
