#pragma once
#include <map>

namespace Globals {
#ifndef GLOBALS_H
#define GLOBALS_H
	inline extern std::map<HWND, LONG_PTR> HwndWndProcs = {};
#endif // !GLOBALS_H
}