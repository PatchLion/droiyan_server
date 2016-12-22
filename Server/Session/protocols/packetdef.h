#ifndef _PACKETDEF_H
#define _PACKETDEF_H

// PACKET FUNCTION DEF...
int ReadShort( char *pBuf, int& read_value );
int WriteShort( char *pBuf, int write_value );
int ReadInt( char *pBuf, int& read_value );
int WriteInt( char *pBuf, int write_value );
int CopyString( char *tBuf, char *sBuf, int length );

int ReadShort( BYTE *pBuf, int& read_value );
int WriteShort( BYTE *pBuf, int write_value );
int ReadInt( BYTE *pBuf, int& read_value );
int WriteInt( BYTE *pBuf, int write_value );
int CopyString( BYTE *tBuf, BYTE *sBuf, int length );
//


// REQ PACKET에 대한 결과...
#define RESULT_SUCCESS		(WORD)1
#define RESULT_FAIL			(WORD)2

#define BD_UNKNOWN_ERROR	(WORD)1
#define BD_ID_CANNOT_FIND	(WORD)2

// 변수 정의...
#define MAX_ZONE		10
#define MAX_IP_ADDRESS	20 //192.203.140.157

// 에러 정의...
#define TOO_MANY_USER	1
#define ZONE_IS_CLOSED	2
#define OUT_OF_RANGE	3
#define UNKNOWN_ERROR	4
//

// PACKET PART...
#define EL_LOG_IN_REQ					(BYTE)0x01
#define EL_LOG_IN_RESULT				(BYTE)0x02


// DIRECTION SERVER PROTOCOL PART...
#define DSZM__CL_CONNECT_ZONE_REQ		(BYTE)0x01
#define DSZM__CL_CONNECT_ZONE_RESULT	(BYTE)0x02

#define DSZM__CL_LOG_IN_REQ				(BYTE)0x01
#define DSZM__CL_LOG_IN_RESULT			(BYTE)0x02

#define ZMDS__SV_CONNECT_REQ			(BYTE)0x01
#define ZMDS__SV_CONNECT_RESULT			(BYTE)0x02

#define DSSD__CL_LOGIN_INFO_REQ			(BYTE)0x01
#define DSSD__CL_LOGIN_INFO_RESULT		(BYTE)0x02


// SESSION DIVIDER PROTOCOL PART...
#define SDDS__SV_LOG_IN_REQ				(BYTE)0x01
#define SDDS__SV_LOG_IN_RESULT			(BYTE)0x02


// SESSION PROTOCOL PART...
#define SMPROTOCOL				(WORD)(0x8000)

#define BUDDY_CONNECTION_GRANT	(SMPROTOCOL + 104)

#define BUDDY_LOGIN_REQ			(SMPROTOCOL + 105)
#define BUDDY_LOGIN_ACK			(SMPROTOCOL + 106)

#endif
