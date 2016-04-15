#pragma once

#include <string>
#include <vector>
#include <stdint.h>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "MobileObject.hpp"
#include "TileSystem.hpp"

class Player {
public:
    std::string name;
    sf::Color colour;

    // collection of all MOBs this player owns
    std::vector<MobileObject> MOBs;

    sf::Image fog;

    Player() {}
    Player(std::string n, sf::Color c) {
        name = n;
        colour = c;
    }

    void render(sf::RenderWindow&);
    uint8_t update(sf::Clock);
};
