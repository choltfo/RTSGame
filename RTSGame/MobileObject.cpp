
#include "MobileObject.hpp"
#include "Minimap.hpp"

MobileObject::MobileObject() {
	
}

MobileObject::MobileObject(MOBTemplate*basePointer, sf::Vector2f pos, PlayerID newOwner,Game&game) {
	position = pos;
	base = basePointer;
	owner = newOwner;
	//stats = base->DefaultStats;

	hitpoints = base->DefaultStats.MaxHealth;

	dir = Direction::UP;
	curCommand.type = CommandType::NONE;

	InitializeFoV(game.map);

	
}



void MobileObject::render(sf::RenderWindow& window) {
    sf::Sprite currentSprite(currentTexture());
    currentSprite.setPosition(position + sf::Vector2f(-base->texSize.x / 2,-base->texSize.y / 2));

    if (curCommand.type == CommandType::MOVE) {
        sf::Vertex trace[] {
            sf::Vertex(targetLoc(), sf::Color::Green),
            sf::Vertex(position, sf::Color::Green)
        };
        window.draw(trace, 2, sf::LinesStrip);
    } else if (curCommand.type == CommandType::ATKTER) {
		sf::Vertex trace[]{
			sf::Vertex(targetLoc(), sf::Color::Red),
			sf::Vertex(position, sf::Color::Red)
		};
		window.draw(trace, 2, sf::LinesStrip);
	}
	else if (curCommand.type != CommandType::NONE) {
		sf::Vertex trace[]{
			sf::Vertex(targetLoc(), sf::Color::Blue),
			sf::Vertex(position, sf::Color::Blue)
		};
		window.draw(trace, 2, sf::LinesStrip);
	}

    for (size_t i = 0; i < commands.size(); i++) {
        sf::Vertex trace[] {
            sf::Vertex(commands[i].targetLoc(), sf::Color::Green),
            sf::Vertex(i == 0 ? targetLoc() : commands[i-1].targetLoc(), sf::Color::Green)
        };
        window.draw(trace, 2, sf::LinesStrip);
    }

    window.draw(currentSprite);



};

// Update this MOB.
// To be overridden as necessary.
// Returns whether this object is dead.
uint8_t MobileObject::update(sf::Clock gameClock, Game*game, Minimap& minimap) {

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
			sf::Vector2f oldPosition = position;
            position = position + scalar(normalize(delta), std::min(
				base->DefaultStats.MovementSpeed,getMagnitude(delta)));


			minimap.ShouldBeUpdated = updateFOW(game->map, oldPosition) || minimap.ShouldBeUpdated;

        }
	
    }

	// Attack things
	if (curCommand.type == CommandType::ATKTER ||
		curCommand.type == CommandType::ATKUNI ||
		curCommand.type == CommandType::ATKSTR) {


		for (int i = 0; i < commands.size(); i++) {
			if (commands[i].type == CommandType::ATKUNI) {
				if (!commands[i].target->alive) {
					commands.back() = commands[i];
					commands.pop_back();
				}
			}
		}

		sf::Vector2f delta = targetLoc() - position;
		dir = eighth(delta);

		int bestWeap = bestWeapon();

		if (bestWeap < 0) {
			// We don't have a gun that can hit the target.
			// TODO: Add logic here.

			std::cout << "No usable weapon" << std::endl;

			// Advance
			if (getSquareMagnitude(delta) > 100) {
				sf::Vector2f oldPosition = position;
				
				position = position + scalar(normalize(delta), std::min(base->DefaultStats.MovementSpeed, getMagnitude(delta)));

				minimap.ShouldBeUpdated = updateFOW(game->map, oldPosition) || minimap.ShouldBeUpdated;
			}
		} else if (getSquareMagnitude(delta) < std::pow(base->attacks[0].range, 2)) {
			// ATTTAAAAAACK!!!
			try {
				engageTarget(game);
			}
			catch (int e) {
				std::cout << "Could not engage target! -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
				curCommand.type = CommandType::NONE;
			}
		} else {
			// Advance

			sf::Vector2f oldPosition = position;
			position = position + scalar(normalize(delta), std::min(base->DefaultStats.MovementSpeed, getMagnitude(delta)));
			minimap.ShouldBeUpdated = updateFOW(game->map, oldPosition) || minimap.ShouldBeUpdated;
		}
	}
	
	//updateFOW(gamemap);
    return !alive;
};

bool hasDeadTarget(Command c, Game&game) {
	if (c.type != CommandType::ATKUNI) return false;

	bool isDead = !c.target->alive;
	if (isDead) return isDead;

	if (std::find(game.MOBs.begin(), game.MOBs.end(), c.target) != game.MOBs.end()) {
		return false;
	}
	else {
		return true;
	}
}

