
#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <math.h>
#include <stdint.h>
#include <iostream>
#include <deque>

#include "Structure.hpp"
#include "VectorMath.hpp"
#include "Direction.hpp"
#include "Minimap.hpp"
#include "MOBTemplate.hpp"
#include "UnitTypes.hpp"
#include "Game.hpp"
#include "PlayerTypes.hpp"

class MobileObject;

// Yes these should be individual types. But I'm doing this quick and dirty.
struct Command {
    CommandType type;

    sf::Vector2f point;     // For movement and terrain attacks.
    MobileObject * target;  // For attacks.
    Structure * statTarget; // Stationary target to blow up.

	sf::Vector2f targetLoc();
};

class MobileObject {
	sf::Clock shotTimer;
public:
    // Current position in WORLD COORDINATES
    sf::Vector2f position;
    Direction dir;

	float hitpoints;

	bool alive = true;

	PlayerID owner;

    // Current frame in current animation.
    // Reset when animation is changed, incremented when a new frame is drawn,
    //  and wraps back to 0 after 7.
    uint8_t animationFrame;

    //UnitStats stats;

	void InitializeFoV(TileSystem&gamemap);
    bool updateFOW(TileSystem&, sf::Vector2f);


    // Commands.
    Command curCommand;
    std::deque<Command> commands;

    // Template from which to take animations, etc.
    MOBTemplate* base;


	MobileObject();
	MobileObject(MOBTemplate*, sf::Vector2f pos, PlayerID, Game&);

    // Draws this MOB in a renderwindow. (rendertarget?)
    void render(sf::RenderWindow&);
    sf::Texture& currentTexture();

    // Performs pertinent operations once per update loop.
    // e.g: Cooldowns, movements, AI ticks.
    // Should be frame rate independent, as it may run in a seperate thread.
    uint8_t update(sf::Clock, Game*game, Minimap&);

	void cleanup(Game&game);

	// Shoot if possible.
	// Returns whether shots were fired.
	bool engageTarget (Game*game);

	bool damage(float damage, WeaponClass wClass);

	sf::Vector2f targetLoc();
	int bestWeapon();
};


