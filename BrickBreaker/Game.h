#pragma once
#include "Window.h"
#include "Event.h"
#include "FPSConter.h"
#include "Systeme.h"

class Game
{
public:
	Game();
	~Game();
	void init();
	void run();

private:
	Window window;
	Event event;
	FPSConter fpsConter;
	ECSManager ecsManager;
	Systeme systeme;
};

