#include "u8char.h"
#include "u8string.h"

namespace str
{
	

	u8char::u8char() {
		
	}

	u8char::u8char(std::string chr) :u8char()
	{
		for (int i = chr.size() - 1; i >= 0 ; i--)
		{
			m_car.push_back(chr[i]);
		}
		calcValueFromChar();
	}

	u8char::u8char(std::vector<char> car):u8char()
	{
		m_car = car;
		calcValueFromChar();
	}
	

	u8char::u8char(const unsigned int car):u8char()
	{
		m_value = car;
		calcCharFromValue();
	}


	u8char::u8char(const u8char& chr) :u8char()
	{
		m_value = chr.m_value;
		m_car = chr.m_car;
	}

	void u8char::operator+=(const unsigned int& i)
	{
		*this = *this + i;
	}

	void u8char::operator+=(const u8char& i)
	{
		*this = *this + i;
	}

	void u8char::operator-=(const unsigned int& i)
	{
		*this = *this + (i);
	}

	void u8char::operator-=(const u8char& i)
	{
		*this = *this + (i.m_value);
	}

	unsigned int u8char::toUInt()
	{
		return m_value;
	}

	char u8char::toChar()
	{
		return m_car[0];
	}

	void u8char::calcCharFromValue()
	{
		int nbOctet = u8char::getNbOctet(m_value);
		m_car.clear();
		m_car = std::vector<char>(nbOctet);

		unsigned int cpy = m_value;

		for (int i = 0; i < nbOctet; i++)
		{
			m_car[i] = cpy;
			cpy >>= 8;
		}
	}

	void u8char::calcValueFromChar()
	{
		std::vector<std::bitset<8>> x;
		for (size_t i = 0; i < m_car.size(); i++) {x.push_back(std::bitset<8>(m_car[i]));}

		std::bitset<32> num;
		for (size_t i = 0; i < x.size() * 8; i++)
		{
			num[i] = x[i/8][i % 8];
		}
		m_value = num.to_ulong();
	}

	std::ostream& operator<<(std::ostream& os, u8char chr)
	{
		std::string str = u8"";
		
		for (int i = chr.size() - 1; i >= 0; i--)
		{
			str += chr.m_car[i];
		}

		os << str;

		return os;
	}
	
	u8char operator+(const u8char& chr1, const u8char& chr2)
	{
		return u8char(chr1.m_value + chr2.m_value);
	}
	u8char operator+(const u8char& chr1, const unsigned int& i)
	{
		return u8char(chr1.m_value + i);
	}

	void u8char::operator=(const u8char& chr)
	{
		m_value = chr.m_value;
		m_car = chr.m_car;
	}

	void u8char::operator=(const short& chr)
	{
		m_value = chr;
		calcCharFromValue();
	}

	u8char::operator unsigned int()
	{
		return m_value;
	}

	void u8char::printBinary()
	{
		std::bitset<32> chrbin3 = m_value;

		std::cout <<"encodage de '"<< *this<<"' : " << std::endl;

		for (int i = m_car.size() - 1; i >= 0; i--)
		{
			std::cout << "chr "<<i+1<<" : " << std::bitset<8>(m_car[i]) << std::endl;
		}
		std::cout << "num ("<<m_value<<") : " << chrbin3 << std::endl;
	}

	int u8char::getNbOctet(unsigned int chrValue)
	{
		unsigned int v = 0;
		for (size_t i = 1; i <= 4; i++)
		{
			if (chrValue < std::pow(2, 8 * i) + v) // 1 octet
			{
				return i;
			}
		}
		return -1;
	}

	int u8char::size()
	{
		return m_car.size();
	}

}