void MobileObject::cleanup(Game&game) {

	if (curCommand.type == CommandType::ATKUNI && !curCommand.target->alive) {
		std::cout << "Removing dead active target" << std::endl;
		curCommand.type = CommandType::NONE;
	}

	for (int i = 0; i < commands.size(); ++i) {
		Command temp = commands.front();
		commands.pop_front();

		if (hasDeadTarget(temp,game)) {
			std::cout << "Ommitting dead target" << std::endl;;
			
		} else {
			commands.push_back(temp);
		}
	}
}

void MobileObject::hasDied(Game& game)
{
	float reach = base->DefaultStats.SightDistance;

	for (int x = std::max(0, (int)(position.x / TEX_DIM - reach + 0.5f)); x < std::min(MAP_DIM, (int)(position.x / TEX_DIM + reach + 0.5)); ++x) {
		for (int y = std::max(0, (int)(position.y / TEX_DIM - reach + 0.5f)); y < std::min(MAP_DIM, (int)(position.y / TEX_DIM + reach + 0.5f)); ++y) {
			if (std::pow(x - position.x / TEX_DIM, 2) + std::pow(y - position.y / TEX_DIM, 2) < std::pow(reach, 2))
			{
				if (game.map.TileArray[x][y].InSight > 0)
				{
					game.map.TileArray[x][y].InSight--;
				}
			}
		}
	}
}


bool MobileObject::damage(float damage, WeaponClass wClass) {
	hitpoints -= damage * base->resistances[wClass];

	std::cout << "Doing " << damage * base->resistances[wClass] << " damage." << std::endl;

	if (hitpoints <= 0) {
		// Dead.
		alive = false;
		return true;
	}
	else {
		// Alive.
		alive = true;
		return false;
	}
}

// Returns the index of the effective weapon for a given task.
// And by most effective, of course, highest DPS.
int MobileObject::bestWeapon() {

	// Attacking terrain
	if (curCommand.type == CommandType::ATKTER) {
		int best = -1;
		int highest = 0;
		for (int i = 0; i < base->attacks.size(); ++i) {
			if (base->attacks[i].targetMask & UnitType::UT_TERRAIN) {
				if (base->attacks[i].damage*(1 / base->attacks[i].cycleTimeS)) {
					best = i;
					highest = base->attacks[i].damage*(1 / base->attacks[i].cycleTimeS);
				}
			}
		}

		return best;
	}

	// Attacking a MOB
	if (curCommand.type == CommandType::ATKUNI) {
		int best = -1;
		int highest = 0;
		for (int i = 0; i < base->attacks.size(); ++i) {
			if (base->attacks[i].targetMask & curCommand.target->base->DefaultStats.type) {

				if (base->attacks[i].damage*(1 / base->attacks[i].cycleTimeS)) {
					best = i;
					highest = base->attacks[i].damage*(1 / base->attacks[i].cycleTimeS);
				}
			}
		}

		return best;
	}

	// Attacking a structure
	if (curCommand.type == CommandType::ATKSTR) {
		int best = -1;
		int highest = 0;
		for (int i = 0; i < base->attacks.size(); ++i) {
			if (base->attacks[i].targetMask & (UnitType::UT_LAND | UnitType::UT_TERRAIN)) {
				if (base->attacks[i].damage*(1 / base->attacks[i].cycleTimeS)) {
					best = i;
					highest = base->attacks[i].damage*(1 / base->attacks[i].cycleTimeS);
				}
			}
		}

		return best;
	}

	// The command isn't an attack.
	return -1;
}

