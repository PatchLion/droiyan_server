#include "stdafx.h"
#include "Keyhooks.h"
#include "main.h"
#include "..\..\GainSunStaticLib\comfun.h"
#include "..\datafunc\common.h"
#include "windowsx.h"
#include "resource.h"

extern HINSTANCE hInst;
extern UIDATA	 UIData;
extern CONFIG    Config;
extern GAMEDATA  GameData;

static int nMainLeftButtonX, nMainLeftButtonY;
static int nMainOldWindowX, nMainOldWindowY;
static int nMainDragX, nMainDragY;

static int nFriendLeftButtonX, nFriendLeftButtonY;
static int nFriendOldWindowX, nFriendOldWindowY;
static int nFriendDragX, nFriendDragY;



BOOL InstallUI(HWND hParent)
{

	HWND hTemp = GetFocus();
	//ReadData();
	//ZeroMemory(&Config,sizeof(CONFIG));
	//ZeroMemory(&GameData,sizeof(GameData));
	//ZeroMemory(&UIData,sizeof(UIDATA));
	//AfxGetInstanceHandle();
	UIData.hMain              = CreateDialog(hInst, MAKEINTRESOURCE(IDD_MAIN_CONFIG), NULL, (DLGPROC)MainDialogProc);	
//	UIData.hMainConfig_Play   = CreateDialog(hInst, MAKEINTRESOURCE(IDD_AUTOPLAY), NULL, (DLGPROC)PlayDialogProc);
//	UIData.hDebug             = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DLG_DATA), NULL, (DLGPROC)DisPlayDialogProc);

//	SetWindowPos(UIData.hDebug, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);


	SetWindowPos(UIData.hMain, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

	//ShowWindow(UIData.hMain, SW_SHOW);
	ShowWindow(UIData.hMain, SW_HIDE);

	//ShowWindow(UIData.hFriend, SW_SHOW);
//	ShowWindow(UIData.hDebug, SW_HIDE);

	UIData.ShowMainDialog = FALSE;

//	UIData.ShowDebugDialog = FALSE;
	UIData.bInstallUI = TRUE;
//	ShowCursor(TRUE);
	//WriteData();
	SetFocus(hTemp);

	return TRUE;
}

BOOL CALLBACK DataDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}


BOOL CALLBACK Form9_1Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char tmp[10];
	LV_COLUMN LvCol;	
	HWND hList;

    switch (uMsg)
    {
	
	    case WM_CREATE:

			return TRUE;

        case WM_INITDIALOG:

			hList = GetDlgItem(hWnd, IDC_LIST_9_1_1);

			memset(&LvCol, 0, sizeof(LvCol));

			LvCol.fmt = LVCFMT_LEFT;


			LvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

			LvCol.fmt = LVCFMT_LEFT;
			LvCol.cx = 40;
			LvCol.pszText = "类型";
			SendMessage(hList, LVM_INSERTCOLUMN, 0, (LPARAM)&LvCol);
	
			LvCol.cx = 115;
			LvCol.pszText = "名称";
			SendMessage(hList, LVM_INSERTCOLUMN, 1, (LPARAM)&LvCol);

			LvCol.cx = 85;
			LvCol.pszText = "坐标";
			SendMessage(hList, LVM_INSERTCOLUMN, 2, (LPARAM)&LvCol);

			SendMessage(hList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_9_1_1), "兰色");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_9_1_1), "黄色");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_9_1_1), "紫色");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_9_1_1), "红色");

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG9_1,wParam,lParam);			
            return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form9_2Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LV_COLUMN LvCol;	
	HWND hList;

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:
			hList = GetDlgItem(hWnd, IDC_LIST_9_2_1);

			memset(&LvCol, 0, sizeof(LvCol));

			LvCol.fmt = LVCFMT_LEFT;

			LvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

			LvCol.fmt = LVCFMT_LEFT;
			LvCol.cx = 80;
			LvCol.pszText = "名称";
			SendMessage(hList, LVM_INSERTCOLUMN, 0, (LPARAM)&LvCol);
	
			LvCol.cx = 160;
			LvCol.pszText = "内容";
			SendMessage(hList, LVM_INSERTCOLUMN, 1, (LPARAM)&LvCol);

			SendMessage(hList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG9_2,wParam,lParam);
				
            return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form9_3Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
