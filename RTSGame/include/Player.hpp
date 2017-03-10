#pragma once

#include <string>
#include <vector>
#include <stdint.h>
#include <algorithm>
#include <math.h>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Structure.hpp"
#include "MobileObject.hpp"
#include "TileSystem.hpp"
#include "GlobalState.hpp"
#include "Minimap.hpp"

enum InterfaceMode {
    imIDLE,               // User is idle. Can select structure/MOB.
    imPLACING,            // User is placing an object.
    imCOMMAND             // User is commanding structure/MOB.

    // There will be more. But not now!
};

enum SelectionType {
    stNONE,
    stUNITS,
    stSTRUCTURES
};

class Player {
public:
    std::string name;
    sf::Color colour;

    InterfaceMode interfaceMode;

    // This players team number.
    // 0 signifies non-combatant (Gaia, world, civillian, or what have you.)
    uint8_t team;

    // Whether this player is the local player, i.e, controllable via the UI.
    // All other players must be controlled via networking (yikes) or AI (bigger yikes)
    bool isLocal;

    // collection of all MOBs this player owns
    std::vector<MobileObject> MOBs;
    std::vector<Structure> structures;

    SelectionType selectionType;
    // The indexes in MOBs of all the units selected by this  player.
    std::vector<uint32_t> selectedUnits;

    sf::Image fog;

    Player() {}
    Player(std::string n, sf::Color c) {
        name = n;
        colour = c;
    }

    void render(
                sf::RenderWindow&,
                std::vector<MOBTemplate>&
                );

    void GUI(sf::RenderWindow&, GlobalState curIn);

    uint8_t update(sf::Clock, TileSystem&, std::vector<MOBTemplate>, Minimap&);

};
