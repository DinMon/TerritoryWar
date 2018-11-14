#include "Map.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "StringUtil.h"

#define RECTDIMENSION 32

int Map::fColumn = 0;
int Map::fRow = 0;
std::vector<sf::Vector2i> Map::fObstructionCoord = {};

Map::Map(sf::RenderWindow* aWindow)
{
	fWindow = aWindow;
	fGroundTile = new TileModel(TileEnum::Ground);
	fWallTile = new TileModel(TileEnum::Barrier);
	LoadMap("level1.txt");
}

Map::~Map()
{
}

void Map::LoadMap(std::string aFileName)
{
	int lColumnNum = 0;
	std::string line;
	std::ifstream myfile(aFileName);
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			std::vector<std::string> tokens = StringUtil::SplitString(line, ",");
			for (auto &type : tokens)
			{
				switch (std::stoi(type))
				{
				case 0:
					map[fRow][fColumn] = Tile(fGroundTile, fRow, fColumn);
					break;
				case 1:
					map[fRow][fColumn] = Tile(fWallTile, fRow, fColumn);
					fObstructionCoord.push_back(sf::Vector2i(fRow, fColumn)); //double check
					break;
				default:
					break;
				}
				fColumn++;
			}
			lColumnNum = fColumn;
			fColumn = 0;
			fRow++;
		}
	}
	fColumn = lColumnNum;
}

void Map::DrawMap()
{
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 20; column++)
		{
			map[row][column].GetSprite()->setPosition(column * RECTDIMENSION, row * RECTDIMENSION);

			fWindow->draw(*(map[row][column].GetSprite()));
		}
	}
}

sf::Vector2i Map::MapLength()
{
	return sf::Vector2i(fColumn, fRow);
}

inline float clamp(float x, float a, float b)
{
	return x < a ? a : (x > b ? b : x);
}

sf::Vector2i Map::GetMapCoordinate(sf::Vector2f worldPosition)
{
	int x, y;
	sf::Vector2f gridWorldSize = sf::Vector2f(RECTDIMENSION * fColumn, RECTDIMENSION * fRow);

	float percentX = ((worldPosition.x) / gridWorldSize.x);
	float percentY = ((worldPosition.y) / gridWorldSize.y);

	percentX = clamp(percentX, 0, 1);
	percentY = clamp(percentY, 0, 1);

	x = round((fColumn - 1) * percentX);
	y = round((fRow - 1) * percentY);

	return sf::Vector2i(x, y);
}

std::vector<sf::Vector2i> Map::GetObstructionCoord()
{
	return fObstructionCoord;
}


