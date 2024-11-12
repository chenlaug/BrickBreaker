#ifndef ECSManager_INL
#define ECSManager_INL

#include <stdexcept>
#include <typeinfo>

template<typename Component>
void ECSManager::addComponent(EntityId entity, Component& component)
{
	auto& componentMap = components[typeid(Component)];
	if (componentMap.find(entity) != componentMap.end()) {
		throw std::runtime_error("Entity already has component of this type");
	}
	componentMap[entity] = std::make_unique<Component>(component);
}

template<typename Component>
Component* ECSManager::getComponent(EntityId entity)
{
	auto it = components.find(typeid(Component));
	if (it != components.end())
	{
		auto& ComponentMap = it->second;
		auto componentIt = ComponentMap.find(entity);
		if (componentIt != ComponentMap.end())
		{
			return static_cast<Component*>(componentIt->second.get());
		}
	}
	return nullptr;
}

template<typename Component>
bool ECSManager::hasComponent(EntityId entity) const
{
	auto it components.find(typeid(Component));
	if (it != components.end()) {
		it->seconde.erase(entity);
	}
}

#endif // ECSManager_INL
