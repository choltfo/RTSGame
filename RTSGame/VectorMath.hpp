
#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <cmath>

#include "Direction.hpp"

// sqrt(2)/2, sin(45deg), sin(pi/4)
#define R2o2 0.707106781
#define PI 3.14159265
#define sin1pi8 0.382683432
#define cos1pi8 0.923879532

// quick and dirty 2D-vector math library, because SFML doesn't have one.

float getSquareMagnitude (sf::Vector2f a);
float getMagnitude (sf::Vector2f a);

float dotProduct (sf::Vector2f a, sf::Vector2f b);

/// Returns input/|input|
sf::Vector2f normalize(sf::Vector2f);

sf::Vector2f scalar(sf::Vector2f, float);

// Gives a direction as an 8th full rotation.
Direction eighth(sf::Vector2f);
