// RecoverRate.h: interface for the CRecoverRate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECOVERRATE_H__0A857551_A515_4E70_8FF8_18BE0C8BA5F7__INCLUDED_)
#define AFX_RECOVERRATE_H__0A857551_A515_4E70_8FF8_18BE0C8BA5F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRecoverRate  
{
public:
	short	m_sSid;
	short	m_sHpSpeedupTime;
	BYTE	m_byHpSpeedupLevel;
	short	m_sSpSpeedupTime;
	BYTE	m_bySpSpeedupLevel;
	short	m_sPpSpeedupTime;
	BYTE	m_byPpSpeedupLevel;

	CRecoverRate();
	virtual ~CRecoverRate();

};

#endif // !defined(AFX_RECOVERRATE_H__0A857551_A515_4E70_8FF8_18BE0C8BA5F7__INCLUDED_)
