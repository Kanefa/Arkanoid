#include "paddle.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace global
{
	extern const unsigned int windowWidth, windowHeight;
	extern const float paddleWidth, paddleHeight, paddleVelocity;
}

Paddle::Paddle(float x, float y)
{
	mShape.setPosition(x, y);
	mShape.setSize({global::paddleWidth, global::paddleHeight});
	mShape.setFillColor(sf::Color::Red);
	mShape.setOrigin(global::paddleWidth / 2, global::paddleHeight / 2);
}

void Paddle::update()
{
	mShape.move(mVelocity);

	// To move the paddle, we check if the user is pressing
	// the left or right arrow key: if so, we change the velocity

	// To keep the paddle "inside the window," we change the
	// velocity only if its position is inside the window
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)
		&& left() > 0)
	{
		mVelocity.x = -global::paddleVelocity;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)
		&& right() < global::windowWidth)
	{
		mVelocity.x = global::paddleVelocity;
	}
	else
	{
		// The user isn't pressing left or right
		mVelocity.x = 0.f;
	}
}

float Paddle::x() const
{
	return mShape.getPosition().x;
}

float Paddle::y() const
{
	return mShape.getPosition().y;
}

float Paddle::left() const
{
	return x() - mShape.getSize().x / 2.f;
}

float Paddle::right() const
{
	return x() + mShape.getSize().x / 2.f;
}

float Paddle::top() const
{
	return y() - mShape.getSize().y / 2.f;
}

float Paddle::bottom() const
{
	return y() + mShape.getSize().y / 2.f;
}
