#include "Systeme.h"
#include "Component.h"
#include <iostream>

Systeme::Systeme(ECSManager& manager, Window& win)
	: ecsManager(manager), window(win) {}

Systeme::~Systeme() {}

// Fonction pour creer les entites
void Systeme::createEntity() {
	float windowWidth = static_cast<float>(window.getSize().x);
	float windowHeight = static_cast<float>(window.getSize().y);

	EntityId racket = ecsManager.createEntity();
	ecsManager.addComponent<Position>(racket, { windowWidth / 2 - 50.0f, windowHeight - 20.0f });
	ecsManager.addComponent<Size>(racket, { 100.0f, 10.0f });
	ecsManager.addComponent<Color>(racket, { 255, 0, 0, 255 });
	ecsManager.addComponent<Racket>(racket, { 300.0f });

	auto racketShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(100.0f, 10.0f));
	racketShape->setPosition(windowWidth / 2 - 50.0f, windowHeight - 20.0f);
	racketShape->setFillColor(sf::Color(255, 0, 0, 255));
	ecsManager.addComponent<RenderShape>(racket, { racketShape });
	ecsManager.nameEntity("racket", racket);

	EntityId ballMain = ecsManager.createEntity();
	ecsManager.addComponent<Position>(ballMain, { windowWidth / 2 - 5.0f, windowHeight - 30.0f });
	ecsManager.addComponent<Size>(ballMain, { 10.0f, 10.0f });
	ecsManager.addComponent<Color>(ballMain, { 0, 255, 0, 255 });
	ecsManager.addComponent<Velocity>(ballMain, { 0.0f, 0.0f });
	ecsManager.addComponent<Ball>(ballMain, { true });

	auto ballShape = std::make_shared<sf::CircleShape>(5.0f);
	ballShape->setPosition(windowWidth / 2 - 5.0f, windowHeight - 30.0f);
	ballShape->setFillColor(sf::Color(0, 255, 0, 255));
	ecsManager.addComponent<RenderShape>(ballMain, { ballShape });
	ecsManager.nameEntity("ballMain", ballMain);

	float brickWidth = 80.0f, brickHeight = 30.0f, spacing = 10.0f;
	int rows = 5, cols = 10;

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			EntityId brick = ecsManager.createEntity();

			float brickX = col * (brickWidth + spacing);
			float brickY = row * (brickHeight + spacing);
			ecsManager.addComponent<Position>(brick, { brickX, brickY });
			ecsManager.addComponent<Size>(brick, { brickWidth, brickHeight });

			// ecsManager.addComponent<Color>(brick, { rand() % 256, rand() % 256, rand() % 256, 255 });

			int health = 1 + rand() % 3;
			ecsManager.addComponent<Brick>(brick, { health });

			if (rand() % 2 == 0) {
				std::string bonusType = (rand() % 2 == 0) ? "extra_ball" : "big_racket";
				ecsManager.addComponent<Bonus>(brick, { bonusType, true });
			}

			auto brickShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(brickWidth, brickHeight));
			brickShape->setPosition(brickX, brickY);

			ecsManager.addComponent<RenderShape>(brick, { brickShape });
			updateBrickColor(brick);

		}
	}
}

// Fonction pour deplace la balle principale
void Systeme::moveBallMain(float deltaTime) {
	auto ballMain = ecsManager.getEntityByName("ballMain");
	auto racket = ecsManager.getEntityByName("racket");

	auto ballPos = ecsManager.getComponent<Position>(ballMain);
	auto ballVelo = ecsManager.getComponent<Velocity>(ballMain);
	auto ballSize = ecsManager.getComponent<Size>(ballMain);

	auto racketPos = ecsManager.getComponent<Position>(racket);
	auto racketSize = ecsManager.getComponent<Size>(racket);

	if (!ballPos || !ballVelo || !ballSize || !racketPos || !racketSize) return;

	if (ballAttachedToRacket) {
		ballPos->x = racketPos->x + racketSize->width / 2 - ballSize->width / 2;
		ballPos->y = racketPos->y - ballSize->height;

		auto ballShape = ecsManager.getComponent<RenderShape>(ballMain);
		if (ballShape) {
			ballShape->shape->setPosition(ballPos->x, ballPos->y);
		}
	}
	else {
		ballPos->x += ballVelo->x * deltaTime;
		ballPos->y += ballVelo->y * deltaTime;

		int windowWidth = window.getSize().x;
		int windowHeight = window.getSize().y;

		if (ballPos->x <= 0 || ballPos->x + ballSize->width >= windowWidth) {
			ballVelo->x = -ballVelo->x;
		}
		if (ballPos->y <= 0) {
			ballVelo->y = -ballVelo->y;
		}

		if (ballPos->y > windowHeight) {
			loseLife();
			std::cout << "Ball missed! Resetting ball to racket." << std::endl;
			ballAttachedToRacket = true;
			ballVelo->x = 0.0f;
			ballVelo->y = 0.0f;
		}

		auto ballShape = ecsManager.getComponent<RenderShape>(ballMain);
		if (ballShape) {
			ballShape->shape->setPosition(ballPos->x, ballPos->y);
		}
	}
}

