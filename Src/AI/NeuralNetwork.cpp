#include "NeuralNetwork.h"



NeuralNetwork::NeuralNetwork()
{

}

void NeuralNetwork::addLayer(int nbNeurons, long double(*actiationFunction)(long double, bool))
{
	m_nbNeroneCouche.push_back(nbNeurons);
	m_allActivationFunction.push_back(actiationFunction);
	m_allBiais.push_back(std::vector<long double>(nbNeurons));
	m_allAgragationValue.push_back(std::vector<long double>(nbNeurons));
	m_allOutput.push_back(std::vector<long double>(nbNeurons));
	
	
}

void NeuralNetwork::clear()
{
	m_nbCouches = 0;
	m_nbNeroneCouche.clear();
	m_allBiais.clear();
	m_allLink.clear();
	m_allAgragationValue.clear();
	m_allActivationFunction.clear();
	m_allOutput.clear();
}


void NeuralNetwork::createLink()
{
	m_nbCouches = m_nbNeroneCouche.size();
	m_allLink.clear();

	// pour chaques couche sauf la dernière qui n'est pas connectée
	for (int i = 0; i < m_nbCouches - 1; i++)
	{
		std::vector<std::vector<long double>> neuronLayer;
		for (size_t j = 0; j < m_nbNeroneCouche[i]; j++)
		{
			// pour chaques neurones de la couche suivante
			std::vector<long double> neuroneConnectedTohim;
			for (size_t k = 0; k < m_nbNeroneCouche[i + 1]; k++)
			{
				neuroneConnectedTohim.push_back(0);
			}
			neuronLayer.push_back(neuroneConnectedTohim);
		}
		m_allLink.push_back(neuronLayer);
	}
}


void NeuralNetwork::setCostFunction(long double(*costFunction)(long double, long double, bool))
{
	m_costFunction = costFunction;
}

long double NeuralNetwork::getCost(std::vector<long double> y, std::vector<long double> y_)
{
	long double moyenne = 0;
	for (size_t i = 0; i < y.size(); i++)
	{
		moyenne += m_costFunction(y[i], y_[i], false);
	}
	return moyenne / ((long double)y.size());
}

void NeuralNetwork::backpropagation(long double alpha, std::vector<long double> y, std::vector<long double> y_)
{

	// initialisation des variables
	int L = m_nbCouches - 1;
	std::vector<std::vector<long double>> delta;
	for (size_t i = 0; i < m_nbCouches; i++)
	{
		std::vector<long double> v;
		vector::initVector(v, m_nbNeroneCouche[i], (long double)0.0);
		delta.push_back(v);
	}

	// back prop
	for (int l = L; l > 0; l--)
	{
		for (int i = 0; i < m_nbNeroneCouche[l]; i++)
		{
			// si on est dans la première couche
			// s[L][i] = f'(z[L][i]) * c'(a[L][i])

			if (l == L)
			{
				
				delta[L][i] = m_allActivationFunction[L](m_allAgragationValue[L][i], true) * m_costFunction(y[i],y_[i], true);
			}
			else
			{
				long double sum = 0;
				for (size_t j = 0; j < m_nbNeroneCouche[l + 1]; j++)
				{
					sum += m_allLink[l][i][j] * delta[l + 1][j];
				}
				delta[l][i] = m_allActivationFunction[l](m_allAgragationValue[l][i], true) * sum;
			}
			// on ajuste les poids :
			for (size_t j = 0; j < m_nbNeroneCouche[l - 1]; j++)
			{
				long double c_w = m_allOutput[l-1][j] * delta[l][i];
				m_allLink[l - 1][j][i] -= alpha * c_w;

			}
			// on ajuste le biais
			long double c_b = delta[l][i];
			m_allBiais[l][i] -= alpha * c_b;
		}
	}	
}

void NeuralNetwork::initWeight(long double value)
{
	for (size_t i = 0; i < m_allLink.size(); i++)
	{
		for (size_t j = 0; j < m_allLink[i].size(); j++)
		{
			for (size_t k = 0; k < m_allLink[i][j].size(); k++)
			{
				m_allLink[i][j][k] = value;
			}
		}
	}
}


