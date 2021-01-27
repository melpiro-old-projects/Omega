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
            sf::Color multiply(const sf::Color& coul, const float& product )
            {
                return sf::Color(
                    (float)coul.r * product,
                    (float)coul.g * product,
                    (float)coul.b * product,
                    (float)coul.a
                );
            }


        } // namespace color

        sf::Color Color(std::string const& hex){
            if (hex[0] == '#') 
            {
                if (hex.size() == 7)
                {
                    std::string c1;
                    c1 += hex[1];
                    c1 += hex[2];
                    std::string c2;
                    c2 += hex[3];
                    c2 += hex[4];
                    std::string c3;
                    c3 += hex[5];
                    c3 += hex[6];
                    return sf::Color(
                        O::math::hex_to_decimal(c1),
                        O::math::hex_to_decimal(c2),
                        O::math::hex_to_decimal(c3)
                    );
                }
                else if (hex.size() == 9)
                {
                    std::string c1;
                    c1 += hex[1];
                    c1 += hex[2];
                    std::string c2;
                    c2 += hex[3];
                    c2 += hex[4];
                    std::string c3;
                    c3 += hex[5];
                    c3 += hex[6];
                    std::string c4;
                    c4 += hex[7];
                    c4 += hex[8];
                    return sf::Color(
                        O::math::hex_to_decimal(c1),
                        O::math::hex_to_decimal(c2),
                        O::math::hex_to_decimal(c3),
                        O::math::hex_to_decimal(c4)
                    );
                }
            }
            if (hex.size() == 7)
            {
                std::string c1;
                c1 += hex[0];
                c1 += hex[1];
                std::string c2;
                c2 += hex[2];
                c2 += hex[3];
                std::string c3;
                c3 += hex[4];
                c3 += hex[5];
                return sf::Color(
                    O::math::hex_to_decimal(c1),
                    O::math::hex_to_decimal(c2),
                    O::math::hex_to_decimal(c3)
                );
            }
            else if (hex.size() == 9)
            {
                std::string c1;
                c1 += hex[0];
                c1 += hex[1];
                std::string c2;
                c2 += hex[2];
                c2 += hex[3];
                std::string c3;
                c3 += hex[4];
                c3 += hex[5];
                std::string c4;
                c4 += hex[6];
                c4 += hex[7];
                return sf::Color(
                    O::math::hex_to_decimal(c1),
                    O::math::hex_to_decimal(c2),
                    O::math::hex_to_decimal(c3),
                    O::math::hex_to_decimal(c4)
                );
            }
            return sf::Color::Transparent;
        }
        
    } // namespace graphics
    
} // namespace O