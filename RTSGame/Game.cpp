
#include "Game.hpp"


uint8_t Game::render (sf::RenderWindow& window) {

    // Map on bottom ("Green on top!")
    map.render(window);

    for (uint16_t i = 0; i < players.size(); ++i) {
        players[i].render(window, *this);
    }

	for (uint32_t i = 0; i < MOBs.size(); i++) {
		MobileObject mob = MOBs[i];
		if (map.TileArray[(int)(mob.position.x / TEX_DIM)][(int)(mob.position.y / TEX_DIM)].InSight)
			MOBs[i].render(window);
	}

	for (uint32_t i = 0; i < structures.size(); i++) {
		if (map.TileArray[structures[i].position.x][structures[i].position.y].InSight)
			structures[i].render(window);
	}

	for (uint32_t i = 0; i < projectiles.size(); i++) {
		//if (map.TileArray[(int)(projectiles[i].position.x / TEX_DIM)][(int)(projectiles[i].position.y / TEX_DIM)].InSight)
		//	projectiles[i].render(window);
	}

    return 0;
}

uint8_t Game::renderUI(sf::RenderWindow& window, UIState curIn) {
    for (uint16_t i = 0; i < players.size(); ++i) {
        if (players[i].isLocal) players[i].GUI(window, curIn, *this);
    }
    return 0;
}

// Update game
uint8_t Game::update(sf::Clock gameClock, Minimap& minimap) {
    for (uint64_t i = 0; i < players.size(); ++i) {
        players[i].update(gameClock, *this, minimap);
    }
	for (uint64_t i = 0; i < projectiles.size(); ++i) {
		if (projectiles[i].update(*this)) {
			// Projectile has blown up.
			Projectile temp = projectiles[i];
			projectiles[i] = projectiles.back();
			projectiles.pop_back();
		}
	}
    return 0;
}

uint8_t Game::loadStructureReference (std::string name, std::string filesuffix) {
    StructureReference temp;
    if (!temp.texture.loadFromFile("textures/"+name+"/"+name+""+filesuffix)) {
        std::cout << "Failed to load textures/"+name+"/"+name+""+filesuffix+"\n";
        return -1;
    }
    temp.size = sf::Vector2u(temp.texture.getSize().x / 32,temp.texture.getSize().y / 32);
    structureReferences.push_back(temp);
    return 0;
}

// Quick, dirty, and effective. Hopefully.
uint8_t Game::loadMOBTemplate (std::string name, std::string filesuffix) {
    MOBTemplate temp;

    temp.staticTextures[Direction::DOWN].loadFromFile(
                "textures/" + name + "/" + name + "-DOWN-IDLE" + filesuffix);
    temp.staticTextures[Direction::DOWNLEFT].loadFromFile(
                "textures/" + name + "/" + name + "-DOWNLEFT-IDLE" + filesuffix);
    temp.staticTextures[Direction::DOWNRIGHT].loadFromFile(
                "textures/" + name + "/" + name + "-DOWNRIGHT-IDLE" + filesuffix);
    temp.staticTextures[Direction::LEFT].loadFromFile(
                "textures/" + name + "/" + name + "-LEFT-IDLE" + filesuffix);
    temp.staticTextures[Direction::RIGHT].loadFromFile(
                "textures/" + name + "/" + name + "-RIGHT-IDLE" + filesuffix);
    temp.staticTextures[Direction::UP].loadFromFile(
                "textures/" + name + "/" + name + "-UP-IDLE" + filesuffix);
    temp.staticTextures[Direction::UPLEFT].loadFromFile(
                "textures/" + name + "/" + name + "-UPLEFT-IDLE" + filesuffix);
    temp.staticTextures[Direction::UPRIGHT].loadFromFile(
                "textures/" + name + "/" + name + "-UPRIGHT-IDLE" + filesuffix);

    temp.name = name;

    MOBTemplates.push_back(temp);
    return 0;
}
