#include <iostream>
#include "Game.h"

int main()
{
   /* try
    {
        ECSManager ecs;

        EntityId entity = ecs.createEntity();
        std::cout << "Entite creee avec l'ID : " << entity << std::endl;

        ecs.addComponent<position>(entity, { 100.0f, 250.0f });
        ecs.addComponent<position>(entity, { 100.0f, 200.0f });

        if (ecs.hasComponent<position>(entity)) {
            std::cout << "L'entite a un composant Position." << std::endl;
        }

        position* pos = ecs.getComponent<position>(entity);
        if (pos) {
            std::cout << "Position : (" << pos->posX << " X " << pos->posY << ")" << std::endl;
        }



        ecs.removeComponent<velocity>(entity);
        if (!ecs.hasComponent<velocity>(entity)) {
            std::cout << "Le composant Velocity a ete supprime." << std::endl;
        }

        ecs.destroyEntity(entity);
        std::cout << "L'entite a ete supprimee." << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Une erreur s'est produite : " << e.what() << std::endl;

    }*/
   
	Game game;
	game.run();

	return 0;
}