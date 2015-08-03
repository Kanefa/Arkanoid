#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include "component.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

using FrameTime = float;

struct CPosition;
struct Game;

struct CRectangle : Component
{
							CRectangle(Game *game, const sf::Vector2f &mHalfSize);
							CRectangle(const CRectangle &) = delete;
	CRectangle &			operator=(const CRectangle &) = delete;

	virtual void			init() override;
	virtual void			update(FrameTime ftStep) override;
	virtual void			draw() override;

	Game					*mGame{nullptr};
	CPosition				*mCPosition{nullptr};
	sf::RectangleShape		mShape;
	sf::Vector2f			mSize;
};

#endif
