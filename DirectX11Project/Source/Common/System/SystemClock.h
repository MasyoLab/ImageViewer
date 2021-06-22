//==========================================================================
// システム時間 [SystemClock.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <string>  // string
#include "mdx.h"

_MDX_SYSTEM_BEGIN

namespace clock
{
	using rep = std::chrono::system_clock::rep; // 時間間隔の内部表現となる符号付き算術型	

	/**
	@brief FPS指定 初期値は60fps
	*/
	void SetFps(int fps);

	/**
	@brief フレーム制限
	*/
	bool FpsFixed();

	/**
	@brief DeltaTime
	*/
	float GetDeltaTime();

	/**
	@brief Framerate
	*/
	rep GetFramerate();

	/**
	@brief FPS
	*/
	float GetFPS();

	/**
	@brief 現在のrepを取得
	*/
	rep GetSystemTimeSinceEpoch();

	/**
	@brief 現在の日時を取得
	*/
	std::string GetTimeString();
}

_MDX_SYSTEM_END

