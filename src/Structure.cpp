

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

// Returns polling state.
uint8_t Structure::update() {

    // Bit flag array.
    uint8_t results = STRU_NONE;

    if (!productionQueue.empty()) {
        /*std::cout << "Production time: " <<
            productionQueue.front().option.timeNeeded
            - productionQueue.front().timer.getElapsedTime().asSeconds()
            << "\n";*/

        if (productionQueue.front().timer.getElapsedTime().asSeconds() >
            productionQueue.front().option.timeNeeded) {

            // When upgrades and superweapons are implemented, fix this.
            results = productionQueue.front().option.type == ProductionType::ptUnit
                ? STRU_UNIT:
                STRU_STRU;
        }
    }


    return results;
}

