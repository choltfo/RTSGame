


#include "Game.hpp"

uint8_t Game::render (sf::RenderWindow &window) {

    // Map on bottom ("Green on top!")
    map.render(window);

    for (int i = 0; i < MOBs.size(); ++i) {
        MOBs[i].render(window, MOBTemplates[MOBs[i].baseIndex]);
    }

}

// Quick, dirty, and effective. Hopefully.

uint8_t Game::loadMOBTemplate (std::string name, std::string filesuffix) {
    MOBTemplate temp;
    temp.staticTextures[Direction::DOWN].loadFromFile(
                "textures/" + name + "/" + name + "-DOWN-IDLE" + filesuffix);
    temp.staticTextures[Direction::DOWNLEFT].loadFromFile(
                "textures/" + name + "/" + name + "-DOWNLEFT-IDLE" + filesuffix);
    temp.staticTextures[Direction::DOWNRIGHT].loadFromFile(
                "textures/" + name + "/" + name + "-DOWNRIGHT-IDLE" + filesuffix);
    temp.staticTextures[Direction::LEFT].loadFromFile(
                "textures/" + name + "/" + name + "-LEFT-IDLE" + filesuffix);
    temp.staticTextures[Direction::RIGHT].loadFromFile(
                "textures/" + name + "/" + name + "-RIGHT-IDLE" + filesuffix);
    temp.staticTextures[Direction::UP].loadFromFile(
                "textures/" + name + "/" + name + "-UP-IDLE" + filesuffix);
    temp.staticTextures[Direction::UPLEFT].loadFromFile(
                "textures/" + name + "/" + name + "-UPLEFT-IDLE" + filesuffix);
    temp.staticTextures[Direction::UPRIGHT].loadFromFile(
                "textures/" + name + "/" + name + "-UPRIGHT-IDLE" + filesuffix);

    temp.testStatic.loadFromFile(
                "textures/" + name + "/" + name + "-LEFT-IDLE" + filesuffix);

    temp.name = "MOBTemplateNameRighHere!";

    MOBTemplates.push_back(temp);
}
