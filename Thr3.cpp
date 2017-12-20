// Thr3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
//#include "windowsx.h"
#define MAX_LOADSTRING 100
//Look into Windowsx.h for System definitions without the prefix R
#define RHANDLE_MSG(hwnd, message, fn)    \
    case (message): return RHANDLE_##message((hwnd), (wParam), (lParam), (fn))

#define RHANDLE_WM_COMMAND(hwnd, wParam, lParam, fn) \
    ((fn)((hwnd), (int)(LOWORD(wParam)), (HWND)(lParam), (UINT)HIWORD(wParam)), -1L)

#define RHANDLE_WM_INITDIALOG(hwnd, wParam, lParam, fn) \
    (LRESULT)(DWORD)(UINT)(BOOL)(fn)((hwnd), (HWND)(wParam), lParam)

#define RFORWARD_WM_COMMAND(hwnd, id, hwndCtl, codeNotify, fn) \
    (LONG)(fn)((hwnd), WM_COMMAND, MAKEWPARAM((UINT)(id),(UINT)(codeNotify)), (LPARAM)(HWND)(hwndCtl))


//Globals to control threads
HANDLE hThreadE[1];
CRITICAL_SECTION cs;

BOOL fTerminateC;


bool bSuspendC;
CRITICAL_SECTION csDC;

unsigned thridC;		//thread identifier

DWORD counter = 2;
DWORD primeNumber = 2;     

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// The title bar text

void TerminateCalculation(HWND hWnd, HMENU hMenu, BOOL *fTerminateE);

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);

//_stdcall for CALLBACK (see Windef.h)
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);



void SuspendCalculation(HMENU hMenu, bool *bSuspend, HWND hWnd);

unsigned int __stdcall  Calculate(void *hWnd);

LONG WndProc_OnCreate(HWND hWnd,LPCREATESTRUCT lpCreateStruct);
LONG WndProc_OnDestroy(HWND hWnd);
void WndProc_OnPaint(HWND hWnd);
LONG WndProc_OnCommand (HWND hWnd,int id,HWND hwndCtl,UINT codeNotify);
void WndProc_OnClose(HWND hWnd);




//_stdcall for APIENTRY (see Windef.h), used for new and last versions
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)

{

	// инициализируем критическую секцию  
	InitializeCriticalSection(&cs); 


 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_THR3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_THR3);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_THR3);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_THR3;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
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
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
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
//	int wmId, wmEvent;
	switch (message) 
	{
		HANDLE_MSG(hWnd,WM_COMMAND,WndProc_OnCommand);//!
		HANDLE_MSG(hWnd,WM_CREATE,WndProc_OnCreate);//!
		HANDLE_MSG(hWnd,WM_DESTROY,WndProc_OnDestroy);//!
        HANDLE_MSG(hWnd,WM_CLOSE,WndProc_OnClose);//!
		default:return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;//BY CHANCE TO BE USED
}
LONG WndProc_OnCommand (HWND hWnd,int id,HWND hwndCtl,UINT codeNotify)
{
		// Parse the menu selections:
			switch (id)
			{
				case IDM_SUSC:
					SuspendCalculation(GetMenu(hWnd),&bSuspendC, hWnd);
					return 0L;
				case IDM_TERMC:
					TerminateCalculation(hWnd, GetMenu(hWnd), &fTerminateC);
					return 0L;

				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   return 0L;//   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd); //PostQuitMessage(0);					                        
					return 0L;//  break;
				default:break;
				  // return DefWindowProc(hWnd, message, wParam, lParam);
			}
		return RFORWARD_WM_COMMAND(hWnd,  id,  hwndCtl,  codeNotify,DefWindowProc);
}

void Print_Text(bool bSuspendC, HWND hWnd) {
	InvalidateRect(hWnd, NULL, TRUE);

	TCHAR sznWM_PAINT[50];
	PAINTSTRUCT ps;
	RECT rt;
	GetClientRect(hWnd, &rt);
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);

	wsprintf(sznWM_PAINT, TEXT("Prime numbers: %d"), primeNumber);
	rt.top = rt.top + 250;
	DrawText(hdc, sznWM_PAINT, strlen(sznWM_PAINT), &rt, DT_CENTER);

	if (!bSuspendC)
		wsprintf(sznWM_PAINT, TEXT("Calculating"), 0);
	else
		wsprintf(sznWM_PAINT, TEXT("Suspend"), 0);
	if (fTerminateC)
		wsprintf(sznWM_PAINT, TEXT("Terminate"), 0);
	rt.top = rt.top + 150;
	DrawText(hdc, sznWM_PAINT, strlen(sznWM_PAINT), &rt, DT_CENTER);

	
	
}

void WndProc_OnPaint(HWND hWnd)
{
	Print_Text(bSuspendC, hWnd);
}

