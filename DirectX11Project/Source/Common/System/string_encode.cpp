//==========================================================================
// string encode [string_encode.cpp]
// author: MasyoLab 
//==========================================================================
#include <Windows.h>
#include "string_encode.hpp"

_MDX_COMMON_BEGIN

namespace string_encode
{
	std::string wide_to_ansi_encode(const std::wstring& wstr)
	{
		if (wstr.empty())return std::string();
		int size_needed = WideCharToMultiByte(CP_ACP, 0, &wstr[0], (int)wstr.size(), nullptr, 0, nullptr, nullptr);
		std::string strTo(size_needed, 0);
		WideCharToMultiByte(CP_ACP, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, nullptr, nullptr);
		return strTo;
	}

	std::wstring ansi_to_wide_encode(const std::string& str)
	{
		if (str.empty())return std::wstring();
		int size_needed = MultiByteToWideChar(CP_ACP, 0, &str[0], (int)str.size(), nullptr, 0);
		std::wstring wstrTo(size_needed, 0);
		MultiByteToWideChar(CP_ACP, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
		return wstrTo;
	}

	std::string wide_to_utf8_encode(const std::wstring& wstr)
	{
		if (wstr.empty())return std::string();
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), nullptr, 0, nullptr, nullptr);
		std::string strTo(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, nullptr, nullptr);
		return strTo;
	}

	std::wstring utf8_to_wide_encode(const std::string& str)
	{
		if (str.empty())return std::wstring();
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), nullptr, 0);
		std::wstring wstrTo(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
		return wstrTo;
	}

	std::string ansi_to_utf8_encode(const std::string& str)
	{
		return wide_to_utf8_encode(ansi_to_wide_encode(str));
	}

	std::string utf8_to_ansi_encode(const std::string& str)
	{
		return wide_to_ansi_encode(utf8_to_wide_encode(str));
	}
}

_MDX_COMMON_END