bool MobileObject::updateFOW(TileSystem&gamemap, sf::Vector2f oldPosition) {
    // Open up the fog of war.
    /*
    for (int x = std::max(0,(int)position.x - base->viewDist); x < std::min(MAP_DIM,(int)position.x+base->viewDist); ++x) {
        for (int y = std::max(0,(int)position.y - base->viewDist); y < std::min(MAP_DIM,(int)position.y+base->viewDist); ++y) {
            if (std::pow(x-pos.x,2)+std::pow(y-pos.y,2) < std::pow(base->viewDist,2)) {
                gamemap.TileArray[x][y].visible = true;
            }
        }
    }*/
	//bool ShouldUpdateTheMinimap = false;//This is useless now, it update it anyway because of the fog update

	float reach = base->DefaultStats.SightDistance;

	for (int x = std::max(0, (int)(oldPosition.x / TEX_DIM - reach + 0.5f)); x < std::min(MAP_DIM, (int)(oldPosition.x / TEX_DIM + reach + 0.5)); ++x) {
		for (int y = std::max(0, (int)(oldPosition.y / TEX_DIM - reach + 0.5f)); y < std::min(MAP_DIM, (int)(oldPosition.y / TEX_DIM + reach + 0.5f)); ++y) {
			if (std::pow(x - oldPosition.x / TEX_DIM, 2) + std::pow(y - oldPosition.y / TEX_DIM, 2) < std::pow(reach, 2))
			{
				if (gamemap.TileArray[x][y].InSight > 0)
				{
					gamemap.TileArray[x][y].InSight--;
				}
			}
		}
	}

	for (int x = std::max(0, (int)(position.x / TEX_DIM - reach + 0.5f)); x < std::min(MAP_DIM, (int)(position.x / TEX_DIM + reach + 0.5f)); ++x) {
		for (int y = std::max(0, (int)(position.y / TEX_DIM - reach + 0.5f)); y < std::min(MAP_DIM, (int)(position.y / TEX_DIM + reach + 0.5f)); ++y) {
			if (std::pow(x - position.x / TEX_DIM, 2) + std::pow(y - position.y / TEX_DIM, 2) < std::pow(reach, 2))
			{
				if (gamemap.TileArray[x][y].visible == false)
				{
					gamemap.TileArray[x][y].visible = true;
					//ShouldUpdateTheMinimap = true;  //This is useless now, it update it anyway because of the fog update
				}
				gamemap.TileArray[x][y].InSight++;
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
	return true;// ShouldUpdateTheMinimap;//This is useless now, it update it anyway because of the fog update
}

// Determines the sprite to render with.
// Reflects all animation, actions, idle states, etc.

sf::Texture & MobileObject::currentTexture () {
    // TODO: Figure this out. Harder than expected.
    // Also, this is not what tonight for.
	
    return base->staticTextures[dir];
};

bool MobileObject::engageTarget(Game*game) {
	sf::Vector2f delta = targetLoc() - position;
	dir = eighth(delta);

	int bWeap = bestWeapon();

	Projectile proj(base->attacks[bWeap],
		position, delta + position);

	bool canFire =
		shotTimer.getElapsedTime().asSeconds() >
		base->attacks[bWeap].cycleTimeS;

	if (canFire) {
		game->projectiles.push_back(proj);
		shotTimer.restart();
	}
	//game.map.TileArray[(int)(curCommand.point.x / TEX_DIM)][(int)(curCommand.point.y / TEX_DIM)].damage++;
	
	
	return false;
}

void MobileObject::InitializeFoV(TileSystem& gamemap)
{
	float reach = base->DefaultStats.SightDistance;
	for (int x = std::max(0, (int)(position.x / TEX_DIM - reach + 0.5f)); x < std::min(MAP_DIM, (int)(position.x / TEX_DIM + reach + 0.5f)); ++x) {
		for (int y = std::max(0, (int)(position.y / TEX_DIM - reach + 0.5f)); y < std::min(MAP_DIM, (int)(position.y / TEX_DIM + reach + 0.5f)); ++y) {
			if (std::pow(x - position.x / TEX_DIM, 2) + std::pow(y - position.y / TEX_DIM, 2) < std::pow(reach, 2))
			{
				if (gamemap.TileArray[x][y].visible == false)
				{
					gamemap.TileArray[x][y].visible = true;
					//ShouldUpdateTheMinimap = true;  //This is useless now, it update it anyway because of the fog update
				}
				gamemap.TileArray[x][y].InSight++;
			}
		}
	}
}



sf::Vector2f MobileObject::targetLoc() {
	if (curCommand.type == CommandType::HARVEST	||
		curCommand.type == CommandType::ATKTER	||
		curCommand.type == CommandType::MOVE	||
		curCommand.type == CommandType::SPECIAL) {

		return curCommand.point;
	}

	if (curCommand.type == CommandType::ATKUNI) {
		return curCommand.target->position;
	}

	if (curCommand.type == CommandType::ATKSTR) {
		return sf::Vector2f(curCommand.statTarget->position.x * 32, curCommand.statTarget->position.y * 32);
	}

	
	return position;
}


sf::Vector2f Command::targetLoc(){
	if (type == CommandType::HARVEST||
		type == CommandType::ATKTER	||
		type == CommandType::MOVE	||
		type == CommandType::SPECIAL) {

		return point;
	}

	if (type == CommandType::ATKUNI) {
		return target->position;
	}

	if (type == CommandType::ATKSTR) {
		return sf::Vector2f(statTarget->position.x*32, statTarget->position.y*32);
	}

	// Fallback, return 0,0
	return sf::Vector2f();
}
