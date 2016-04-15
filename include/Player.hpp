#pragma once

#include <string>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "MobileObject.hpp"

class Player {
public:
    std::string name;
    sf::Color colour;

    Player() {}
    Player(std::string n, sf::Color c) {
        name = n;
        colour = c;
    };


    std::vector<MobileObject> MOBs;

};
