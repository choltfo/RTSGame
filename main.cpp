
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <stdint.h>
#include <iostream>

#include "TileSystem.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1440, 768), "SFML works!");

    window.setFramerateLimit(60);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color(0,0,255,128));

    sf::RectangleShape shape2(sf::Vector2f(200.f,200.f));
    shape2.setFillColor(sf::Color::Red);
    shape2.setPosition(100.f,100.f);

    sf::View view;


    sf::Clock clock;
    clock.restart();

    sf::Clock FPS;
    float lastTime = 0;

    TileSystem tileSystem;

    view.reset(sf::FloatRect(-200 + clock.getElapsedTime().asSeconds()*100.f, 100, window.getSize().x, window.getSize().y));
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    if (tileSystem.loadTextures("mapdata/Textures.map")) {
        std::cout << "Could not load textures for map!\n";
        return 0;
    }

    if (tileSystem.loadMap("mapdata/Test512RGBBl.png")) {
        std::cout << "Could not load textures for map!\n";
        return 0;
    }



    sf::FloatRect viewport(100.f,100.f,window.getSize().x, window.getSize().y);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            viewport.left-=2;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            viewport.left+=2;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            viewport.top-=2;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            viewport.top+=2;
        }

        view.reset(viewport);

        window.setView(view);

        tileSystem.render(window);
        // RENDER game-world


        window.setView(window.getDefaultView());

        // RENDER UI.

        window.draw(shape2);
        window.draw(shape);

        window.display();
        float deltaT = FPS.restart().asSeconds();
        //std::cout << 1.f/(deltaT) << '\n';
    }

    return 0;
};


