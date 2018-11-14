#pragma once
#include "TileModel.h"
#include "Tile.h"
#include <string>
#include <vector>

class Map
{
public:
	Map(sf::RenderWindow*);
	~Map();

	void LoadMap(std::string);
	void DrawMap();
	static sf::Vector2i MapLength();
	static sf::Vector2i GetMapCoordinate(sf::Vector2f);
	static std::vector<sf::Vector2i> GetObstructionCoord();
private:
	static int fRow, fColumn;
	static std::vector<sf::Vector2i> fObstructionCoord;
	sf::RenderWindow* fWindow;
	TileModel* fGroundTile;
	TileModel* fWallTile;

	Tile map[10][10];
};

