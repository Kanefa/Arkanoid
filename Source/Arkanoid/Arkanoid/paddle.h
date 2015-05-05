#ifndef PADDLE_H
#define PADDLE_H

#include "rectangle.h"
#include <SFML/System/Vector2.hpp>

struct Paddle : public Rectangle
{
							Paddle(sf::Vector2f position, sf::Vector2f size, float velocity);
							Paddle(const Paddle &) = delete;
	Paddle &				operator=(const Paddle &) = delete;

	void					update();

	const float				mMaxVelocity{6.f};
	sf::Vector2f			mVelocity;
};

#endif
