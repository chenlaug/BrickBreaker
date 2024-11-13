#pragma once
#include <SFML/Window/Event.hpp>
#include "Window.h"

class Event
{
private:
	sf::Event event;
	Window* window;
	Systeme* systeme;

public:
	Event(Window* window, Systeme* systeme);
	void handleEvent();
};

