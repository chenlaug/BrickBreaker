#include "ECSManager.h"
#include <iostream>

// Crée une nouvelle entité et retourne son ID
EntityId ECSManager::createEntity() {
    EntityId newEntity = nextEntityId++;
    entities.push_back(newEntity);
    return newEntity;
}


// Supprime une entité et tous ses composants
void ECSManager::destroyEntity(EntityId entity)
{
    for (auto& [type, entityComponents] : components) {
        entityComponents.erase(entity); // Supprime les composants de l'entité
    }

    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

// Retourne la liste des entités
const std::vector<EntityId>& ECSManager::getEntities() const {
    return entities;
}

