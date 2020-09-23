#include "EncodeFunction.h"

namespace encodage {
	sf::String encodeToUTF32(std::string str)
	{
        
		std::basic_string<sf::Uint32> utf32;
		sf::Utf8::toUtf32(str.begin(), str.end(), std::back_inserter(utf32));
        sf::String SFstr = utf32;

		return SFstr;
	}

    

    std::wstring encodeToUTF32(std::wstring str)
    {
        std::basic_string<sf::Uint32> utf32;
        sf::Utf8::toUtf32(str.begin(), str.end(), std::back_inserter(utf32));
        sf::String SFstr = utf32;

        return SFstr;
    }


    void ucs2CharToUtf8Char(const wchar_t ucs2Char, char* utf8Tok)
    {
        //We do math, that relies on unsigned data types
        uint32_t ucs2CharValue = static_cast<uint32_t>(ucs2Char);   //The standard doesn't specify the signed/unsignedness of wchar_t
        unsigned char* utf8TokUs = reinterpret_cast<unsigned char*>(utf8Tok);

        //Decode
        if (0x80 > ucs2CharValue)
        {
            //Tokensize: 1 byte
            utf8TokUs[0] = static_cast<unsigned char>(ucs2CharValue);
            utf8TokUs[1] = '\0';
        }
        else if (0x800 > ucs2CharValue)
        {
            //Tokensize: 2 bytes
            utf8TokUs[2] = '\0';
            utf8TokUs[1] = static_cast<unsigned char>(0x80 | (ucs2CharValue & 0x3F));
            ucs2CharValue = (ucs2CharValue >> 6);
            utf8TokUs[0] = static_cast<unsigned char>(0xC0 | ucs2CharValue);
        }
        else
        {
            //Tokensize: 3 bytes
            utf8TokUs[3] = '\0';
            utf8TokUs[2] = static_cast<unsigned char>(0x80 | (ucs2CharValue & 0x3F));
            ucs2CharValue = (ucs2CharValue >> 6);
            utf8TokUs[1] = static_cast<unsigned char>(0x80 | (ucs2CharValue & 0x3F));
            ucs2CharValue = (ucs2CharValue >> 6);
            utf8TokUs[0] = static_cast<unsigned char>(0xE0 | ucs2CharValue);
        }
    }

    std::string ucs2ToUtf8(const std::wstring& ucs2Str)
    {
        std::string utf8Result;
        char utf8Sequence[] = { 0, 0, 0, 0, 0 };
        const wchar_t* cursor = ucs2Str.c_str();
        const wchar_t* const end = ucs2Str.c_str() + ucs2Str.length();

        while (end > cursor)
        {
            const wchar_t ucs2Char = *cursor;
            ucs2CharToUtf8Char(ucs2Char, utf8Sequence);
            utf8Result.append(utf8Sequence);
            cursor++;
        }

        return utf8Result;
    }
}

