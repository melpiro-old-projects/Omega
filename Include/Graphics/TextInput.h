#pragma once

#include "Input.h"
#include <bitset>

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

		int nbReturn = 0;
		bool isEraseReturn = false;

	private:
		static int give_letter_size(sf::Uint32 &letter, sf::Font &font, int font_size);
		static sf::String ready_text(sf::String text, int width, int font_size, sf::Font &font);
		
	};
}


