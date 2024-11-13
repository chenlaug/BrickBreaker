#include "Game.h"
#include "Component.h"
#include <iostream>

// constructeur de la classe Game
Game::Game() : window(800, 600, "Brick Breaker"), event(&window), systeme(ecsManager,window) {}

// destructeur de la classe Game
Game::~Game() {
}

// Cette fonction initialise tout ce que le jeu a besoin pour fonctionner
void Game::init()
{
	fpsConter.init();
	systeme.createEntity();

}


void Game::run()
{
	init();
	while (window.isOpen()) {
		event.handleEvent();
		window.clear();
		fpsConter.display();


		// Rendu graphique des entités
		for (auto e : ecsManager.getEntities()) {
			// Récupérer les composants de l'entité
			position* pos = ecsManager.getComponent<position>(e);
			size* s = ecsManager.getComponent<size>(e);
			color* c = ecsManager.getComponent<color>(e);

			if (pos && s && c) { // Vérifie que tous les composants nécessaires sont présents
				sf::RectangleShape rect;
				rect.setSize(sf::Vector2f(s->width, s->height));     // Taille
				rect.setPosition(pos->posX, pos->posY);              // Position
				rect.setFillColor(sf::Color(c->red, c->green, c->blue, c->alpha)); // Couleur

				window.draw(rect); // Dessiner le rectangle
			}
		}
		window.draw(fpsConter.getText());
		// Afficher la fenêtre
		window.display();
	}
}

