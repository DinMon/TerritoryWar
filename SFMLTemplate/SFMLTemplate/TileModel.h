#pragma once
#include "TileEnum.h"
#include <SFML\Graphics.hpp>

class TileModel
{
public:
	TileModel(TileEnum);
	~TileModel();
	sf::Texture* GetTexture();
	bool GetIsObstacle();
private:
	//Textures
	sf::Texture fTileTexture;
	//Sprites
	sf::Sprite fTileSprite;
	bool fIsObstacle;
};

