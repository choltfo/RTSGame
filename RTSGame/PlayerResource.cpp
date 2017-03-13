#include "PlayerResource.hpp"
#include <iostream>

PlayerResource::PlayerResource()
{
	QuantityOwned = 0;
	MaximumQuantity = 0;
	DrawingPosition = sf::Vector2f(0, 0);
	ResourceSprite.setPosition(DrawingPosition);
	setName("None");
	NameFont.loadFromFile("textures/Font/red alert extended.ttf");
	
	UpdateNameText();
	UpdateQuantityText();	
}

uint8_t PlayerResource::LoadTextures(std::string Path)
{
	SourcePath = Path;
	SourceImage.loadFromFile(SourcePath);
	ResourceTexture.loadFromImage(SourceImage);
	ResourceSprite.setTexture(ResourceTexture);


	
	return 0;
}


sf::Vector2f PlayerResource::getDrawingPosition()
{
	return DrawingPosition;
}
void PlayerResource::setDrawingPosition(sf::Vector2f NewPosition)
{
	DrawingPosition = NewPosition;
	ResourceSprite.setPosition(DrawingPosition);
	UpdateNameText();
}

std::string PlayerResource::getName()
{
	return Name;
}
void PlayerResource::setName(std::string NewName)
{
	Name = NewName;

	UpdateNameText();
}

int PlayerResource::getQuantity()
{
	return QuantityOwned;
}

void PlayerResource::setQuantity(int NewQuanity)
{
	QuantityOwned = NewQuanity;
	UpdateQuantityText();
}

int PlayerResource::getMaxQuantity()
{
	return MaximumQuantity;
}

void PlayerResource::setMaxQuantity(int NewMaxQuanity)
{
	MaximumQuantity = NewMaxQuanity;
	UpdateQuantityText();
}

void PlayerResource::UpdateNameText()
{
	NameText = sf::Text(Name, NameFont);
	NameText.setCharacterSize(30);
	NameText.setStyle(sf::Text::Bold);
	NameText.setFillColor(sf::Color::Yellow);
	NameText.setOutlineColor(sf::Color::Black);
	NameText.setPosition(DrawingPosition + sf::Vector2f(5, -30));
}


void PlayerResource::UpdateQuantityText()
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


bool PlayerResource::CanCollect(int WantToCollect)
{
	return WantToCollect >= 0 && QuantityOwned + WantToCollect <= MaximumQuantity;
}
bool PlayerResource::CanUse(int WantToUse)
{
	return WantToUse >= 0 && QuantityOwned >= WantToUse;
}

bool PlayerResource::Collect(int Collecting)
{
	bool CanDo = CanCollect(Collecting);
	if (CanDo)
	{
		QuantityOwned += Collecting;
		UpdateQuantityText();
	}
	return CanDo;
}
bool PlayerResource::Use(int Using)
{
	bool CanDo = CanUse(Using);
	if (CanDo)
	{
		QuantityOwned -= Using;
		UpdateQuantityText();
	}
	return CanDo;
}



uint8_t PlayerResource::Render(sf::RenderWindow& window)
{
	window.draw(ResourceSprite);
	window.draw(NameText);
	window.draw(QuantityText);
	return 0;
}
