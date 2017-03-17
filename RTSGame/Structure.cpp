

#include "Structure.hpp"

Structure::Structure() {}

Structure::Structure(StructureReference* b, sf::Vector2i pos,TileSystem&gamemap) {
	this->position = pos;
    this->base = b; 
	this->updateFOW(gamemap);
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
uint8_t Structure::update(Game&game) {

    // Bit flag array.
    uint8_t results = STRU_NONE;

    if (!productionQueue.empty()) {
        if (productionQueue.front().timer.getElapsedTime().asSeconds() >
            productionQueue.front().option.timeNeeded) {

            // When upgrades and superweapons are implemented, fix this.
			if (productionQueue.front().option.type == ProductionType::ptUnit) {
				MobileObject newMob(productionQueue.front().option.MOBTPointer,
					sf::Vector2f(position.x * 32, position.y * 32),
					owner);


				Command initial;
				initial.type = CommandType::MOVE;
				initial.point = sf::Vector2f(newMob.position.x + 64,
					newMob.position.y + 64);
				newMob.commands.push_back(initial);
				newMob.curCommand.type = CommandType::NONE;

				game.MOBs.push_back(newMob);
				for (int x = std::max(0, (int)(game.MOBs.back().position.x / TEX_DIM - 5)); x < std::min(MAP_DIM, (int)(game.MOBs.back().position.x / TEX_DIM + 5)); ++x) {
					for (int y = std::max(0, (int)(game.MOBs.back().position.y / TEX_DIM - 5)); y < std::min(MAP_DIM, (int)(game.MOBs.back().position.y / TEX_DIM + 5)); ++y) {
						if (std::pow(x - game.MOBs.back().position.x / TEX_DIM, 2) + std::pow(y - game.MOBs.back().position.y / TEX_DIM, 2) < std::pow(5, 2)) {
							game.map.TileArray[x][y].InSight++;
						}
					}
				}
				game.MOBs.back().dir = Direction::DOWN;  // You wouldn't think this was necessary.

				productionQueue.pop_front();
				if (!productionQueue.empty())
					productionQueue.front().timer.restart();
			}


        }
    }


    return results;
}

