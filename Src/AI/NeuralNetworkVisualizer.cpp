#include "NeuralNetworkVisualizer.h"

NeuralNetworkVisualizer::NeuralNetworkVisualizer():
	m_haveTempData(false),
	m_textShowMaxBiasAndWheight(&m_fen, 400, 10, false)
{
	m_textShowMaxBiasAndWheight.setCharacterSize(25);
}

void NeuralNetworkVisualizer::setPosition(int x, int y)
{
	m_fen.setPosition(sf::Vector2i(x, y));
}

void NeuralNetworkVisualizer::run()
{
	m_fen.create(sf::VideoMode(800, 650), "neuronal visualisation", sf::Style::Default, sf::ContextSettings(0, 0, 3));
	m_fen.setFramerateLimit(10);
	while (m_fen.isOpen())
	{
		event();
		update();
		render();
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
	m_textShowMaxBiasAndWheight.update();

	if (m_haveTempData)
	{
		m_haveTempData = false;
		updateVisualise();
	}
}

void NeuralNetworkVisualizer::render()
{
	m_fen.clear(sf::Color(19,19,19));

	m_textShowMaxBiasAndWheight.draw();

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
	m_fen.display();
}

void NeuralNetworkVisualizer::visualise(NeuralNetwork n)
{
	m_visual = n;
	m_haveTempData = true;
}

void NeuralNetworkVisualizer::updateVisualise()
{
	double maxBiais = 0;
	double maxWeight = 0;

	std::vector < std::vector<long double>> b = m_visual.getAllLayerNeuroneBiais();
	std::vector<std::vector<std::vector<long double>>> w = m_visual.getAllLink();
	for (size_t i = 0; i < w.size(); i++)
	{
		for (size_t j = 0; j < w[i].size(); j++)
		{
			if (abs(b[i][j]) > maxBiais) maxBiais = abs(b[i][j]);

			for (size_t k = 0; k < w[i][j].size(); k++)
			{
				if (abs(w[i][j][k]) > maxWeight) maxWeight = abs(w[i][j][k]);
			}
		}
	}


	m_textShowMaxBiasAndWheight.setString("Max for biais : " + std::to_string(maxBiais, 2) +"\nMax for Weight : " + std::to_string(maxWeight, 2));

	float margin = 50.0;

	m_allNeurone.clear();
	m_allBiais.clear();

	std::vector<int> layers = m_visual.getAllLayerNeurone();
	std::vector<std::vector<long double>> layersBiais = m_visual.getAllLayerNeuroneBiais();
	int width = layers.size();
	int heightMax = 0;
	for (size_t i = 0; i < layers.size(); i++)
	{
		if (layers[i] > heightMax) heightMax = layers[i];
	}
	// /!\ on garde un espacement avec les bordures de 50
	float heightWithMargins = (650.0 - margin * 2.0);
	float widthWithMargins = (800.0 - margin * 2.0);
	float spacingBetweenLayers = widthWithMargins / (float)width;
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
			neurons.push_back(cercle);

			sf::CircleShape cercleBiais;
			if (layersBiais[i][j] >= 0) cercleBiais.setFillColor(sf::Color(120, 255, 120));
			else cercleBiais.setFillColor(sf::Color(255, 100, 100));
			float radius = (abs(layersBiais[i][j]) / maxBiais) * radiusCir;
			cercleBiais.setOrigin(radius, radius);
			if (radius > radiusCir)
			{
				cercleBiais.setRadius(radiusCir);
				if (layersBiais[i][j] >= 0) cercleBiais.setFillColor(sf::Color::Yellow);
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
	std::vector<std::vector<std::vector<long double>>> link = m_visual.getAllLink();
	float maxWidth = radiusCir;

	for (size_t i = 0; i < link.size(); i++)
	{
		std::vector<std::vector<sf::RectangleShape>> layer;
		for (size_t j = 0; j < link[i].size(); j++)
		{
			std::vector<sf::RectangleShape> conec;
			for (size_t k = 0; k < link[i][j].size(); k++)
			{
				sf::Vector2f pos1 = m_allNeurone[i][j].getPosition();
				sf::Vector2f pos2 = m_allNeurone[i + 1][k].getPosition();
				sf::RectangleShape rect;
				float width = ((abs(link[i][j][k]) / maxWeight) * maxWidth);
				float length = math::getDistance((sf::Vector2f)pos1, (sf::Vector2f)pos2);
				float angle = math::ToDeg(math::getAngle((sf::Vector2f)pos1, (sf::Vector2f)pos2));
				if (link[i][j][k] >= 0) rect.setFillColor(sf::Color(50, 255, 50, 200));
				else rect.setFillColor(sf::Color(255, 50, 50, 200));
				rect.setOrigin(0, width / 2.0);
				if (width > maxWidth)
				{
					rect.setSize(sf::Vector2f(length, maxWidth));
					if (link[i][j][k] >= 0) rect.setFillColor(sf::Color(255, 255, 0, 150));
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



void NeuralNetworkVisualizer::close() {
	m_fen.close();
}