void NeuralNetwork::initWeight(long double min, long double max)
{
	for (size_t i = 0; i < m_allLink.size(); i++)
	{
		for (size_t j = 0; j < m_allLink[i].size(); j++)
		{
			for (size_t k = 0; k < m_allLink[i][j].size(); k++)
			{
				do {
					m_allLink[i][j][k] = math::randFloat(min, max);
				} while (m_allLink[i][j][k] == 0);
			}
		}
	}
}

void NeuralNetwork::initBiais(long double value)
{
	for (size_t i = 0; i < m_allBiais.size(); i++)
	{
		for (size_t j = 0; j < m_allBiais[i].size(); j++)
		{
			m_allBiais[i][j] = value;
		}
	}
}

void NeuralNetwork::initBiais(long double min, long double max)
{
	for (size_t i = 0; i < m_allBiais.size(); i++)
	{
		for (size_t j = 0; j < m_allBiais[i].size(); j++)
		{
			m_allBiais[i][j] = math::randFloat(min, max);
		}
	}
}


std::vector<long double> NeuralNetwork::getOutput(std::vector<long double> input)
{
	int i, j, k, i_1;

	for (i = 0; i < m_allAgragationValue.size(); i++)
	{
		for (j = 0; j < m_allAgragationValue[i].size(); j++)
		{
			m_allAgragationValue[i][j] = 0;
		}
	}

	m_allOutput[0] = input;
	

	// propagation avant
	// pour chaques couches (sauf la dernière qui ne transmet rien)
	for (i=0; i < m_nbCouches - 1; i++)
	{
		i_1 = i + 1;
		// pour chaques neurones de la couche
		for (j=0; j < m_nbNeroneCouche[i]; j++)
		{
			// on calcule les émission pondérée pour faire l'agrégation
			for (k=0; k < m_nbNeroneCouche[i_1]; k++)
			{
				m_allAgragationValue[i_1][k] += m_allOutput[i][j] * m_allLink[i][j][k];
			}
		}
		// pour chaques neurones de la couche suivante
		for (j=0; j < m_nbNeroneCouche[i_1]; j++)
		{
			// on ajoute son biais
			m_allAgragationValue[i_1][j] += m_allBiais[i_1][j];

			// on applique la fonction d'activation (sortie = f(agregation))
			m_allOutput[i_1][j] = m_allActivationFunction[i_1](m_allAgragationValue[i_1][j], false);

			// enfin on actualise la valeur du neurone
			//m_allNodes[i + 1][j] = m_allOutput[i + 1][j];
		}

	}

	//on retourne la couche d'output
	return m_allOutput[m_allOutput.size() - 1];
}

//std::vector<std::vector<double>> NeuralNetwork::getOutputs(std::vector<std::vector<double>> inputs)
//{
//	std::vector<std::vector<double>> res;
//	for (size_t i = 0; i < inputs.size(); i++)
//	{
//		res.push_back(getOutput(inputs[i]));
//	}
//	return res;
//}



std::vector<int> NeuralNetwork::getAllLayerNeurone()
{
	return m_nbNeroneCouche;
}

std::vector<std::vector<long double>> NeuralNetwork::getAllLayerNeuroneBiais()
{
	return m_allBiais;
}

std::vector<std::vector<std::vector<long double>>> NeuralNetwork::getAllLink()
{
	return m_allLink;
}

void NeuralNetwork::mutation(double coefMutation, double minW, double maxW, double minB,double maxB)
{
	for (size_t i = 0; i < m_allLink.size(); i++)
	{
		for (size_t j = 0; j < m_allLink[i].size(); j++)
		{
			for (size_t k = 0; k < m_allLink[i][j].size(); k++)
			{
				if (math::randFloat(0, 100) <= coefMutation)
				{
					m_allLink[i][j][k] = math::randFloat(minW, maxW);
				}
			}
		}
	}
	for (size_t i = 0; i < m_allBiais.size(); i++)
	{
		for (size_t j = 0; j < m_allBiais[i].size(); j++)
		{
			if (math::randFloat(0, 100) <= coefMutation)
			{
				m_allBiais[i][j] = math::randFloat(minW, maxW);
			}
		}
	}
}

