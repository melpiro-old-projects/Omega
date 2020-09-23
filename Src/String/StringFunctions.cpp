#include "StringFunctions.h"
#include <iomanip>

namespace str {

	std::string subStr(std::string str, int start, int length)
	{
		return str.substr(start, length);
	}
	///////////////////////////////////////////////////////////////
	std::vector<std::string> split(std::string str, char sparator)
	{
		std::vector<std::string> res;
		int lastCutIndex = 0;
		for (size_t i = 0; i < str.size(); i++)
		{
			if (str[i] == sparator)
			{
				res.push_back(subStr(str, lastCutIndex, i - lastCutIndex));
				lastCutIndex = i + 1;
			}
		}
		res.push_back(subStr(str, lastCutIndex, str.size()));
		return res;
	}
	///////////////////////////////////////////////////////////////
	std::vector<std::string> split(std::string str, std::string sparator)
	{
		std::vector<std::string> res;
		int lastCutIndex = 0;
		for (size_t i = 0; i < str.size(); i++)
		{
			if (subStr(str, i, sparator.size()) == sparator)
			{
				res.push_back(subStr(str, lastCutIndex, i - lastCutIndex));
				i += sparator.size() - 1;
				lastCutIndex = i + 1;
			}
		}
		res.push_back(subStr(str, lastCutIndex, str.size()));
		return res;
	}
	///////////////////////////////////////////////////////////////
	int findStrInStr(std::string string, std::string find)
	{
		if (find.size() > string.size()) return -1;
		for (size_t i = 0; i < string.size() - find.size() + 1; i++)
		{
			if (string.substr(i, find.size()) == find) return i;
		}
		return -1;

	}
	///////////////////////////////////////////////////////////////
	void toUpper(std::string& str)
	{
		std::for_each(str.begin(), str.end(), [](char& c) {
			c = ::toupper(c);
		});
	}
	///////////////////////////////////////////////////////////////
	void toLower(std::string& str)
	{
		std::for_each(str.begin(), str.end(), [](char& c) {
			c = ::tolower(c);
		});
	}
	///////////////////////////////////////////////////////////////
	void toUpper(char& c)
	{
		c = ::toupper(c);
	}
	///////////////////////////////////////////////////////////////
	void toLower(char& c)
	{
		c = ::tolower(c);
	}
	///////////////////////////////////////////////////////////////
	bool isNumber(std::string str)
	{
		bool point = false;
		if (str[0] == '-') str.erase(str.begin());
		for (size_t i = 0; i < str.size(); i++)
		{
			if (!point && i > 0 && i < str.size() - 1 && str[i] == '.')
			{
				point = true;
			}
			else if (!isNumber(str[i])) return false;
		}
		return true;
	}
	///////////////////////////////////////////////////////////////
	bool isNumber(sf::String str)
	{
		bool point = false;
		if (str[0] == '-') str.erase(0);
		for (size_t i = 0; i < str.getSize(); i++)
		{
			if (!point && i > 0 && i < str.getSize() - 1 && str[i] == '.')
			{
				point = true;
			}
			else if (!isNumber(str[i])) return false;
		}
		return true;
	}
	///////////////////////////////////////////////////////////////
	bool isNumber(char c)
	{
		return (c >= '0' && c <= '9');
	}
	///////////////////////////////////////////////////////////////
	bool isLetter(char c)
	{
		return isUpperCaseLetter(c) || isLowerCaseLetter(c);
	}
	///////////////////////////////////////////////////////////////
	bool isUpperCaseLetter(char c)
	{
		return (c >= 'A' && c <= 'Z');
	}
	///////////////////////////////////////////////////////////////
	bool isLowerCaseLetter(char c)
	{
		return (c >= 'a' && c <= 'z');
	}
	///////////////////////////////////////////////////////////////
	std::string remove(std::string source, int from, int length)
	{
		return subStr(source, 0, from) + subStr(source, from + length, source.size() - (from + length));
	}
	///////////////////////////////////////////////////////////////
	void remove(std::string* source, int from, int length)
	{
		*source = remove(*source, from, length);
	}
	///////////////////////////////////////////////////////////////
	std::string remove(sf::String source, int from, int length)
	{
		return source.substring(0, from) + source.substring(from + length, source.getSize() - (from + length));
	}
	///////////////////////////////////////////////////////////////
	void remove(sf::String* source, int from, int length)
	{
		*source = remove(*source, from, length);
	}
	///////////////////////////////////////////////////////////////
	void remplace(std::string& source, int from, int length, std::string str)
	{
		remove(&source, from, length);
		insert(source, from, str);
	}
	///////////////////////////////////////////////////////////////
	void remplace(sf::String& source, int from, int length, sf::String str)
	{
		remove(&source, from, length);
		insert(source, from, str);
	}
	///////////////////////////////////////////////////////////////
	int remplace(std::string& source, std::string strIn, std::string str)
	{
		int nb = 0;
		int v = -1;
		do {
			v = findStrInStr(source, strIn);

			if (v != -1)
			{
				remplace(source, v, strIn.size(), str);
				nb++;
			}

		} while (v != -1);
		return nb;
	}
	///////////////////////////////////////////////////////////////
	void insert(std::string& source, int index, std::string data)
	{
		for (size_t i = 0; i < data.size(); i++)
		{
			source.insert(source.begin() + index + i, data[i]);
		}

	}
	///////////////////////////////////////////////////////////////
	void insert(sf::String& source, int index, sf::String data)
	{
		source.insert(index, data);
	}

