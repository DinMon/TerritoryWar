#include "TileModel.h"

TileModel::TileModel(TileEnum type)
{
	switch (type)
	{
	case Ground:
		if (!fTileTexture.loadFromFile("data/images/metal.png"))
		{
			throw "Cannot load texture";
		}
		fIsObstacle = false;
		break;
	case Barrier:
		if (!fTileTexture.loadFromFile("data/images/box.png"))
		{
			throw "Cannot load texture";
		}
		fIsObstacle = true;
		break;
	default:
		break;
	}
}

TileModel::~TileModel()
{
}

sf::Texture* TileModel::GetTexture()
{
	return &fTileTexture;
}

bool TileModel::GetIsObstacle()
{
	return fIsObstacle;
}
