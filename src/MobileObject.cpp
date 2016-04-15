
#include "MobileObject.hpp"

void MobileObject::render(sf::RenderWindow& window, MOBTemplate& dammit) {
    sf::Sprite currentSprite(currentTexture(dammit));
    currentSprite.setPosition(position);

    window.draw(currentSprite);
};

// Update this MOB.
// To be overridden as necessary.
uint8_t MobileObject::update(sf::Clock gameClock) {
    direction = Direction(int(floor(gameClock.getElapsedTime().asSeconds()/2)) % 8);
    return 0;
};

// Determines the sprite to render with.
// Reflects all animation, actions, idle states, etc.

sf::Texture & MobileObject::currentTexture (MOBTemplate& dammit) {
    // TODO: Figure this out. Harder than expected.
    // Also, this is not what tonight for.

    return dammit.staticTextures[direction];
};