void NeuralNetwork::mutationAdd(double coefMutation, double minW, double maxW, double minB, double maxB)
{
	for (size_t i = 0; i < m_allLink.size(); i++)
	{
		for (size_t j = 0; j < m_allLink[i].size(); j++)
		{
			for (size_t k = 0; k < m_allLink[i][j].size(); k++)
			{
				if (math::randFloat(0, 100) <= coefMutation)
				{
					m_allLink[i][j][k] += math::randFloat(minW, maxW);
				}
			}

		}
	}
	for (size_t i = 0; i < m_allBiais.size(); i++)
	{
		for (size_t j = 0; j < m_allBiais[i].size(); j++)
		{
			if (math::randFloat(0, 100) <= coefMutation)
			{
				m_allBiais[i][j] += math::randFloat(minW, maxW);
			}
		}
	}
}

void NeuralNetwork::cross(NeuralNetwork n, double t)
{
	for (size_t i = 1; i < m_nbCouches; i++)
	{
		for (size_t j = 0; j < m_nbNeroneCouche[i]; j++)
		{
			if (math::randFloat(0, 100) < t)
			{
				m_allBiais[i][j] = n.m_allBiais[i][j];

				for (size_t k = 0; k < m_nbNeroneCouche[i-1]; k++)
				{
					m_allLink[i-1][k][j] = n.m_allLink[i-1][k][j];
				}

			}
		}
	}
}

void NeuralNetwork::addNeurons(int layer, int nbNeurons, double min, double max, double ratio)
{
	m_nbNeroneCouche[layer] += nbNeurons;
	for (size_t i = 0; i < nbNeurons; i++)
	{
		m_allBiais[layer].push_back(math::randFloat(min, max));
		m_allAgragationValue[layer].push_back(0);
		m_allOutput[layer].push_back(0);
	}

	// pour chaques neurones de la couche précédante, on conecteeeee (sauf su on est dans la couche d'entre)
	if (layer != 0)
	{
		for (size_t i = 0; i < m_allLink[layer - 1].size(); i++)
		{
			// pour chaques nouveau neurones connectés
			for (size_t j = 0; j < nbNeurons; j++)
			{
				if (math::randFloat(0, 100) <= ratio)
				{
					m_allLink[layer - 1][i].push_back(math::randFloat(min, max));
				}
				else
				{
					m_allLink[layer - 1][i].push_back(0);
				}
			}
		}
	}

	// pour chaques neurones ajoutés on les conect a la couche suivante (sauf si on est dans la dernière couche)
	if (layer != m_nbCouches - 1)
	{
		// pour chaques nouveaux neurones
		for (size_t i = 0 ; i < nbNeurons; i++)
		{
			std::vector<long double> m_conectionForIemeNeuron;
			// pour chaques neurones de la couche suivant
			for (size_t j = 0; j < m_nbNeroneCouche[layer + 1]; j++)
			{
				if (math::randFloat(0, 100) <= ratio)
				{
					m_conectionForIemeNeuron.push_back(math::randFloat(min, max));
				}
				else
				{
					m_conectionForIemeNeuron.push_back(0);
				}
				
			}
			// on ajoute le lien
			m_allLink[layer].push_back(m_conectionForIemeNeuron);
		}
	}
	
}



long double NeuralNetwork::getWeightScale()
{
	return 1.0;
}

long double NeuralNetwork::getBiaisScale()
{
	return 1.0;
}

void NeuralNetwork::save(std::ofstream& file)
{
	file << m_nbCouches << '\n';
	for (size_t i = 0; i < m_nbNeroneCouche.size(); i++)
	{
		file << m_nbNeroneCouche[i] << " ";
	}
	file << "\n";
	for (size_t i = 0; i < m_nbCouches; i++)
	{
		if (m_allActivationFunction[i] == &ActivationFunction::atan)
		{
			file << 0 <<" ";
		}
		else if (m_allActivationFunction[i] == &ActivationFunction::tanh)
		{
			file << 1 << " ";
		}
		else if (m_allActivationFunction[i] == &ActivationFunction::relu)
		{
			file << 2 << " ";
		}
		else if (m_allActivationFunction[i] == &ActivationFunction::sigmoide)
		{
			file << 3 << " ";
		}
		else if (m_allActivationFunction[i] == &ActivationFunction::sin)
		{
			file << 4 << " ";
		}
	}
	file << "\n";
	for (size_t i = 0; i < m_nbCouches; i++)
	{
		for (size_t j = 0; j < m_nbNeroneCouche[i]; j++)
		{
			file << m_allBiais[i][j] << " ";
		}
		file << "\n";
	}
	for (size_t i = 0; i < m_nbCouches - 1; i++)
	{
		for (size_t j = 0; j < m_nbNeroneCouche[i]; j++)
		{
			for (size_t k = 0; k < m_nbNeroneCouche[i + 1]; k++)
			{
				file << m_allLink[i][j][k] << " ";
			}
			file << "\n";
		}
	}
	file << "#\n";
}

