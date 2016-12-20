// KeyHooks.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "KeyHooks.h"
#include "windowsx.h"
#include "..\..\GainSunStaticLib\comfun.h"
#include "..\datafunc\common.h"
#include "resource.h"		// main symbols
#include "COMMCTRL.H"
#include "main.h"
#include "resource.h"		// main symbols

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#pragma data_seg ("shareddata")
HHOOK hKeyHook;
HHOOK hMsgHook;
HINSTANCE hInst;
//#pragma data_seg()
extern UIDATA	UIData;
extern CONFIG   Config;
extern GAMEDATA GameData;
//共享内存指针
extern HANDLE hMapFile;

int PoupDialog()
{
	
	ReadDataEx((LPSTR)&UIData, 0, sizeof(UIDATA));
	if( !UIData.GamehWnd )
		return 0;
//	SaveLog("PostMessage WM_POPUPMAIN",FILELOG);
	::SendMessage(UIData.GamehWnd,WM_POPUPMAIN,0,0);
	return 0;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	//if(((DWORD)lParam & 0x40000000) && (HC_ACTION == nCode));
	WORD wKey = (WORD)wParam;
	//键按下
	if ((HIWORD(lParam) & KF_UP) == 0 && HC_ACTION == nCode)
	{		
		if (wKey == VK_HOME)
		{ 
			PoupDialog();
			return 0;
		}

		if (wKey == VK_END)
		{
		//	::SendMessage(UIData.GamehWnd,WM_DEBUG,0,0);
			return 0;
		}
		if( GetKeyState(VK_CONTROL) & 0x8000 ){
			switch( wKey )
			{
				case VK_F1:
					::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG6,IDC_CHECK_START_AUTOPLAY,1);
					if (Button_GetCheck(GetDlgItem(UIData.hMainConfig[5], IDC_CHECK_START_AUTOPLAY)) == 0)
					{	
						Button_SetCheck(GetDlgItem(UIData.hMainConfig[5], IDC_CHECK_START_AUTOPLAY),2);
					}
					else
					{
					Button_SetCheck(GetDlgItem(UIData.hMainConfig[5], IDC_CHECK_START_AUTOPLAY),0);
					}
					break;
				case 0x31:
				//额外+血
				//	Button_SetCheck(GetDlgItem(UIData.hMainConfig[0], IDC_CHECK_OTHER_ADD_BLOOD),1);

					::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG1,IDC_CHECK_OTHER_ADD_BLOOD,1);
					if (Button_GetCheck(GetDlgItem(UIData.hMainConfig[0], IDC_CHECK_OTHER_ADD_BLOOD)) == 0)
					{	
					Button_SetCheck(GetDlgItem(UIData.hMainConfig[0], IDC_CHECK_OTHER_ADD_BLOOD),2);
					}
					else
					{
						Button_SetCheck(GetDlgItem(UIData.hMainConfig[0], IDC_CHECK_OTHER_ADD_BLOOD),0);
					}

					break;
				case 0x32:
				//锁定用户

					::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG1,IDC_CHECK_LOCK_TARGET,1);
					if (Button_GetCheck(GetDlgItem(UIData.hMainConfig[0], IDC_CHECK_LOCK_TARGET)) == 0)
					{	
						Button_SetCheck(GetDlgItem(UIData.hMainConfig[0], IDC_CHECK_LOCK_TARGET),2);

					}
					else
					{
						Button_SetCheck(GetDlgItem(UIData.hMainConfig[0], IDC_CHECK_LOCK_TARGET),0);
					}

					break;
				case 0x33:
					//修卖
					::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG7,IDC_BUTTON_AUTOWEAPON,0);
					break;
				case 0x34:
					//备药
					::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG7,IDC_BUTTON_AUTODRUG,0);
					break;
				case 0x35:
					//银行
					::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG7,IDC_BUTTON_AUTOBANK,0);
					break;
				case 0x36:
				//一键修买
				::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG7,IDC_BUTTON_AUTOALL,0);
				break;

			}

		}
	}
	
	
	LRESULT RetVal = CallNextHookEx(hKeyHook, nCode, wParam, lParam);
	return  RetVal;
}

LRESULT CALLBACK CallWndProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	/*if(HC_ACTION==nCode)
	{
		CWPSTRUCT * pCwpStruct= (CWPSTRUCT  *)lParam;
		if( pCwpStruct->message == WM_ACTIVATE )
		{
			ReadData();
			if( pCwpStruct->hwnd == UIData.GamehWnd )
			{
				//TCHAR temp[256];
				//wsprintf(temp,"pCwpStruct->message=0x%x",pCwpStruct->message);
				//SaveLog(temp,FILELOG);
				//if( !UIData.bInstallUI )
				//	InstallUI(NULL);
				//wsprintf(temp,"UIData.bInstallUI2 =0x%x",UIData.bInstallUI);
				//SaveLog(temp,FILELOG);
			}
		}
	}*/
	LRESULT RetVal = CallNextHookEx( hMsgHook, nCode, wParam, lParam );	
	return  RetVal;
}

BOOL _declspec(dllexport)__stdcall InstallHotKey( DWORD dwThreadId )
{
	SaveLog("InstallHotKey",FILELOG);
	ReadDataEx((LPSTR)&UIData, 0, sizeof(UIDATA));
	UIData.GameTheadID = dwThreadId;
	hKeyHook = SetWindowsHookEx(WH_KEYBOARD,(HOOKPROC)KeyboardProc, hInst, dwThreadId);
	hMsgHook = SetWindowsHookEx(WH_CALLWNDPROC,(HOOKPROC)CallWndProc, hInst, dwThreadId);
	WriteDataEx((LPSTR)&UIData, 0, sizeof(UIDATA));
	return true;
}

BOOL _declspec(dllexport)__stdcall UninstallHotKey( )
{
	SaveLog("UnInstallHotKey",FILELOG);
	UnhookWindowsHookEx(hKeyHook);
	UnhookWindowsHookEx(hMsgHook);
	return true;
}

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CKeyHooksApp

BEGIN_MESSAGE_MAP(CKeyHooksApp, CWinApp)
	//{{AFX_MSG_MAP(CKeyHooksApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyHooksApp construction

CKeyHooksApp::CKeyHooksApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CKeyHooksApp object

CKeyHooksApp theApp;

BOOL CKeyHooksApp::InitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	hInst = (HINSTANCE)AfxGetInstanceHandle();
	TCHAR temp[256];
	wsprintf(temp,"keyhooks dll load,inst=0x%x",hInst);
	SaveLog(temp,FILELOG);
	hMapFile = CreateMapFile();
//	InitalizeApplication(hInst);
	DWORD CurID = GetCurrentThreadId();
	ReadDataEx((LPSTR)&UIData, 0, sizeof(UIDATA));
	if( UIData.GameTheadID == CurID )
	{
		if( !UIData.bInstallUI )
			InstallUI(NULL);
		wsprintf(temp,"InitInstance UIData.hMain = 0x%x",UIData.hMain);
		SaveLog(temp,FILELOG);
	}
	WriteDataEx((LPSTR)&UIData, 0, sizeof(UIDATA));
	//WriteData();
	wsprintf(temp,"GetCurrentThreadId=0x%x,GameTheadID = 0x%x",CurID,UIData.GameTheadID);
	SaveLog(temp,FILELOG);
	return CWinApp::InitInstance();
}

int CKeyHooksApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
//	UninstallHotKey();
	CloseHandle( hMapFile );
	return CWinApp::ExitInstance();
}
