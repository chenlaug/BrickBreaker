#pragma once
#include <map>
#include <string>
#include <variant>
#include "Component.h"

using Component = std::variant<position, velocity, size, color, texture>;

class ECSManager
{
private:
	std::map <std::string, std::map <std::string, Component>> entities;

public:
	ECSManager() {};
	~ECSManager() {};

	void addComponent(std::string entity, std::string component, Component data)
	{
		entities[entity][component] = data;
	}

	Component getComponent(std::string entity, std::string component)
	{
		return entities[entity][component];
	}
};

