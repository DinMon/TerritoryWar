#include <SFML\Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Game");

	while (window.isOpen())
	{
		// handle events

		// update

		window.clear();

		// draw objects

		window.display();
	}
}