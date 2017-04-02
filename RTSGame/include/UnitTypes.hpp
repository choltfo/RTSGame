#pragma once


#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>

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

#define N_WEAPONCLASS 9
enum WeaponClass {
	WC_UNKNOWN,		// There's an error in the file
	WC_Melee,		// Punching
	WC_Slashing,	// Knives, stabby things
	WC_Grenade,		// Lands places and explodes
	WC_Smallarms,	// Small bullets (9mm, 5.56, .45)
	WC_Heavyrifle,	// Fairly large bullets (7.62, .308, .50)
	WC_Cannon,		// Annihlates one thing at a time (Kaboom. Kaboom. Kaboom.)
	WC_AutoCannon,	// Rapidly blows things up (Kaboomboomboomboomboom)
	WC_Missile,		// Flies slowly, hits what you point it at.
};

WeaponClass weaponClass(std::string string);

struct Attack {
	std::string name;
	uint8_t targetMask;
	float range;
	float damage;
	float cycleTime;
	
	Animation anim;
};