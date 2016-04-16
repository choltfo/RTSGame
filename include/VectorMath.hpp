
#pragma once
#include <SFML/System.hpp>

// quick and dirty 2D-vector math library, because SFML doesn't have one.

double getSquareMagnitude (sf::Vector2f a);
double getMagnitude (sf::Vector2f a);

double dotProduct (sf::Vector2f a, sf::Vector2f b);
