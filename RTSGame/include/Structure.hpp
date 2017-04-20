
#pragma once

#include <SFML/Graphics.hpp>
#include <deque>
#include <iostream>

#include "TileSystem.hpp"
#include "Production.hpp"
#include "Game.hpp"
#include "PlayerTypes.hpp"

#define STRU_NONE 0b00000000
#define STRU_UNIT 0b00000001
#define STRU_STRU 0b00000010
#define STRU_SUWE 0b00000100
#define STRU_UPGR 0b00001000

class StructureReference {
public:
    std::vector<ProductionOption> productionOptions;

	std::string name;

    // SOOOO much easier than MOBs.
    sf::Texture texture;
	
    sf::Vector2u size;

	// Icon should be 94 * 64
	sf::Texture icon;

	float maxHitpoints;

    int32_t viewDist;

	void loadSR(std::string, std::string, std::vector<MOBTemplate>&);
};

class Structure {
public:
    Structure();
    Structure(StructureReference*, sf::Vector2i, TileSystem&gamemap);
    void render(sf::RenderWindow & window);

    void updateFOW(TileSystem&gamemap);

	PlayerID owner;

	float HP;

    uint8_t update(Game&game);

    sf::Vector2i position;

    std::deque<ProductionItem> productionQueue;

    StructureReference* base;
};


