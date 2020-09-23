#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string.h>

#include "VectorFunctions.h"
#include "u8string.h"

namespace str {

	std::string subStr(std::string str, int start, int length);
	std::vector<std::string> split(std::string str, char sparator);
	std::vector<std::string> split(std::string str, std::string sparator);

	int findStrInStr(std::string string, std::string find);

	void toUpper(std::string& str);
	void toLower(std::string& str);
	void toUpper(char& c);
	void toLower(char& c);
	
	bool isNumber(std::string str);
	bool isNumber(sf::String str);

	bool isNumber(char c);
	bool isLetter(char c);
	bool isUpperCaseLetter(char c);
	bool isLowerCaseLetter(char c);

	std::string remove(std::string source, int from, int length);
	void remove(std::string* source, int from, int length);
	std::string remove(sf::String source, int from, int length);
	void remove(sf::String* source, int from, int length);

	void remplace(std::string& source, int from, int length, std::string str);
	void remplace(sf::String& source, int from, int length, sf::String str);
	int remplace(std::string& source, std::string strIn, std::string str);

	void insert(std::string& source, int index, std::string data);
	void insert(sf::String& source, int index, sf::String data);

	std::vector<char> generateRandomAlphabet();

	bool isVoyelle(char c);
	bool isConsone(char c);

	void swap(std::string& str, int i, int j);
	void reverse(std::string& str);

	std::string genStringNumPuissance(int nb);
	std::string genStringNumIndex(int nb);

	str::u8char getExposantOf(str::u8char c);
	str::u8string getExposantOf(str::u8string str);

	str::u8char getIndexOf(str::u8char c);
	str::u8string getIndexOf(str::u8string str);

	int getOccurences(std::string str, char c);

	std::vector<char> toCharVector(std::string str);

}

namespace std {
	std::string to_string(char c);
	std::string to_string(double value, int precision);
	std::string to_string(std::vector<char> vec);

	int to_int(std::string str);
	int to_int(char c);

	float to_float(std::string str);
	double to_double(std::string str);
}


std::string operator*(std::string str, int m);
std::string operator*(int m, std::string str);

void operator*=(std::string& str, const int& m);
