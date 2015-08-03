#ifndef CPOSITION_H
#define CPOSITION_H

#include "component.h"
#include <SFML/System/Vector2.hpp>

using FrameTime = float;

struct CPosition : Component
{
							CPosition() = default;
							CPosition(const sf::Vector2f &position);
							CPosition(const CPosition &) = delete;
	CPosition &				operator=(const CPosition &) = delete;

	float					getX() const;
	float					getY() const;

	sf::Vector2f			mPosition;
};

#endif
