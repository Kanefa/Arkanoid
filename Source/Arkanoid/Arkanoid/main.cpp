#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>


int main()
{
	const unsigned int windowWidth{800}, windowHeight{600};
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

		// Show the window contents
		window.display();
	}

	return 0;
}
