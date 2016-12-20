///////////////////////////////////////////////////////////////////////////////
// BProtocol.h - Buddy Protocol Define
//

#ifndef _BPROTOCOL_H_
#define _BPROTOCOL_H_

// Netgame과는 반대...
#define WM_BUDDYWRITE_PIPE		(WM_USER + 110)
#define WM_BUDDYREAD_PIPE		(WM_USER + 111)

#define BPROTOCOL				(WORD)(0x7000)

///////////////////////////////////////////////////////////////////////////////
// Request & Receive User Id
// None
#define BP_GETCLIENTID_REQ		(BPROTOCOL + 0)
// STRING		UserID
#define BP_GETCLIENTID_ACK		(BPROTOCOL + 1)
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Request & Receive Buddy List
// Binary
#define BP_GETBUDDYLIST_REQ		(BPROTOCOL + 2)
// Binary
#define BP_GETBUDDYLIST_ACK		(BPROTOCOL + 3)
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Request & Receive Buddy List
// Binary
#define BP_SETBUDDYLIST_REQ		(BPROTOCOL + 4)
// Binary
#define BP_SETBUDDYLIST_ACK		(BPROTOCOL + 5)
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Request & Receive User Information
// String		UserID
// BYTE			AskType
//				0 : by ID
//				1 : by Name
#define BP_GETUSERINFO_REQ		(BPROTOCOL + 6)
// String		UserID
// String		UserName
// String		Position
// String		Email
// BYTE			bConnected
//				0 : Logged In
//				1 : Can't Find
//				2 : Not Logged In
//				3 : Logged In but the target User rejects to send his/her info
#define BP_GETUSERINFO_ACK		(BPROTOCOL + 7)
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Request & Receive User Status
// String		UserID
#define BP_GETUSERSTATUS_REQ	(BPROTOCOL + 8)
// String		UserID
// BYTE			bConnected
// String		Position
#define BP_GETUSERSTATUS_ACK	(BPROTOCOL + 9)
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Send & Receive Chatting
// String		UserID
// String		Message
#define BP_SENDCHAT				(BPROTOCOL + 10)
// String		UserID
// String		Message
#define BP_RECVCHAT				(BPROTOCOL + 11)
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Allow to show user's Information
// From Server
// String		UserID
#define BP_ALLOWBUDDY_REQ		(BPROTOCOL + 12)
// String		UserID
#define BP_ALLOWBUDDY_ACK		(BPROTOCOL + 13)
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// IKING 1999.1.
// PIPE 접속 메시지...
#define BP_CN_LOGIN_REQ			(BPROTOCOL + 20)
#define BP_NC_LOGIN_ACK			(BPROTOCOL + 21)

#define BP_BUDDYMSGRESULT_REQ	(BPROTOCOL + 22)
// WORD result
// String UserID
// String findID
//

#define BP_BUDDYSAVEDMSG_REQ	(BPROTOCOL + 23)
// String ID

#define BP_BUDDYSAVEDMSG_ACK	(BPROTOCOL + 24)
// WORD result
// WORD n
// String MSG

#define BP_CN_LOGOUT_REQ		(BPROTOCOL + 25)
#define BP_NC_LOGOUT_ACK		(BPROTOCOL + 26)

//

#endif//_BPROTOCOL_H_