#include "Hook.h"


LRESULT __stdcall Hook::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_NCCALCSIZE:
	case WM_WINDOWPOSCHANGED:
	case WM_MOVE:
	case WM_SIZE:
	case WM_WINDOWPOSCHANGING:
	case WM_MOVING:
		return LRESULT(0);
		break;
	default:
		break;
	}


	auto wndProc = Globals::HwndWndProcs.at(hWnd);

	return CallWindowProcW((WNDPROC)wndProc, hWnd, uMsg, wParam, lParam);
}