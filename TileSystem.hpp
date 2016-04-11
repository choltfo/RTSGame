
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <fstream>

#include <stdint.h>

#define MAP_DIM 256

class Tile {
public:

    // Data, flags, overlay information go here.

    uint16_t TileRefIndex;
};

class TileTextureRef {
    std::string imageSource;
    sf::Image source;
    sf::Texture texture;
};

// Object containing a floor, more or less.
// Has the ground and whatever else.
class TileSystem {
public:
    // The actual map data.
    Tile TileArray[MAP_DIM][MAP_DIM];
    // The textures that will be referenced bya the tile objects to keep image storage low.
    std::vector<TileTextureRef> TextureRefs;

    uint8_t LoadTextures(std::string path);
    uint8_t LoadMap (std::string path);
};
