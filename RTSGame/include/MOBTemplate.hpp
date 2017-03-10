#pragma once

#include <SFML/Graphics.hpp>

// An 8 frame animation loop.
struct Animation {
	float stepTime;         // Time between animation steps.
	sf::Texture frames[8];  // Frames of the animation.
};

// Unit types. Staggered for bitmask.
enum UnitType {
	AIR = 1,
	INFANTRY = 2,
	LAND = 4
};

struct UnitStats {
	float MaxHealth;
	float MovementSpeed;

	float SightDistance;

	UnitType type;
};

struct Attack {
	uint8_t targetMask;
	float range;
	float damage;
	float cycleTime;

	Animation anim;
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

	UnitStats DefaultStats;

	std::vector<Attack> attacks;

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