#include "pch.h"
#include "Hook.h"


LONG_PTR Hook::oriWndProc = NULL;

LRESULT __stdcall Hook::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_NCCALCSIZE:
	case WM_WINDOWPOSCHANGED:
		return 0;
		break;
	default:
		break;
	}

	return CallWindowProcW((WNDPROC)Hook::oriWndProc, hWnd, uMsg, wParam, lParam);
}