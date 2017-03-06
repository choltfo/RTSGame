

#include "Structure.hpp"

Structure::Structure() {}

Structure::Structure(StructureReference* b, sf::Vector2i pos,TileSystem&gamemap) {
    position = pos;
    base = b;
    updateFOW(gamemap);
}

void Structure::updateFOW(TileSystem&gamemap) {
    // Open up the fog of war.
    for (int x = std::max(0,position.x - base->viewDist); x < std::min(MAP_DIM,position.x+base->viewDist); ++x) {
        for (int y = std::max(0,position.y - base->viewDist); y < std::min(MAP_DIM,position.y+base->viewDist); ++y) {
            if (std::pow(x-position.x,2)+std::pow(y-position.y,2) < std::pow(base->viewDist,2)) {
                gamemap.TileArray[x][y].visible = true;
            }
        }
    }
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

