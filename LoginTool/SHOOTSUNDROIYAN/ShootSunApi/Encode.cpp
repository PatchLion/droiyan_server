#include <tchar.h>
#include <Winsock2.h>
#include <time.h>
#include "Encode.h"
#include "shootsunapi.h"
#include "..\..\GainSunStaticLib\comfun.h"


#define				S_D_WORD_XOR1MUL				((WORD)0x009f)
#define				S_D_WORD_XOR3BASE				((WORD)0x0861)
#define				S_D_WORD_XOR3MUL				((WORD)0x087c)
BYTE S_G_BYTE_DOII_XorTable[10] = { 0x11, 0x54, 0x6, 0x58, 0x45, 0x22, 0x12, 0x53,0x34 ,0x94 };
BYTE S_G_BYTE_XorTable[10];


void Encode::S_Encode_Decode(char *lpTarget, char * lpSource, int nLen)
{

	BYTE	l_BYTE_Xor1 = nLen * S_D_WORD_XOR1MUL, l_BYTE_Xor3;
	//                     0x086d
	WORD	l_WORD_Xor3 = S_D_WORD_XOR3BASE, nCir;

	for (nCir=0; nCir<nLen; nCir++) 
	{
		l_BYTE_Xor3    = HIBYTE(l_WORD_Xor3);
		lpTarget[nCir] = lpSource[nCir] ^ l_BYTE_Xor1 ^ S_G_BYTE_XorTable[nCir % 10] ^ l_BYTE_Xor3;
		l_WORD_Xor3   *= S_D_WORD_XOR3MUL;
	}
}

Encode::Encode(void)
{
	srand( (unsigned)time( NULL ) );
}

Encode::~Encode(void)
{
}

int Encode::S_Encode_send(SOCKET s,char *data)
{
	char buf[200];
	char senddata[200];
	char key[10];
	int i;

	for(i=0;i<200;i++)
		buf[i]= (char)(rand()%256);
	for(i=0;i<10;i++){
		key[i]=buf[107+i];
		S_G_BYTE_XorTable[i]=S_G_BYTE_DOII_XorTable[i]^key[i];
	}
//	SaveSendRecvLog("KEY:",(char*)key,10,"C:\\niuniu2.log");
	::WritePrivateProfileString("AUTO","1","1","c:\\ddd.ini");
	::WritePrivateProfileString("AUTO","KEY",(char*)key,"c:\\ddd.ini");
	for(i=0;i<40;i++){
		buf[i+47]=data[i];
	}
	
	senddata[0]=(char)0xFF;
	senddata[1]=(char)0x88;
	S_Encode_Decode(senddata+2,buf,100);
	for(i=0;i<96;i++){
		senddata[i+2+100]=buf[i+100];
	}
	senddata[198]=(char)0x88;
	senddata[199]=(char)0xFF;
	
	return send(s,senddata,200,0);
}
int Encode::S_Encode_recv(SOCKET s,char *data)
{
	char buf[200];
	char recvdata[200];
	char key[10];
	int i;

	int len =recv(s,recvdata,200,0);//接收数据
	if(len!=200)//如果没有接收到200个字节 退出
		return -1;
	if((recvdata[0]!=(char)0xff) ||(recvdata[1]!=(char)0x88) ||(recvdata[198]!=(char)0x88) ||(recvdata[199]!=(char)0xff))
		return -1;
	//取得KEY
	for(i=0;i<10;i++){
		key[i]=recvdata[107+2+i];
		S_G_BYTE_XorTable[i]=S_G_BYTE_DOII_XorTable[i]^key[i];
	}
	::WritePrivateProfileString("AUTO","33","33","c:\\ddd.ini");
	S_Encode_Decode(buf,recvdata+2,100);
	for(i=0;i<40;i++) data[i]=buf[47+i];
	return 1;
}
BOOL Encode::connect_Server()
{
	struct sockaddr_in Address;
	Socket = socket(AF_INET, SOCK_STREAM, 0);
	Address.sin_family=AF_INET;
	Address.sin_addr.s_addr = inet_addr("61.129.33.167"); 
    Address.sin_port        = htons(65500); 
	if(connect(Socket,(struct sockaddr *)&Address, sizeof(Address))==SOCKET_ERROR)
	{
		con=false;
		return false;
	}
	con=true;
	return true;
}
int Encode::Send_User(char *name,int len)
{
	char data[40];

	data[0]=0x22;
	data[1]=(char)len;
	for(int i=0;i<len;i++){
		data[2+i]=(name[i])^((char)(0xaa+i));
	}
//	SaveSendRecvLog("账号:",(char*)data,10,"C:\\niuniu2.log");
	return S_Encode_send(Socket,data);
		::WritePrivateProfileString("AUTO","2","2","c:\\ddd.ini");
}