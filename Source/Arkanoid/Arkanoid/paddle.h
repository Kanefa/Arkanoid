#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

struct Paddle
{
				Paddle(float x, float y);
				Paddle(const Paddle &) = delete;
	Paddle &	operator=(const Paddle &) = delete;

	void		update();

	float left() const;
	float right() const;
	float top() const;
	float bottom() const;

	sf::RectangleShape mShape;
	sf::Vector2f mVelocity;
};

#endif
