#include "paddle.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace global
{
	extern const unsigned int windowWidth, windowHeight;
}

Paddle::Paddle(sf::Vector2f position, sf::Vector2f size)
: mVelocity{0.0f, 0.0f}
{
	mShape.setPosition(position);
	mShape.setSize(size);
	mShape.setFillColor(sf::Color::Red);
	mShape.setOrigin(size / 2.f);
}

void Paddle::update(FrameTime ftStep)
{
	mShape.move(mVelocity * ftStep);

	// To move the paddle, we check if the user is pressing
	// the left or right arrow key: if so, we change the velocity

	// To keep the paddle "inside the window," we change the
	// velocity only if its position is inside the window
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)
		&& getLeft() > 0)
	{
		mVelocity.x = -mMaxVelocity;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)
		&& getRight() < global::windowWidth)
	{
		mVelocity.x = mMaxVelocity;
	}
	else
	{
		// The user isn't pressing left or right
		mVelocity.x = 0.f;
	}
}
