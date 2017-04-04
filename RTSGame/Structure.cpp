

#include "Structure.hpp"

Structure::Structure() {}

Structure::Structure(StructureReference* b, sf::Vector2i pos,TileSystem&gamemap) {
	this->position = pos;
    this->base = b;
	this->updateFOW(gamemap);
}

void Structure::updateFOW(TileSystem&gamemap) {
    // Open up the fog of war.
    for (int x = std::max(0,(int)(position.x - base->viewDist - 2.5f)); x < std::min(MAP_DIM, (int)(position.x + base->viewDist + 2.5f)); ++x) {
        for (int y = std::max(0, (int)(position.y - base->viewDist - 2.5f)); y < std::min(MAP_DIM, (int)(position.y + base->viewDist + 2.5f)); ++y) {
            if (std::pow(x-position.x,2)+std::pow(y-position.y,2) < std::pow(base->viewDist,2)) {
                gamemap.TileArray[x][y].visible = true;
            }
        }
    }
}

void Structure::render(sf::RenderWindow & window) {
    sf::Sprite sprite;
    sprite.setTexture(base -> texture);
    sprite.setPosition(position.x * TEX_DIM, position.y  * TEX_DIM);

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
					sf::Vector2f(position.x * TEX_DIM, position.y * TEX_DIM),
					owner, game);


				Command initial;
				initial.type = CommandType::MOVE;
				initial.point = sf::Vector2f(newMob.position.x + 64,
					newMob.position.y + 64);

				newMob.commands.clear();
				//newMob.commands.push_back(initial);
				newMob.curCommand = initial;
				
				game.MOBs.push_back(newMob);
				productionQueue.pop_front();

				if (!productionQueue.empty())
					productionQueue.front().timer.restart();
			}


        }
    }


    return results;
}

