#include "AI/AITrainer.hpp"

namespace O
{
namespace AI
{

AITrainer::AITrainer()
{

}
///////////////////////////////////////////////////////////////
// PUBLIC
///////////////////////////////////////////////////////////////

void AITrainer::loadDataSetFromSVG(std::string svgPath,  bool haveHeader, std::string separator)
{
    _haveHeader = haveHeader;
    _stringSvgData = O::file::parceSVG("Churn_Modelling.csv", separator);
    if (_stringSvgData.size()> 0 && _stringSvgData.back().size() > 0)
    {
        _parseOk = true;
    }
    else
    {
        std::cerr << "AITrainer::loadDataSetFromSVG : fichier vide !" <<std::endl;
    }
    
}


void AITrainer::removeCollumn(std::string name)
{
    if (!_parseOk)
    {
        std::cerr << "AITrainer::removeCollumn : fichier vide "<< name<<std::endl;
        return;
    }
    if (!_haveHeader)
    {
        std::cerr << "AITrainer::removeCollumn : pas d'header, utilisez removeCollumn avec un index"<<std::endl;
        return;
    }
    int id = -1;
    for (size_t i = 0; i < _stringSvgData[0].size(); i++)
    {
        if (_stringSvgData[0][i] == name)
        {
            id = i;
        }
    }

    if (id == -1)
    {
        std::cerr << "AITrainer::removeCollumn : impossible de trouver la collone "<< name<<std::endl;
        return;
    }
    else
    {
        removeCollumn(id);
    }
    
    
}

void AITrainer::removeCollumn(int index)
{
    if (index < 0 && index >= _stringSvgData.back().size() )
    {
        std::cerr << "AITrainer::removeCollumn : index de la collone invalide "<<std::endl;
    }
    else
    {
        O::vector::removeCol(&_stringSvgData, index);
    }
    
}

void AITrainer::remplaceCategoricalCol(std::string name, std::vector<std::string> value, std::vector<std::pair<std::string, std::string>> columnName_newVal, std::string nullValue)
{
    if (!_parseOk)
    {
        std::cerr << "AITrainer::removeCollumn : fichier vide "<< name<<std::endl;
        return;
    }
    if (!_haveHeader)
    {
        std::cerr << "AITrainer::removeCollumn : pas d'header, utilisez removeCollumn avec un index"<<std::endl;
        return;
    }
    int id = -1;
    for (size_t i = 0; i < _stringSvgData[0].size(); i++)
    {
        if (_stringSvgData[0][i] == name)
        {
            id = i;
        }
    }

    if (id == -1)
    {
        std::cerr << "AITrainer::removeCollumn : impossible de trouver la collone "<< name<<std::endl;
        return;
    }
    else
    {
        remplaceCategoricalCol(id, value, columnName_newVal, nullValue);
    }
}
void AITrainer::remplaceCategoricalCol(int index, std::vector<std::string> value, std::vector<std::pair<std::string, std::string>> columnIndex_newVal, std::string nullValue)
{
    std::map<std::string,std::vector<std::string>> newsCollumn;

    for (size_t i = 0; i < columnIndex_newVal.size(); i++)
    {
        newsCollumn[columnIndex_newVal[i].first] = std::vector<std::string>(0);
    }
    

    for (size_t i = 1; i < _stringSvgData.size(); i++)
    {
        int indexElementInRemplTable = O::vector::find(value, _stringSvgData[i][index]);
        if (indexElementInRemplTable == -1)
        {
            for (auto it = newsCollumn.begin(); it != newsCollumn.end(); it++)
            {
                it->second.push_back(nullValue);
            }
        }
        else
        {
            for (auto it = newsCollumn.begin(); it != newsCollumn.end(); it++)
            {
                if (it->first == columnIndex_newVal[indexElementInRemplTable].first)
                {
                    it->second.push_back(columnIndex_newVal[indexElementInRemplTable].second);
                }
                else it->second.push_back(nullValue);
            }
            
        }
    }

    removeCollumn(index);
    int idl = 0;
    for (auto it = newsCollumn.begin(); it != newsCollumn.end(); it++)
    {
        _stringSvgData[0].insert(_stringSvgData[0].begin() + index + idl, it->first);
        idl++;
    }
    idl = 0;
    for (auto it = newsCollumn.begin(); it != newsCollumn.end(); it++)
    {
        for (size_t i = 0; i < it->second.size(); i++)
        {
            _stringSvgData[i + 1].insert(_stringSvgData[i + 1].begin() + index + idl,it->second[i]);
        }
        idl++;
    }
}

void AITrainer::normalizeXDataSet(long double min, long double max)
{
    _normalize_minX = min;
    _normalize_maxX = max;
}
void AITrainer::normalizeYDataSet(long double min, long double max)
{
    _normalize_minY = min;
    _normalize_maxY = max;
}
void AITrainer::defineTrainingSetPropotion(long double pourcent)
{
    _trainig_prop = pourcent;
}
void AITrainer::defineOutputColons(std::vector<int> cols)
{
    _out_col.clear();
    for (size_t i = 0; i < cols.size(); i++)
    {
        _out_col.push_back(_stringSvgData[0][cols[i]]);
    }
}
void AITrainer::defineOutputColons(int col)
{
    _out_col = {_stringSvgData[0][col]};
}
void AITrainer::defineOutputColons(std::vector<std::string> cols)
{
    _out_col = cols;
}
void AITrainer::defineOutputColons(std::string col)
{
    _out_col = {col};
}
void AITrainer::categorizeOutputValue(std::vector<std::vector<long double>> outputValuePosibilities)
{
    _outputValuePosibilities = outputValuePosibilities;
}




void AITrainer::train(int nbEpoque, int batchSize, long double trainingRate, long double velocity_conservation, long double velocity_influance)
{
    initTrain();

    //std::cout << _headerX <<std::endl;
    
    m_th_NN_visualizer = std::async(std::launch::async, &O::AI::NeuralNetworkVisualizer::run, &m_NN_visualizer);
    sf::sleep(sf::seconds(0.1));
    m_th_cost_visualizer = std::async(std::launch::async, &O::graphics::CurveGraphApp::run, &m_cost_visualizer);
    sf::sleep(sf::seconds(0.1));
    m_th_result_visualizer = std::async(std::launch::async, &O::graphics::BarsGraphApp::run, &m_result_visualizer);



    m_cost_visualizer.addCourbe("cost", sf::Color(100,100,255));
    
	m_result_visualizer.setMaxSizeSpaceBetweenGroup(30);
	m_result_visualizer.addBarreGroup("out 0");
	m_result_visualizer.addBarreGroup("out 1");
	m_result_visualizer.addBarre("out 0", 0, sf::Color(120, 255, 120));
	m_result_visualizer.addBarre("out 1", 0, sf::Color(120, 255, 120));
	m_result_visualizer.addBarre("out 0", 0, sf::Color(255, 100, 100));
	m_result_visualizer.addBarre("out 1", 0, sf::Color(255, 100, 100));
   
    for (size_t e = 0; e < nbEpoque; e++)
    {
        std::vector<O::math::Matrix<long double>> batch_x;
        std::vector<O::math::Matrix<long double>> batch_y;

        if (classifiedOutputPossibilities.size() >= 2)
        {
            for (size_t b = 0; b < batchSize; b++)
            {
                int indexB;

                bool _continue = true;
                do
                {
                    indexB = O::math::rdm::randInt(0, x.size());

                    
                    if ((y[indexB] == classifiedOutputPossibilities[e % classifiedOutputPossibilities.size()]))
                    {
                        _continue = false;
                    }


                } while (_continue);
                
                batch_x.push_back(x[indexB]);
                batch_y.push_back(y[indexB]);
            }
        }
        else
        {
            for (size_t b = 0; b < batchSize; b++)
            {
                int indexB = O::math::rdm::randInt(0, x.size());

                batch_x.push_back(x[indexB]);
                batch_y.push_back(y[indexB]);
            }
        }
        

        // test
        O::math::Matrix<long double> yAvg(y.back().getNbLine(), 1, 0);
        O::math::Matrix<long double> y_Avg = yAvg;
        for (size_t i = 0; i < batch_x.size(); i++)
        {
            auto out = m_ANN.getOutput(batch_x[i]);
            y_Avg = y_Avg + out;
            yAvg = yAvg + batch_y[i];
        }
        y_Avg = y_Avg /(long double) batchSize;
        yAvg = yAvg /(long double) batchSize;



        m_ANN.backpropagation(trainingRate, velocity_conservation, velocity_influance,yAvg, y_Avg);

        m_NN_visualizer.visualise(m_ANN);

        if (trainingClock.getElapsedTime() > sf::seconds(2))
        {
            int nbOk1 = 0, nbOk0 = 0, nbNotOk1 = 0, nbNotOk0 = 0;
            trainingClock.restart();
            long double agvCost = 0;
            for (size_t i = 0; i < x.size(); i++)
            {
                auto out = m_ANN.getOutput(x[i]);
                agvCost += m_ANN.getCost(y[i], out);

                if (y[i][0][0] >= 0.5)
                {
                    if (out[0][0] >= 0.5) nbOk1++;
                    else nbNotOk1++;
                }
                else
                {
                    if (out[0][0] >= 0.5) nbNotOk0++;
                    else nbOk0++;
                }
            }
            std::cout <<" Epoque "<< e <<" / "<< nbEpoque<<" cost : "<<agvCost / (long double)  x.size() <<std::endl;

            m_cost_visualizer.addPoint("cost", sf::Vector2f(e, agvCost / (long double)  x.size()));
            m_result_visualizer.setSize("out 0", nbOk0, 0);
            m_result_visualizer.setSize("out 1", nbOk1, 0);
            m_result_visualizer.setSize("out 0", nbNotOk0, 1);
            m_result_visualizer.setSize("out 1", nbNotOk1, 1);
            
        }
    }

    // test final a la fin de l'entrainement

    int nbOk1 = 0, nbOk0 = 0, nbNotOk1 = 0, nbNotOk0 = 0;
    trainingClock.restart();
    long double agvCost = 0;
    for (size_t i = 0; i < x_test.size(); i++)
    {
        auto out = m_ANN.getOutput(x_test[i]);
        agvCost += m_ANN.getCost(y_test[i], out);

        if (y_test[i][0][0] >= 0.5)
        {
            if (out[0][0] >= 0.5) nbOk1++;
            else nbNotOk1++;
        }
        else
        {
            if (out[0][0] >= 0.5) nbNotOk0++;
            else nbOk0++;
        }
    }
    std::cout <<" Resultats : sur "<< nbEpoque<<" epoques, cost : "<<agvCost / (long double)  x_test.size() <<std::endl;
    m_cost_visualizer.addCourbe("result", sf::Color(100,255,100));
    m_cost_visualizer.addPoint("result", sf::Vector2f(0, agvCost / (long double)  x_test.size()));
    m_cost_visualizer.addPoint("result", sf::Vector2f(nbEpoque, agvCost / (long double)  x_test.size()));
    m_result_visualizer.setSize("out 0", nbOk0, 0);
    m_result_visualizer.setSize("out 1", nbOk1, 0);
    m_result_visualizer.setSize("out 0", nbNotOk0, 1);
    m_result_visualizer.setSize("out 1", nbNotOk1, 1);

}

///////////////////////////////////////////////////////////////
// PRIVATE
///////////////////////////////////////////////////////////////
void AITrainer::initTrain()
{
    _numerizeDataSet();
    _normalizeDataSet();
    _computeSet();
    _computeOuputClassifyMatrix();
    _initAnn();
}




    

void AITrainer::_numerizeDataSet()
{
    if (_haveHeader)
    {
        _headerNum = _stringSvgData[0];
    }
    else
    {
        _headerNum = O::vector::applyFunction
            <long double, const double&, std::string, std::string>(
                O::vector::createVector(_stringSvgData[0].size(), 0.l, 1.l),
                O::str::to_string
            );
    }
    
    
    for (size_t i = 1; i < _stringSvgData.size(); i++)
    {
        std::vector<long double> line;
        for (size_t j = 0; j < _stringSvgData[i].size(); j++)
        {
            line.push_back(str::to_double(_stringSvgData[i][j]));
        }
        _numSvgData.push_back(line);
    }
}


void AITrainer::_normalizeDataSet()
{
    for (size_t col = 0; col < _headerNum.size(); col++)
    {
        // pour chaques colonnes du dataset
        long double mediane = 0;
        long double delta = 0;

        long double maxCol = _numSvgData[0][col];
        long double minCol = _numSvgData[0][col];
        for (size_t e = 0; e < _numSvgData.size(); e++)
        {
            if (_numSvgData[e][col] > maxCol)
            {
                maxCol = _numSvgData[e][col] ;
            }
            if (_numSvgData[e][col] < minCol)
            {
                minCol = _numSvgData[e][col] ;
            }
        }
        mediane = (minCol + maxCol) / 2.l;

        for (size_t e = 0; e < _numSvgData.size(); e++)
        {
            delta += std::pow((_numSvgData[e][col] - mediane),2);
        }
        delta /= (long double) _numSvgData.size();
        delta = std::sqrt((long double) delta);


        long double minBase = mediane - delta;
        long double maxBase = mediane + delta;

        if (O::vector::find(_out_col, _headerNum[col]) != -1)
        {
            long double scale = (maxBase - minBase) / (_normalize_maxY - _normalize_minY);

            for (size_t e = 0; e < _numSvgData.size(); e++)
            {
                _numSvgData[e][col] = (_numSvgData[e][col] - minBase) / scale + _normalize_minY;
            }

            m_normalizeDatas[_headerNum[col]] = {minBase, scale};
        }
        else
        {
            long double scale = (maxBase - minBase) / (_normalize_maxX - _normalize_minX);

            for (size_t e = 0; e < _numSvgData.size(); e++)
            {
                _numSvgData[e][col] = (_numSvgData[e][col] - minBase) / scale + _normalize_minX;
            }

            m_normalizeDatas[_headerNum[col]] = {minBase, scale};
        }
    }
}


void AITrainer::_computeSet()
{
    int maxTrainProp = (long double)_numSvgData.size() * _trainig_prop / 100.0;
    if (_out_col.size() == 0)
    {
        _out_col.push_back(_headerNum.back());
    }
    for (size_t j = 0; j < _headerNum.size(); j++)
    {
        if (O::vector::find(_out_col, _headerNum[j]) != -1)
        {
            _headerY.push_back(_headerNum[j]);
        }
        else
        {
            _headerX.push_back(_headerNum[j]);
        }
        
    }
    for (size_t i = 0; i < _numSvgData.size(); i++)
    {
        std::vector<long double> x_line;
        std::vector<long double> y_line;

        for (size_t j = 0; j < _headerNum.size(); j++)
        {
            if (O::vector::find(_out_col, _headerNum[j]) != -1)
            {
                y_line.push_back(_numSvgData[i][j]);
            }
            else
            {
                x_line.push_back(_numSvgData[i][j]);
            }
            
        }
        
        if (i < maxTrainProp)
        {
            x.push_back(O::math::convertToColMatrix(x_line));
            y.push_back(O::math::convertToColMatrix(y_line));
        }
        else
        {
            x_test.push_back(O::math::convertToColMatrix(x_line));
            y_test.push_back(O::math::convertToColMatrix(y_line));
        }
    }
}


void AITrainer::_initAnn()
{
    m_ANN.initBiais(_min_init_b, _max_init_b);
    m_ANN.initWeight(_min_init_w, _max_init_w);
}


void AITrainer::_computeOuputClassifyMatrix()
{
    if (_outputValuePosibilities.size() >= 2)
    {
        for (size_t o = 0; o < _outputValuePosibilities.size(); o++)
        {
            O::math::Matrix<long double> mat = O::math::convertToColMatrix(_outputValuePosibilities[o]);

            for (size_t i = 0; i < mat.getNbLine(); i++)
            {
                auto data = m_normalizeDatas[_headerY[i]];
                mat.setValue(i, 0, (mat.getValue(i, 0) + data.first ) / data.second + _normalize_minY);
            }
            
            // puis on regarde dans la lsite des sorte si on trouve ces valeurs

            if (O::vector::find(y,mat) != -1)
            {
                // si on trouve cette sortie dans la liste ! c'est ok !
                classifiedOutputPossibilities.push_back(mat);
            }

        }

        if (classifiedOutputPossibilities.size() < 2)
        {
            std::cout << "AITrainer::categorizeOutputValue : Echec de la catégorisation : valeurs sépcifiés non trouvée" <<std::endl;
        }
    }
    
}


void AITrainer::setNeuralNetwork(ArtificialNeuralNetwork n)
{
    m_ANN = n;
}

void AITrainer::initBiaisAndWeightValues(long double minW, long double maxW, long double minB, long double maxB)
{
    _min_init_b = minB;
    _min_init_w = minW;
    _max_init_b = maxB;
    _max_init_w = maxW;
}


} 
}

