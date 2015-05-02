#include "ball.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

int main()
{
	const unsigned int windowWidth{800}, windowHeight{600};

	Ball ball{windowWidth / 2, windowHeight / 2};

	sf::RenderWindow window({windowWidth, windowHeight}, "Arkanoid");
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

		// "Clear" the window from previouly drawn graphics
		window.clear(sf::Color::Black);

		window.draw(ball.shape);
		window.display();
	}

	return 0;
}
