#include "game.h"
#include "collision.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <chrono>

Game::Game()
{
	mWindow.setFramerateLimit(240);

	const sf::Vector2f brickSize{60.f, 20.f};
	const sf::Vector2i brickCount{11, 4};
	const int buffer = 3;
	const int margin = 22;
	for (int column{ 0 }; column < brickCount.x; ++column)
	{
		for (int row{ 0 }; row < brickCount.y; ++row)
		{
			mBricks.emplace_back(sf::Vector2f((column + 1) * (brickSize.x + buffer) + margin, (row + 2) * (brickSize.y + buffer))
				, brickSize);
		}
	}
}

void Game::run()
{
	mRunning = true;

	while (mRunning)
	{
		auto startFrame(std::chrono::high_resolution_clock::now());

		inputPhase();
		updatePhase();
		drawPhase();

		auto endFrame(std::chrono::high_resolution_clock::now());
		auto frameTime(std::chrono::duration_cast<std::chrono::duration<FrameTime, std::milli>>(endFrame - startFrame).count());
		mLastFt = frameTime;
		auto fps(1.f / (frameTime / 1000.f)); // Convert to seconds
		mWindow.setTitle("FT: " + std::to_string(frameTime) + " FPS: " + std::to_string(fps));
	}
}

void Game::inputPhase()
{
	// Events and input should be prcocesed every frame to ensure maximum responsiveness.
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			mWindow.close();
			mRunning = false;
			break;

		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			{
				mWindow.close();
				mRunning = false;
			}
			break;
		}
	}
}

void Game::updatePhase()
{
	mCurrentSlice += mLastFt;

	// If 'currentSlice' is greater or equal to 'ftSlice,' we update our game logic and 
	// decrease 'currentSlice' by 'ftSlice' until 'currentSlice' becomes less than 'ftSlice.'
	for (; mCurrentSlice >= mFtSlice; mCurrentSlice -= mFtSlice)
	{
		mBall.update(mFtStep);
		mPaddle.update(mFtStep);

		testCollision(mPaddle, mBall);
		for (auto &brick : mBricks)
		{
			testCollision(brick, mBall);
		}

		mBricks.erase(std::remove_if(begin(mBricks), end(mBricks),
			[](const Brick &brick){ return brick.mDestroyed; }),
			end(mBricks));
	}
}

void Game::drawPhase()
{
	mWindow.clear(sf::Color::Black);
	mWindow.draw(mBall.mShape);
	mWindow.draw(mPaddle.mShape);
	for (const auto &brick : mBricks)
	{
		mWindow.draw(brick.mShape);
	}
	mWindow.display();
}
