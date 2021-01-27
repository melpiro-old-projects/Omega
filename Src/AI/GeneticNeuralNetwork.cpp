#include "GeneticNeuralNetwork.hpp"
#include "Operators/PrintFunctions.h"

namespace O
{
namespace AI
{
    

GeneticNeuralNetwork::GeneticNeuralNetwork()
{

}
///////////////////////////////////////////////////////////////
// INIT
///////////////////////////////////////////////////////////////


void GeneticNeuralNetwork::setInputLayerSize(const int& size)
{
    m_inputSize = size;
}

void GeneticNeuralNetwork::setOutputLayerSize(const int& size, long double (*activationFunction)(long double))
{
    m_outputSize = size;
    m_outLayerActivationFunction = activationFunction;
}


void GeneticNeuralNetwork::construct()
{
    clear();
    m_allNeurons.push_back(std::vector<Neuron>(m_inputSize));
    m_allNeurons.push_back(std::vector<Neuron>(m_outputSize));
    for (size_t i = 0; i < m_allNeurons.back().size(); i++)
    {
        m_allNeurons.back()[i].activationFunction = m_outLayerActivationFunction;
    }
}

///////////////////////////////////////////////////////////////
// reset
///////////////////////////////////////////////////////////////

void GeneticNeuralNetwork::clear()
{
    m_haveConnexion = false;
    m_allNeurons.clear();
}
    
///////////////////////////////////////////////////////////////
// IA
///////////////////////////////////////////////////////////////

std::vector<long double> GeneticNeuralNetwork::getOutput(std::vector<long double> input)
{

// reset init
    
    for (size_t i = 0; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            m_allNeurons[i][j].activation = 0;
            m_allNeurons[i][j].agregation = 0;
        }
    }
    
    for (size_t i = 0; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            if (i == 0)
                m_allNeurons[i][j].activation = input[j];
            else
            {
                
                m_allNeurons[i][j].activation = 
                    m_allNeurons[i][j].activationFunction
                    (
                        m_allNeurons[i][j].agregation 
                        +
                        m_allNeurons[i][j].biais
                    );
            }
            

            for (size_t k = 0; k < m_allNeurons[i][j].out.size(); k++)
            {
                if (m_allNeurons[i][j].out[k].first >= m_allNeurons.size())
                {
                    std::cout << "layer "<< i <<"neuron "<< j <<" got to layer "<< m_allNeurons[i][j].out[k].first  <<std::endl;
                    std::cout << "ALERT ! ALERT ERROR 1 /!\\" <<std::endl;
                }
                else if (m_allNeurons[i][j].out[k].second >= m_allNeurons[m_allNeurons[i][j].out[k].first].size())
                {
                    std::cout << getLayersStructure() <<std::endl;
                    std::cout << "from layer "<< i <<std::endl;
                    std::cout << "from neuron " << j <<std::endl;
                    std::cout << "targeted layer : "<<m_allNeurons[i][j].out[k].first <<std::endl;
                    std::cout << "targeted neuron : "<<m_allNeurons[i][j].out[k].second <<std::endl;
                    std::cout << "but targeted layer size : "<< m_allNeurons[m_allNeurons[i][j].out[k].first].size()<<std::endl;
                    std::cout << "ALERT ! ALERT ERROR 2 /!\\" <<std::endl;

                    int i;
                    std::cin >> i;
                }
                else
                {
                    m_allNeurons[m_allNeurons[i][j].out[k].first][m_allNeurons[i][j].out[k].second].agregation 
                        += m_allNeurons[i][j].activation * m_allNeurons[i][j].out[k].third;
                }
                
                
            }
        }
    }
    
    std::vector<long double> res;
    for (size_t i = 0; i < m_allNeurons.back().size(); i++)
    {
        res.push_back(m_allNeurons.back()[i].activation);
    }
    return res;
}


