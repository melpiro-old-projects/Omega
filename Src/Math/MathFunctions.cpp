#include "MathFunctions.h"

namespace math {
	double ToDeg(double rad)
	{
		return rad * STATIC::MATH::DEG_RAD;
	}
	double ToRad(double deg)
	{
		return deg * STATIC::MATH::RAD_DEG;
	}

	double round(double value, int nbChiffre)
	{
		return std::round(value * pow(10,nbChiffre) ) / pow(10, nbChiffre);
	}

	int getNbDigits(int nb)
	{
		if (nb == 0) return 1;
		return log10(std::abs(nb));
	}

	sf::Vector2f normalise(sf::Vector2f vec)
	{
		double angle = math::getAngle(sf::Vector2f(0,0), vec);
		return sf::Vector2f(std::cos(angle), std::sin(angle));
	}
	double dot(sf::Vector2f a, sf::Vector2f b)
	{
		return a.x * b.x + a.y * b.y;
	}

}