//	char tmp[10];

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG9_3,wParam,lParam);
				
            return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form9_4Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
//	char tmp[10];

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG9_4,wParam,lParam);
				
            return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form9Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	HWND hWC;

    switch (uMsg)
    {
	
	    case WM_CREATE:

			return TRUE;

        case WM_INITDIALOG:

			hWC = GetDlgItem(hWnd, IDC_9_PAGE);

		//	UIData.hMainConfig9_1 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG9_1), hWC, (DLGPROC)Form9_1Proc);
		//	UIData.hMainConfig9_2 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG9_2), hWC, (DLGPROC)Form9_2Proc);
		//	UIData.hMainConfig9_3 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG9_3), hWC, (DLGPROC)Form9_3Proc);
		//	UIData.hMainConfig9_4 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG9_4), hWC, (DLGPROC)Form9_4Proc);

            return TRUE;

		case WM_SHOWWINDOW:

			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG9,wParam,lParam);	
            return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form8_1Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char tmp[10];

	switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;

        case WM_COMMAND:			
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG8_1, wParam,lParam);
            return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form8_2Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char tmp[10];

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG8_2, wParam,lParam);
            return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form8_3Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG8_3, wParam,lParam);			
            return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form8Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hWC;

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:

			hWC = GetDlgItem(hWnd, IDC_8_PAGE);

		//	UIData.hMainConfig8_1 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG8_1), hWC, (DLGPROC)Form8_1Proc);
		//	UIData.hMainConfig8_2 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG8_2), hWC, (DLGPROC)Form8_2Proc);
		//	UIData.hMainConfig8_3 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG8_3), hWC, (DLGPROC)Form8_3Proc);

            return TRUE;

		case WM_SHOWWINDOW:

			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG8, wParam,lParam);				
            return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form7Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
//	char tmp[10];

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:



            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG7, wParam,lParam);		
            return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form6Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hWC;

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:

			hWC = GetDlgItem(hWnd, IDC_6_PAGE);

	//		UIData.hMainConfig6_1 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG6_1), hWC, (DLGPROC)Form6_1Proc);
	//		UIData.hMainConfig6_2 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG6_2), hWC, (DLGPROC)Form6_2Proc);
            return TRUE;

		case WM_SHOWWINDOW:

			return TRUE;
		case WM_NOTIFY:
            ::PostMessage(UIData.GamehWnd,WM_NOTIFYCONFIG6,wParam,lParam);
			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG6, wParam,lParam);
            return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form6_1Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	LV_COLUMN LvCol;	
	HWND hList;
	char tmp[10];
	LONG t1;
	
	switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:
            // 危险指数为8个等级 依次是很低到很高
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_6_1_2), "0");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_6_1_2), "1");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_6_1_2), "2");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_6_1_2), "3");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_6_1_2), "4");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_6_1_2), "5");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_6_1_2), "6");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_6_1_2), "7");

			hList = GetDlgItem(hWnd, IDC_LIST_6_1_1);

			memset(&LvCol, 0, sizeof(LvCol));

			LvCol.fmt = LVCFMT_LEFT;


			LvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

			LvCol.fmt = LVCFMT_LEFT;
			LvCol.cx = 50;
			LvCol.pszText = "时间";
			SendMessage(hList, LVM_INSERTCOLUMN, 0, (LPARAM)&LvCol);
	

			LvCol.cx = 120;
			LvCol.pszText = "地点名称";
			SendMessage(hList, LVM_INSERTCOLUMN, 1, (LPARAM)&LvCol);

			LvCol.cx = 80;
			LvCol.pszText = "范围";
			SendMessage(hList, LVM_INSERTCOLUMN, 2, (LPARAM)&LvCol);

			SendMessage(hList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;

		case WM_NOTIFY:
            ::PostMessage(UIData.GamehWnd,WM_NOTIFYCONFIG6,wParam,lParam);
			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG6_1, wParam,lParam);
            return FALSE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form6_2Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
