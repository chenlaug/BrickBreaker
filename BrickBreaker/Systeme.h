#pragma once
#include "ECSManager.h"

class Systeme
{
private:
	ECSManager* ecsManager;
public:
	Systeme();
	~Systeme();

	void createEntity();
	void onCollision(EntityId e1, EntityId e2);
	void brickBreak(EntityId e);
	void entityMove(EntityId e);
	void destroyEntity(EntityId e);
};
