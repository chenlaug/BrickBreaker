#include "Systeme.h"
#include "Component.h"
#include <iostream>

Systeme::Systeme(ECSManager& manager, Window& win)
	: ecsManager(manager), window(win) {}

Systeme::~Systeme()
{
}

void Systeme::createEntity() {
	float windowWidth = static_cast<float>(window.getSize().x);
	float windowHeight = static_cast<float>(window.getSize().y);

	float racketWidth = windowWidth * 0.1f;
	float racketHeight = windowHeight * 0.03f;
	float racketX = (windowWidth - racketWidth) / 2.0f;
	float racketY = windowHeight - (2 * racketHeight);

	EntityId racket = ecsManager.createEntity();
	ecsManager.addComponent<velocity>(racket, { 100.0f, 0.0f });
	ecsManager.addComponent<position>(racket, { racketX, racketY });
	ecsManager.addComponent<size>(racket, { racketWidth, racketHeight });
	ecsManager.addComponent<color>(racket, { 255, 0, 0, 255 }); // Rouge
	ecsManager.nameEntity("racket", racket);

	float ballSize = windowWidth * 0.02f;
	float ballX = racketX + (racketWidth - ballSize) / 2.0f;
	float ballY = racketY - (1.5f * ballSize);

	EntityId ball = ecsManager.createEntity();
	ecsManager.addComponent<velocity>(ball, { 100.0f, 100.0f });
	ecsManager.addComponent<position>(ball, { ballX, ballY });
	ecsManager.addComponent<size>(ball, { ballSize, ballSize });
	ecsManager.addComponent<color>(ball, { 0, 255, 0, 255 }); // Vert
	ecsManager.nameEntity("ball", ball);

	float brickWidth = windowWidth * 0.1f;
	float brickHeight = windowHeight * 0.04f;
	float spacingX = brickWidth * 0.1f;
	float spacingY = brickHeight * 0.1f;

	float startX = spacingX;
	float startY = spacingY;

	float posX = startX;
	float posY = startY;

	int bricksPerRow = static_cast<int>((windowWidth - startX) / (brickWidth + spacingX));

	for (int i = 0; i < 63; i++) {
		EntityId brick = ecsManager.createEntity();

		ecsManager.addComponent<position>(brick, { posX, posY });
		ecsManager.addComponent<size>(brick, { brickWidth, brickHeight });

		int red = rand() % 256;
		int green = rand() % 256;
		int blue = rand() % 256;
		ecsManager.addComponent<color>(brick, { red, green, blue, 255 });

		// 20% de chance qu'une brique contienne un bonus
		if (rand() % 5 == 0) {
			ecsManager.addComponent<bonus>(brick, { true, "extra_ball" });
		}

		posX += brickWidth + spacingX;
		if (i % bricksPerRow == (bricksPerRow - 1)) {
			posX = startX;
			posY += brickHeight + spacingY;
		}
	}

}

void Systeme::createBonus(EntityId brickId) {
	position* brickPos = ecsManager.getComponent<position>(brickId);
	size* brickSize = ecsManager.getComponent<size>(brickId);

	if (brickPos && brickSize) {
		EntityId bonusEntity = ecsManager.createEntity();

		ecsManager.addComponent<position>(bonusEntity, { brickPos->posX + brickSize->width / 2 - 10.0f, brickPos->posY });
		ecsManager.addComponent<size>(bonusEntity, { 20.0f, 20.0f });
		ecsManager.addComponent<velocity>(bonusEntity, { 0.0f, 150.0f });
		ecsManager.addComponent<color>(bonusEntity, { 255, 255, 0, 255 });
		ecsManager.addComponent<bonus>(bonusEntity, { true, "extra_ball" });

	}
	else {
		std::cerr << "Erreur : Impossible de créer un bonus, composants manquants pour la brique " << brickId << std::endl;
	}
}

// casse la brique et supprime l'entite
void Systeme::brickBreak(EntityId brick)
{
	if (ecsManager.getEntityByName("racket") == brick) {
		std::cerr << "Erreur : Tentative de suppression de la raquette détectée !" << std::endl;
		return;
	}

	std::cout << "Brique détruite : " << brick << std::endl;
	ecsManager.destroyEntity(brick);
}

