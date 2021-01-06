#include <math.h>
#include <iostream>

namespace O
{
namespace AI
{

namespace ActivationFunction {


	//fonction d'activation
	long double sigmoid(long double x);
	long double tanh(long double x);
	long double atan(long double x);
	long double sin(long double x);
	long double relu(long double x);
	long double elu(long double x);
	long double linear(long double x);

	long double sigmoidPrime(long double x);
	long double tanhPrime(long double x);
	long double atanPrime(long double x);
	long double sinPrime(long double x);
	long double reluPrime(long double x);
	long double eluPrime(long double x);
	long double linearPrime(long double x);


	long double(*getPrime(long double(*function)(long double)))(long double);
}

namespace CostFunction {
    long double linear(long double y, long double y_);
    long double logarithmic_binary(long double y, long double y_);
    long double logarithmic_categorical(long double y, long double y_);

    long double linearPrime(long double y, long double y_);
    long double logarithmic_binaryPrime(long double y, long double y_);
    long double logarithmic_categoricalPrime(long double y, long double y_);

    long double(*getPrime(long double(*function)(long double, long double)))(long double, long double);
}
}
}