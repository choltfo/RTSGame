
#include "Projectile.hpp"

uint8_t Projectile::update (Game&game) {
	sf::Vector2f delta = target - position;
	position = position + scalar(normalize(delta), std::min(speed, getMagnitude(delta)));

	if (getMagnitude(delta) < speed) {
		// We're not getting any closer. Boom time.
		arrive(game);
	}

	return 0;
}

uint8_t Projectile::arrive(Game&game) {

	return 0; // What should this even return?
}


uint8_t Projectile::render (sf::RenderWindow& window) {
	sf::Sprite currentSprite(currentTexture());
	currentSprite.setPosition(position + sf::Vector2f(-32, -32));

	return 0;
}

sf::Texture & Projectile::currentTexture() {
	// TODO: Figure this out. Harder than expected.
	// Also, this is not what tonight for.

	return travelAnim.frames[(int)(lifeTime.getElapsedTime().asSeconds() / travelAnim.stepTime)%ANIM_LENGTH];
};