std::vector<double> GeneticNeuralNetwork::getOutput(std::vector<double> input)
{
    for (size_t i = 0; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            m_allNeurons[i][j].activation = 0;
            m_allNeurons[i][j].agregation = 0;
        }
    }
    
    for (size_t i = 0; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            if (i == 0)
                m_allNeurons[i][j].activation = input[j];
            else
            {
                
                m_allNeurons[i][j].activation = 
                    m_allNeurons[i][j].activationFunction
                    (
                        m_allNeurons[i][j].agregation 
                        +
                        m_allNeurons[i][j].biais
                    );
            }
            

            for (size_t k = 0; k < m_allNeurons[i][j].out.size(); k++)
            {
                if (m_allNeurons[i][j].out[k].first >= m_allNeurons.size())
                {
                    std::cout << "layer "<< i <<"neuron "<< j <<" got to layer "<< m_allNeurons[i][j].out[k].first  <<std::endl;
                    std::cout << "ALERT ! ALERT ERROR 1 /!\\" <<std::endl;
                }
                else if (m_allNeurons[i][j].out[k].second >= m_allNeurons[m_allNeurons[i][j].out[k].first].size())
                {
                    std::cout << getLayersStructure() <<std::endl;
                    std::cout << "from layer "<< i <<std::endl;
                    std::cout << "from neuron " << j <<std::endl;
                    std::cout << "targeted layer : "<<m_allNeurons[i][j].out[k].first <<std::endl;
                    std::cout << "targeted neuron : "<<m_allNeurons[i][j].out[k].second <<std::endl;
                    std::cout << "but targeted layer size : "<< m_allNeurons[m_allNeurons[i][j].out[k].first].size()<<std::endl;
                    std::cout << "ALERT ! ALERT ERROR 2 /!\\" <<std::endl;

                    int i;
                    std::cin >> i;
                }
                else
                {
                    m_allNeurons[m_allNeurons[i][j].out[k].first][m_allNeurons[i][j].out[k].second].agregation 
                        += m_allNeurons[i][j].activation * m_allNeurons[i][j].out[k].third;
                }
                
                
            }
        }
    }
    
    std::vector<double> res;
    for (size_t i = 0; i < m_allNeurons.back().size(); i++)
    {
        res.push_back(m_allNeurons.back()[i].activation);
    }
    return res;
}

///////////////////////////////////////////////////////////////
// getters
///////////////////////////////////////////////////////////////


int GeneticNeuralNetwork::getLayerSize(int layer)
{
    return m_allNeurons[layer].size();
}
std::vector<int> GeneticNeuralNetwork::getLayersStructure()
{
    std::vector<int> res;
    for (size_t i = 0; i < m_allNeurons.size(); i++)
    {
        res.push_back(m_allNeurons[i].size());
    }
    return res;
}
int GeneticNeuralNetwork::getNbLayer()
{
    return m_allNeurons.size();
}

bool GeneticNeuralNetwork::haveConnexion(int layerIndexFrom, int neuronIndexFrom, int layerIndexTo, int neuronIndexTo)
{
    if (layerIndexFrom >= layerIndexTo)
    {
        return false;
    }
    if(layerIndexFrom>=m_allNeurons.size() || layerIndexFrom < 0)
    {
        return false;
    }
    if(layerIndexTo >=m_allNeurons.size() || layerIndexTo < 0)
    {
        return false;
    }
    if(neuronIndexFrom >= m_allNeurons[layerIndexFrom].size() || neuronIndexFrom < 0)
    {
        return false; 
    }
    if(neuronIndexTo >= m_allNeurons[layerIndexTo].size() || neuronIndexTo < 0)
    {
        return false;
    }

    for (size_t i = 0; i < m_allNeurons[layerIndexFrom][neuronIndexFrom].out.size(); i++)
    {
        if (m_allNeurons[layerIndexFrom][neuronIndexFrom].out[i].first == layerIndexTo
            && m_allNeurons[layerIndexFrom][neuronIndexFrom].out[i].second == neuronIndexTo)
        {
            return true;
        }
    }   
    return false;
}
std::pair<std::pair<int,int>,std::pair<int,int>> GeneticNeuralNetwork::getRdmConnextion()
{
    O::data::triplet<int,int,int> conn = getRdmConnextionByIndex();
    return std::make_pair(
        std::make_pair(conn.first, conn.second),
        std::make_pair(m_allNeurons[conn.first][conn.second].out[conn.third].first, m_allNeurons[conn.first][conn.second].out[conn.third].second)
    );
}


O::data::triplet<int, int, int> GeneticNeuralNetwork::getRdmConnextionByIndex()
{
    if(!m_haveConnexion)
    {
        return O::data::make_triplet(-1,-1,-1);
    }
    int layerFrom;
    int neuronFrom;

    int nb = 10;
    do
    {

        int nb2 = 10;
        do
        {
            layerFrom = O::math::rdm::randInt(0, m_allNeurons.size());
            nb2--;
        } while (nb2 >= 0 && m_allNeurons[layerFrom].size() == 0);


        neuronFrom = O::math::rdm::randInt(0, m_allNeurons[layerFrom].size());

        nb--;
    } while (nb >= 0 && m_allNeurons[layerFrom][neuronFrom].out.size() == 0);

    if (nb < 0)
    {
        return O::data::make_triplet(-1,-1,-1);
    }

    return O::data::make_triplet(
        layerFrom,
        neuronFrom,
        O::math::rdm::randInt(0,m_allNeurons[layerFrom][neuronFrom].out.size()));
}


