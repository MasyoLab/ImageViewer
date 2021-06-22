//==========================================================================
// フォルダ探索[folder_path.hpp]
// author: MasyoLab
//==========================================================================
#pragma once
#include <Windows.h>
#include <list>
#include <string>
#include <algorithm>
#include <stdexcept>

namespace folder_path {
	/**
	@brief 実行ファイル直下フォルダ探索
	@return 探索結果
	*/
	std::list<std::wstring> get() noexcept(false);

	/**
	@brief 指定フォルダ直下フォルダ探索
	@param folder_name [in] 探索対象のフォルダ
	@return 探索結果
	*/
	std::list<std::wstring> get_in(const std::wstring& folder_name) noexcept(false);

	/**
	@brief 指定フォルダ直下フォルダの再帰探索
	@param path [in] 探索対象のフォルダ
	@return 探索結果
	*/
	std::list<std::wstring> get_in_recursive(const std::list<std::wstring>& path) noexcept(false);

	/**
	@brief 実行ファイル直下フォルダ全探索
	@return 探索結果
	*/
	std::list<std::wstring> get_all() noexcept(false);

	size_t GetLength();

	void SetLength(size_t length);
}