#ifndef PADDLE_H
#define PADDLE_H

#include "rectangle.h"
#include <SFML/System/Vector2.hpp>

using FrameTime = float;

struct Paddle : public Rectangle
{
							Paddle(sf::Vector2f position, sf::Vector2f size);
							Paddle(const Paddle &) = delete;
	Paddle &				operator=(const Paddle &) = delete;

	void					update(FrameTime ftStep);

	const float				mMaxVelocity{0.6f};
	sf::Vector2f			mVelocity;
};

#endif
