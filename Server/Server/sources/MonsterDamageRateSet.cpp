// MonsterDamageRateSet.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "MonsterDamageRateSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonsterDamageRateSet

IMPLEMENT_DYNAMIC(CMonsterDamageRateSet, CRecordset)

CMonsterDamageRateSet::CMonsterDamageRateSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CMonsterDamageRateSet)
	m_F1 = 0;
	m_F2 = 0;
	m_F3 = 0;
	m_F4 = 0;
	m_F5 = 0;
	m_F6 = 0;
	m_F7 = 0;
	m_F8 = 0;
	m_F9 = 0;
	m_F10 = 0;
	m_F11 = 0;
	m_F12 = 0;
	m_F13 = 0;
	m_F14 = 0;
	m_F15 = 0;
	m_F16 = 0;
	m_F17 = 0;
	m_F18 = 0;
	m_F19 = 0;
	m_F20 = 0;
	m_F21 = 0;
	m_F22 = 0;
	m_F23 = 0;
	m_F24 = 0;
	m_F25 = 0;
	m_F26 = 0;
	m_F27 = 0;
	m_F28 = 0;
	m_F29 = 0;
	m_F30 = 0;
	m_F31 = 0;
	m_F32 = 0;
	m_F33 = 0;
	m_F34 = 0;
	m_F35 = 0;
	m_F36 = 0;
	m_F37 = 0;
	m_F38 = 0;
	m_F39 = 0;
	m_F40 = 0;
	m_F41 = 0;
	m_F42 = 0;
	m_F43 = 0;
	m_F44 = 0;
	m_F45 = 0;
	m_F46 = 0;
	m_F47 = 0;
	m_F48 = 0;
	m_F49 = 0;
	m_F50 = 0;
	m_F51 = 0;
	m_F52 = 0;
	m_F53 = 0;
	m_F54 = 0;
	m_F55 = 0;
	m_F56 = 0;
	m_F57 = 0;
	m_F58 = 0;
	m_F59 = 0;
	m_F60 = 0;
	m_F61 = 0;
	m_F62 = 0;
	m_F63 = 0;
	m_F64 = 0;
	m_F65 = 0;
	m_F66 = 0;
	m_F67 = 0;
	m_F68 = 0;
	m_F69 = 0;
	m_F70 = 0;
	m_F71 = 0;
	m_F72 = 0;
	m_F73 = 0;
	m_F74 = 0;
	m_F75 = 0;
	m_F76 = 0;
	m_F77 = 0;
	m_F78 = 0;
	m_F79 = 0;
	m_F80 = 0;
	m_F81 = 0;
	m_F82 = 0;
	m_F83 = 0;
	m_F84 = 0;
	m_F85 = 0;
	m_F86 = 0;
	m_F87 = 0;
	m_F88 = 0;
	m_F89 = 0;
	m_F90 = 0;
	m_F91 = 0;
	m_F92 = 0;
	m_F93 = 0;
	m_F94 = 0;
	m_F95 = 0;
	m_F96 = 0;
	m_F97 = 0;
	m_F98 = 0;
	m_F99 = 0;
	m_F100 = 0;
	m_nFields = 100;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CMonsterDamageRateSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=drgame;UID=z6game;PWD=!zk#9dr");
}

CString CMonsterDamageRateSet::GetDefaultSQL()
{
	return _T("[dbo].[MON_DAMAGE_RATE]");
}

void CMonsterDamageRateSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CMonsterDamageRateSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[F1]"), m_F1);
	RFX_Int(pFX, _T("[F2]"), m_F2);
	RFX_Int(pFX, _T("[F3]"), m_F3);
	RFX_Int(pFX, _T("[F4]"), m_F4);
	RFX_Int(pFX, _T("[F5]"), m_F5);
	RFX_Int(pFX, _T("[F6]"), m_F6);
	RFX_Int(pFX, _T("[F7]"), m_F7);
	RFX_Int(pFX, _T("[F8]"), m_F8);
	RFX_Int(pFX, _T("[F9]"), m_F9);
	RFX_Int(pFX, _T("[F10]"), m_F10);
	RFX_Int(pFX, _T("[F11]"), m_F11);
	RFX_Int(pFX, _T("[F12]"), m_F12);
	RFX_Int(pFX, _T("[F13]"), m_F13);
	RFX_Int(pFX, _T("[F14]"), m_F14);
	RFX_Int(pFX, _T("[F15]"), m_F15);
	RFX_Int(pFX, _T("[F16]"), m_F16);
	RFX_Int(pFX, _T("[F17]"), m_F17);
	RFX_Int(pFX, _T("[F18]"), m_F18);
	RFX_Int(pFX, _T("[F19]"), m_F19);
	RFX_Int(pFX, _T("[F20]"), m_F20);
	RFX_Int(pFX, _T("[F21]"), m_F21);
	RFX_Int(pFX, _T("[F22]"), m_F22);
	RFX_Int(pFX, _T("[F23]"), m_F23);
	RFX_Int(pFX, _T("[F24]"), m_F24);
	RFX_Int(pFX, _T("[F25]"), m_F25);
	RFX_Int(pFX, _T("[F26]"), m_F26);
	RFX_Int(pFX, _T("[F27]"), m_F27);
	RFX_Int(pFX, _T("[F28]"), m_F28);
	RFX_Int(pFX, _T("[F29]"), m_F29);
	RFX_Int(pFX, _T("[F30]"), m_F30);
	RFX_Int(pFX, _T("[F31]"), m_F31);
	RFX_Int(pFX, _T("[F32]"), m_F32);
	RFX_Int(pFX, _T("[F33]"), m_F33);
	RFX_Int(pFX, _T("[F34]"), m_F34);
	RFX_Int(pFX, _T("[F35]"), m_F35);
	RFX_Int(pFX, _T("[F36]"), m_F36);
	RFX_Int(pFX, _T("[F37]"), m_F37);
	RFX_Int(pFX, _T("[F38]"), m_F38);
	RFX_Int(pFX, _T("[F39]"), m_F39);
	RFX_Int(pFX, _T("[F40]"), m_F40);
	RFX_Int(pFX, _T("[F41]"), m_F41);
	RFX_Int(pFX, _T("[F42]"), m_F42);
	RFX_Int(pFX, _T("[F43]"), m_F43);
	RFX_Int(pFX, _T("[F44]"), m_F44);
	RFX_Int(pFX, _T("[F45]"), m_F45);
	RFX_Int(pFX, _T("[F46]"), m_F46);
	RFX_Int(pFX, _T("[F47]"), m_F47);
	RFX_Int(pFX, _T("[F48]"), m_F48);
	RFX_Int(pFX, _T("[F49]"), m_F49);
	RFX_Int(pFX, _T("[F50]"), m_F50);
	RFX_Int(pFX, _T("[F51]"), m_F51);
	RFX_Int(pFX, _T("[F52]"), m_F52);
	RFX_Int(pFX, _T("[F53]"), m_F53);
	RFX_Int(pFX, _T("[F54]"), m_F54);
	RFX_Int(pFX, _T("[F55]"), m_F55);
	RFX_Int(pFX, _T("[F56]"), m_F56);
	RFX_Int(pFX, _T("[F57]"), m_F57);
	RFX_Int(pFX, _T("[F58]"), m_F58);
	RFX_Int(pFX, _T("[F59]"), m_F59);
	RFX_Int(pFX, _T("[F60]"), m_F60);
	RFX_Int(pFX, _T("[F61]"), m_F61);
	RFX_Int(pFX, _T("[F62]"), m_F62);
	RFX_Int(pFX, _T("[F63]"), m_F63);
	RFX_Int(pFX, _T("[F64]"), m_F64);
	RFX_Int(pFX, _T("[F65]"), m_F65);
	RFX_Int(pFX, _T("[F66]"), m_F66);
	RFX_Int(pFX, _T("[F67]"), m_F67);
	RFX_Int(pFX, _T("[F68]"), m_F68);
	RFX_Int(pFX, _T("[F69]"), m_F69);
	RFX_Int(pFX, _T("[F70]"), m_F70);
	RFX_Int(pFX, _T("[F71]"), m_F71);
	RFX_Int(pFX, _T("[F72]"), m_F72);
	RFX_Int(pFX, _T("[F73]"), m_F73);
	RFX_Int(pFX, _T("[F74]"), m_F74);
	RFX_Int(pFX, _T("[F75]"), m_F75);
	RFX_Int(pFX, _T("[F76]"), m_F76);
	RFX_Int(pFX, _T("[F77]"), m_F77);
	RFX_Int(pFX, _T("[F78]"), m_F78);
	RFX_Int(pFX, _T("[F79]"), m_F79);
	RFX_Int(pFX, _T("[F80]"), m_F80);
	RFX_Int(pFX, _T("[F81]"), m_F81);
	RFX_Int(pFX, _T("[F82]"), m_F82);
	RFX_Int(pFX, _T("[F83]"), m_F83);
	RFX_Int(pFX, _T("[F84]"), m_F84);
	RFX_Int(pFX, _T("[F85]"), m_F85);
	RFX_Int(pFX, _T("[F86]"), m_F86);
	RFX_Int(pFX, _T("[F87]"), m_F87);
	RFX_Int(pFX, _T("[F88]"), m_F88);
	RFX_Int(pFX, _T("[F89]"), m_F89);
	RFX_Int(pFX, _T("[F90]"), m_F90);
	RFX_Int(pFX, _T("[F91]"), m_F91);
	RFX_Int(pFX, _T("[F92]"), m_F92);
	RFX_Int(pFX, _T("[F93]"), m_F93);
	RFX_Int(pFX, _T("[F94]"), m_F94);
	RFX_Int(pFX, _T("[F95]"), m_F95);
	RFX_Int(pFX, _T("[F96]"), m_F96);
	RFX_Int(pFX, _T("[F97]"), m_F97);
	RFX_Int(pFX, _T("[F98]"), m_F98);
	RFX_Int(pFX, _T("[F99]"), m_F99);
	RFX_Int(pFX, _T("[F100]"), m_F100);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CMonsterDamageRateSet diagnostics

#ifdef _DEBUG
void CMonsterDamageRateSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CMonsterDamageRateSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
