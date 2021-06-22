//==========================================================================
// �V�X�e������ [SystemClock.h]
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
	using rep = std::chrono::system_clock::rep; // ���ԊԊu�̓����\���ƂȂ镄���t���Z�p�^	

	/**
	@brief FPS�w�� �����l��60fps
	*/
	void SetFps(int fps);

	/**
	@brief �t���[������
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
	@brief ���݂�rep���擾
	*/
	rep GetSystemTimeSinceEpoch();

	/**
	@brief ���݂̓������擾
	*/
	std::string GetTimeString();
}

_MDX_SYSTEM_END

