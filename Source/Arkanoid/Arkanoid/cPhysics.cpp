#include "cPhysics.h"
#include "componentID.h"
#include "entity.h"

CPhysics::CPhysics(const sf::Vector2f& halfSize)
: mHalfSize(halfSize)
{
}

float CPhysics::getX() const
{
	return mCPosition->getX();
}

float CPhysics::getY() const
{
	return mCPosition->getY();
}

float CPhysics::getLeft() const
{
	return getX() - mHalfSize.x;
}

float CPhysics::getRight() const
{
	return getX() + mHalfSize.x;
}

float CPhysics::getTop() const
{
	return getY() - mHalfSize.y;
}

float CPhysics::getBottom() const
{
	return getY() + mHalfSize.y;
}

void CPhysics::init()
{
	mCPosition = &mEntity->getComponent<CPosition>();
}

void CPhysics::update(FrameTime ftStep)
{
	mCPosition->mPosition += mVelocity * ftStep;

	if (onOutOfBounds == nullptr)
		return;

	if (getLeft() < 0) 
		onOutOfBounds(sf::Vector2f{1.f, 0.f});
	else if (getRight() > global::windowWidth)
		onOutOfBounds(sf::Vector2f{-1.f, 0.f});

	if (getTop() < 0)
		onOutOfBounds(sf::Vector2f{0.f, 1.f});
	else if (getBottom() > global::windowHeight)
		onOutOfBounds(sf::Vector2f{0.f, -1.f});
}
