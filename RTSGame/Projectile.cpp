
#include "Projectile.hpp"

#include <math.h>

uint8_t Projectile::update (Game&game) {
	sf::Vector2f delta = target - position;
	position = position + scalar(normalize(delta), std::min(speed, getMagnitude(delta)));

	std::cout << position.x << ", " << position.y << std::endl;

	dir = normalize(delta);

	if (getMagnitude(delta) < speed) {
		// We're not getting any closer. Boom time.
		return arrive(game);
	}

	return 0;
}

uint8_t Projectile::arrive(Game&game) {

	return 1; // What should this even return?
	
}


uint8_t Projectile::render (sf::RenderWindow& window) {
	sf::Sprite currentSprite(currentTexture());
	currentSprite.setPosition(position + sf::Vector2f(-8, -8));

	currentSprite.setRotation(atan2(dir.y,dir.x) /PI * 180.0);

	window.draw(currentSprite);

	return 0;
}

Projectile::Projectile(Weapon atk, sf::Vector2f loc, sf::Vector2f tar) {
	position = loc;
	target = tar;

	speed = atk.speed;
	// splashRadius = ???
	peakDamage = atk.damage;
	// travelAnim = ???
	texture = atk.texture;
}

sf::Texture & Projectile::currentTexture() {
	// TODO: Figure this out. Harder than expected.

	return texture;

	//return travelAnim.frames[(int)(lifeTime.getElapsedTime().asSeconds() / travelAnim.stepTime)%ANIM_LENGTH];
};