#ifndef _SHOOTSUNAPI_H_
#define _SHOOTSUNAPI_H_

static BYTE OldDefWindowProcRoutineA[32];
typedef LRESULT (WINAPI *OldDefWindowProcA)(
  //WNDPROC lpPrevWndFunc,  // pointer to previous procedure
  HWND hWnd,      // handle to window
  UINT Msg,       // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
);
static OldDefWindowProcA OldDefWindowProcAddressA = 
				(OldDefWindowProcA)&OldDefWindowProcRoutineA;


static BYTE OldCallWindowProcRoutineA[32];
typedef LRESULT (WINAPI *OldCallWindowProcA)(
  WNDPROC lpPrevWndFunc,  // pointer to previous procedure
  HWND hWnd,      // handle to window
  UINT Msg,       // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
);
static OldCallWindowProcA OldCallWindowProcAddressA = 
				(OldCallWindowProcA)&OldCallWindowProcRoutineA;

static BYTE OldrecvRoutine[32];
typedef int (WINAPI *Oldrecv)(
	SOCKET s,           
	char FAR *buf, 
	int len, 
	int flags        
);
static Oldrecv OldrecvAddress = 
				(Oldrecv)&OldrecvRoutine;

static BYTE OldSendRoutine[32];
typedef int (WINAPI *OldSend)(
	SOCKET s, 
	const char FAR *buf, 
	int len, 
	int flags );
static OldSend OldSendAddress = 
				(OldSend)&OldSendRoutine;


static BYTE OldconnectRoutine[32];
typedef int (WINAPI *Oldconnect)(
  SOCKET s,                          
  const struct sockaddr FAR *name,  
  int namelen                        
);
static Oldconnect OldconnectAddress = 
				(Oldconnect)&OldconnectRoutine;

static BYTE OldclosesocketRoutine[32];
typedef int (WINAPI *Oldclosesocket)(
  SOCKET s
);
static Oldclosesocket OldclosesocketAddress = 
				(Oldclosesocket)&OldclosesocketRoutine;

static BYTE OldshutdownRoutine[32];
typedef int (WINAPI *Oldshutdown)(
  SOCKET s, int how
);
static Oldshutdown OldshutdownAddress = 
				(Oldshutdown)&OldshutdownRoutine;

static BYTE OldGetLastErrorRoutine[32];
typedef BOOL (WINAPI *OldGetLastError)( );
static OldGetLastError OldGetLastErrorAddress = 
				(OldGetLastError)&OldGetLastErrorRoutine;


static BYTE OldExitProcessRoutine[32];
typedef BOOL (WINAPI *OldExitProcess)( UINT uExitCode );
static OldExitProcess OldExitProcessAddress = 
				(OldExitProcess)&OldExitProcessRoutine;

static BYTE OldSetTimerRoutine[32];
typedef UINT (WINAPI *OldSetTimer)(
    HWND hWnd ,
    UINT nIDEvent,
    UINT uElapse,
    TIMERPROC lpTimerFunc);
static OldSetTimer OldSetTimerAddress = 
				(OldSetTimer)&OldSetTimerRoutine;

static BYTE OldGetTickCountRoutine[32];
typedef DWORD (WINAPI *OldGetTickCount)( void );
static OldGetTickCount OldGetTickCountAddress = 
				(OldGetTickCount)&OldGetTickCountRoutine;

static BYTE OldQueryPerformanceCounterRoutine[32];
typedef BOOL (WINAPI *OldQueryPerformanceCounter)( LARGE_INTEGER *lpPerformanceCount );
static OldQueryPerformanceCounter OldQueryPerformanceCounterAddress = 
				(OldQueryPerformanceCounter)&OldQueryPerformanceCounterRoutine;

