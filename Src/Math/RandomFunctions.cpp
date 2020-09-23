#include "RandomFunctions.h"


namespace math {
	int randInt(int min, int max)
	{
		if (max - min == 0) return min;
		return min + (rand() % (max - min));
	}
	BigInt randBigInt(BigInt min, BigInt max)
	{
		std::string str;
		size_t mis = min.size();
		size_t mas = max.size();
		size_t size = 0;
		if (mis == mas) size = mis;
		else size = math::randInt(mis, mas);
		for (size_t i = 0; i < size; i++)
		{
			str += randInt('0','9' + 1);
		}
		return BigInt(str);
	}

	double randFloat(double a, double b) {
		return ((double)rand() / (double)RAND_MAX) * (b - a) + a;
	}

	
	double randFloat(double a, double b, int nb_digit)
	{
		double mult = std::pow(10, nb_digit);
		return ((double)((int)(randFloat(a,b) * mult))) / mult;
	}
}