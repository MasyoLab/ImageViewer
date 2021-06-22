//==========================================================================
// 全てのファイルをチェック [CheckAllFile.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include <string>
#include <list>
#include <random>
#include "common.h"
#include "file_path.hpp"
#include "folder_path.hpp"

namespace check_all_file
{
	// ファイルのデータ
	struct DataInfo
	{
		std::wstring m_str_name; // ファイル名
		std::wstring m_str_path; // ファイルパス
		std::wstring m_str_extension; // 拡張子

		DataInfo(const std::wstring& str_name, const std::wstring& str_path, const std::wstring& str_extension);
		DataInfo() {}
	};

	using DataInfoList = std::list<DataInfo>;
	using string_list = std::list<std::wstring>;

	// 全てのデータをチェック
	class CheckAllFile :
		public mdx::component::Component
	{
	private:
		DataInfoList m_InfoList; // データ格納用
	public:
		CheckAllFile();
		virtual ~CheckAllFile();

		/**
		@brief ディレクトリの読み込み
		*/
		void LoadDirectory(const std::wstring& directory);

		/**
		@brief データを取得
		*/
		const DataInfoList& GetData() const;

		/**
		@brief データの長さを取得
		*/
		size_t Length() const;

		/**
		@brief ランダムでイテレーターを取得
		*/
		DataInfoList::iterator GetRandomIterator(std::mt19937& engine);
	private:

		/**
		@brief ファイル探索
		@param dir_name [in] 探索対象ディレクトリ
		@param extension [in] 拡張子指定
		@param set_ [in]
		*/
		DataInfoList search(const std::wstring& dir_name, const string_list& extension, const std::wstring set_);

		/**
		@brief 初期化
		*/
		void Init() override;
	};
}