O::data::triplet<int, int, int> GeneticNeuralNetwork::getRdmConnextionByIndex(const int& minfromLayer)
{
    if(!m_haveConnexion)
    {
        return O::data::make_triplet(-1,-1,-1);
    }
    int layerFrom;
    int neuronFrom;

    int nb = 10;
    do
    {

        int nb2 = 10;
        do
        {
            layerFrom = O::math::rdm::randInt(0, m_allNeurons.size());
            nb2--;
        } while (nb2 >= 0 && (m_allNeurons[layerFrom].size() == 0 || layerFrom < minfromLayer));


        neuronFrom = O::math::rdm::randInt(0, m_allNeurons[layerFrom].size());

        nb--;
    } while (nb >= 0 && m_allNeurons[layerFrom][neuronFrom].out.size() == 0);

    if (nb < 0)
    {
        return O::data::make_triplet(-1,-1,-1);
    }

    return O::data::make_triplet(
        layerFrom,
        neuronFrom,
        O::math::rdm::randInt(0,m_allNeurons[layerFrom][neuronFrom].out.size()));
}

///////////////////////////////////////////////////////////////
// mutation
///////////////////////////////////////////////////////////////



void GeneticNeuralNetwork::mutateWeight(const double& pourcent, const long double& min, const long double& max)
{
    for (size_t i = 1; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            if (O::math::rdm::randFloat(0, 100) < pourcent)
            {
                for (size_t iF = 0; iF < i; iF++)
                {
                    for (size_t jF = 0; jF < m_allNeurons[iF].size(); jF++)
                    {
                        for (size_t kF = 0; kF < m_allNeurons[iF][jF].out.size(); kF++)
                        {
                            if (m_allNeurons[iF][jF].out[kF].first == i && m_allNeurons[iF][jF].out[kF].first == j)
                            {
                                if (O::math::rdm::randInt(0, 2) == 0)
                                {
                                    m_allNeurons[iF][jF].out[kF].third = O::math::rdm::randFloat(0.75 * min + 0.25 * max, 0.25 * min + 0.75 * max);
                                }
                                else
                                {
                                    if (O::math::rdm::randInt(0, 2) == 0)
                                    {
                                        m_allNeurons[iF][jF].out[kF].third = O::math::rdm::randFloat(min, 0.75 * min + 0.25 * max);
                                    }
                                    else
                                    {
                                        m_allNeurons[iF][jF].out[kF].third = O::math::rdm::randFloat(0.25 * min + 0.75 * max, max);
                                    }
                                    
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void GeneticNeuralNetwork::mutateBiais(const double& pourcent, const long double& min, const long double& max)
{
    for (size_t i = 1; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            if (O::math::rdm::randFloat(0, 100) < pourcent)
                m_allNeurons[i][j].biais = O::math::rdm::randDouble(min, max);
        }
        
    }
}
void GeneticNeuralNetwork::mutateWeight(const double& pourcent, const long double& delta)
{
    for (size_t i = 0; i < m_allNeurons.size() - 1; i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            for (size_t k = 0; k < m_allNeurons[i][j].out.size(); k++)
            {
                if (O::math::rdm::randFloat(0, 100) < pourcent)
                    m_allNeurons[i][j].out[k].third += O::math::rdm::randDouble(-delta, delta);
            }
            
        }
        
    }
}
void GeneticNeuralNetwork::mutateBiais(const double& pourcent, const long double& delta)
{
    for (size_t i = 1; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            if (O::math::rdm::randFloat(0, 100) < pourcent)
                m_allNeurons[i][j].biais += O::math::rdm::randDouble(-delta, delta);
        }
        
    }
}
void GeneticNeuralNetwork::mutateBiais(const double& pourcent,const int& layerMin, const long double& min, const long double& max)
{
    for (size_t i = layerMin; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            if (O::math::rdm::randFloat(0, 100) < pourcent)
                m_allNeurons[i][j].biais = O::math::rdm::randDouble(min, max);
        }
    }
}
bool GeneticNeuralNetwork::mutateAddConnection(const double& minW, const double& maxW)
{
    int layerFrom, layerTo,neuronFrom,neuronTo;
    int nb = 10;
    do
    {
        layerFrom = O::math::rdm::randInt(0, getNbLayer() - 1);
        layerTo = O::math::rdm::randInt(layerFrom + 1, getNbLayer());
        neuronFrom = O::math::rdm::randInt(0, getLayerSize(layerFrom));
        neuronTo = O::math::rdm::randInt(0, getLayerSize(layerTo));
        nb--;

    } while (nb > 0 && haveConnexion(layerFrom, neuronFrom, layerTo, neuronTo));
    if (nb != 0)
    {
        return addConnexion(layerFrom, neuronFrom,layerTo, neuronTo, O::math::rdm::randDouble(minW, maxW));
    }
    return false;
}

bool GeneticNeuralNetwork::mutateAddConnectedNeuron(const int& nbInputConnexion, const int& nbOutputConnexion, long double(*activationFunction)(long double) ,const double& minB, const double& maxB, const double& minW, const double& maxW)
{
    if (getNbLayer() > 2)
    {
        int indexLayer = O::math::rdm::randInt(1, getNbLayer() - 1);
        int newNeuronIndex = addNeuronInLayer(indexLayer, activationFunction, O::math::rdm::randDouble(minB, maxB));
        
        
        if (newNeuronIndex != -1)
        {
            // create input
            for (size_t i = 0; i < nbInputConnexion; i++)
            {
                int layer;
                int neuron;
                do{
                    layer = O::math::rdm::randInt(0, indexLayer);
                    neuron = O::math::rdm::randInt(0, getLayerSize(layer));

                }while(!addConnexion(layer, neuron, indexLayer, newNeuronIndex, O::math::rdm::randDouble(minW, maxW)));
            }

            // create ouput
            for (size_t i = 0; i < nbOutputConnexion; i++)
            {
                int layer;
                int neuron;
                do{
                    layer = O::math::rdm::randInt(indexLayer + 1, getNbLayer());
                    neuron = O::math::rdm::randInt(0, getLayerSize(layer));

                }while(!addConnexion(indexLayer, newNeuronIndex, layer, neuron, O::math::rdm::randDouble(minW, maxW)));
            }
            return true;
        }
    }
    return false;
}


void GeneticNeuralNetwork::mutateAddConectedLayer(const int& nbNeurons, const int& nbInputConnexion, const int& nbOutputConnexion, long double(*activationFunction)(long double)  ,const double& minB, const double& maxB, const double& minW, const double& maxW)
{
    int indexNewLayer = O::math::rdm::randInt(1, getNbLayer());
    addLayer(indexNewLayer);

    for (size_t i = 0; i < nbNeurons; i++)
    {
        int newNeuronIndex = addNeuronInLayer(indexNewLayer, activationFunction, O::math::rdm::randDouble(minB, maxB));
        
        if (newNeuronIndex != -1)
        {
            // create input
            for (size_t i = 0; i < nbInputConnexion; i++)
            {
                int layer;
                int neuron;
                do{
                    layer = O::math::rdm::randInt(0, indexNewLayer);
                    neuron = O::math::rdm::randInt(0, getLayerSize(layer));
                }while(!addConnexion(layer, neuron, indexNewLayer, newNeuronIndex, O::math::rdm::randDouble(minW, maxW)));
                
            }

            // create ouput
            for (size_t i = 0; i < nbOutputConnexion; i++)
            {

                int layer;
                int neuron;
                do
                {
                    layer = O::math::rdm::randInt(indexNewLayer + 1, getNbLayer());
                    neuron = O::math::rdm::randInt(0, getLayerSize(layer));

                } while (!addConnexion(indexNewLayer, newNeuronIndex, layer, neuron, O::math::rdm::randDouble(minW, maxW)));
            }
        }
    }
}

bool GeneticNeuralNetwork::mutateRemoveConnection()
{
    auto transition = this->getRdmConnextionByIndex();
    if(transition.first != -1)
    {
        return removeConnexion(transition.first, transition.second, transition.third);
    }
    return false;
}


bool GeneticNeuralNetwork::mutateRemoveConnection(const int& minLayer)
{
    auto transition = this->getRdmConnextionByIndex(minLayer);
    if(transition.first != -1)
    {
        return removeConnexion(transition.first, transition.second, transition.third);
    }
    return false;
}

bool GeneticNeuralNetwork::mutateMoveConnectionInput()
{
    auto transition = this->getRdmConnextionByIndex();
    if(transition.first != -1)
    {

        int layer = -1;
        int neuron = -1;
        int ok2 = 10;
        do
        {
            int ok = 10;
            do
            {
                layer =  O::math::rdm::randInt(0, transition.first);
                ok--;
            } while (m_allNeurons[layer].size() == 0 && ok > 0 );

            if (ok != 0)
            {
                neuron = O::math::rdm::randInt(0, getLayerSize(layer));
            }
            ok2 --;
            
        } while (haveConnexion(layer, neuron, m_allNeurons[transition.first][transition.second].out[transition.third].first, m_allNeurons[transition.first][transition.second].out[transition.third].second) && ok2 > 0);

        if (ok2 != 0)
        {
            long double w = m_allNeurons[transition.first][transition.second].out[transition.third].third;
            int toLayer = m_allNeurons[transition.first][transition.second].out[transition.third].first;
            int toNeuron = m_allNeurons[transition.first][transition.second].out[transition.third].second;

            removeConnexion(transition.first,transition.second, transition.third);


            addConnexion(layer, neuron, toLayer, toNeuron, w);

            return true;
        }
    }
    return false;
}


bool GeneticNeuralNetwork::mutateMoveConnectionOutput()
{
    auto transition = this->getRdmConnextionByIndex();
    if(transition.first != -1)
    {

        int layer = -1;
        int neuron = -1;
        int ok2 = 10;
        do
        {
            int ok = 10;
            do
            {
                layer = O::math::rdm::randInt(transition.first + 1, m_allNeurons.size());
                ok--;
            } while (m_allNeurons[layer].size() == 0 && ok > 0);

            if (ok != 0)
            {
                neuron = O::math::rdm::randInt(0, getLayerSize(layer));
            }
            ok2 --;
        
        } while (haveConnexion(transition.first, transition.second, layer, neuron) && ok2 > 0);


        if (ok2 != 0)
        {
            m_allNeurons[transition.first][transition.second].out[transition.third].first = layer;
            m_allNeurons[transition.first][transition.second].out[transition.third].second = neuron;

            return true;
        }
    }
    return false;
}

bool GeneticNeuralNetwork::mutateDuplicateConnectionOutput()
{
    auto transition = this->getRdmConnextionByIndex();
    if(transition.first != -1)
    {

        int layer = -1;
        int neuron = -1;
        int ok2 = 10;
        do
        {
            int ok = 10;
            do
            {
                layer = O::math::rdm::randInt(transition.first + 1, m_allNeurons.size());
                ok--;
            } while (m_allNeurons[layer].size() == 0 && ok > 0);

            if (ok != 0)
            {
                neuron = O::math::rdm::randInt(0, getLayerSize(layer));
            }
            ok2 --;
        
        } while (haveConnexion(transition.first, transition.second, layer, neuron) && ok2 > 0);


        if (ok2 != 0)
        {
            addConnexion(transition.first, transition.second, layer, neuron, m_allNeurons[transition.first][transition.second].out[transition.third].third);
            return true;
        }
    }
    return false;
}


void GeneticNeuralNetwork::mutateCrossOver(O::AI::GeneticNeuralNetwork& ann)
{

}

///////////////////////////////////////////////////////////////
// modifieurs
///////////////////////////////////////////////////////////////

int GeneticNeuralNetwork::addNeuronInLayer(int layerIndex, long double (*activationFunction)(long double), long double biais)
{
    if (layerIndex <= 0 || layerIndex >= m_allNeurons.size() - 1)
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::addNeuronInLayer] layerIndex invalide"<<std::endl;
        return -1;
    }

    m_allNeurons[layerIndex].push_back(Neuron());
    m_allNeurons[layerIndex].back().activationFunction = activationFunction;
    m_allNeurons[layerIndex].back().biais = biais;
    return m_allNeurons[layerIndex].size() - 1;
}
bool GeneticNeuralNetwork::addConnexion(int layerIndexFrom, int neuronIndexFrom, int layerIndexTo, int neuronIndexTo, long double w)
{
    if (layerIndexFrom >= layerIndexTo)
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::addConnexion] layerIndexFrom doit etre inférieur à layerIndexTo"<<std::endl;
        return false;
    }
    if(layerIndexFrom>=m_allNeurons.size())
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::addConnexion] layerIndexFrom invalides "<<std::endl;
        return false;
    }
    if(layerIndexTo >=m_allNeurons.size())
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::addConnexion] layerIndexTo invalides "<<std::endl;
        return false;
    }
    if(neuronIndexFrom >= m_allNeurons[layerIndexFrom].size())
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::addConnexion] neuronIndexFrom invalides "<<std::endl;
        return false; 
    }
    if(neuronIndexTo >= m_allNeurons[layerIndexTo].size())
    {
        std::cout << layerIndexTo<<" "<<m_allNeurons[layerIndexTo].size()<<" "<< neuronIndexTo<<std::endl;
        std::cerr<< "[O::AI::GeneticNeuralNetwork::addConnexion] neuronIndexTo invalides "<<std::endl;
        return false;
    }
    for (size_t i = 0; i < m_allNeurons[layerIndexFrom][neuronIndexFrom].out.size(); i++)
    {
        if (m_allNeurons[layerIndexFrom][neuronIndexFrom].out[i].first == layerIndexTo
         && m_allNeurons[layerIndexFrom][neuronIndexFrom].out[i].second == neuronIndexTo)
        {
            return false;
        }
    }
    m_allNeurons[layerIndexFrom][neuronIndexFrom].out.push_back(O::data::make_triplet(layerIndexTo, neuronIndexTo, w));
    m_haveConnexion = true;
    return true;
}

