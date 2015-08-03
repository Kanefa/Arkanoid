#include "entity.h"
#include "manager.h"

Entity::Entity(Manager &manager)
: mManager(manager)
{
}

bool Entity::isAlive() const
{
	return mAlive;
}

void Entity::destroy()
{
	mAlive = false;
}

bool Entity::hasGroup(Group group) const
{
	return mGroupBitset[group];
}

void Entity::addGroup(Group group)
{
	mGroupBitset[group] = true;
	mManager.addToGroup(this, group);
}

void Entity::delGroup(Group group)
{
	mGroupBitset[group] = false;
}

void Entity::update(float ftStep)
{
	for (auto &c : mComponents)
		c->update(ftStep);
}

void Entity::draw()
{
	for (auto &c : mComponents)
		c->draw();
}
