// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "pch.h"

#include <stdlib.h>     // for _itoa_s functions, _countof, count macro
#include <stdio.h>      // for printf
#include <string.h>     // for strnlen
#include "Hook.h"

#define SIZEOF(f) (sizeof(f) / sizeof(f[0]))

typedef struct ENUM_WIN_INFO {
  DWORD dwProcID;
  int nNextHWNDIndex;
  HWND hFoundHWNDs[256];
} ENUM_WIN_INFO;

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
  ENUM_WIN_INFO* pEWI = (ENUM_WIN_INFO*)lParam;

  // get our process Id
  DWORD dwProcID = 0;
  GetWindowThreadProcessId(hWnd, &dwProcID);

  // is this our process Id ?
  if (dwProcID != pEWI->dwProcID) {
    return true;
  }

  HWND isTaskbar = FindWindowEx(hWnd, NULL, L"Start", NULL);
  HWND isPrimaryTaskbar = FindWindowEx(hWnd, NULL, L"RebarWindow32", NULL);

  // we only want taskbars
  if (isTaskbar == NULL) {
    return true;
  }

  pEWI->hFoundHWNDs[pEWI->nNextHWNDIndex] = hWnd;
  pEWI->nNextHWNDIndex++;
  
  return true;
}


void Start()
{

  ENUM_WIN_INFO ewi = { 0 };
  memset(&ewi, 0, sizeof(ewi));
  ewi.dwProcID = GetCurrentProcessId();

  EnumWindows(EnumWindowsProc, (LPARAM)&ewi);

  if (ewi.nNextHWNDIndex == 0) {
    // we did not find anything (bad!)
    MessageBoxA(NULL, "Could not find any taskbar", "Error", 0);
    return;
  }

  // iterate trough all task bars
  for (int i = 0; i < ewi.nNextHWNDIndex; i++)
  {
    HWND wnd = ewi.hFoundHWNDs[i];
    SetWindowLongPtr(wnd, GWLP_WNDPROC, (LONG_PTR)Hook::WndProc);
  }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
      case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(Start), NULL, NULL, NULL);
      case DLL_THREAD_ATTACH:
      case DLL_THREAD_DETACH:
      case DLL_PROCESS_DETACH:
          break;
    }
    return TRUE;
}



