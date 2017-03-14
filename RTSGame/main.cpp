
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
#include "PlayerResource.hpp"

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


	game.map.generateMap();

	// Test object.

	Attack TestATK;
	TestATK.damage = 100;
	TestATK.range = 320;
	TestATK.targetMask = UnitType::UT_AIR | UnitType::UT_INFANTRY | UnitType::UT_LAND;
	TestATK.cycleTime = 0.5f;
	for (int i = 0; i < 8; ++i) {
		TestATK.anim.frames[i].loadFromFile("textures/projectiles/MissileThing.png");
	}

	game.loadMOBTemplate("MRAP", ".png");
	game.MOBTemplates[0].attacks.push_back(TestATK);

	MobileObject TestMOB;
	TestMOB.base = &(game.MOBTemplates[0]);
	TestMOB.position = sf::Vector2f(200, 200);
	TestMOB.base = &game.MOBTemplates[0];



	// Test player
	Player TestPlayer("Player1", sf::Color::Red);
	TestPlayer.MOBs.push_back(TestMOB);
	TestPlayer.isLocal = true;

	// Test structure
	game.loadStructureReference("VehiclePlant", ".png");


	game.structureReferences[0].viewDist = 5;
	game.structureReferences[0].productionOptions.push_back(ProductionOption());

	game.structureReferences[0].productionOptions[0].type = ProductionType::ptUnit;
	game.structureReferences[0].productionOptions[0].MOBTPointer = &game.MOBTemplates[0];
	game.structureReferences[0].productionOptions[0].timeNeeded = 1.f;

	TestPlayer.structures.push_back(Structure(
		&game.structureReferences[0],
		sf::Vector2i(15, 10),
		game.map)
	);


	
	game.players.push_back(TestPlayer);



	curIn.viewport = sf::FloatRect(100.f, 100.f, window.getSize().x, window.getSize().y);



	//no event when a building is spawned? it's code is here... - clone //
	for (int x = std::max(0, (int)(game.players[0].structures[0].position.x - game.players[0].structures[0].base->viewDist)); x < std::min(MAP_DIM, (int)(game.players[0].structures[0].position.x + game.players[0].structures[0].base->viewDist)); ++x) {
		for (int y = std::max(0, (int)(game.players[0].structures[0].position.y - game.players[0].structures[0].base->viewDist)); y < std::min(MAP_DIM, (int)(game.players[0].structures[0].position.y + game.players[0].structures[0].base->viewDist)); ++y) {
			if (std::pow(x - game.players[0].structures[0].position.x, 2) + std::pow(y - game.players[0].structures[0].position.y, 2) < std::pow(game.players[0].structures[0].base->viewDist, 2))
			{
				game.map.TileArray[x][y].InSight++;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////

	minimap.UpdateTheMinimap(game.map);



	//////////////////////////////////////
	// PlayerResources example - clone //
	//////////////////////////////////////
	
	PlayerResource ImmaPotato = PlayerResource();

	ImmaPotato.LoadTextures("textures/Resources/PotatoIcon.png");
	ImmaPotato.setName("Potato");
	ImmaPotato.setDrawingPosition(sf::Vector2f(window.getSize().x - 200.0f, 300.0f));
	ImmaPotato.setQuantity(0); //This is redundant
	ImmaPotato.setMaxQuantity(1000000); //I hope you like potatoes
	//////////////////////////////////////
	//////////////////////////////////////
	//////////////////////////////////////





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

		curIn.atkMod = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
						|| sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
		curIn.stackCommands = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
						|| sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

		view.reset(curIn.viewport);
		window.setView(view);

		// RENDER game-world
		game.render(window);
		window.setView(window.getDefaultView());

		// RENDER UI.
		game.renderUI(window, curIn);
		

		minimap.DrawTheMinimap(window, game, view);



		//////////////////////////////////////
		// PlayerResources example - clone //
		//////////////////////////////////////
		ImmaPotato.Render(window);
		if (!ImmaPotato.Collect(1))
		{
			ImmaPotato.setQuantity(0);
		}
		//////////////////////////////////////
		//////////////////////////////////////
		//////////////////////////////////////



		window.display();
		game.update(clock, minimap);


		float deltaT = FPS.restart().asSeconds();
		//std::cout << 1.f/(deltaT) << '\n';
	}

	//nothing to delete? 

	return 0;
};


