#pragma once


#include <stdlib.h>
#include <ctime>
#include "BigInt.h"
#include "math.h"

namespace math {
	int randInt(int min, int max);
	BigInt randBigInt(BigInt min, BigInt max);
	double randFloat(double a, double b);
	double randFloat(double a, double b, int nb_digit);
}
