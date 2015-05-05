#include "brick.h"
#include <SFML/Graphics/Color.hpp>

Brick::Brick(sf::Vector2f position, sf::Vector2f size)
{
	mShape.setPosition(position);
	mShape.setSize(size);
	mShape.setFillColor(sf::Color::Yellow);
	mShape.setOrigin(size / 2.f);
}
