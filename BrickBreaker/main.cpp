#include <iostream>
#include "Window.h" 
#include "Event.h"

int main()
{
	Window window(800, 600, "Brick Breaker");
	Event event(&window);
	while (window.isOpen())
	{
		event.handleEvent();
		window.display();
		window.clear();
	}

	return 0;
}