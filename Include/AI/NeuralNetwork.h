
#pragma once
#include <vector>
#include <iostream>
#include <math.h> 
#include <fstream>

#include "VectorFunctions.h"
#include "MathFunctions.h"


#include "RandomFunctions.h"


namespace ActivationFunction {
	//fonction d'activation
	long double sigmoide(long double x, bool prime = false);
	long double tanh(long double x, bool prime = false);
	long double atan(long double x, bool prime = false);
	long double sin(long double x, bool prime = false);
	long double relu(long double x, bool prime = false);
}

namespace CostFunction {
	long double linear(long double y, long double y_, bool prime = false);
	long double logarithmic_binary(long double y, long double y_, bool prime = false);
	long double logarithmic_categorical(long double y, long double y_, bool prime = false);
}

class NeuralNetwork
{
public:
	NeuralNetwork();

	void addLayer(int nbNeurons, long double(*actiationFunction)(long double, bool));
	void clear();

	// crée les instances de allLink en fonction des couches
	void createLink();

	void setCostFunction(long double(*costFunction)(long double, long double, bool));
	long double getCost(std::vector<long double> y, std::vector<long double> y_);
	//double getCost(std::vector< std::vector<double> > y, std::vector < std::vector<double> > y_);

	// dérivée de la fonction de cout
	// par apport à l'activation du i eme neurone de
	// la couche d'output
	void backpropagation(long double alpha, std::vector<long double> y, std::vector<long double> y_);

	//initialisation
	void initWeight(long double value);
	void initWeight(long double min, long double max);
	void initBiais(long double value);
	void initBiais(long double min, long double max);
	
	//NeuralNetwork& operator=(NeuralNetwork const& n);
	//NeuralNetwork(NeuralNetwork const& n);

	std::vector<long double> getOutput(std::vector<long double> input);
	//std::vector<std::vector<double>> getOutputs(std::vector < std::vector<double> > inputs);

	std::vector<int> getAllLayerNeurone();
	std::vector<std::vector<long double>> getAllLayerNeuroneBiais();
	std::vector<std::vector<std::vector<long double>>> getAllLink();

	void mutation(double coefMutation, double minW, double maxW, double minB, double maxB);
	void mutationAdd(double coefMutation, double minW, double maxW, double minB, double maxB);
	void cross(NeuralNetwork n, double t); // on récupère t pourcent de n

	void addNeurons(int layer, int nbNeurons, double min = 0.1, double max = 0.1, double ratio = 100);

	long double getWeightScale();
	long double getBiaisScale();

	void save(std::ofstream& file);
	void load(std::string str);

private:

	int m_nbCouches = 0;
	std::vector<int> m_nbNeroneCouche;

	// liste des biais de chaques neurones
	std::vector<std::vector<long double>>m_allBiais;

	// liste des conections de la couche [i] partant du neurone [j] allant au neurone [k] de la couche  [i+1]
	std::vector<std::vector<std::vector<long double>>> m_allLink;

	// les activations de chaques couches
	std::vector<long double(*)(long double, bool)> m_allActivationFunction;


	// charactéristiques des chouches (sauvegarde pour la desentre de gradiant)
	std::vector<std::vector<long double>> m_allAgragationValue;
	std::vector<std::vector<long double>> m_allOutput;
	
	// fonction de cout
	long double(*m_costFunction)(long double, long double, bool);

};



