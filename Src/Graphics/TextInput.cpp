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
			updatePosCursor(sf::Vector2f(e.mouseButton.x,e.mouseButton.y));
		}
		else if (e.type == sf::Event::MouseButtonReleased)
		{
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				setFocus(false);
			}
		}

		else if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Left)
			{
				if (m_cusorIndex == -1)
				{
					if (m_text.getString().getSize() != 0)
					{
						m_cusorIndex = m_text.getString().getSize() - 1;
					}
				}
				else
				{
					m_cusorIndex --;
					if (m_cusorIndex<0) m_cusorIndex = 0;
				}
				updatePosCursor();
			}
			else if (e.key.code == sf::Keyboard::Right)
			{
				m_cusorIndex++;
				if (m_cusorIndex>m_text.getString().getSize()) m_cusorIndex = m_text.getString().getSize();
				
				updatePosCursor();
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
					removeChar();
				}
				else
				{
					addChar(e.text.unicode);
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
		int nbLine = 0;
		for (size_t i = 0; i < m_cusorIndex; i++)
		{
			if (m_text.getString()[i] == '\n') nbLine++;
		}

		// todo compute the + 5.0
		if (m_text.getString().getSize() == 0)
		{
			m_cursor.setPosition(m_text.findCharacterPos(m_cusorIndex).x,
				m_text.getPosition().y + 5.0
			);
		}
		else if (m_cusorIndex > 0 && m_text.getString()[m_cusorIndex-1] == '\n')
		{
			m_cursor.setPosition(m_text.getPosition().x,
				m_text.getPosition().y + (nbLine) * (m_text.getFont()->getLineSpacing(m_text.getCharacterSize()))  + 5.0
			);
		}
		else if (m_cusorIndex == m_text.getString().getSize())
		{
			m_cursor.setPosition(m_text.findCharacterPos(m_cusorIndex - 1).x + give_letter_size(m_text.getString()[m_cusorIndex - 1],*m_text.getFont(), m_text.getCharacterSize() + 2.0),
				m_text.getPosition().y + (nbLine) * (m_text.getFont()->getLineSpacing(m_text.getCharacterSize()))  + 5.0
			);
		}
		else
		{
			m_cursor.setPosition(m_text.findCharacterPos(m_cusorIndex).x,
				m_text.getPosition().y + (nbLine) * (m_text.getFont()->getLineSpacing(m_text.getCharacterSize()))  + 5.0
			);
		}
	}




	int TextInput::give_letter_size(const sf::Uint32 &letter, const sf::Font &font, const int& font_size)
	{
		return font.getGlyph(letter, font_size, false).advance;
	}

	sf::String TextInput::ready_text(sf::String text, int width,const int& font_size, const sf::Font &font)
	{
		increaced = false;
		decreaced = false;

		indexAddedReturn.clear();
		int s_width = 0;
		int last_word = 0;
		for(int i = 0; i < text.getSize(); i++)
		{
			
			if(s_width < width)
			{
				if (text[i] == '\n') s_width = 0, last_word = 0;
				else s_width += give_letter_size(text[i], font, font_size);

			}
			if(s_width >= width)
			{
				if (last_word == 0)
				{
					text.insert(i, '\n');
					indexAddedReturn.push_back(i);
					last_word = i;
					s_width = 0;
				}
				else
				{
					text.replace(last_word, 1, "\n");
					i = last_word;
					last_word = 0;
					s_width = 0;
				}
			}


			if(text[i] == ' ')
				last_word = i;
		}
		
		if (lastIndexAddedReturnSize > indexAddedReturn.size())
		{
			decreaced = true;
		}
		else if (lastIndexAddedReturnSize < indexAddedReturn.size())
		{
			increaced = true;
		}
		lastIndexAddedReturnSize = indexAddedReturn.size();
		return text;
	}

	void TextInput::addChar(sf::Uint32 c)
	{
		int posCursor = getCursorPosInNonModifiedString();//getCursorPosInNonModifiedString();
		
		std::cout <<"a: "<< posCursor <<"->"<<m_cusorIndex <<std::endl;
		if (c == 13) //retour a la ligne
		{
			// on verifie qu'il est possible d'ajouter le retour a la ligne
			m_text.setString(m_text.getString()+'p'); // on ajoute un p pour se rendre compte de la hauteur du texte réél
			if (m_text.getGlobalBounds().height + m_text.getFont()->getLineSpacing(m_text.getCharacterSize()) < Rectangle::getSize().y - 2.0 * (ssf::Button::gR().getOutlineThickness() - 2))
			{
				m_text.setString(m_text.getString().substring(0, m_text.getString().getSize() - 1));

				nonModifiedString.insert(posCursor,'\n');
				m_cusorIndex++;
				nbReturn++;

				ssf::Button::setString(
					ready_text(nonModifiedString, getSize().x - ssf::Button::gR().getOutlineThickness() - 10, m_text.getCharacterSize(), *m_text.getFont())
				);
			}
			else m_text.setString(m_text.getString().substring(0, m_text.getString().getSize() - 1));
		}
		else
		{
			nbReturn = 0; // il y a pu de retours à la lignes ajoutés consécutivement
			
			sf::String nonModifiedStringCpy = nonModifiedString;
			nonModifiedString.insert(posCursor,c);
			m_cusorIndex++;

			ssf::Button::setString(
				ready_text(nonModifiedString, getSize().x - ssf::Button::gR().getOutlineThickness() - 10, m_text.getCharacterSize(), *m_text.getFont())
			);

			if (increaced)
			{
				m_cusorIndex++;
			}
			

			if (gT().getGlobalBounds().height + m_text.getFont()->getLineSpacing(m_text.getCharacterSize()) > Rectangle::getSize().y - 2.0 * (ssf::Button::gR().getOutlineThickness() - 2))
			{
				// retour arrère
				nonModifiedString = nonModifiedStringCpy;
				m_cusorIndex--;

				ssf::Button::setString(
					ready_text(nonModifiedString, getSize().x - ssf::Button::gR().getOutlineThickness() - 10, m_text.getCharacterSize(), *m_text.getFont())
				);

				if (decreaced)
				{
					m_cusorIndex--;
				}
			}
		}
		update();
		std::cout << nonModifiedString.toAnsiString() <<std::endl;
	}

	
	void TextInput::removeChar()
	{
		int posCursor = getCursorPosInNonModifiedString() - 1;//getCursorPosInNonModifiedString() - 1;
		std::cout <<"d: "<< posCursor <<"->"<<m_cusorIndex <<std::endl;
		if (posCursor >= 0)
		{
			if (nonModifiedString.getSize() > 0)
			{
				nonModifiedString.erase(posCursor);
				m_cusorIndex--;
				
			
				sf::Font font = *gT().getFont();
				ssf::Button::setString(
					ready_text(nonModifiedString, getSize().x - ssf::Button::gR().getOutlineThickness() - 10, gT().getCharacterSize(), font)
				);

				if (decreaced)
				{
					m_cusorIndex--;
				}
					
				nbReturn=0;
				if (nonModifiedString.getSize() > 0 && nonModifiedString[nonModifiedString.getSize() - 1] == '\n') isEraseReturn = true;
				
				
				isEraseReturn= false;
			}
		}
		update();
	}

	void TextInput::updatePosCursor(sf::Vector2f clic)
	{
		// new computation
		sf::String text = m_text.getString();
		sf::Vector2f clicAbsolutePos = clic - m_text.getPosition();
		int line = clicAbsolutePos.y / (m_text.getFont()->getLineSpacing(m_text.getCharacterSize()));
		int index = text.getSize();
		bool find = false;
		int acualLineExplo = 0;
		double minDistance = 1000000000;
		for (size_t i = 0; i < text.getSize(); i++)
		{
			if (acualLineExplo == line)
			{
				double d = clic.x - m_text.findCharacterPos(i).x;
				if (std::abs(d) < minDistance && std::abs(d) < m_text.getCharacterSize())
				{
					minDistance = std::abs(d);
					index = i;
					find = true;
				}
			}
			else if (acualLineExplo > line)
			{
				if (!find)
				{
					index = i - 1;
				}
				break;

			}
			
			if (text[i] == '\n') acualLineExplo++;
		}
		m_cusorIndex = index;
		updatePosCursor();
	}

	int TextInput::getCursorPosInNonModifiedString()
	{
		for (int i = ((int)indexAddedReturn.size()) - 1; i >= 0; i--)
		{
			if (m_cusorIndex >= indexAddedReturn[i]) return m_cusorIndex - (i + 1);
		}
		return m_cusorIndex;
	}
}


