#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SFML/Graphics/RectangleShape.hpp>

struct Rectangle
{
							Rectangle();
							Rectangle(const Rectangle &) = default;
	Rectangle &				operator=(const Rectangle &) = default;

	float					getX() const;
	float					getY() const;
	float					getLeft() const;
	float					getRight() const;
	float					getTop() const;
	float					getBottom() const;

	sf::RectangleShape		mShape;
};

#endif
