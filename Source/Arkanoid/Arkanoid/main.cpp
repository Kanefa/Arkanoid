#include "ball.h"
#include "paddle.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace global
{
	extern const unsigned int windowWidth{800}, windowHeight{600};
	extern const float paddleWidth{60.f}, paddleHeight{20.f}, paddleVelocity{6.f};
}

int main()
{
	Ball ball{global::windowWidth / 2, global::windowHeight / 2};
	Paddle paddle{global::windowWidth / 2, global::windowHeight - 50.f};

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

		// "Clear" the window from previouly drawn graphics
		window.clear(sf::Color::Black);

		window.draw(ball.mShape);
		window.draw(paddle.mShape);
		window.display();
	}

	return 0;
}
