
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <stdint.h>
#include <iostream>

#include "TileSystem.hpp"
#include "Game.hpp"
#include "GlobalState.hpp"
#include "VectorMath.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1440, 768), "SFML works!");

    window.setFramerateLimit(120);

    GlobalState curIn;

    sf::View view;

    sf::Clock clock;
    clock.restart();

    sf::Clock FPS;
    float lastTime = 0;

    Game game;



    view.reset(sf::FloatRect(-200 + clock.getElapsedTime().asSeconds()*100.f, 100, window.getSize().x, window.getSize().y));
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    if (game.map.loadTextures("mapdata/Textures.map")) {
        std::cout << "Could not load textures for map!\n";
        return 0;
    }

    if (game.map.loadMap("mapdata/Test512RGBBl.png")) {
        std::cout << "Could not load textures for map!\n";
        return 0;
    }



    // Test object.
    game.loadMOBTemplate("MRAP", ".png");

    MobileObject TestMOB;
    TestMOB.base = &(game.MOBTemplates[0]);
    TestMOB.position = sf::Vector2f(200,200);
    TestMOB.baseIndex = 0;

    // Test player
    Player TestPlayer("Player1",sf::Color::Red);
    TestPlayer.MOBs.push_back(TestMOB);
    TestPlayer.isLocal = true;

    //TestPlayer.selectedUnits.push_back(0);

    // Test structure
    game.loadStructureReference("VehiclePlant",".png");

    TestPlayer.structures.push_back(Structure(
                                        &game.structureReferences[0],
                                        sf::Vector2u(15,10))
                                    );

    game.structureReferences[0].productionOptions.push_back(ProductionOption());
    game.structureReferences[0].productionOptions[0].type = ProductionType::ptUnit;
    game.structureReferences[0].productionOptions[0].MOBIndex = 0;
    game.structureReferences[0].productionOptions[0].timeNeeded = 1.f;


    game.players.push_back(TestPlayer);


    game.map.generateMap();

    curIn.viewport = sf::FloatRect(100.f,100.f,window.getSize().x, window.getSize().y);


    while (window.isOpen()) {
        sf::Event event;

        curIn.LMBPressed = false;
        curIn.RMBPressed = false;
        curIn.scroll = 0;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                curIn.LMBPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
                curIn.RMBPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
            }
        }

        window.clear(sf::Color(64,64,64));

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            curIn.viewport.left-=5;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            curIn.viewport.left+=5;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            curIn.viewport.top-=5;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            curIn.viewport.top+=5;
        }

        view.reset(curIn.viewport);
        window.setView(view);

        // RENDER game-world
        game.render(window);
        window.setView(window.getDefaultView());

        // RENDER UI.
        game.renderUI(window,curIn);

        window.display();
        game.update(clock);

        float deltaT = FPS.restart().asSeconds();
        //std::cout << 1.f/(deltaT) << '\n';
    }

    return 0;
};


