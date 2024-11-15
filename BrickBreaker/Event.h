#pragma once
#include <SFML/Window/Event.hpp>
#include "Window.h"
#include "GameState.h"

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
	void handleEvent(float deltaTime, GameState& currentState);
};

