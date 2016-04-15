
#include "TileSystem.hpp"

uint8_t TileSystem::loadTextures(std::string path) {
    std::ifstream infile(path.c_str(), std::ios::in);

    if (infile.is_open()) {
		std::string in;
		while (std::getline(infile, in)) {
            // Filter commented lines.
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

                // Trims the useless index helper.
                ss >> uselessFiller;

                ss >> newTexRef.imageSource;

				ss >> newTexRef.name;

                // TODO: There should be some sort of error checking involved?
                newTexRef.source.loadFromFile(newTexRef.imageSource);
                newTexRef.texture.loadFromImage(newTexRef.source);

                TextureRefs.push_back(newTexRef);
                std::cout << in << '\n';
            }
		}
    }
    return 0;
};

uint8_t TileSystem::loadMap(std::string path) {

    sf::Image mapin;

    mapin.loadFromFile(path);

    for (int x = 0; x < MAP_DIM; x ++) {
        for (int y = 0; y < MAP_DIM; y ++) {
            TileArray[x][y].TileRefIndex = mapin.getPixel(x,y).r;
            TileArray[x][y].visible = mapin.getPixel(x,y).g;
        }
    }

    return 0;
};


uint8_t TileSystem::render(sf::RenderWindow& window) {

    int xLow = (window.getView().getCenter().x - window.getView().getSize().x/2)/TEX_DIM - 1;
    int xHigh =(window.getView().getCenter().x + window.getView().getSize().x/2)/TEX_DIM + 1;

    int yLow = (window.getView().getCenter().y - window.getView().getSize().y/2)/TEX_DIM - 1;
    int yHigh =(window.getView().getCenter().y + window.getView().getSize().y/2)/TEX_DIM + 1;

    //std::cout << "X: " << xLow << " \t - " << xHigh << '\n';

    for (int x = std::max(xLow, 0); x < std::min(xHigh, MAP_DIM); x ++) {
        for (int y = std::max(yLow, 0); y < std::min(yHigh, MAP_DIM); y ++) {
            if (!TileArray[x][y].visible) {
                sf::Sprite tile(TextureRefs[TileArray[x][y].TileRefIndex].texture);
                tile.setPosition(x* TEX_DIM,y*TEX_DIM );
                window.draw(tile);
             }
        }
    }
    return 0;
}


