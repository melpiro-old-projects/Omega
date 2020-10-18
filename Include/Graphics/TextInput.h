#pragma once

#include "Input.h"
#include <bitset>
#include <math.h>
namespace ssf {
	class TextInput : public ssf::Input
	{
	public:
		TextInput();
		TextInput(sf::RenderWindow* window, float x, float y, float sizeX, float sizeY, float posRx, float posRy, bool centered = false);
		TextInput(sf::RenderWindow* window, std::string font, float x, float y, float sizeX, float sizeY, float posRx, float posRy, bool centered = false);
		TextInput(sf::RenderWindow* window, float x, float y, float sizeX, float sizeY, bool centered = false);

		bool event(sf::Event e);

		void setPosition(float x, float y);
		void move(float x, float y);
		void update();

		void updatePosText();
		void updatePosCursor();

		void setOutlineThickness(float v);
		void setFocus(bool value);
		void setString(sf::String str);
		sf::String getString();

		

	protected:
		sf::String nonModifiedString;
		std::vector<int> indexAddedReturn;
		int lastIndexAddedReturnSize = 0;
		bool increaced = false;
		bool decreaced = false;

		int nbReturn = 0;
		bool isEraseReturn = false;
		
		void updatePosCursor(sf::Vector2f clic);
		void addChar(sf::Uint32 c);
		void removeChar();

	private:
		static int give_letter_size(const sf::Uint32 &letter, const sf::Font &font,const int& font_size);
		sf::String ready_text(sf::String text, int width, const int& font_size, const sf::Font &font);
		int getCursorPosInNonModifiedString();
	};
}


