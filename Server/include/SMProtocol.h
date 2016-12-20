///////////////////////////////////////////////////////////////////////////////
// SMProtocol.h - Session Manager Protocol Define
//

#ifndef _SMPROTOCOL_H_
#define _SMPROTOCOL_H_

// Session Management Messages
#define SMPROTOCOL				(WORD)(0x8000)
#define SM_LOGIN_REQ			(SMPROTOCOL + 0)	// Login Req.
// STRING	UserID
// STRING	Passwd
// STRING	Serial1
// STRING	Serial2

// Droiyan Login by zi_gi 2002-03-20
#define SM_LOGIN_ACK			(SMPROTOCOL + 1)	// Login Ack.
// Login Success, Login User Duplicate FAIL
	// BYTE		LoginRes

	// BYTE		bCP
	// BYTE		bDisplayType	(if bCP == 1)
	// BYTE		bMon
	// BYTE		bDay
	// int		iRemainTime

	// BYTE		bNotice
	// STRING	strNotice (if bNotice == 1)

// Login FAIL
	// BYTE		LoginRes

#define SM_LOGIN_ACK			(SMPROTOCOL + 1)	// Login Ack.
// BYTE		LoginRes
// BYTE		SNRes
// BYTE		bNotice
// STRING	strNotice (if bNotice == 1)
#define SM_REGUSER_REQ			(SMPROTOCOL + 2)	// Register user Req.
// STRING	UserID		User ID
// STRING	Passwd		Password
// STRING	Name		Name
// STRING	SocNo		Social Number
// STRING	Address		Address
// STRING	TelNo		Telephone Number
// STRING	Email		Email Address
#define SM_REGUSER_ACK			(SMPROTOCOL + 3)	// Register user Ack.
// BYTE		Result		0 on success, or 1

#define SM_GETINFO_REQ			(SMPROTOCOL + 4)	// Get user information Req.
// No Argument
#define SM_GETINFO_ACK			(SMPROTOCOL + 5)	// Get user information Ack.
// STRING	UserID		User ID
// STRING	Passwd		Password
// STRING	Name		Name
// STRING	SocNo		Social Number
// STRING	Address		Address
// STRING	TelNo		Telephone Number
// STRING	Email		Email Address

#define SM_SETINFO_REQ			(SMPROTOCOL + 6)	// Set user information req.
// STRING	Passwd		Password
// STRING	Name		Name
// STRING	SocNo		Social Number
// STRING	Address		Address
// STRING	TelNo		Telephone Number
// STRING	Email		Email Address
#define SM_SETINFO_ACK			(SMPROTOCOL + 7)	// Set user information ack.
// BYTE		Result		1 on success, or 0

#define SM_REGSN_REQ			(SMPROTOCOL + 8)	// Register S/N Req.
// STRING	Passwd		Serial Number Password
#define SM_REGSN_ACK			(SMPROTOCOL + 9)	// Register S/N Ack.
// BYTE		Result		1 on success, or 0

#define SM_DOWN_REQ				(SMPROTOCOL + 10)	// Start downloading Req.
// No Argument
#define SM_DOWN_ACK				(SMPROTOCOL + 11)	// Start downloading Ack.
// BYTE		Result		1 on success, or 0

#define SM_GAME_REQ				(SMPROTOCOL + 12)	// Start game Req.
// BYTE		Success		1 on start game, or 0 on cancel
#define SM_GAME_ACK				(SMPROTOCOL + 13)	// Start game Ack.
// BYTE		Result		1 on success, or 0

#define SM_GAMEINFO_REQ			(SMPROTOCOL + 14)
// No Argument
#define SM_GAMEINFO_ACK			(SMPROTOCOL + 15)
// STRING	ServiceName
// BYTE		PayOpt
// STRING	GameID
// WORD		GameVer
#define SM_DIR_REQ				(SMPROTOCOL + 16)
// DWORD	DesID
// STRING	UserID
// BYTE		Start
#define SM_DIR_ACK				(SMPROTOCOL + 17)
// DWORD	DesID
// STRING	UserID
// BYTE		Start
// STRING	Addr
// DWORD	Port

#define SM_LOGIN_ACK2			(SMPROTOCOL + 18)	// Login Ack.
// BYTE		LoginRes
// BYTE		SNRes

#define SM_IDEXIST_REQ			(SMPROTOCOL + 19)	// ID exist???
// STRING	UserID

#define SM_IDEXIST_ACK			(SMPROTOCOL + 20)	// ID exist!!!
// BYTE		Result		1 is exist ID, 0 is not exist ID

#define SM_UPGRADING_ACK			(SMPROTOCOL + 21)	// Updrading Status...
// STRING	msg

