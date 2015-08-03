#ifndef COMPONENTID_H
#define COMPONENTID_H

#include <array>
#include <bitset>
#include <cstddef>
#include <type_traits>

struct Component;
class Entity;

using ComponentID = std::size_t;
using Group = std::size_t;

namespace Internal
{

	inline ComponentID getUniqueComponentID()
	{
		static ComponentID lastID{0u};
		return lastID++;
	}

	template<typename T> inline ComponentID getComponentTypeID()
	{
		// ALW - Each time we call this function with a specific type 'T' we are calling the corresponding
		// ALW - instantiation of this template. Therefore, the first call with a specific type 'T' will
		// ALW - initialize typeID. Then each call with a specific type 'T' will return the corresponding
		// ALW - intantiation's typeID.
		static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component!");
		static ComponentID typeID{getUniqueComponentID()};
		return typeID;
	}

	const std::size_t maxComponents{32};
	using ComponentBitset = std::bitset<maxComponents>;
	using ComponentArray = std::array<Component*, maxComponents>;

	const std::size_t maxGroups{32};
	using GroupBitset = std::bitset <maxGroups>;

} // Internal namespace

#endif
