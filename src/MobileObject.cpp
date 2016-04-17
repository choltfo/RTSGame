
#include "MobileObject.hpp"

void MobileObject::render(sf::RenderWindow& window, MOBTemplate& temp) {
    sf::Sprite currentSprite(currentTexture(temp));
    currentSprite.setPosition(position + sf::Vector2f(-32,-32));

    window.draw(currentSprite);
};

// Update this MOB.
// To be overridden as necessary.
uint8_t MobileObject::update(sf::Clock gameClock) {
    //dir = Direction(int(floor(gameClock.getElapsedTime().asSeconds()/2)) % 8);

    if (!commands.empty()){
        if (curCommand.type == CommandType::NONE) {
            curCommand = commands.front();
            commands.pop();
        }
    }

    if (curCommand.type == CommandType::MOVE) {
        sf::Vector2f delta = curCommand.point - position;
        dir = eighth(delta);

        if (getSquareMagnitude(delta) < 10) {
            curCommand.type = CommandType::NONE;
        }

        // Should this be better? Maybe. Maybe....
        //position = position + scalar(delta, stats.MovementSpeed);
        position = position + scalar(normalize(delta), std::min(3.f,getMagnitude(delta)));
    }

    return 0;
};

// Determines the sprite to render with.
// Reflects all animation, actions, idle states, etc.

sf::Texture & MobileObject::currentTexture (MOBTemplate& temp) {
    // TODO: Figure this out. Harder than expected.
    // Also, this is not what tonight for.

    return temp.staticTextures[dir];
};
