#include "Systeme.h"
#include "Event.h"
#include <iostream>
#include "Window.h"

// Constructeur de la classe Event
Event::Event(Window* window, Systeme* systeme)
{
	this->window = window;
	this->systeme = systeme;
}

// Cette fonction permet de gérer les événements de la fenêtre
void Event::handleEvent()
{
	while (window->pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			window->close();
			break;

		case sf::Event::KeyPressed:

			switch (event.key.code) {
			case sf::Keyboard::Escape:
				window->close();
				break;

			case sf::Keyboard::Right:
				std::cout << "Right" << std::endl;
				systeme->moveRacketRight();
				// c'est ici qu'on vas rajouter la fonction pour bouger la raquette ->
				break;

			case sf::Keyboard::Left:
				std::cout << "Left" << std::endl;
				// c'est ici qu'on vas rajouter la fonction pour bouger la raquette <-
				break;
			case sf::Keyboard::F:
			case sf::Keyboard::F11:
				// Mettre en plein écran ou en fenêtré selon l'état actuel de la fenêtre avec F ou F11
				window->toggleFullscreen();
				break;
			}
		}
	}
}