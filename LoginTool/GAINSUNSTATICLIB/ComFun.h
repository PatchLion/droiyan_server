#ifndef _COMFUN_H_
#define _COMFUN_H_

//#ifdef _DEBUG
//	#define __LOG
//#endif
#define		NORMALFREG9X	0x1742
#define		NORMALFREGNT	0x2ea5

void SaveLog(char *p,const char* filename );
void SaveSendRecvLog(const char* title,char *buf,int len,const char* filename );
char IsEnglishChar( BYTE byEn );
int GetNumber(char *buf);                  // 数学函数，从字符串得到一个正确的数字
int InitalizeApplication(HINSTANCE hInstance);
void SetClock9x(int freq);
void Ring0();
void SetSpeed9x( WORD freg );
void SetSpeedNT(int freq);
void SetSpeed(int freq);
int	 IsWinNT();
void GetExeDir( char* szExeDir);
void TFPKware_(LPBYTE lpTarget, int nLen,LPBYTE dst,int &len);
//////////////////////////////////
//PORTTALK
/////////////////////////////////
unsigned char OpenPortTalk(void);
void ClosePortTalk(void);

void outportb(unsigned short PortAddress, unsigned char byte);
unsigned char inportb(unsigned short PortAddress);

void InstallPortTalkDriver(void);
unsigned char StartPortTalkDriver(void);

BYTE GetByte(char* sBuf, int& index);
int GetShort(char* sBuf, int& index);
int GetInt(char* sBuf, int& index);
DWORD GetDWORD(char* sBuf, int& index);
void _GetString(char* tBuf, char* sBuf, int len, int& index);
int ParseSpaceInUser( char* tBuf, char* sBuf, int iSize);
#endif
