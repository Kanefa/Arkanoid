#ifndef BRICK_H
#define BRICK_H

#include <SFML/Graphics/RectangleShape.hpp>

struct Brick
{
			Brick(float x, float y);
			Brick(const Brick &) = default;
	Brick &	operator=(const Brick &) = default;

	float	x() const;
	float	y() const;
	float	left() const;
	float	right() const;
	float	top() const;
	float	bottom() const;

	sf::RectangleShape mShape;
	bool			   mDestroyed; // Has the brick been struck?
};

#endif
