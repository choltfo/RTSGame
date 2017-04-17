#include "Weapon.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

Weapon::Weapon(std::string path) {
	std::ifstream input;
	input.open(path);

	// File could not be opened.
	if (!input) {
		std::cout << "Could not open " << path << std::endl;
	}

	std::string line;
	while (std::getline(input, line)) {
		std::cout << "Load: " << line << std::endl;

		std::istringstream lss(line);
		std::string token;

		std::string cols[4];

		for (int i = 0; i < 4 && std::getline(lss, token, ','); ++i) {
			cols[i] = token;
		}

		// Commence the actual parsing!
		std::transform(cols[0].begin(), cols[0].end(),
			cols[0].begin(), tolower);

		if (!cols[0].compare("name")) {
			name = cols[1];

		}
		else if(!cols[0].compare("index")) {
			index = cols[1];

		}
		else if (!cols[0].compare("texture")) {
			if (texture.loadFromFile("textures/Projectiles/" + cols[1])) {
				std::cout << "Loaded texture " << cols[1] << std::endl;
			}
			else {
				std::cout << "Could not load texture " << cols[1] << std::endl;
			}
		}
		else if (!cols[0].compare("rof")) {
			cycleTimeS = 60.0 / atof(cols[1].c_str());
		}
		else if (!cols[0].compare("class")) {
			wClass = WeaponClass::WC_Cannon;

		}
		else if (!cols[0].compare("damage")) {
			damage = atof(cols[1].c_str());
		}
		else if (!cols[0].compare("range")) {
			range = atof(cols[1].c_str());
		}
		else if (!cols[0].compare("speed")) {
			speed = atof(cols[1].c_str());
		}
		else if (!cols[0].compare("splashradius")) {
			splashRadius = atof(cols[1].c_str());
		}
		else if (!cols[0].compare("target")) {
			// Hmm...
			targetMask = (UnitType)atoi(cols[1].c_str());
		}
	}
}

WeaponClass getWeaponClassByName(std::string) {
	
	return WeaponClass::WC_UNKNOWN;
}