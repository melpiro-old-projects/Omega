#include "Text.h"


namespace ssf {

	Text::Text() : m_text()
	{
		m_x = 0;
		m_y = 0;
		m_isOrigineAsCenter = false;
	}
	Text::Text(sf::RenderWindow* window, float x, float y, float posRx, float posRy, bool centered) : m_text()
	{
		m_fen = window; // on defini la fenetre
		m_text.setFont(GLOBAL::GLOBAL_FONT["global"]); // on defini la font

		// positionement de l'element
		m_x = x; 
		m_y = y;

		// delta de redimention
		if (posRx == -1) m_posRx = x;
		else m_posRx = posRx;
		if (posRy == -1) m_posRy = y;
		else m_posRy = posRy;

		if (centered)
		{
			// si l'objet doit etre centr�, un appel � update n'est pas n�c�saire
			// car la fonction setOrigineAsCenter le fait deja !
			setOrigineAsCenter();
		}
		else
		{
			update();
		}
	}

	Text::Text(sf::RenderWindow* window,std::string fontName, float x, float y, float posRx, float posRy, bool centered)
	{
		m_fen = window; // on defini la fenetre
		m_text.setFont(GLOBAL::GLOBAL_FONT[fontName]); // on defini la font

		// positionement de l'element
		m_x = x; 
		m_y = y;

		// delta de redimention
		if (posRx == -1) m_posRx = x;
		else m_posRx = posRx;
		if (posRy == -1) m_posRy = y;
		else m_posRy = posRy;

		if (centered)
		{
			// si l'objet doit etre centr�, un appel � update n'est pas n�c�saire
			// car la fonction setOrigineAsCenter le fait deja !
			setOrigineAsCenter();
		}
		else
		{
			update();
		}
	}

	Text::Text(sf::RenderWindow* window, float x, float y, bool centered):
		ssf::Text(window, x, y, -1.f, -1.f, centered)
	{

	}
	Text::Text(sf::RenderWindow* window, float x, float y) :
		ssf::Text(window, x, y, -1.f, -1.f, false)
	{

	}
	void Text::update()
	{
		//facteur de redimentionnement
		float factorX = (float)m_fen->getSize().x / STATIC::SYS::WIDTH;
		float factorY = (float)m_fen->getSize().y / STATIC::SYS::HIGHT;

		m_text.setPosition(m_x + (factorX - 1) * m_posRx, m_y + (factorY - 1) * m_posRy);

	}
	void Text::update(float viewZoom)
	{
		setScale(viewZoom, viewZoom);

		//facteur de redimentionnement
		float factorX = (float)m_fen->getSize().x / STATIC::SYS::WIDTH;
		float factorY = (float)m_fen->getSize().y / STATIC::SYS::HIGHT;

		m_text.setPosition(m_x + (factorX - 1) * m_posRx * viewZoom, m_y + (factorY - 1) * m_posRy * viewZoom);
	}
	void Text::draw()
	{
		m_fen->draw(m_text);
	}
	sf::Text& Text::gT()
	{
		return m_text;
	}
	void Text::setPosition(float x, float y)
	{
		m_x = x;
		m_y = y;
	}
	void Text::setPosition(float x, float y, bool update)
	{
		m_x = x;
		m_y = y;
		if (update) Text::update();
	}
	sf::Vector2f Text::getPosition()
	{
		return sf::Vector2f(m_x, m_y);
	}
	void Text::move(float x, float y)
	{
		setPosition(getPosition().x + x, getPosition().y + y);
	}
	bool Text::hover(float viewZoom)
	{
		sf::View v = m_fen->getView();
		float x = sf::Mouse::getPosition(*m_fen).x * viewZoom + v.getCenter().x - v.getSize().x / 2;
		float y = sf::Mouse::getPosition(*m_fen).y * viewZoom + v.getCenter().y - v.getSize().y / 2;

		return (m_text.getGlobalBounds().contains(x, y));
	}
	void Text::setScale(float x, float y)
	{
		m_text.setScale(x, y);
	}
	bool Text::clicked(sf::Event& e, float viewZoom)
	{
		if (e.type == sf::Event::MouseButtonReleased)
		{
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				if (hover(viewZoom))
				{
					return true;
				}
			}
		}
		return false;
	}
	void Text::setString(sf::String text)
	{
		m_text.setString(text);

		if (m_isOrigineAsCenter) setOrigineAsCenter();
	}
	sf::String Text::getString()
	{
		return m_text.getString();
	}
	void Text::setCharacterSize(unsigned int value)
	{
		m_text.setCharacterSize(value);
		if (m_isOrigineAsCenter) setOrigineAsCenter();
	}
	void Text::setPointRedi(float x, float y)
	{
		m_posRx = x;
		m_posRy = y;

		update();
	}
	void Text::setOrigineAsCenter()
	{
		sf::FloatRect r = m_text.getGlobalBounds();
		m_text.setOrigin(r.width / 2.0, r.height / 2.0 +(float) m_text.getCharacterSize() /5.0);
		m_isOrigineAsCenter = true;

		update();
	}
}