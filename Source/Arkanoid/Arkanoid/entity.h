#ifndef ENTITY_H
#define ENTITY_H

#include "component.h"
#include "componentID.h"
#include <memory>
#include <vector>

class Manager;

class Entity
{
public:
							Entity(Manager &manager);
							Entity(const Entity &) = delete;
	Entity &				operator=(const Entity &) = delete;

	template<typename T> bool hasComponent() const;
	template<typename T> T&   getComponent() const;

	bool					hasGroup(Group group) const;

	bool					isAlive() const;
	void					destroy();

	template<typename T, typename... TArgs>
	T&						addComponent(TArgs&&... args);
	void					addGroup(Group group);
	void					delGroup(Group group);

	void					update(float ftStep);
	void					draw();

private:
	Manager					&mManager;
	bool					mAlive{true};

	// ALW - A separate vector is used to hold the components, instead of using the mComponentArray,
	// ALW - so the existance of components does not have to be checked each iteration (optimization).
	std::vector<std::unique_ptr<Component>> mComponents; // ALW - Allow fast iteration through components 
	Internal::ComponentArray  mComponentArray;           // ALW - Allow fast component retrieval
	Internal::ComponentBitset mComponentBitset;          // ALW - Allow fast existance check of a component
	Internal::GroupBitset     mGroupBitset;				 // ALW - Allow fast existance check of a group
};

#include "entity.inl"

#endif
