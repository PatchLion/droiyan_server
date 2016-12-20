// Msg.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSG_H__55896525_178D_11D2_A53D_00A0248552AD__INCLUDED_)
#define AFX_MSG_H__55896525_178D_11D2_A53D_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define	DEFAULT_SIZE	8192

class CMsg : public CObject
{
protected:
	BYTE	m_buf[DEFAULT_SIZE];
	BYTE*	m_pHead;	
	BYTE*	m_pData;	
	WORD	m_nRdOff;
	WORD	m_nWrOff;

	void ReadData (void* pData, int n);
	void WriteData (void* pData, int n);

public:
	CMsg();
	CMsg(CMsg& msg);
	CMsg(void* pBuf);

	CMsg& ID( WORD id );
	WORD  ID();

	void* GetBuf ();
	void SetBuf (BYTE* pBuf);
	WORD GetSize ();
	BOOL IsReadAll ();
	void Copy (void* pBuf);
	void Clear () { m_nRdOff = 0; m_nWrOff = 0; }

// Archive Operators
	CMsg&		operator<<( char		arg );
	CMsg&		operator<<( BYTE		arg );
	CMsg&		operator<<( short		arg );
	CMsg&		operator<<( WORD		arg );
	CMsg&		operator<<( int			arg );
	CMsg&		operator<<( DWORD		arg );
	CMsg&		operator<<( LPCTSTR		arg );

	CMsg&		operator>>( char&		arg );
	CMsg&		operator>>( BYTE&		arg );
	CMsg&		operator>>( short&		arg );	
	CMsg&		operator>>( WORD&		arg );	
	CMsg&		operator>>( int&		arg );	
	CMsg&		operator>>( DWORD&		arg );	
	CMsg&		operator>>( CString&	arg );	

	CMsg&		operator=( CMsg&		msg );	
};

#endif // !defined(AFX_MSG_H__55896525_178D_11D2_A53D_00A0248552AD__INCLUDED_)
