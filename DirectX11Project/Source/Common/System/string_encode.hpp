//==========================================================================
// string encode [string_encode.hpp]
// author: MasyoLab 
//==========================================================================
#pragma once
#include <string> 
#include "mdx.h"

_MDX_COMMON_BEGIN

namespace string_encode
{
	// Convert a wide Unicode string to an ANSI string
	std::string wide_to_ansi_encode(const std::wstring& wstr);

	// Convert a ANSI string to an wide Unicode string
	std::wstring ansi_to_wide_encode(const std::string& str);

	// Convert a wide Unicode string to an UTF8 string
	std::string wide_to_utf8_encode(const std::wstring& wstr);

	// Convert a UTF8 string to an wide Unicode string
	std::wstring utf8_to_wide_encode(const std::string& str);

	// Convert a ANSI string to an UTF8 string
	std::string ansi_to_utf8_encode(const std::string& str);

	// Convert a UTF8 string to an ANSI string
	std::string utf8_to_ansi_encode(const std::string& str);
}

_MDX_COMMON_END

#define WIDE_TO_ANSI_ENCODE(str) mdx::common::string_encode::wide_to_ansi_encode(str)
#define ANSI_TO_WIDE_ENCODE(str) mdx::common::string_encode::ansi_to_wide_encode(str)
#define WIDE_TO_UTF8_ENCODE(str) mdx::common::string_encode::wide_to_utf8_encode(str)
#define UTF8_TO_WIDE_ENCODE(str) mdx::common::string_encode::utf8_to_wide_encode(str)
#define ANSI_TO_UTF8_ENCODE(str) mdx::common::string_encode::ansi_to_utf8_encode(str)
#define UTF8_TO_ANSI_ENCODE(str) mdx::common::string_encode::utf8_to_ansi_encode(str)
