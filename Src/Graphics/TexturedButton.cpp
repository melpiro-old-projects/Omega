#include "TexturedButton.h"


namespace ssf {
	TexturedButton::TexturedButton()
	{
		ssf::Text::setOrigineAsCenter();
	}

	TexturedButton::TexturedButton(sf::RenderWindow* fen,std::string local, float x, float y, float posRx, float posRy, bool centered) :
		m_fen(fen),
		Sprite(fen, local, x, y, posRx, posRy, centered),
		Text(fen, x, y, 0, 0, true)// le texte est toujour centré !
	{
		m_rectB = sf::IntRect(-1, -1, -1, -1);
		m_rectHover = sf::IntRect(-1, -1, -1, -1);
	}

	TexturedButton::TexturedButton(sf::RenderWindow* window, std::string local, float x, float y, bool centered):
		TexturedButton(window, local, x, y, -1, -1, centered)
	{

	}

	void TexturedButton::loadTexture()
	{
		Sprite::loadTexture();

		if (m_rectB.height == -1 && m_rectB.width == -1)
			calcNoRectHover();

	}
	void TexturedButton::loadTexture(sf::Texture& tex)
	{
		Sprite::loadTexture(tex);

		if (m_rectB.height == -1 && m_rectB.width == -1) 
			calcNoRectHover();
	}


	bool TexturedButton::hover(float viewZoom)
	{
		bool isIn = Sprite::hover(viewZoom);
		if (isIn)
		{
			gS().setTextureRect(m_rectHover);
			update();
		}
		else
		{
			gS().setTextureRect(m_rectB);
			update();
		}
		return isIn;
	}

	bool TexturedButton::clicked(sf::Event& e, float viewZoom)
	{
		if (hover(viewZoom))
		{
			if (e.type == sf::Event::MouseButtonReleased)
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					return true;
				}
			}
		}
	
		return false;
	}

	void TexturedButton::update()
	{
		Sprite::update();
		updatePosText();
	}
	void TexturedButton::update(float viewZoom)
	{
		Sprite::update(viewZoom);
		updatePosText();

	}


	void TexturedButton::draw()
	{
		Sprite::draw();
		Text::draw();
	}

	void TexturedButton::setRectButton(sf::IntRect rectB, sf::IntRect rectHover)
	{
		m_rectB = rectB;
		m_rectHover = rectHover;
		gS().setTextureRect(rectB);
		if (Sprite::m_isOrigineAsCenter) Sprite::setOrigineAsCenter();
	}

	void TexturedButton::setPosition(float x, float y)
	{
		Sprite::setPosition(x, y);
		updatePosText();
	}

	void TexturedButton::move(float x, float y)
	{
		TexturedButton::setPosition(Sprite::getPosition().x + x, Sprite::getPosition().y + y);
	}

	void TexturedButton::setPointRedi(float x, float y)
	{
		Sprite::m_posRx = x;
		Sprite::m_posRy = y;
		Text::m_posRx = x;
		Text::m_posRy = y;
	}

	void TexturedButton::setOrigineAsCenter()
	{
		Sprite::setOrigineAsCenter();
		update();
	}

	void TexturedButton::updatePosText()
	{
		sf::FloatRect rect = m_sprite.getGlobalBounds();
		Text::setPosition(rect.left + rect.width / 2.0, rect.top + rect.height / 2.0);
		Text::update();
	}

	void TexturedButton::setTextColor(sf::Color c)
	{
		m_text.setFillColor(c);
	}

	void TexturedButton::calcAutoRectHover()
	{
		sf::Vector2u size = m_texture.getSize();
		m_rectB = sf::IntRect(0, 0, size.x, size.y / 2.0);
		m_rectHover = sf::IntRect(0, size.y / 2.0, size.x, size.y / 2.0);
	}

	void TexturedButton::calcNoRectHover()
	{
		sf::Vector2u size = m_texture.getSize();
		m_rectB = sf::IntRect(0, 0, size.x, size.y);
		m_rectHover = sf::IntRect(0, 0, size.x, size.y);
	}


}