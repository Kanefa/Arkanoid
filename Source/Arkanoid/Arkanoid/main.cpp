#include "ball.h"
#include "brick.h"
#include "paddle.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <cstdlib>
#include <vector>

namespace global
{
	extern const unsigned int windowWidth{800}, windowHeight{600};
}

// Define a generic function to check if two shapes are intersecting
template<class T1, class T2> bool isIntersecting(T1 &shape0, T2 &shape1)
{
	return shape0.getRight() >= shape1.getLeft() && shape0.getLeft() <= shape1.getRight()
		&& shape0.getBottom() >= shape1.getTop() && shape0.getTop() <= shape1.getBottom();
}

// Define a function that deals with paddle/ball collisions
void testCollision(Paddle &paddle, Ball &ball)
{
	// If there's no intersection, exit the function
	if (!isIntersecting(paddle, ball))
	{
		return;
	}

	// Otherwise redirect the ball upwards
	ball.mVelocity.y = -ball.getMaxVelocity();

	// Direct he ball dependently on the position where he paddle was struck
	if (ball.getX() < paddle.getX())
	{
		// paddle struck on left side
		ball.mVelocity.x = -ball.getMaxVelocity();
	}
	else
	{
		// paddle struck on right side
		ball.mVelocity.x = ball.getMaxVelocity();
	}
}

// Define a function that deals with brick/ball collisions
void testCollision(Brick &brick, Ball &ball)
{
	// If there's no intersection, exit the function
	if (!isIntersecting(brick, ball))
	{
		return;
	}

	// Otherwise the brick has been struck!
	brick.mDestroyed = true;

	// Calculate how much the ball intersects the brick in every direction
	float overlapLeft{ball.getRight() - brick.getLeft()};
	float overlapRight{ brick.getRight() - ball.getLeft()};
	float overlapTop{ball.getBottom() - brick.getTop()};
	float overlapBottom{brick.getBottom() - ball.getTop()};

	// If the magnitude of the left overlap is smaller than the right
	// overlap we can assume the ball hit the brick from the left.
	bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));

	// If the magnitude of the top overlap is smaller than the bottom
	// overlap we can assume the ball hit the brick from the top.
	bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

	// Store the minimum overlaps for the X and Y axis
	float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
	float minOverlapY{ballFromTop ? overlapTop : overlapBottom};

	// If the magnitude of the X overlap is less than the magnitude of the Y
	// overlap, we can assume the ball struck the brick horizontally - otherwise,
	// the ball hit the brick vertically

	// The based on our results we change either the X or Y velocity
	// of the ball, creating a "realistic" response for the collision
	if (abs(minOverlapX) < abs(minOverlapY))
	{
		ball.mVelocity.x = ballFromLeft ? -ball.getMaxVelocity() : ball.getMaxVelocity();
	}
	else
	{
		ball.mVelocity.y = ballFromTop ? -ball.getMaxVelocity() : ball.getMaxVelocity();
	}
}

int main()
{
	Ball ball{{global::windowWidth / 2, global::windowHeight / 2}};
	Paddle paddle{{global::windowWidth / 2, global::windowHeight - 50.f}, {60.f, 20.f}, 6.f};

	std::vector<Brick> bricks;
	const sf::Vector2f brickSize{60.f, 20.f};
	const sf::Vector2i brickCount{11, 4};
	const int buffer = 3;
	const int margin = 22;
	for (int column{0}; column < brickCount.x; ++column)
	{
		for (int row{0}; row < brickCount.y; ++row)
		{
			bricks.emplace_back(sf::Vector2f((column + 1) * (brickSize.x + buffer) + margin, (row + 2) * (brickSize.y + buffer))
				, brickSize);
		}
	}

	sf::RenderWindow window({global::windowWidth, global::windowHeight}, "Arkanoid");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
						window.close();
					break;
			}
		}

		ball.update();
		paddle.update();
		testCollision(paddle, ball);

		for (auto &brick : bricks)
		{
			testCollision(brick, ball);
		}

		bricks.erase(std::remove_if(begin(bricks), end(bricks),
			[](const Brick &brick){ return brick.mDestroyed; }),
			end(bricks));

		// "Clear" the window from previouly drawn graphics
		window.clear(sf::Color::Black);

		window.draw(ball.mShape);
		window.draw(paddle.mShape);
		for (const auto &brick : bricks)
		{
			window.draw(brick.mShape);
		}

		window.display();
	}

	return 0;
}
