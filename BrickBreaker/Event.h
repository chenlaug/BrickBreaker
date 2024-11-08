#pragma once
#include <SFML/Window/Event.hpp>
#include "Window.h"

class Event
{
private:
	sf::Event event;
	Window* window;

public:
	Event(Window* window); 
	void handleEvent();
};

