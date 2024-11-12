#include "ECSManager.h"

// Cr�e une nouvelle entit� et retourne son ID
EntityId ECSManager::createEntity()
{
    entities.push_back(nextEntityId);
    return nextEntityId++;
}

// Supprime une entit� et tous ses composants
void ECSManager::destroyEntity(EntityId entity)
{
    for (auto& [type, entityComponents] : components) {
        entityComponents.erase(entity); // Supprime les composants de l'entit�
    }

    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

// Retourne la liste des entit�s
const std::vector<EntityId>& ECSManager::getEntities() const
{
    return entities;
}
