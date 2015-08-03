#ifndef CCIRCLE_H
#define CCIRCLE_H

#include "component.h"
#include <SFML/Graphics/CircleShape.hpp>

using FrameTime = float;

struct CPosition;
struct Game;

struct CCircle : Component
{
							CCircle(Game *game, float radius);
							CCircle(const CCircle &) = delete;
	CCircle &				operator=(const CCircle &) = delete;

	virtual void			init() override;
	virtual void			update(FrameTime ftStep) override;
	virtual void			draw() override;

	Game					*mGame{nullptr};
	CPosition				*mCPosition{nullptr};
	sf::CircleShape			mShape;
	float					mRadius;
};

#endif
