#ifndef MANAGER_H
#define MANAGER_H

#include "componentID.h"
#include "entity.h"
#include <array>
#include <memory>
#include <vector>

class Entity;

class Manager
{
public:
							Manager() = default;
							Manager(const Manager &) = delete;
	Manager &				operator=(const Manager &) = delete;

	void					update(float ftStep);
	void					draw();

	void					addToGroup(Entity *entity, Group group);
	std::vector<Entity *>&	getEntitiesByGroup(Group group);
	void					refresh();

	Entity &				addEntity();

private:
	std::vector<std::unique_ptr<Entity>> mEntities;
	std::array<std::vector<Entity *>, Internal::maxGroups> mGroupedEntities;
};

#endif