void Systeme::moveBall(float deltaTime)
{
	EntityId ball = ecsManager.getEntityByName("ball");
	EntityId racket = ecsManager.getEntityByName("racket");
	position* ballPos = ecsManager.getComponent<position>(ball);
	velocity* ballVelo = ecsManager.getComponent<velocity>(ball);
	size* ballSize = ecsManager.getComponent<size>(ball);
	position* racketPos = ecsManager.getComponent<position>(racket);
	size* racketSize = ecsManager.getComponent<size>(racket);

	if (!(ballPos && ballVelo && ballSize && racketPos && racketSize)) {
		std::cerr << "Erreur : Composants manquants pour la balle ou la raquette" << std::endl;
		return;
	}

	if (ballOnRacket) {
		// Si la balle est sur la raquette, positionner la balle au-dessus de la raquette
		ballPos->posX = racketPos->posX + (racketSize->width - ballSize->width) / 2.0f;
		ballPos->posY = racketPos->posY - ballSize->height;
	}
	else {
		// Déplacement de la balle
		ballPos->posX += ballVelo->veloX * deltaTime;
		ballPos->posY += ballVelo->veloY * deltaTime;

		int windowWidth = window.getSize().x;
		int windowHeight = window.getSize().y;

		// Rebondir sur les murs (gauche et droite)
		if (ballPos->posX <= 0 || ballPos->posX + ballSize->width >= windowWidth) {
			ballVelo->veloX = -ballVelo->veloX;
		}

		// Rebondir sur le plafond
		if (ballPos->posY <= 0) {
			ballVelo->veloY = -ballVelo->veloY;
		}

		// Si la balle touche le bas de la fenêtre
		if (ballPos->posY + ballSize->height >= windowHeight) {
			std::cout << "La balle a touche le bas de la fenetre. Reinitialisation." << std::endl;
			ballOnRacket = true; 
			ballVelo->veloX = 0; 
			ballVelo->veloY = 0;
		}
	}
}

void Systeme::moveBonuses(float deltaTime) {
	for (auto e : ecsManager.getEntities()) {
		position* bonusPos = ecsManager.getComponent<position>(e);
		velocity* bonusVelo = ecsManager.getComponent<velocity>(e);
		size* bonusSize = ecsManager.getComponent<size>(e);

		if (bonusPos && bonusVelo && bonusSize) {
	
			bonusPos->posY += bonusVelo->veloY * deltaTime;

			
			if (bonusPos->posY > window.getSize().y) {
				ecsManager.destroyEntity(e);
			}
		}
	}
}

void Systeme::applyBonus(bonus* bonusComp) {
	if (bonusComp->type == "extra_ball") {
		
		EntityId newBall = ecsManager.createEntity();

		EntityId racket = ecsManager.getEntityByName("racket");
		position* racketPos = ecsManager.getComponent<position>(racket);
		size* racketSize = ecsManager.getComponent<size>(racket);

		ecsManager.addComponent<position>(newBall, { racketPos->posX + racketSize->width / 2 - 10.0f, racketPos->posY - 20.0f });
		ecsManager.addComponent<size>(newBall, { 20.0f, 20.0f });
		ecsManager.addComponent<velocity>(newBall, { 150.0f, -200.0f });
		ecsManager.addComponent<color>(newBall, { 0, 255, 255, 255 }); // Couleur cyan
	}
}

void Systeme::launchBall()
{
	if (ballOnRacket) {
		ballOnRacket = false;
		EntityId ball = ecsManager.getEntityByName("ball");
		velocity* ballVelo = ecsManager.getComponent<velocity>(ball);

		if (ballVelo) {
			ballVelo->veloX = 150.0f; 
			ballVelo->veloY = -200.0f; 
		}
	}
}

void Systeme::moveRacketRight(float deltaTime)
{
	EntityId racket = ecsManager.getEntityByName("racket");
	position* racketPos = ecsManager.getComponent<position>(racket);
	velocity* racketVelo = ecsManager.getComponent<velocity>(racket);
	size* racketSize = ecsManager.getComponent<size>(racket);

	if (!(racketPos && racketVelo && racketSize)) {
		std::cerr << "Erreur : Composants manquants pour l'entité 'racket'" << std::endl;
		return;
	}

	racketPos->posX += racketVelo->veloX * deltaTime;


	int windowWidth = window.getSize().x;
	if (racketPos->posX + racketSize->width > windowWidth) {
		racketPos->posX = windowWidth - racketSize->width;
	}
}

void Systeme::moveRacketLeft(float deltaTime)
{
	EntityId racket = ecsManager.getEntityByName("racket");
	position* racketPos = ecsManager.getComponent<position>(racket);
	velocity* racketVelo = ecsManager.getComponent<velocity>(racket);
	size* racketSize = ecsManager.getComponent<size>(racket);

	if (!(racketPos && racketVelo && racketSize)) {
		std::cerr << "Erreur : Composants manquants pour l'entité 'racket'" << std::endl;
		return;
	}

	racketPos->posX -= racketVelo->veloX * deltaTime;

	if (racketPos->posX < 0) {
		racketPos->posX = 0;
	}
}