void GeneticNeuralNetwork::addLayer(int index)
{
    if (index == 0 || index >= m_allNeurons.size())
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::addLayer] layerIndex invalide"<<std::endl;
        return;
    }

    for (size_t i = 0; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            for (size_t k = 0; k < m_allNeurons[i][j].out.size(); k++)
            {
                if (m_allNeurons[i][j].out[k].first >= index)
                    m_allNeurons[i][j].out[k].first++;
            }
        }
    }
    m_allNeurons.insert(m_allNeurons.begin() + index, std::vector<Neuron>(0));
}

bool GeneticNeuralNetwork::removeConnexion(int layerIndexFrom, int neuronIndexFrom, int layerIndexTo, int neuronIndexTo)
{
    if (layerIndexFrom >= layerIndexTo)
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::removeConnexion] layerIndexFrom doit etre inférieur (strictement) à layerIndexTo"<<std::endl;
        return false;
    }
    if (layerIndexFrom > m_allNeurons.size())
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::removeConnexion] layerIndexFrom invalide"<<std::endl;
        return false;
    }
    if (neuronIndexFrom > m_allNeurons[layerIndexFrom].size())
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::removeConnexion] neuronIndexFrom invalide"<<std::endl;
        return false;
    }
    if(neuronIndexTo >= m_allNeurons[layerIndexTo].size())
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::removeConnexion] neuronIndexTo invalides "<<std::endl;
        return false;
    }
    if(layerIndexTo >=m_allNeurons.size())
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::removeConnexion] layerIndexTo invalides "<<std::endl;
        return false;
    }

    for (size_t i = 0; i < m_allNeurons[layerIndexFrom][neuronIndexFrom].out.size(); i++)
    {
        if (m_allNeurons[layerIndexFrom][neuronIndexFrom].out[i].first == layerIndexTo
            && m_allNeurons[layerIndexFrom][neuronIndexFrom].out[i].second == neuronIndexTo)
        {
            m_allNeurons[layerIndexFrom][neuronIndexFrom].out.erase(m_allNeurons[layerIndexFrom][neuronIndexFrom].out.begin() + i);
            return true;
        }
    }
    return false;
}


