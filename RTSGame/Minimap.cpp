#include "Minimap.hpp"
#include <type_traits>
#include <TileSystem.hpp>
#include <Game.hpp>

Minimap::Minimap()
{
	if (!AllyMobTexture.loadFromFile("textures/Minimap/Vehicle_Friendly.png"))
	{
		// error... - clone
		std::cout << "could not load the textures/Minimap/Vehicle_Friendly.png";
	}

	if (!EnemyMobTexture.loadFromFile("textures/Minimap/Vehicle_Enemy.png"))
	{
		// error... - clone
		std::cout << "could not load the textures/Minimap/Vehicle_Enemy.png";
	}

	if (!AllyPlantTexture.loadFromFile("textures/Minimap/VehiclePlant.png"))
	{
		// error... - clone
		std::cout << "could not load the textures/Minimap/VehiclePlant.png";
	}
	MinimapTexture.create(MAP_DIM, MAP_DIM);

	MinimapBackground.setSize(sf::Vector2f(MINIMAP_WIDTH, MINIMAP_WIDTH));
	MinimapBackground.setFillColor(sf::Color(239, 228, 176, 50));
	MinimapBackground.setOutlineColor(sf::Color::Red);
	MinimapBackground.setOutlineThickness(2.f);



	
	MinimapFOVIndicator.setFillColor(sf::Color(200, 200, 200, 32));
	MinimapFOVIndicator.setOutlineColor(sf::Color::Red);
	MinimapFOVIndicator.setOutlineThickness(1.f);


	AllyMobSprite.setTexture(AllyMobTexture);
	AllyPlantSprite.setTexture(AllyPlantTexture);
	Pixies = new sf::Uint8[MAP_DIM*MAP_DIM * 4];

}

void Minimap::UpdateTheMinimap(TileSystem& gamemap)
{
	for (int i = 0; i < MAP_DIM; i++)
		for (int j = 0; j < MAP_DIM; j++)
		{
			if (gamemap.TileArray[j][i].visible)
			{
				/*
				0,mapdata/Tiles/WaterTile32.png,Water
				1,mapdata/Tiles/DesertTile32.png,Desert
				2,mapdata/Tiles/GrassTile32.png,Grass
				3,mapdata/Tiles/StoneTile32.png,Stone
				*/
				switch (gamemap.TileArray[j][i].TileRefIndex)
				{
				case 0:
					Pixies[i*MAP_DIM  * 4 + j * 4] = 50; //R
					Pixies[i*MAP_DIM  * 4 + j * 4 + 1] = 50;  //G
					Pixies[i*MAP_DIM  * 4 + j * 4 + 2] = 255;  //B
					Pixies[i*MAP_DIM  * 4 + j * 4 + 3] = 255;  //A
					break;
				case 1:
					Pixies[i*MAP_DIM  * 4 + j * 4] = 255;
					Pixies[i*MAP_DIM  * 4 + j * 4 + 1] = 175;
					Pixies[i*MAP_DIM  * 4 + j * 4 + 2] = 45;
					Pixies[i*MAP_DIM  * 4 + j * 4 + 3] = 255;
					break;
				case 2:
					Pixies[i*MAP_DIM  * 4 + j * 4] = 10;
					Pixies[i*MAP_DIM  * 4 + j * 4 + 1] = 120;
					Pixies[i*MAP_DIM  * 4 + j * 4 + 2] = 0;
					Pixies[i*MAP_DIM  * 4 + j * 4 + 3] = 255;
					break;
				case 3:
					Pixies[i*MAP_DIM  * 4 + j * 4] = 100;
					Pixies[i*MAP_DIM  * 4 + j * 4 + 1] = 100;
					Pixies[i*MAP_DIM  * 4 + j * 4 + 2] = 100;
					Pixies[i*MAP_DIM  * 4 + j * 4 + 3] = 255;
					break;
				default:
					Pixies[i*MAP_DIM * 4 + j * 4] = 10;
					Pixies[i*MAP_DIM * 4 + j * 4 + 1] = 10;
					Pixies[i*MAP_DIM * 4 + j * 4 + 2] = 10;
					Pixies[i*MAP_DIM * 4 + j * 4 + 3] = 10;
					break;
				}
			}
		}
	
	MinimapTexture.create(MAP_DIM, MAP_DIM);
	MinimapTexture.update(Pixies);
	
	MinimapSprite.setTexture(MinimapTexture);
	MinimapSprite.setScale(sf::Vector2f(MINIMAP_WIDTH / MAP_DIM, MINIMAP_WIDTH / MAP_DIM));

	
}


void Minimap::DrawTheMinimap(sf::RenderWindow& window, Game& game, sf::View view)
{

	MinimapSprite.setPosition(sf::Vector2f(window.getSize().x - 200.f, 50.f));
	window.draw(MinimapSprite);

	MinimapBackground.setPosition(sf::Vector2f(window.getSize().x - 200.f, 50.f));
	

	window.draw(MinimapBackground);
	
	for (int i = 0; i < game.players.size(); i++)
	{
		for (int j = 0; j < game.players[i].MOBs.size(); j++)
		{
			AllyMobSprite.setPosition(sf::Vector2f(game.players[i].MOBs[j].position.x * MINIMAP_WIDTH / MAP_DIM / TEX_DIM + window.getSize().x - 200.f - 4, game.players[i].MOBs[j].position.y * MINIMAP_WIDTH / MAP_DIM / TEX_DIM + 50.f));
			window.draw(AllyMobSprite);
		}
		for (int j = 0; j < game.players[i].structures.size(); j++)
		{
			AllyPlantSprite.setPosition(sf::Vector2f(game.players[i].structures[j].position.x * MINIMAP_WIDTH / MAP_DIM + window.getSize().x - 200.f - 4, game.players[i].structures[j].position.y * MINIMAP_WIDTH / MAP_DIM + 50.f));
			window.draw(AllyPlantSprite);
		}
	}

	sf::Vector2f ViewSize = view.getSize();
	sf::Vector2f ViewCornerPosition = view.getCenter() - ViewSize / 2.0f;
	MinimapFOVIndicator.setPosition(ViewCornerPosition.x * MINIMAP_WIDTH / MAP_DIM / TEX_DIM + window.getSize().x - 200.f, ViewCornerPosition.y * MINIMAP_WIDTH / MAP_DIM / TEX_DIM + 50.f);
	MinimapFOVIndicator.setSize(sf::Vector2f(ViewSize.x * MINIMAP_WIDTH / MAP_DIM / TEX_DIM, ViewSize.y * MINIMAP_WIDTH / MAP_DIM / TEX_DIM));
	window.draw(MinimapFOVIndicator);

}
