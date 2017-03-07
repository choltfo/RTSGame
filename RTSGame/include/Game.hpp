
#pragma once

#include <stdint.h>
#include <vector>

#include "TileSystem.hpp"
#include "MobileObject.hpp"
#include "Player.hpp"
#include "GlobalState.hpp"
#include "Structure.hpp"

/// Represents a game, consisting of a map,
///  players, and whatever other data is needed.
/// To be instantiated by the main menu and called inside whatever loop
///  that consists of. Will take RenderWindow for a single render function that
///  will pass it down to all sub objects.

class Game {
public:
    TileSystem map;

    std::vector<MOBTemplate> MOBTemplates;
    std::vector<StructureReference> structureReferences;

    std::vector<Player> players;

    uint8_t loadMOBTemplate(std::string name, std::string filesuffix);
    uint8_t loadStructureReference(std::string name, std::string filesuffix);

    uint8_t render(sf::RenderWindow&);
    uint8_t renderUI(sf::RenderWindow&, GlobalState curIn);
    uint8_t update(sf::Clock);
};