void Systeme::renderEntity(EntityId e, sf::RenderWindow& window)
{
	position* pos = ecsManager.getComponent<position>(e);
	size* s = ecsManager.getComponent<size>(e);
	color* c = ecsManager.getComponent<color>(e);

	if (pos && s && c) {
		if (ecsManager.getEntityByName("ball") == e) {
			sf::CircleShape circle(s->width / 2.0f);
			circle.setPosition(pos->posX, pos->posY);
			circle.setFillColor(sf::Color(c->red, c->green, c->blue, c->alpha));
			window.draw(circle);
		}
		else {
			sf::RectangleShape rect;
			rect.setSize(sf::Vector2f(s->width, s->height));
			rect.setPosition(pos->posX, pos->posY);
			rect.setFillColor(sf::Color(c->red, c->green, c->blue, c->alpha));
			window.draw(rect);
		}
	}
}

void Systeme::checkBallBrickCollision() {
	EntityId ball = ecsManager.getEntityByName("ball");
	position* ballPos = ecsManager.getComponent<position>(ball);
	velocity* ballVelo = ecsManager.getComponent<velocity>(ball);
	size* ballSize = ecsManager.getComponent<size>(ball);

	if (!(ballPos && ballVelo && ballSize)) {
		std::cerr << "Erreur : Composants manquants pour la balle" << std::endl;
		return;
	}

	for (auto e : ecsManager.getEntities()) {

		if (e == ball || e == ecsManager.getEntityByName("racket")) {
			continue;
		}

		position* brickPos = ecsManager.getComponent<position>(e);
		size* brickSize = ecsManager.getComponent<size>(e);
		bonus* brickBonus = ecsManager.getComponent<bonus>(e); 

		if (brickPos && brickSize) {
			bool collisionX = ballPos->posX + ballSize->width > brickPos->posX &&
				ballPos->posX < brickPos->posX + brickSize->width;

			bool collisionY = ballPos->posY + ballSize->height > brickPos->posY &&
				ballPos->posY < brickPos->posY + brickSize->height;

			if (collisionX && collisionY) {
				float ballCenterX = ballPos->posX + ballSize->width / 2;
				float ballCenterY = ballPos->posY + ballSize->height / 2;
				float brickCenterX = brickPos->posX + brickSize->width / 2;
				float brickCenterY = brickPos->posY + brickSize->height / 2;

				float dx = ballCenterX - brickCenterX;
				float dy = ballCenterY - brickCenterY;

				if (std::abs(dx) > std::abs(dy)) {
					ballVelo->veloX = -ballVelo->veloX;
				}
				else {
					ballVelo->veloY = -ballVelo->veloY;
				}

				if (brickBonus && brickBonus->active) {
					createBonus(e);
				}

				brickBreak(e);

				break;
			}
		}
	}
}

void Systeme::checkBallRacketCollision()
{
	EntityId ball = ecsManager.getEntityByName("ball");
	EntityId racket = ecsManager.getEntityByName("racket");

	position* ballPos = ecsManager.getComponent<position>(ball);
	size* ballSize = ecsManager.getComponent<size>(ball);
	velocity* ballVelo = ecsManager.getComponent<velocity>(ball);

	position* racketPos = ecsManager.getComponent<position>(racket);
	size* racketSize = ecsManager.getComponent<size>(racket);

	if (ballPos && ballSize && ballVelo && racketPos && racketSize) {
		bool collisionX = ballPos->posX + ballSize->width > racketPos->posX &&
			ballPos->posX < racketPos->posX + racketSize->width;

		bool collisionY = ballPos->posY + ballSize->height > racketPos->posY &&
			ballPos->posY < racketPos->posY + racketSize->height;

		if (collisionX && collisionY) {
			ballVelo->veloY = -std::abs(ballVelo->veloY); 
		}
	}
}

void Systeme::checkBonusCollision() {
	EntityId racket = ecsManager.getEntityByName("racket");
	position* racketPos = ecsManager.getComponent<position>(racket);
	size* racketSize = ecsManager.getComponent<size>(racket);

	if (!racketPos || !racketSize) {
		std::cerr << "Erreur : Composants manquants pour la raquette !" << std::endl;
		return;
	}

	for (auto e : ecsManager.getEntities()) {
		position* bonusPos = ecsManager.getComponent<position>(e);
		size* bonusSize = ecsManager.getComponent<size>(e);
		bonus* bonusComp = ecsManager.getComponent<bonus>(e);

		if (bonusPos && bonusSize && bonusComp) {


			bool collisionX = bonusPos->posX + bonusSize->width > racketPos->posX &&
				bonusPos->posX < racketPos->posX + racketSize->width;

			bool collisionY = bonusPos->posY + bonusSize->height > racketPos->posY &&
				bonusPos->posY < racketPos->posY + racketSize->height;

			if (collisionX && collisionY) {

				applyBonus(bonusComp);

				ecsManager.destroyEntity(e);
			}
		}
	}
}


void Systeme::destroyEntity(EntityId e)
{
	ecsManager.destroyEntity(e);
}
