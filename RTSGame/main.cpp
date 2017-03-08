
// Comments are for those of weak constitutions and simple minds.

//I am weak!! HELP!


#pragma comment(linker, "/STACK:16777216")  //Increase stack size to 16Mo 
										   //(quick and dirty fix to current memory leaks and bad assignations)
#pragma comment(linker, "/HEAP:4194304")

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "TileSystem.hpp"
#include "Game.hpp"
#include "GlobalState.hpp"
#include "Minimap.hpp"


int main() {


	sf::RenderWindow window(sf::VideoMode(1366, 768), "SFML works!"); //Open and display the SFML window// resolution was (1440, 768)

	window.setFramerateLimit(60); //was 120, this is a RTS, not a FPS.  There is no (good) reasons to set it to 120

	GlobalState curIn;  //curIn?  I guess that it is the section of the window that you can click in

	sf::View view;  //Now I'm lost, it this a double buffer?

	sf::Clock clock; //pretty explicit - clone
	clock.restart();

	sf::Clock FPS;
//	float lastTime = 0;  //this thing is not used anywhere else in the code - clone

	Game game; //probably useful, I guess - clone

	Minimap minimap;// = Minimap();

	view.reset(sf::FloatRect(100, 100, window.getSize().x, window.getSize().y)); //clock.getElapsedTime().asSeconds()*100.f ??? Doesn't 'reset()' reset the view to a given rectangle? - clone
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
	TestMOB.position = sf::Vector2f(200, 200);
	TestMOB.baseIndex = 0;

	// Test player
	Player TestPlayer("Player1", sf::Color::Red);
	TestPlayer.MOBs.push_back(TestMOB);
	TestPlayer.isLocal = true;

	//TestPlayer.selectedUnits.push_back(0);

	// Test structure
	game.loadStructureReference("VehiclePlant", ".png");

	game.structureReferences[0].viewDist = 5;
	game.structureReferences[0].productionOptions.push_back(ProductionOption());
	game.structureReferences[0].productionOptions[0].type = ProductionType::ptUnit;
	game.structureReferences[0].productionOptions[0].MOBIndex = 0;
	game.structureReferences[0].productionOptions[0].timeNeeded = 1.f;

	TestPlayer.structures.push_back(Structure(
		&game.structureReferences[0],
		sf::Vector2i(15, 10),
		game.map)
	);

	game.players.push_back(TestPlayer);


	game.map.generateMap();

	curIn.viewport = sf::FloatRect(100.f, 100.f, window.getSize().x, window.getSize().y);





	//Main game loop is HERE!
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

		window.clear(sf::Color(64, 64, 64));



		sf::Vector2f ViewSize = view.getSize();
		sf::Vector2f ViewCornerPosition = view.getCenter() - ViewSize / 2.0f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			curIn.viewport.left -= 5;
			if (curIn.viewport.left < 0)
			{
				curIn.viewport.left = 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			curIn.viewport.left += 5;
			if (curIn.viewport.left > TEX_DIM * MAP_DIM - ViewSize.x)
			{
				curIn.viewport.left = TEX_DIM * MAP_DIM - ViewSize.x;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			curIn.viewport.top -= 5;
			if (curIn.viewport.top < 0)
			{
				curIn.viewport.top = 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			curIn.viewport.top += 5;
			if (curIn.viewport.top > TEX_DIM * MAP_DIM - ViewSize.y)
			{
				curIn.viewport.top = TEX_DIM * MAP_DIM - ViewSize.y;
			}
		}

		view.reset(curIn.viewport);
		window.setView(view);

		// RENDER game-world
		game.render(window);
		window.setView(window.getDefaultView());

		// RENDER UI.
		game.renderUI(window, curIn);
		



		minimap.DrawTheMinimap(window, game, view);



		window.display();
		game.update(clock);

		float deltaT = FPS.restart().asSeconds();
		//std::cout << 1.f/(deltaT) << '\n';
	}

	//nothing to delete? 

	return 0;
};


