
#include "Player.hpp"
#include "VectorMath.hpp"

// Renders all things controlled by the player.
void Player::render(sf::RenderWindow& window, std::vector<MOBTemplate> & templates) {
    for (uint32_t i = 0; i < MOBs.size(); i++) {
        MOBs[i].render(window,templates[MOBs[i].baseIndex]);
    }

    for (uint32_t i = 0; i < selectedUnits.size(); i++) {
        MobileObject thismob = MOBs[selectedUnits[i]];

        sf::Vertex outline[] = {
            sf::Vertex(thismob.position + sf::Vector2f(-16,-32)),
            sf::Vertex(thismob.position + sf::Vector2f(-32,-32)),
            sf::Vertex(thismob.position + sf::Vector2f(-32,32)),
            sf::Vertex(thismob.position + sf::Vector2f(32,32)),
            sf::Vertex(thismob.position + sf::Vector2f(32,-32)),
            sf::Vertex(thismob.position + sf::Vector2f(16,-32))
        };

        window.draw(outline, 6, sf::LinesStrip);

    }
}

// UI renderer is called while the window's view is reset. Everything but the world view
//  is in here.

void Player::renderUI(sf::RenderWindow& window, GlobalState curIn) {
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


    // Production Options sidebar.

    uint16_t minimum = std::min(
            (window.getSize().y-400)/70,
            productionOptions.size()
            );

    for (uint16_t i = 0; i < minimum;i++) {
        sf::RectangleShape button;
        button.setPosition(sf::Vector2f(window.getSize().x-197+(i%2)*100,200+2+(68*std::floor(i/2))));
        button.setSize(sf::Vector2f(94,64));

        sf::Vector2f relMPos = sf::Vector2f(mousePos) - button.getPosition();

        if (relMPos.x < 94 && relMPos.y < 64 && relMPos.x > 0 && relMPos.y > 0) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) button.setFillColor(sf::Color::Red);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && curIn.LMBPressed) {
                std::cout << "Button clicked!\n";
                button.setFillColor(sf::Color::Blue);
                // TODO: Implement production queue logic.
            }
        }
        window.draw(button);
    }

    // Select mobs/clear selection.
    if (curIn.LMBPressed && mousePos.x > 0 && mousePos.y > 0
            && mousePos.x < window.getSize().x - 200) {

        selectedUnits.clear();

        for (uint32_t i = 0; i < MOBs.size(); i++) {
            sf::Vector2f delta = (
                    sf::Vector2f(mousePos) +
                    sf::Vector2f(curIn.viewport.left,curIn.viewport.top) -
                    MOBs[i].position
                    );
            std::cout << delta.x << ", " << delta.y << '\n';
            if (std::abs(delta.x) < 32 && std::abs(delta.y) < 32) {
                selectedUnits.push_back(i);
            }
        }

        std::cout << "Clicked on world.\n";
    }

    // Selected mob drawer.
    for (uint32_t i = 0; i < MOBs.size(); i++) {
        sf::Vector2f relMPos = sf::Vector2f(mousePos) - MOBs[i].position;
        //if (relMPos)
    }

}

uint8_t Player::update(sf::Clock gameClock) {
    for (uint32_t i = 0; i < MOBs.size(); i++) {
        MOBs[i].update(gameClock);
    }

    return 0;
}

