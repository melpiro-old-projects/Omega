#include "AI/AIFunctions.hpp"

namespace O
{
namespace AI
{
namespace CostFunction {
	long double linear(long double y, long double y_) { return std::pow(y - y_, 2.0);}
	long double logarithmic_categorical(long double y, long double y_){
		return y * log(y_);	
	}
	long double logarithmic_binary(long double y, long double y_) {
		// if (y_ < std::pow(10, -20))
		// {
		// 	y_ = std::pow(10, -20);
		// }
		// else if (1.0 - y_ < std::pow(10, -20))
		// {
		// 	y_ = 1.0 - std::pow(10, -20);
		// }

		return -(y * std::log10(y_) + (1.0 - y) * std::log10(1.0 - y_)); 
		}
	
	long double linearPrime(long double y, long double y_){return 2.0 * (y_ - y);	}
	long double logarithmic_categoricalPrime(long double y, long double y_){return y * 1.0 / y_;}
	long double logarithmic_binaryPrime(long double y, long double y_){
		long double ln10 = std::log(10);
		// if (y_ < std::pow(10, -20))
		// {
		// 	y_ = std::pow(10, -20);
		// }
		// else if (1.0 - y_ < std::pow(10, -20))
		// {
		// 	y_ = 1.0 - std::pow(10, -20);
		// }
		return -(y/(y_*ln10))+((1.0-y)/((1.0-y_)*ln10));
	}

	
	long double(*getPrime(long double(*function)(long double, long double)))(long double, long double)
	{
		if (function == CostFunction::linear) return CostFunction::linearPrime;
		if (function == CostFunction::logarithmic_categorical) return CostFunction::logarithmic_categoricalPrime;
		if (function == CostFunction::logarithmic_binary) return CostFunction::logarithmic_binaryPrime;

		return NULL;
	}
}


namespace ActivationFunction {
	long double sigmoid(long double x){return 1.0l / (1.0l + std::exp(-x));}
	long double tanh(long double x){return std::tanh(x);}
	long double atan(long double x){return  std::atan(x);}
	long double sin(long double x){return  std::sin(x);}
	long double relu(long double x){return x >= 0.l ? x : 0.l;}
	long double elu(long double x){return x > 0.l ? x : exp(x) - 1;}
	long double linear(long double x){return x;}

	long double sigmoidPrime(long double x){return sigmoid(x) * (1 - sigmoid(x));}
	long double tanhPrime(long double x){return 1.0l - std::pow(tanh(x), 2.l);}
	long double atanPrime(long double x){return 1.0l / (std::pow(x,2.) + 1.l);}
	long double sinPrime(long double x){return cos(x);}
	long double reluPrime(long double x){return x > 0.l ? 1.l : 0.l;}
	long double eluPrime(long double x){return x > 0.l ? 1.l : exp(x);}
	long double linearPrime(long double x){return 1.l;}

	long double(*getPrime(long double(*function)(long double)))(long double)
	{
		if (function == ActivationFunction::sigmoid) return ActivationFunction::sigmoidPrime;
		if (function == ActivationFunction::tanh) return ActivationFunction::tanhPrime;
		if (function == ActivationFunction::atan) return ActivationFunction::atanPrime;
		if (function == ActivationFunction::sin) return ActivationFunction::sinPrime;
		if (function == ActivationFunction::relu) return ActivationFunction::reluPrime;
		if (function == ActivationFunction::linear) return ActivationFunction::linearPrime;

		return NULL;
	}
}


}}