bool GeneticNeuralNetwork::removeConnexion(int layerIndexFrom, int neuronIndexFrom, int outIndex)
{
    if (layerIndexFrom > m_allNeurons.size())
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::removeConnexion] layerIndexFrom invalide"<<std::endl;
        return false;
    }
    if (neuronIndexFrom > m_allNeurons[layerIndexFrom].size())
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::removeConnexion] neuronIndexFrom invalide"<<std::endl;
        return false;
    }
    if(outIndex >= m_allNeurons[layerIndexFrom][neuronIndexFrom].out.size())
    {
        std::cerr << "[O::AI::GeneticNeuralNetwork::removeConnexion] outIndex invalides "<<std::endl;
        return false;
    }

    m_allNeurons[layerIndexFrom][neuronIndexFrom].out.erase(m_allNeurons[layerIndexFrom][neuronIndexFrom].out.begin() + outIndex);
    return true;
}


void GeneticNeuralNetwork::removeConnexionsFromLayer(int layerIndexFrom)
{
    for (size_t i = 0; i < m_allNeurons[layerIndexFrom].size(); i++)
    {
        m_allNeurons[layerIndexFrom][i].out.clear();
    }
}

void GeneticNeuralNetwork::setBiaisOfLayer(int layerIndexFrom, long double biais)
{
    for (size_t i = 0; i < m_allNeurons[layerIndexFrom].size(); i++)
    {
        m_allNeurons[layerIndexFrom][i].biais = biais;
    }
}