//	char tmp[10];

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;
        case WM_COMMAND:

			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG6_2, wParam,lParam);
			return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form5Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hWC;
    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:

			hWC = GetDlgItem(hWnd, IDC_5_PAGE);

		//	UIData.hMainConfig5_1 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG5_1), hWC, (DLGPROC)Form5_1Proc);
		//	UIData.hMainConfig5_2 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG5_2), hWC, (DLGPROC)Form5_2Proc);
		//	UIData.hMainConfig5_3 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG5_3), hWC, (DLGPROC)Form5_3Proc);

            return TRUE;

		case WM_SHOWWINDOW:

			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG5, wParam,lParam);

            return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;


}

BOOL CALLBACK Form5_1Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LV_COLUMN LvCol;	
	HWND hList;

	char tmp[10];
	LONG t1;

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:

			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_5_1_1), "友人");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_5_1_1), "友团");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_5_1_1), "敌人");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_5_1_1), "敌团");


			hList = GetDlgItem(hWnd, IDC_LIST_5_1_1);

			memset(&LvCol, 0, sizeof(LvCol));

			LvCol.fmt = LVCFMT_LEFT;


			LvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

			LvCol.fmt = LVCFMT_LEFT;
			LvCol.cx = 60;
			LvCol.pszText = "类型模式";
			SendMessage(hList, LVM_INSERTCOLUMN, 0, (LPARAM)&LvCol);
	

			LvCol.cx = 140;
			LvCol.pszText = "名称";
			SendMessage(hList, LVM_INSERTCOLUMN, 1, (LPARAM)&LvCol);

			LvCol.cx = 60;
			LvCol.pszText = "自动组队";
			SendMessage(hList, LVM_INSERTCOLUMN, 2, (LPARAM)&LvCol);

			SendMessage(hList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;
		case WM_NOTIFY:
            ::PostMessage(UIData.GamehWnd,WM_NOTIFYCONFIG5,wParam,lParam);
			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG5_1, wParam,lParam);
            return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form5_2Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
//	char tmp[10];

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;
        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG5_2, wParam,lParam);
			return TRUE;
        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form5_3Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
//	char tmp[10];

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;
        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG5_3, wParam,lParam);
			return TRUE;
        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form4_1Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LV_COLUMN LvCol;
	HWND hList;

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:

			hList = GetDlgItem(hWnd, IDC_LIST_4_1_1);

			memset(&LvCol, 0, sizeof(LvCol));

			LvCol.fmt = LVCFMT_LEFT;

			LvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

			LvCol.fmt = LVCFMT_LEFT;
			LvCol.cx = 40;
			LvCol.pszText = "位置";
			SendMessage(hList, LVM_INSERTCOLUMN, 0, (LPARAM)&LvCol);
	
			LvCol.cx = 100;
			LvCol.pszText = "名称";
			SendMessage(hList, LVM_INSERTCOLUMN, 1, (LPARAM)&LvCol);

			LvCol.cx = 50;
			LvCol.pszText = "数量";
			SendMessage(hList, LVM_INSERTCOLUMN, 2, (LPARAM)&LvCol);

			LvCol.cx = 60;
			LvCol.pszText = "耐久";
			SendMessage(hList, LVM_INSERTCOLUMN, 3, (LPARAM)&LvCol);

			SendMessage(hList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_4_1_1), "私人银行");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_4_1_1), "综合银行");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_4_1_1), "随身物品");

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG4_1, wParam,lParam);		
            return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form4_2Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LV_COLUMN LvCol;
	HWND hList;

	char tmp[128]; LONG t1;

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:
			hList = GetDlgItem(hWnd, IDC_LIST_4_2_1);

			memset(&LvCol, 0, sizeof(LvCol));

			LvCol.fmt = LVCFMT_LEFT;

			LvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

			LvCol.fmt = LVCFMT_LEFT;
			LvCol.cx = 160;
			LvCol.pszText = "名称";
			SendMessage(hList, LVM_INSERTCOLUMN, 0, (LPARAM)&LvCol);
	
			LvCol.cx = 80;
			LvCol.pszText = "处理方式";
			SendMessage(hList, LVM_INSERTCOLUMN, 1, (LPARAM)&LvCol);

			SendMessage(hList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_4_2_2), "保留装备");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_4_2_2), "卖掉装备");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_4_2_2), "强制拾取");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_4_2_2), "不拾取");

			SendDlgItemMessage(hWnd, IDC_COMBO_4_2_2, CB_SETCURSEL, 0, 0);

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG4_2, wParam,lParam);			
            return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form4_3Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	LV_COLUMN LvCol;
	HWND hList;

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:

			hList = GetDlgItem(hWnd, IDC_LIST_4_3_1);

			memset(&LvCol, 0, sizeof(LvCol));

			LvCol.fmt = LVCFMT_LEFT;

			LvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

			LvCol.fmt = LVCFMT_LEFT;
			LvCol.cx = 40;
			LvCol.pszText = "位置";
			SendMessage(hList, LVM_INSERTCOLUMN, 0, (LPARAM)&LvCol);
	
			LvCol.cx = 100;
			LvCol.pszText = "名称";
			SendMessage(hList, LVM_INSERTCOLUMN, 1, (LPARAM)&LvCol);

			LvCol.cx = 50;
			LvCol.pszText = "数量";
			SendMessage(hList, LVM_INSERTCOLUMN, 2, (LPARAM)&LvCol);

			LvCol.cx = 60;
			LvCol.pszText = "处理方式";
			SendMessage(hList, LVM_INSERTCOLUMN, 3, (LPARAM)&LvCol);

			SendMessage(hList, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);


			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_4_3_1), "开启");
			ComboBox_AddString(GetDlgItem(hWnd, IDC_COMBO_4_3_1), "关闭");

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;
        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG4_3, wParam,lParam);
			return TRUE;
        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form4_4Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
