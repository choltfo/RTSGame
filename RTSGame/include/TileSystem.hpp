
#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include <stdint.h>
#include <algorithm>

#define TEX_DIM 32.0f //Width of the textures used for a tile - clone 
#define MAP_DIM 256 //represent the size of the map ex: 512x512 - clone



class Tile {
public:

    // Data, flags, overlay information go here.

    uint8_t visible;

    // Index of TileTextureRef in TileSystem.TexutreRefs to use for this tile.
    uint16_t TileRefIndex;
};

class TileTextureRef {
public:
    std::string imageSource;
    sf::Image source;
    sf::Texture texture;
	std::string name;
};

// Object containing a floor, more or less.
// Has the ground and whatever else.
class TileSystem {
public:
    // The actual map data.
    Tile TileArray[MAP_DIM][MAP_DIM];
    // The textures that will be referenced by the tile objects to keep image storage low.
    std::vector<TileTextureRef> TextureRefs;

    uint8_t render (sf::RenderWindow&);

    uint8_t checkSpot (sf::Vector2i postion, int16_t XSize, int16_t YSize);

    uint8_t loadTextures(std::string path);
    uint8_t loadMap (std::string path);

    uint8_t generateMap();
};



