#include "cRectangle.h"
#include "cPosition.h"
#include "entity.h"
#include "game.h"
#include <SFML/Graphics/Color.hpp>
	
CRectangle::CRectangle(Game *game, const sf::Vector2f & mHalfSize)
: mGame(game), mSize(mHalfSize * 2.f)
{
}

void CRectangle::init()
{
	mCPosition = &mEntity->getComponent<CPosition>();

	mShape.setSize(mSize);
	mShape.setFillColor(sf::Color::Yellow);
	mShape.setOrigin(mSize.x / 2.f, mSize.y / 2.f);
}

void CRectangle::update(FrameTime ftStep)
{
	mShape.setPosition(mCPosition->mPosition);
}

void CRectangle::draw()
{
	mGame->render(mShape);
}
