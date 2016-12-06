// Crypto1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Crypto1.h"
#include "encrypt.h"
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
#include <sstream>
#include <Mmsystem.h>
#include "OpenFileDialog.h"


//allow use of PlaySound
#pragma comment( lib, "winmm.lib" )

#define MAX_LOADSTRING 100
 
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Splash(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Encrypt(HWND, UINT, WPARAM, LPARAM);
TCHAR* GetFileToSaveEncryptedMsg(HWND hDlg) ;
INT_PTR CALLBACK	Decrypt(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

COLORREF BkgndColor = COLOR_WINDOWFRAME; // = COLOR_WINDOW + 1;
void ChangeBkgndColor(HWND hWnd);
void ChangeMusic(HWND hWnd);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	PlaySound(L".\\Music\\Mission Impossible.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CRYPTO1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CRYPTO1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CRYPTO1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_CRYPTO1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable
   //---------------------------------------------
	HWND hSplashWnd = CreateDialogParam(hInst,
								MAKEINTRESOURCE(IDD_SPLASH),
								NULL,
								NULL,
								NULL);
	ShowWindow(hSplashWnd, SW_NORMAL);
	UpdateWindow(hSplashWnd);
	Sleep(5000);
	ShowWindow(hSplashWnd, SW_HIDE);
   //---------------------------------------------
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_FILE_ENCRYPT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_Encrypt), hWnd, Encrypt);
			break;
		case IDM_FILE_DECRYPT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_Decrypt), hWnd, Decrypt);
			break;
		case ID_FILE_MUSIC:
			ChangeMusic(hWnd);
			break;
		case ID_FILE_BACKGROUNDCOLOR:
			ChangeBkgndColor(hWnd);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_ERASEBKGND:
		RECT rc;
         GetClientRect(hWnd, &rc);
         SetBkColor((HDC)wParam, BkgndColor); // user selected
         ExtTextOut((HDC)wParam, 0, 0, ETO_OPAQUE, &rc, 0, 0, 0);
         return 1;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for Splash box.
INT_PTR CALLBACK Splash(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	return (INT_PTR)FALSE;
}
// Message handler for Encrypt box.
LPCWSTR myLPCWSTRFileName = L"";

std::string myFileName;

INT_PTR CALLBACK Encrypt(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON_BROWSE)
		{
			//https:/msdn.microsoft.com/en-us/library/windows/desktop/ms646927(v=vs.85).aspx
			myLPCWSTRFileName = (LPCWSTR) GetFileToSaveEncryptedMsg(hDlg);
			std::wstring fpName = myLPCWSTRFileName;
			myFileName = std::string(fpName.begin(), fpName.end());

			SetDlgItemText(hDlg, IDC_EDIT_FILENAME, (LPCWSTR)myLPCWSTRFileName); 
			return (INT_PTR)TRUE;
		} 
		else if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			char szMsg[4096];
			char szFileName[4096];
			GetDlgItemText(hDlg,IDC_CryptoMessage,(LPWSTR)szMsg, 4096);		
			GetDlgItemText(hDlg,IDC_EDIT_FILENAME,(LPWSTR)szFileName, 4096);
			
			std::wstring wMsg = (LPWSTR)szMsg;
			std::string myMsg = std::string(wMsg.begin(), wMsg.end());
			
			vector<int> input;
			for (int i = 0; i < myMsg.size(); i++)
				input.push_back(int(myMsg[i]));

		   std::wstring fpName = (LPWSTR)szFileName;
            myFileName = std::string(fpName.begin(), fpName.end());
			encryptToFile(myFileName, input);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
// Message handler for Decrypt box.
INT_PTR CALLBACK Decrypt(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON_BROWSE)
		{
			//https:/msdn.microsoft.com/en-us/library/windows/desktop/ms646927(v=vs.85).aspx
			myLPCWSTRFileName = (LPCWSTR) GetFileToSaveEncryptedMsg(hDlg);
			std::wstring fpName = myLPCWSTRFileName;
			myFileName = std::string(fpName.begin(), fpName.end());

			SetDlgItemText(hDlg, IDC_EDIT_FILENAME, (LPCWSTR)myLPCWSTRFileName); 
			vector<char> decryptedData = decryptFromFile(myFileName);			
			string decryptedString(decryptedData.begin(), decryptedData.end());

			std::wstring stemp = std::wstring(decryptedString.begin(), decryptedString.end());
			LPCWSTR sw = stemp.c_str();

			SetDlgItemText(hDlg, IDC_CryptoMessage2, sw); 
			return (INT_PTR)TRUE;
		} else if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


TCHAR* GetFileToSaveEncryptedMsg(HWND hDlg) 
{
	OpenFileDialog* openFileDialog1 = new OpenFileDialog();
	openFileDialog1->FilterIndex = 1;
	openFileDialog1->Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;  //|= OFN_SHOWHELP;
	openFileDialog1->InitialDir = _T("C:\\");
	openFileDialog1->Title = _T("Encrypt to File");

	if (openFileDialog1->ShowDialog())
	{
		//MessageBox(0, openFileDialog1->FileName, _T("openFileDialog1"),
		//		   MB_OK | MB_ICONINFORMATION);
	}
	return openFileDialog1->FileName;
}

// https:/msdn.microsoft.com/en-us/library/windows/desktop/ms646829
void ChangeBkgndColor(HWND hWnd)
{
	CHOOSECOLOR cc;                 // common dialog box structure 
	static COLORREF acrCustClr[16]; // array of custom colors 
	HWND hwnd;                      // owner window
	HBRUSH hbrush;                  // brush handle
	static DWORD rgbCurrent;        // initial color selection

	// Initialize CHOOSECOLOR 
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hWnd;
	cc.lpCustColors = (LPDWORD) acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
 
	if (ChooseColor(&cc)==TRUE) 
	{
		//hbrush = CreateSolidBrush(cc.rgbResult);
		//rgbCurrent = cc.rgbResult; 

		BkgndColor  = cc.rgbResult;
		RECT rc;
        GetClientRect(hWnd, &rc);
		InvalidateRect (hWnd, &rc, TRUE);
		RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	}

}

void ChangeMusic(HWND hWnd) 
{
	PlaySound((LPCWSTR)GetFileToSaveEncryptedMsg(hWnd), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); //https:/msdn.microsoft.com/en-us/library/windows/desktop/dd743680(v=vs.85).aspx
}
