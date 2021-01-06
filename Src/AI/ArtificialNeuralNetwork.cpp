#include "AI/ArtificialNeuralNetwork.hpp"


namespace O
{
namespace AI
{

ArtificialNeuralNetwork::ArtificialNeuralNetwork()
{

}

void ArtificialNeuralNetwork::addLayer(int nbNeurons, long double(*actiationFunction)(long double))
{
	w.push_back(O::math::Matrix<long double>(nbNeurons, nbLayer == 0 ? 0 : a.back().getNbLine()));
	wv.push_back(O::math::Matrix<long double>(nbNeurons, nbLayer == 0 ? 0 : a.back().getNbLine()));
	b.push_back(O::math::Matrix<long double>(nbNeurons,1,0.0));
	bv.push_back(O::math::Matrix<long double>(nbNeurons,1,0.0));
	a.push_back(O::math::Matrix<long double>(nbNeurons,1,0.0));
	z.push_back(O::math::Matrix<long double>(nbNeurons,1,0.0));
	s.push_back(O::math::Matrix<long double(*)(long double)>(nbNeurons,1,actiationFunction));
	s_.push_back(O::math::Matrix<long double(*)(long double)>(nbNeurons,1, ActivationFunction::getPrime(actiationFunction)));
    
	nbLayer ++;
}
void ArtificialNeuralNetwork::addLayer(O::math::Matrix<long double> _w, O::math::Matrix<long double> _b, long double(*actiationFunction)(long double))
{
	w.push_back(_w);
	wv.push_back(O::math::Matrix<long double>(_w.getNbLine(), _w.getNbCollumn(), 0.0));
	b.push_back(_b);
	bv.push_back(O::math::Matrix<long double>(_b.getNbLine(),_b.getNbCollumn(),0.0));
	a.push_back(O::math::Matrix<long double>(_b.getNbLine(),_b.getNbCollumn(),0.0));
	z.push_back(O::math::Matrix<long double>(_b.getNbLine(),_b.getNbCollumn(),0.0));
	s.push_back(O::math::Matrix<long double(*)(long double)>(_b.getNbLine(),_b.getNbCollumn(),actiationFunction));
	s_.push_back(O::math::Matrix<long double(*)(long double)>(_b.getNbLine(),_b.getNbCollumn(), ActivationFunction::getPrime(actiationFunction)));
    
	nbLayer ++;
}

void ArtificialNeuralNetwork::clear()
{
    w.clear();
    wv.clear();
	b.clear();
	bv.clear();
	a.clear();
	z.clear();
	s.clear();
	s_.clear();
	nbLayer = 0;
}

void ArtificialNeuralNetwork::setCostFunction(long double(*costFunction)(long double, long double))
{
    cost = costFunction;
	cost_ = CostFunction::getPrime(cost);
}
long double ArtificialNeuralNetwork::getCost(O::math::Matrix<long double> y, O::math::Matrix<long double> y_)
{
    long double moyenne = 0;
	for (size_t i = 0; i < y.getNbLine(); i++)
	{
		moyenne += cost(y[i][0], y_[i][0]);
	}
	return moyenne / ((long double)y.getNbLine());
}
void ArtificialNeuralNetwork::backpropagation(long double alpha, O::math::Matrix<long double> y,O::math:: Matrix<long double> y_)
{
	backpropagation(alpha, 0, 1, y, y_);
}
void ArtificialNeuralNetwork::backpropagation(long double alpha, long double momentumConservation, long double momentum, O::math::Matrix<long double> y,O::math:: Matrix<long double> y_)
{
    // initialisation des variables
	// L -> actual Layer
	std::vector<O::math::Matrix<long double>> wcpy;

	for (size_t i = 0; i < w.size(); i++)
	{
		wcpy.push_back(O::math::Matrix<long double>(
			w[i].getNbLine(),
			w[i].getNbCollumn(),
			0));

		for (size_t j = 0; j < w[i].getNbLine(); j++)
		{
			for (size_t k = 0; k < w[i].getNbCollumn(); k++)
			{
				wcpy.back().setValue(j, k, w[i][j][k]);	
			}
		}
	}
	

	size_t L = nbLayer - 1;
	std::vector<O::math::Matrix<long double>> delta(nbLayer);
	for (size_t i = 0; i < delta.size(); i++)
	{
		delta[i] = O::math::Matrix<long double>(z[i].getNbLine(), 1, 0);
	}
	
	// back prop
	for (int l = L; l > 0; l--)
	{
		for (int i = 0; i < z[l].getNbLine(); i++)
		{
			// si on est dans la premi�re couche
			// s[L][i] = f'(z[L][i]) * c'(a[L][i])
			if (l == L)
			{
				delta[l][i][0] = s_[l][i][0](z[l][i][0]) * cost_(y[i][0],a[l][i][0]);
			}
			else
			{
				long double sum = 0;
				for (size_t j = 0; j < b[l + 1].getNbLine(); j++)
				{
					
					sum += (wcpy[l + 1][j][i]) * delta[l + 1][j][0];
				}

				delta[l][i][0] = s_[l][i][0](z[l][i][0]) * sum;

				
			}

			// on ajuste les poids :
			for (size_t j = 0; j < a[l - 1].getNbLine(); j++)
			{
				long double c_w = a[l-1][j][0] * delta[l][i][0];

				wv[l][i][j] = momentumConservation * wv[l][i][j] + momentum * c_w;
				w[l][i][j] -= alpha * wv[l][i][j] ;
				//w[l][i][j] -= alpha * c_w ;
				
				

			}
			// on ajuste le biais
			long double c_b = delta[l][i][0];

			bv[l][i][0] = momentumConservation * bv[l][i][0] + momentum * c_b;
			b[l][i][0] -= alpha * bv[l][i][0];
			//b[l][i][0] -= alpha * c_b;
		}

	}	

	
}
O::math::Matrix<long double> ArtificialNeuralNetwork::getOutput(O::math::Matrix<long double> X) 
{
	a[0] = X;

    for (size_t i = 1; i < nbLayer; i++)
	{
		if (m_debug && i == 2)
		{
			//std::cout << w[i][0][0] <<std::endl;
		}
		z[i] = w[i] * a[i - 1] + b[i];
		a[i] = s[i](z[i]);

	}
	return a.back();
}

O::math::Matrix<long double> ArtificialNeuralNetwork::getCostPrimeMatrix(O::math::Matrix<long double> y, O::math::Matrix<long double> y_)
{
	O::math::Matrix<long double> res(y.getNbLine(), y.getNbCollumn(), 0);
	for (size_t i = 0; i < y.getNbLine(); i++)
	{
		res[i][0] = cost_(y[i][0], y_[i][0]);
	}
	return res;
}


void ArtificialNeuralNetwork::initWeight(const double& min, const double& max)
{
	for (size_t i = 1; i < w.size(); i++)
	{
		for (size_t n = 0; n < w[i].getNbLine(); n++)
		{
			for (size_t m = 0; m < w[i].getNbCollumn(); m++)
			{
				float v;
				do{
					v = O::math::rdm::randFloat(min, max);
				}while (v == 0);
				
				w[i].setValue(n, m, v);
			}
			
		}
		
	}
	
}
void ArtificialNeuralNetwork::initBiais(const double& min, const double& max)
{
	for (size_t i = 1; i < b.size(); i++)
	{
		for (size_t n = 0; n < b[i].getNbLine(); n++)
		{
			float v;
			do{
				v = O::math::rdm::randFloat(min, max);
			}while (v == 0);
			b[i].setValue(n, 0, v);
		}
		
	}
}

std::vector<O::math::Matrix<long double>> ArtificialNeuralNetwork::getWeight() const
{
	return w;
}
std::vector<O::math::Matrix<long double>> ArtificialNeuralNetwork::getBias() const
{
	return b;
}
std::vector<O::math::Matrix<long double(*)(long double)>> ArtificialNeuralNetwork::getActivationFunction() const
{
	return s;
}


int ArtificialNeuralNetwork::getNbLayer() const
{
	return nbLayer;
}

std::vector<int> ArtificialNeuralNetwork::getLayersStructure()
{
	std::vector<int> v;

	for (size_t i = 0; i < nbLayer; i++)
	{
		v.push_back(b[i].getNbLine());
	}
	return v;
}

std::ofstream& operator<<( std::ofstream &flux, ArtificialNeuralNetwork const& m )
{
	flux << m.getNbLayer()<<" ";
	for (size_t i = 0; i < m.getNbLayer(); i++)
	{
		flux << m.getWeight()[i]<<" ";
		flux << m.getBias()[i]<<" ";
		if (m.getActivationFunction()[i][0][0] == AI::ActivationFunction::sigmoid)
		{
			flux << 0<<" ";
		}
		else if (m.getActivationFunction()[i][0][0] == AI::ActivationFunction::tanh)
		{
			flux << 1<<" ";
		}
		else if (m.getActivationFunction()[i][0][0] == AI::ActivationFunction::atan)
		{
			flux << 2<<" ";
		}
		else if (m.getActivationFunction()[i][0][0] == AI::ActivationFunction::sin)
		{
			flux << 3<<" ";
		}
		else if (m.getActivationFunction()[i][0][0] == AI::ActivationFunction::relu)
		{
			flux << 4<<" ";
		}
	}
	return flux;
}
std::ifstream& operator>>( std::ifstream &flux, ArtificialNeuralNetwork& m)
{
	int nbLayer;
	flux >> nbLayer;

	for (size_t i = 0; i < nbLayer; i++)
	{
		O::math::Matrix<long double> _w, _b;
		int idFunction = -1;
		flux >> _w >> _b >> idFunction;
		long double(*_actiationFunction)(long double);

		if (idFunction == 0) _actiationFunction = AI::ActivationFunction::sigmoid;
		if (idFunction == 1) _actiationFunction = AI::ActivationFunction::tanh;
		if (idFunction == 2) _actiationFunction = AI::ActivationFunction::atan;
		if (idFunction == 3) _actiationFunction = AI::ActivationFunction::sin;
		if (idFunction == 4) _actiationFunction = AI::ActivationFunction::relu;

		m.addLayer(_w, _b, _actiationFunction);
	}

	return flux;
}


long double ArtificialNeuralNetwork::computeCostFor(int l ,int i, int j, long double wvalue, O::math::Matrix<long double> X, O::math::Matrix<long double> Y)
{
	long double saveW = w[l][i][j];
	m_debug = true;

	w[l][i][j] = wvalue;
	O::math::Matrix<long double> out = getOutput(X);
	long double res = getCost(Y, out);

	//std::cout << out<<" "<<res <<std::endl;

	w[l][i][j] = saveW;
	m_debug = false;
	

	return res;
}


void ArtificialNeuralNetwork::mutateWeight(const double& pourcent, const long double& min, const long double& max)
{
	for (size_t l = 1; l < nbLayer; l++)
	{
		for (size_t i = 0; i < w[l].getNbCollumn(); i++)
		{
			for (size_t j = 0; j < w[l].getNbLine(); j++)
			{
				if (O::math::rdm::randFloat(0, 100) < pourcent)
				{
					w[l].setValue(j, i, O::math::rdm::randDouble(min, max));
				}
			}
		}
	}
}
void ArtificialNeuralNetwork::mutateBiais(const double& pourcent, const long double& min, const long double& max)
{
	for (size_t l = 1; l < nbLayer; l++)
	{
		for (size_t i = 0; i < w[l].getNbLine(); i++)
		{
			if (O::math::rdm::randFloat(0, 100) < pourcent)
			{
				b[l].setValue(i, 0, O::math::rdm::randDouble(min, max));
			}
		}
	}
}
void ArtificialNeuralNetwork::mutateWeight(const double& pourcent, const long double& delta)
{
	for (size_t l = 1; l < nbLayer; l++)
	{
		for (size_t i = 0; i < w[l].getNbCollumn(); i++)
		{
			for (size_t j = 0; j < w[l].getNbLine(); j++)
			{
				if (O::math::rdm::randFloat(0, 100) < pourcent)
				{
					w[l].setValue(j, i, w[l].getValue(j, i) + O::math::rdm::randDouble(-delta, delta));
				}
			}
		}
	}
}
void ArtificialNeuralNetwork::mutateBiais(const double& pourcent, const long double& delta)
{
	for (size_t l = 1; l < nbLayer; l++)
	{
		for (size_t i = 0; i < w[l].getNbLine(); i++)
		{
			if (O::math::rdm::randFloat(0, 100) < pourcent)
			{
				b[l].setValue(i, 0, b[l].getValue(i, 0) + O::math::rdm::randDouble(-delta, delta));
			}
		}
	}
}
void ArtificialNeuralNetwork::crossOver(const ArtificialNeuralNetwork& other, const double& pourcent)
{
	for (size_t l = 1; l < nbLayer; l++)
	{
		for (size_t n = 0; n < w[l].getNbLine(); n++)
		{
			if (O::math::rdm::randFloat(0, 100) < pourcent)
			{
				int neuronDes = O::math::rdm::randInt(0, w[l].getNbLine());

				w[l][neuronDes] = other.w[l].getLine(n);
				b[l][neuronDes] = other.b[l].getLine(n);
			}
		}
	}
}



}}