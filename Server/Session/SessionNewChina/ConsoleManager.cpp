///////////////////////////////////////////////////////////////////////////////
// Console Manager Impl.
//
#include "stdafx.h"
#include "Mcommon.h"
#include "SessionCom.h"

/* Color Definition */
#define BACKGROUND_WHITE  (WORD) 0x00f0
#define BACKGROUND_CYAN   (WORD) 0x0030
#define BACKGROUND_BLACK  (WORD) 0X0000
#define FOREGROUND_YELLOW (WORD) 0x0006
#define FOREGROUND_CYAN   (WORD) 0x0003
#define FOREGROUND_WHITE  (WORD) 0x000f
#define FOREGROUND_BLACK  (WORD) 0X0000

/* Rectangle of boundary*/
#define BOX_TOP 0
#define BOX_LEFT   0
#define BOX_BOTTOM 5
#define BOX_RIGHT  79


HANDLE hStdIn, hStdOut; 
/*indicate color setting of characters*/
int charColor  = BACKGROUND_GREEN|FOREGROUND_BLACK;
extern int NUMSTARTRESOURCES_USER;
extern int NUMSTARTRESOURCES_ROOM;
extern CSessionCom	*g_pCom;
extern TCHAR g_szAppName[];

void mputs(int x,int y,char* str)
{
	COORD dwWriteCoord = {x,y};
	DWORD cCharsWritten;
	/*Write string at dwWriteCoord*/
	WriteConsoleOutputCharacter(hStdOut, str, strlen(str),dwWriteCoord, &cCharsWritten);
	/*Set Foreground and Background Color of written string with saved Color Setting*/
    FillConsoleOutputAttribute(hStdOut,FOREGROUND_INTENSITY | charColor, strlen(str),
        dwWriteCoord, &cCharsWritten);
}

void DrawBox(int left,int top,int right,int bottom)
{
	int x;
	int y;
	for (x=left;x<=right;x=x+2)
		for (y=top;y<=bottom;y++) {
			if (x==left) {
				if (y==top) mputs(x,y,"¦£");
				else if (y==bottom) mputs(x,y,"¦¦");
				else mputs(x,y,"¦¢");
			}
			else if (x+1>=right) {
				if (y==top) mputs(x,y,"¦¤");
				else if (y==bottom)	mputs(x,y,"¦¥");
				else mputs(x,y,"¦¢");
			}
			else {
				if (y==top) mputs(x,y,"¦¡");
				else if (y==bottom) mputs(x,y,"¦¡");
				else mputs(x,y,"  ");
			}
		}
}

void SetColor(int tmp)
{
	charColor = tmp;
}

void cls()
{
  COORD coordScreen = { 0, 0 }; 
  BOOL bSuccess;
  DWORD cCharsWritten;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD dwConSize;

  /*set whole screen with blank character*/
  bSuccess = GetConsoleScreenBufferInfo(hStdOut, &csbi);
  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
  bSuccess = FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ',
      dwConSize, coordScreen, &cCharsWritten);

  /*fill color with original console setting*/
  bSuccess = GetConsoleScreenBufferInfo(hStdOut, &csbi);
  bSuccess = FillConsoleOutputAttribute(hStdOut, csbi.wAttributes,
      dwConSize, coordScreen, &cCharsWritten);

  /* move mouse postion to 0,0*/
  bSuccess = SetConsoleCursorPosition(hStdOut, coordScreen);
  return;
}

int console_main(void)
{
	OSVERSIONINFO osVer; 
	
	BOOL bSuccess;
	DWORD dwMode;
	CONSOLE_CURSOR_INFO cci;

	/*version Check - accept only windows family(except 3.1)*/
	osVer.dwOSVersionInfoSize = sizeof(osVer);
	bSuccess = GetVersionEx(&osVer);
	if (osVer.dwPlatformId == VER_PLATFORM_WIN32s)
	{
		printf("This program doesn't work non-win32 platform");
		return (1);
	}
	
	/* set title of console*/
	//
	CString capStr = "Session Server V1.0";
	CTime t = CTime::GetCurrentTime();
	CString osTime = t.Format("[%y/%m/%d]");
	capStr += osTime;
	//
	bSuccess = SetConsoleTitle(capStr);

	/* get the standard handles */
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdIn = GetStdHandle(STD_INPUT_HANDLE);

	/*clear screen*/
	cls();

	/*set up input 
	TURN_OFF  line_input
	TURN_ON   echo_input
	*/

	bSuccess = GetConsoleMode(hStdIn, &dwMode);
	
	bSuccess = SetConsoleMode(hStdIn, (dwMode & ~(ENABLE_LINE_INPUT |
		ENABLE_ECHO_INPUT))); 
	
	/*hide the cursor */
	cci.dwSize = 100;
	cci.bVisible = FALSE;
	bSuccess = SetConsoleCursorInfo(hStdOut, &cci);
	
	/*DISPLAY ORIGINAL SCREENS*/
	SetColor(BACKGROUND_BLACK|FOREGROUND_WHITE);
	DrawBox(BOX_LEFT,BOX_TOP,BOX_RIGHT,BOX_BOTTOM);

	char str_buf[255];
	sprintf(str_buf, "CONSOLE MODE");
	SetColor(BACKGROUND_BLACK|FOREGROUND_CYAN);
	mputs(2,1,str_buf);

	SetColor(BACKGROUND_BLACK|FOREGROUND_WHITE);
	sprintf(str_buf, "Title        : MAIN SERVER(%s)", g_szAppName);
	mputs(2,2,str_buf);
	sprintf(str_buf, "ISP NAME     : %s Session", g_pCom->m_strGameID);
	mputs(2,3,str_buf);

#ifdef _DEBUG
	sprintf(str_buf, "Running Mode : %s", "Debug Mode");
	mputs(2,4,str_buf);
#else if _CONSOLE
	sprintf(str_buf, "Running Mode : %s", "Release Mode");
	mputs(2,4,str_buf);
#endif

	sprintf(str_buf, "]Max User : %d", NUMSTARTRESOURCES_USER );
	mputs(1,7,str_buf);

	return 0;
}
