
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
#include "../Minimap.hpp"

// An 8 frame animation loop.
struct Animation {
    float stepTime;         // Time between animation steps.
    sf::Texture frames[8];  // Frames of the animation.
};

// Unit types. Staggered for bitmask.
enum UnitType {
    AIR,
    INFANTRY,
    LAND
};

struct UnitStats {
    float MaxHealth;
    float MovementSpeed;

    float AttackDamage;
    float AttackDelay;

    float SightDistance;

    uint8_t TargetMask;

    UnitType type;

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

    UnitStats stats;

    uint8_t load(std::string);

    // Animation/rendering
    sf::Texture staticTextures[8];// Static, standing around, textures for all directions.
    Animation moveLoops[8];         // Movement loops for all directions.
    Animation attackLoops[8];       // Attack loops for all directions.

    uint32_t viewDist = 5;  //I selected a default value, it should not be used - clone
};

enum CommandType {
    NONE,
    MOVE,       // Proceed towards a point.
    ATKUNI,     // Attack unit.
    ATKSTR,     // Attack structure.
    ATKTER,     // Attack terrain.
    HARVEST,
    SPECIAL     // Unimplemented until further notice.
};

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
    size_t baseIndex;

    // Draws this MOB in a renderwindow. (rendertarget?)
    void render(sf::RenderWindow&, MOBTemplate&);
    sf::Texture& currentTexture(MOBTemplate&);

    // Performs pertinent operations once per update loop.
    // e.g: Cooldowns, movements, AI ticks.
    // Should be frame rate independent, as it may run in a seperate thread.
    uint8_t update(sf::Clock, TileSystem&, Minimap&);
};


