// Recover.h: interface for the CRecover class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECOVER_H__84E9F8A9_AA80_40E2_B2A1_9F400FE53F29__INCLUDED_)
#define AFX_RECOVER_H__84E9F8A9_AA80_40E2_B2A1_9F400FE53F29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRecover  
{
public:
	short	m_sSid;
	BYTE	m_byHPDivide;
	BYTE	m_bySPDivide;
	BYTE	m_byPPDivide;
	BYTE	m_byTown;

	CRecover();
	virtual ~CRecover();

};

#endif // !defined(AFX_RECOVER_H__84E9F8A9_AA80_40E2_B2A1_9F400FE53F29__INCLUDED_)
