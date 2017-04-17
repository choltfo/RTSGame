
#include "Projectile.hpp"

#include <math.h>

uint8_t Projectile::update (Game&game) {
	sf::Vector2f delta = target - position;
	// TODO: Normalize speed to framerate (*deltaT sort of thing.)
	position = position + scalar(normalize(delta), std::min(source->speed, getMagnitude(delta)));

	std::cout << position.x << ", " << position.y << std::endl;

	dir = normalize(delta);

	if (getMagnitude(delta) < source->speed) {
		// We're not getting any closer. Boom time.
		position = target;
		return arrive(game);
	}

	return 0;
}

uint8_t Projectile::arrive(Game&game) {
	game.effects[0].add(position,rand()/(float)RAND_MAX * 360.0);
	std::cout << "Exploding!" << std::endl;
	for (int i = 0; i < game.MOBs.size(); ++i) {
		sf::Vector2f delta = game.MOBs[i]->position - position;
		float distsquare = getSquareMagnitude(delta);

		// Boom, baby!
		if (distsquare < source->splashRadius*source->splashRadius) {
			float baseDamage = source->damage * ((source->splashRadius - std::sqrtf(distsquare)) / source->splashRadius);
			game.MOBs[i]->damage(baseDamage,source->wClass);
		}
		
	}

	return 1; // What should this even return?
}


uint8_t Projectile::render (sf::RenderWindow& window) {
	sf::Sprite currentSprite(currentTexture());
	currentSprite.setOrigin(texture.getSize().x/2, texture.getSize().y / 2);
	currentSprite.setPosition(position);

	currentSprite.setRotation(atan2(dir.y,dir.x) /PI * 180.0);

	window.draw(currentSprite);

	return 0;
}

Projectile::Projectile(Weapon&atk, sf::Vector2f loc, sf::Vector2f tar) {
	position = loc;
	target = tar;

	source = &atk;
}

sf::Texture & Projectile::currentTexture() {
	// TODO: Figure this out. Harder than expected.

	return texture;

	//return travelAnim.frames[(int)(lifeTime.getElapsedTime().asSeconds() / travelAnim.stepTime)%ANIM_LENGTH];
};