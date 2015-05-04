#include "brick.h"
#include <SFML/Graphics/Color.hpp>

namespace global
{
	extern const float brickWidth, brickHeight;
}

Brick::Brick(float x, float y)
: mDestroyed{false}
{
	mShape.setPosition(x, y);
	mShape.setSize({global::brickWidth, global::brickHeight});
	mShape.setFillColor(sf::Color::Yellow);
	mShape.setOrigin(global::brickWidth / 2.f, global::brickHeight / 2.f);
}

float Brick::x() const
{
	return mShape.getPosition().x;
}

float Brick::y() const
{
	return mShape.getPosition().y;
}

float Brick::left() const
{
	return x() - mShape.getSize().x / 2.f;
}

float Brick::right() const
{
	return x() + mShape.getSize().x / 2.f;
}

float Brick::top() const
{
	return y() - mShape.getSize().y / 2.f;
}

float Brick::bottom() const
{
	return y() + mShape.getSize().y / 2.f;
}
