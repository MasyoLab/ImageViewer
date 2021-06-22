//==========================================================================
// ファイル探索[file_path.hpp]
// author: MasyoLab
//==========================================================================
#pragma once
#include <Windows.h>
#include <list>
#include <string>
#include <stdexcept>

namespace file_path {
    /**
    @brief ファイル探索
    @param dir_name [in] 探索対象ディレクトリ
    @param extension [in] 拡張子指定
    @param set_ [in]
    @return 探索結果
    */
    std::list<std::wstring> get_in(const std::wstring& dir_name, const std::wstring& extension, std::wstring set_ = L"\\*.") noexcept(false);

    /**
    @brief ファイル探索
    @param extension [in] 拡張子指定
    @return 探索結果
    */
    std::list<std::wstring> get(const std::wstring& extension) noexcept(false);

    size_t GetLength();

    void SetLength(size_t length);
}
