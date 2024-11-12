#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <vector>
#include <stdexcept>
#include <typeinfo>
#include <algorithm>

using EntityId = int;

class ECSManager
{
private:
    EntityId nextEntityId = 0;
    std::vector<EntityId> entities;
    std::unordered_map<std::type_index, std::unordered_map<EntityId, std::shared_ptr<void>>> components;

public:
    EntityId createEntity();
    void destroyEntity(EntityId entity);
    const std::vector<EntityId>& getEntities() const;

    template<typename Component>
    void addComponent(EntityId entity, const Component& component);

    template<typename Component>
    Component* getComponent(EntityId entity);

    template<typename Component>
    bool hasComponent(EntityId entity) const;

    template<typename Component>
    void removeComponent(EntityId entity);
};

// ########## Implémentation des méthodes template ##########

// Crée une nouvelle entité et retourne son ID
template<typename Component>
inline void ECSManager::addComponent(EntityId entity, const Component& component)
{
    auto& componentMap = components[typeid(Component)];
    if (componentMap.find(entity) != componentMap.end()) {
        throw std::runtime_error("Entity already has component of this type");
    }
    componentMap[entity] = std::make_shared<Component>(component);
}

// Retourne un composant d'une entité
template<typename Component>
inline Component* ECSManager::getComponent(EntityId entity)
{
    auto it = components.find(typeid(Component));
    if (it != components.end())
    {
        auto& componentMap = it->second;
        auto componentIt = componentMap.find(entity);
        if (componentIt != componentMap.end())
        {
            return static_cast<Component*>(componentIt->second.get());
        }
    }
    return nullptr;
}

// Vérifie si une entité a un composant
template<typename Component>
inline bool ECSManager::hasComponent(EntityId entity) const
{
    auto it = components.find(typeid(Component));
    if (it != components.end()) {
        return it->second.find(entity) != it->second.end();
    }
    return false;
}

// Supprime un composant d'une entité
template<typename Component>
inline void ECSManager::removeComponent(EntityId entity)
{
    auto it = components.find(typeid(Component));
    if (it != components.end()) {
        it->second.erase(entity);
    }
}

// ####################