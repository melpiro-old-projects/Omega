#pragma once

#include <ostream>

#include <iostream>
#include <bitset>
#include <vector>
#include <cmath>

namespace str 
{

	class u8char
	{
	public:
		u8char();
		u8char(std::string chr);
		u8char(std::vector<char> car);
		u8char(const unsigned int car);
		u8char(const u8char& chr);

		friend std::ostream& operator<<(std::ostream& os, u8char chr);
		friend u8char operator+(const u8char& chr1, const u8char& chr2);
		friend u8char operator+(const u8char& chr1, const unsigned int& i);


		void operator=(const u8char& chr);
		void operator=(const short& chr);
		void operator+=(const unsigned int& i);
		void operator+=(const u8char& i);
		void operator-=(const unsigned int& i);
		void operator-=(const u8char& i);
		operator unsigned int();

		unsigned int toUInt();
		char toChar();

		void printBinary();

		static int getNbOctet(unsigned int chrValue);

		int size();


	private:

		void calcValueFromChar();
		void calcCharFromValue();

		std::vector<char> m_car;
		unsigned int m_value;
	};

}