LONG WndProc_OnCreate(HWND hWnd,LPCREATESTRUCT lpCreateStruct)
{
	fTerminateC=FALSE;

	bSuspendC = false;


			unsigned ususpend=0;
  hThreadE[0]=(HANDLE)_beginthreadex(NULL,//must be FOR W95 ,SA
							    0,//stack size committed
								Calculate,
							    (void *)hWnd, //*arglist
							    ususpend  ,//0
							    &thridC
								);
  if(!hThreadE[0]){MessageBox(NULL,"Thread start Error",
						       "Calculate Thread",
							   MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
  }

		return TRUE;//BOOL
}

LONG WndProc_OnDestroy(HWND hWnd)
{
	if(bSuspendC)
			ResumeThread(hThreadE[0]);

	fTerminateC=TRUE;

	TCHAR szRetRes [100];
	DWORD dwRet;

	switch(dwRet= WaitForSingleObject(hThreadE[0],INFINITE))
	{
	case WAIT_ABANDONED_0 :	
       	wsprintf(szRetRes,TEXT("WAIT_ABANDONED_0=%d dwRet=%d"),WAIT_ABANDONED_0,dwRet);
		MessageBox(NULL,szRetRes,"WaitForSingleObjects",MB_OK|MB_ICONEXCLAMATION);
		break;
	case WAIT_FAILED:
		break;
	case WAIT_OBJECT_0:	
		wsprintf(szRetRes,TEXT("WAIT_OBJECT_0=%d dwRet=%d"),WAIT_OBJECT_0,dwRet);
	MessageBox(NULL,szRetRes,"WaitForSingleObjects",MB_OK|MB_ICONEXCLAMATION);
		break;
	}
	if (!fTerminateC)
		if(!CloseHandle(hThreadE[0]))
		{MessageBox(NULL,"CloseHandle  failed",//NULL , no hWnd(the window is destroied) 
							   "Calculate Thread",MB_OK|MB_ICONEXCLAMATION);
		};
	

	
	// Release resources used by the critical section object.
	DeleteCriticalSection(&cs);
		
	PostQuitMessage(0);
	return (0);
}

void  WndProc_OnClose(HWND hWnd)
{ 	 
	DestroyWindow(hWnd);
}

// Message handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;		
}

#include <cmath>
bool CheckForPrime(long number) {
	for (int i = 2; i < (int)sqrt((double)number); i++)
		if (number % i == 0)
			return false;
	return true;
}

unsigned int __stdcall  Calculate(void *hWnd){

	while(!fTerminateC){	
		counter++;
		if (CheckForPrime(counter)) {
			primeNumber = counter;
			Print_Text(bSuspendC, (HWND)hWnd);
		}
		Sleep(5);
		
		
	}//End of while

	return 0;
}//End of PaintEllipse

 //terminates
void TerminateCalculation(HWND hWnd, HMENU hMenu, BOOL *fTerminateE)
{
	if (!*fTerminateE)
	{
		//Check
		//Sets the check-mark attribute to the unchecked state.
		CheckMenuItem(hMenu, IDM_TERMC, MF_CHECKED);
		*fTerminateE = true;
		if (bSuspendC)
			ResumeThread(hThreadE[0]);

		WaitForSingleObject(hThreadE[0], INFINITE);//Block the primary thread if PaintEllipse
												   // is in the suspended state
		if (!CloseHandle(hThreadE[0]))
		{
			MessageBox(NULL, "CloseHandle  failed",
				"Calculate Thread",
				MB_OK | MB_ICONEXCLAMATION);
		};

	}
	else
	{
		//Uncheck
		//Sets the check-mark attribute to the checked state.
		CheckMenuItem(hMenu, IDM_TERMC, MF_UNCHECKED);

		*fTerminateE = false;

		unsigned ususpend = (bSuspendC) ? CREATE_SUSPENDED : 0;
		hThreadE[0] = (HANDLE)_beginthreadex(NULL,//must be FOR W95
			0,//stack size
			Calculate,
			(void *)hWnd,
			ususpend,//0
			&thridC
		);
		if (!hThreadE[0])MessageBox(NULL, "Thread start Error",
			"Calculate Thread",
			MB_OK | MB_ICONEXCLAMATION);

	}
	Print_Text(bSuspendC, (HWND)hWnd);
	return;
}



void SuspendCalculation(HMENU hMenu, bool *bSuspend, HWND hWnd)
{
	TCHAR message[260];
	DWORD dwRetCode;

	EnterCriticalSection(&cs);

	if (!*bSuspend) {
		if (0xFFFFFFFF == SuspendThread(hThreadE[0]))//or -1 (==0xFFFFFFFF)
		{
			wsprintf(message, TEXT("SuspendThread Error %ld"), GetLastError());
			MessageBox(NULL, message, "PaintEllipse Thread", MB_OK | MB_ICONEXCLAMATION);
			LeaveCriticalSection(&cs);
			return;
		}

		*bSuspend = true;
		Print_Text(&bSuspend, hWnd);
		//Check
		//Sets the check-mark attribute to the checked state.
		CheckMenuItem(hMenu, IDM_SUSC, MF_CHECKED);
	}
	else
	{
		if (0xFFFFFFFF == ResumeThread(hThreadE[0]))
		{
			wsprintf(message, TEXT("ResumeThread Error %ld"), GetLastError());
			MessageBox(NULL, message, "PaintEllipse Thread", MB_OK | MB_ICONEXCLAMATION);
			LeaveCriticalSection(&cs);
			return;
		}

		*bSuspend = false;
		//Uncheck 
		//Sets the check-mark attribute to the unchecked state.
		CheckMenuItem(hMenu, IDM_SUSC, MF_UNCHECKED);
	}
	LeaveCriticalSection(&cs);
	return;
	
}//Suspend Calculation