#pragma once

#include "NeuralNetwork.h"
#include <SFML/Graphics.hpp>
#include "Text.h"
#include "MathFunctions.h"
#include "StringFunctions.h"

class NeuralNetworkVisualizer
{
public:
	NeuralNetworkVisualizer();

	void setPosition(int x, int y);

	void event();
	void update();
	void render();

	void run();

	void close();

	void visualise(NeuralNetwork n);


private:

	void updateVisualise();

	bool m_haveTempData;

	sf::RenderWindow m_fen;

	NeuralNetwork m_visual;

	ssf::Text m_textShowMaxBiasAndWheight;

	std::vector<std::vector<sf::CircleShape>> m_allNeurone;
	std::vector<std::vector<sf::CircleShape>> m_allBiais;

	std::vector < std::vector<std::vector<sf::RectangleShape>>> m_allLink;

	
};