//	char tmp[10];

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;
        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG4_4, wParam,lParam);
			return TRUE;
        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form4Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hWC;

    switch (uMsg)
    {	
	    case WM_CREATE:

			return TRUE;

        case WM_INITDIALOG:

			hWC = GetDlgItem(hWnd, IDC_4_PAGE);

//			UIData.hMainConfig4_1 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG4_1), hWC, (DLGPROC)Form4_1Proc);
//			UIData.hMainConfig4_2 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG4_2), hWC, (DLGPROC)Form4_2Proc);
//			UIData.hMainConfig4_3 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG4_3), hWC, (DLGPROC)Form4_3Proc);
//			UIData.hMainConfig4_4 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG4_4), hWC, (DLGPROC)Form4_4Proc);

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG4, wParam,lParam);
            return TRUE; 
        case WM_DESTROY:
            return TRUE;
    }
 
    return FALSE;

}

BOOL CALLBACK Form3Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hWC;

    switch (uMsg)
    {	
	    case WM_CREATE:

			return TRUE;

        case WM_INITDIALOG:

			hWC = GetDlgItem(hWnd, IDC_3_PAGE);

			UIData.hMainConfig3_1 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG3_1), hWC, (DLGPROC)Form3_1Proc);
			UIData.hMainConfig3_2 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG3_2), hWC, (DLGPROC)Form3_2Proc);

            return TRUE;

		case WM_SHOWWINDOW:

			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG3, wParam,lParam);
            return TRUE; 
        case WM_DESTROY:
            return TRUE;
    }
 
    return FALSE;
}

BOOL CALLBACK Form3_1Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char tmp[10];
	char tmp1[255];

    switch (uMsg)
    {
	    case WM_CREATE:
			return TRUE;

        case WM_INITDIALOG:

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG3_1, wParam,lParam);
			return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;
}

BOOL CALLBACK Form3_2Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
	    case WM_CREATE:
			return TRUE;

        case WM_INITDIALOG:

            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;

        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG3_2, wParam,lParam);
			return TRUE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;
}

