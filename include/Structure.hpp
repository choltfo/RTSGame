
#pragma once

#include <SFML/Graphics.hpp>
#include <deque>
#include <iostream>

#include "Production.hpp"

class StructureReference {
public:
    // TODO: Add production queueueueueueues.
    std::vector<ProductionOption> productionOptions;

    // SOOOO much easier than MOBs.
    sf::Texture texture;
    sf::Vector2u size;
};

class Structure {
public:
    Structure();
    Structure(StructureReference*, sf::Vector2u);
    void render(sf::RenderWindow & window);

    void update();

    sf::Vector2u position;

    std::deque<ProductionItem> productionQueue;

    StructureReference* base;
};