// Fonction pour deplace la balle bonus
void Systeme::moveBallBonus(float deltaTime) {
	for (auto ball : ecsManager.getEntities()) {
		if (!ecsManager.hasComponent<Ball>(ball)) continue;

		auto ballComp = ecsManager.getComponent<Ball>(ball);
		if (ballComp->isMain) continue;

		auto ballPos = ecsManager.getComponent<Position>(ball);
		auto ballVelo = ecsManager.getComponent<Velocity>(ball);
		auto ballSize = ecsManager.getComponent<Size>(ball);

		if (!ballPos || !ballVelo || !ballSize) continue;

		ballPos->x += ballVelo->x * deltaTime;
		ballPos->y += ballVelo->y * deltaTime;

		int windowWidth = window.getSize().x;
		int windowHeight = window.getSize().y;

		if (ballPos->x <= 0 || ballPos->x + ballSize->width >= windowWidth) {
			ballVelo->x = -ballVelo->x;
		}
		if (ballPos->y <= 0) {
			ballVelo->y = -ballVelo->y;
		}

		auto ballShape = ecsManager.getComponent<RenderShape>(ball);
		if (ballShape) {
			ballShape->shape->setPosition(ballPos->x, ballPos->y);
		}

		if (ballPos->y > windowHeight) {
			std::cout << "Bonus ball " << ball << " removed after missing." << std::endl;
			ecsManager.destroyEntity(ball);
		}
	}
}

// Fonction pour deplace les bonus
void Systeme::moveBonuses(float deltaTime) {
	for (auto entity : ecsManager.getEntities()) {
		if (ecsManager.hasComponent<Bonus>(entity)) {
			auto pos = ecsManager.getComponent<Position>(entity);
			auto velo = ecsManager.getComponent<Velocity>(entity);
			auto shape = ecsManager.getComponent<RenderShape>(entity);

			if (pos && velo && shape) {
				pos->y += velo->y * deltaTime;

				shape->shape->setPosition(pos->x, pos->y);

				if (pos->y > window.getSize().y) {
					ecsManager.destroyEntity(entity);
				}
			}
		}
	}
}

