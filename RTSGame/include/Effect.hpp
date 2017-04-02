#pragma once

#include <vector>

#include <sfml/Graphics.hpp>

#include "ClassPredec.hpp"

struct EffectInstance {
	sf::Vector2f pos;
	sf::Clock time;
	sf::Sprite sprite;
};

class Effect {
	// list of all instances of this effect.
	std::vector<EffectInstance> instances;

	// The textures to loop through when rendering this.
	sf::Texture texture[8];

	// Time between frames - seconds.
	// If zero, stays rendered to end of life.
	float frameTime;

	// Total time to exist for.
	// If 0, lasts to the end of game.
	float timeToLive;
public:
	std::string name;

	void render(sf::RenderWindow&window);
	void update();

	void addEffect();

	void clear();
};

class EffectHandler {
	std::vector<Effect> effects;
public:
	// Add an effect to the list of all effects.
	void registerEffect (Effect);

	// Add an efffect from a CSV file describing it
	void loadEffect(std::string);

	// Find the index of an effect by namestring
	int find(std::string);
	
	// Get an effect by index.
	Effect operator[](int x) {
		return effects[x];
	};

	// Clears all effects
	void clear();
};