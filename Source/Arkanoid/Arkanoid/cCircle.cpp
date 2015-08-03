#include "cCircle.h"
#include "cPosition.h"
#include "entity.h"
#include "game.h"
#include <SFML/Graphics/Color.hpp>

CCircle::CCircle(Game *game, float radius)
: mGame(game)
, mRadius(radius)
{
}

void CCircle::init()
{
	mCPosition = &mEntity->getComponent<CPosition>();

	mShape.setRadius(mRadius);
	mShape.setFillColor(sf::Color::Red);
	mShape.setOrigin(mRadius, mRadius);
}

void CCircle::update(FrameTime ftStep)
{
	mShape.setPosition(mCPosition->mPosition);
}

void CCircle::draw()
{
	mGame->render(mShape);
}