void GeneticNeuralNetwork::removeNeuron(int layer, int index)
{
    if (layer == 0 || layer == m_allNeurons.size() -1)
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::removeNeuron] layer protégés"<<std::endl;
        return;
    }
    if (layer > m_allNeurons.size())
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::removeNeuron] layer invalide"<<std::endl;
        return;
    }
    if (index > m_allNeurons[layer].size())
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::removeNeuron] indexNeuron invalide"<<std::endl;
        return;
    }

    m_allNeurons[layer].erase(m_allNeurons[layer].begin() + index);

    for (size_t i = 0; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            for (int k = 0; k < m_allNeurons[i][j].out.size(); k++)
            {
                if (m_allNeurons[i][j].out[k].first == layer &&
                    m_allNeurons[i][j].out[k].second == index)
                {
                    m_allNeurons[i][j].out.erase(m_allNeurons[i][j].out.begin() + k);
                    k--;
                }
            }
        }
    }
    for (size_t i = 0; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            for (size_t k = 0; k < m_allNeurons[i][j].out.size(); k++)
            {
                if (m_allNeurons[i][j].out[k].first == layer &&
                    m_allNeurons[i][j].out[k].second > index)
                {
                    m_allNeurons[i][j].out[k].second --;
                }
            }
        }
    }
    
    for (size_t i = 0; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            for (size_t k = 0; k < m_allNeurons[i][j].out.size(); k++)
            {
                if (m_allNeurons[i][j].out[k].second >= m_allNeurons[m_allNeurons[i][j].out[k].first].size())
                {
                    std::cout << "AHHHHHHHHHHHH 1" <<std::endl;
                }
                if (m_allNeurons[i][j].out[k].first >= m_allNeurons.size())
                {
                    std::cout << "AHHHHHHHHHHHH 2" <<std::endl;
                }
            }
        }
    }
}


