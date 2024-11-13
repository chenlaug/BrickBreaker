#pragma once
#include "ECSManager.h"
#include "Window.h"

class Systeme
{
private:
	ECSManager& ecsManager;
	Window& window;
public:
	Systeme(ECSManager& manager, Window& win); 
	~Systeme();

	void createEntity();
	void onCollision(EntityId e1, EntityId e2);
	void brickBreak(EntityId e);
	void moveBall(float deltaTime);
	void moveRacketRight(float deltaTime);
	void moveRacketLeft(float deltaTime);
	void renderEntity(EntityId e, sf::RenderWindow& window);
	void checkBallBrickCollision();
	void destroyEntity(EntityId e);
};
