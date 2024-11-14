#pragma once
#include "ECSManager.h"
#include "Window.h"
#include "Component.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Systeme {
private:
	ECSManager& ecsManager;
	Window& window;
	bool ballAttachedToRacket = true;

public:
	Systeme(ECSManager& manager, Window& win);
	~Systeme();

	// Initialisation des entités
	void createEntity();


	// Logique du jeu
	void moveBallMain(float deltaTime);
	void moveBallBonus(float deltaTime);
	void moveBonuses(float deltaTime);
	void checkBallBrickCollision();
	void checkBallRacketCollision();
	void checkBonusCollision();
	void checkBonusRacketCollision();

	// Rendu
	void renderEntity(EntityId entity, sf::RenderWindow& renderWindow);


	// Actions de jeu
	void launchBallMain();
	void moveRacketLeft(float deltaTime);
	void moveRacketRight(float deltaTime);
	void applyBonus(Bonus* bonusComp, EntityId entity);
	void limitBallSpeed(EntityId ball, float maxSpeed);
};