// Fonction pour verifier les collisions avec les briques
void Systeme::checkBallBrickCollision() {
	std::vector<EntityId> bricksToDestroy;

	for (auto ball : ecsManager.getEntities()) {
		if (!ecsManager.hasComponent<Ball>(ball)) continue;

		auto ballShape = ecsManager.getComponent<RenderShape>(ball);
		auto ballVelo = ecsManager.getComponent<Velocity>(ball);

		if (!ballShape || !ballVelo) continue;

		for (auto brick : ecsManager.getEntities()) {
			if (!ecsManager.hasComponent<Brick>(brick)) continue;

			auto brickShape = ecsManager.getComponent<RenderShape>(brick);
			auto brickComp = ecsManager.getComponent<Brick>(brick);
			auto bonusComp = ecsManager.getComponent<Bonus>(brick);

			if (!brickShape || !brickComp) continue;

			if (ballShape->shape->getGlobalBounds().intersects(brickShape->shape->getGlobalBounds())) {
				std::cout << "Collision detected between ball and brick " << brick << std::endl;

				sf::FloatRect ballBounds = ballShape->shape->getGlobalBounds();
				sf::FloatRect brickBounds = brickShape->shape->getGlobalBounds();

				float ballCenterX = ballBounds.left + ballBounds.width / 2;
				float ballCenterY = ballBounds.top + ballBounds.height / 2;

				float brickCenterX = brickBounds.left + brickBounds.width / 2;
				float brickCenterY = brickBounds.top + brickBounds.height / 2;

				float dx = ballCenterX - brickCenterX;
				float dy = ballCenterY - brickCenterY;

				float overlapX = (brickBounds.width / 2 + ballBounds.width / 2) - std::abs(dx);
				float overlapY = (brickBounds.height / 2 + ballBounds.height / 2) - std::abs(dy);

				if (overlapX < overlapY) {
					ballVelo->x = -ballVelo->x;
					std::cout << "Horizontal collision with brick " << brick << std::endl;
				}
				else {
					ballVelo->y = -ballVelo->y;
					std::cout << "Vertical collision with brick " << brick << std::endl;
				}

				brickComp->health -= 1;
				updateBrickColor(brick);
				std::cout << "Brick " << brick << " health reduced to " << brickComp->health << std::endl;

				if (brickComp->health <= 0 && bonusComp && bonusComp->active) {
					EntityId bonus = ecsManager.createEntity();

					ecsManager.addComponent<Position>(bonus, { brickShape->shape->getPosition().x, brickShape->shape->getPosition().y });
					ecsManager.addComponent<Size>(bonus, { 20.0f, 20.0f });
					ecsManager.addComponent<Velocity>(bonus, { 0.0f, 100.0f });
					ecsManager.addComponent<Color>(bonus, { 255, 255, 0, 255 });
					ecsManager.addComponent<Bonus>(bonus, { bonusComp->type, true });

					auto bonusShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(20.0f, 20.0f));
					bonusShape->setPosition(brickShape->shape->getPosition().x, brickShape->shape->getPosition().y);
					bonusShape->setFillColor(sf::Color(255, 255, 0, 255));
					ecsManager.addComponent<RenderShape>(bonus, { bonusShape });

					std::cout << "Bonus created at position (" << brickShape->shape->getPosition().x << ", " << brickShape->shape->getPosition().y << ") with type " << bonusComp->type << std::endl;
				}


				if (brickComp->health <= 0) {
					bricksToDestroy.push_back(brick);
				}

				break;
			}
		}
	}

	for (auto brick : bricksToDestroy) {
		ecsManager.destroyEntity(brick);
		std::cout << "Brick " << brick << " destroyed." << std::endl;
	}
}

// Fonction pour verifier les collisions avec la raquette
void Systeme::checkBallRacketCollision() {
	auto racket = ecsManager.getEntityByName("racket");

	auto racketShape = ecsManager.getComponent<RenderShape>(racket);
	if (!racketShape) {
		std::cerr << "Error: Racket shape is missing!" << std::endl;
		return;
	}

	for (auto ball : ecsManager.getEntities()) {
		if (!ecsManager.hasComponent<Ball>(ball)) continue;

		auto ballShape = ecsManager.getComponent<RenderShape>(ball);
		auto ballVelo = ecsManager.getComponent<Velocity>(ball);

		if (!ballShape || !ballVelo) continue;

		if (ballShape->shape->getGlobalBounds().intersects(racketShape->shape->getGlobalBounds())) {
			std::cout << "Collision detected between ball " << ball << " and racket!" << std::endl;

			ballVelo->y = -std::abs(ballVelo->y);

			float ballCenterX = ballShape->shape->getPosition().x + ballShape->shape->getGlobalBounds().width / 2;
			float racketCenterX = racketShape->shape->getPosition().x + racketShape->shape->getGlobalBounds().width / 2;
			float impactOffset = (ballCenterX - racketCenterX) / (racketShape->shape->getGlobalBounds().width / 2);

			ballVelo->x += impactOffset * 200.0f;


			if (std::abs(ballVelo->x) > 400.0f) {
				ballVelo->x = (ballVelo->x > 0 ? 400.0f : -400.0f);
			}
		}
	}
}

