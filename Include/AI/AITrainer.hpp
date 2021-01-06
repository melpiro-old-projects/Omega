#pragma once
#include "Vector/VectorFunctions.h"
#include "Files/FileFunctions.h"
#include "Operators/PrintFunctions.h"
#include "AI/ArtificialNeuralNetwork.hpp"

#include "NeuralNetworkVisualizer.h"
#include "Graphics/CurveGraphApp.h"
#include "Graphics/BarsGraphApp.h"

#include <future>

namespace O
{
namespace AI
{
    

class AITrainer
{
public:
    AITrainer();

    ///////////////////////////////////////////////////////////////
    // DATASET
    ///////////////////////////////////////////////////////////////
    
    void loadDataSetFromSVG(std::string svgPath, bool haveHeader,  std::string separator = ",");
    void removeCollumn(std::string name);
    void removeCollumn(int index);
    void remplaceCategoricalCol(std::string name, std::vector<std::string> value, std::vector<std::pair<std::string, std::string>> columnName_newVal, std::string nullValue = "0");
    void remplaceCategoricalCol(int index, std::vector<std::string> value, std::vector<std::pair<std::string, std::string>> columnIndex_newVal, std::string nullValue = "0");
    void normalizeXDataSet(long double min, long double max);
    void normalizeYDataSet(long double min, long double max);
    void defineTrainingSetPropotion(long double pourcent);
    void defineOutputColons(std::vector<int> cols);
    void defineOutputColons(int col);
    void defineOutputColons(std::vector<std::string> cols);
    void defineOutputColons(std::string col);
    void categorizeOutputValue(std::vector<std::vector<long double>> outputValuePosibilities);

    ///////////////////////////////////////////////////////////////
    // NEURAL NETWORK
    ///////////////////////////////////////////////////////////////
    void setNeuralNetwork(ArtificialNeuralNetwork n);
    void initBiaisAndWeightValues(long double minW, long double maxW, long double minB, long double maxB);



    ///////////////////////////////////////////////////////////////
    // SUPER FINAL FUNCTION !
    void train(int nbEpoque, int batchSize, long double trainingRate, long double velocity_conservation = 0.l, long double velocity_influance = 1.l);
    
    
private:
    void initTrain();

    void _numerizeDataSet();
    void _normalizeDataSet();
    void _computeSet();
    void _computeOuputClassifyMatrix();
    void _initAnn();


    long double _normalize_minX = -1;
    long double _normalize_maxX = 1;
    long double _normalize_minY = 0;
    long double _normalize_maxY = 1;
    long double _trainig_prop = 80;
    long double _min_init_w = -1;
    long double _max_init_w = 1;
    long double _min_init_b = -1;
    long double _max_init_b = 1;
    bool _haveHeader = true;
    std::vector < std::vector<std::string> > _stringSvgData;
    std::vector<std::string> _headerNum;
    std::vector<std::string> _headerX;
    std::vector<std::string> _headerY;
    std::vector < std::vector<long double> > _numSvgData;
    std::vector<std::string> _out_col;
    std::vector<std::vector<long double>> _outputValuePosibilities;
    bool _parseOk = false;

    std::vector<O::math::Matrix<long double>> classifiedOutputPossibilities;

    std::vector < O::math::Matrix<long double> > x;
    std::vector < O::math::Matrix<long double> > y;
    std::vector < O::math::Matrix<long double> > x_test;
    std::vector < O::math::Matrix<long double> > y_test;
    ArtificialNeuralNetwork m_ANN;

    // le pair est composé de minBase et scale
    std::map<std::string,std::pair<long double, long double>> m_normalizeDatas; // permet de renormaliser d'autres valeur, ou de dénormaliser des valeur.

    sf::Clock trainingClock;

    O::AI::NeuralNetworkVisualizer m_NN_visualizer;
    std::future<void> m_th_NN_visualizer;
    O::graphics::CurveGraphApp m_cost_visualizer;
    std::future<void> m_th_cost_visualizer;
    O::graphics::BarsGraphApp m_result_visualizer;
    std::future<void> m_th_result_visualizer;

};

} 
}

