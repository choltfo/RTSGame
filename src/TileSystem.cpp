
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

                // Replace commas with spaces and spaces with hyphens.
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

                // TODO (Ian): There should be some sort of error checking involved?
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
            TileArray[x][y].visible = 0;//mapin.getPixel(x,y).g;
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


uint8_t TileSystem::generateMap() {
    std::srand(std::time(0));

    // First, populate regions.
    // Regions are abstract 8*8 tiles, seeded from a
    //  point where x and y are equal to 8n + 4.
    // These points start at 4,4, (4+(0*8)) and end and 252,252 (4+(31*8)).
    for (int x = 4; x < MAP_DIM; x+=8) {
        for (int y = 4; y < MAP_DIM; y+=8) {
            TileArray[x][y].TileRefIndex = std::rand() % TextureRefs.size();
        }
    }

    // Tightness of expansion grouping.
    int seedOffset = 3;

    // Expand seeding.
    for (int x = 4+8*seedOffset; x < MAP_DIM-(8*seedOffset); x+=8) {
        for (int y = 4+8*seedOffset; y < MAP_DIM-(8*seedOffset); y+=8) {
            TileArray[x][y].TileRefIndex = TileArray
            [x+ ((std::rand() % (seedOffset*2 + 1) - seedOffset)*8)]
            [y+ ((std::rand() % (seedOffset*2 + 1) - seedOffset)*8)]
            .TileRefIndex;
        }
    }

    // Expand domains.
    for (int x = 0; x < MAP_DIM; x++) {
        for (int y = 0; y < MAP_DIM; y++) {
                        // Integer division: Because failure is always an option!
            TileArray[x][y].TileRefIndex = TileArray[(x/8)*8+4][(y/8)*8+4].TileRefIndex;
        }
    }

    int offset = 2;

    for (int x = offset; x < MAP_DIM-offset; x++) {
        for (int y = offset; y < MAP_DIM-offset; y++) {
                        // Integer division: Because failure is always an option!
            TileArray[x][y].TileRefIndex = TileArray[x+(std::rand() % (offset*2 + 1) - offset)][y+(std::rand() % (offset*2 + 1) - offset)].TileRefIndex;
        }
    }

    return 0;
}

