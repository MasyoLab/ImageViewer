//==========================================================================
// 物理メモリと仮想メモリの現在の状態 [MemoryInfo.cpp]
// author : MasyoLab
//==========================================================================
#include "MemoryInfo.h"

_MDX_SYSTEM_BEGIN

namespace memory
{
	static MemoryInfo<DWORDLONG> memoryInfo_DwordLong; // メモリ情報
	static MemoryInfo<float> memoryInfo_float; // メモリ情報

	struct MemoryStatus : public MEMORYSTATUSEX
	{
		MemoryStatus()
		{
			dwLength = sizeof(MEMORYSTATUSEX);
		}

		const MemoryInfo<float>& ChangeByteSize(int64_t byte)
		{
			float fbyte = 1.0f / byte;
			memoryInfo_float.physicalMemoryUsage = dwMemoryLoad;
			memoryInfo_float.maxPhysicalMemoryCapacity = ullTotalPhys * fbyte;
			memoryInfo_float.freePhysicalMemory = ullAvailPhys * fbyte;
			memoryInfo_float.maxVirtualMemoryCapacity = ullTotalPageFile * fbyte;
			memoryInfo_float.freeVirtualMemory = ullAvailPageFile * fbyte;
			memoryInfo_float.maxUserSpaceCapacity = ullTotalVirtual * fbyte;
			memoryInfo_float.freeUserSpace = ullAvailVirtual * fbyte;
			memoryInfo_float.freeExtensionUserSpace = ullAvailExtendedVirtual * fbyte;
			return memoryInfo_float;
		}

		const MemoryInfo<DWORDLONG>& ChangeByteSize()
		{
			memoryInfo_DwordLong.physicalMemoryUsage = dwMemoryLoad;
			memoryInfo_DwordLong.maxPhysicalMemoryCapacity = ullTotalPhys;
			memoryInfo_DwordLong.freePhysicalMemory = ullAvailPhys;
			memoryInfo_DwordLong.maxVirtualMemoryCapacity = ullTotalPageFile;
			memoryInfo_DwordLong.freeVirtualMemory = ullAvailPageFile;
			memoryInfo_DwordLong.maxUserSpaceCapacity = ullTotalVirtual;
			memoryInfo_DwordLong.freeUserSpace = ullAvailVirtual;
			memoryInfo_DwordLong.freeExtensionUserSpace = ullAvailExtendedVirtual;
			return memoryInfo_DwordLong;
		}
	};

	static MemoryStatus nemoryStatus; // ステータス
	constexpr int64_t kByte = 1024;
	constexpr int64_t mByte = kByte * kByte;
	constexpr int64_t gByte = mByte * kByte;

	const MemoryInfo<DWORDLONG>& GetMemoryInfoInByte()
	{
		GlobalMemoryStatusEx(&nemoryStatus);
		return nemoryStatus.ChangeByteSize();
	}
	const MemoryInfo<float>& GetMemoryInfoInKByte()
	{
		GlobalMemoryStatusEx(&nemoryStatus);
		return nemoryStatus.ChangeByteSize(kByte);
	}
	const MemoryInfo<float>& GetMemoryInfoInMByte()
	{
		GlobalMemoryStatusEx(&nemoryStatus);
		return nemoryStatus.ChangeByteSize(mByte);
	}
	const MemoryInfo<float>& GetMemoryInfoInGByte()
	{
		GlobalMemoryStatusEx(&nemoryStatus);
		return nemoryStatus.ChangeByteSize(gByte);
	}
}

_MDX_SYSTEM_END