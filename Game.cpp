


#include "Game.hpp"

uint8_t Game::render (sf::RenderWindow &window) {

    // Map on bottom ("Green on top!")
    map.render(window);

    for (int i = 0; i < MOBs.size(); ++i) {
        MOBs[i].render(window);
    }

}
