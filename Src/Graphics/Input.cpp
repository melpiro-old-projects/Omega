#include "Input.h"

namespace ssf {
	
	Input::Input()
	{

	}

	Input::Input(sf::RenderWindow* window, float x, float y, float sizeX, float sizeY, float posRx, float posRy, bool centered):
		ssf::Input(window,"global", x, y, sizeX, sizeY, posRx, posRy, centered)
	{
		

	}


	Input::Input(sf::RenderWindow* window, std::string font, float x, float y, float sizeX, float sizeY, float posRx, float posRy, bool centered):
		ssf::Button(window, font, x, y, sizeX, sizeY, posRx, posRy, centered)
	{
		ssf::Text::m_isOrigineAsCenter = false;
		ssf::Text::gT().setOrigin(0, 0);
		//ssf::Text::update();

		ssf::Button::setColorOnHover(sf::Color::Transparent, sf::Color::Transparent);
		ssf::Button::setOutlineColorOnHover(sf::Color::White, sf::Color::White);
		ssf::Button::setOutlineThickness(3);
		ssf::Button::setCharacterSize(sizeY - ssf::Button::getOutlineThickness() * 2.0 - 4);

		m_cursor.setSize(sf::Vector2f( 1, ssf::Button::gT().getCharacterSize() ));
		setCharacterSize(sizeY * 8.8 / 10.0);
		m_cursor.setFillColor(sf::Color::White);

		update();

	}




	Input::Input(sf::RenderWindow* window, float x, float y, float sizeX, float sizeY, bool centered):
		Input(window, x,y, sizeX, sizeY,-1,-1,centered)
	{
	}

	bool Input::event(sf::Event e)
	{
		if (Button::clicked(e))
		{
			m_haveFocus = true;
			updatePosCursor();
		}
		else if (e.type == sf::Event::MouseButtonReleased)
		{
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				setFocus(false);
			}
		}

		if (m_haveFocus)
		{
			if (e.type == sf::Event::KeyReleased)
			{
				if (e.key.code == sf::Keyboard::Escape || e.key.code == sf::Keyboard::Return)
				{
					setFocus(false);
					return false;
				}
			}
			if (e.type == sf::Event::TextEntered)
			{
				if (e.text.unicode == 8)
				{
					
					std::string str = ssf::Button::getString();
					if (str.size() > 0)
					{
						str.pop_back();
						ssf::Button::setString(str);
						update();
						return true;
					}
				}
				else
				{
					char c = e.text.unicode;
					ssf::Button::setString(ssf::Button::getString() + c);

					if (m_text.getGlobalBounds().width > m_rectangle.getGlobalBounds().width - m_rectangle.getOutlineThickness() - 8)
					{
						std::string str = ssf::Button::getString();
						str.pop_back();
						ssf::Button::setString(str);
					}
					else
					{
						update();
						return true;
					}
				}
			}
		}
		return false;
	}

	void Input::setString(std::string str)
	{
		ssf::Text::setString(str);
		update();
	}

	std::string Input::getString()
	{
		return m_text.getString();
	}

	void Input::draw()
	{
		Button::draw();
		if (m_haveFocus)
		{
			m_fen->draw(m_cursor);
		}
	}

	void Input::setFocus(bool value)
	{
		m_haveFocus = value;
		update();
	}

	bool Input::haveFocus()
	{
		return m_haveFocus;
	}

	void Input::setPosition(float x, float y)
	{
		Rectangle::setPosition(x, y);
		updatePosText();
	}

	void Input::move(float x, float y)
	{
		setPosition(Rectangle::getPosition().x + x, Rectangle::getPosition().y + y);
	}

	void Input::update()
	{
		Rectangle::update();
		updatePosText();
	}

	void Input::setOutlineThickness(float v)
	{
		Rectangle::setOutlineThickness(v);
		updatePosText();
	}

	void Input::updatePosText()
	{
		if (m_haveFocus) updatePosCursor();
		sf::FloatRect rect = m_rectangle.getGlobalBounds();
		sf::FloatRect textRect = m_text.getGlobalBounds();
		Text::setPosition(rect.left + ssf::Button::gR().getOutlineThickness() + 2, rect.top + rect.height / 2.0 - ((double)m_text.getCharacterSize()) / 1.5 );
		Text::update();
	}

	void Input::updatePosCursor()
	{

		sf::FloatRect boundText = m_text.getGlobalBounds();
		sf::FloatRect boundRect = m_rectangle.getGlobalBounds();
		m_cursor.setPosition(boundText.left + boundText.width + 2, boundRect.top + ssf::Button::getOutlineThickness() + 4);
	}

	void Input::setTextColor(sf::Color c)
	{
		m_text.setFillColor(c);
		m_cursor.setFillColor(c);
	}

	void Input::setCharacterSize(int value)
	{
		Text::setCharacterSize(value);
		m_cursor.setSize(sf::Vector2f( 1, ssf::Button::gT().getCharacterSize() ));
	}


}