#pragma once
#include "ECSManager.h"
#include "Window.h"
#include "Component.h" 


class Systeme
{
private:
	ECSManager& ecsManager;
	Window& window;
	bool ballOnRacket = true;

public:
	Systeme(ECSManager& manager, Window& win); 
	~Systeme();

	void createEntity();
	void createBonus(EntityId brickId);
	void onCollision(EntityId e1, EntityId e2);
	void brickBreak(EntityId e);
	void moveBall(float deltaTime);
	void moveBonuses(float deltaTime);
	void applyBonus(bonus* bonusComp);
	void moveRacketRight(float deltaTime);
	void moveRacketLeft(float deltaTime);
	void renderEntity(EntityId e, sf::RenderWindow& window);
	void checkBallBrickCollision();
	void checkBallRacketCollision();
	void checkBonusCollision();
	void destroyEntity(EntityId e);
	void launchBall();
};
