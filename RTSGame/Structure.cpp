

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

				MobileObject *newMob = new MobileObject(productionQueue.front().option.MOBTPointer,
					sf::Vector2f(position.x * TEX_DIM, position.y * TEX_DIM),
					owner, game);


				Command initial;
				initial.type = CommandType::MOVE;
				initial.point = sf::Vector2f(newMob->position.x + 128,
					newMob->position.y + 128);

				newMob->commands.clear();
				//newMob.commands.push_back(initial);
				newMob->curCommand = initial;
				
				game.MOBs.push_back(newMob);
				productionQueue.pop_front();

				if (!productionQueue.empty())
					productionQueue.front().timer.restart();
			}


        }
    }


    return results;
}

const int StructureParserCols = 4;

ProductionOption parseProductionOption (std::string cols[StructureParserCols], std::vector<MOBTemplate>&MOBTs) {
	std::cout << "Loading production option:" << std::endl;
	std::cout << cols[2] << std::endl;
	ProductionOption po;

	if (!cols[1].compare("unit")) {
		po.type = ProductionType::ptUnit;

		for (int i = 0; i < MOBTs.size(); ++i) {
			if (!cols[2].compare(MOBTs[i].index)) {
				po.MOBTPointer = &MOBTs[i];
				po.cost = std::stoi(cols[3]);
				//po.timeNeeded = MOBTs[i].
				// TODO: Decide on where to take this from.
				po.timeNeeded = 1.0f;

				std::cout << "Production option refers to " << po.MOBTPointer->name << std::endl;

				po.buttonSpr.setTexture(po.MOBTPointer->icon);
				return po;
			}
		}
	}
}

void StructureReference::loadSR(std::string fileName, std::string textureDir, std::vector<MOBTemplate>&MOBTs) {
	std::ifstream input;
	input.open(textureDir + "/" + fileName);

	// File could not be opened.
	if (!input) {
		std::cout << "Could not open " << fileName << std::endl;
	}
	else {
		std::cout << "Reading " << fileName << std::endl;
	}

	std::string line;
	while (std::getline(input, line)) {
		std::cout << "Load: " << line << std::endl;

		std::istringstream lss(line);
		std::string token;

		std::string cols[StructureParserCols];

		for (int i = 0; i < StructureParserCols && std::getline(lss, token, ','); ++i) {
			cols[i] = token;
		}

		// Commence the actual parsing!
		std::transform(cols[0].begin(), cols[0].end(),
			cols[0].begin(), tolower);

		if (!cols[0].compare("name")) {
			name = cols[1];
		}
		else if (!cols[0].compare("texture")) {
			texture.loadFromFile(textureDir + "/" + cols[1]);
		}
		else if (!cols[0].compare("lineofsight")) {
			viewDist = std::stof(cols[1]);
		}
		else if (!cols[0].compare("symbol")) {
			icon.loadFromFile(textureDir + "/" + cols[1]);
		}
		else if (!cols[0].compare("production")) {
			productionOptions.push_back(parseProductionOption(cols,MOBTs));
		}
		else if (!cols[0].compare("hp")) {
			maxHitpoints = std::stof(cols[1]);
		}
		else if (!cols[0].compare("texsize")) {
			size.x = (UnitType)std::stoi(cols[1]);
			size.y = (UnitType)std::stoi(cols[2]);
		}

	}
	
}

