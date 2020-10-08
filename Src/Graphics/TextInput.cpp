#include "TextInput.h"

namespace ssf {
	
	TextInput::TextInput()
	{

	}

	TextInput::TextInput(sf::RenderWindow* window, float x, float y, float sizeX, float sizeY, float posRx, float posRy, bool centered):
		ssf::TextInput(window,"global", x, y, sizeX, sizeY, posRx, posRy, centered)
	{
		

	}


	TextInput::TextInput(sf::RenderWindow* window, std::string font, float x, float y, float sizeX, float sizeY, float posRx, float posRy, bool centered):
		ssf::Input(window, font, x, y, sizeX, sizeY, posRx, posRy, centered)
	{
		
	}




	TextInput::TextInput(sf::RenderWindow* window, float x, float y, float sizeX, float sizeY, bool centered):
		TextInput(window, x,y, sizeX, sizeY,-1,-1,centered)
	{
		
	}

	bool TextInput::event(sf::Event e)
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
				if (e.key.code == sf::Keyboard::Escape)
				{
					setFocus(false);
					return false;
				}
			}
			if (e.type == sf::Event::TextEntered)
			{
				std::cout << e.text.unicode <<std::endl;
				if (e.text.unicode == 8) // effacer
				{
					if (nonModifiedString.getSize() > 0)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
						{
							while (nonModifiedString.getSize() > 0
								&&(nonModifiedString[nonModifiedString.getSize() - 1] == ' '
									||nonModifiedString[nonModifiedString.getSize() - 1] == '\n'))
							{
								nonModifiedString.erase(nonModifiedString.getSize() - 1);
							}
							while (nonModifiedString.getSize() > 0
								&&(nonModifiedString[nonModifiedString.getSize() - 1] != ' '
									&&nonModifiedString[nonModifiedString.getSize() - 1] != '\n'))
							{
								nonModifiedString.erase(nonModifiedString.getSize() - 1);
							}
							while (nonModifiedString.getSize() > 0
								&&(nonModifiedString[nonModifiedString.getSize() - 1] == ' '
									||nonModifiedString[nonModifiedString.getSize() - 1] == '\n'))
							{
								nonModifiedString.erase(nonModifiedString.getSize() - 1);
							}
						}
						else
						{
							nonModifiedString.erase(nonModifiedString.getSize() - 1);
						}
					
						sf::Font font = *gT().getFont();
						ssf::Button::setString(
							ready_text(nonModifiedString, getSize().x - ssf::Button::gR().getOutlineThickness() - 10, gT().getCharacterSize(), font)
						);
						
						nbReturn=0;
						if (nonModifiedString.getSize() > 0 && nonModifiedString[nonModifiedString.getSize() - 1] == '\n') isEraseReturn = true;
						
						update();
						isEraseReturn= false;
						return true;
					
					}
				}
				else if (e.text.unicode == 13) //retour a la ligne
				{
					if (m_text.getGlobalBounds().height + (nbReturn + 1) * (m_text.getFont()->getLineSpacing(m_text.getCharacterSize())) + m_cursor.getSize().y < Rectangle::getSize().y - 2.0 * (ssf::Button::gR().getOutlineThickness() - 2) - 10)
					{
						nonModifiedString += '\n';
						nbReturn++;
						update();
					}
					
				}
				else
				{
					nbReturn = 0;
					sf::Uint32 c = e.text.unicode;

					nonModifiedString += c;

					sf::Font font = *gT().getFont();
					ssf::Button::setString(
						ready_text(nonModifiedString, getSize().x - ssf::Button::gR().getOutlineThickness() - 10, gT().getCharacterSize(), font)
					);

					if (gT().getGlobalBounds().height +  m_cursor.getSize().y > Rectangle::getSize().y - 2.0 * (ssf::Button::gR().getOutlineThickness() - 2) - 10)
					{
						nonModifiedString.erase(nonModifiedString.getSize() - 1);
						ssf::Button::setString(
							ready_text(nonModifiedString, getSize().x - ssf::Button::gR().getOutlineThickness() - 10, gT().getCharacterSize(), font)
						);
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

	void TextInput::setString(sf::String str)
	{
		nonModifiedString = str;
		sf::Font font = *gT().getFont();
		ssf::Button::setString(
			ready_text(nonModifiedString, getSize().x - ssf::Button::gR().getOutlineThickness() - 10, gT().getCharacterSize(), font)
		);
		update();
	}

	sf::String TextInput::getString()
	{
		return nonModifiedString;
	}

	void TextInput::setFocus(bool value)
	{
		m_haveFocus = value;
		update();
	}


	void TextInput::setPosition(float x, float y)
	{
		Rectangle::setPosition(x, y);
		updatePosText();
	}


	void TextInput::update()
	{
		Rectangle::update();
		updatePosText();
	}

	void TextInput::setOutlineThickness(float v)
	{
		Rectangle::setOutlineThickness(v);
		updatePosText();
	}

	void TextInput::updatePosText()
	{
		if (m_haveFocus) updatePosCursor();
		sf::FloatRect rect = m_rectangle.getGlobalBounds();
		sf::FloatRect textRect = m_text.getGlobalBounds();
		Text::setPosition(rect.left + ssf::Button::gR().getOutlineThickness() + 2, rect.top + ssf::Button::gR().getOutlineThickness() + 2);
		Text::update();
	}

	void TextInput::updatePosCursor()
	{
		if (nbReturn > 0 || isEraseReturn)
		{
			std::cout<<"aaa : " << nbReturn <<std::endl;
			sf::FloatRect boundText = m_text.getGlobalBounds();
			if (boundText.height == 0)
			{
				m_cursor.setPosition(boundText.left,
					boundText.top + (nbReturn) * (m_text.getFont()->getLineSpacing(m_text.getCharacterSize())) +  0.2 *  m_text.getCharacterSize() );
			}
			else
			{
				m_cursor.setPosition(boundText.left,
					boundText.top + boundText.height + (nbReturn - 1) * (m_text.getFont()->getLineSpacing(m_text.getCharacterSize())) +  0.2 *  m_text.getCharacterSize() );
			}
			
		}
		else
		{
			std::cout << "bbb" <<std::endl;
			sf::FloatRect boundText = m_text.getGlobalBounds();
			sf::FloatRect boundRect = m_rectangle.getGlobalBounds();
			int lcharI = m_text.getString().getSize()-1;
			sf::Vector2f posChar = m_text.findCharacterPos(lcharI);
			sf::Font font = *gT().getFont();
			sf::String str = m_text.getString();
			m_cursor.setPosition(posChar.x + give_letter_size(str[lcharI],font, m_text.getCharacterSize() + 2.0),
				posChar.y + 0.2 *  m_text.getCharacterSize() );
		}
	}


	int TextInput::give_letter_size(sf::Uint32 &letter, sf::Font &font, int font_size)
	{
		return font.getGlyph(letter, font_size, false).advance;
	}

	sf::String TextInput::ready_text(sf::String text, int width, int font_size, sf::Font &font)
	{
		int s_width = 0;
		int last_word = 0;
		for(int i = 0; i < text.getSize(); i++)
		{
			
			if(s_width < width)
			{
				if (text[i] == '\n') s_width = 0;
				else s_width += give_letter_size(text[i], font, font_size);

			}
			if(s_width >= width)
			{
				if (last_word == 0 || text[last_word]=='\n')
				{
					text.insert(i, '\n');
					last_word = i;
					s_width = 0;
				}
				else
				{
					text.replace(last_word, 1, "\n");
					i = last_word;
					s_width = 0;
				}
			}


			if(text[i] == ' ')
				last_word = i;
		}
		return text;
	}


}