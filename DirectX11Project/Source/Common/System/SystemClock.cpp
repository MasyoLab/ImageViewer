//==========================================================================
// ƒVƒXƒeƒ€ŽžŠÔ [SystemClock.cpp]
// author : MasyoLab
//==========================================================================
#include "SystemClock.h"

_MDX_SYSTEM_BEGIN

namespace clock
{
	constexpr float requestFps_f = 1000;
	constexpr int requestFps = 1000;
	constexpr int reqZero = 0;
	double timePerFrame = requestFps / 60;
	rep framerate = reqZero;
	float deltaTime = 0.0f;
	std::chrono::system_clock::time_point endTimePoint = std::chrono::system_clock::now();

	void SetFps(int fps)
	{
		timePerFrame = requestFps / fps;
	}

	bool FpsFixed()
	{
		for (framerate = reqZero; framerate < timePerFrame; )
			framerate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - endTimePoint).count();
		endTimePoint = std::chrono::system_clock::now();
		deltaTime = framerate / requestFps_f;
		return true;
	}

	float GetDeltaTime()
	{
		return deltaTime;
	}

	rep GetFramerate()
	{
		return framerate;
	}

	float GetFPS()
	{
		return requestFps / (framerate * 1.0f);
	}

	rep GetSystemTimeSinceEpoch()
	{
		return std::chrono::system_clock::now().time_since_epoch().count();
	}

	std::string GetTimeString()
	{
		std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
		std::time_t t = std::chrono::system_clock::to_time_t(p);
		std::stringstream ss;

		ss << std::put_time(std::localtime(&t), "%Y/%m/%d (%a) %X");
		return ss.str();
	}
}

_MDX_SYSTEM_END
