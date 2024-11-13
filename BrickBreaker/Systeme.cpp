#include "Systeme.h"
#include "Component.h"
#include <iostream>

Systeme::Systeme(ECSManager& manager, Window& win)
	: ecsManager(manager), window(win) {}

Systeme::~Systeme()
{
}

void Systeme::createEntity() {
	// Récupérer la taille de la fenêtre
	float windowWidth = static_cast<float>(window.getSize().x);
	float windowHeight = static_cast<float>(window.getSize().y);

	// Création de la raquette (centrée en bas)
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

	// Création de la balle (au-dessus de la raquette)
	float ballSize = windowWidth * 0.02f;
	float ballX = racketX + (racketWidth - ballSize) / 2.0f;
	float ballY = racketY - (1.5f * ballSize);

	EntityId ball = ecsManager.createEntity();
	ecsManager.addComponent<velocity>(ball, { 100.0f, 100.0f });
	ecsManager.addComponent<position>(ball, { ballX, ballY });
	ecsManager.addComponent<size>(ball, { ballSize, ballSize });
	ecsManager.addComponent<color>(ball, { 0, 255, 0, 255 }); // Vert
	ecsManager.nameEntity("ball", ball);

	// Paramètres pour les briques
	float brickWidth = windowWidth * 0.1f;
	float brickHeight = windowHeight * 0.04f;
	float spacingX = brickWidth * 0.1f;
	float spacingY = brickHeight * 0.1f;

	float startX = spacingX;
	float startY = spacingY;

	float posX = startX;
	float posY = startY;

	int bricksPerRow = static_cast<int>((windowWidth - startX) / (brickWidth + spacingX));

	// Générer les briques
	for (int i = 0; i < 63; i++) {
		EntityId brick = ecsManager.createEntity();

		// Position de la brique
		ecsManager.addComponent<position>(brick, { posX, posY });
		ecsManager.addComponent<size>(brick, { brickWidth, brickHeight });

		// Couleur aléatoire
		int red = rand() % 256;
		int green = rand() % 256;
		int blue = rand() % 256;
		ecsManager.addComponent<color>(brick, { red, green, blue, 255 });
		ecsManager.nameEntity("brick :" + std::to_string(i), brick);

		// Passer à la brique suivante
		posX += brickWidth + spacingX;

		// Si on dépasse la largeur de la fenêtre, aller à la ligne suivante
		if (i % bricksPerRow == (bricksPerRow - 1)) {
			posX = startX;
			posY += brickHeight + spacingY;
		}
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

void Systeme::moveBall(float deltaTime)
{
	int windowWidth = window.getSize().x;
	int windowHeight = window.getSize().y;

	EntityId ball = ecsManager.getEntityByName("ball");
	position* ballPos = ecsManager.getComponent<position>(ball);
	velocity* ballVelo = ecsManager.getComponent<velocity>(ball);
	size* ballSize = ecsManager.getComponent<size>(ball);

	if (ballPos && ballVelo && ballSize) {
		ballPos->posX += ballVelo->veloX * deltaTime;
		ballPos->posY += ballVelo->veloY * deltaTime;

		// Gestion des rebonds sur les bords gauche et droit
		if (ballPos->posX <= 0) {
			ballPos->posX = 0;
			ballVelo->veloX = -ballVelo->veloX;
		}
		else if (ballPos->posX + ballSize->width >= windowWidth) {
			ballPos->posX = windowWidth - ballSize->width;
			ballVelo->veloX = -ballVelo->veloX;
		}

		// Gestion des rebonds sur le haut et le bas
		if (ballPos->posY <= 0) {
			ballPos->posY = 0;
			ballVelo->veloY = -ballVelo->veloY;
		}
		else if (ballPos->posY + ballSize->height >= windowHeight) {
			ballPos->posY = windowHeight - ballSize->height;
			ballVelo->veloY = -ballVelo->veloY;
		}
	}
	else {
		std::cerr << "Erreur : Composants manquants pour l'entité 'ball'" << std::endl;
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

void Systeme::checkBallBrickCollision()
{
	// Récupérer les informations de la balle
	EntityId ball = ecsManager.getEntityByName("ball");
	EntityId racket = ecsManager.getEntityByName("racket");
	position* ballPos = ecsManager.getComponent<position>(ball);
	velocity* ballVelo = ecsManager.getComponent<velocity>(ball);
	size* ballSize = ecsManager.getComponent<size>(ball);

	if (!(ballPos && ballVelo && ballSize)) {
		std::cerr << "Erreur : Composants manquants pour l'entité 'ball'" << std::endl;
		return;
	}

	// Gestion de la collision balle-raquette
	position* racketPos = ecsManager.getComponent<position>(racket);
	size* racketSize = ecsManager.getComponent<size>(racket);

	if (racketPos && racketSize) {
		// Vérifier si la balle touche la raquette (AABB collision)
		bool collisionX = ballPos->posX + ballSize->width > racketPos->posX &&
			ballPos->posX < racketPos->posX + racketSize->width;

		bool collisionY = ballPos->posY + ballSize->height > racketPos->posY &&
			ballPos->posY < racketPos->posY + racketSize->height;

		if (collisionX && collisionY) {
			// Inverser uniquement la direction verticale (rebond sur la raquette)
			ballVelo->veloY = -std::abs(ballVelo->veloY); // Rebond vers le haut

			// Ajuster la direction horizontale en fonction de l'impact sur la raquette
			float impactPoint = (ballPos->posX + ballSize->width / 2) - racketPos->posX;
			float normalizedImpact = (impactPoint / racketSize->width) - 0.5f; // Normalisé entre -0.5 et 0.5
			ballVelo->veloX += normalizedImpact * 200.0f; // Ajuste la vitesse horizontale
		}
	}

	// Gestion des collisions balle-briques
	for (auto e : ecsManager.getEntities()) {
		if (e == ball || e == racket) continue; // Ignore la balle et la raquette

		// Récupérer les informations de la brique
		position* brickPos = ecsManager.getComponent<position>(e);
		size* brickSize = ecsManager.getComponent<size>(e);

		if (brickPos && brickSize) {
			// Vérifier si la balle et la brique se chevauchent (AABB collision)
			bool collisionX = ballPos->posX + ballSize->width > brickPos->posX &&
				ballPos->posX < brickPos->posX + brickSize->width;

			bool collisionY = ballPos->posY + ballSize->height > brickPos->posY &&
				ballPos->posY < brickPos->posY + brickSize->height;

			if (collisionX && collisionY) {
				// Collision détectée avec une brique
				float ballCenterX = ballPos->posX + ballSize->width / 2;
				float ballCenterY = ballPos->posY + ballSize->height / 2;
				float brickCenterX = brickPos->posX + brickSize->width / 2;
				float brickCenterY = brickPos->posY + brickSize->height / 2;

				float dx = ballCenterX - brickCenterX; // Différence sur X
				float dy = ballCenterY - brickCenterY; // Différence sur Y

				if (std::abs(dx) > std::abs(dy)) {
					// Collision sur les côtés gauche ou droit
					ballVelo->veloX = -ballVelo->veloX;
				}
				else {
					// Collision sur le haut ou le bas
					ballVelo->veloY = -ballVelo->veloY;
				}

				// Supprimer la brique
				brickBreak(e);

				// Quitter la boucle après avoir géré une collision
				break;
			}
		}
	}
}


void Systeme::destroyEntity(EntityId e)
{
	ecsManager.destroyEntity(e);
}
