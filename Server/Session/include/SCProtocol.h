///////////////////////////////////////////////////////////////////////////////
// SCProtocol.h - Service Control Protocol Define
//

#ifndef _SCPROTOCOL_H_
#define _SCPROTOCOL_H_

#define SCPROTOCOL				(WORD)(0x8300)
#define SC_INSTALL_REQ			(SCPROTOCOL + 0)
// STRING	ServiceName
// STRING	ModulePath
// STRING	DisplayName
// DWORD	ServerID
// STRING	ServerAddress	
// DWORD	ServerPort
// DWORD	Capacity
// DWORD	Timer
// DWORD	TimeOuts
#define SC_INSTALL_ACK			(SCPROTOCOL + 1)
// DWORD	Result				1 if success, 0 if fail
// STRING	ServiceName
// STRING	DisplayName
// DWORD	ServerID
// STRING	ServerAddress	
// DWORD	ServerPort
// DWORD	Capacity
// DWORD	Timer
// DWORD	TimeOuts

#define SC_REMOVE_REQ			(SCPROTOCOL + 2)
// STRING	ServiceName
#define SC_REMOVE_ACK			(SCPROTOCOL + 3)
// STRING	ServiceName
// DWORD	Result				1 if success, 0 if fail

#define SC_START_REQ			(SCPROTOCOL + 4)
// STRING	ServiceName
#define SC_START_ACK			(SCPROTOCOL + 5)
// STRING	ServiceName
// DWORD	Result				1 if success, 0 if fail

#define SC_STOP_REQ				(SCPROTOCOL + 6)
// STRING	ServiceName
#define SC_STOP_ACK				(SCPROTOCOL + 7)
// STRING	ServiceName
// DWORD	Result				1 if success, 0 if fail

#define SC_PAUSE_REQ			(SCPROTOCOL + 8)
// STRING	ServiceName
#define SC_PAUSE_ACK			(SCPROTOCOL + 9)
// STRING	ServiceName
// DWORD	Result				1 if success, 0 if fail

#define SC_CONTINUE_REQ			(SCPROTOCOL + 10)
// STRING	ServiceName
#define SC_CONTINUE_ACK			(SCPROTOCOL + 11)
// STRING	ServiceName
// DWORD	Result				1 if success, 0 if fail

#define SC_SETINTVALUE_REQ		(SCPROTOCOL + 12)
// STRING	ServiceName
// STRING	FieldName
// DWORD	Value
#define SC_SETINTVALUE_ACK		(SCPROTOCOL + 13)
// STRING	ServiceName
// STRING	FieldName
// DWORD	Result
// DWORD	Value

#define SC_SETSTRINGVALUE_REQ	(SCPROTOCOL + 14)
// STRING	ServiceName
// STRING	FieldName
// DWORD	Value
#define SC_SETSTRINGVALUE_ACK	(SCPROTOCOL + 15)
// STRING	ServiceName
// STRING	FieldName
// DWORD	Result
// STRING	Value

#define SC_GETINTVALUE_REQ		(SCPROTOCOL + 16)
// STRING	ServiceName
// STRING	FieldName
#define SC_GETINTVALUE_ACK		(SCPROTOCOL + 17)
// STRING	ServiceName
// STRING	FieldName
// DWORD	Result
// DWORD	Value

#define SC_GETSTRINGVALUE_REQ	(SCPROTOCOL + 18)
// STRING	ServiceName
// STRING	FieldName
#define SC_GETSTRINGVALUE_ACK	(SCPROTOCOL + 19)
// STRING	ServiceName
// STRING	FieldName
// DWORD	Result
// STRING	Value

#define SC_LIST_REQ				(SCPROTOCOL + 20)
// None
#define SC_LIST_ACK				(SCPROTOCOL + 21)
// DWORD	NumOfServices
// {
// STRING	ServiceName
// STRING	DisplayName
// DWORD	ServerID
// STRING	ServerAddress	
// DWORD	ServerPort
// DWORD	Capacity
// DWORD	Timer
// DWORD	TimeOuts
// DWORD	Status
// } NumOfServices

#define SC_STATUS_REQ			(SCPROTOCOL + 22)
// STRING	ServiceName
#define SC_STATUS_ACK			(SCPROTOCOL + 23)
// STRING	ServiceName
// DWORD	Status

#define SC_LOGIN_REQ			(SCPROTOCOL + 24)
// STRING	GameID
// STRING	Passwd
#define SC_LOGIN_ACK			(SCPROTOCOL + 25)
// DWORD	Result

#endif//_SCPROTOCOL_H_
