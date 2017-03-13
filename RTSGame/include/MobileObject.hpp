
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

class MobileObject;

// Yes these should be individual types. But I'm doing this quick and dirty.
struct Command {
    CommandType type;

    sf::Vector2f point;     // For movement and terrain attacks.
    MobileObject * target;  // For attacks.
    Structure * statTarget; // Stationary target to blow up.
    int viewDist = 5;  //I selected a default value, it should not be used - clone
};

class MobileObject {
public:
    // Current position in WORLD COORDINATES
    sf::Vector2f position;
    Direction dir;

    // Current frame in current animation.
    // Reset when animation is changed, incremented when a new frame is drawn,
    //  and wraps back to 0 after 7.
    uint8_t animationFrame;

    UnitStats stats;


    bool updateFOW(TileSystem&gamemap);


    // Commands.
    Command curCommand;
    std::deque<Command> commands;

    // Template from which to take animations, etc.
    MOBTemplate* base;


	MobileObject();
	MobileObject(MOBTemplate*, sf::Vector2f pos);

    // Draws this MOB in a renderwindow. (rendertarget?)
    void render(sf::RenderWindow&);
    sf::Texture& currentTexture();

    // Performs pertinent operations once per update loop.
    // e.g: Cooldowns, movements, AI ticks.
    // Should be frame rate independent, as it may run in a seperate thread.
    uint8_t update(sf::Clock, TileSystem&, Minimap&);
};


