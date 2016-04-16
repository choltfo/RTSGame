

#include "Structure.hpp"

Structure::Structure() {}

Structure::Structure(StructureReference* b, sf::Vector2u pos) {
    position = pos;
    base = b;
}

void Structure::render(sf::RenderWindow & window) {
    sf::Sprite sprite;
    sprite.setTexture(base -> texture);
    sprite.setPosition(position.x * 32, position.y  *32);

    window.draw(sprite);
}
