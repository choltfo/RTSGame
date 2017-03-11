#pragma once

#include <string>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>




class PlayerResource
{
protected:
	std::string SourcePath;  //here for debug - clone
	sf::Image SourceImage;
	sf::Texture ResourceTexture;
	sf::Sprite ResourceSprite;
	sf::Vector2f DrawingPosition;
	std::string Name;
	sf::Text NameText;
	sf::Font NameFont;
	std::string QuantityString;
	sf::Text QuantityText;
	std::string MaxQuantityString;
	sf::Text MaxQuantityText;
	int QuantityOwned;
	int MaximumQuantity;

	void UpdateQuantityText();
	void UpdateNameText();


public:
	
	

	PlayerResource();
	bool Use(int);
	bool CanUse(int);
	bool Collect(int);
	bool CanCollect(int);

	std::string getName();
	void setName(std::string);

	sf::Vector2f getDrawingPosition();
	void setDrawingPosition(sf::Vector2f);

	int getQuantity();
	void setQuantity(int);

	int getMaxQuantity();
	void setMaxQuantity(int);


	uint8_t Render(sf::RenderWindow&);
	uint8_t LoadTextures(std::string);
};