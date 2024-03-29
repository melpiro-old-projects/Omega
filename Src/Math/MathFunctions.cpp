#include "Math/MathFunctions.h"
namespace O{
namespace math {
	double ToDeg(const double& rad)
	{
		return rad * STATIC::MATH::DEG_RAD;
	}
	double ToRad(const double& deg)
	{
		return deg * STATIC::MATH::RAD_DEG;
	}

	double round(const double& value, const int& nbChiffre)
	{
		return std::round(value * pow(10,nbChiffre) ) / pow(10, nbChiffre);
	}

	int getNbDigits(const int& nb)
	{
		if (nb == 0) return 1;
		return log10(std::abs(nb));
	}

	sf::Vector2f normalise(const sf::Vector2f& vec)
	{
		double angle = math::getAngle(sf::Vector2f(0,0), vec);
		return sf::Vector2f(std::cos(angle), std::sin(angle));
	}
	double dot(const sf::Vector2f& a, const sf::Vector2f& b)
	{
		return a.x * b.x + a.y * b.y;
	}
	double dot(const sf::Vector3f& a, const sf::Vector3f& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}


	std::function<double (double)> getDerivative(double (* function)(double))
	{
		return [function](double n)->double {
			return (function(n) - function(n + 0.000000000001)) / (-0.000000000001);
		};
	}

	int hex_to_decimal(char const& hex)
	{
		if (hex >= '0' && hex <= '9')
			return hex - '0';
		else if  (hex >= 'A' && hex <= 'F')
			return hex - 'A' + 10;
		else if  (hex >= 'a' && hex <= 'f')
			return hex - 'a' + 10;
		
		return 0;
	}

	int hex_to_decimal(std::string const& hex)
	{
		int res = 0;
		int pow = 1;
		for (int i = 0; i < hex.size(); i++)
		{
			char c = hex[hex.size() - 1 - i];
			res += hex_to_decimal(c) * pow;
			if (i + 1<= hex.size())
				pow *= 16;
		}
		return res;
	}



}
}