
#include "Player.hpp"
#include "VectorMath.hpp"

// Renders all things controlled by the player.
void Player::render(
	sf::RenderWindow& window,
	Game & game
    ) {

    if (selectionType == SelectionType::stUNITS) {
        for (uint32_t i = 0; i < selectedUnits.size(); i++) {
            MobileObject thismob = game.MOBs[selectedUnits[i]];

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

    if (selectionType == SelectionType::stSTRUCTURES) {
        for (uint32_t i = 0; i < selectedUnits.size(); i++) {
            Structure thisstruct = game.structures[selectedUnits[i]];

            int32_t xsize = game.structures[i].base->size.x*32;
            int32_t ysize = game.structures[i].base->size.y*32;

            sf::Vector2f pos(thisstruct.position.x * 32,thisstruct.position.y * 32);

            sf::Vertex outline[] = {
                sf::Vertex(pos + sf::Vector2f(16,0)),
                sf::Vertex(pos + sf::Vector2f(0,0)),
                sf::Vertex(pos + sf::Vector2f(0,ysize)),
                sf::Vertex(pos + sf::Vector2f(xsize,ysize)),
                sf::Vertex(pos + sf::Vector2f(xsize,0)),
                sf::Vertex(pos + sf::Vector2f(xsize-16,0))
            };

            window.draw(outline, 6, sf::LinesStrip);
        }
    }
}

// UI renderer is called while the window's view is reset. Everything but the world view
//  is in here.
void Player::GUI(sf::RenderWindow& window, UIState curIn, Game & game) {
    sf::RectangleShape Sidebar;

    sf::Color SidebarCol(25,25,25,128);
	sf::Color Basebar(15,15,15,128); //This is not used anywhere else in the code - clone
    sf::Color Line(50,50,50,128);

    Sidebar.setPosition(sf::Vector2f(window.getSize().x-200.f,0.f));
    Sidebar.setSize(sf::Vector2f(200.f,window.getSize().y));

    Sidebar.setFillColor(SidebarCol);
    Sidebar.setOutlineColor(Line);
    Sidebar.setOutlineThickness(2.f);

    window.draw(Sidebar);

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);


    // Draw and implement productionOptions sidebar.

    // Make sure we don't start drawing off the screen.
    uint16_t screenMax = ((window.getSize().y-400)/70) * 2;

    uint16_t itemsDrawn = 0;
    if (selectionType == SelectionType::stSTRUCTURES) {
        for (uint16_t i = 0; i < game.structures.size() && itemsDrawn < screenMax; i++) {
            for (uint16_t u = 0; u < (*(game.structures[i].base)).productionOptions.size() && itemsDrawn < screenMax; u++) {
                sf::RectangleShape button;
				button.setPosition(sf::Vector2f(window.getSize().x-197+(i%2)*100,200+2+(68*std::floor(i/2))));
				button.setSize(sf::Vector2f(94,64));

				sf::Vector2f relMPos = sf::Vector2f(mousePos) - button.getPosition();

				if (relMPos.x < 94 && relMPos.y < 64 && relMPos.x > 0 && relMPos.y > 0) {
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) button.setFillColor(sf::Color::Red);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && curIn.LMBPressed) {
						std::cout << "Issued production item to unit "<<i<<"\n";
						button.setFillColor(sf::Color::Blue);
						game.structures[i].productionQueue.push_back(ProductionItem(
								(*(game.structures[i].base)).productionOptions[u])
							);
						// TODO: Implement production queue logic.
					}
				}
				window.draw(button);
				++itemsDrawn;
            }
        }
    }

    // Select mobs/clear selection.
    if (curIn.LMBPressed && mousePos.x > 0 && mousePos.y > 0
            && mousePos.x < window.getSize().x - 200) {


        // Continuous selection switch.
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
            selectionType == SelectionType::stSTRUCTURES) {
            selectedUnits.clear();
            selectionType = SelectionType::stNONE;
        }

        for (uint32_t i = 0; i < game.MOBs.size(); i++) {
            sf::Vector2f delta = (
                    sf::Vector2f(mousePos) +
                    sf::Vector2f(curIn.viewport.left,curIn.viewport.top) -
				game.MOBs[i].position
                    );
            //std::cout << delta.x << ", " << delta.y << '\n';
            if (std::abs(delta.x) < 32 && std::abs(delta.y) < 32) {
                if (std::find(selectedUnits.begin(), selectedUnits.end(), i)
                    == selectedUnits.end()) {
                    selectedUnits.push_back(i);
                    selectionType = SelectionType::stUNITS;
                }
            }
        }

        // Units take precedence over structures.
        if (selectedUnits.size() == 0) {
            for (uint32_t i = 0; i < game.structures.size(); i++) {
                sf::Vector2f delta = (
                        sf::Vector2f(mousePos) +
                        sf::Vector2f(curIn.viewport.left,curIn.viewport.top) -
                        sf::Vector2f(game.structures[i].position.x * 32, game.structures[i].position.y * 32)
                        );
                std::cout << delta.x << ", " << delta.y << '\n';
                if (
                    delta.x < game.structures[i].base->size.x*32 &&
                    delta.y < game.structures[i].base->size.y*32 &&
                    delta.y > 0 &&
                    delta.x > 0
                    ) {

                    selectedUnits.push_back(i);
                    selectionType = SelectionType::stSTRUCTURES;
                }
            }
        }
    }

    // Send commands.
    if (curIn.RMBPressed && mousePos.x > 0 && mousePos.y > 0
            && mousePos.x < window.getSize().x - 200) {

        // Issue commands!
        if (selectionType == SelectionType::stUNITS) {

			// Attack modifier. This enables terrain attack
			if (curIn.atkMod) {
				// Attack command
				// TODO: ATKstr, ATKuni
				Command comm;
				sf::Vector2f point = sf::Vector2f(mousePos) + sf::Vector2f(curIn.viewport.left, curIn.viewport.top);
				comm.point = point;
				comm.type = CommandType::ATKTER;

				for (uint32_t i = 0; i < selectedUnits.size(); i++) {

					if (curIn.stackCommands) {
						game.MOBs[selectedUnits[i]].commands.push_back(comm);
					}
					else {
						game.MOBs[selectedUnits[i]].commands.clear();
						game.MOBs[selectedUnits[i]].commands.push_back(comm);
						game.MOBs[selectedUnits[i]].curCommand.type = CommandType::NONE;
					}
				}

				std::cout << "Issued move command to " << selectedUnits.size() << " units.\n";
			} else { // If attack modifier is not active...
				// Move order

				Command comm;
				sf::Vector2f point = sf::Vector2f(mousePos) + sf::Vector2f(curIn.viewport.left, curIn.viewport.top);
				comm.point = point;
				comm.type = CommandType::MOVE;

				// Now for the space filling math!
				// x += ((i%crn)-crn/2)*32
				// y += ((i/crn)-crn/2)*32

				int crn = std::ceil(std::sqrt(selectedUnits.size()));

				std::cout << "crn of selection number is " << crn << "\n";
				std::cout << "Input location: " << point.x
					<< ", " << point.y << "\n";

				for (uint32_t i = 0; i < selectedUnits.size(); i++) {
					comm.point = sf::Vector2f(point.x + ((i%crn) * 64) - ((crn - 1) * 32),
						point.y + ((i / crn) * 64) - ((crn - 1) * 32)
					);
					std::cout << "Command location: " << comm.point.x
						<< ", " << comm.point.y << "\n";

					if (curIn.stackCommands) {
						game.MOBs[selectedUnits[i]].commands.push_back(comm);
					}
					else {
						game.MOBs[selectedUnits[i]].commands.clear();
						game.MOBs[selectedUnits[i]].commands.push_back(comm);
						game.MOBs[selectedUnits[i]].curCommand.type = CommandType::NONE;
					}
				}

				std::cout << "Issued move command to " << selectedUnits.size() << " units.\n";
			}
        }
    }

    // Selected mob drawer.
    for (uint32_t i = 0; i < game.MOBs.size(); i++) {
       // sf::Vector2f relMPos = sf::Vector2f(mousePos) - MOBs[i].position;  //Not implemented yet - clone
    }

}

uint8_t Player::update(sf::Clock gameClock, Game & game, Minimap & minimap) {
    for (uint32_t i = 0; i < game.MOBs.size(); i++) {
        game.MOBs[i].update(gameClock, game, minimap);
    }

    for (uint32_t i = 0; i < game.structures.size(); i++) {
        uint8_t result = game.structures[i].update(game);
    }
    // Handle command sending.

    return 0;
}




