#include "Tile.h"

Tile::Tile(TileModel* aTileModel, int aX, int aY)
{
	fSelected = false;
	fTileModel = aTileModel;
	fTileSprite.setTexture(*(fTileModel->GetTexture()));
	fCoordinate = sf::Vector2i(aX, aY);
}

Tile::Tile()
{
}

Tile::~Tile()
{
}

TileModel * Tile::GetTileModel()
{
	return fTileModel;
}

sf::Vector2i Tile::GetCoordinate()
{
	return fCoordinate;
}

bool Tile::GetIsSelected()
{
	return fSelected;
}

sf::Sprite* Tile::GetSprite()
{
	return &fTileSprite;
}

void Tile::SetIsSelected(bool aValue)
{
	fSelected = aValue;
}