// Fonction pour verifier les collisions avec les bonus
void Systeme::checkBonusCollision() {
	auto racket = ecsManager.getEntityByName("racket");
	auto racketShape = ecsManager.getComponent<RenderShape>(racket);

	for (auto bonus : ecsManager.getEntities()) {
		if (!ecsManager.hasComponent<Bonus>(bonus)) continue;

		auto bonusShape = ecsManager.getComponent<RenderShape>(bonus);
		auto bonusComp = ecsManager.getComponent<Bonus>(bonus);

		if (bonusShape && racketShape && bonusComp) {
			if (bonusShape->shape->getGlobalBounds().intersects(racketShape->shape->getGlobalBounds())) {
				applyBonus(bonusComp, racket);
				ecsManager.destroyEntity(bonus);
			}
		}
	}
}

// Fonction pour verifier les collisions avec la raquette et les bonus
void Systeme::checkBonusRacketCollision() {
	auto racket = ecsManager.getEntityByName("racket");

	auto racketShape = ecsManager.getComponent<RenderShape>(racket);
	auto racketPos = ecsManager.getComponent<Position>(racket);
	auto racketSize = ecsManager.getComponent<Size>(racket);

	if (!racketShape || !racketPos || !racketSize) {
		std::cerr << "Error: Racket components are missing!" << std::endl;
		return;
	}

	for (auto entity : ecsManager.getEntities()) {
		if (!ecsManager.hasComponent<Bonus>(entity)) continue;

		auto bonusShape = ecsManager.getComponent<RenderShape>(entity);
		auto bonusPos = ecsManager.getComponent<Position>(entity);
		auto bonusComp = ecsManager.getComponent<Bonus>(entity);

		if (!bonusShape || !bonusPos || !bonusComp) continue;

		if (bonusShape->shape->getGlobalBounds().intersects(racketShape->shape->getGlobalBounds())) {
			std::cout << "Bonus " << entity << " caught by racket!" << std::endl;

			applyBonus(bonusComp, entity);
			ecsManager.destroyEntity(entity);
		}
	}
}

int Systeme::getLifePoint()
{
	return this->lifePoint;	
}

void Systeme::loseLife()
{
	std::cout << "Life lost!" << std::endl;
	this->lifePoint--;
}

// fonction pour rendre les entites
void Systeme::renderEntity(EntityId entity, sf::RenderWindow& renderWindow) {
	auto shape = ecsManager.getComponent<RenderShape>(entity);
	if (shape) {
		renderWindow.draw(*shape->shape);
	}
}

// fonction pour lance la balle principale aleatoirement quand on appuie sur la touche espace etc
void Systeme::launchBallMain() {
	if (ballAttachedToRacket) {
		auto ballMain = ecsManager.getEntityByName("ballMain");
		auto ballVelo = ecsManager.getComponent<Velocity>(ballMain);

		if (ballVelo) {
			ballVelo->x = static_cast<float>(rand() % 201 - 100);

			ballVelo->y = static_cast<float>(-(100 + rand() % 101));

			if (std::abs(ballVelo->x) < 30) {
				ballVelo->x += (ballVelo->x < 0 ? -30 : 30);
			}
		}
		ballAttachedToRacket = false;
	}
}

// fonction pour deplace la raquette a gauche
void Systeme::moveRacketLeft(float deltaTime) {
	auto racket = ecsManager.getEntityByName("racket");
	auto pos = ecsManager.getComponent<Position>(racket);
	auto velo = ecsManager.getComponent<Racket>(racket);
	auto size = ecsManager.getComponent<Size>(racket);
	auto shape = ecsManager.getComponent<RenderShape>(racket);

	if (pos && velo && size && shape) {
		pos->x -= velo->speed * deltaTime;

		if (pos->x < 0) {
			pos->x = 0;
		}

		shape->shape->setPosition(pos->x, pos->y);
	}
}

// fonction pour deplace la raquette a droite
void Systeme::moveRacketRight(float deltaTime) {
	auto racket = ecsManager.getEntityByName("racket");
	auto pos = ecsManager.getComponent<Position>(racket);
	auto velo = ecsManager.getComponent<Racket>(racket);
	auto size = ecsManager.getComponent<Size>(racket);
	auto shape = ecsManager.getComponent<RenderShape>(racket);

	if (pos && velo && size && shape) {
		pos->x += velo->speed * deltaTime;

		if (pos->x + size->width > window.getSize().x) {
			pos->x = window.getSize().x - size->width;
		}

		shape->shape->setPosition(pos->x, pos->y);
	}
}

