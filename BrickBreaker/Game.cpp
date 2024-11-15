#include "Game.h"
#include "Component.h"
#include "Menu.h"
#include <iostream>
#include <ctime>

// constructeur de la classe Game
Game::Game() : window(800, 600, "Brick Breaker"), event(&window, &systeme), systeme(ecsManager, window) {
	srand(static_cast<unsigned int>(time(0)));
}

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
	systeme.moveBallMain(deltaTime);
	systeme.moveBallBonus(deltaTime);
	systeme.moveBonuses(deltaTime);
	systeme.checkBonusCollision();
	systeme.checkBallBrickCollision();
	systeme.checkBallRacketCollision();
}

void Game::run() {
	init();

	// Ajoutez une instance du menu
	Menu menu(window, systeme);
	menu.init();
	GameState currentState = GameState::Menu;

	while (window.isOpen()) {
		switch (currentState) {
		case GameState::Menu: {
			// Gestion des événements via le menu
			menu.handleInput();
			menu.display();

			// Gestion de la sélection dans le menu
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				int selectedOption = menu.getSelectedOption();
				if (selectedOption == 0 && systeme.getLifePoint() == 0) {
					currentState = GameState::Restart; // Restart le jeu
				}
				else if (selectedOption == 0) {
					currentState = GameState::Playing; // Démarrer le jeu
				}
				else if (selectedOption == 1) {
					currentState = GameState::Options; // Aller dans les options
				}
				else if (selectedOption == 2) {
					window.close(); // Quitter
				}
			}
			break;
		}

		case GameState::Playing: {
			// Gestion des événements dans l'état de jeu
			event.handleEvent(fpsConter.getDeltaTime(), currentState);
			functionality(fpsConter.getDeltaTime());
			fpsConter.update();
			fpsConter.updateLife(systeme.getLifePoint());

			// Rendu du jeu
			window.clear();
			window.drawBackground();

			for (auto e : ecsManager.getEntities()) {
				systeme.renderEntity(e, window.getRenderWindow());
			}

			window.draw(fpsConter.getTextLife());
			window.draw(fpsConter.getText());
			window.display();

			if (systeme.getLifePoint() == 0)
			{
				menu.init();
				currentState = GameState::Menu;
			}
			break;
		}

		case GameState::Restart: {
			systeme.resetGame();
			currentState = GameState::Playing;
			break;
		}

		case GameState::Options: {
			// Afficher les options
			std::cout << "Options en construction..." << std::endl;

			// Retour au menu pour l'instant
			currentState = GameState::Menu;
			break;
		}

		}
	}
}