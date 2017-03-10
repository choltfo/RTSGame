#pragma once
#include <string>
#include <SFML/Graphics/Texture.hpp>

namespace sf {
	class RenderWindow;
}

class Ressource
{
protected:
	std::string imageSource;
	sf::Image source;
	sf::Texture texture;
	std::string Name;
	int Quantity;
	int MaximumQuantity;
	
public:
	Ressource();
	int Use(int);
	int Collect(int);
	uint8_t Render(sf::RenderWindow&);
	uint8_t LoadTextures(std::string path);
};
