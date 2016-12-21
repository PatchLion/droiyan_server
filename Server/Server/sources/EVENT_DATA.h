// EVENT_DATA.h: interface for the EVENT_DATA class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENT_DATA_H__7514FC26_511B_11D3_BE41_00105A6B97E2__INCLUDED_)
#define AFX_EVENT_DATA_H__7514FC26_511B_11D3_BE41_00105A6B97E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class LOGIC;
class EXEC;
class LOGIC_ELSE;

typedef CTypedPtrArray <CPtrArray, LOGIC*> LogicArray;
typedef CTypedPtrArray <CPtrArray, EXEC*> ExecArray;
typedef CTypedPtrArray <CPtrArray, LOGIC_ELSE*> LogicElseArray;

class EVENT_DATA  
{
public:
	int m_EventNum;
	LogicArray m_arLogic;
	ExecArray m_arExec;
	LogicElseArray m_arLogicElse;

	EVENT_DATA();
	virtual ~EVENT_DATA();

};

#endif // !defined(AFX_EVENT_DATA_H__7514FC26_511B_11D3_BE41_00105A6B97E2__INCLUDED_)
