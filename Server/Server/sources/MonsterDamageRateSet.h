#if !defined(AFX_MONSTERDAMAGERATESET_H__3A0EF036_28A1_4BC8_A0F0_5F871FA1905F__INCLUDED_)
#define AFX_MONSTERDAMAGERATESET_H__3A0EF036_28A1_4BC8_A0F0_5F871FA1905F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MonsterDamageRateSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMonsterDamageRateSet recordset

class CMonsterDamageRateSet : public CRecordset
{
public:
	CMonsterDamageRateSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CMonsterDamageRateSet)

// Field/Param Data
	//{{AFX_FIELD(CMonsterDamageRateSet, CRecordset)
	int		m_F1;
	int		m_F2;
	int		m_F3;
	int		m_F4;
	int		m_F5;
	int		m_F6;
	int		m_F7;
	int		m_F8;
	int		m_F9;
	int		m_F10;
	int		m_F11;
	int		m_F12;
	int		m_F13;
	int		m_F14;
	int		m_F15;
	int		m_F16;
	int		m_F17;
	int		m_F18;
	int		m_F19;
	int		m_F20;
	int		m_F21;
	int		m_F22;
	int		m_F23;
	int		m_F24;
	int		m_F25;
	int		m_F26;
	int		m_F27;
	int		m_F28;
	int		m_F29;
	int		m_F30;
	int		m_F31;
	int		m_F32;
	int		m_F33;
	int		m_F34;
	int		m_F35;
	int		m_F36;
	int		m_F37;
	int		m_F38;
	int		m_F39;
	int		m_F40;
	int		m_F41;
	int		m_F42;
	int		m_F43;
	int		m_F44;
	int		m_F45;
	int		m_F46;
	int		m_F47;
	int		m_F48;
	int		m_F49;
	int		m_F50;
	int		m_F51;
	int		m_F52;
	int		m_F53;
	int		m_F54;
	int		m_F55;
	int		m_F56;
	int		m_F57;
	int		m_F58;
	int		m_F59;
	int		m_F60;
	int		m_F61;
	int		m_F62;
	int		m_F63;
	int		m_F64;
	int		m_F65;
	int		m_F66;
	int		m_F67;
	int		m_F68;
	int		m_F69;
	int		m_F70;
	int		m_F71;
	int		m_F72;
	int		m_F73;
	int		m_F74;
	int		m_F75;
	int		m_F76;
	int		m_F77;
	int		m_F78;
	int		m_F79;
	int		m_F80;
	int		m_F81;
	int		m_F82;
	int		m_F83;
	int		m_F84;
	int		m_F85;
	int		m_F86;
	int		m_F87;
	int		m_F88;
	int		m_F89;
	int		m_F90;
	int		m_F91;
	int		m_F92;
	int		m_F93;
	int		m_F94;
	int		m_F95;
	int		m_F96;
	int		m_F97;
	int		m_F98;
	int		m_F99;
	int		m_F100;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonsterDamageRateSet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONSTERDAMAGERATESET_H__3A0EF036_28A1_4BC8_A0F0_5F871FA1905F__INCLUDED_)
