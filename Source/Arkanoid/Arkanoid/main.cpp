#include "ball.h"
#include "brick.h"
#include "paddle.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>

namespace global
{
	extern const unsigned int windowWidth{800}, windowHeight{600};
	extern const float ballVelocity{8.f};
	extern const float paddleWidth{60.f}, paddleHeight{20.f}, paddleVelocity{6.f};
	extern const float brickWidth{60.f}, brickHeight{20.f};
	extern const int countBlocksX{11}, countBlocksY{4};
}

// Define a generic function to check if two shapes are intersecting
template<class T1, class T2> bool isIntersecting(T1 &shape0, T2 &shape1)
{
	return shape0.right() >= shape1.left() && shape0.left() <= shape1.right()
		&& shape0.bottom() >= shape1.top() && shape0.top() <= shape1.bottom();
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
	ball.mVelocity.y = -global::paddleVelocity;

	// Direct he ball dependently on the position where he paddle was struck
	if (ball.x() < paddle.x())
	{
		// paddle struck on left side
		ball.mVelocity.x = -global::ballVelocity;
	}
	else
	{
		// paddle struck on right side
		ball.mVelocity.x = global::ballVelocity;
	}
}

int main()
{
	Ball ball{global::windowWidth / 2, global::windowHeight / 2};
	Paddle paddle{global::windowWidth / 2, global::windowHeight - 50.f};

	const int buffer = 3;
	const int margin = 22;
	std::vector<Brick> bricks;
	for (int column{0}; column < global::countBlocksX; ++column)
	{
		for (int row{0}; row < global::countBlocksY; ++row)
		{
			bricks.emplace_back((column + 1) * (global::brickWidth + buffer) + margin,
								(row + 2) * (global::brickHeight + buffer));
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