BOOL CALLBACK Form2Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:
            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;

		case WM_NOTIFY:


			return FALSE;

        case WM_COMMAND:
			if( HIWORD(wParam) == CBN_SELENDOK || HIWORD(wParam) == CBN_SELCHANGE || HIWORD(wParam) == CBN_CLOSEUP)
				SetFocus(UIData.hMainConfig[0]);
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG2, wParam,lParam);
            return FALSE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK Form1Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CSliderCtrl *m_Slider1, *m_Slider2;
	m_Slider1 = (CSliderCtrl *)(CWnd::FromHandle(GetDlgItem(hWnd, IDC_SLIDER_GAME_SPEED)));
	m_Slider2 = (CSliderCtrl *)(CWnd::FromHandle(GetDlgItem(hWnd, IDC_SLIDER_ATTACK_SPEED)));
	char ctemp[256], temp[256];
    switch (uMsg)
    {
	    case WM_CREATE:
			return TRUE;
        case WM_INITDIALOG:	
			m_Slider1->SetRange(0,6);
			m_Slider1->SetPos(0);
			m_Slider1->SetLineSize(6);
			m_Slider1->SetPageSize(6);

			m_Slider2->SetRange(1,20);
			m_Slider2->SetPos(1);
			m_Slider2->SetLineSize(17);
			m_Slider2->SetPageSize(17);

		//	Static_SetText(GetDlgItem(hWnd, IDC_STATIC_SPEEDER), "1.0倍");
		//	Static_SetText(GetDlgItem(hWnd, IDC_STATIC_ATTACK), "0.3秒");


            return TRUE;

		case WM_COMMON_SPEED1:

			m_Slider1->SetPos(Config.Speed1);

			Config.m_nGameSpeeder = Config.Speed1 + 1;

			if (Config.Speed1 == 0)
				sprintf(ctemp,"正常");
			else
				sprintf(ctemp,"%0.1f倍",(float(Config.Speed1))*0.5 + 1);
			
				
			Static_SetText(GetDlgItem(hWnd, IDC_STATIC_SPEEDER), ctemp);
			SetFocus(hWnd);

			SendMessage(UIData.GamehWnd, WM_NOTIFYCONFIG1, 0, Config.Speed1);

			return TRUE;

		case WM_COMMON_SPEED2:
			m_Slider2->SetPos(Config.Speed2);

//	        _MainAggressiveKillTimer();
//		    _MainAggressiveSetTimer(Config.Speed2 * 100);

			sprintf(ctemp,"%0.1f秒",(float(Config.Speed2))*0.1);
			Static_SetText(GetDlgItem(hWnd, IDC_STATIC_ATTACK), ctemp);
			SetFocus(hWnd);
			return TRUE;

		case WM_SHOWWINDOW:

			return TRUE;
		case WM_NOTIFY :
			if( wParam == IDC_SLIDER_GAME_SPEED )
			{
				NMHDR* pNMHDR = (NMHDR*)lParam;
				if( pNMHDR->code == NM_RELEASEDCAPTURE )
				{
					//ReadDataEx((LPSTR)&Config, sizeof(UIDATA), sizeof(Config));
					int nPos = m_Slider1->GetPos();

	            	Config.Speed1 = nPos;

					Config.m_nGameSpeeder = nPos + 1;

					if (Config.Speed1 == 0)
						sprintf(ctemp,"正常");
					//Config.m_nGameSpeeder = nPos + 1;
					//Config.bSpeedChanged = TRUE;
					//WriteDataEx((LPSTR)&Config, sizeof(UIDATA), sizeof(Config));
					else
						sprintf(ctemp,"%0.1f倍",(float(nPos))*0.5+1);

					Static_SetText(GetDlgItem(hWnd, IDC_STATIC_SPEEDER), ctemp);

					SendMessage(UIData.GamehWnd, WM_NOTIFYCONFIG1, 0, Config.Speed1);

					sprintf(temp,"游戏速度调整 %s", ctemp);

//					SetToGameInfo(temp, 3);

					SetFocus(hWnd);
				}
			}

			if( wParam == IDC_SLIDER_ATTACK_SPEED )
			{
				NMHDR* pNMHDR = (NMHDR*)lParam;
				if( pNMHDR->code == NM_RELEASEDCAPTURE )
				{
					//ReadDataEx((LPSTR)&Config, sizeof(UIDATA), sizeof(Config));
					int nPos = m_Slider2->GetPos();
		            Config.Speed2 = nPos;
	 //           	_MainAggressiveKillTimer();
	 //	            _MainAggressiveSetTimer(nPos * 100);
					//Config.m_nGameSpeeder = nPos + 1;
					//Config.bSpeedChanged = TRUE;
					//WriteDataEx((LPSTR)&Config, sizeof(UIDATA), sizeof(Config));
					sprintf(ctemp,"%0.1f秒",(float(nPos))*0.1);
					Static_SetText(GetDlgItem(hWnd, IDC_STATIC_ATTACK), ctemp);

					sprintf(temp,"攻击速度调整 %s", ctemp);

//					SetToGameInfo(temp, 3);

					SetFocus(hWnd);
				}
			}
			return TRUE;
        case WM_COMMAND:
			::PostMessage(UIData.GamehWnd,WM_COMMONDCONFIG1, wParam,lParam);
	
			return TRUE;
        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK MainDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hWC;
	TCITEM tcI;
	switch (uMsg)
    {
		//HANDLE_MSG(hWnd, WM_CREATE,			OnMainCreate);
		//HANDLE_MSG(hWnd, WM_MOUSEMOVE,		OnMainMouseMove);
		//HANDLE_MSG(hWnd, WM_LBUTTONDOWN,	OnMainLButtonDown);
        case WM_INITDIALOG:
			ReadDataEx((LPSTR)&UIData, 0, sizeof(UIDATA));
			//TCHAR sztemp[256];
			
			hWC = GetDlgItem(hWnd, IDC_MAIN_TAB);

			tcI.mask = TCIF_TEXT;
			tcI.pszText = "基本";
			

			TabCtrl_InsertItem(hWC, 0, &tcI);

	//		tcI.mask = TCIF_TEXT;
	//		tcI.pszText = "位置";

	//		TabCtrl_InsertItem(hWC, 1, &tcI);

			tcI.mask = TCIF_TEXT;
			tcI.pszText = "聊天";

			TabCtrl_InsertItem(hWC, 2, &tcI);

		//	tcI.mask = TCIF_TEXT;
		//	tcI.pszText = "物品";

		//	TabCtrl_InsertItem(hWC, 3, &tcI);

		//	tcI.mask = TCIF_TEXT;
		//	tcI.pszText = "组队";

		//	TabCtrl_InsertItem(hWC, 4, &tcI);

		//	tcI.mask = TCIF_TEXT;
		//	tcI.pszText = "挂机";

		//	TabCtrl_InsertItem(hWC, 5, &tcI);

		//	tcI.mask = TCIF_TEXT;
		//	tcI.pszText = "快捷";

		//	TabCtrl_InsertItem(hWC, 6, &tcI);

	//		tcI.mask = TCIF_TEXT;
		//	tcI.pszText = "设置";

	//		TabCtrl_InsertItem(hWC, 7, &tcI);

	//		tcI.mask = TCIF_TEXT;
	//		tcI.pszText = "信息";

	//		TabCtrl_InsertItem(hWC, 8, &tcI);


			hWC = GetDlgItem(hWnd, IDC_MAIN_PAGE);

			UIData.hMainConfig[0] = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG1), hWC, (DLGPROC)Form1Proc);
			UIData.hMainConfig[1] = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG3), hWC, (DLGPROC)Form3Proc);
		//	UIData.hMainConfig[2] = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG3), hWC, (DLGPROC)Form3Proc);
		//	UIData.hMainConfig[3] = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG4), hWC, (DLGPROC)Form4Proc);
		//	UIData.hMainConfig[4] = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG5), hWC, (DLGPROC)Form5Proc);
		//	UIData.hMainConfig[5] = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG6), hWC, (DLGPROC)Form6Proc);
		//	UIData.hMainConfig[6] = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG7), hWC, (DLGPROC)Form7Proc);
		//	UIData.hMainConfig[7] = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG8), hWC, (DLGPROC)Form8Proc);
		//	UIData.hMainConfig[8] = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONFIG9), hWC, (DLGPROC)Form9Proc);

			InstallTab(0);
			TCHAR cTemp[256];
			wsprintf(cTemp,"MainDialogProc UIData.hMainConfig[0]=0x%x",UIData.hMainConfig[0]);
			SaveLog(cTemp,FILELOG);
			//UIData.hMain = hWnd;
			//UIData.bInstallUI = TRUE;
			WriteDataEx((LPSTR)&UIData, 0, sizeof(UIDATA));
            return TRUE;
		case WM_SHOWWINDOW:

			return TRUE;

		case WM_NOTIFY:
			switch (wParam) {
				case IDC_MAIN_TAB:
					hWC = GetDlgItem(hWnd, IDC_MAIN_TAB);
					InstallTab(TabCtrl_GetCurSel(hWC));


					return TRUE;
			}
			return FALSE;

        case WM_COMMAND:
	
            return TRUE;
		case WM_CLOSE:
		//	::PostMessage(UIData.GamehWnd,WM_POPUPMAIN,0,0);
			ReadDataEx((LPSTR)&UIData, 0, sizeof(UIDATA));
	
			ShowWindow(UIData.hMain, SW_HIDE);

			UIData.ShowMainDialog = FALSE;
			WriteDataEx((LPSTR)&UIData, 0, sizeof(UIDATA));

			return TRUE;
        case WM_DESTROY:


            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK DisPlayDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:
            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;

		case WM_NOTIFY:


			return FALSE;

        case WM_COMMAND:

	//		::PostMessage(UIData.GamehWnd,WM_COMMONDEBUG,wParam,lParam);

            return FALSE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}

