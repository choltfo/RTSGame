#pragma once
#include <SFML/Graphics.hpp>
class Game;
const float MINIMAP_WIDTH = 150.0f;




class Minimap
{
protected:
	sf::Texture AllyMobTexture;
	sf::Texture EnemyMobTexture;
	sf::Texture AllyPlantTexture;
	sf::Sprite AllyMobSprite;
	sf::Sprite AllyPlantSprite;
	sf::RectangleShape MinimapBackground;
	sf::RectangleShape MinimapTile;
	sf::RectangleShape MinimapFOVIndicator;
public:
	Minimap();
	void DrawTheMinimap (sf::RenderWindow&, Game&, sf::View);
};