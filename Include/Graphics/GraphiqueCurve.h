#pragma once

#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "Line.h"


class GraphiqueCurve
{
public:
	GraphiqueCurve();
	GraphiqueCurve(sf::RenderWindow* window, float x, float y, float sizeX, float sizeY, float posRx, float posRy, bool centered = true);
	GraphiqueCurve(sf::RenderWindow* window, float x, float y, float sizeX, float sizeY, bool centered = true);

	void setBackgroundColor(sf::Color c);
	void setBackgroundOutlineThickness(float value);
	void setBackgroundOutlineColor(sf::Color c);
	void setLineWidth(std::string name, float width);
	void setLineWidth(float width);

	void addCourbe(std::string name, sf::Color couleur);
	void addPoint(std::string name, sf::Vector2f coord);

	void setPosition(float x, float y);

	void clear();

	void update();
	void update(double viewZoom);
	void draw();

private:

	void updateView(double viewZoom = 1);

	sf::RenderWindow* m_fen;

	ssf::Rectangle m_background;


	double m_ligneWidth = 5;
	const double PADDING = 10;

	std::map<std::string, std::pair<std::pair<std::vector<sf::Vector2f>, std::vector<ssf::Line>>, sf::Color>> m_allCourbe;



};

