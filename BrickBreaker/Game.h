#pragma once
#include "Window.h"
#include "Event.h"
#include "FPSConter.h"

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	Window window;
	Event event;
	FPSConter fpsConter;
};

