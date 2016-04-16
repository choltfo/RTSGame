#include "Player.hpp"


// Renders all things controlled by the player.
void Player::render(sf::RenderWindow& window, std::vector<MOBTemplate> & templates) {
    for (uint32_t i = 0; i < MOBs.size(); i++) {
        MOBs[i].render(window,templates[MOBs[i].baseIndex]);
    }
}

void Player::renderUI(sf::RenderWindow& window) {
    sf::RectangleShape Sidebar;

    sf::Color SidebarCol(25,25,25,128);
    sf::Color Basebar(15,15,15,128);
    sf::Color Line(50,50,50,128);

    Sidebar.setPosition(sf::Vector2f(window.getSize().x-200.f,0.f));
    Sidebar.setSize(sf::Vector2f(200.f,window.getSize().y));

    Sidebar.setFillColor(SidebarCol);
    Sidebar.setOutlineColor(Line);
    Sidebar.setOutlineThickness(2.f);

    window.draw(Sidebar);

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        uint16_t minimum = std::min(
                 (window.getSize().y-400)/70,
                 productionOptions.size()
                 );

    for (uint16_t i = 0; i < minimum;i++) {
        sf::RectangleShape button;
        button.setPosition(sf::Vector2f(window.getSize().x-197+(i%2)*100,200+2+(68*std::floor(i/2))));
        button.setSize(sf::Vector2f(94,64));
        window.draw(button);
        std::cout << "Drew a button!" << i << '\n';
    }


}

uint8_t Player::update(sf::Clock gameClock) {
    for (uint32_t i = 0; i < MOBs.size(); i++) {
        MOBs[i].update(gameClock);
    }
    return 0;
}

