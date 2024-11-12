#pragma once
#include "Window.h"
#include "Event.h"

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	Window window;
	Event event;
};

