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
    ecsManager.addComponent<position>(racket, { racketX, racketY });
    ecsManager.addComponent<size>(racket, { racketWidth, racketHeight });
    ecsManager.addComponent<color>(racket, { 255, 0, 0, 255 }); // Rouge

    // Création de la balle (au-dessus de la raquette)
    float ballSize = windowWidth * 0.02f; 
    float ballX = racketX + (racketWidth - ballSize) / 2.0f; 
    float ballY = racketY - (1.5f * ballSize); 

    EntityId ball = ecsManager.createEntity();
    ecsManager.addComponent<position>(ball, { ballX, ballY });
    ecsManager.addComponent<size>(ball, { ballSize, ballSize });
    ecsManager.addComponent<color>(ball, { 0, 255, 0, 255 }); // Vert

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
