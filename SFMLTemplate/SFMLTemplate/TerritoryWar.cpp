#include <SFML\Graphics.hpp>
#include "StageManager.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Game");

	while (window.isOpen())
	{
		// handle events
		StageManager::Instance(&window)->HandleInput();
		
		// update
		StageManager::Instance(&window)->HandleUpdate();
		
		window.clear();

		// draw objects
		StageManager::Instance(&window)->HandleDraw();

		window.display();
	}
}