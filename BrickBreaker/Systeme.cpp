#include "Systeme.h"
#include "Component.h"
#include <iostream>

Systeme::Systeme(ECSManager& manager) : ecsManager(manager) {}

Systeme::~Systeme()
{
}

void Systeme::createEntity()
{

	EntityId racket = ecsManager->createEntity();

	ecsManager->addComponent<position>(racket, { 100.0f, 250.0f });
	ecsManager->addComponent<size>(racket, { 100.0f, 20.0f });
	ecsManager->addComponent<color>(racket, { 255, 0, 0, 255 });
	/*ecsManager->addComponent<texture>(racket, "racket.png");*/

	EntityId ball = ecsManager->createEntity();
	ecsManager->addComponent<position>(ball, { 100.0f, 200.0f });
	ecsManager->addComponent<size>(ball, { 20.0f, 20.0f });
	ecsManager->addComponent<color>(ball, { 0, 255, 0, 255 });
	/*ecsManager->addComponent<texture>(ball, "ball.png");*/

	float posX = 0;
	float posY = 0;
	float width = 50.0f;
	float height = 20.0f;
	for (int i = 0; i < 64; i++)
	{
		EntityId brick = ecsManager->createEntity();

		if (window->getSize().x >= (posX + width))
		{
			posX += width;
		}
		else
		{
			posX = 0;
			posY += height;
		}

		ecsManager->addComponent<position>(brick, { posX, posY });
		ecsManager->addComponent<size>(brick, { width, height });

		int red = rand() % 256;
		int green = rand() % 256;
		int blue = rand() % 256;
		ecsManager->addComponent<color>(brick, { red, green, blue, 255 });
		/*ecsManager->addComponent<texture>(brick, "brick.png");*/
	}
}

// change la direction de la balle apres une collision 
void Systeme::onCollision(EntityId e1, EntityId e2)
{
	velocity* velo1 = ecsManager.getComponent<velocity>(e1);
	velocity* velo2 = ecsManager.getComponent<velocity>(e2);

	if (velo1 && velo2)
	{
		velo1->veloY = -velo1->veloY;
		velo2->veloY = -velo2->veloY;
	}
}

// casse la brique et supprime l'entite
void Systeme::brickBreak(EntityId e)
{
	ecsManager.destroyEntity(e);
}

void Systeme::entityMove(EntityId e)
{
	position* pos = ecsManager.getComponent<position>(e);
	velocity* velo = ecsManager.getComponent<velocity>(e);

	if (pos && velo)
	{
		pos->posX += velo->veloX;
		pos->posY += velo->veloY;
	}
}

void Systeme::destroyEntity(EntityId e)
{
	ecsManager.destroyEntity(e);
}
