#pragma once
#include <SFML\Graphics.hpp>
#include "ComponentHolder.h"

class Entity
{
public:
	Entity(std::string);
	virtual ~Entity() {};
	sf::Sprite getSprite();
	ComponentHolder* GetComponentContainer();
	int GetId();
	std::string GetName();
protected:
	int fId;
	std::string fName;

	ComponentHolder* fComponentContainer;

	virtual void loadMedia() = 0;

	//Textures
	sf::Texture fEntityTexture;

	//Sprites
	sf::Sprite fEntitySprite;
};
