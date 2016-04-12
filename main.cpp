// F:\CWorkspace\RTSGame

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <stdint.h>
#include <iostream>

#include "TileSystem.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color(0,0,255,128));

    sf::RectangleShape shape2(sf::Vector2f(200.f,200.f));
    shape2.setFillColor(sf::Color::Red);
    shape2.setPosition(100.f,100.f);

    sf::View view;


    sf::Clock clock;
    clock.restart();

    TileSystem tileSystem;

    if (tileSystem.loadTextures("mapdata/TextureList.csv")) {
        std::cout << "Could not load textures for map!\n";
        return 0;
    }

    if (tileSystem.loadMap("mapdata/Test512RGBBl.png")) {
        std::cout << "Could not load textures for map!\n";
        return 0;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //view.reset(sf::FloatRect(-200 + clock.getElapsedTime().asSeconds()*100.f, 100, 200, 200));
        //view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

        window.clear();
        //window.setView(view);

        window.draw(shape2);
        window.draw(shape);

        window.display();
    }

    return 0;
};
