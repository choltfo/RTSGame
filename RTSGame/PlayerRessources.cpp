#include "PlayerRessources.hpp"
#include <iostream>

PlayerRessources::PlayerRessources()
{
	QuantityOwned = 0;
	MaximumQuantity = 0;
	DrawingPosition = sf::Vector2f(0, 0);
	RessourceSprite.setPosition(DrawingPosition);
	setName("None");
	NameFont.loadFromFile("textures/Font/red alert extended.ttf");
	
	UpdateNameText();
	UpdateQuantityText();	
}

uint8_t PlayerRessources::LoadTextures(std::string Path)
{
	SourcePath = Path;
	SourceImage.loadFromFile(SourcePath);
	RessourceTexture.loadFromImage(SourceImage);
	RessourceSprite.setTexture(RessourceTexture);


	
	return 0;
}


sf::Vector2f PlayerRessources::getDrawingPosition()
{
	return DrawingPosition;
}
void PlayerRessources::setDrawingPosition(sf::Vector2f NewPosition)
{
	DrawingPosition = NewPosition;
	RessourceSprite.setPosition(DrawingPosition);
	UpdateNameText();
}

std::string PlayerRessources::getName()
{
	return Name;
}
void PlayerRessources::setName(std::string NewName)
{
	Name = NewName;

	UpdateNameText();
}

int PlayerRessources::getQuantity()
{
	return QuantityOwned;
}

void PlayerRessources::setQuantity(int NewQuanity)
{
	QuantityOwned = NewQuanity;
	UpdateQuantityText();
}

int PlayerRessources::getMaxQuantity()
{
	return MaximumQuantity;
}

void PlayerRessources::setMaxQuantity(int NewMaxQuanity)
{
	MaximumQuantity = NewMaxQuanity;
	UpdateQuantityText();
}

void PlayerRessources::UpdateNameText()
{
	NameText = sf::Text(Name, NameFont);
	NameText.setCharacterSize(30);
	NameText.setStyle(sf::Text::Bold);
	NameText.setFillColor(sf::Color::Yellow);
	NameText.setOutlineColor(sf::Color::Black);
	NameText.setPosition(DrawingPosition + sf::Vector2f(5, -30));
}


void PlayerRessources::UpdateQuantityText()
{
	QuantityString = std::to_string(QuantityOwned) + " / " + std::to_string(MaximumQuantity);
	QuantityText = sf::Text(QuantityString, NameFont);
	QuantityText.setCharacterSize(30);
	QuantityText.setStyle(sf::Text::Bold);
	if (QuantityOwned > MaximumQuantity / 2)
	{
		QuantityText.setFillColor(sf::Color::Green);
	}
	else
	{
		QuantityText.setFillColor(sf::Color::Red);
	}
	QuantityText.setOutlineColor(sf::Color::Black);
	QuantityText.setPosition(DrawingPosition + sf::Vector2f(5, 70));
}


bool PlayerRessources::CanCollect(int WantToCollect)
{
	return WantToCollect >= 0 && QuantityOwned + WantToCollect <= MaximumQuantity;
}
bool PlayerRessources::CanUse(int WantToUse)
{
	return WantToUse >= 0 && QuantityOwned >= WantToUse;
}

bool PlayerRessources::Collect(int Collecting)
{
	bool CanDo = CanCollect(Collecting);
	if (CanDo)
	{
		QuantityOwned += Collecting;
		UpdateQuantityText();
	}
	return CanDo;
}
bool PlayerRessources::Use(int Using)
{
	bool CanDo = CanUse(Using);
	if (CanDo)
	{
		QuantityOwned -= Using;
		UpdateQuantityText();
	}
	return CanDo;
}



uint8_t PlayerRessources::Render(sf::RenderWindow& window)
{
	window.draw(RessourceSprite);
	window.draw(NameText);
	window.draw(QuantityText);
	return 0;
}
