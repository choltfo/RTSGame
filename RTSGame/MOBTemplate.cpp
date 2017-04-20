#include "MOBTemplate.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

MOBTemplate::MOBTemplate() {
	name = "INVALID MOB TEMPLATE";

	std::fill(resistances, resistances + N_WEAPONCLASS, 1.0);

	DefaultStats.MaxHealth = 10;
	DefaultStats.MovementSpeed = 3.14159;
	DefaultStats.SightDistance = 5;
	DefaultStats.type = UnitType::UT_TERRAIN;

	texSize.x = 32;
	texSize.y = 32;
}

// Populate this MobTemplate with a data file.
// Generally a CSV file.
int8_t MOBTemplate::loadFromFile(std::string path, std::vector<Weapon>& allAttacks) {
	std::ifstream input;
	input.open(path);

	// File could not be opened.
	if (!input) {
		std::cout << "Could not open " << path<< std::endl;
		return -1;
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
		else if (!cols[0].compare("multiplier")) {
			int weap = (int)weaponClass(cols[1]);
			if (weap > N_WEAPONCLASS || weap == 0) {
				std::cout << "Invalid weapon class in "<<path<<", \"" <<
					line << "\"" << std::endl;
			} else {
				resistances[weap] =
					std::stof(cols[2]);
			}
		}
		else if (!cols[0].compare("icon")) {
			icon.loadFromFile(cols[1]);
		}
		else if (!cols[0].compare("weapon")) {

			bool found = false;
			for (int i = 0; i < allAttacks.size() && !found; i++) {
				if (!allAttacks[i].index.compare(cols[1])) {
					attacks.push_back(allAttacks[i]);
					found = true;
					std::cout << "Found weapon " << cols[1] << std::endl;
				}
			}

			if (!found) {
				std::cout << "Could not find weapon \"" << cols[1] <<
					"\" from " << path << "" << std::endl;
			}

		} else if (!cols[0].compare("hp")) {
			DefaultStats.MaxHealth = std::stof(cols[1]);

		} else if (!cols[0].compare("speed")) {
			std::cout << "Setting speed: " << cols[1] << std::endl;
			DefaultStats.MovementSpeed = std::stof(cols[1]);
			
		} else if (!cols[0].compare("lineofsight")) {
			DefaultStats.SightDistance = std::stof(cols[1]);

		} else if (!cols[0].compare("unitType")) {
			DefaultStats.type = (UnitType)std::stoi(cols[1]);
		}
		else if (!cols[0].compare("texsizey")) {
			texSize.x = (UnitType)std::stoi(cols[1]);
		}
		else if (!cols[0].compare("texsizey")) {
			texSize.y = (UnitType)std::stoi(cols[1]);
		}

	}
	
	return 0; // VICTORY!
}
