//==========================================================================
// デバッグ機能 [d3dx11debug.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "mdx.h"

_MDX_SYSTEM_BEGIN

namespace d3dx11debug
{
#pragma region DebugConsole
	/**
	@brief コンソールデバッグ機能の開始
	*/
	bool DebugConsoleBegin();

	/**
	@brief コンソールデバッグ機能の終了
	*/
	bool DebugConsoleEnd();
#pragma endregion
}

_MDX_SYSTEM_END