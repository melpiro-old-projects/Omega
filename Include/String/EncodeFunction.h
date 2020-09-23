#pragma once

#include <SFML/System.hpp>


namespace encodage {
	sf::String encodeToUTF32(std::string str);
	std::wstring encodeToUTF32(std::wstring str);

	void ucs2CharToUtf8Char(const wchar_t ucs2Char, char* utf8Tok);

	std::string ucs2ToUtf8(const std::wstring& ucs2Str);
}
