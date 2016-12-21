#pragma once

#include "stdafx.h"
//#include "Define.h"

#define DisplayErrorMsg(c)			_DisplayErrorMsg(c, __FILE__, __LINE__)

// 2002.1.25 JJS ------------------------------------------------------------------------------------//
//#define CheckGetVarString(a, b, c, d, e)	_CheckGetVarString(a, b, c, d, e, __FILE__, __LINE__)
#define GetVarString(a, b, c, d)			_GetVarString(a, b, c, d, __FILE__, __LINE__)
#define GetVarLongString(a, b, c, d)		_GetVarLongString(a, b, c, d, __FILE__, __LINE__)
#define GetString(a, b, c, d)				_GetString(a, b, c, d, __FILE__, __LINE__)

//BOOL	_CheckGetVarString(int nLength, TCHAR* tBuf, TCHAR* sBuf, int nSize, int& index, char* strFn, int nLine);
int		_GetVarString(int iMax, TCHAR* tBuf, TCHAR* sBuf, int& index, char* strFn, int nLine);
int		_GetVarLongString(int iMax, TCHAR* tBuf, TCHAR* sBuf, int& index, char* strFn, int nLine);
void	_GetString(char* tBuf, char* sBuf, int len, int& index, char* strFn, int nLine);

/*
BYTE	GetByte(char* sBuf, int& index);
int		GetShort(char* sBuf, int& index);
int		GetInt(char* sBuf, int& index);
DWORD	GetDWORD(char* sBuf, int& index);
void	SetString(char* tBuf, char* sBuf, int len, int& index);
void	SetVarString(TCHAR *tBuf, TCHAR* sBuf, int len, int &index);
void	SetByte(char* tBuf, BYTE sByte, int& index);
void	SetShort(char* tBuf, int sShort, int& index);
void	SetInt(char* tBuf, int sInt, int& index);
void	SetDWORD(char* tBuf, DWORD sDword, int& index);
*/

int		ParseSpace( char* tBuf, char* sBuf);
int		ParseSpaceInUser( char* tBuf, char* sBuf, int iSize);
CString	GetProgPath();
CPoint	ConvertToClient( int x, int y, int cx, int cy );
CPoint	ConvertToServer( int x, int y, int cx, int cy );
int		myrand( int min, int max, BOOL bSame = FALSE );
int		XdY(int x, int y);
void	SpaceCopy(LPSTR source, CString dest, int size);
void	SpaceCopy(CString& source, CString dest, int size);

void	CheckMaxValue(DWORD& dest, DWORD add);
void	CheckMaxValue(int& dest, int add);
void	CheckMaxValue(short& dest, short add);
BOOL	CheckMaxValueReturn(DWORD& dest, DWORD add);

void	_DisplayErrorMsg(SQLHANDLE hstmt, LPCTSTR strFile, int nLine);
CString _ID( WORD string_id );

__forceinline BYTE GetByte(char* sBuf, int& index)
{
	int t_index = index;
	index++;
	return (BYTE)(*(sBuf+t_index));
}

__forceinline int GetShort(char* sBuf, int& index)
{
	index += 2;
	return *(short*)(sBuf+index-2);
}

__forceinline int GetInt(char* sBuf, int& index)
{
	index += 4;
	return *(int*)(sBuf+index-4);
}

__forceinline DWORD GetDWORD(char* sBuf, int& index)
{
	index += 4;
	return *(DWORD*)(sBuf+index-4);
}

__forceinline void SetString(char* tBuf, char* sBuf, int len, int& index)
{
	CopyMemory(tBuf+index, sBuf, len);
	index += len;
}

__forceinline void SetVarString(TCHAR *tBuf, TCHAR* sBuf, int len, int &index)
{
	*(tBuf+index) = (BYTE)len;
	index++;

	CopyMemory(tBuf+index, sBuf, len);
	index += len;
}

__forceinline void SetByte(char* tBuf, BYTE sByte, int& index)
{
	*(tBuf+index) = (char)sByte;
	index++;
}

__forceinline void SetShort(char* tBuf, int sShort, int& index)
{
	short temp = (short)sShort;

	CopyMemory( tBuf+index, &temp, 2);
	index += 2;
}

__forceinline void SetInt(char* tBuf, int sInt, int& index)
{
	CopyMemory( tBuf+index, &sInt, 4);
	index += 4;
}

__forceinline void SetDWORD(char* tBuf, DWORD sDword, int& index)
{
	CopyMemory( tBuf+index, &sDword, 4);
	index += 4;
}

