#include "PrintFunctions.h"

namespace print {

	void print(CityNode var)
	{
		std::cout << var.id << " -> x:" << var.x << " y:" << var.y << std::endl;
	}

}

std::ostream& operator<<(std::ostream& os, std::wstring str)
{
	os << str.c_str();
	return os;
}

std::ostream& operator<<(std::ostream& os, const sf::Color v)
{ 
	os<< "("<< (int)v.r<<", "<<(int)v.g<<", "<<(int)v.b<<", "<<(int)v.a<<")";
	return os;
}