	///////////////////////////////////////////////////////////////
	std::vector<char> generateRandomAlphabet()
	{
		return vector::shuffle(vector::createVector(26, 'A', 1));

	}
	bool isVoyelle(char c)
	{
		if (!isLetter(c)) return false;
		str::toLower(c);
		return (c == 'a' || c == 'o' || c == 'i' || c == 'e' || c == 'u' || c == 'y');
	}
	bool isConsone(char c)
	{
		if (!isLetter(c)) return false;
		return !isVoyelle(c);
	}
	void swap(std::string& str, int i, int j)
	{
		char tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
	}
	void reverse(std::string& str)
	{
		std::string res = "";
		for (int i = str.size() - 1 ; i >= 0; i--)
		{
			res += str[i];
		}
		str = res;
	}

	str::u8char getExposantOf(str::u8char c)
	{
		if (isNumber(c))
		{
			char chr = c;
			switch (chr)
			{
			case '0':
				return str::u8char(u8"⁰");
			case '1':
				return str::u8char(u8"¹");
			case '2':
				return str::u8char(u8"²");
			case '3':
				return str::u8char(u8"²");
			case '4':
				return str::u8char(u8"⁴");
			case '5':
				return str::u8char(u8"⁵");
			case '6':
				return str::u8char(u8"⁶");
			case '7':
				return str::u8char(u8"⁷");
			case '8':
				return str::u8char(u8"⁸");
			case '9':
				return str::u8char(u8"⁹");
			}
		}

		return c;
	}

	str::u8string getExposantOf(str::u8string str)
	{
		for (size_t i = 0; i < str.size(); i++)
		{
			str[i] = getExposantOf(str[i]);
		}
		return str;
	}

	str::u8char getIndexOf(str::u8char c)
	{
		if (isNumber(c))
		{
			return str::u8char(c.toUInt() + 14844496);
		}

		return c;
	}

	str::u8string getIndexOf(str::u8string str)
	{
		for (size_t i = 0; i < str.size(); i++)
		{
			str[i] = getIndexOf(str[i]);
		}

		return str;
	}
	
	int getOccurences(std::string str, char c)
	{
		int nb = 0;
		for (size_t i = 0; i < str.size(); i++)
		{
			if (c == str[i]) nb ++;
		}
		return nb;
	}

	std::vector<char> toCharVector(std::string str)
	{
		return std::vector<char>(str.c_str(), str.c_str() + str.size());
	}
}	

std::string operator*(std::string str, int m)
{
	std::string res = "";
	for (int i = 0; i < m; i++)
	{
		res += str;
	}
	return res;
}

std::string operator*(int m, std::string str)
{
	std::string res = "";
	for (int i = 0; i < m; i++)
	{
		res += str;
	}
	return res;

}


void operator*=(std::string& str, const int& m)
{
	str = str * m;
}

std::string std::to_string(char c)
{
	return std::string(1, c);
}

std::string std::to_string(double value, int precision)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(precision) << value;
	std::string mystring = ss.str();

	return mystring;
}

std::string std::to_string(std::vector<char> vec)
{
	std::string str = "";
	for (size_t i = 0; i < vec.size(); i++)
	{
		str+=vec[i];
	}
	return str;
}

int std::to_int(std::string str)
{
	return atoi(str.c_str());
}

int std::to_int(char c)
{
	return to_int(to_string(c));
}

float std::to_float(std::string str)
{
	return atof(str.c_str());
}

double std::to_double(std::string str)
{
	return to_float(str);
}
