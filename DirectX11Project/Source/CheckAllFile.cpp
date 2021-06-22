//==========================================================================
// 全てのファイルをチェック [CheckAllFile.cpp]
// author : MasyoLab
//==========================================================================
#include "CheckAllFile.h"

namespace check_all_file
{
	DataInfo::DataInfo(const std::wstring& str_name, const std::wstring& str_path, const std::wstring& str_extension):
		m_str_name(str_name), m_str_path(str_path), m_str_extension(str_extension)
	{
	}

	CheckAllFile::CheckAllFile()
	{
		SetObjectName("CheckAllFile");
	}

	CheckAllFile::~CheckAllFile()
	{
	}

	void CheckAllFile::LoadDirectory(const std::wstring& directory)
	{
		string_list extension; // 拡張子
		extension.push_back(L"png");
		extension.push_back(L"jpeg");
		extension.push_back(L"jpg");
		extension.push_back(L"gif");
		extension.push_back(L"tif");
		extension.push_back(L"tiff");
		extension.push_back(L"bmp");

		std::wstring directory_str = directory;
		std::replace(directory_str.begin(), directory_str.end(), '\\', '/');

		// 同じディレクトリ内を探索
		auto directoryList = folder_path::get_in_recursive(folder_path::get_in(directory_str));

		// 自身のディレクトリを追加
		directoryList.push_back(directory_str);

		// ディレクトリ指定なし
		m_InfoList = search(L"", extension, L"*.");

		// ディレクトリ指定あり
		for (auto& itr1 : directoryList)
			// 検出したディレクトリ内の全データを探索する
			// 取得した結果を追加する
			for (auto& itr2 : search(itr1, extension, L"\\*."))
				m_InfoList.push_back(itr2);
	}

	const DataInfoList& CheckAllFile::GetData() const
	{
		return m_InfoList;
	}

	size_t CheckAllFile::Length() const
	{
		return m_InfoList.size();
	}

	DataInfoList::iterator CheckAllFile::GetRandomIterator(std::mt19937& engine)
	{
		if (m_InfoList.size() == 0)
			return m_InfoList.begin();

		std::uniform_int_distribution<> dist(0, m_InfoList.size() - 1);
		int nLimit = dist(engine);
		auto itr = m_InfoList.begin();

		for (int i = 0; i < nLimit; i++, ++itr);

		return itr;
	}

	DataInfoList CheckAllFile::search(const std::wstring& dir_name, const string_list& extension, const std::wstring set_)
	{
		DataInfoList infoList; // データ格納用

		// 探索データ記録
		for (auto& itr1 : extension)
		{
			// 全探索対象ディレクトリ内を検索
			// データの格納
			for (auto& itr2 : file_path::get_in(dir_name, itr1, set_))
			{
				std::wstring _file_name; // ファイル名
				std::wstring _path_name; // 拡張子
				bool bchange = false;

				// 拡張子排除
				for (auto& itr3 : itr2)
				{
					std::wstring str_;
					str_ = itr3;

					if (str_ == L".")
						bchange = true;
					if (bchange == false && str_ != L".")
						_file_name += str_;
					else if (bchange == true && str_ != L".")
						_path_name += str_;
				}

				if (dir_name == L"")
					infoList.emplace_back(_file_name, dir_name + itr2, _path_name);
				else if (dir_name != L"")
					infoList.emplace_back(_file_name, dir_name + L"/" + itr2, _path_name);
			}
		}
		return infoList;
	}
	void CheckAllFile::Init()
	{
	}
}