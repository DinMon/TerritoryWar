#pragma once
#include <SFML\Graphics.hpp>

class Stage
{
public:
	Stage() {};
	~Stage() {};
	virtual void Update() = 0;
	virtual void Draw(sf::RenderWindow*) = 0;
	virtual void GetInput(sf::RenderWindow*) = 0;
};

