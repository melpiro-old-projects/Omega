#pragma once


#include "AI/ArtificialNeuralNetwork.hpp"
#include "AI/GeneticNeuralNetwork.hpp"
#include "Math/MathFunctions.h"
#include "String/StringFunctions.h"
#include "Operators/PrintFunctions.h"

namespace O
{
namespace AI
{


class NeuralNetworkVisualizer
{
public:
	NeuralNetworkVisualizer();

	void setPosition(int x, int y);

	void run();

	void close();

	void visualise(O::AI::ArtificialNeuralNetwork n);
	void visualise(O::AI::GeneticNeuralNetwork n);
	
	void setInputTexts(std::vector<sf::String> texts);
	void setOutputTexts(std::vector<sf::String> texts);

	void setFont(sf::Font& font);
private:

	void event();
	void update();
	void render();

	void updateVisualise();

	bool m_haveTempData;

	sf::RenderWindow m_fen;

	int m_visualKind = 0;
	O::AI::ArtificialNeuralNetwork m_visualAnn;
	O::AI::GeneticNeuralNetwork m_visualGnn;

	//O::graphics::Text m_textShowMaxBiasAndWheight;

	std::vector<std::vector<sf::CircleShape>> m_allNeurone;
	std::vector<std::vector<sf::CircleShape>> m_allBiais;

	std::vector < std::vector<std::vector<sf::RectangleShape>>> m_allLink;

	std::vector<sf::Text> m_inputTexts;
	std::vector<sf::Text> m_ouputTexts;
	sf::Font m_font;
};

}}