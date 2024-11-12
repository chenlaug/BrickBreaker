#include <iostream>
#include "Window.h" 
#include "Event.h"
#include "Component.h"
#include "ECSManager.h"

int main()
{
	ECSManager ecsmanager;
	position p;
	p.posX = 10.0f;
	p.posY = 10.0f;
	ecsmanager.addComponent("Player", "Position", p);
	color c;
	c.red = 255.0f;
	c.green = 255.0f;
	c.blue = 0;
	ecsmanager.addComponent("Player", "Color", c);

	position p2 = ecsmanager.getComponent("Player", "Position");
	
	std::cout << "Position: " << ecsmanager.getComponent("Player", "Position") << std::endl;
	return 0;
}