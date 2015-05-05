#include "rectangle.h"

Rectangle::Rectangle()
{
}

float Rectangle::getX() const
{
	return mShape.getPosition().x;
}

float Rectangle::getY() const
{
	return mShape.getPosition().y;
}

float Rectangle::getLeft() const
{
	return getX() - mShape.getSize().x / 2.f;
}

float Rectangle::getRight() const
{
	return getX() + mShape.getSize().x / 2.f;
}

float Rectangle::getTop() const
{
	return getY() - mShape.getSize().y / 2.f;
}

float Rectangle::getBottom() const
{
	return getY() + mShape.getSize().y / 2.f;
}
