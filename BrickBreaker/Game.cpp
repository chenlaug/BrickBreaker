#include "Game.h"
#include "Component.h"
#include <iostream>

// constructeur de la classe Game
Game::Game() : window(800, 600, "Brick Breaker"), event(&window, &systeme), systeme(ecsManager, window) {}

// destructeur de la classe Game
Game::~Game() {
}

// Cette fonction initialise tout ce que le jeu a besoin pour fonctionner
void Game::init()
{
	fpsConter.init();
	systeme.createEntity();

}

// Cette fonction gère la logique du jeu
void Game::functionality(float deltaTime) {
	systeme.moveBall(deltaTime);
	systeme.moveBonuses(deltaTime); 
	systeme.checkBonusCollision();
	systeme.checkBallBrickCollision();
	systeme.checkBallRacketCollision();
}


// Cette fonction est la boucle principale du jeu
void Game::run()
{
	init();
	while (window.isOpen()) {
		event.handleEvent(fpsConter.getDeltaTime());
		functionality(fpsConter.getDeltaTime());
		fpsConter.update();
		window.clear();


		for (auto e : ecsManager.getEntities()) {
			systeme.renderEntity(e, window.getRenderWindow());
		}


		window.draw(fpsConter.getText());
		// Afficher la fenêtre
		window.display();
	}
}