int WINAPI analysesend(SOCKET s, char *buf, int len);
int WINAPI analyserecv(SOCKET s, char *buf, int len);
void Encode_Decode(LPBYTE lpTarget, LPBYTE lpSource, WORD nLen);
void RegisterUser(LPBYTE lpTarget);
void SelectPlayerMode();
void UseSpell(BYTE Code1, BYTE Code2, BYTE data);   // 使用魔法
void AggressiveComputer();
BOOL TFGetXYAggressive();
void Aggressive(BYTE Code1, BYTE Code2);
void SetMeXY(BYTE _mode, BYTE oldx1, BYTE oldx2, BYTE oldy1, BYTE oldy2, BYTE newx1, BYTE newx2, BYTE newy1, BYTE newy2, BYTE mode);
void Encode_Recv(char *buf, int NowLen);
void TF(LPBYTE lpTarget, int nLen);
int TFCommand(char *buf, int len);              // 命令行控制
int TFPkData(char *buf, int nLen);
int TFOBJData(char *buf, int nLen);
void TFZipData(char* lpTarget, int NowLen);
void TFSpell(LPBYTE lpTarget);
void SendGameMessage(char *info, BYTE mode);
//NOVELITYSTATUS GetSite(BYTE Code1, BYTE Code2, int Mode);
void Sell(LPBYTE lpTarget, int nLen);
void GotoSite(BYTE Code1, BYTE Code2, BYTE Code3, BYTE Code4, BYTE Code5);
void Buy(BYTE NPC, int ha, int hb, int hc, int hd, int ba, int bb, int bc, int sb, int fc, int fh);
void DeleteDoor(char *buf, BYTE Number);
void OpenRepair(BYTE Code);
void OpenSell(BYTE Code);
void Repair(LPBYTE Mode, int Number);
void OpenFun(BYTE Code);
void OpenDrug(BYTE Code);
void Sell(LPBYTE Se, int Number);
void AutoSaveDoor(BYTE Code);
void AutoBank();
void AutoWeapon();
void AutoDrug();
void AutoAll();
void GotoSpellXY(BYTE Code1, BYTE Code2, int X, int Y);
void BankControl(LPBYTE lpTarget, int nLen);
void PutNovelityToBank(BYTE Code, int Number);
void SetToGameInfo(char tmp1[64], int Status);
char *GetMeNow(BYTE Code);
void GetNovelityFormBank(BYTE NPC, int Money, BYTE Code, int Number);
char *GetNovelitytName(BYTE Code1, BYTE Code2);
//STATUS GetDoorStatus(BYTE Code);
int GetNovelityStatus(BYTE Code1, BYTE Code2, int Score, BYTE Mode, BYTE Color);
void Speak(BYTE mode, char *buf);
void BuyWeapon(BYTE NPC, BYTE Code, int Number);
void Remedy(BYTE NPC, BYTE Code);
int TFPKOBJData(char *buf, int nLen);
void MoveMEXY();
int FindNextTarget();

void _SetGotSiteTimer(UINT nElapse);
void _KillGotoSiteTimer();
void _SpellSetTimer(UINT nElapse);
void _SpellKillTimer();
void _MainAggressiveSetTimer(UINT nElapse);
void _MainAggressiveKillTimer();
void _OtherAggressiveSetTimer(UINT nElapse);
void _OtherAggressiveKillTimer();
void _OtherSetTimer(UINT nElapse);
void _OtherBloodSetTimer(UINT nElapse);
void _OtherBloodKillTimer();
void _StayBloodSetTimer(UINT nElapse);
void _StayKillTimer();
void _TalkSetTimer(UINT nElapse);
void _TalkKillTimer();
void _MoveSetTimer(UINT nElapse);
void _MoveKillTimer();

void _BankSetTimer(UINT nElapse);
void _BankKillTimer();

void CALLBACK _BankTimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void CALLBACK _MoveTimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void CALLBACK _SpellTimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void CALLBACK _MainAggressiveTimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void CALLBACK _OtherAggressiveTimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void BloodControl();
void CALLBACK _TalkTimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void CALLBACK _OtherBloodTimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void CALLBACK _StayTimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void CALLBACK _GotoSiteTimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void CALLBACK _AuthenticationProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

void SubAutoSite(char *name);
void AddAutoSite();
void AddChum();
void Parse_Novelity(int a);
void UserNovelity(BYTE mode,BYTE now);//使用物品
void GetNovelity(int x, int y);

#endif