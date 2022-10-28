#pragma once
#include <iostream>
#include <Windows.h>
#include "Globals.h"

namespace Hook
{
	LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}