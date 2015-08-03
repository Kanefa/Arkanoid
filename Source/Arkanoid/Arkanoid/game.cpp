#include "game.h"
#include "collision.h"
#include "cCircle.h"
#include "cPaddleControl.h"
#include "cPhysics.h"
#include "cPosition.h"
#include "cRectangle.h"
#include "entity.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdlib>
#include <chrono>

namespace global
{
	extern const float ballVelocity;
}

Game::Game()
{
	mWindow.setFramerateLimit(240);

	createPaddle();
	createBall();

	const sf::Vector2i brickCount{11, 4};
	const int buffer = 3;
	const int margin = 22;
	for (int column{ 0 }; column < brickCount.x; ++column)
	{
		for (int row{ 0 }; row < brickCount.y; ++row)
		{
			createBrick(sf::Vector2f((column + 1) * (mBrickSize.x + buffer) + margin, (row + 2) * (mBrickSize.y + buffer)));
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
	// Events and input should be proccesed every frame to ensure maximum responsiveness.
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
		mManager.refresh();
		mManager.update(mFtStep);

		auto &paddles(mManager.getEntitiesByGroup(GPaddle));
		auto &bricks(mManager.getEntitiesByGroup(GBrick));
		auto &balls(mManager.getEntitiesByGroup(GBall));

		for (auto &b : balls)
		{
			for (auto &p : paddles)
				testCollisionPB(*p, *b);

			for (auto &br : bricks)
				testCollisionBB(*br, *b);
		}
	}
}

void Game::drawPhase()
{
	mWindow.clear(sf::Color::Black);
	mManager.draw();
	mWindow.display();
}

void Game::render(const sf::Drawable &drawable)
{
	mWindow.draw(drawable);
}

Entity & Game::createBall()
{
	auto &entity(mManager.addEntity());

	entity.addComponent<CPosition>(sf::Vector2f{global::windowWidth / 2.f, global::windowHeight / 2.f});
	entity.addComponent<CPhysics>(sf::Vector2f{mBallRadius, mBallRadius});
	entity.addComponent<CCircle>(this, mBallRadius);

	auto &cPhysics(entity.getComponent<CPhysics>());
	cPhysics.mVelocity = sf::Vector2f{-global::ballVelocity, -global::ballVelocity};
	cPhysics.onOutOfBounds = [&cPhysics](const sf::Vector2f &side)
	{
		if (side.x != 0.f)
			cPhysics.mVelocity.x = std::abs(cPhysics.mVelocity.x) * side.x;

		if (side.y != 0.f)
			cPhysics.mVelocity.y = std::abs(cPhysics.mVelocity.y) * side.y;
	};

	entity.addGroup(ArkanoidGroup::GBall);

	return entity;
}

Entity & Game::createBrick(const sf::Vector2f &position)
{
	sf::Vector2f halfSize{mBrickSize.x / 2.f, mBrickSize.y / 2.f};
	auto &entity(mManager.addEntity());

	entity.addComponent<CPosition>(position);
	entity.addComponent<CPhysics>(halfSize);
	entity.addComponent<CRectangle>(this, halfSize);

	entity.addGroup(ArkanoidGroup::GBrick);

	return entity;
}

Entity & Game::createPaddle()
{
	sf::Vector2f halfSize{mPaddleSize.x / 2.f, mPaddleSize.y / 2.f};
	auto &entity(mManager.addEntity());

	entity.addComponent<CPosition>(sf::Vector2f{mWindow.getSize().x / 2.f, mWindow.getSize().y - 60.f});
	entity.addComponent<CPhysics>(halfSize);
	entity.addComponent<CRectangle>(this, halfSize);
	entity.addComponent<CPaddleControl>();

	entity.addGroup(ArkanoidGroup::GPaddle);

	return entity;
}
