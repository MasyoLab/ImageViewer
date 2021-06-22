//==========================================================================
// フォルダ探索[folder_path.cpp]
// author: MasyoLab
//==========================================================================
#include "folder_path.hpp"

static size_t g_numFolders = 0;

std::list<std::wstring> folder_path::get() noexcept(false)
{
	HANDLE hFind = nullptr;
	WIN32_FIND_DATAW win32fd; //defined at Windwos.h
	std::list<std::wstring> folder_names;

	ZeroMemory(&win32fd, sizeof(win32fd));

	hFind = FindFirstFileW(L"*", &win32fd);

	if (win32fd.dwFileAttributes == 0) {
		FindClose(hFind);
		return folder_names;
	}

	if (hFind == INVALID_HANDLE_VALUE) {
		throw std::runtime_error("file not found");
		return folder_names;
	}

	do {
		if (win32fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
			std::wstring str_ = win32fd.cFileName;
			if (str_ != L"." && str_ != L"..")
				folder_names.emplace_back(str_);
		}
	} while (FindNextFileW(hFind, &win32fd));

	FindClose(hFind);

	g_numFolders += folder_names.size();

	return folder_names;
}

std::list<std::wstring> folder_path::get_in(const std::wstring& folder_name) noexcept(false)
{
	HANDLE hFind = nullptr;
	WIN32_FIND_DATAW win32fd;//defined at Windwos.h
	std::list<std::wstring> folder_names;

	ZeroMemory(&win32fd, sizeof(win32fd));

	std::wstring _folder = folder_name + L"/*";

	hFind = FindFirstFileW(_folder.c_str(), &win32fd);

	if (win32fd.dwFileAttributes == 0) {
		FindClose(hFind);
		return folder_names;
	}

	if (hFind == INVALID_HANDLE_VALUE) {
		throw std::runtime_error("file not found");
		return folder_names;
	}

	do {
		if (win32fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
			std::wstring str_ = win32fd.cFileName;

			if (str_ != L"." && str_ != L"..")
				folder_names.emplace_back(folder_name + L"/" + str_);
		}
	} while (FindNextFileW(hFind, &win32fd));

	FindClose(hFind);

	g_numFolders += folder_names.size();

	return folder_names;
}

std::list<std::wstring> folder_path::get_in_recursive(const std::list<std::wstring>& path) noexcept(false)
{
	std::list<std::wstring> str_folder_new;
	std::list<std::wstring> str_folder;

	for (auto& itr1 : path)
		for (auto& itr2 : get_in(itr1))
			str_folder_new.emplace_back(itr2);

	for (auto& itr : path)
		str_folder.emplace_back(itr);
	for (auto& itr : str_folder_new)
		str_folder.emplace_back(itr);

	// 再帰前にデータの最適化
	str_folder.sort(std::greater<std::wstring>());
	str_folder.unique();

	// 探索するデータが存在する場合データを引き継ぎ再帰する
	if (str_folder_new.size() != 0)
	{
		g_numFolders += str_folder_new.size();
		for (auto& itr : get_in_recursive(str_folder_new))
			str_folder.emplace_back(itr);
	}

	// データを戻す前に最適化
	str_folder.sort(std::greater<std::wstring>());
	str_folder.unique();

	return str_folder;
}

std::list<std::wstring> folder_path::get_all() noexcept(false)
{
	return get_in_recursive(get());
}

size_t folder_path::GetLength()
{
	return g_numFolders;
}

void folder_path::SetLength(size_t length)
{
	g_numFolders = length;
}
