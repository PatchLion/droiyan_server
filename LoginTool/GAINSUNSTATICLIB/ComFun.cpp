#include "stdafx.h"
#include <tchar.h>
#include <WINSVC.H>
#include <winioctl.h>
#include "comfun.h"
#include "time.h"
#include "compress.h"

#define FREE_INT_NO 5
#define ZDH 5
#define    inp(PortAddress)         inportb(PortAddress)
#define    outp(PortAddress, Value) outportb(PortAddress, Value)
#define PORTTALK_TYPE 40000 /* 32768-65535 are reserved for customers */

DWORD dwSendRecvIndex = 0;
// The IOCTL function codes from 0x800 to 0xFFF are for customer use.

#define IOCTL_IOPM_RESTRICT_ALL_ACCESS \
    CTL_CODE(PORTTALK_TYPE, 0x900, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_IOPM_ALLOW_EXCUSIVE_ACCESS \
    CTL_CODE(PORTTALK_TYPE, 0x901, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_SET_IOPM \
    CTL_CODE(PORTTALK_TYPE, 0x902, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_ENABLE_IOPM_ON_PROCESSID \
    CTL_CODE(PORTTALK_TYPE, 0x903, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_READ_PORT_UCHAR \
    CTL_CODE(PORTTALK_TYPE, 0x904, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_WRITE_PORT_UCHAR \
    CTL_CODE(PORTTALK_TYPE, 0x905, METHOD_BUFFERED, FILE_ANY_ACCESS)

void SaveLog(char *p,const char* filename)
{
#ifdef _DEBUG
	HANDLE hFile = NULL;
	CHAR PRecord[MAX_PATH*2+64];
	DWORD i;
	DWORD sPRecord = wsprintf( PRecord,"%s\n",p);
	hFile = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL);
	SetFilePointer(hFile, 0, NULL, FILE_END);
	WriteFile(hFile, PRecord, sPRecord, &i, NULL);
	CloseHandle(hFile);
#endif
}

char IsEnglishChar( BYTE byEn )
{
	BYTE i;
	for( i = 32;i < 127 ;i ++ )
	{
		if( byEn == i )
			return byEn;
	}
	return 46;
}


void SaveSendRecvLog(const char* title,char *buf,int len,const char* filename)
{
	TCHAR aaa[1024];
	TCHAR bbb[1024];
	TCHAR cTemp[1024];
	TCHAR cTemp1[1024];
	int j = 0,k = 0;
#ifdef _DEBUG
	struct tm *newtime;
	long ltime;
	time( &ltime );
	newtime = gmtime( &ltime );
	//wsprintf( cTemp,_T("%s %d Bytes at %02d:%02d:%02d"),title,len,newtime->tm_hour,
	//	newtime->tm_min,newtime->tm_sec,newtime->);
	wsprintf( cTemp,"%s %d Index : %d Bytes at %02d:%02d:%02d",title,dwSendRecvIndex,len,newtime->tm_hour,
		newtime->tm_min,newtime->tm_sec);
	dwSendRecvIndex++;
	SaveLog(cTemp,filename);
	ZeroMemory(aaa,1024);
	ZeroMemory(bbb,1024);
	for( int i = 0 ;i < len ; i++ )
	{	
		wsprintf( aaa+j,_T("%02X "),(BYTE)buf[i]);
		wsprintf( bbb+k,_T("%c"),IsEnglishChar(buf[i]));
		j+=3;
		k++;
		if( (i + 1)%16 == 0 )
		{
			*(aaa+j+1) = '\0';
			*(bbb+k+1) = '\0';
			wsprintf( cTemp,_T("%s-> %04X:\t%s\t%s"),title,i/16*16,aaa,bbb);
			SaveLog(cTemp,filename);
			j = 0;
			k = 0;
			ZeroMemory(aaa,1024);
			ZeroMemory(bbb,1024);
		}
	}
	if( j )
	{
		for( ;j<48;j++ )
			*(aaa+j) = 0x20;
		*(aaa+j+1) = '\0';
		*(bbb+k+1) = '\0';
		wsprintf( cTemp,_T("%s-> %04X:\t%s\t%s"),title,i/16*16,aaa,bbb);
		SaveLog(cTemp,filename);
	}
#endif
}

int GetNumber(char *buf)
{
	int i, n, m;

	if (strcmp(buf, "") == 0) return 0;

	for(i=0; i<strlen(buf); i++)
	{
		switch((BYTE)buf[i])
		{
		    case 0x30:
				n = 0;
				break;

			case 0x31:
				n = 1;
				break;

			case 0x32:
				n = 2;
				break;

			case 0x33:
				n = 3;
				break;

			case 0x34:
				n = 4;
				break;

			case 0x35:
				n = 5;
				break;

			case 0x36:
				n = 6;
				break;

			case 0x37:
				n = 7;
				break;

			case 0x38:
				n = 8;
				break;

			case 0x39:
				n = 9;
				break;
		}
		if ((i == 0) && (strlen(buf) == 6)) m = n * 100000;
		if ((i == 1) && (strlen(buf) == 6)) m = n + n * 10000;
		if ((i == 2) && (strlen(buf) == 6)) m = m + n * 1000;
		if ((i == 3) && (strlen(buf) == 6)) m = m + n * 100;
		if ((i == 4) && (strlen(buf) == 6)) m = m + n * 10;
		if ((i == 5) && (strlen(buf) == 6)) m = m + n;

		if ((i == 0) && (strlen(buf) == 5)) m = n * 10000;
		if ((i == 1) && (strlen(buf) == 5)) m = m + n * 1000;
		if ((i == 2) && (strlen(buf) == 5)) m = m + n * 100;
		if ((i == 3) && (strlen(buf) == 5)) m = m + n * 10;
		if ((i == 4) && (strlen(buf) == 5)) m = m + n;

		if ((i == 0) && (strlen(buf) == 4)) m = n * 1000;
		if ((i == 1) && (strlen(buf) == 4)) m = m + n * 100;
		if ((i == 2) && (strlen(buf) == 4)) m = m + n * 10;
		if ((i == 3) && (strlen(buf) == 4)) m = m + n;

		if ((i == 0) && (strlen(buf) == 3)) m = n * 100;
		if ((i == 1) && (strlen(buf) == 3)) m = m + n * 10;
		if ((i == 2) && (strlen(buf) == 3)) m = m + n;

		if ((i == 0) && (strlen(buf) == 2)) m = n * 10;
		if ((i == 1) && (strlen(buf) == 2)) m = m + n;

		if ((i == 0) && (strlen(buf) == 1)) m = n;
	}
	return m;
}

int InitalizeApplication(HINSTANCE hInstance) 
{
	INITCOMMONCONTROLSEX IntComStruct;
	HKEY hKeyResults = 0;

	IntComStruct.dwSize = sizeof(IntComStruct);
	IntComStruct.dwICC = ICC_TREEVIEW_CLASSES;
	InitCommonControls();	
	InitCommonControlsEx(&IntComStruct);

	return TRUE;
}


void Ring0()
{	//在Windows9x下进入ring0后进行的操作
	__asm
	{
		//cli
		mov al,34h
		out 43h,al	//写入8253控制寄存器，设置写0号定时器
		mov ax,bx	
		out 40h,al	//写定时值低位
		mov al,ah
		out 40h,al	//写定时值高位
		sti
		iretd;
	}
}

void SetClock9x(int freq)
{
	union Function_Pointer
	{
		void (*pointer)();
		char bytes[sizeof(void *)];
	}OldIntAddress,NewIntAddress;

	int IDTAddress;		//IDT表基地址
	int IDTItemAddress;	//要修改的中断门所在地址
	char *Pointer;	//要修改的中断门所在地址，指针形式

	__asm
	{
		push eax
		sidt [esp-2]
		pop eax
		mov IDTAddress,eax	//得到IDT表基地址
	}
	
	IDTItemAddress=FREE_INT_NO*8+IDTAddress;
	Pointer=(char *)IDTItemAddress;
	NewIntAddress.pointer=Ring0;
	
	OldIntAddress.bytes[0]=Pointer[0];
	OldIntAddress.bytes[1]=Pointer[1];
	OldIntAddress.bytes[2]=Pointer[6];
	OldIntAddress.bytes[3]=Pointer[7];	//保存旧的中断门

	Pointer[0]=NewIntAddress.bytes[0];
	Pointer[1]=NewIntAddress.bytes[1];
	Pointer[6]=NewIntAddress.bytes[2];
	Pointer[7]=NewIntAddress.bytes[3]; //设置新的中断门
	
	__asm
	{
		mov ebx,freq
		int FREE_INT_NO			//产生中断，进入ring0
	}

	Pointer[0]=OldIntAddress.bytes[0];
	Pointer[1]=OldIntAddress.bytes[1];
	Pointer[6]=OldIntAddress.bytes[2];
	Pointer[7]=OldIntAddress.bytes[3];	//恢复旧的中断门
}


void SetSpeed9x( WORD freg )
{
	BYTE IDT[5];
	DWORD OG;
	__asm
	{
		//push ebx 
		sidt IDT //读入中断描述符表 
		mov ebx, dword ptr [IDT+2] //IDT表基地址 
		add ebx, 8*ZDH //计算中断在中断描述符表中的位置 
		cli //关中断 
		mov dx, word ptr [ebx+6] 
		shl edx, 16
		mov dx, word ptr [ebx] 
		mov [OG], edx 
		//mov bx, freg
		mov eax, offset Ring0Code //指向Ring0级代码段 
		mov word ptr [ebx], ax //低16位,保存在1,2位 
		shr eax, 16
		mov word ptr [ebx+6], ax //高16位，保存在6,7位 
		int ZDH //中断 
		mov ebx, dword ptr [IDT+2] //重新定位 
		add ebx, 8*ZDH 
		mov edx, [OG] 
		mov word ptr [ebx], dx 
		shr edx, 16
		mov word ptr [ebx+6], dx //恢复被改了的向量 
		jmp	exitasm
		//pop ebx 
Ring0Code:
		mov al,34h
		out 43h,al	//写入8253控制寄存器，设置写0号定时器
		mov ax,freg	
		out 40h,al	//写定时值低位
		mov al,ah
		out 40h,al	//写定时值高位
		iretd;
exitasm:
	}
}

void SetSpeedNT(int freq)
{	
	if( OpenPortTalk() != 0 )
		return;
	//NT下的操作
	//这里使用了NT Port库
	outportb(0x43,0x34);	//写入8253控制寄存器，设置写0号定时器
	outportb(0x40,freq&0xff);	//写定时值低位
	outportb(0x40,(freq>>8)&0xff);	//写定时值高位
	ClosePortTalk();
}

void SetSpeed(int freq)
{
	if( IsWinNT() )
	{
		SetSpeedNT(freq);
	}
	if( IsWinNT() == 0 )
	{
		SetSpeed9x(freq);
	}
}

int	 IsWinNT()
{
	OSVERSIONINFOEX osvi;
	BOOL bOsVersionInfoEx;

    // Try calling GetVersionEx using the OSVERSIONINFOEX structure.
    //
    // If that fails, try using the OSVERSIONINFO structure.

    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

    if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
    {
      // If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.

      osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
      if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) ) 
         return -1;
    }
	switch (osvi.dwPlatformId)
	{
		case VER_PLATFORM_WIN32_NT:
			return 1;
		case VER_PLATFORM_WIN32_WINDOWS:
			return 0;
	}
	return -1;

}

////////////////////////////////////////////////////////
//PORTTALK
///////////////////////////////////////////////////////
HANDLE PortTalk_Handle;        /* Handle for PortTalk Driver */

void outportb(unsigned short PortAddress, unsigned char byte)
{
    unsigned int error;
    DWORD BytesReturned;        
    unsigned char Buffer[3];
    unsigned short * pBuffer;
    pBuffer = (unsigned short *)&Buffer[0];
    *pBuffer = PortAddress;
    Buffer[2] = byte;

    error = DeviceIoControl(PortTalk_Handle,
                            IOCTL_WRITE_PORT_UCHAR,
                            &Buffer,
                            3,
                            NULL,
                            0,
                            &BytesReturned,
                            NULL);

    if (!error) printf("Error occured during outportb while talking to PortTalk driver %d\n",GetLastError());
}

unsigned char inportb(unsigned short PortAddress)
{
    unsigned int error;
    DWORD BytesReturned;
    unsigned char Buffer[3];
    unsigned short * pBuffer;
    pBuffer = (unsigned short *)&Buffer;
    *pBuffer = PortAddress;

    error = DeviceIoControl(PortTalk_Handle,
                            IOCTL_READ_PORT_UCHAR,
                            &Buffer,
                            2,
                            &Buffer,
                            1,
                            &BytesReturned,
                            NULL);

    if (!error) printf("Error occured during inportb while talking to PortTalk driver %d\n",GetLastError());
    return(Buffer[0]);
}

unsigned char OpenPortTalk(void)
{
    /* Open PortTalk Driver. If we cannot open it, try installing and starting it */
    PortTalk_Handle = CreateFile("\\\\.\\PortTalk", 
                                 GENERIC_READ, 
                                 0, 
                                 NULL,
                                 OPEN_EXISTING, 
                                 FILE_ATTRIBUTE_NORMAL, 
                                 NULL);

    if(PortTalk_Handle == INVALID_HANDLE_VALUE) {
            /* Start or Install PortTalk Driver */
            StartPortTalkDriver();
            /* Then try to open once more, before failing */
            PortTalk_Handle = CreateFile("\\\\.\\PortTalk", 
                                         GENERIC_READ, 
                                         0, 
                                         NULL,
                                         OPEN_EXISTING, 
                                         FILE_ATTRIBUTE_NORMAL, 
                                         NULL);
               
            if(PortTalk_Handle == INVALID_HANDLE_VALUE) {
                    printf("PortTalk: Couldn't access PortTalk Driver, Please ensure driver is loaded.\n\n");
                    return -1;
            }
    }
	return 0;
}

void ClosePortTalk(void)
{
    CloseHandle(PortTalk_Handle);
}

unsigned char StartPortTalkDriver(void)
{
    SC_HANDLE  SchSCManager;
    SC_HANDLE  schService;
    BOOL       ret;
    DWORD      err;

    /* Open Handle to Service Control Manager */
    SchSCManager = OpenSCManager (NULL,                        /* machine (NULL == local) */
                                  NULL,                        /* database (NULL == default) */
                                  SC_MANAGER_ALL_ACCESS);      /* access required */
                         
    if (SchSCManager == NULL)
      if (GetLastError() == ERROR_ACCESS_DENIED) {
         /* We do not have enough rights to open the SCM, therefore we must */
         /* be a poor user with only user rights. */
         printf("PortTalk: You do not have rights to access the Service Control Manager and\n");
         printf("PortTalk: the PortTalk driver is not installed or started. Please ask \n");
         printf("PortTalk: your administrator to install the driver on your behalf.\n");
         return(0);
         }

    do {
         /* Open a Handle to the PortTalk Service Database */
         schService = OpenService(SchSCManager,         /* handle to service control manager database */
                                  "PortTalk",           /* pointer to name of service to start */
                                  SERVICE_ALL_ACCESS);  /* type of access to service */

         if (schService == NULL)
            switch (GetLastError()){
                case ERROR_ACCESS_DENIED:
                        printf("PortTalk: You do not have rights to the PortTalk service database\n");
                        return(0);
                case ERROR_INVALID_NAME:
                        printf("PortTalk: The specified service name is invalid.\n");
                        return(0);
                case ERROR_SERVICE_DOES_NOT_EXIST:
                        printf("PortTalk: The PortTalk driver does not exist. Installing driver.\n");
                        printf("PortTalk: This can take up to 30 seconds on some machines . .\n");
                        InstallPortTalkDriver();
                        break;
            }
         } while (schService == NULL);

    /* Start the PortTalk Driver. Errors will occur here if PortTalk.SYS file doesn't exist */
    
    ret = StartService (schService,    /* service identifier */
                        0,             /* number of arguments */
                        NULL);         /* pointer to arguments */
                    
    if (ret) printf("PortTalk: The PortTalk driver has been successfully started.\n");
    else {
        err = GetLastError();
        if (err == ERROR_SERVICE_ALREADY_RUNNING)
          printf("PortTalk: The PortTalk driver is already running.\n");
        else {
          printf("PortTalk: Unknown error while starting PortTalk driver service.\n");
          printf("PortTalk: Does PortTalk.SYS exist in your \\System32\\Drivers Directory?\n");
          return(0);
        }
    }

    /* Close handle to Service Control Manager */
    CloseServiceHandle (schService);
    return(TRUE);
}

void InstallPortTalkDriver(void)
{
    SC_HANDLE  SchSCManager;
    SC_HANDLE  schService;
    DWORD      err;
    CHAR         DriverFileName[80];

    /* Get Current Directory. Assumes PortTalk.SYS driver is in this directory.    */
    /* Doesn't detect if file exists, nor if file is on removable media - if this  */
    /* is the case then when windows next boots, the driver will fail to load and  */
    /* a error entry is made in the event viewer to reflect this */

    /* Get System Directory. This should be something like c:\windows\system32 or  */
    /* c:\winnt\system32 with a Maximum Character lenght of 20. As we have a       */
    /* buffer of 80 bytes and a string of 24 bytes to append, we can go for a max  */
    /* of 55 bytes */

    if (!GetSystemDirectory(DriverFileName, 55))
        {
         printf("PortTalk: Failed to get System Directory. Is System Directory Path > 55 Characters?\n");
         printf("PortTalk: Please manually copy driver to your system32/driver directory.\n");
        }

    /* Append our Driver Name */
    lstrcat(DriverFileName,"\\Drivers\\PortTalk.sys");
    printf("PortTalk: Copying driver to %s\n",DriverFileName);

    /* Copy Driver to System32/drivers directory. This fails if the file doesn't exist. */

    if (!CopyFile("PortTalk.sys", DriverFileName, FALSE))
        {
         printf("PortTalk: Failed to copy driver to %s\n",DriverFileName);
         printf("PortTalk: Please manually copy driver to your system32/driver directory.\n");
        }

    /* Open Handle to Service Control Manager */
    SchSCManager = OpenSCManager (NULL,                   /* machine (NULL == local) */
                                  NULL,                   /* database (NULL == default) */
                                  SC_MANAGER_ALL_ACCESS); /* access required */

    /* Create Service/Driver - This adds the appropriate registry keys in */
    /* HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services - It doesn't  */
    /* care if the driver exists, or if the path is correct.              */

    schService = CreateService (SchSCManager,                      /* SCManager database */
                                "PortTalk",                        /* name of service */
                                "PortTalk",                        /* name to display */
                                SERVICE_ALL_ACCESS,                /* desired access */
                                SERVICE_KERNEL_DRIVER,             /* service type */
                                SERVICE_DEMAND_START,              /* start type */
                                SERVICE_ERROR_NORMAL,              /* error control type */
                                "System32\\Drivers\\PortTalk.sys", /* service's binary */
                                NULL,                              /* no load ordering group */
                                NULL,                              /* no tag identifier */
                                NULL,                              /* no dependencies */
                                NULL,                              /* LocalSystem account */
                                NULL                               /* no password */
                                );

    if (schService == NULL) {
         err = GetLastError();
         if (err == ERROR_SERVICE_EXISTS)
               printf("PortTalk: Driver already exists. No action taken.\n");
         else  printf("PortTalk: Unknown error while creating Service.\n");    
    }
    else printf("PortTalk: Driver successfully installed.\n");

    /* Close Handle to Service Control Manager */
    CloseServiceHandle (schService);
}

//获得运行目录
void GetExeDir( char* szExeDir)
{
	char buf[MAX_PATH];
	char *cptr;

	//now change the directory
	//to make sure were accessing the proper file
	GetModuleFileName(NULL, buf, MAX_PATH);

	//move pointer to end of string
	cptr = buf + lstrlen(buf);

	//find the end of the path
	do
	{
		cptr--;
	} while (*cptr != '\\');
	cptr++;
	*cptr='\0';
	strcpy(szExeDir,buf);
}

void TFPKware_(LPBYTE lpTarget, int nLen,LPBYTE dst,int &len)
{
	
}
BYTE GetByte(char* sBuf, int& index)
{
	int t_index = index;
	index++;
	return (BYTE)(*(sBuf+t_index));
}

int GetShort(char* sBuf, int& index)
{
	index += 2;
	return *(short*)(sBuf+index-2);
}

int GetInt(char* sBuf, int& index)
{
	index += 4;
	return *(int*)(sBuf+index-4);
}

DWORD GetDWORD(char* sBuf, int& index)
{
	index += 4;
	return *(DWORD*)(sBuf+index-4);
}

void _GetString(char* tBuf, char* sBuf, int len, int& index)
{
	memcpy(tBuf, sBuf+index, len);
	index += len;
}

int ParseSpace( char* tBuf, char* sBuf)
{
	int i = 0, index = 0;
	BOOL flag = FALSE;
	
	while(sBuf[index] == ' ' || sBuf[index] == '\t')index++;
	while(sBuf[index] !=' ' && sBuf[index] !='\t' && sBuf[index] !=(BYTE) 0){
		tBuf[i++] = sBuf[index++];
		flag = TRUE;
	}
	tBuf[i] = 0;

	while(sBuf[index] == ' ' || sBuf[index] == '\t')index++;
	if(!flag) return 0;	
	return index;
}

int ParseSpaceInUser( char* tBuf, char* sBuf, int iSize)
{
	int i = 0, index = 0;
	BOOL flag = FALSE;
	BOOL bNext = FALSE;

	if(iSize == 0)
	{
		tBuf[0] = 0;
		return 0;
	}

	while(sBuf[index] == ' ' || sBuf[index] == '\t')
	{
		if(iSize > index) index++;
		else break;
	}

	while(sBuf[index] !=' ' && sBuf[index] !='\t' && sBuf[index] !=(BYTE) 0)
	{
		if(iSize > index)
		{
			tBuf[i++] = sBuf[index++];
			flag = TRUE;
		}
		else break;
	}

	tBuf[i] = 0;

	if(!flag)
	{
		tBuf[0] = 0;
		return 0;	
	}

//	while ( sBuf[index] == ' ' || sBuf[index] == '\t' ) index++;

	return index;
}