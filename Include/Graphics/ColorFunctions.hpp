#pragma once
#include <SFML/Graphics/Color.hpp>
#include "Math/MathFunctions.h"
#include <iostream>
#include <string>

namespace O
{
    namespace graphics
    {
        namespace color
        {
            sf::Color liearGradiant(const sf::Color& from, const sf::Color& to, const float& pourcent);
            sf::Color multiply(const sf::Color& coul, const float& product );
        } // namespace color

         sf::Color Color(std::string const& hex);
        
    } // namespace graphics
    
} // namespace O
