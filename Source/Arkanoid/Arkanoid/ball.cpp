#include "ball.h"
#include <SFML/Graphics/Color.hpp>

Ball::Ball(float x, float y)
{
	const float ballRadius{10.f};
	shape.setPosition(x, y);
	shape.setRadius(ballRadius);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(ballRadius, ballRadius);
}
