
#include "MobileObject.hpp"

uint8_t MobileObject::render(sf::RenderWindow & window, MOBTemplate & dammit) {
    sf::Sprite currentSprite(currentTexture(dammit));
    currentSprite.setPosition(position);

    std::cout << dammit.name << '\n';

    window.draw(currentSprite);
};


// Determines the sprite to render with.
// Reflects all animation, actions, idle states, etc.

sf::Texture & MobileObject::currentTexture (MOBTemplate & dammit) {
    // TODO: Figure this out. Harder than expected.
    // Also, this is not what tonight for.

    //dammit.staticTextures[Direction::DOWN];
    return dammit.testStatic;
};
