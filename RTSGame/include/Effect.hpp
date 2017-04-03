#pragma once

#include <vector>
#include <iostream>

#include <sfml/Graphics.hpp>

#include "ClassPredec.hpp"

struct EffectInstance {
	sf::Vector2f pos;
	sf::Clock time;
	sf::Sprite sprite;
	
	float rotation;

	/*EffectInstance() {
		std::cout << "CREATING!" << std::endl;
		std::cout << pos.x << ", " << pos.y << std::endl;
	};
	~EffectInstance() {
		std::cout << "DYING!" << std::endl;
		std::cout << pos.x << ", " << pos.y << std::endl;
	};*/
};

class Effect {
public:
	// list of all instances of this effect.
	std::vector<EffectInstance> instances;

	// The textures to loop through when rendering this.
	//std::vector<sf::Texture> textures;
	sf::Texture texture;
	int nFrames;
	int cols;
	int rows;

	int frameWidth;
	int frameHeight;

	// +-+-+-+-+-+
	// |1|2|3|4|5|
	// +-+-+-+-+-+
	// |6|7|8|9|A|
	// +-+-+-+-+-+
	// |B|C|D|E|F|
	// +-+-+-+-+-+
	// |0| | | | |
	// +-+-+-+-+-+
	// | | | | | |
	// +-+-+-+-+-+

	// 16, 5, 6

	// Time between frames - seconds.
	// If zero, stays rendered as textures[0]
	float frameTime;

	// Total time to exist for.
	// If 0, lasts to the end of game.
	float timeToLive;

	// Should loop until TTL is reached,
	// Else, die at frameTime*nframe
	bool loop;
public:

	std::string name;

	Effect(std::string);

	void render(sf::RenderWindow&window);
	void update();

	void add(sf::Vector2f&,float rotation = 0.0);

	void clear();
};

class EffectHandler {
	std::vector<Effect> effects;
public:
	// Add an effect to the list of all effects.
	void registerEffect (Effect);

	// Add an efffect from a CSV file describing it
	uint8_t loadEffect(std::string);

	// Find the index of an effect by namestring
	int find(std::string);

	// Draw all effects
	void render(sf::RenderWindow&);

	// Update all effects
	void update();
	
	// Get an effect by index.
	Effect& operator[](int x) {
		return effects[x];
	};

	// Clears all effects
	void clear();
};

