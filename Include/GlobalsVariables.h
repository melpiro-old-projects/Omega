#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "EncodeFunction.h"
#include "StaticValues.h"
#include "FileFunctions.h"

namespace GLOBAL 
{


	extern std::map<std::string,sf::Font> GLOBAL_FONT;

	extern std::vector<sf::String> ALL_TEXTS;
	extern std::vector<std::string> PROTECTED_TEXTS;

}


