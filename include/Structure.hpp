
#pragma once

#include <SFML/Graphics.hpp>

class StructureReference {
public:
    // TODO: Add production queueueueueueues.
    // std::vector<ProductionOption> ProductionOptions;

    // SOOOO much easier than MOBs.
    sf::Texture texture;
    sf::Vector2u size;
};

class Structure {
public:
    Structure();
    Structure(StructureReference*, sf::Vector2u);
    void render(sf::RenderWindow & window);

    sf::Vector2u position;

    //std::vector<ProductionQueue> ProductionQueue;

    StructureReference* base;
};


