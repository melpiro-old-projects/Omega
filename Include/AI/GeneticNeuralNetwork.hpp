#pragma once
#include "AI/AIFunctions.hpp"
#include "Data/triplet.h"
#include <vector>
#include "Math/RandomFunctions.h"
namespace O
{
namespace AI
{
    

class Neuron{
public:
    Neuron() :
        out(0)
    {

    }
    std::vector<O::data::triplet<int,int, long double>> out; 
    long double(*activationFunction)(long double) = O::AI::ActivationFunction::linear;
    long double biais = 0.l;
    long double agregation = 0.l;
    long double activation = 0.l;
    
};

class GeneticNeuralNetwork
{
public:
    GeneticNeuralNetwork();

    // init
    void setInputLayerSize(const int& size);
    void setOutputLayerSize(const int& size, long double (*activationFunction)(long double));
    void construct();
    
    // rester
    void clear();

    //base
    std::vector<long double> getOutput(std::vector<long double> input);
    std::vector<double> getOutput(std::vector<double> input);
    
    // geteurs
    int getLayerSize(int layer);
    std::vector<int> getLayersStructure();
    int getNbLayer();
    bool haveConnexion(int layerIndexFrom, int neuronIndexFrom, int layerIndexTo, int neuronIndexTo);
    std::pair<std::pair<int,int>,std::pair<int,int>> getRdmConnextion();
    O::data::triplet<int, int, int> getRdmConnextionByIndex();
    O::data::triplet<int, int, int> getRdmConnextionByIndex(const int& minfromLayer);
    long double getMaxWeightAbs();
    long double getMaxBiaisAbs();

    //rdm mutation
    void mutateWeight(const double& pourcent, const long double& min, const long double& max);
    void mutateBiais(const double& pourcent, const long double& min, const long double& max);
    void mutateWeight(const double& pourcent, const long double& delta);
    void mutateBiais(const double& pourcent, const long double& delta);
    void mutateBiais(const double& pourcent,const int& layerMin, const long double& min, const long double& max);
    bool mutateAddConnection(const double& minW, const double& maxW);
    bool mutateAddConnectedNeuron(const int& nbInputConnexion, const int& nbOutputConnexion, long double(*activationFunction)(long double) ,const double& minB, const double& maxB, const double& minW, const double& maxW);
    void mutateAddConectedLayer(const int& nbNeurons, const int& nbInputConnexion, const int& nbOutputConnexion, long double(*activationFunction)(long double) ,const double& minB, const double& maxB, const double& minW, const double& maxW);
    bool mutateRemoveConnection();
    bool mutateRemoveConnection(const int& minfromLayer);
    bool mutateMoveConnectionInput();
    bool mutateMoveConnectionOutput();
    bool mutateDuplicateConnectionOutput();
    void mutateCrossOver(O::AI::GeneticNeuralNetwork& ann);

    
    // modifieurs
    int addNeuronInLayer(int layerIndex, long double (*activationFunction)(long double), long double biais = 0.l);
    bool addConnexion(int layerIndexFrom, int neuronIndexFrom, int layerIndexTo, int neuronIndexTo, long double w);
    void addLayer(int index);
    bool removeConnexion(int layerIndexFrom, int neuronIndexFrom, int layerIndexTo, int neuronIndexTo);
    bool removeConnexion(int layerIndexFrom, int neuronIndexFrom, int outIndex);
    void removeConnexionsFromLayer(int layerIndexFrom);
    void setBiaisOfLayer(int layerIndexFrom, long double biais);
    void removeNeuron(int layer, int index);
    void removeLayer(int layer);
    std::pair<int,int> splitTransition(int layerIndexFrom, int neuronIndexFrom, int layerIndexTo, int neuronIndexTo, long double (*activationFunction)(long double));
    void setBiais(int layer, int index, long double b);

    std::vector<std::vector<Neuron>> getNeurons();

    void clean();
    void normalize(long double max);

    /*
    * return the complexity of the neural network
    * = nb layer * 10 + nb neuron + nb connexions
    */
    int getComplexity() const;

private:

    int m_inputSize;
    int m_outputSize;
    long double (*m_outLayerActivationFunction)(long double);
    bool m_isConstruct;

    bool m_haveConnexion = false;

    std::vector<std::vector<Neuron>> m_allNeurons;

};



} // namespace AI
} // namespace O