
#pragma once
#include "Math/Matrix.h"
#include <iostream>
#include <math.h> 
#include "Math/RandomFunctions.h"
#include "AI/AIFunctions.hpp"
#include "Operators/PrintFunctions.h"
#include <fstream>

namespace O
{
namespace AI
{


class ArtificialNeuralNetwork
{
public:
    ArtificialNeuralNetwork();

    void addLayer(int nbNeurons, long double(*actiationFunction)(long double));
    void addLayer(O::math::Matrix<long double> _w, O::math::Matrix<long double> _b, long double(*actiationFunction)(long double));
    void clear();

    void setCostFunction(long double(*costFunction)(long double, long double));
    long double getCost(O::math::Matrix<long double> y, O::math::Matrix<long double> y_);
    void backpropagation(long double alpha, O::math::Matrix<long double> y, O::math::Matrix<long double> y_);
    void backpropagation(long double alpha, long double momentumConservation, long double momentum, O::math::Matrix<long double> y, O::math::Matrix<long double> y_);
    O::math::Matrix<long double> getOutput(O::math::Matrix<long double> X);
 
    void initWeight(const double& min, const double& max);
    void initBiais(const double& min, const double& max);

    

    std::vector<O::math::Matrix<long double>> getWeight() const;
    std::vector<O::math::Matrix<long double>> getBias() const;
    std::vector<O::math::Matrix<long double(*)(long double)>> getActivationFunction() const;
    std::vector<int> getLayersStructure();

    long double computeCostFor(int l ,int i, int j, long double w, O::math::Matrix<long double> X, O::math::Matrix<long double> Y);
    
    void mutateWeight(const double& pourcent, const long double& min, const long double& max);
    void mutateBiais(const double& pourcent, const long double& min, const long double& max);
    void mutateWeight(const double& pourcent, const long double& delta);
    void mutateBiais(const double& pourcent, const long double& delta);
    void crossOver(const ArtificialNeuralNetwork& other, const double& pourcent);

    int getNbLayer() const;



    

private:

    O::math::Matrix<long double> getCostPrimeMatrix(O::math::Matrix<long double> y, O::math::Matrix<long double> y_);


    size_t nbLayer = 0;

    std::vector<O::math::Matrix<long double>> w;
    std::vector<O::math::Matrix<long double>> wv;
    std::vector<O::math::Matrix<long double>> b;
    std::vector<O::math::Matrix<long double>> bv;
    std::vector<O::math::Matrix<long double>> a;
    std::vector<O::math::Matrix<long double>> z;
    std::vector<O::math::Matrix<long double(*)(long double)>> s;
    std::vector<O::math::Matrix<long double(*)(long double)>> s_;

    long double(*cost)(long double, long double);
    long double(*cost_)(long double, long double);

    bool m_debug = false;
};

// ARTUNG LA FONCTION DE COUT N'EST PAS SAUVEGARDEE !
std::ofstream& operator<<( std::ofstream &flux, ArtificialNeuralNetwork const& m );
std::ifstream& operator>>( std::ifstream &flux, ArtificialNeuralNetwork& m);

}} 


