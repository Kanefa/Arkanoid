#include <cassert>
#include <utility>

template<typename T> bool Entity::hasComponent() const
{
	return mComponentBitset[Internal::getComponentTypeID<T>()];
}

template<typename T> T& Entity::getComponent() const
{
	assert(hasComponent<T>());
	auto ptr(mComponentArray[Internal::getComponentTypeID<T>()]);
	return *static_cast<T*>(ptr);
}

template<typename T, typename... TArgs>
T& Entity::addComponent(TArgs&&... args)
{
	// ALW - Before adding a component, make sure it doesn't already exist.
	assert(!hasComponent<T>());

	// Create component and then add it to vector.
	T* c(new T(std::forward<TArgs>(args)...));
	c->mEntity = this;
	std::unique_ptr<Component> uPtr{c};
	mComponents.emplace_back(std::move(uPtr));

	// Add component to array and bitset. 
	mComponentArray[Internal::getComponentTypeID<T>()] = c;
	mComponentBitset[Internal::getComponentTypeID<T>()] = true;

	c->init();

	return *c;
}
