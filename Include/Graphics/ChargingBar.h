#pragma once

#include "Rectangle.h"

class ChargingBar
{
public:
	ChargingBar();
	ChargingBar(sf::RenderWindow* window, float x, float y, float sizeX, float sizeY, float posRx, float posRy, bool centered = true);
	ChargingBar(sf::RenderWindow* window, float x, float y, float sizeX, float sizeY, bool centered = true);

	void setChargingValue(float value);
	float getChargingValue();

	void setMinChargingValue(double value);
	void setMaxChargingValue(double value);

	bool hover(float viewZoom = 1);
	bool clicked(sf::Event e, float viewZoom = 1);

	void update();
	void update(double viewZoom);

	void setPosition(float x, float y);
	void setPosition(float x, float y, bool update);
	void move(float x, float y);

	void setBackgroundColor(sf::Color c);
	void setForgroundColor(sf::Color c);
	void setOutlineThickness(double size);

	void setSize(float x, float y);

	double getOutlineThickness();
	void setOutlineColor(sf::Color c);

	void draw();

private:

	void updatePosForeground(double viewZoom = 1);

	sf::RenderWindow* m_fen;

	double m_minCharge = 0;
	double m_maxCharge = 1;
	double m_chargeValue = 0;
	double m_chargingPercent = 0;


	ssf::Rectangle m_backgroundRect;
	ssf::Rectangle m_foregroundRect;


};

