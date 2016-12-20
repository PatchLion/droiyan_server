///////////////////////////////////////////////////////////////////////////////
// SMProtocol.h - Session Manager Protocol Define
//

#ifndef _UMPROTOCOL_H_
#define _UMPROTOCOL_H_

#define UMPROTOCOL				(WORD)(0x8200)

#define UM_CONNECT_REQ			(UMPROTOCOL + 0)	// Connect Req.
// DWORD	ID			User Identifier
// STRING	IPAddress	Client Socket Name

#define UM_LOGIN_REQ			(UMPROTOCOL + 2)	// Login Req.
// DWORD	ID			User Identifier
// STRING	UserID		User ID
// STRING	Passwd		Password
#define UM_LOGIN_ACK			(UMPROTOCOL + 3)	// Login Ack.
// DWORD	ID			User Identifier
// BYTE		LoginResult	Password Check Result Code
// BYTE		SNResult	Serial Number Check Result Code

// Password Check Result Code
#define LR_USER_VALID	(BYTE)0
#define LR_USER_UNREG	(BYTE)1
#define LR_USER_INVALID	(BYTE)2
#define LR_USER_DUP			(BYTE)3

// SN Check Result Code
#define LR_SN_VALID		(BYTE)0
#define LR_SN_NOSN		(BYTE)1
#define LR_SN_UNREG		(BYTE)2
#define LR_SN_INVALID	(BYTE)3
#define LR_SN_OUTOFDATE	(BYTE)4

/////////////////////////////////////////////////////////////
// EVERLAND LOGIN RESULTS
// added by amnesia
// Login Result (UM_EVERLOGIN)
#define LIR_SUCCESS			(BYTE)0
#define LIR_INVALIDID		(BYTE)1
#define LIR_INVALIDPASS		(BYTE)2
#define LIR_USERDUP			(BYTE)3
#define LIR_NOACCOUNT		(BYTE)4
#define LIR_INVALIDACCOUNT	(BYTE)5
#define LIR_UNKNOWNERR		(BYTE)6
// Logout Result (UM_EVERLOGOUT)
#define LOR_SUCCESS			(BYTE)0
#define LOR_NOTLOGIN		(BYTE)1
// CpLogin Result (UM_CPLOGIN)
#define CLIR_SUCCESS		(BYTE)0
#define CLIR_NAVIGATOR		(BYTE)1
#define CLIR_NOACCOUNT		(BYTE)2
#define CLIR_INVALIDACCOUNT	(BYTE)3
// CpLogout Result (UM_CPLOGOUT)
#define CLOR_SUCCESS		(BYTE)0
#define CLOR_NOTLOGIN		(BYTE)1
// EVERLAND LOGIN RESULTS
/////////////////////////////////////////////////////////////

#define UM_REGUSER_REQ			(UMPROTOCOL + 4)
// DWORD	ID			User Identifier
// STRING	UserID		User ID
// STRING	Passwd		Password
// STRING	Name		Name
// STRING	SocNo		Social Number
// STRING	Address		Address
// STRING	TelNo		Telephone Number
// STRING	Email		Email Address
// BYTE		RegSN		Serial No. Register
// STRING	Serial1		Serial String 1 (Optional)
// STRING	Serial2		Serial String 2 (Optional)
// STRING	Passwd		Serial No Passwd (Optional)
#define UM_REGUSER_ACK			(UMPROTOCOL + 5)
// DWORD	ID			User Identifier
// BYTE		Result		1 on success, or 0

#define UM_GETINFO_REQ			(UMPROTOCOL + 6)
// DWORD	ID			User Identifier
// STRING	UserID
// STRING	Passwd
#define UM_GETINFO_ACK			(UMPROTOCOL + 7)
// DWORD	ID			User Identifier
// STRING	UserID		User ID
// STRING	Passwd		Password
// STRING	Name		Name
// STRING	SocNo		Social Number
// STRING	Address		Address
// STRING	TelNo		Telephone Number
// STRING	Email		Email Address

#define UM_SETINFO_REQ			(UMPROTOCOL + 8)
// DWORD	ID			User Identifier
// STRING	Passwd		Password
// STRING	Name		Name
// STRING	SocNo		Social Number
// STRING	Address		Address
// STRING	TelNo		Telephone Number
// STRING	Email		Email Address
// BYTE		RegSN		Serial No. Register
// STRING	Serial1		Serial String 1 (Optional)
// STRING	Serial2		Serial String 2 (Optional)
// STRING	Passwd		Serial No Passwd (Optional)
#define UM_SETINFO_ACK			(UMPROTOCOL + 9)
// DWORD	ID			User Identifier
// BYTE		Result		1 on success, or 0

#define UM_REGSN_REQ			(UMPROTOCOL + 10)
// DWORD	ID			User Identifier
// STRING	Passwd		Serial Number Password
#define UM_REGSN_ACK			(UMPROTOCOL + 11)
// DWORD	ID			User Identifier
// BYTE		Result		1 on success, or 0

#define UM_DISCONNECT_REQ		(UMPROTOCOL + 13)
// DWORD	ID			User Identifier
// BYTE		Reason		Reason for disconnect

#define DR_NORMAL		(BYTE)0		// Normal Terminate
#define DR_CLIENT		(BYTE)1		// Client Connection Closed
#define DR_TIMEOUT		(BYTE)2		// Time out
#define DR_DUPLICATE	(BYTE)3		// Duplicated
#define DR_LINK			(BYTE)4		// Game server link failed
#define DR_CANCEL		(BYTE)5		// Canceld by manager
#define DR_SESSION		(BYTE)6		// Session Close

#define UM_DISCONNECT_ACK		(UMPROTOCOL + 14)
// DWORD	ID			User Identifier

#define UM_IDENTIFY_REQ			(UMPROTOCOL + 15)
// STRING	GameID		Game ID
// DWORD	ServID		Session Manager Server ID
#define UM_IDENTIFY_ACK			(UMPROTOCOL + 16)
// BYTE		Result		1 on success, or 0
// WORD		GameVer		Game Version
// STRING	GSAddr		Game Server Addr
// DWORD	GSPort		Game Server Port
// STRING	FMAddr		File Manager Address
// DWORD	FMPort		File Manager Port

#define UM_NUMUSER_REQ			(UMPROTOCOL + 17)
// None
#define UM_NUMUSER_ACK			(UMPROTOCOL + 18)
// {
// DWORD	ServID	
// DWORD	NumUser
// }

#define UM_GETUSER_REQ			(UMPROTOCOL + 19)
// STRING	UserID
#define UM_GETUSER_ACK			(UMPROTOCOL + 20)
// DWORD	ServID	
// STRING	UserID
// DWORD	LogTime
// BYTE		CheckResult
// WORD		Serial
// STRING	IPAddr

#define UM_KICKOUT_REQ			(UMPROTOCOL + 21)
#define UM_KICKOUT_ACK			(UMPROTOCOL + 22)

#define UM_CURSTATUS_REQ		(UMPROTOCOL + 23)
// DWORD	DesID
#define UM_CURSTATUS_ACK		(UMPROTOCOL + 24)
// DWORD	DesID
// BYTE		result
// STRING	msg

#define UM_CURSTATUS1_REQ		(UMPROTOCOL + 25)
// DWORD	DesID
#define UM_CURSTATUS1_ACK		(UMPROTOCOL + 26)
// DWORD	DesID
// BYTE		result
// STRING	msg

#endif//_UMPROTOCOL_H_
