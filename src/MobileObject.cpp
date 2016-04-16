
#include "MobileObject.hpp"

void MobileObject::render(sf::RenderWindow& window, MOBTemplate& temp) {
    sf::Sprite currentSprite(currentTexture(temp));
    currentSprite.setPosition(position + sf::Vector2f(-32,-32));

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

sf::Texture & MobileObject::currentTexture (MOBTemplate& temp) {
    // TODO: Figure this out. Harder than expected.
    // Also, this is not what tonight for.

    return temp.staticTextures[direction];
};
