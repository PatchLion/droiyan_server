///////////////////////////////////////////////////////////////////////////////
// FMProtocol.h - File Manager Server Protocol Define
//

#ifndef _FMPROTOCOL_H_
#define _FMPROTOCOL_H_

// Version Checking & File Download Messages
#define FMPROTOCOL				(WORD)(0x8100)
#define FM_DOWNINFO_REQ			(FMPROTOCOL + 0)
// Remark :		Download Information Req.
// Argument :	WORD	Ver			Client Version
#define FM_DOWNINFO_ACK			(FMPROTOCOL + 1)
// Remark :		File Information Ack.
// Argument :	INT		NumFiles	The number of files to download.

#define FM_FILEINFO_REQ			(FMPROTOCOL + 2)
// Remark :		File Information Req.
// Argument :	NONE
#define FM_FILEINFO_ACK			(FMPROTOCOL + 3)
// Remark :		File Information Ack && Start Download.
// Argument :	STRING	FileName	local file name to download (include path)
//									or null string if no more files.
//				DWORD	FileLength	file length to download
//				BYTE	Compressed	1 if the file is compressed or 0.

#define FM_ENDDOWN_REQ				(FMPROTOCOL + 4)
// Remark :		End Download Req.
// Argument :	None
#define FM_ENDDOWN_ACK				(FMPROTOCOL + 5)
// Remark :		End Download Ack.
// Argument :	None

#define FM_DOWN_REQ					(FMPROTOCOL + 6)
// Remark :		Download Req.
// Argument :	DWORD CurrentLength
#define FM_DOWN_ACK					(FMPROTOCOL + 7)
// Remark :		Download Req.
// Argument :	DWORD CurrentLength

#define FM_VERSIONINFO_REQ			(FMPROTOCOL + 8)
// Remark :		Ask Filemanager version Req.

#define FM_VERSIONINFO_ACK			(FMPROTOCOL + 9)
// Remark :		Ask Filemanager version ack.
// Argument :	int CurrentVersion

#endif//_FMPROTOCOL_H_