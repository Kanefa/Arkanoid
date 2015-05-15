#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

using FrameTime = float;

struct Ball
{
							Ball(sf::Vector2f position);
							Ball(const Ball &) = delete;
	Ball &					operator=(const Ball &) = delete;

	float					getX() const;
	float					getY() const;
	float					getLeft() const;
	float					getRight() const;
	float					getTop() const;
	float					getBottom() const;
	float					getMaxVelocity() const;

	void					update(FrameTime ftStep);

	const float				mRadius{10.f};
	const float				mMaxVelocity{0.8f};
	sf::CircleShape			mShape;
	sf::Vector2f			mVelocity;
};

#endif