#define SM_GAMEINFO2_REQ			(SMPROTOCOL + 22)
// No Argument

#define SM_GAMEINFO2_ACK			(SMPROTOCOL + 23)
// No Argument

#define SM_NOTICE_ACK				(SMPROTOCOL + 50)
// BYTE		Result(3)
// STRING	Notice

//////////////////////////////////////////////////////////////////////////
// EVERLAND CP SERVICE LOGIN
// added by amnesia
#define SM_CPLOGOUT_ACK			(SMPROTOCOL + 33)	// Logout Ack.
// BYTE		LogoutRes
// EVERLAND CP SERVICE LOGIN
//////////////////////////////////////////////////////////////////////////
/*
// IKING 1999.1.
#define SM_CONNECTINFO_ACK			(SMPROTOCOL + 100)
// STRING	UserID
// BYTE		Start
// STRING	Addr
// DWORD	Port
// 
*/

// By Youn Gyu 2001. 10.17
#define SM_CONNECTINFO_ACK			(SMPROTOCOL + 100)
// STRING	UserID
// BYTE		Start
// DWORD	Total_Num

// DWORD	Server_Num	// 횟수만큼...
// STRING	Addr
// DWORD	Port
// ...


#define SM_GAMEEND_REQ			(SMPROTOCOL + 101)
#define SM_RECONNECT_REQ		(SMPROTOCOL + 102)

// Buddy Server Manager Packet...
#define BUDDY_CONNECTION_GRANT	(SMPROTOCOL + 104)

#define BUDDY_LOGIN_REQ			(SMPROTOCOL + 105)
#define BUDDY_LOGIN_ACK			(SMPROTOCOL + 106)

#define BUDDY_PACKET			(SMPROTOCOL + 107)

#define SM_BP_SENDCHAT_REQ		(SMPROTOCOL + 108)
#define SM_BP_SENDCHAT_ACK		(SMPROTOCOL + 109)

#define SM_BP_GETBUDDYLIST_REQ	(SMPROTOCOL + 110)
#define SM_BP_GETBUDDYLIST_ACK	(SMPROTOCOL + 111)

#define SM_BP_SETBUDDYLIST_REQ	(SMPROTOCOL + 112)
#define SM_BP_SETBUDDYLIST_ACK	(SMPROTOCOL + 113)

#define SM_BP_GETUSERINFO_REQ	(SMPROTOCOL + 114)
#define SM_BP_GETUSERINFO_ACK	(SMPROTOCOL + 115)

#define SM_BP_GETUSERSTATUS_REQ	(SMPROTOCOL + 116)
#define SM_BP_GETUSERSTATUS_ACK	(SMPROTOCOL + 117)

#define SM_BP_ALLOWBUDDY_REQ	(SMPROTOCOL + 118)
#define SM_BP_ALLOWBUDDY_ACK	(SMPROTOCOL + 119)

#define SM_BP_FINDUSER_REQ		(SMPROTOCOL + 120)
#define SM_BP_FINDUSER_ACK		(SMPROTOCOL + 121)

#define SM_BP_BUDDYMSGRESULT_REQ (SMPROTOCOL + 122)

#define SM_BP_BUDDYSAVEDMSG_REQ (SMPROTOCOL + 123)
#define SM_BP_BUDDYSAVEDMSG_ACK (SMPROTOCOL + 124)

// SUB CODE

// BUDDY PACKET...
#define BDY_FINDUSER_REQ				1
// int SESSION NO
// string ID

#define BDY_FINDUSER_IN_SESSION_REQ		3
// int SESSION NO
// string ID

#define BDY_FINDUSER_IN_SESSION_RESULT	4
// int SESSION NO ; user를 발견한 서버.
// int SESSION NO ; user를 발견을 요청한 서버.
// string ID

// by Youn Gyu 2001. 3 27
#define SM_CHANGEPASSWD_REQ			(SMPROTOCOL + 500)
// STRING	UserID
// STRING	CurrentPasswd
// STRING	NewPasswd

#define SM_CHANGEPASSWD_ACK			(SMPROTOCOL + 501)
// BYTE		Result	---->	ok == 1, fail = 0	

#define SM_GAMESERVER_CONNECT_REQ	(SMPROTOCOL + 502)	// 게임 서버에 연결되었음을 세션에 알린다.
// STRING	UserID

#define SM_GAMESERVER_CONNECT_ACK	(SMPROTOCOL + 503)
// BYTE		Result	---->	ok == 1, fail = 0	

#define SM_ALIVE_ACK			(SMPROTOCOL + 999)

#endif _SMPROTOCOL_H_
