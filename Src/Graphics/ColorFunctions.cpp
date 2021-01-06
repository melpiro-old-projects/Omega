#include "Graphics/ColorFunctions.hpp"
namespace O
{
    namespace graphics
    {
        namespace color
        {
            sf::Color liearGradiant(const sf::Color& from, const sf::Color& to, const float& pourcent)
            {
                return sf::Color(
                    (float)from.r * (100.f - pourcent) / 100.f + (float)to.r * pourcent / 100.f,
                    (float)from.g * (100.f - pourcent) / 100.f + (float)to.g * pourcent / 100.f,
                    (float)from.b * (100.f - pourcent) / 100.f + (float)to.b * pourcent / 100.f,
                    (float)from.a * (100.f - pourcent) / 100.f + (float)to.a * pourcent / 100.f
                );
            }

        } // namespace color
        
    } // namespace graphics
    
} // namespace O