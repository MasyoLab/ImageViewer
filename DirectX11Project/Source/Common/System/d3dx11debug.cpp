//==========================================================================
// デバッグ機能 [d3dx11debug.cpp]
// author : MasyoLab
//==========================================================================
#include "d3dx11debug.h"
#include <Windows.h>
#include <stdio.h>
#include <iostream>

_MDX_SYSTEM_BEGIN

namespace d3dx11debug
{
	FILE* g_pfPtr = nullptr;

	bool DebugConsoleBegin()
	{
		if (g_pfPtr != nullptr)
			return false;
		if (!AllocConsole())
			return false;
		freopen_s(&g_pfPtr, "CONOUT$", "w", stdout);
		std::cout.clear();
		return true;
	}

	bool DebugConsoleEnd()
	{
		if (g_pfPtr == nullptr)
			return false;
		fclose(g_pfPtr);
		g_pfPtr = nullptr;
		return FreeConsole();
	}
}

_MDX_SYSTEM_END