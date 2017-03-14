#pragma once
#include <SFML/Graphics.hpp>
#include <TileSystem.hpp>
class Game;
const float MINIMAP_WIDTH = 150.0f;




class Minimap
{
protected:
	sf::Texture AllyMobTexture;
	sf::Texture EnemyMobTexture;
	sf::Texture AllyPlantTexture;
	sf::Texture MinimapTexture;
	sf::Sprite AllyMobSprite;
	sf::Sprite EnemyMobSprite;
	sf::Sprite AllyPlantSprite;
	sf::Sprite MinimapSprite;
	sf::RectangleShape MinimapBackground;
	sf::RectangleShape MinimapFOVIndicator;
	sf::Uint8* Pixies;
	
public:
	bool ShouldBeUpdated;
	Minimap();
	void UpdateTheMinimap(TileSystem&);
	void DrawTheMinimap (sf::RenderWindow&, Game&, sf::View);
};