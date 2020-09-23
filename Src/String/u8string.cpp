#include "u8string.h"

namespace str {
	u8string::u8string() : m_str(0)
	{
		
	}
	u8string::u8string(const std::string& str)
	{

		for (size_t i = 0; i < str.size(); i++)
		{
			std::bitset<8> x = str[i];
			// on verif l'encodage
			if (x[7] == 1 && x[6] == 1 && x[5] == 1 && x[4] == 1 && x[3] == 0)
			{
				std::vector<char> u8chr = { str[i], str[i + 1], str[i + 2], str[i + 3] };
				i += 3;
				m_str.push_back(u8char(u8chr));
			}
			else if (x[7] == 1 && x[6] == 1 && x[5] == 1 && x[4] == 0)
			{
				std::vector<char> u8chr = { str[i], str[i + 1], str[i + 2] };
				i+=2;
				m_str.push_back(u8char(u8chr));
			}
			else if (x[7] == 1 && x[6] == 1 && x[5] == 0)
			{
				std::vector<char> u8chr = { str[i], str[i + 1] };
				i++;
				m_str.push_back(u8char(u8chr));
			}
			else
			{
				std::vector<char> u8chr = { str[i] };
				m_str.push_back(u8char(u8chr));
			}
		}
	}

	u8string::u8string(std::vector<str::u8char> vector)
	{
		m_str = vector;
	}

	size_t u8string::size()
	{
		return m_str.size();
	}

	std::vector<str::u8char>::iterator u8string::begin()
	{
		return m_str.begin();
	}

	std::vector<str::u8char>::iterator u8string::end()
	{
		return m_str.end();
	}

	std::ostream& operator<<(std::ostream& os, u8string chr)
	{
		for (size_t i = 0; i < chr.size(); i++)
		{
			os << chr[i];
		}
		return os;
	}

	u8string operator+(const u8string& str1, const u8string& str2)
	{
		return u8string::concat(str1, str2);
	}

	u8string operator+(const u8string& str1, const u8char& str2)
	{
		u8string str = str1;
		str.m_str.push_back(str2);
		return str;
	}
	u8string operator+(const u8char& str1, const u8string& str2)
	{
		u8string str = str2;
		str.m_str.insert(str.m_str.begin(), str1);
		return str;
	}

	void u8string::operator+=(u8string& str)
	{
		for (size_t i = 0; i < str.size(); i++)
		{
			(*this) += str[i];
		}
	}

	void u8string::operator+=(const u8char& chr)
	{
		m_str.push_back(chr);
	}



	str::u8char& u8string::operator[](int i)
	{
		return this->m_str[i];
	}


	u8string u8string::concat(u8string str1, u8string str2)
	{
		u8string res = std::string(u8"");
		for (size_t i = 0; i < str1.size(); i++)
		{
			res += str1[i];
		}
		for (size_t i = 0; i < str2.size(); i++)
		{
			res += str2[i];
		}
		return res;
	}

	std::vector<str::u8char> u8string::to_u8char_vector()
	{
		return m_str;
	}
	
}