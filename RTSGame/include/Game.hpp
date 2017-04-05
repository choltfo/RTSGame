
#pragma once

#include <stdint.h>
#include <vector>
#include <list>

#include "ClassPredec.hpp"

#include "TileSystem.hpp"
#include "MobileObject.hpp"
#include "Player.hpp"
#include "GlobalState.hpp"
#include "Structure.hpp"
#include "Projectile.hpp"
#include "Effect.hpp"

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
	
	std::vector<Projectile> projectiles;
	
	std::list<MobileObject> MOBs;
	std::list<Structure> structures;
	
	
	EffectHandler effects;
	
    uint8_t loadMOBTemplate(std::string name, std::string filesuffix);
    uint8_t loadStructureReference(std::string name, std::string filesuffix);

    uint8_t render(sf::RenderWindow&);
    uint8_t renderUI(sf::RenderWindow&, UIState curIn);
    uint8_t update(sf::Clock,Minimap&);
};
