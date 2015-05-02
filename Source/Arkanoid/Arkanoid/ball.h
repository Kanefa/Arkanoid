#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics/CircleShape.hpp>

struct Ball
{
			Ball(float x, float y);
			Ball(const Ball &) = delete;
	Ball &	operator=(const Ball &) = delete;

	sf::CircleShape	shape;
};

#endif
