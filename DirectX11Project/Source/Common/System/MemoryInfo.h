//==========================================================================
// �����������Ɖ��z�������̌��݂̏�� [MemoryInfo.h]
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
    �����������Ɖ��z�������̌��݂̏�ԂɊւ����񂪊܂܂�܂��B
    */
    template<typename _Ty>
    struct MemoryInfo final
    {
        DWORD physicalMemoryUsage = (DWORD)0; // �����������g�p��
        _Ty maxPhysicalMemoryCapacity = (_Ty)0; // �������������ڗe��
        _Ty freePhysicalMemory = (_Ty)0; // �����������󂫗e��
        _Ty maxVirtualMemoryCapacity = (_Ty)0; // ���z�������ő�e��
        _Ty freeVirtualMemory = (_Ty)0; // ���z�������󂫗e��
        _Ty maxUserSpaceCapacity = (_Ty)0; // ���[�U�[��ԑ��e��
        _Ty freeUserSpace; // ���[�U�[��ԋ�e��
        _Ty freeExtensionUserSpace = (_Ty)0; // �g�����[�U�[��ԋ�e��
    };

    using MemoryInfo_DWORDLONG = MemoryInfo<DWORDLONG>;
    using MemoryInfo_float = MemoryInfo<float>;

    /**
    @brief �����������Ɖ��z�������̌��݂̏�ԂɊւ����� (Byte�P��)
    */
    const MemoryInfo<DWORDLONG>& GetMemoryInfoInByte();

    /**
    @brief �����������Ɖ��z�������̌��݂̏�ԂɊւ����� (KByte�P��)
    */
    const MemoryInfo<float>& GetMemoryInfoInKByte();

    /**
    @brief �����������Ɖ��z�������̌��݂̏�ԂɊւ����� (MByte�P��)
    */
    const MemoryInfo<float>& GetMemoryInfoInMByte();

    /**
    @brief �����������Ɖ��z�������̌��݂̏�ԂɊւ����� (GByte�P��)
    */
    const MemoryInfo<float>& GetMemoryInfoInGByte();
}

_MDX_SYSTEM_END