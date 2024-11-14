#include "Systeme.h"
#include "Event.h"
#include <iostream>
#include "Window.h"

// Constructeur de la classe Event
Event::Event(Window* window, Systeme* systeme) : event()
{
	this->window = window;
	this->systeme = systeme;
}

// Cette fonction permet de gérer les événements de la fenêtre
void Event::handleEvent(float deltaTime)
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
				isMovingRight = true; 
				break;

			case sf::Keyboard::Left:
				isMovingLeft = true; 
				break;

			case sf::Keyboard::Space:
			case sf::Keyboard::Up:
			case sf::Keyboard::Enter:
				systeme->launchBallMain();
				break;

			case sf::Keyboard::F:
			case sf::Keyboard::F11:
				// window->reCreateWindow();
				break;
			}
			break;

		case sf::Event::KeyReleased:
			switch (event.key.code) {
			case sf::Keyboard::Right:
				isMovingRight = false; // La touche "Right" est relâchée
				break;

			case sf::Keyboard::Left:
				isMovingLeft = false; // La touche "Left" est relâchée
				break;
			}
			break;
		}
	}

	// Appliquer les mouvements si les touches sont enfoncées
	if (isMovingRight) {
		systeme->moveRacketRight(deltaTime);
	}
	if (isMovingLeft) {
		systeme->moveRacketLeft(deltaTime);
	}
}
