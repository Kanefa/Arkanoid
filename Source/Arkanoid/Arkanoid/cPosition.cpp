#include "cPosition.h"

CPosition::CPosition(const sf::Vector2f &position)
: mPosition(position)
{
}

float CPosition::getX() const
{
	return mPosition.x;
}

float CPosition::getY() const
{
	return mPosition.y;
}
