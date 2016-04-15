
#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <math.h>
#include <stdint.h>
#include <iostream>

enum Direction {
    DOWN = 0,
    DOWNRIGHT = 1,
    RIGHT = 2,
    UPRIGHT = 3,
    UP = 4,
    UPLEFT = 5,
    LEFT = 6,
    DOWNLEFT = 7
};

// An 8 frame animation loop.
struct Animation {
    float stepTime;         // Time between animation steps.
    sf::Texture frames[8];  // Frames of the animation.
};

// This is a bad design. Sprites are not designed to work in reams.
// That said, there will only be one per unit. Perhaps it wouldn't be too bad?
// It would only use a couple hundred kilobytes of VRAM storing all the textures (assuming 32x32px, 8 frames, and 15 animations),
//  but the draw calls would be all over the place. Sorting the MOBS by static texture MIGHT be worthwhile, but it's unlikely.
class MOBTemplate {
public:
    // TODO: Actions/attacks/stats
    // TODO: Implement all of this!

    std::string name;

    uint8_t load(std::string fileName);

    // Animation/rendering
    sf::Texture staticTextures[8];// Static, standing around, textures for all directions.
    Animation moveLoops[8];         // Movement loops for all directions.
    Animation attackLoops[8];       // Attack loops for all directions.
};

class MobileObject {
public:
    // Current position in WORLD COORDINATES
    sf::Vector2f position;
    Direction direction;

    // Current frame in current animation.
    // Reset when animation is changed, incremented when a new frame is drawn,
    //  and wraps back to 0 after 7.
    uint8_t animationFrame;

    // Template from which to take animations, etc.
    MOBTemplate * base;
    uint64_t baseIndex;

    // Draws this MOB in a renderwindow. (rendertarget?)
    void render(sf::RenderWindow & window, MOBTemplate & dammit);
    sf::Texture & currentTexture(MOBTemplate & dammit);

    // Performs pertinent operations once per update loop.
    // e.g: Cooldowns, movements, AI ticks.
    // Should be frame rate independent, as it may run in a seperate thread.
    uint8_t update(sf::Clock);
};