// fonction pour appliquer les bonus
void Systeme::applyBonus(Bonus* bonusComp, EntityId entity) {
	if (bonusComp->type == "extra_ball") {
		std::cout << "Applying bonus: extra ball" << std::endl;

		EntityId newBall = ecsManager.createEntity();

		auto racket = ecsManager.getEntityByName("racket");
		auto racketPos = ecsManager.getComponent<Position>(racket);
		auto racketSize = ecsManager.getComponent<Size>(racket);

		ecsManager.addComponent<Position>(newBall, { racketPos->x + racketSize->width / 2 - 5.0f, racketPos->y - 10.0f });
		ecsManager.addComponent<Size>(newBall, { 10.0f, 10.0f });
		ecsManager.addComponent<Color>(newBall, { 0, 255, 255, 255 });
		ecsManager.addComponent<Velocity>(newBall, { 150.0f, -200.0f });
		ecsManager.addComponent<Ball>(newBall, { false });

		auto ballShape = std::make_shared<sf::CircleShape>(5.0f);
		ballShape->setPosition(racketPos->x + racketSize->width / 2 - 5.0f, racketPos->y - 10.0f);
		ballShape->setFillColor(sf::Color(0, 255, 255, 255));
		ecsManager.addComponent<RenderShape>(newBall, { ballShape });

		std::cout << "Extra ball created!" << std::endl;
	}
	else if (bonusComp->type == "big_racket") {
		std::cout << "Applying bonus: big racket" << std::endl;

		auto racket = ecsManager.getEntityByName("racket");
		auto racketSize = ecsManager.getComponent<Size>(racket);
		auto racketShape = ecsManager.getComponent<RenderShape>(racket);

		if (racketSize && racketShape) {
			racketSize->width += 20.0f;

			auto rectShape = std::dynamic_pointer_cast<sf::RectangleShape>(racketShape->shape);
			if (rectShape) {
				rectShape->setSize(sf::Vector2f(racketSize->width, racketSize->height));
			}
		}
	}
}

// fonction pour verifier les collisions avec les murs
void Systeme::limitBallSpeed(EntityId ball, float maxSpeed) {
	auto ballVelo = ecsManager.getComponent<Velocity>(ball);
	if (ballVelo) {
		float speed = std::sqrt(ballVelo->x * ballVelo->x + ballVelo->y * ballVelo->y);
		if (speed > maxSpeed) {
			float scale = maxSpeed / speed;
			ballVelo->x *= scale;
			ballVelo->y *= scale;
		}
	}
}

// fonction pour mettre a jour la couleur des briques
void Systeme::updateBrickColor(EntityId brick) {
	auto brickComp = ecsManager.getComponent<Brick>(brick);
	auto renderShape = ecsManager.getComponent<RenderShape>(brick);

	if (!brickComp) {
		std::cerr << "Error: Missing Brick component for entity " << brick << std::endl;
	}
	if (!renderShape) {
		std::cerr << "Error: Missing RenderShape component for entity " << brick << std::endl;
	}

	if (!brickComp || !renderShape) return;

	// Mise à jour de la couleur
	sf::Color newColor;
	switch (brickComp->health) {
	case 3:
		newColor = sf::Color(0, 255, 0);
		break;
	case 2:
		newColor = sf::Color(255, 165, 0);
		break;
	case 1:
		newColor = sf::Color(255, 0, 0);
		break;
	default:
		newColor = sf::Color(128, 128, 128);
		break;
	}
	renderShape->shape->setFillColor(newColor);
}

void Systeme::resetGame() {
	setLifePoint(3);
	std::cout << "Game reset!" << std::endl;
	std::cout << "Life points: " << this->lifePoint << std::endl;
	ecsManager.clearEntities();
	createEntity();
	ballAttachedToRacket = true;
}

void Systeme::setLifePoint(int lifePoint)
{
	this->lifePoint = lifePoint;
}