BOOL CALLBACK PlayDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch (uMsg)
    {
	
	    case WM_CREATE:


			return TRUE;

        case WM_INITDIALOG:
            return TRUE;


		case WM_SHOWWINDOW:

			return TRUE;

		case WM_NOTIFY:


			return FALSE;

        case WM_COMMAND:

//			::PostMessage(UIData.GamehWnd,WM_COMMONDEBUG,wParam,lParam);

            return FALSE;

        case WM_DESTROY:
            return TRUE;
    }

    return FALSE;

}
/*
void InstallTab(int index)
{
	for(int i = 0 ;i<TABNUMBER;i++)
	{
		if( i == index )
			ShowWindow(UIData.hMainConfig[i],SW_SHOW );
		else
			ShowWindow(UIData.hMainConfig[i],SW_HIDE );
	}
}
*/
// 主窗体事件
static int OnMainLButtonDown(HWND, BOOL, int x, int y, UINT)
{
	RECT clientRect;
	GetWindowRect(UIData.hMain, &clientRect);
		
	nMainOldWindowX = clientRect.left;
	nMainOldWindowY = clientRect.top;

	nMainLeftButtonX = clientRect.left + x;
	nMainLeftButtonY = clientRect.top + y;

	return 0;
}

static int OnMainMouseMove(HWND, int x, int y, UINT keyIndicators)
{
	if (keyIndicators == MK_LBUTTON) {
		RECT clientRect;

		GetWindowRect(UIData.hMain, &clientRect);
		
		if ((nMainLeftButtonX - (clientRect.left + x)) < nMainDragX && (nMainLeftButtonX - (clientRect.left + x)) > -nMainDragX && (nMainLeftButtonY - (clientRect.top + y)) < nMainDragY && (nMainLeftButtonY - (clientRect.top + y)) > - nMainDragY) {
			SetWindowPos(UIData.hMain, NULL, nMainOldWindowX, nMainOldWindowY, 0, 0, SWP_NOREPOSITION | SWP_NOSIZE);		
		} else {
			int nNewX = nMainOldWindowX - (nMainLeftButtonX - (clientRect.left + x));
			int nNewY = nMainOldWindowY - (nMainLeftButtonY - (clientRect.top + y));
			
			SetWindowPos(UIData.hMain, NULL, nNewX, nNewY, 0, 0, SWP_NOREPOSITION | SWP_NOSIZE);
		}

		return 0;
	}
	return 1;
}

static int OnMainCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)	// HWND hwnd, LPCREATESTRUCT lpCreateStruct
{
	return 1;
}
