#include "maths.hpp"
#include <cmath> 

sf::Vector2f maths::round(const sf::Vector2f vector)
{
    return sf::Vector2f{std::round(vector.x), std::round(vector.y)};
}