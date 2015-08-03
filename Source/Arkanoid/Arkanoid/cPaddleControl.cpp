#include "cPaddleControl.h"
#include "cPhysics.h"
#include "entity.h"
#include <SFML/Window/Keyboard.hpp>

namespace global
{
	extern const unsigned int windowWidth, windowHeight;
}

void CPaddleControl::init()
{
	mCPhysics = &mEntity->getComponent<CPhysics>();
}

void CPaddleControl::update(FrameTime ftStep)
{
	// To move the paddle, we check if the user is pressing
	// the left or right arrow key: if so, we change the velocity

	// To keep the paddle "inside the window," we change the
	// velocity only if its position is inside the window
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)
		&& mCPhysics->getLeft() > 0)
	{
		mCPhysics->mVelocity.x = -mVelocity;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)
		&& mCPhysics->getRight() < global::windowWidth)
	{
		mCPhysics->mVelocity.x = mVelocity;
	}
	else
	{
		// The user isn't pressing left or right
		mCPhysics->mVelocity.x = 0.f;
	}
}