void GeneticNeuralNetwork::removeLayer(int layer)
{
    if (layer == 0 || layer == m_allNeurons.size() -1)
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::removeLayer] layer protégés"<<std::endl;
        return;
    }
    if (layer >= m_allNeurons.size() || layer < 0)
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::removeLayer] layer invalide"<<std::endl;
        return;
    }

    for (size_t j = 0; j < m_allNeurons[layer].size(); j++)
    {
        removeNeuron(layer, j);
    }
    m_allNeurons.erase(m_allNeurons.begin() + layer);
    
    for (size_t i = 0; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            for (size_t k = 0; k < m_allNeurons[i][j].out.size(); k++)
            {
                if(m_allNeurons[i][j].out[k].first > layer)
                {
                    m_allNeurons[i][j].out[k].first--;
                }
            }
        }
    }
}


std::pair<int,int> GeneticNeuralNetwork::splitTransition(int layerIndexFrom, int neuronIndexFrom, int layerIndexTo, int neuronIndexTo, long double (*activationFunction)(long double))
{
    if (layerIndexFrom >= layerIndexTo)
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::splitTransition] layerIndexFrom doit etre inférieur (strictement) à layerIndexTo"<<std::endl;
        return std::make_pair(-1,-1);
    }
    if (layerIndexFrom >= layerIndexTo)
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::splitTransition] layerIndexFrom doit etre inférieur (strictement) à layerIndexTo"<<std::endl;
        return std::make_pair(-1,-1);
    }
    if (layerIndexFrom >= m_allNeurons.size())
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::splitTransition] layerIndexFrom invalide"<<std::endl;
        return std::make_pair(-1,-1) ;
    }
    if (neuronIndexFrom >= m_allNeurons[layerIndexFrom].size())
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::splitTransition] neuronIndexFrom invalide"<<std::endl;
        return std::make_pair(-1,-1);
    }
    if(neuronIndexTo >= m_allNeurons[layerIndexTo].size())
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::splitTransition] neuronIndexTo invalides "<<std::endl;
        return std::make_pair(-1,-1);
    }
    if(layerIndexTo >=m_allNeurons.size())
    {
        std::cerr<< "[O::AI::GeneticNeuralNetwork::splitTransition] layerIndexTo invalides "<<std::endl;
        return std::make_pair(-1,-1);
    }
    
    for (size_t k = 0; k < m_allNeurons[layerIndexFrom][neuronIndexFrom].out.size(); k++)
    {
        if (m_allNeurons[layerIndexFrom][neuronIndexFrom].out[k].first == layerIndexTo &&
            m_allNeurons[layerIndexFrom][neuronIndexFrom].out[k].second == neuronIndexTo)
        {

            // find ok !
            long double w = m_allNeurons[layerIndexFrom][neuronIndexFrom].out[k].third;
            int layerNewNeuron;
            int indexNewNeuron;
            if (true)
            {
                addLayer(layerIndexTo);
                layerNewNeuron = layerIndexTo;
                indexNewNeuron = m_allNeurons[layerIndexTo].size();
                layerIndexTo++;
            }
            addNeuronInLayer(layerNewNeuron, activationFunction, 0.l);

            addConnexion(layerIndexFrom, neuronIndexFrom, layerNewNeuron, indexNewNeuron, 1.l);
            addConnexion(layerNewNeuron, indexNewNeuron, layerIndexTo, neuronIndexTo, w);
            removeConnexion(layerIndexFrom, neuronIndexFrom, layerIndexTo, neuronIndexTo);

            return std::make_pair(layerNewNeuron, indexNewNeuron);
        }
    }
    return std::make_pair(-1,-1);
}

