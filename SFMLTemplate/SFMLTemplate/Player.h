#pragma once
#include <SFML\Graphics.hpp>

class Player
{
public:
	Player();
	~Player();
	void Move(int, int, sf::RenderWindow*);
	sf::Sprite getSprite();
private:
	void loadMedia();
	void RetainInWindow(sf::RenderWindow*);
	
	//Textures
	sf::Texture fPlayerTexture;

	//Sprites
	sf::Sprite fPlayerSprite;
};

