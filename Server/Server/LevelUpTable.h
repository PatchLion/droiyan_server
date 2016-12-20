// LevelUpTable.h: interface for the CLevelUpTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEVELUPTABLE_H__7DEEAB25_1E2A_4E7D_B5D1_C0E386F7A4B8__INCLUDED_)
#define AFX_LEVELUPTABLE_H__7DEEAB25_1E2A_4E7D_B5D1_C0E386F7A4B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLevelUpTable  
{
public:
	long long	m_dwExp;
	short	m_sLevel;
	BYTE	m_tBasicUp;	

	CLevelUpTable();
	~CLevelUpTable();

};

#endif // !defined(AFX_LEVELUPTABLE_H__7DEEAB25_1E2A_4E7D_B5D1_C0E386F7A4B8__INCLUDED_)
