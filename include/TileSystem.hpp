
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

#define TEX_DIM 32.f
#define MAP_DIM 512

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

    // Pre-rendered tiles. Stored in a straight vector to keep the madness to a minimum.
    // 0,1,2,3,     Truncate as needed. 1024 tiles (32x32) is the worst case,
    // 4,5,6,7,      with a maxTexSize of 512. Still better!
    // 8,9,A,B,     All tiles are min(MAP_DIM*TEX_DIM, sf::Texture::getMaximumSize())
    // C,D,E,F       on both dimensions.
    std::vector<sf::Texture> PreRenders;

    // Size of tiles (min(MAP_DIM*TEX_DIM, sf::Texture::getMaximumSize()))
    uint64_t PreRenEdgeLength;

    // Number of prerenders on an edge.
    uint64_t NumPreRenSqrt;

    // Called after texture load and before first render. Will cause a lag spike!
    uint8_t InitTiles();

    uint8_t render (sf::RenderWindow&);

    uint8_t checkSpot (sf::Vector2i postion, int16_t XSize, int16_t YSize);

    uint8_t loadTextures(std::string path);
    uint8_t loadMap (std::string path);

    uint8_t generateMap();
};



