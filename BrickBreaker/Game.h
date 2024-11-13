#pragma once
#include "Window.h"
#include "Systeme.h"
#include "Event.h"
#include "FPSConter.h"

class Game
{
public:
	Game();
	~Game();
	void init();
	void functionality();
	void run();

private:
	Window window;
	Event event;
	FPSConter fpsConter;
	ECSManager ecsManager;
	Systeme systeme;
};

