#include "NeuralNetworkVisualizer.h"

namespace O
{
namespace AI
{


NeuralNetworkVisualizer::NeuralNetworkVisualizer():
	m_haveTempData(false)//,
	//m_textShowMaxBiasAndWheight(&m_fen, "default", 400, 10, false)
{
	//m_textShowMaxBiasAndWheight.setCharacterSize(25);
}

void NeuralNetworkVisualizer::setPosition(int x, int y)
{
	m_fen.setPosition(sf::Vector2i(x, y));
}

void NeuralNetworkVisualizer::run()
{
	m_fen.create(sf::VideoMode(800, 650), "neural network");

	sf::sleep(sf::seconds(0.1));
	render();
	while (m_fen.isOpen())
	{
		event();
		update();
		
		sf::sleep(sf::seconds(0.1));
	}
}

void NeuralNetworkVisualizer::event()
{
	sf::Event e;
	while (m_fen.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			m_fen.close();
		}
	}
}

void NeuralNetworkVisualizer::update()
{
	//m_textShowMaxBiasAndWheight.update();

	if (m_haveTempData)
	{
		m_haveTempData = false;
		updateVisualise();

		
		render();
	}
}

void NeuralNetworkVisualizer::render()
{
	m_fen.clear(sf::Color(19,19,19));

	//m_textShowMaxBiasAndWheight.draw();

	for (size_t i = 0; i < m_allLink.size(); i++)
	{
		for (size_t j = 0; j < m_allLink[i].size(); j++)
		{
			for (size_t k = 0; k < m_allLink[i][j].size(); k++)
			{
				m_fen.draw(m_allLink[i][j][k]);
			}
		}
	}
	
	for (size_t i = 0; i < m_allNeurone.size(); i++)
	{
		for (size_t j = 0; j < m_allNeurone[i].size(); j++)
		{
			m_fen.draw(m_allNeurone[i][j]);
		}
	}
	
	for (size_t i = 0; i < m_allBiais.size(); i++)
	{
		for (size_t j = 0; j < m_allBiais[i].size(); j++)
		{
			m_fen.draw(m_allBiais[i][j]);
		}
	}

	for (size_t i = 0; i < m_inputTexts.size(); i++)
	{
		m_fen.draw(m_inputTexts[i]);
	}
	for (size_t i = 0; i < m_ouputTexts.size(); i++)
	{
		m_fen.draw(m_ouputTexts[i]);
	}
	
	m_fen.display();
}

void NeuralNetworkVisualizer::visualise(O::AI::ArtificialNeuralNetwork n)
{
	m_visualKind = 0;
	m_visualAnn = n;
	m_haveTempData = true;
}
void NeuralNetworkVisualizer::visualise(O::AI::GeneticNeuralNetwork n)
{
	m_visualKind = 1;
	m_visualGnn = n;
	m_haveTempData = true;
}

void NeuralNetworkVisualizer::updateVisualise()
{
	if (m_visualKind == 0)
	{
		double maxBiais = 0;
		double maxWeight = 0;

		std::vector<O::math::Matrix<long double>> b = m_visualAnn.getBias();
		std::vector<O::math::Matrix<long double>> w = m_visualAnn.getWeight();

		
		for (size_t i = 1; i < w.size(); i++)
		{
			for (size_t j = 0; j < w[i].getNbCollumn(); j++)
			{
				
				if ( abs(b[i - 1][j][0]) > maxBiais) maxBiais = abs(b[i - 1][j][0]);

				for (size_t k = 0; k < w[i].getNbLine(); k++)
				{
					if (abs(w[i][k][j]) > maxWeight) maxWeight = abs(w[i][k][j]);
				}
			}
		}

		

		//std::cout << "Max for biais : " + O::str::to_string(maxBiais, 2) +"\nMax for Weight : " + O::str::to_string(maxWeight, 2) <<std::endl;
		//m_textShowMaxBiasAndWheight.setString("Max for biais : " + O::str::to_string(maxBiais, 2) +"\nMax for Weight : " + O::str::to_string(maxWeight, 2));

		float margin = 50.0;

		m_allNeurone.clear();
		m_allBiais.clear();

		std::vector<int> layers = m_visualAnn.getLayersStructure();
		std::vector<O::math::Matrix<long double>> layersBiais = m_visualAnn.getBias();
		int width = layers.size();
		int heightMax = 0;
		for (size_t i = 0; i < layers.size(); i++)
		{
			if (layers[i] > heightMax) heightMax = layers[i];
		}
		// /!\ on garde un espacement avec les bordures de 50
		float heightWithMargins = (650.0 - margin * 2.0);
		float widthWithMargins = (800.0 - margin * 2.0);
		float spacingBetweenLayers = widthWithMargins / (float)(width - 1) ;
		float spacingBetweenNeuron = heightWithMargins / (float)heightMax;
		float radiusCir = spacingBetweenNeuron / 4;
		// on affiche les neurones
		for (size_t i = 0; i < layers.size(); i++)
		{
			std::vector<sf::CircleShape> neurons;
			std::vector<sf::CircleShape> neuronsBiais;
			float posX = spacingBetweenLayers * i + margin + spacingBetweenNeuron / 2.0;
			float firstPosY = ((1.0 - ((float)layers[i] / (float)heightMax)) * heightWithMargins) / 2.0;

			for (size_t j = 0; j < layers[i]; j++)
			{
				float posY = spacingBetweenNeuron * j + firstPosY + margin + spacingBetweenNeuron / 2.0;

				sf::CircleShape cercle;
				cercle.setFillColor(sf::Color(100,100,255));
				cercle.setRadius(radiusCir);
				cercle.setOrigin(radiusCir, radiusCir);
				cercle.setPosition(posX, posY);

				if (i == 0)
				{
					if (j < m_inputTexts.size())
						m_inputTexts[j].setPosition(posX - radiusCir - m_inputTexts[j].getGlobalBounds().width - 10 , posY -  m_inputTexts[j].getGlobalBounds().height);
				}
				if (i == layers.size() - 1)
				{
					if (j < m_inputTexts.size())
						m_ouputTexts[j].setPosition(posX + radiusCir + 10 , posY - m_ouputTexts[j].getGlobalBounds().height);
				}

				neurons.push_back(cercle);

				sf::CircleShape cercleBiais;
				if (layersBiais[i][j][0] >= 0) cercleBiais.setFillColor(sf::Color(120, 255, 120));
				else cercleBiais.setFillColor(sf::Color(255, 100, 100));
				float radius = (abs(layersBiais[i][j][0]) / maxBiais) * radiusCir;
				cercleBiais.setOrigin(radius, radius);
				if (radius > radiusCir)
				{
					cercleBiais.setRadius(radiusCir);
					if (layersBiais[i][j][0] >= 0) cercleBiais.setFillColor(sf::Color::Yellow);
					else cercleBiais.setFillColor(sf::Color::Magenta);
					cercleBiais.setOrigin(radiusCir, radiusCir);
				}
				else
				{
					cercleBiais.setRadius(radius);
				}
				cercleBiais.setPosition(posX, posY);
				neuronsBiais.push_back(cercleBiais);
			}
			m_allNeurone.push_back(neurons);
			m_allBiais.push_back(neuronsBiais);
		}

		// on affiche les liens
		m_allLink.clear();
		std::vector<O::math::Matrix<long double>> link = m_visualAnn.getWeight();
		float maxWidth = radiusCir;
		for (size_t i = 0; i < link.size() - 1; i++)
		{
			std::vector<std::vector<sf::RectangleShape>> layer;
			for (size_t j = 0; j < link[i + 1].getNbCollumn(); j++)
			{
				std::vector<sf::RectangleShape> conec;
				for (size_t k = 0; k < link[i + 1].getNbLine(); k++)
				{
					sf::Vector2f pos1 = m_allNeurone[i][j].getPosition();
					sf::Vector2f pos2 = m_allNeurone[i + 1][k].getPosition();
					sf::RectangleShape rect;
					float width = ((abs(link[i + 1][k][j]) / maxWeight) * maxWidth);
					float length = O::math::getDistance(pos1, pos2);
					float angle = O::math::ToDeg(math::getAngle(pos1, pos2));
					if (link[i + 1][k][j] >= 0) rect.setFillColor(sf::Color(50, 255, 50, 200));
					else rect.setFillColor(sf::Color(255, 50, 50, 200));
					rect.setOrigin(0, width / 2.0);
					if (width > maxWidth)
					{
						rect.setSize(sf::Vector2f(length, maxWidth));
						if (link[i + 1][k][j] >= 0) rect.setFillColor(sf::Color(255, 255, 0, 150));
						else rect.setFillColor(sf::Color(255, 0, 255, 150));
						rect.setOrigin(0, maxWidth / 2.0);
					}
					else
					{
						rect.setSize(sf::Vector2f(length, width));
					}
					rect.setPosition(pos1);
					rect.setRotation(angle);
					conec.push_back(rect);
				}
				layer.push_back(conec);
			}
			m_allLink.push_back(layer);
		}
	}
	else if (m_visualKind == 1)
	{
		//std::cout << "// A" <<std::endl;
		double maxBiais = 0;
		double maxWeight = 0;

		std::vector<std::vector<Neuron>> gnnNeurons = m_visualGnn.getNeurons();

		for (size_t i = 0; i < gnnNeurons.size(); i++)
		{
			for (size_t j = 0; j < gnnNeurons[i].size(); j++)
			{
				if (abs(gnnNeurons[i][j].biais) > maxBiais) maxBiais = abs(gnnNeurons[i][j].biais);

				for (size_t k = 0; k < gnnNeurons[i][j].out.size(); k++)
				{
					if (abs(gnnNeurons[i][j].out[k].third) > maxWeight) maxWeight = abs(gnnNeurons[i][j].out[k].third);
				}
			}
		}

		
		//std::cout << "// B" <<std::endl;

		//std::cout << "Max for biais : " + O::str::to_string(maxBiais, 2) +"\nMax for Weight : " + O::str::to_string(maxWeight, 2) <<std::endl;
		//m_textShowMaxBiasAndWheight.setString("Max for biais : " + O::str::to_string(maxBiais, 2) +"\nMax for Weight : " + O::str::to_string(maxWeight, 2));

		float margin = 50.0;

		m_allNeurone.clear();
		m_allBiais.clear();

		std::vector<int> layers = m_visualGnn.getLayersStructure();
		int width = layers.size();
		int heightMax = 0;
		for (size_t i = 0; i < layers.size(); i++)
		{
			if (layers[i] > heightMax) heightMax = layers[i];
		}
		// /!\ on garde un espacement avec les bordures de 50
		float heightWithMargins = (650.0 - margin * 2.0);
		float widthWithMargins = (800.0 - margin * 2.0);
		float spacingBetweenNeuron = heightWithMargins / (float)heightMax;
		float radiusCir = spacingBetweenNeuron / 4.0;
		float spacingBetweenLayers = (widthWithMargins / (float)(width - 1)) - (radiusCir * 2.0) / ((float)(layers.size() - 1));
		
		//std::cout << "// C" <<std::endl;
		// on affiche les neurones
		for (size_t i = 0; i < layers.size(); i++)
		{
			std::vector<sf::CircleShape> neurons;
			std::vector<sf::CircleShape> neuronsBiais;
			float posX = spacingBetweenLayers * i + margin + radiusCir;
			float firstPosY = (layers[i] == 1) ? heightWithMargins / 2.0 : 0;//((1.0 - ((float)layers[i] / (float)heightMax)) * heightWithMargins) / 2.0;

			for (size_t j = 0; j < layers[i]; j++)
			{

				float posY = (layers[i] == 1) ? firstPosY + margin: spacingBetweenNeuron * ((float)(heightMax - 1) / ((float)layers[i] - 1)) * j + firstPosY + margin + spacingBetweenNeuron / 2.0;
				sf::CircleShape cercle;
				cercle.setFillColor(sf::Color(100,100,255));
				cercle.setRadius(radiusCir);
				cercle.setOrigin(radiusCir, radiusCir);
				cercle.setPosition(posX, posY);

				if (i == 0)
				{
					if (j < m_inputTexts.size())
						m_inputTexts[j].setPosition(posX - radiusCir - m_inputTexts[j].getGlobalBounds().width - 10 , posY -  m_inputTexts[j].getGlobalBounds().height);
				}
				if (i == layers.size() - 1)
				{
					if (j < m_inputTexts.size())
						m_ouputTexts[j].setPosition(posX + radiusCir + 10 , posY - m_ouputTexts[j].getGlobalBounds().height);
				}

				neurons.push_back(cercle);

				sf::CircleShape cercleBiais;
				if (gnnNeurons[i][j].biais >= 0) cercleBiais.setFillColor(sf::Color(120, 255, 120));
				else cercleBiais.setFillColor(sf::Color(255, 100, 100));
				float radius = (abs(gnnNeurons[i][j].biais) / maxBiais) * radiusCir;
				cercleBiais.setOrigin(radius, radius);
				if (radius > radiusCir)
				{
					cercleBiais.setRadius(radiusCir);
					if (gnnNeurons[i][j].biais >= 0) cercleBiais.setFillColor(sf::Color::Yellow);
					else cercleBiais.setFillColor(sf::Color::Magenta);
					cercleBiais.setOrigin(radiusCir, radiusCir);
				}
				else
				{
					cercleBiais.setRadius(radius);
				}
				cercleBiais.setPosition(posX, posY);
				neuronsBiais.push_back(cercleBiais);
			}
			m_allNeurone.push_back(neurons);
			m_allBiais.push_back(neuronsBiais);
		}

		
		//std::cout << "// D" <<std::endl;

		// on affiche les liens
		m_allLink.clear();
		float maxWidth = radiusCir;
		for (size_t i = 0; i < layers.size() - 1; i++)
		{
			//std::cout << link[i + 1] <<std::endl;
			std::vector<std::vector<sf::RectangleShape>> layer;
			for (size_t j = 0; j < layers[i]; j++)
			{
				std::vector<sf::RectangleShape> conec;
				for (size_t k = 0; k < gnnNeurons[i][j].out.size(); k++)
				{
					sf::Vector2f pos1 = m_allNeurone[i][j].getPosition();
					sf::Vector2f pos2 = m_allNeurone[gnnNeurons[i][j].out[k].first][gnnNeurons[i][j].out[k].second].getPosition();
					sf::RectangleShape rect;
					float width = (abs(gnnNeurons[i][j].out[k].third) / maxWeight) * (maxWidth - 1) + 1;
					float length = O::math::getDistance(pos1, pos2);
					float angle = O::math::ToDeg(math::getAngle(pos1, pos2));
					if (gnnNeurons[i][j].out[k].third >= 0) rect.setFillColor(sf::Color(50, 255, 50, 200));
					else rect.setFillColor(sf::Color(255, 50, 50, 200));
					rect.setOrigin(0, width / 2.0);
					if (width > maxWidth)
					{
						rect.setSize(sf::Vector2f(length, maxWidth));
						if (gnnNeurons[i][j].out[k].third >= 0) rect.setFillColor(sf::Color(255, 255, 0, 150));
						else rect.setFillColor(sf::Color(255, 0, 255, 150));
						rect.setOrigin(0, maxWidth / 2.0);
					}
					else
					{
						rect.setSize(sf::Vector2f(length, width));
					}
					rect.setPosition(pos1);
					rect.setRotation(angle);
					conec.push_back(rect);
				}
				layer.push_back(conec);
			}
			m_allLink.push_back(layer);
		}
		
		//std::cout << "// E" <<std::endl;
	}
}



void NeuralNetworkVisualizer::close() {
	m_fen.close();
}


void NeuralNetworkVisualizer::setInputTexts(std::vector<sf::String> texts)
{
	for (size_t i = 0; i < texts.size(); i++)
	{
		m_inputTexts.push_back(sf::Text(texts[i], m_font));
	}
	
}
void NeuralNetworkVisualizer::setOutputTexts(std::vector<sf::String> texts)
{
	for (size_t i = 0; i < texts.size(); i++)
	{
		m_ouputTexts.push_back(sf::Text(texts[i], m_font));
	}
}


void NeuralNetworkVisualizer::setFont(sf::Font& font)
{
	m_font = font;
}

}}