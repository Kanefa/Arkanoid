#ifndef PHYSICS_H
#define PHYSICS_H

#include "component.h"
#include "cPosition.h"
#include "SFML/System/Vector2.hpp"
#include <functional>

using FrameTime = float;

namespace global
{
	extern const unsigned int windowWidth, windowHeight;
}

struct CPhysics : Component
{
							CPhysics(const sf::Vector2f &halfSize);
							CPhysics(const CPhysics &) = delete;
	CPhysics &				operator=(const CPhysics &) = delete;

	float					getX() const;
	float					getY() const;
	float					getLeft() const;
	float					getRight() const;
	float					getTop() const;
	float					getBottom() const;

	virtual void			init() override;
	virtual void			update(FrameTime ftStep) override;

	std::function<void(const sf::Vector2f&)> onOutOfBounds;

	CPosition				*mCPosition{nullptr};
	sf::Vector2f			mVelocity;
	sf::Vector2f			mHalfSize;
};

#endif
