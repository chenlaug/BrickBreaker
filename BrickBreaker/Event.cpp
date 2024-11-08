#include "Event.h"
#include <iostream>
#include "Window.h"

Event::Event(Window* window)
{
	this->window = window;
}

void Event::handleEvent()
{
	while (window->pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			window->close();
			break;

		case sf::Event::KeyPressed:
		{
			switch (event.key.code) {
			case sf::Keyboard::Escape:
				window->close();
				break;

			case sf::Keyboard::Right:
				std::cout << "Right" << std::endl;
				// c'est ici qu'on vas rajouter la fonction pour bouger la raquette ->
				break;

			case sf::Keyboard::Left:
				std::cout << "Left" << std::endl;
				// c'est ici qu'on vas rajouter la fonction pour bouger la raquette <-
				break;

			}
		}

		}
	}
