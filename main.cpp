#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "resource.h"

//Global variables
HINSTANCE g_hInstance;
HWND g_hWnd;
int QueryLen;
char *QueryCaption, *QueryText, *QueryDst;


BOOL CALLBACK QueryDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			SetWindowText(hwndDlg, QueryCaption);
			SetDlgItemText(hwndDlg, IDC_QUERY_TEXT, QueryText);
			SetDlgItemText(hwndDlg, IDC_QUERY_EDIT, QueryDst);
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDOK:
				{
					GetWindowText(GetDlgItem(hwndDlg, IDC_QUERY_EDIT), QueryDst, QueryLen);
					EndDialog(hwndDlg, IDOK);
					return TRUE;
				}
			case IDCANCEL:
				{
					EndDialog(hwndDlg, IDCANCEL);
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

bool InputBox(char *caption, char *text, char *dst, int len)
{
	QueryCaption = caption;
	QueryText = text;
	QueryDst = dst;
	QueryLen = len;
	return (DialogBox(0, MAKEINTRESOURCE(IDD_DLG_QUERY), 0, QueryDlgProc) == IDOK);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		char caption[MAX_PATH];
		strcpy(caption, "caption text");

		if (InputBox("Set Caption", "Title:", caption, sizeof(caption)))
		{
			MessageBox(0, caption, caption, 0);
		}
		break;
	case WM_NOTIFY:
		break;
	case WM_COMMAND:
		break;
	case WM_PAINT:
		break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	case WM_SIZE:
		break;
	case WM_GETMINMAXINFO:
		{
			//Set window size constraints
			((MINMAXINFO *)lParam)->ptMinTrackSize.x = 500;
			((MINMAXINFO *)lParam)->ptMinTrackSize.y = 300;
			break;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Initialize global variables
	g_hInstance = GetModuleHandle(0);

	static char szClassName[] = "Console";
	static char szWindowName[] = "Console";

	//Define & register window class
	WNDCLASSEX WndClass;
	MSG msg;

	memset(&WndClass, 0, sizeof(WndClass));
	WndClass.cbSize = sizeof(WndClass);
	WndClass.lpszClassName = szClassName;
	WndClass.lpfnWndProc = WndProc;
	WndClass.hInstance = g_hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	WndClass.lpszMenuName = NULL;
	RegisterClassEx(&WndClass);

	//Create actual window
	g_hWnd = CreateWindowEx(WS_EX_WINDOWEDGE, szClassName, szWindowName, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 300, 0, 0, g_hInstance, 0);

	if (!g_hWnd)
	{
		return false;
	}

	while( GetMessage(&msg, NULL, 0, 0) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}