#include <iostream>
#include "Window.h" 
#include "Event.h"
#include "Component.h"
#include "ECSManager.h"

int main()
{
    ECSManager ecs;

    EntityId entity = ecs.createEntity();
	EntityId balle = ecs.createEntity();
    std::cout << "Entite creee avec l'ID : " << entity << std::endl;
    std::cout << "Entite creee avec l'ID : " << balle << std::endl;

    ecs.addComponent<position>(entity, { 100.0f, 200.0f });
    ecs.addComponent<velocity>(entity, { 0.5f, 1.0f });

    if (ecs.hasComponent<position>(entity)) {
        std::cout << "L'entite a un composant Position." << std::endl;
    }

    position* pos = ecs.getComponent<position>(entity);
    if (pos) {
        std::cout << "Position : (" << pos->posX << ", " << pos->posY << ")" << std::endl;
    }

    ecs.removeComponent<velocity>(entity);
    if (!ecs.hasComponent<velocity>(entity)) {
        std::cout << "Le composant Velocity a ete supprime." << std::endl;
    }

    ecs.destroyEntity(entity);
    std::cout << "L'entite a ete supprimee." << std::endl;
	return 0;
}