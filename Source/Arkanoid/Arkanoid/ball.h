#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

struct Ball
{
			Ball(float x, float y);
			Ball(const Ball &) = delete;
	Ball &	operator=(const Ball &) = delete;

	void	update();

	sf::CircleShape	mShape;
	sf::Vector2f	mVelocity;
};

#endif
