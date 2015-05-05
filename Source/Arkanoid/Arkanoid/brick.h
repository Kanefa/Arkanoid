#ifndef BRICK_H
#define BRICK_H

#include "rectangle.h"
#include <SFML/System/Vector2.hpp>

struct Brick : public Rectangle
{
							Brick(sf::Vector2f position, sf::Vector2f size);
							Brick(const Brick &) = default;
	Brick &					operator=(const Brick &) = default;

	bool					mDestroyed{false}; // Has the brick been struck?
};

#endif