void NeuralNetwork::load(std::string str)
{
	clear();

	std::stringstream ss(str); // on lit le string comme un fichier
	ss >> m_nbCouches;
	for (size_t i = 0; i < m_nbCouches; i++)
	{
		int nbNeurone;
		ss >> nbNeurone;
		m_nbNeroneCouche.push_back(nbNeurone);
	}
	for (size_t i = 0; i < m_nbCouches; i++)
	{
		int idFunction;
		ss >> idFunction;
		switch (idFunction)
		{
		case 0:
			m_allActivationFunction.push_back(&ActivationFunction::atan);
			break;
		case 1:
			m_allActivationFunction.push_back(&ActivationFunction::tanh);
			break;
		case 2:
			m_allActivationFunction.push_back(&ActivationFunction::relu);
			break;
		case 3:
			m_allActivationFunction.push_back(&ActivationFunction::sigmoide);
			break;
		case 4:
			m_allActivationFunction.push_back(&ActivationFunction::sin);
			break;
		}
	}
	for (size_t i = 0; i < m_nbCouches; i++)
	{
		m_allBiais.push_back(std::vector<long double>(m_nbNeroneCouche[i]));
		m_allAgragationValue.push_back(std::vector<long double>(m_nbNeroneCouche[i]));
		m_allOutput.push_back(std::vector<long double>(m_nbNeroneCouche[i]));

		for (size_t j = 0; j < m_nbNeroneCouche[i]; j++)
		{
			double biais;
			ss >> biais;
			m_allBiais[i][j] = biais;
		}
	}
	for (size_t i = 0; i < m_nbCouches - 1; i++)
	{
		m_allLink.push_back(std::vector < std::vector<long double> >(m_nbNeroneCouche[i]));

		for (size_t j = 0; j < m_nbNeroneCouche[i]; j++)
		{
			m_allLink[i][j] = std::vector<long double>(m_nbNeroneCouche[i + 1]);
			for (size_t k = 0; k < m_nbNeroneCouche[i + 1]; k++)
			{
				double poid;
				ss >> poid;
				m_allLink[i][j][k] = poid;
			}
		}
	}
}

namespace ActivationFunction {
	long double sigmoide(long double x, bool prime)
	{
		if (prime) return sigmoide(x) * (1 - sigmoide(x));
		return 1.0 / (1 + exp(-x));
	}
	long double tanh(long double x, bool prime)
	{
		if (prime) return 1 - std::pow(tanh(x), 2);
		return std::tanh(x);
	}
	long double atan(long double x, bool prime)
	{
		if (prime) return 1.0 / (std::pow(x,2) + 1);
		return  std::atan(x);
	}
	long double sin(long double x, bool prime)
	{
		if (prime) return cos(x);
		return  std::sin(x);
	}
	long double relu(long double x, bool prime)
	{
		if (prime)
		{
			if (x >= 0) return 1.0;
			return 0;
		}
		if (x >= 0) return x;
		return 0;
	}
}

namespace CostFunction {
	long double linear(long double y, long double y_, bool prime)
	{

		if (prime)
		{
			
			return -2.0 * (y - y_);
			
		}
		return std::pow(y - y_, 2.0);
		
	}
	long double logarithmic_categorical(long double y, long double y_, bool prime)
	{
		if (prime)
		{
			return y * 1.0 / y_;
		}
		return y * log(y_);	
	}
	long double logarithmic_binary(long double y, long double y_, bool prime)
	{
		if (y_ == 0 || y_ == 1)
		{
			return 0;
		}
		
		if (prime)
		{
			return (y_- y) / y_*(1.0-y_);
		}
		return -(y * log(y_) + (1.0 - y) * log(1.0 - y_));
	}
}
