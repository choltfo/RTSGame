
#include "Effect.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

////////////////////////////////
// Code for effect management //
////////////////////////////////

void EffectHandler::registerEffect(Effect effect) {
	effects.push_back(effect);

	//effects.reserve
}

uint8_t EffectHandler::loadEffect(std::string file) {
	effects.push_back(Effect(file));
	return 1;
}

int EffectHandler::find (std::string name) {
	for (int i = 0; i < effects.size(); ++i) {
		if (!name.compare(effects[i].name)) {
			return i;
		}
	}
	
	return -1; // Failure.
}

void EffectHandler::update() {
	for (int i = 0; i < effects.size(); ++i) {
		effects[i].update();
	}
}

void EffectHandler::render(sf::RenderWindow&window) {
	for (int i = 0; i < effects.size(); ++i) {
		effects[i].render(window);
	}
}

void EffectHandler::clear() {
	for (int i = 0; i < effects.size(); ++i) {
		effects[i].clear();
	}
}

/////////////////////////////////
// Code for individual effects //
/////////////////////////////////

Effect::Effect(std::string path) {
	std::ifstream input;
	input.open(path);


	// File could not be opened.
	if (!input) {
		std::cout << "Could not open " << path << std::endl;
		return;
	}

	std::string line;
	while (std::getline(input, line)) {
		std::cout << "Load: " << line << std::endl;

		std::istringstream lss(line);
		std::string token;

		std::string column[4];

		for (int i = 0; i < 4 && std::getline(lss, token, ','); ++i) {
			column[i] = token;
		}

		// Commence the actual parsing!
		std::transform(column[0].begin(), column[0].end(),
			column[0].begin(), tolower);

		if (!column[0].compare("name")) {
			name = column[1];

		}
		else if (!column[0].compare("texture")) {
			texture.loadFromFile(column[1]);
		}
		else if (!column[0].compare("rows")) {
			rows = std::stoi(column[1]);
			frameHeight = texture.getSize().y / rows;
		}
		else if (!column[0].compare("cols")) {
			cols = std::stoi(column[1]);
			frameWidth = texture.getSize().x / cols;
		}
		else if (!column[0].compare("nframes")) {
			nFrames = std::stoi(column[1]);
		}
		else if (!column[0].compare("frametime")) {
			frameTime = std::stof(column[1]);
			std::cout << "Frame time = " << frameTime << std::endl;
		}
		else if (!column[0].compare("TTL")) {
			timeToLive = std::stof(column[1]);
		}
		else if (!column[0].compare("loop")) {
			loop = std::stoi(column[1]);
			if (!loop) {
				timeToLive = frameTime * nFrames;
			}
		}

	}

	return;
}

void Effect::clear() {
	instances.clear();
}

void Effect::update() {
	/*for (int i = 0; i < instances.size(); ++i) {
		instances[i].update();
	}*/
}

void Effect::add(sf::Vector2f & pos,float rotation) {
	EffectInstance newInst;
	newInst.time.restart();
	newInst.pos = pos;
	newInst.sprite.setTexture(texture);

	newInst.sprite.setOrigin(frameWidth/2, frameHeight / 2);

	newInst.sprite.setRotation(rotation);

	instances.push_back(newInst);
}

void Effect::render(sf::RenderWindow& window) {
	for (int i = 0; i < instances.size(); ++i) {

		if (frameTime > 0.0) {
			// Effect is dynamic
			int frameNumber = ((int)(instances[i].time.getElapsedTime().asSeconds() / frameTime)) % nFrames;

			//std::cout << "Frame " << frameNumber << std::endl;

			
			instances[i].sprite.setTextureRect(sf::IntRect(
				(frameNumber%cols) * frameWidth,
				(frameNumber/cols) * frameHeight,
				frameWidth,
				frameHeight
			));
			

		}
		//std::cout << "Drawing " << name << " at " << instances[i].pos.x  << ", " << instances[i].pos.y << std::endl;

		instances[i].sprite.setPosition(instances[i].pos);
		window.draw(instances[i].sprite);

		// Remove this element and pass through i again.
		if (!loop && instances[i].time.getElapsedTime().asSeconds() >= timeToLive) {
			instances[i] = instances.back();
			instances.pop_back();
			--i;
		}

	}
}
