//==========================================================================
// 物理メモリと仮想メモリの現在の状態 [MemoryInfo.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include <Windows.h>
#include <stdint.h>
#include "mdx.h"

_MDX_SYSTEM_BEGIN

namespace memory
{
    /**
    物理メモリと仮想メモリの現在の状態に関する情報が含まれます。
    */
    template<typename _Ty>
    struct MemoryInfo final
    {
        DWORD physicalMemoryUsage = (DWORD)0; // 物理メモリ使用率
        _Ty maxPhysicalMemoryCapacity = (_Ty)0; // 物理メモリ搭載容量
        _Ty freePhysicalMemory = (_Ty)0; // 物理メモリ空き容量
        _Ty maxVirtualMemoryCapacity = (_Ty)0; // 仮想メモリ最大容量
        _Ty freeVirtualMemory = (_Ty)0; // 仮想メモリ空き容量
        _Ty maxUserSpaceCapacity = (_Ty)0; // ユーザー空間総容量
        _Ty freeUserSpace; // ユーザー空間空容量
        _Ty freeExtensionUserSpace = (_Ty)0; // 拡張ユーザー空間空容量
    };

    using MemoryInfo_DWORDLONG = MemoryInfo<DWORDLONG>;
    using MemoryInfo_float = MemoryInfo<float>;

    /**
    @brief 物理メモリと仮想メモリの現在の状態に関する情報 (Byte単位)
    */
    const MemoryInfo<DWORDLONG>& GetMemoryInfoInByte();

    /**
    @brief 物理メモリと仮想メモリの現在の状態に関する情報 (KByte単位)
    */
    const MemoryInfo<float>& GetMemoryInfoInKByte();

    /**
    @brief 物理メモリと仮想メモリの現在の状態に関する情報 (MByte単位)
    */
    const MemoryInfo<float>& GetMemoryInfoInMByte();

    /**
    @brief 物理メモリと仮想メモリの現在の状態に関する情報 (GByte単位)
    */
    const MemoryInfo<float>& GetMemoryInfoInGByte();
}

_MDX_SYSTEM_END