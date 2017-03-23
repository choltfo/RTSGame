#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <math.h>
#include <stdint.h>

#include "UnitTypes.hpp"
#include "Game.hpp"

class Projectile {
	
	sf::Vector2f position;
	sf::Vector2f target;		// Point to travel to before exploding.

	float splashRadius;			// Radius of circle over which to project damage.
	float peakDamage;			// Damage to be done at d=0

	float speed;				// Speed at which to travel towards target.

	Animation travelAnim;		// Animation to draw while travelling.

	sf::Clock lifeTime;

public:
	uint8_t update(Game&game);	// Run this each game step

	uint8_t render(sf::RenderWindow& window); // Run this every render step. No side effects.

	uint8_t arrive(Game&game);	// Called

	sf::Texture & currentTexture();

};