#pragma once
#include <SFML/Window/Event.hpp>
#include "Window.h"

class Event
{
private:
	sf::Event event;
	Window* window;
	Systeme* systeme;
	bool isMovingRight = false;
	bool isMovingLeft = false;

public:
	Event(Window* window, Systeme* systeme);
	void handleEvent(float deltaTime);
};

