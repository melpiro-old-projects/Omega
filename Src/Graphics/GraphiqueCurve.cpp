#include "GraphiqueCurve.h"

GraphiqueCurve::GraphiqueCurve()
{
}

GraphiqueCurve::GraphiqueCurve(sf::RenderWindow* window, float x, float y, float sizeX, float sizeY, float posRx, float posRy, bool centered) :
	m_fen(window),
	m_background(window, x, y, sizeX, sizeY, posRx, posRy, centered)
{
	m_background.setFillColor(sf::Color(20, 20, 20, 100));
}

GraphiqueCurve::GraphiqueCurve(sf::RenderWindow* window, float x, float y, float sizeX, float sizeY, bool centered):
	GraphiqueCurve(window, x, y, sizeX, sizeY, -1,-1, centered)
{

}

void GraphiqueCurve::setBackgroundColor(sf::Color c)
{
	m_background.setFillColor(c);
}

void GraphiqueCurve::setBackgroundOutlineThickness(float value)
{
	m_background.setOutlineThickness(value);
}

void GraphiqueCurve::setBackgroundOutlineColor(sf::Color c)
{
	m_background.setOutlineColor(c);
}

void GraphiqueCurve::setLineWidth(std::string name, float width)
{
	auto it = m_allCourbe.find(name);

	if (it != m_allCourbe.end())
	{
		for (size_t i = 0; i < it->second.first.second.size(); i++)
		{
			it->second.first.second[i].setWidth(width);
		}
	}
	
}

void GraphiqueCurve::setLineWidth(float width)
{
	m_ligneWidth = width;
	auto it = m_allCourbe.begin();
	for (it; it != m_allCourbe.end(); it++)
	{
		for (size_t i = 0; i < it->second.first.second.size(); i++)
		{
			it->second.first.second[i].setWidth(width);
		}

	}
}

void GraphiqueCurve::addCourbe(std::string name, sf::Color couleur)
{
	std::pair < std::pair < std::vector<sf::Vector2f>, std::vector < ssf::Line >> , sf::Color > courbe;

	courbe.first.first = std::vector < sf::Vector2f>(0);
	courbe.first.second = std::vector < ssf::Line>(0);
	courbe.second = couleur;

	m_allCourbe[name] = courbe;
}

void GraphiqueCurve::addPoint(std::string name, sf::Vector2f coord)
{
	auto it = m_allCourbe.find(name);

	if (it != m_allCourbe.end())
	{
		// on ajoute le point
		it->second.first.first.push_back(coord);

		// si il y a plus de deux point -> conection !
		if (it->second.first.first.size() >= 2)
		{
			float lineWidth = m_ligneWidth;
			if (it->second.first.second.size() > 0)
			{
				lineWidth = it->second.first.second.back().getWidth();
			}
			sf::Vector2f pointRedi = m_background.getPointRedi();

			ssf::Line newLine(m_fen, sf::Vector2f(1, 1), sf::Vector2f(10, 10), m_ligneWidth, pointRedi.x, pointRedi.y);
			newLine.setFillColor(it->second.second);

			it->second.first.second.push_back(newLine);
		}
	}
}

void GraphiqueCurve::setPosition(float x, float y)
{
	m_background.setPosition(x, y);
}

void GraphiqueCurve::clear()
{
	m_allCourbe.clear();
}

void GraphiqueCurve::update()
{

	m_background.update();

	auto it = m_allCourbe.begin();
	for (it; it != m_allCourbe.end(); it++)
	{
		for (size_t i = 0; i < it->second.first.second.size(); i++)
		{
			it->second.first.second[i].update();
		}

	}
}

void GraphiqueCurve::update(double viewZoom)
{
	m_background.update(viewZoom);
	updateView(viewZoom);
}

void GraphiqueCurve::draw()
{
	m_background.draw();

	auto it = m_allCourbe.begin();
	for (it; it != m_allCourbe.end(); it++)
	{
		for (size_t i = 0; i < it->second.first.second.size(); i++)
		{
			it->second.first.second[i].draw();
		}
	}
}

void GraphiqueCurve::updateView(double viewZoom)
{
	float minX = 10000000;
	float maxX = 0;

	float minY = 10000000;
	float maxY = 0;
	auto it = m_allCourbe.begin();
	for (it; it != m_allCourbe.end(); it++)
	{
		///////////////////////////////////////////////////////////////:
		// on calcule l'echelle des élement que l'ont vas devoir représenter

		for (size_t i = 0; i < it->second.first.first.size(); i++)
		{
			sf::Vector2f p = it->second.first.first[i];
			if (p.x > maxX)
			{
				maxX = p.x;
			}
			if (p.y > maxY)
			{
				maxY = p.y;
			}
			if (p.x < minX)
			{
				minX = p.x;
			}
			if (p.y < minY)
			{
				minY = p.y;
			}
		}
	}
	it = m_allCourbe.begin();
	for (it; it != m_allCourbe.end(); it++)
	{
		///////////////////////////////////////////////////////////////:
		// on détermine le visuel

		sf::FloatRect rect = m_background.gR().getGlobalBounds();

		double maxWidthForDraw = rect.width - (PADDING * 2.0 - m_background.getOutlineThickness() * 2.0) * viewZoom;
		double maxHeightForDraw = rect.height - (PADDING * 2.0  - m_background.getOutlineThickness() * 2.0) * viewZoom;

		sf::Vector2f topLeftCornerCoords(rect.left + (PADDING + m_background.getOutlineThickness()) * viewZoom, rect.top + (PADDING + m_background.getOutlineThickness()) * viewZoom);

		for (int i = 0; i < ((int)it->second.first.first.size()) - 1; i++)
		{
			sf::Vector2f ratio1((it->second.first.first[i].x - minX) / (maxX - minX), (it->second.first.first[i].y - minY) / (maxY - minY));
			sf::Vector2f p1( ratio1.x * maxWidthForDraw + topLeftCornerCoords.x, -ratio1.y * maxHeightForDraw + topLeftCornerCoords.y + (rect.height - 2.0 * PADDING * viewZoom));

			sf::Vector2f ratio2((it->second.first.first[i + 1].x - minX) / (maxX - minX), (it->second.first.first[i + 1].y - minY) / (maxY - minY));
			sf::Vector2f p2( ratio2.x * maxWidthForDraw + topLeftCornerCoords.x, -ratio2.y * maxHeightForDraw + topLeftCornerCoords.y + (rect.height - 2.0 * PADDING * viewZoom));


			it->second.first.second[i].setWidth(m_ligneWidth * viewZoom);
			it->second.first.second[i].setPoints(p1, p2);
		}
	}
}


