#pragma once

#include <SFML/Graphics.hpp>

#include "UnitTypes.hpp"

// This is a bad design. Sprites are not designed to work in reams.
// That said, there will only be one per unit. Perhaps it wouldn't be too bad?
// It would only use a couple hundred kilobytes of VRAM storing all the textures (assuming 32x32px, 8 frames, and 15 animations),
//  but the draw calls would be all over the place. Sorting the MOBS by static texture MIGHT be worthwhile, but it's unlikely.
class MOBTemplate {
public:
	// TODO: Actions/attacks/stats
	// TODO: Implement all of this!

	MOBTemplate();

	int8_t loadFromFile(std::string, std::vector<Attack>&);


	std::string name;
	UnitStats DefaultStats;
	std::vector<Attack> attacks;

	// Initialized to 1.0 in default constructor
	float resistances[N_WEAPONCLASS];

	// Animation/rendering
	sf::Texture staticTextures[8];// Static, standing around, textures for all directions.
	Animation moveLoops[8];         // Movement loops for all directions.
	Animation attackLoops[8];       // Attack loops for all directions.

	uint32_t viewDist;
};

enum CommandType {
	NONE,
	MOVE,		// Proceed towards a point.
	ATKUNI,		// Attack unit.
	ATKSTR,		// Attack structure.
	ATKTER,		// Attack terrain.
	HARVEST,
	SPECIAL,	// Unimplemented until further notice.
};
