
#include "TileSystem.hpp"

uint8_t TileSystem::loadTextures(std::string path) {
    std::ifstream infile;
    infile.open(path);

    //if (infile.)
    while (infile.peek()) {
        std::cout << infile;
    }
    return 0;
};

uint8_t TileSystem::loadMap(std::string path) {
    std::ifstream infile(path, std::ios::in);

    if (infile.is_open()) {
		std::string in;
		while (std::getline(infile, in)) {
            if (in[0] != '#') {

                int uselessFiller;

                // Okay, so this is kinda dirty and simple, but it worked in Blackened-Soil.

                for (int i = 0; i < in.length(); i++) {
                    if (in[i] == ' ') in[i] = '-';
                    if (in[i] == ',') in[i] = ' ';
                }

                std::stringstream ss;
                ss.clear();
                ss << in;

                TileTextureRef newTexRef;

                ss >> uselessFiller;
                ss >> newTexRef.imageSource;

                // TODO: There should be some sort of error checking involved?
                newTexRef.source.loadFromFile(newTexRef.imageSource);
            }
		}
    }
};


uint8_t TileSystem::render(sf::RenderWindow& window) {
    for (int x = 0; x < MAP_DIM; x ++) {
        for (int y = 0; y < MAP_DIM; y ++) {

        }
    }
    return 0;
}


