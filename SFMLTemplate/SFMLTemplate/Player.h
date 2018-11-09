#pragma once
#include <SFML\Graphics.hpp>

class Player
{
public:
	Player();
	~Player();
	void Move(int, int, sf::RenderWindow*);
	void LookAt(int, int);
	sf::Sprite getSprite();
private:
	void loadMedia();
	void RetainInWindow(sf::RenderWindow*);
	
	bool fToRotate;
	//Textures
	sf::Texture fPlayerTexture;

	//Sprites
	sf::Sprite fPlayerSprite;
};

