#include "manager.h"
#include <algorithm>
#include <cassert>

void Manager::update(float ftStep)
{
	for (auto &e : mEntities)
		e->update(ftStep);
}

void Manager::draw()
{
	for (auto &e : mEntities)
		e->draw();
}

void Manager::addToGroup(Entity *entity, Group group)
{
	assert(("The group already contains the entity!", std::find(mGroupedEntities[group].begin(), mGroupedEntities[group].end()
		, entity) == mGroupedEntities[group].end()));

	mGroupedEntities[group].emplace_back(entity);
}

std::vector<Entity*>& Manager::getEntitiesByGroup(Group group)
{
	return mGroupedEntities[group];
}

void Manager::refresh()
{
	// During refresh, we need to remove dead entities and entities with the incorrect groups from buckets.
	for (auto i(0u); i < Internal::maxGroups; ++i)
	{
		auto &v(mGroupedEntities[i]);
		v.erase(
			std::remove_if(std::begin(v), std::end(v),
			[i](Entity* entity)
			{
				return !entity->isAlive() || !entity->hasGroup(i);
			}),
			std::end(v));
	}

	// Cleanup dead entities
	mEntities.erase(
		std::remove_if(std::begin(mEntities), std::end(mEntities),
		[](const std::unique_ptr<Entity> &entity)
		{
			return !entity->isAlive();
		}),
		std::end(mEntities));
}

Entity & Manager::addEntity()
{
	Entity* e{new Entity{*this}};
	std::unique_ptr<Entity> uPtr{e};
	mEntities.emplace_back(std::move(uPtr));
	return *e;
}
