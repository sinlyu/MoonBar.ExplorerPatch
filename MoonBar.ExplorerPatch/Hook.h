#pragma once
#include <iostream>
#include <Windows.h>


namespace Hook
{
	extern LONG_PTR oriWndProc;

	LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}