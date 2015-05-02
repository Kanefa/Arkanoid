#include "ball.h"
#include <SFML/Graphics/Color.hpp>

const float ballVelocity{8.f};

Ball::Ball(float x, float y)
: mVelocity{-ballVelocity, -ballVelocity}
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
}
