#include <iostream>
#include "Window.h" 

int main()
{
	Window window(800, 600, "Brick Breaker");

	while (window.isOpen())
	{
		while (window.pollEvent()) {
		}
		std::cout << window.getSize().x << " X " << window.getSize().y << std::endl;
	}

	return 0;
}