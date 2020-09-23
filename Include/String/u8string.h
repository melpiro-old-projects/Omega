#pragma once

#include <vector>
#include "u8char.h"

namespace str {

	class u8string
	{
	public:
		u8string();
		u8string(const std::string& str);
		u8string(std::vector<str::u8char> vector);

		size_t size();

		std::vector<str::u8char>::iterator begin();
		std::vector<str::u8char>::iterator end();

		friend std::ostream& operator<<(std::ostream& os, u8string chr);
		friend u8string operator+(const u8string& str1, const u8string& str2);
		friend u8string operator+(const u8string& str1, const u8char& str2);
		friend u8string operator+(const u8char& str1, const u8string& str2);

		void operator+=(u8string& str);
		void operator+=(const u8char& chr);

		str::u8char& operator[](int i);

		static u8string concat(u8string str1, u8string str2);

		std::vector<str::u8char> to_u8char_vector();

		


	private:

		std::vector<str::u8char> m_str;

	};

}

