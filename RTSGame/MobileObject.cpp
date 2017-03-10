
#include "MobileObject.hpp"
#include "Minimap.hpp"

MobileObject::MobileObject() {
	
}

MobileObject::MobileObject(MOBTemplate*basePointer, sf::Vector2f pos) {
	position = pos;
	base = basePointer;
}



void MobileObject::render(sf::RenderWindow& window) {
    sf::Sprite currentSprite(currentTexture());
    currentSprite.setPosition(position + sf::Vector2f(-32,-32));

    if (curCommand.type == CommandType::MOVE) {
        sf::Vertex trace[] {
            sf::Vertex(curCommand.point, sf::Color::Green),
            sf::Vertex(position, sf::Color::Green)
        };
        window.draw(trace, 2, sf::LinesStrip);
    }

	if (curCommand.type == CommandType::ATKTER) {
		sf::Vertex trace[]{
			sf::Vertex(curCommand.point, sf::Color::Red),
			sf::Vertex(position, sf::Color::Red)
		};
		window.draw(trace, 2, sf::LinesStrip);
	}

    for (int64_t i = 0; i < commands.size(); i++) {
        sf::Vertex trace[] {
            sf::Vertex(commands[i].point, sf::Color::Green),
            sf::Vertex(i == 0 ? curCommand.point : commands[i-1].point, sf::Color::Green)
        };
        window.draw(trace, 2, sf::LinesStrip);
    }

    window.draw(currentSprite);



};

// Update this MOB.
// To be overridden as necessary.
uint8_t MobileObject::update(sf::Clock gameClock, TileSystem& gamemap, Minimap& minimap) {
    //dir = Direction(int(floor(gameClock.getElapsedTime().asSeconds()/2)) % 8);

    if (!commands.empty()){
        if (curCommand.type == CommandType::NONE) {
            curCommand = commands.front();
            commands.pop_front();
        }
    }

    if (curCommand.type == CommandType::MOVE) {
        sf::Vector2f delta = curCommand.point - position;
        dir = eighth(delta);

        if (getSquareMagnitude(delta) < 10) {
            curCommand.type = CommandType::NONE;
        } else {
            // Should this be better? Maybe. Maybe....
            //position = position + scalar(delta, stats.MovementSpeed);
            position = position + scalar(normalize(delta), std::min(3.f,getMagnitude(delta)));

			
        }
		if (updateFOW(gamemap))
			minimap.UpdateTheMinimap(gamemap);
    }
	
	//updateFOW(gamemap);
    return 0;
};

bool MobileObject::updateFOW(TileSystem&gamemap) {
    // Open up the fog of war.
    /*
    for (int x = std::max(0,(int)position.x - base->viewDist); x < std::min(MAP_DIM,(int)position.x+base->viewDist); ++x) {
        for (int y = std::max(0,(int)position.y - base->viewDist); y < std::min(MAP_DIM,(int)position.y+base->viewDist); ++y) {
            if (std::pow(x-pos.x,2)+std::pow(y-pos.y,2) < std::pow(base->viewDist,2)) {
                gamemap.TileArray[x][y].visible = true;
            }
        }
    }*/
	bool ShouldUpdateTheMinimap = false;




	for (int x = std::max(0, (int)(position.x / TEX_DIM - 5)); x < std::min(MAP_DIM, (int)(position.x / TEX_DIM + 5)); ++x) {
		for (int y = std::max(0, (int)(position.y / TEX_DIM - 5)); y < std::min(MAP_DIM, (int)(position.y / TEX_DIM + 5)); ++y) {
			if (std::pow(x - position.x / TEX_DIM, 2) + std::pow(y - position.y / TEX_DIM, 2) < std::pow(5, 2))
			{
				if (gamemap.TileArray[x][y].visible == false)
				{
					gamemap.TileArray[x][y].visible = true;
					ShouldUpdateTheMinimap = true;
				}
			}
		}
	}

	//base cause some multi thread bugs
	/*if (base != NULL)
	{
		for (int x = std::max(0, (int)(position.x / TEX_DIM - base->viewDist)); x < std::min(MAP_DIM, (int)(position.x / TEX_DIM + base->viewDist)); ++x) {
			for (int y = std::max(0, (int)(position.y / TEX_DIM - base->viewDist)); y < std::min(MAP_DIM, (int)(position.y / TEX_DIM + base->viewDist)); ++y) {
				if (std::pow(x - position.x / TEX_DIM, 2) + std::pow(y - position.y / TEX_DIM, 2) < std::pow(base->viewDist, 2))
				{
					if (gamemap.TileArray[x][y].visible == false)
					{
						gamemap.TileArray[x][y].visible = true;
						ShouldUpdateTheMinimap = true;
					}
				}
			}
		}
	}*/
	return ShouldUpdateTheMinimap;
}

// Determines the sprite to render with.
// Reflects all animation, actions, idle states, etc.

sf::Texture & MobileObject::currentTexture () {
    // TODO: Figure this out. Harder than expected.
    // Also, this is not what tonight for.
	
    return base->staticTextures[dir];
};
