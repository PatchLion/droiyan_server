#pragma once

class Encode
{
public:
	Encode(void);
public:
	~Encode(void);
public:
	SOCKET Socket;
	BOOL con;
	void S_Encode_Decode(char *lpTarget, char * lpSource, int nLen);
	int S_Encode_send(SOCKET s,char *data);
	int S_Encode_recv(SOCKET s,char *data);
	BOOL connect_Server();
	int Send_User(char *name,int len);
	int Time;
};
/*****************************************
封包格式  长度 200字节
FF 88  开头
88 FF  结尾
从第47个字节开存储数据到87字节结束 数据区
从第97字到107字节是   加密KEY存放区
其它字节随机产生

数据区：1个字节表示 封包类型
客户端：
0x11: 注册账号 +账号长度 + 账号 + 使用时间 （8位节）
0x22：验证用户名 +账号长度 + 账号
0x33：重设置用户名使用时间  +账号长度 + 账号 + 使用时间 （8位节）
服务端
0xEE 验证成功  + 到期时间
0xDD 验证失败
0xBB 操作成功
0xAA 操作失败
******************************************/