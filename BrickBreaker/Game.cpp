#include "Game.h"
#include <iostream>

// constructeur de la classe Game
Game::Game() : window(800, 600, "Brick Breaker"), event(&window) {}

// destructeur de la classe Game
Game::~Game() {
}

// Cette fonction est la boucle principale du jeu
void Game::run()
{
	fpsConter.init();

	while (window.isOpen())
	{
		fpsConter.getFps();
		fpsConter.display();

		sf::CircleShape shape(50.f);
		// change la couleur de la forme pour du vert
		shape.setFillColor(sf::Color(100, 250, 50));

		event.handleEvent();
		window.clear();
		window.draw(shape);
		window.draw(fpsConter.getText());
		window.display();
	}
}