void GeneticNeuralNetwork::setBiais(int layer, int index, long double b)
{
    m_allNeurons[layer][index].biais = b;
}



std::vector<std::vector<Neuron>> GeneticNeuralNetwork::getNeurons()
{
    return m_allNeurons;
}



void GeneticNeuralNetwork::clean()
{
    bool isClean = true;
    for (size_t i = 1; i < m_allNeurons.size() - 1; i++)
    {
        for (int j = 0; j < m_allNeurons[i].size(); j++)
        {
            if (m_allNeurons[i][j].out.size() == 0)
            {
                removeNeuron(i, j);
                j--;
                isClean = false;
            }
        }
    }

    for (size_t i = 1; i < m_allNeurons.size() - 1; i++)
    {
        for (int j = 0; j < m_allNeurons[i].size(); j++)
        {
            bool find = false;
            for (size_t l = 0; !find && l < i; l++)
            {
                for (size_t lj = 0; !find && lj < m_allNeurons[l].size(); lj++)
                {
                    for (size_t o = 0; !find && o < m_allNeurons[l][lj].out.size(); o++)
                    {
                        if (m_allNeurons[l][lj].out[o].first == i && m_allNeurons[l][lj].out[o].second == j)
                        {
                            find = true;
                        }
                    }
                    
                }
                
            }
            if (!find)
            {
                removeNeuron(i, j);
                j--;
                isClean = false;
            }
        }
    }

    for (int i = 1; i < m_allNeurons.size() - 1; i++)
    {
        if (m_allNeurons[i].size() == 0)
        {
            removeLayer(i);
            i--;
        }
    }
    

    if (!isClean) clean();
}


void GeneticNeuralNetwork::normalize(long double max)
{
    long double maxB = -10000000, minB = 10000000, maxW = -10000000, minW = 10000000;
    
    for (size_t i = 0; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            if (m_allNeurons[i][j].biais > maxB)
            {
                maxB = m_allNeurons[i][j].biais;
            }
            if (m_allNeurons[i][j].biais < minB)
            {
                minB = m_allNeurons[i][j].biais;
            }
            for (size_t k = 0; k < m_allNeurons[i][j].out.size(); k++)
            {
                if (m_allNeurons[i][j].out[k].third > maxW)
                {
                    maxW = m_allNeurons[i][j].out[k].third;
                }
                if (m_allNeurons[i][j].out[k].third < minW)
                {
                    minW = m_allNeurons[i][j].out[k].third;
                }
            }
        }
    }

    long double factor = max /  std::max(std::max(abs(maxW),abs(minW)) , std::max(abs(maxB),abs(minB)));
 

    for (size_t i = 0; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            if (i != 0)
                m_allNeurons[i][j].biais *= factor;

            for (size_t k = 0; k < m_allNeurons[i][j].out.size(); k++)
            {
                m_allNeurons[i][j].out[k].third *= factor;
            }
        }
    }
}



int GeneticNeuralNetwork::getComplexity() const
{
    int res = (m_allNeurons.size() - 2) * 10;
    for (size_t i = 1; i < m_allNeurons.size() - 1; i++)
    {
        res += m_allNeurons[i].size();
        
        
    }
    for (size_t i = 0; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            res += m_allNeurons[i][j].out.size();
        }
    }
    return res;
}

long double GeneticNeuralNetwork::getMaxWeightAbs()
{
    long double max;
    for (size_t i = 0; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            for (size_t k = 0; k < m_allNeurons[i][j].out.size(); k++)
            {
                if (abs(m_allNeurons[i][j].out[k].third) > max)
                {
                    max = abs(m_allNeurons[i][j].out[k].third);
                }
            }
        }
    }
    return max;
}
long double GeneticNeuralNetwork::getMaxBiaisAbs()
{
    long double max;
    for (size_t i = 0; i < m_allNeurons.size(); i++)
    {
        for (size_t j = 0; j < m_allNeurons[i].size(); j++)
        {
            if (abs(m_allNeurons[i][j].biais) > max)
            {
                max = abs(m_allNeurons[i][j].biais);
            }
        }
    }
    return max;
}

} // namespace AI
} // namespace O
