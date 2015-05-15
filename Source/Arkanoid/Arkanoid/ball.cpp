#include "ball.h"
#include <SFML/Graphics/Color.hpp>

namespace global
{
	extern const unsigned int windowWidth, windowHeight;
}

Ball::Ball(sf::Vector2f position)
: mVelocity{-mMaxVelocity, -mMaxVelocity}
{
	mShape.setPosition(position);
	mShape.setRadius(mRadius);
	mShape.setFillColor(sf::Color::Red);
	mShape.setOrigin(mRadius, mRadius);
}

void Ball::update(FrameTime ftStep)
{
	mShape.move(mVelocity * ftStep);

	if (getLeft() < 0)
	{
		mVelocity.x = mMaxVelocity;
	}
	else if (getRight() > global::windowWidth)
	{
		mVelocity.x = -mMaxVelocity;
	}

	if (getTop() < 0)
	{
		mVelocity.y = mMaxVelocity;
	}
	else if (getBottom() > global::windowHeight)
	{
		mVelocity.y = -mMaxVelocity;
	}
}

float Ball::getX() const
{
	return mShape.getPosition().x;
}

float Ball::getY() const
{
	return mShape.getPosition().y;
}

float Ball::getLeft() const
{
	return getX() - mShape.getRadius();
}

float Ball::getRight() const
{
	return getX() + mShape.getRadius();
}

float Ball::getTop() const
{
	return getY() - mShape.getRadius();
}

float Ball::getBottom() const
{
	return getY() + mShape.getRadius();
}

float Ball::getMaxVelocity() const
{
	return mMaxVelocity;
}
