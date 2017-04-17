#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>

#include "UnitTypes.hpp"

class Weapon {
public:
	std::string name;	// Human friendly name
	std::string index;	// Machine friendly name
	uint8_t targetMask;
	float range;
	float damage;
	float cycleTimeS;	// In seconds
	float speed;
	float splashRadius = 16;

	WeaponClass wClass = WeaponClass::WC_UNKNOWN;

	sf::Texture texture;

	Animation anim;

	Weapon(std::string filePath);
};

WeaponClass getWeaponClassByName(std::string);