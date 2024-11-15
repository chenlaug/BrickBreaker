#include "ECSManager.h"
#include <iostream>

// Cr�e une nouvelle entit� et retourne son ID
EntityId ECSManager::createEntity() {
    EntityId newEntity = nextEntityId++;
    entities.push_back(newEntity);
    return newEntity;
}


// Supprime une entit� et tous ses composants
void ECSManager::destroyEntity(EntityId entity) {
    for (auto& [type, componentMap] : components) {
        componentMap.erase(entity); // Supprime uniquement les composants de l'entit�
    }
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
    std::cout << "Entity " << entity << " destroyed." << std::endl;
}



// Ajouter un nom a une entit�
void ECSManager::nameEntity(const std::string& name, EntityId entity)
{
    if (namedEntities.find(name) != namedEntities.end()) {
        throw std::runtime_error("Entity name already exists: " + name);
    }
    namedEntities[name] = entity;
}

// Supprime toutes les entit�s et leurs composants
void ECSManager::clearEntities(){
	for (auto entity : entities) {
		destroyEntity(entity);
	}
	entities.clear();
	namedEntities.clear();
	components.clear();
}

// Retourne l'entit� avec le nom donn�
EntityId ECSManager::getEntityByName(const std::string& name) const
{
    auto it = namedEntities.find(name);
    if (it != namedEntities.end()) {
        return it->second;
    }
    throw std::runtime_error("No entity found with name: " + name);
}


// Retourne la liste des entit�s
const std::vector<EntityId>& ECSManager::getEntities() const {
    return entities;
}


