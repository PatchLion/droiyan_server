#include "common.h"
#include "..\ShootSunApi\ShootSunApi.h"


#define    CMP_BUFFER_SIZE  36312
#define    EXP_BUFFER_SIZE  12596

#define    CMP_DICT_SIZE1   1024
#define    CMP_DICT_SIZE2   2048
#define    CMP_DICT_SIZE3   4096

#define    CMP_BINARY  0
#define    CMP_ASCII   1 

#define    CMP_NO_ERROR          0
#define    CMP_INVALID_DICTSIZE  1
#define    CMP_INVALID_MODE      2
#define    CMP_BAD_DATA          3
#define    CMP_ABORT             4


char CMP_BUFF[CMP_BUFFER_SIZE];
char EXP_BUFF[EXP_BUFFER_SIZE];

unsigned int (__cdecl *implode)(void *, void *, char*, void*, unsigned int*, unsigned int*);
unsigned int (__cdecl *explode)(void*, void*, char*, void*);
unsigned long (__cdecl *crc32)(void*, unsigned int*, unsigned long*);
// the PKWARE Data Compression Library.  The content of this
// structure is entirely up to the programmer.
typedef struct {

   FILE *PKInputHandle;
   FILE *PKOutputHandle;

   unsigned int type;
   unsigned int dsize;
   unsigned long CRC;
   unsigned long CompressedSize;
   unsigned int (*ReadBuffPtr)(char  *buff, unsigned int  *size, void *pParam);
   void (*WriteBuffPtr)(char  *buff, unsigned int *size, void *pParam);

   char *buf;
   int nLen;
   int nNow;
   BOOL Analyse;

} IMPLODE_PARAMS;

extern GAMEDATA GameData;
HMODULE hLib;

IMPLODE_PARAMS pParams_Implode;
IMPLODE_PARAMS pParams_Explode;

BOOL InstallPKware(char* cExePath)
{
	FARPROC _Class;

	char buf[MAX_PATH] = {'\0'};
	strcat(buf,cExePath);
	strcat(buf,"impborl.dll");
	hLib = LoadLibrary(buf);

	if(hLib != NULL) 
	{
		_Class       = GetProcAddress(hLib, "_crc32");
		crc32        = (unsigned long (__cdecl*)(void*, unsigned int*, unsigned long*))_Class;
	
		_Class       = GetProcAddress(hLib, "_explode");
		explode      = (unsigned int (__cdecl*)(void*, void*, char*, void*))_Class;

		_Class       = GetProcAddress(hLib, "_implode");
		implode      = (unsigned int (__cdecl*)(void*, void*, 
								   char*, void*, unsigned int*, unsigned int*))_Class;

	}

//	FreeLibrary(hLib);

	return TRUE;
}

unsigned int ReadBuff_Implode(char  *buff, unsigned int  *size, void *pParam)
{
//	IMPLODE_PARAMS *pParamPtr = (IMPLODE_PARAMS *) pParam;

	//strcpy(buff, pParams_Implode.buf);
	memcpy(buff,pParams_Implode.buf,pParams_Implode.nLen);

	if (pParams_Implode.Analyse == TRUE)  
	{ 
		pParams_Implode.Analyse = FALSE; return pParams_Implode.nLen; 
	}

	else { /*pParams_Implode.CRC = 0; */return 0; }

//	pParamPtr->CRC = 
		//crc32( (char *) buff, (unsigned int  *) &read, (unsigned long *) &pParamPtr->CRC );


	return 0;
}

void WriteBuff_Implode(char  *buff, unsigned int  *size, void *pParam)
{
   
//	IMPLODE_PARAMS *pParamPtr = (IMPLODE_PARAMS *) pParam;
   
//	unsigned int wrote;


	char szTemp[12048], szTemp1[8];

	int i;

	for(i=0; i<pParams_Implode.nNow; i++ )
	{
		sprintf(szTemp1, "%2.2X ", (BYTE)buff[i]);
		
		strcat(szTemp, szTemp1);
	}

	strcat(szTemp, "\n");
	
	SaveLog_(szTemp);
	
}

unsigned int ReadBuff_Explode(char  *buff, unsigned int  *size, void *pParam)
{
//	IMPLODE_PARAMS *pParamPtr = (IMPLODE_PARAMS *) pParam;

	memcpy(buff, pParams_Explode.buf, pParams_Explode.nLen);

	if (pParams_Explode.Analyse == TRUE)  
	{
		pParams_Explode.Analyse = FALSE; return pParams_Explode.nLen; 
	}
	else {/* pParams_Explode.CRC = 0; */return 0; }
	return 0;
}

void WriteBuff_Explode(char  *buff, unsigned int  *size, void *pParam)
{
	memcpy(GameData.StrPKWARE, buff, pParams_Explode.nNow);
	GameData.PKLen = pParams_Explode.nNow;

}

int PKware_Implode(char *buf, int nLen, int resLen)
{
	int res = 0;

	pParams_Implode.buf = (char*)malloc(nLen+100);
	memcpy(pParams_Implode.buf,buf,nLen);

	pParams_Implode.nNow          = resLen;
	pParams_Implode.nLen          = nLen;
	pParams_Implode.Analyse       = TRUE;
	pParams_Implode.type          = CMP_ASCII;
	pParams_Implode.dsize         = CMP_DICT_SIZE3;
	pParams_Implode.ReadBuffPtr   = ReadBuff_Implode;
	pParams_Implode.WriteBuffPtr  = WriteBuff_Implode;

	res = implode(pParams_Implode.ReadBuffPtr, pParams_Implode.WriteBuffPtr, CMP_BUFF, 
		&pParams_Implode, &pParams_Implode.type, &pParams_Implode.dsize);

	return res;
}

int PKware_Explode(char *buf, int nLen, int resLen)
{
	int res = 0;

	pParams_Explode.buf = (char*)malloc(nLen+100);

	
	//strcpy(pParams_Explode.buf, buf);
	memcpy(pParams_Explode.buf,buf,nLen);
	pParams_Explode.nNow          = resLen;
	pParams_Explode.nLen          = nLen;
	pParams_Explode.Analyse       = TRUE;
	pParams_Explode.type          = CMP_ASCII;
	pParams_Explode.dsize         = CMP_DICT_SIZE3;
	pParams_Explode.ReadBuffPtr   = ReadBuff_Explode;
	pParams_Explode.WriteBuffPtr  = WriteBuff_Explode;

	res = explode(pParams_Explode.ReadBuffPtr, pParams_Explode.WriteBuffPtr, EXP_BUFF, &pParams_Explode);
	
	return res;
}
