#pragma once
#include "ECSManager.h"
#include "Window.h"

class Systeme
{
private:
	ECSManager* ecsManager;
	Window* window;

public:
	Systeme() = default;
	~Systeme();

	void createEntity();
	void onCollision(EntityId e1, EntityId e2);
	void brickBreak(EntityId e);
	void entityMove(EntityId e);
	void destroyEntity(EntityId e);
};
