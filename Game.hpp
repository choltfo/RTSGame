
#pragma once

#include <stdint.h>
#include <vector>

#include "TileSystem.hpp"
#include "MobileObject.hpp"

/// Represents a game, consisting of a map,
///  players, and whatever other data is needed.
/// To be instantiated by the main menu and called inside whatever loop
///  that consists of. Will take RenderWindow for a single render function that
///  will pass it down to all sub objects.

class Game {
public:
    TileSystem map;
    std::vector<MobileObject> MOBs;

    std::vector<MOBTemplate> MOBTemplates;

    uint8_t loadMOBTemplate(std::string name, std::string filesuffix);

    uint8_t render(sf::RenderWindow& window);
    uint8_t update();
};
