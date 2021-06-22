//==========================================================================
// ファイル探索[file_path.cpp]
// author: MasyoLab
//==========================================================================
#include "file_path.hpp"

static size_t g_numFiles = 0;

std::list<std::wstring> file_path::get_in(const std::wstring& dir_name, const std::wstring& extension, std::wstring set_) noexcept(false)
{
	HANDLE hFind = nullptr;
	WIN32_FIND_DATAW win32fd;//defined at Windwos.h
	std::list<std::wstring> file_names;

	ZeroMemory(&win32fd, sizeof(win32fd));

	//拡張子の設定
	std::wstring search_name = dir_name + set_ + extension;

	hFind = FindFirstFileW(search_name.c_str(), &win32fd);

	if (win32fd.dwFileAttributes == 0) {
		FindClose(hFind);
		return file_names;
	}

	if (hFind == INVALID_HANDLE_VALUE) {
		throw std::runtime_error("file not found");
		return file_names;
	}

	do {
		if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {}
		else
		{
			file_names.push_back(win32fd.cFileName);
			g_numFiles++;
		}
	} while (FindNextFileW(hFind, &win32fd));

	FindClose(hFind);

	return file_names;
}

std::list<std::wstring> file_path::get(const std::wstring& extension) noexcept(false)
{
	return get_in(L"", extension, L"*.");
}

size_t file_path::GetLength()
{
	return g_numFiles;
}

void file_path::SetLength(size_t length)
{
	g_numFiles = length;
}
