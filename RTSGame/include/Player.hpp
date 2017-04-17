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
#include "PlayerTypes.hpp"
#include "Game.hpp"

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


    PlayerID me;

    // Whether this player is the local player, i.e, controllable via the UI.
    // All other players must be controlled via networking (yikes) or AI (bigger yikes)
    bool isLocal;

    SelectionType selectionType;
    // The indexes in MOBs of all the units selected by this  player.
    std::vector<uint32_t> selectedUnits;
	std::vector<MobileObject*> selectedMOBs;

    sf::Image fog;

    Player() {}
    Player(std::string n, sf::Color c) {
        name = n;
        colour = c;
    }

    void render(
                sf::RenderWindow&,
				Game & game
                );

    void GUI(sf::RenderWindow&, UIState curIn, Game & game);

	void handleLMB(sf::RenderWindow&, UIState curIn, Game & game, sf::Vector2i mousePos);
	void handleRMB(sf::RenderWindow&, UIState curIn, Game & game, sf::Vector2i mousePos);

	uint8_t update(sf::Clock gameClock, Game & game, Minimap & minimap);

};
