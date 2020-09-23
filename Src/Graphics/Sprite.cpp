#include "Sprite.h"


namespace ssf
{
	Sprite::Sprite() :m_local("")
	{

	}

	Sprite::Sprite(sf::RenderWindow* window, std::string local, float x, float y, float posRx, float posRy, bool centered) : m_sprite(),
		m_x(x), m_y(y)
	{
		m_fen = window;

		if (posRx == -1) m_posRx = x;
		else m_posRx = posRx;
		if (posRy == -1) m_posRy = y;
		else m_posRy = posRy;

		m_local = local;

		m_isOrigineAsCenter = false;

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

	Sprite::Sprite(sf::RenderWindow* window, std::string local, float x, float y, bool centered):
		Sprite(window, local, x, y, -1, -1, centered)
	{
	}

	Sprite::Sprite(sf::RenderWindow* window, std::string local, float x, float y):
		Sprite(window, local, x, y, -1, -1, false)
	{
	}

	void Sprite::loadTexture()
	{
		m_texture.loadFromFile(m_local);
		m_sprite.setTexture(m_texture);

		if (m_isOrigineAsCenter)
		{
			setOrigineAsCenter();
		}
		else
		{
			update();
		}
		
	}

	void Sprite::loadTexture(sf::Texture& tex)
	{

		m_sprite.setTexture(tex);

		if (m_isOrigineAsCenter)
		{
			sf::FloatRect r = m_sprite.getGlobalBounds();
			m_sprite.setOrigin(r.width / (2.0 * m_sprite.getScale().x), r.height / (2.0 * m_sprite.getScale().y));
		}
		update();
	}

	void Sprite::update()
	{
		//facteur de redimentionnement
		float factorX = (float)m_fen->getSize().x / STATIC::SYS::WIDTH;
		float factorY = (float)m_fen->getSize().y / STATIC::SYS::HIGHT;

		

		m_sprite.setPosition(m_x + (factorX - 1) * m_posRx, m_y + (factorY - 1) * m_posRy);

	}

	void Sprite::update(float viewZoom)
	{
		setScale(viewZoom, viewZoom);
		
		//facteur de redimentionnement
		float factorX = (float)m_fen->getSize().x / STATIC::SYS::WIDTH;
		float factorY = (float)m_fen->getSize().y / STATIC::SYS::HIGHT;

		m_sprite.setPosition(m_x + (factorX - 1) * m_posRx * viewZoom, m_y + (factorY - 1) * m_posRy * viewZoom);
	}

	void Sprite::draw()
	{
		m_fen->draw(m_sprite);
	}

	void Sprite::draw(sf::IntRect bound)
	{
		if (bound.contains(m_sprite.getPosition().x, m_sprite.getPosition().y))
		{
			m_fen->draw(m_sprite);
		}
	}

	void Sprite::setColor(sf::Color c)
	{
		m_sprite.setColor(c);
	}

	sf::Sprite& Sprite::gS()
	{
		return m_sprite;
	}

	void Sprite::setPosition(float x, float y)
	{
		m_x = x;
		m_y = y;
	}
	void Sprite::setPosition(float x, float y, bool update)
	{
		m_x = x;
		m_y = y;
		if (update) Sprite::update();
	}
	sf::Vector2f Sprite::getPosition()
	{
		return sf::Vector2f(m_x, m_y);
	}

	void Sprite::move(float x, float y)
	{
		setPosition(getPosition().x + x, getPosition().y + y);
	}
	void Sprite::setScale(float x, float y)
	{
		m_sprite.setScale(x, y);
	}

	bool Sprite::hover(float viewZoom)
	{
		sf::View v = m_fen->getView();
		float x = sf::Mouse::getPosition(*m_fen).x * viewZoom + v.getCenter().x - v.getSize().x / 2;
		float y = sf::Mouse::getPosition(*m_fen).y * viewZoom + v.getCenter().y - v.getSize().y / 2;

		return (m_sprite.getGlobalBounds().contains(x, y));
	}

	bool Sprite::clicked(sf::Event& e, float viewZoom)
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

	void Sprite::setPointRedi(float x, float y)
	{
		m_posRx = x;
		m_posRy = y;
	}

	void Sprite::setOrigineAsCenter()
	{
		sf::FloatRect r = m_sprite.getGlobalBounds();
		m_sprite.setOrigin(r.width / (2.0 * m_sprite.getScale().x), r.height / (2.0 * m_sprite.getScale().y));
		m_isOrigineAsCenter = true;

		update();
	}

}