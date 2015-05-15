#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include "brick.h"
#include "paddle.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

using FrameTime = float;

namespace global
{
	extern const unsigned int windowWidth, windowHeight;
}

struct Game
{
							Game();
							Game(const Game &) = delete;
	Game &					operator=(const Game &) = delete;

	void					run();

	void					inputPhase();
	void					updatePhase();
	void					drawPhase();

	const float				mFtStep{1.f};
	const float				mFtSlice{1.f};

	sf::RenderWindow		mWindow{{global::windowWidth, global::windowHeight}, "Arkanoid"};
	FrameTime				mLastFt{0.f};
	FrameTime				mCurrentSlice{0.f};
	bool					mRunning{false};

	Ball					mBall{{global::windowWidth / 2.f, global::windowHeight / 2.f}};
	Paddle					mPaddle{{global::windowWidth / 2.f, global::windowHeight - 50.f}, {60.f, 20.f}};
	std::vector<Brick>		mBricks;
};

#endif
