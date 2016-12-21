// MyDB.h: interface for the CMyDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDB_H__15818A22_88EA_4A91_8F64_8669DF55DEB6__INCLUDED_)
#define AFX_MYDB_H__15818A22_88EA_4A91_8F64_8669DF55DEB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_DB_USE_TIME		2000

typedef struct _DB_CONNECTION
{
	CDatabase		db;
	BOOL			bConnect;
	LONG			lRef;
	int				iCount;
	DWORD			dwGetDBTime;

//	DWORD			dwUseTime;
} DB_CONNECTION;

typedef CTypedPtrArray <CPtrArray, DB_CONNECTION*> DBArray;

class CMyDB  
{
public:
	void ReleaseDB(int index);
	CDatabase* GetDB(int &index);
	BOOL DBConnect(LPCTSTR strConnect);
	void Init(int num);

	DBArray		m_arDB;
	int			m_iTotalConnection;
	CString		m_strConnect;

	CMyDB();
	virtual ~CMyDB();
};

#endif // !defined(AFX_MYDB_H__15818A22_88EA_4A91_8F64_8669DF55DEB6__INCLUDED_)
