#pragma once


#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#define ANIM_LENGTH 8


typedef uint8_t TargetMask;

// An ANIM_LENGTH frame animation loop.
struct Animation {
	float stepTime;         // Time between animation steps.
	sf::Texture frames[ANIM_LENGTH];  // Frames of the animation.
};

// Unit types. Staggered for bitmask.
enum UnitType {
	UT_AIR = 1,
	UT_INFANTRY = 2,
	UT_LAND = 4,
	UT_TERRAIN = 8,
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