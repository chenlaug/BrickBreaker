#include "Game.h"

// constructeur de la classe Game
Game::Game() : window(800, 600, "Brick Breaker"), event(&window) {}

// destructeur de la classe Game
Game::~Game() {
}

// Cette fonction est la boucle principale du jeu
void Game::run()
{
	while (window.isOpen())
	{
		event.handleEvent();
		window.clear();
		window.display();
	}
}

