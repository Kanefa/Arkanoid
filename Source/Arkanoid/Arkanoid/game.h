#ifndef GAME_H
#define GAME_H

#include "manager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <cstddef>
#include <vector>

using FrameTime = float;

namespace global
{
	extern const unsigned int windowWidth, windowHeight;
}

class Entity;

struct Game
{
	enum ArkanoidGroup : std::size_t
	{
		GPaddle,
		GBrick,
		GBall
	};

							Game();
							Game(const Game &) = delete;
	Game &					operator=(const Game &) = delete;

	void					run();

	void					inputPhase();
	void					updatePhase();
	void					drawPhase();
	void					render(const sf::Drawable &drawable);

	Entity &                createBall();
	Entity &				createBrick(const sf::Vector2f &position);
	Entity &				createPaddle();

	const float				mFtStep{1.f};
	const float				mFtSlice{1.f};

	const sf::Vector2f		mBrickSize{60.f, 20.f};
	const sf::Vector2f		mPaddleSize{60.f, 20.f};
	const float				mBallRadius{10.f};

	sf::RenderWindow		mWindow{{global::windowWidth, global::windowHeight}, "Arkanoid"};
	FrameTime				mLastFt{0.f};
	FrameTime				mCurrentSlice{0.f};
	bool					mRunning{false};
	Manager                 mManager;
};

#endif
