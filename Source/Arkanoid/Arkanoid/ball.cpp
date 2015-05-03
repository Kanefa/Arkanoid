#include "ball.h"
#include <SFML/Graphics/Color.hpp>

namespace global
{
	extern const unsigned int windowWidth, windowHeight;
	extern const float ballVelocity;
}

Ball::Ball(float x, float y)
: mVelocity{-global::ballVelocity, -global::ballVelocity}
{
	const float ballRadius{10.f};
	mShape.setPosition(x, y);
	mShape.setRadius(ballRadius);
	mShape.setFillColor(sf::Color::Red);
	mShape.setOrigin(ballRadius, ballRadius);
}

void Ball::update()
{
	mShape.move(mVelocity);

	if (left() < 0)
	{
		mVelocity.x = global::ballVelocity;
	}
	else if (right() > global::windowWidth)
	{
		mVelocity.x = -global::ballVelocity;
	}

	if (top() < 0)
	{
		mVelocity.y = global::ballVelocity;
	}
	else if (bottom() > global::windowHeight)
	{
		mVelocity.y = -global::ballVelocity;
	}
}

float Ball::x() const
{
	return mShape.getPosition().x;
}

float Ball::y() const
{
	return mShape.getPosition().y;
}

float Ball::left() const
{
	return x() - mShape.getRadius();
}

float Ball::right() const
{
	return x() + mShape.getRadius();
}

float Ball::top() const
{
	return y() - mShape.getRadius();
}

float Ball::bottom() const
{
	return y() + mShape.getRadius();
}
