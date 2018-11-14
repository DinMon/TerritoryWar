#pragma once
#include <SFML\Graphics.hpp>
#include "TileModel.h"
	
class Tile
{
public:
	Tile(TileModel*, int, int);
	Tile();
	~Tile();
	TileModel* GetTileModel();
	sf::Vector2i GetCoordinate();
	bool GetIsSelected();
	sf::Sprite* GetSprite();
	void SetIsSelected(bool);
private:
	TileModel* fTileModel;
	sf::Sprite fTileSprite;
	sf::Vector2i fCoordinate;
	bool fSelected;
};

